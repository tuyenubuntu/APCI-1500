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

/* core interrupt functionalities (handler and so on, except for watchdog ) */

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

//------------------------------------------------------------------------------
/* global interrupt call back */
void (*apci1500_private_InterruptCallback) (struct pci_dev * pdev, char dummy) = NULL;

//------------------------------------------------------------------------------
/* locked by caller */
static __inline__ void do_port1_interrupt( struct pci_dev * pdev, uint8_t * b_InterruptMask)
{
	volatile uint8_t b_RegValue;

	/* Tests if an interrupt occured on port 1 */
	/* Selects the port 1 command register     */
	outb_mb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Reads the command register of port 1 */
	b_RegValue =
	    inb_mb( GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* If the RegValue == 0x60, an interrupt occurs */
	if ((b_RegValue & 0x60) == 0x60)
	{
		/* Event 1 occured */
		*b_InterruptMask =  *b_InterruptMask | 0x01;

		/* Selects the port 1 command register */
		outb_mb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Prepares the variable to reset the interrupt */
		b_RegValue = (b_RegValue & 0x0F) | 0x20;

		/* Writes the new RegValue to the board */
		outb_mb(b_RegValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	}
}
//------------------------------------------------------------------------------
/* locked by caller */
static __inline__ void do_port2_interrupt(struct pci_dev * pdev, uint8_t * b_InterruptMask)
{
	volatile uint8_t b_RegValue;

	/* Tests if an interrupt occured on port 2 */
	/* Selects the port 2 command register     */
	outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Reads the command register of port 2 */
	b_RegValue = inb_mb( GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* If the RegValue == 0x60, an interrupt occurs */
	if ((b_RegValue & 0x60) == 0x60)
	{

		/* Event 2 occured */
		*b_InterruptMask =  *b_InterruptMask | 0x02;

		/* Selects the port 2 command register */
		outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Prepares the variable to reset the interrupt */
		b_RegValue = (b_RegValue & 0x0F) | 0x20;

		/* Writes the new RegValue to the board */
		outb_mb(b_RegValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	}
}
//------------------------------------------------------------------------------
/* locked by caller */
static __inline__ void do_timer1_interrupt(struct pci_dev * pdev, uint8_t * b_InterruptMask)
{

	volatile uint8_t b_RegValue;
	/* Tests if an interrupt occured from timer 1 */
	/* Selects the timer 1 command register       */
	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Reads the command register of timer 1 */
	b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* If the RegValue == 0x60, an interrupt occurs */
	if ((b_RegValue & 0x60) == 0x60)
	{
		/* Counter/Timer 1 */
		*b_InterruptMask =  *b_InterruptMask | 0x04;

		/* Selects the timer 1 command register       */
		outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Prepares the variable to reset the interrupt */
		b_RegValue = ((b_RegValue & 0x0F) | 0x20);

		/* Writes the new RegValue to the board */
		outb_mb(b_RegValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	}
}
//------------------------------------------------------------------------------
/* locked by caller */
static __inline__ void do_timer2_interrupt(struct pci_dev * pdev, uint8_t * b_InterruptMask)
{

	volatile uint8_t b_RegValue;
	/* Tests if an interrupt occured from timer 2 */
	/* Selects the timer 2 command register       */
	outb_mb(APCI1500_RW_CPT_TMR2_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Reads the command register of timer 2 */
	b_RegValue = inb_mb( GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* If the RegValue == 0x60, an interrupt occurs */
	if ((b_RegValue & 0x60) == 0x60)
	{
		/* Counter/Timer 2 */
		*b_InterruptMask =  *b_InterruptMask | 0x08;

		/* Selects the timer 2 command register       */
		outb_mb(APCI1500_RW_CPT_TMR2_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Prepares the variable to reset the interrupt */
		b_RegValue = ((b_RegValue & 0x0F) | 0x20);

		/* Writes the new RegValue to the board */
		outb_mb(b_RegValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	}
}

//------------------------------------------------------------------------------
/** Interrupt handler.
*
* This function is called if an interrupt occurs. Its the top half IRQ.
*
* @note actually dev_id is the struct pci_dev * defining the board.
*
*/

/** IRQ handler prototype has changed between 2.4 and 2.6.
 * in 2.4 the handler has not return value, in 2.6 it is of type irqreturn_t
 * IRQ_HANDLED means that the device did indeed need attention from the driver
 * IRQ_NONE means that the device didn't actually need attention
 *
 * NOTE: the change between 2.4 and 2.6 was not so important that it needed
 * two version of the function. BUT if in the course of the implementation you
 * notice the changes are so important that maintaining a code for both version
 * in one function is just a hassle, DON'T HESITATE and create two versions
 * of the same function.
 *
 */

/** IRQ Handler */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)	/* 2.4  */
	#define RETURN_HANDLED return
	#define RETURN_NONE return
#else
	#define RETURN_HANDLED return IRQ_HANDLED
	#define RETURN_NONE return IRQ_NONE
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)	/* 2.4  */
	static void apci1500_do_interrupt(int irq, void * dev_id, struct pt_regs *regs)
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
	static irqreturn_t apci1500_do_interrupt(int irq, void * dev_id, struct pt_regs *regs)
#else
	static irqreturn_t apci1500_do_interrupt(int irq, void * dev_id)
#endif
{
	unsigned long irqstate;
	uint8_t b_InterruptMask = 0;
	volatile uint16_t ui_TmpValue = 0;

	APCI1500_LOCK( VOID_TO_PCIDEV(dev_id) , &irqstate);
	{
		volatile uint32_t ul_Status;

		/* Read status of digital inputs */
		ui_TmpValue = inw_mb(GET_BAR2(VOID_TO_PCIDEV(dev_id)));

		/* Reads the status of the interrupt register */
		ul_Status = inl_mb( GET_BAR0(VOID_TO_PCIDEV(dev_id)) + 0x38);

		/* if status == 0x800000UL, an interrupt occured
		* otherwise, return
		* @note: could this happen in case of shared interrupt, or never ?
		*/
		if (!((ul_Status & 0x800000UL) == 0x800000UL))
		{
			APCI1500_UNLOCK(VOID_TO_PCIDEV(dev_id), irqstate);
			RETURN_NONE;
			//return;
		}

		do_port1_interrupt(VOID_TO_PCIDEV(dev_id),&b_InterruptMask);

		do_port2_interrupt(VOID_TO_PCIDEV(dev_id),&b_InterruptMask);

		do_timer1_interrupt(VOID_TO_PCIDEV(dev_id),&b_InterruptMask);

		do_timer2_interrupt(VOID_TO_PCIDEV(dev_id),&b_InterruptMask);

		do_watchdog_interrupt(VOID_TO_PCIDEV(dev_id),&b_InterruptMask);

		if (b_InterruptMask & 0x3F) {
		    /* Copy informations in the FIFO */

			if (((GET_EVENT_CPTW(VOID_TO_PCIDEV(dev_id)) + 1 ) % APCI1500_MAX_EVENT_COUNTER) != GET_EVENT_CPTR(VOID_TO_PCIDEV(dev_id)))
				{
				APCI1500_PRIVDATA(VOID_TO_PCIDEV(dev_id))->dw_InterruptSource[GET_EVENT_CPTW(VOID_TO_PCIDEV(dev_id))] = b_InterruptMask;
				APCI1500_PRIVDATA(VOID_TO_PCIDEV(dev_id))->dw_BoardID[GET_EVENT_CPTW(VOID_TO_PCIDEV(dev_id))] = APCI1500_PRIVDATA(VOID_TO_PCIDEV(dev_id))->i_MinorNumber;

				/* If event interrupt, save digital input status */
				if (b_InterruptMask & 3)
					APCI1500_PRIVDATA(VOID_TO_PCIDEV(dev_id))->dw_ValueArray[GET_EVENT_CPTW(VOID_TO_PCIDEV(dev_id))] = ui_TmpValue;
				else
				    APCI1500_PRIVDATA(VOID_TO_PCIDEV(dev_id))->dw_ValueArray[GET_EVENT_CPTW(VOID_TO_PCIDEV(dev_id))] = 0;

				SET_EVENT_CPTW(VOID_TO_PCIDEV(dev_id), ((GET_EVENT_CPTW(VOID_TO_PCIDEV(dev_id)) + 1 ) % APCI1500_MAX_EVENT_COUNTER) );
				}
			else
				{
				/* FIFO is full */
				APCI1500_PRIVDATA(VOID_TO_PCIDEV(dev_id))->dw_InterruptSource[GET_EVENT_CPTW(VOID_TO_PCIDEV(dev_id))] = 0x7fffffff;
				}
		}

		/* call registred interrupt callback */
		if (apci1500_private_InterruptCallback)
		{
			// (apci1500_private_InterruptCallback) (VOID_TO_PCIDEV(dev_id), b_InterruptMask);
			(apci1500_private_InterruptCallback) (VOID_TO_PCIDEV(dev_id), 0);
		}

	}
	APCI1500_UNLOCK(VOID_TO_PCIDEV(dev_id), irqstate);

	{
		/* set asychronous signal notification */
		if (APCI1500_PRIVDATA(VOID_TO_PCIDEV(dev_id))->async_queue)
		{
			kill_fasync( &(APCI1500_PRIVDATA(VOID_TO_PCIDEV(dev_id))->async_queue), SIGIO, POLL_IN);
		}

		/* wake up processes waiting for events */
		wake_up_interruptible (&APCI1500_PRIVDATA(VOID_TO_PCIDEV(dev_id))->wq);
	}

	RETURN_HANDLED;
}

//------------------------------------------------------------------------------
int apci1500_register_interrupt(struct pci_dev * pdev)
{
	uint32_t tmp = 0;

	/* Enable the interrupt on the PCI-Express controller */
	if (pdev->device == APCIE1500_BOARD_DEVICE_ID)
	{
		tmp = inl(GET_BAR4(pdev) + 0x68); // old GET_BAR1
		outl((tmp | (1<<11) | (1 << 8)), GET_BAR4(pdev) + 0x68); //old GET_BAR1
	}


#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)
	return request_irq( pdev->irq, apci1500_do_interrupt, SA_SHIRQ, __DRIVER_NAME, pdev);
#else
	return request_irq( pdev->irq, apci1500_do_interrupt, IRQF_SHARED, __DRIVER_NAME, pdev);
#endif


}
//------------------------------------------------------------------------------
