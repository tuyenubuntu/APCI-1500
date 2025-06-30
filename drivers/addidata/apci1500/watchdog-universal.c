/** @par LICENCE
* @verbatim
Copyright (C) 2004,2005  ADDI-DATA GmbH for the source code of this module.
        
        ADDI-DATA GmbH 
        Dieselstrasse 3 
        D-77833 Ottersweier 
        Tel: +19(0)7223/9493-0 
        Fax: +49(0)7223/9493-92 
        http://www.addi-data-com 
        info@addi-data.com 
        
This program is free software; you can redistribute it and/or modify it under 
the terms of the GNU General Public License as published by the Free Software 
Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with 
this program; if not, write to the Free Software Foundation, 
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

You shoud also find the complete GPL in the COPYING file 
accompanying this source code.
* @endverbatim
*/
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
	#include <linux/config.h>
#else
	#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,33)
		#include <linux/autoconf.h>
	#else
		#include <generated/autoconf.h>
	#endif
#endif
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/pci.h>
#include <asm/io.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0)
	#include <asm/system.h>
#endif
//#include <asm/system.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,12,0)
	#include <asm/uaccess.h>
#else
	#include <linux/uaccess.h>
#endif
#include <asm/bitops.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/delay.h>

#include "apci1500-private.h"

EXPORT_NO_SYMBOLS;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,27)
	#define __user 
#endif

#define WATCHDOG_CURRENT_VALUE(__base)  (__base + 4)
#define WATCHDOG_CTRL_RGSTR(__base)  (__base + 6)
#define WATCHDOG_RELOAD_VALUE_RGSTR(__base) ( __base + 8)
#define WATCHDOG_OVERFLOW_STATUS(__base) ( __base + 6)


/** Initialise and start the watchdog.
 * 
 * @param[in,out] pdev Internal information of the card.
 * @param[in] arg Configuration parameters.
 * 
 * arg encodes two information:
 * - HISHORT(arg) contains the mode of the watchdog 
 * - LOSHORT(arg) is the reload value.
 * 
 * This file manage the "new" watchdog, which is built-in in the board and not located on the Zilog.
 * 
 * 
 * 
 *  */

#define MSG_UNAVAILABLE() printk(KERN_WARNING "apci 1500: timer 3 is not available on this board\n")

//------------------------------------------------------------------------------
int
do_CMD_APCI1500_InitWatchdogCounter3(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{

	unsigned long irqstate = 0; /**< save local interrupt flag*/
	int ret;
	
	APCI1500_LOCK(pdev, &irqstate);
	{
		ret = i_APCI1500_InitWatchdogCounter3(pdev,arg);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	return ret;
}

//------------------------------------------------------------------------------
int
do_CMD_APCI1500_TriggerWatchdog(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{

	unsigned long irqstate = 0; /**< save local interrupt flag*/
	int ret;

	/* Set trigger bit  */
	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_TriggerWatchdog(pdev);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	return ret;
}

//------------------------------------------------------------------------------
int
do_CMD_APCI1500_TriggerCounter3( struct pci_dev * pdev , unsigned int cmd, unsigned long arg)
{
	/* this function does nothing, doesn't need to be locked */
	return i_APCI1500_TriggerCounter3(pdev);
}
//------------------------------------------------------------------------------
int
do_CMD_APCI1500_StopCounter3(struct pci_dev * pdev , unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate = 0; /**< save local interrupt flag*/
	int ret;
	
	APCI1500_LOCK(pdev,&irqstate);
	/* Unset watchdog start (enable) bit  */
	{		
		ret = i_APCI1500_StopCounter3(pdev);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	
	return ret;
}
//------------------------------------------------------------------------------
int do_CMD_APCI1500_EnableDisableWatchdogCounter3Interrupt(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	MSG_UNAVAILABLE();
	return -ENODEV;
}

//------------------------------------------------------------------------------
/** enable and start the watchdog */
int
do_CMD_APCI1500_StartCounter3(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate = 0; /**< save local interrupt flag*/	
	int ret;
	APCI1500_LOCK(pdev,&irqstate);
	/* Set watchdog enable bit  */
	{
		ret = i_APCI1500_StartCounter3(pdev);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	return ret;
}

//-------------------------------------------------------------------
int
do_CMD_APCI1500_ReadCounter3(struct pci_dev* pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate = 0; /**< save local interrupt flag*/	
	unsigned long value = 0;	
	int ret;
		
	APCI1500_LOCK(pdev,&irqstate);
	/* Set watchdog enable bit  */
	{
		ret = i_APCI1500_ReadCounter3(pdev, &value);			
	}
	APCI1500_UNLOCK(pdev,irqstate);	
	
	if(ret)
		return ret;
	
	if ( put_user(value, (long __user *) arg) )
		return -EFAULT;
	
	return 0;
}

//-------------------------------------------------------------------
int
do_CMD_APCI1500_GetWatchdogStatus(struct pci_dev* pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long status = 0;
		
	//Overflow
	if( inw(WATCHDOG_OVERFLOW_STATUS(GET_BAR2(pdev)) ) & 0x2 )
	{
		status = APCI1500_WATCHDOG_STATE_OVERFLOWED;
		goto fin;
	}

	// Enable bit set
	if( inw( WATCHDOG_CTRL_RGSTR(GET_BAR2(pdev)) ) & 0x1 )
			status = APCI1500_WATCHDOG_STATE_ENABLED;

	fin:	

	if ( put_user(status, (unsigned long __user *) arg) )
		return -EFAULT;	
		
	return 0;
}
//-------------------------------------------------------------------
int 
do_CMD_APCI1500_GetWatchdogReloadValue(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	volatile unsigned long reloadvalue = 0;
	
	reloadvalue = inw( WATCHDOG_RELOAD_VALUE_RGSTR(GET_BAR2(pdev) ) );	;
	
	if ( put_user(reloadvalue, (unsigned long __user *) arg) )
		return -EFAULT;	
			
	return 0;
}
