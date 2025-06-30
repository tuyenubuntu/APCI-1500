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

/* interrupt kernel API */

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

EXPORT_SYMBOL(i_APCI1500_SetBoardIntRoutine);
EXPORT_SYMBOL(i_APCI1500_ResetBoardIntRoutine);
EXPORT_SYMBOL(i_APCI1500_TestInterrupt);

EXPORT_NO_SYMBOLS;

//------------------------------------------------------------------------------
/**  */
int 
APCI1500_SetIntCallback( void(*InterruptCallback) (struct pci_dev * pdev , char dummy))
{
	apci1500_private_InterruptCallback = InterruptCallback;
	return 0;
}

//------------------------------------------------------------------------------

int 
APCI1500_ResetIntCallback(void)
{
	apci1500_private_InterruptCallback = NULL;
	return 0;
}

//--------------------------------------------------------------------------------------------------

/** Return interrupt values. 
 */
int i_APCI1500_TestInterrupt(struct pci_dev * pdev, unsigned long *arg)
{
	if (GET_EVENT_CPTW(pdev) != GET_EVENT_CPTR(pdev))
	{
		arg[0] = APCI1500_PRIVDATA(pdev)->dw_InterruptSource[GET_EVENT_CPTR(pdev)];
		arg[1] = APCI1500_PRIVDATA(pdev)->dw_ValueArray[GET_EVENT_CPTR(pdev)];		
			
		SET_EVENT_CPTR(pdev, ((GET_EVENT_CPTR(pdev) + 1 ) % APCI1500_MAX_EVENT_COUNTER) );
	}
	else
	{
		/* FIFO empty */
		arg[0] = 0x7ffffffe;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------------

/* activate interrupt 
 * 
 * @retval 0 on success
 * @retval -EBUSY if IRQ registration failed
 * 
 * 
 * */
int i_APCI1500_PrivateSetBoardIntRoutine(struct pci_dev * pdev)
{

	volatile uint8_t b_RegValue;
	volatile uint32_t ul_Status;	
	
	APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_InterruptStatus = APCI1500_ENABLE;
	
	/* changes below are atomic, yet they must be done with IRQ deactivated,  */

	/* initialize event FIFO */

	SET_EVENT_CPTR(pdev, 0);
	SET_EVENT_CPTW(pdev, 0);

	DELAY();
		
	outl(0x3000UL, GET_BAR0(pdev) + 0x38);
	ul_Status = inl(GET_BAR0(pdev) + 0x10);
	ul_Status = inl(GET_BAR0(pdev) + 0x38);
	outl(0x23000UL, GET_BAR0(pdev) + 0x38);

	outb_mb(APCI1500_RW_PORT_B_SPECIFICATION, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_PORT_B_SPECIFICATION,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	b_RegValue = (uint8_t) ((b_RegValue & 0xF9) | APCI1500_OR);

	outb_mb(b_RegValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(0xC0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_PORT_B_PATTERN_POLARITY,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(0xC0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_PORT_B_PATTERN_TRANSITION,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(0xC0, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_PORT_B_PATTERN_MASK,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(0xC0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb((uint8_t) ((b_RegValue & 0x0F) | 0x20),GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER);

	b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb((uint8_t) ((b_RegValue & 0x0F) | 0x20),GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb((uint8_t) ((b_RegValue & 0x0F) | 0x20),GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	outb_mb(APCI1500_RW_CPT_TMR2_CMD_STATUS,GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER);
	
	b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	outb_mb(APCI1500_RW_CPT_TMR2_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	outb_mb((uint8_t) ((b_RegValue & 0x0F) | 0x20), GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb((uint8_t) ((b_RegValue & 0x0F) | 0x20),GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	outb_mb(APCI1500_RW_MASTER_INTERRUPT_CONTROL,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	outb_mb(0xD0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	printk(KERN_DEBUG "%s: board %s: interrupt deactivated\n",__DRIVER_NAME,pci_name(pdev));

	return 0;
}

//--------------------------------------------------------------------------------------------------

int i_APCI1500_SetBoardIntRoutine(struct pci_dev * pdev, void(*InterruptCallback)(struct pci_dev * pdev , char dummy))
{
	if ( apci1500_interrupt_is_enabled(pdev) )
	{
		printk(KERN_ERR "%s: board %s: IRQ already initialized\n", __DRIVER_NAME,pci_name(pdev));
		return  -EBUSY;
	}
	{
		int ret = i_APCI1500_PrivateSetBoardIntRoutine(pdev);
		if(ret) return ret;
	}

	APCI1500_SetIntCallback(InterruptCallback);
	
	return 0;
}

//--------------------------------------------------------------------------------------------------
/* deactivate interrupt from card */
int i_APCI1500_ResetBoardIntRoutine(struct pci_dev * pdev)
{

	//Test if SetBoardIntRoutine function as been loaded (test internal state information : are interrupt disabled ?)
	if ( ! apci1500_interrupt_is_enabled(pdev) )
	{
		return -EINVAL;
	}

	DELAY();	
	
	/* Disable the board interrupt */

	/* Selects the master interrupt control register */

	outb_mb(APCI1500_RW_MASTER_INTERRUPT_CONTROL,GET_BAR1(pdev) +
		APCI1500_Z8536_CONTROL_REGISTER);


	/* Deactivates all interrupts */

	outb_mb(0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the command and status register of port A */

	outb_mb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Deactivates the interrupt */

	outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the command and status register of port B */

	outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER);


	/* Deactivates the interrupt */

	outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the command and status register of timer 1 */

	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Deactivates the interrupt */

	outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the command and status register of timer 2 */

	outb_mb(APCI1500_RW_CPT_TMR2_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Deactivates the interrupt */

	outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Test if counter/watchdog 3 used for counter or                   */
	/* used for watchdog and permentlay watchdog functionality disabled */

	if ( IS_COUNTER3_WATCHDOG(pdev) ) 
	{
		/* Selects the command and status register of timer 3 */

		outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Deactivates the interrupt and the gate */      
		outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	}

	else 
	{
		/* Selects the command and status register of timer 3 */
		outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Deactivates the interrupt and the gate */      
		outb_mb(0xE4,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);                        
	}
	/* set internal state information that interrupt are disabled*/
	APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_InterruptStatus = APCI1500_DISABLE;
	
	APCI1500_ResetIntCallback ();
	
	printk(KERN_DEBUG "%s: board %s: interrupt deactivated\n",__DRIVER_NAME,pci_name(pdev));

	return 0;	
}
