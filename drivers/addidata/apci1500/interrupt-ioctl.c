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
#include <linux/fs.h>
#include <linux/pci.h>
#include <linux/version.h>
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

#include "apci1500-private.h"


EXPORT_NO_SYMBOLS;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,27)
	#define __user 
#endif

//--------------------------------------------------------------------------------------------------

/** Wait on interrupt. 
 * 
 * This function block until an interrupt occured 
 * and value are available 
 */
int do_CMD_APCI1500_WaitInterrupt(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	uint32_t dw_ArgTable[2];	

	/* the following doesn't need interrupt locking because:
	 * 1) APCI1500_PRIVDATA(pdev)->wq has already a sping_lock implemented
	 * 2) GET_EVENT_CPTW() and GET_EVENT_CPTR() implement atomic type
	 *  */
	if (wait_event_interruptible (APCI1500_PRIVDATA(pdev)->wq, GET_EVENT_CPTW(pdev) != GET_EVENT_CPTR(pdev)))
		return -ERESTARTSYS;

	if (GET_EVENT_CPTW(pdev) != GET_EVENT_CPTR(pdev))
	{
		/* the code below needs to be protected against modification from interrupt  */
		unsigned long irqstate;
		APCI1500_LOCK(pdev,&irqstate);
		{
			dw_ArgTable[0] = APCI1500_PRIVDATA(pdev)->dw_InterruptSource[GET_EVENT_CPTR(pdev)];
			dw_ArgTable[1] = APCI1500_PRIVDATA(pdev)->dw_ValueArray[GET_EVENT_CPTR(pdev)];
			SET_EVENT_CPTR(pdev, ((GET_EVENT_CPTR(pdev) + 1 ) % APCI1500_MAX_EVENT_COUNTER) );
		}		
		APCI1500_UNLOCK(pdev,irqstate);
	}
	else
	{
		/* FIFO empty */
		dw_ArgTable[0] = 0x7ffffffe;
	}

    /* Transfers the value to the user */
	if ( copy_to_user((uint32_t __user *) arg , dw_ArgTable, sizeof(dw_ArgTable) ) )
    	return -EFAULT;	    	

	return 0;
}

//--------------------------------------------------------------------------------------------------
/* activate interrupt */
int
do_CMD_APCI1500_SetBoardIntRoutine(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate;
	int ret;
	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_PrivateSetBoardIntRoutine(pdev);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	return ret;
}
//--------------------------------------------------------------------------------------------------
/* deactivate interrupt from card */
int
do_CMD_APCI1500_ResetBoardIntRoutine(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	unsigned long irqstate;
	int ret;
	APCI1500_LOCK(pdev,&irqstate);
	{
		ret = i_APCI1500_ResetBoardIntRoutine(pdev);
	}
	APCI1500_UNLOCK(pdev,irqstate);
	return ret;
}
