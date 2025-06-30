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
#include <linux/init.h>

#include "apci1500-private.h"


EXPORT_NO_SYMBOLS;

//-------------------------------------------------------------------

/* not used yet */
//static int do_CMD_APCI1500_SetInputEventMask_PortNumber1(struct pci_dev* pdev, unsigned long arg)
//{
//	unsigned long irqstate;
//	int ret;
//	APCI1500_LOCK(pdev,&irqstate);
//	{
//		ret = i_APCI1500_SetInputEventMask_PortNumber1(pdev, arg);
//	}
//	APCI1500_UNLOCK(pdev,irqstate);
//	return ret;
//}

//-------------------------------------------------------------------

/* not used yet */
//static int do_CMD_APCI1500_SetInputEventMask_PortNumber2(struct pci_dev* pdev, unsigned long arg)
//{
//	unsigned long irqstate = 0; /**< save local interrupt flag*/			
//	int ret;
//	
//	APCI1500_LOCK(pdev, &irqstate);
//	{
//		ret = i_APCI1500_SetInputEventMask_PortNumber2(pdev, arg);
//	}
//	APCI1500_UNLOCK(pdev,irqstate);
//	
//	return ret;
//
//}

//-------------------------------------------------------------------
/**
* @param pdev Pointer to a struct pci_dev 
* @param arg configuration values for port
* 
* 
*/
int
do_CMD_APCI1500_SetInputEventMask(struct pci_dev* pdev, unsigned int cmd, unsigned long arg)
{
	return (i_APCI1500_SetInputEventMask(pdev, arg));	
}

//------------------------------------------------------------------------------
/*
 * @param arg (long) Contains the port(s) to start : APCI1500_INPUT_PORT_1 et/or APCI1500_INPUT_PORT_2
 * actually port "1" is port "A" in Zilog documentation, port "2" is port "B" in Zilog documentation
 */
int
do_CMD_APCI1500_StartInputEvent(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate;
	int ret;
	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_StartInputEvent(pdev, arg);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	
	return ret;	
}

//------------------------------------------------------------------------------
/*
 * @param arg (long) Contains the port(s) to start : APCI1500_INPUT_PORT_1 et/or APCI1500_INPUT_PORT_2
 * actually port "1" is port "A" in Zilog documentation, port "2" is port "B" in Zilog documentation
 */
int
do_CMD_APCI1500_StopInputEvent(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate;
	int ret;

	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_StopInputEvent(pdev, arg);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	
	return ret;
	
}

