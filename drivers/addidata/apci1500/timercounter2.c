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

#include <linux/module.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,12,0)
	#include <asm/uaccess.h>
#else
	#include <linux/uaccess.h>
#endif
#include <asm/io.h>

#include "apci1500-private.h"

EXPORT_NO_SYMBOLS;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,27)
	#define __user 
#endif

//------------------------------------------------------------------------------
int
do_CMD_APCI1500_InitTimerCounter2(struct pci_dev* pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate;
	int ret;
	APCI1500_LOCK(pdev,&irqstate);  
	{
		ret = i_APCI1500_InitTimerCounter2(pdev, arg);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	
	return ret;
}

//------------------------------------------------------------------------------
int
do_CMD_APCI1500_ReadTimerCounter2(struct pci_dev* pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long l_ReadValue = 0;
	int ret = 0;
	unsigned long irqstate = 0; /**< save local interrupt flag*/
	
	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_ReadTimerCounter2(pdev, &l_ReadValue);
	}
	APCI1500_UNLOCK(pdev,irqstate);

	if (ret)
		return ret;
	
	if ( put_user((unsigned long) l_ReadValue, ( unsigned long __user *) arg) )
		return -EFAULT;
	
	return 0;
}

//------------------------------------------------------------------------------
int do_CMD_APCI1500_TriggerTimerCounter2(struct pci_dev* pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate;
	int ret;
	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_TriggerTimerCounter2(pdev);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	
	return ret;
}

//------------------------------------------------------------------------------
int
do_CMD_APCI1500_StopTimerCounter2(struct pci_dev* pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate;
	int ret;
	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_StopTimerCounter2(pdev);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	
	return ret;
}
//------------------------------------------------------------------------------

int 
do_CMD_APCI1500_EnableDisableTimerCounter2Interrupt(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate;
	int ret;
	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_EnableDisableTimerCounter2Interrupt(pdev, arg);
	}
	APCI1500_UNLOCK(pdev,irqstate);

	return ret;
}

//------------------------------------------------------------------------------

int
do_CMD_APCI1500_StartTimerCounter2(struct pci_dev* pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate;
	int ret;
	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_StartTimerCounter2(pdev);
	}
	APCI1500_UNLOCK(pdev,irqstate);

	return ret;
}
