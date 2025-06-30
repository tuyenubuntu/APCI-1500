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
int i_APCI1500_InitWatchdogCounter3(struct pci_dev * pdev , unsigned long arg)
{
	
	/* Test if b_CounterOrWatchdogSelect == APCI1500_COUNTER */
	if ( GET_TIMERMODE(arg) & APCI1500_COUNTER) 
	{
		/* timer 3 is no more available */		
		MSG_UNAVAILABLE();
	 	return -ENODEV;		
	}

	APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_WatchdogCounter3Select = APCI1500_WATCHDOG;
	
	/* (Re)initialisation of watchdog = set all bit to 0 */	
	{
		u16 val = 0x0000;
		outw(val, WATCHDOG_CTRL_RGSTR( GET_BAR2(pdev) ) );
	}


	/* set reload value */
	{
		/*reload value is 16 bits wide */
		outw( GET_RELOADVALUE(arg) , WATCHDOG_RELOAD_VALUE_RGSTR(GET_BAR2(pdev) ) );	
		printk(KERN_INFO "apci 1500: watchdog initialized with reload value 0x%X\n",GET_RELOADVALUE(arg));
	}
	
	/* Enable the watchdog (reread value) = set  */
	{
		outw( 0x0001,WATCHDOG_CTRL_RGSTR( GET_BAR2(pdev)) ); 
	}
	
	/* now the watchdog should be started.
	* Let be paranoid and check that.
	* */
	{
		volatile  u16 val = inw(WATCHDOG_CTRL_RGSTR( GET_BAR2(pdev)) );	
		
		if ( ! (val & 0x0001) )
		{
			printk("apci 1500: %s: error, watchdog enable bit has not been set\n",__FUNCTION__ );
			return -EINVAL;
		}
	}

	return 0;
}

//------------------------------------------------------------------------------
int i_APCI1500_TriggerWatchdog(struct pci_dev * pdev)
{

	/* TODO: perform checks here */

	volatile u16 val = inw(WATCHDOG_CTRL_RGSTR( GET_BAR2(pdev) ) );		
	mb();
	
	/* watchdog enabled ? */
	if (! (val & 0x0001) )
	{
		printk( KERN_WARNING "apci 1500: watchdog trigger but watchdog not enabled\n");
		return -1;
	}

	/* set trigger bit */
	val = val | 0x0200; 
	
	outw( val , WATCHDOG_CTRL_RGSTR( GET_BAR2(pdev) ) ); 
			
	return 0;
}

//------------------------------------------------------------------------------
int i_APCI1500_TriggerCounter3(struct pci_dev * pdev)
{
	MSG_UNAVAILABLE();
	return -ENODEV;
}
//------------------------------------------------------------------------------
int i_APCI1500_StopCounter3(struct pci_dev * pdev)
{		
	/* unset start (enable) bit */				
	outw( 0x0 , WATCHDOG_CTRL_RGSTR( GET_BAR2(pdev) ) ); 
	return 0;	
}

//------------------------------------------------------------------------------
/** enable and start the watchdog */
int i_APCI1500_StartCounter3(struct pci_dev * pdev)
{
	/* read the control register */
	volatile u16 val = inw(WATCHDOG_CTRL_RGSTR( GET_BAR2(pdev) ) );		
	mb();
		
	/* watchdog enabled ? */
	if ( (val & 0x0001) )
	{
		return 0; /* still started, no need to start it again ! */
	}

	/* Set the enable + trigger bits  */		
	outw( 0x201 , WATCHDOG_CTRL_RGSTR( GET_BAR2(pdev) ) ); 

	return 0;		
}

//------------------------------------------------------------------------------
/**  interrupt manager for watchdog.
* locked by caller 
*/
void do_watchdog_interrupt(struct pci_dev * pdev, uint8_t * b_InterruptMask)
{
	/* the universal watchdog generates no interrupt */
	return ;			
}
//-------------------------------------------------------------------
int i_APCI1500_ReadCounter3(struct pci_dev* pdev, unsigned long *arg)
{			
	/* read the control register */
	volatile uint16_t val = inw(WATCHDOG_CURRENT_VALUE( GET_BAR2(pdev) ) );		
	mb();		
	*arg = val;
	return 0;
}
