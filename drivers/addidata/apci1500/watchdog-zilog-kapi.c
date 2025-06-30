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

#include "apci1500-private.h"

EXPORT_SYMBOL(i_APCI1500_InitWatchdogCounter3);
EXPORT_SYMBOL(i_APCI1500_TriggerWatchdog);
EXPORT_SYMBOL(i_APCI1500_TriggerCounter3);
EXPORT_SYMBOL(i_APCI1500_StopCounter3);
EXPORT_SYMBOL(i_APCI1500_EnableDisableWatchdogCounter3Interrupt);
EXPORT_SYMBOL(i_APCI1500_StartCounter3);
EXPORT_SYMBOL(i_APCI1500_ReadCounter3);

EXPORT_NO_SYMBOLS;

#define WATCHDOG_CTRL_RGSTR(__base)  (__base + 6)
#define WATCHDOG_RELOAD_VALUE_RGSTR(__base) ( __base + 8)
#define WATCHDOG_IRQSTAT_RGSTR(__base) ( __base + 10)

/** Initialise and start the watchdog.
 * 
 * @param[in,out] BoardInformations Internal information of the card.
 * @param[in] arg Configuration parameters.
 * 
 * arg encodes two information:
 * - HISHORT(arg) contains the mode of the watchdog 
 * - LOSHORT(arg) is the reload value.
 * 
 * This file manage the standard board that uses the Zilog watchdog.
 * 
 * 
 *  */


//------------------------------------------------------------------------------

/** Init watchdog / counter 3.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Initialisation parameters.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_InitWatchdogCounter3(struct pci_dev * pdev , unsigned long arg)
{	
	volatile uint8_t b_MasterConfiguration = 0;
	
	/* Test if b_CounterOrWatchdogSelect == APCI1500_COUNTER */

	if ( GET_TIMERMODE(arg) & APCI1500_COUNTER ) 
	{
		/* counter mode */
		APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_WatchdogCounter3Select = APCI1500_COUNTER;
	}
	else 
	{
		/* watchdog mode */
		APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_WatchdogCounter3Select = APCI1500_WATCHDOG;
	}
	
	/* Selects the mode register of watchdog/counter 3 */

	outb_mb(APCI1500_RW_CPT_TMR3_MODE_SPECIFICATION,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Writes the new mode */
	{
		uint16_t mode = GET_TIMERMODE(arg);
		if ( IS_COUNTER3_WATCHDOG(pdev) )
		{
			/* watchdog mode */
			
			/* clear bits 0 and 1 ( Output duty cycle select )
			 * counter should work in "Pulse output mode" 
			 */
			mode &= ~0x3;
			/* set retrigger enable bit + external trigger enable + external output enable  */
			mode |= 0x54;
		}
		else
		{
			/* counter mode */
			
			/* force bits 0 and 1 + 3 (retrigger enable bit) */
			mode |= APCI1500_RETRIGGER_ENABLE;
			mode |= APCI1500_TIMERCOUNTER_ODC;
		}
		outb_mb(mode,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	}


	/* Selects the constant register of watchdog/counter 3 */

	outb_mb(APCI1500_RW_CPT_TMR3_TIME_CST_LOW,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Writes the low value of time constant */

	outb_mb((uint8_t) GET_RELOADVALUE(arg),GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Selects the constant register of watchdog/counter 3 */

	outb_mb(APCI1500_RW_CPT_TMR3_TIME_CST_HIGH,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Writes the high value */

	outb_mb((uint8_t) (GET_RELOADVALUE(arg) >> 8),GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);



	/* Selects the master configuration register */

	outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Reads the register */

	b_MasterConfiguration = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Enables watchdog/counter 3 and triggers watchdog/counter 3 */

	b_MasterConfiguration = (uint8_t) (b_MasterConfiguration | 0x10);


	/* Selects the master configuration register */

	outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Writes the new configuration */

	outb_mb(b_MasterConfiguration,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Test if watchdog */


	if (IS_COUNTER3_WATCHDOG(pdev)) 
	{
		APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_Counter3Enabled = APCI1500_ENABLE;


		/* Test if interrupt enabled */

		if ( apci1500_interrupt_is_enabled(pdev) &&
		    (APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_WatchdogCounter3UseInterrupt == APCI1500_ENABLE))
		{


			/* Selects the commands register of */
			/* watchdog/counter 3               */

			outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


			/* Enables the interrupt for the    */
			/* watchdog/counter 3 and starts it */

			// SW                           
			outb_mb(0xC6,//	outb_mb(0x6,
				GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		} 
		else	// SN ! APCI1500_ENABLE
		{
			
			/* Selects the commands register of */
			/* watchdog/counter 3               */

			outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


			/* Enables the  watchdog/counter 3 and starts it */

			outb_mb(0x6,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		}	// APCI1500_ENABLE
	}
	else 
	{
		/* Selects the command register of   */
		/* watchdog/counter 3                */

		outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Disable the watchdog/counter 3 and starts it */

		outb_mb(0x0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


		/* Selects the command register of   */
		/* watchdog/counter 3                */

		outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


		/* Trigger the  watchdog/counter 3 and starts it */

		outb_mb(0x2,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);        
	}

	/* Sets the flags for the WatchdogCounter3 */

	APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.
	b_WatchdogCounter3Init = APCI1500_ENABLE;
	return 0;
}

//------------------------------------------------------------------------------

/** Trigger watchdog.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		  0: No error.
 * @retval 	-EINVAL: Watchdog not initialized.                                                                   
 */
int i_APCI1500_TriggerWatchdog(struct pci_dev * pdev)
{

	if ( ! IS_COUNTER3_WATCHDOG(pdev) )
	{
		return -EINVAL;
	}
	 		
	/* Selects the command and status register */
	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Writes the new command */
	outb_mb(0x6, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	return 0;
}
//------------------------------------------------------------------------------

/** Trigger counter 3.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		  0: No error.                                                                  
 */
int i_APCI1500_TriggerCounter3(struct pci_dev * pdev)
{

	uint8_t b_CommandAndStatusValue = 0;
	
	if (APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_Counter3Enabled == APCI1500_ENABLE) 
	{
		b_CommandAndStatusValue = (uint8_t) 0x6;
	}

	else 
	{
		b_CommandAndStatusValue = (uint8_t) 0x2;
	}

	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	outb_mb(b_CommandAndStatusValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	return 0;	
}
//------------------------------------------------------------------------------

/** Stop counter 3.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		  0: No error.                                                                  
 */
int i_APCI1500_StopCounter3(struct pci_dev * pdev)
{


	uint8_t b_CommandAndStatusValue = 0;
	volatile uint8_t b_RegValue = 0;	
	b_CommandAndStatusValue = (uint8_t) 0x00;
		
	/* Selects the command and status register */

	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Stop  the timer */

	outb_mb(b_CommandAndStatusValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the command and status register of timer 3 */

	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Reads the register */

	b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	if ((b_RegValue & 0x60) == 0x60) 
	{


		/* Selects the command and status register of timer 3 */

		outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


		/* Deletes the interrupt of timer 3 */

		outb_mb(0x20,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	}


	/* Selects the command and status register */

	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Disable the interrupt */

	outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_Counter3Enabled = APCI1500_DISABLE;
		

	return 0;	
}

//------------------------------------------------------------------------------

/** Enable / Disable watchdog / counter 3.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : APCI1500_ENABLE or APCI1500_DISABLE.
 *
 * @retval 		 0: No error.     
 * @retval -EINVAL: Interrupt already enable or argument is wrong.                                                            
 */
int i_APCI1500_EnableDisableWatchdogCounter3Interrupt(struct pci_dev * pdev, unsigned long arg)
{
	/* Test if the interrupt is set */
	if ( ! apci1500_interrupt_is_enabled(pdev) )
		return -EINVAL;
	
	/* Test the argument */
	if ((arg != APCI1500_ENABLE) && (arg != APCI1500_DISABLE))
		return -EINVAL;
		
	if (arg == APCI1500_ENABLE)
		APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_WatchdogCounter3UseInterrupt = APCI1500_ENABLE;
	else
		APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_WatchdogCounter3UseInterrupt = APCI1500_DISABLE;	 

	return 0;
}

//------------------------------------------------------------------------------

/** Start counter 3.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		  0: No error.                                                                  
 */
int i_APCI1500_StartCounter3(struct pci_dev * pdev)
{
	uint8_t b_CommandAndStatusValue = 0;
	
	if (APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_WatchdogCounter3Init != APCI1500_ENABLE) 
	{
		return -EINVAL;
	}

	DELAY();
		

	
	if ( apci1500_interrupt_is_enabled(pdev) &&
	    (APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_WatchdogCounter3UseInterrupt == APCI1500_ENABLE))
	{
		b_CommandAndStatusValue = (uint8_t) 0xC4;
	}
	else 
	{
		b_CommandAndStatusValue = (uint8_t) 0xE4;
	}		
	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	outb_mb(b_CommandAndStatusValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_Counter3Enabled = APCI1500_ENABLE;
		
	return 0;
}

//------------------------------------------------------------------------------
/**  interrupt manager for watchdog  
* locked by caller 
*/
void do_watchdog_interrupt(struct pci_dev * pdev, uint8_t * b_InterruptMask)
{

	volatile uint8_t b_RegValue;	
	
	/* Tests if an interrupt occured from timer 3 */
	/* Selects the timer 3 command register       */
	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Reads the command register of timer 3 */
	b_RegValue = inb_mb( GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* If the RegValue == 0x60, an interrupt occurs */
	if ((b_RegValue & 0x60) == 0x60) 
	{

		if ( IS_COUNTER3_WATCHDOG(pdev) )
		{
			/* Watchdog */
			*b_InterruptMask =  *b_InterruptMask | 0x20;
		}
		else 
		{
			/* Counter/Timer 3 */
			*b_InterruptMask =  *b_InterruptMask | 0x10;			
		} 

		/* Selects the timer 3 command register       */
		outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Prepares the variable to reset the interrupt */
		b_RegValue = ((b_RegValue & 0x0F) | 0x20);

		/* Writes the new RegValue to the board */
		outb_mb(b_RegValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	}
}

//-------------------------------------------------------------------

/** Read timer counter 3.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Counter value.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_ReadCounter3(struct pci_dev* pdev, unsigned long *arg)
{
	uint8_t b_HighValue = 0;
	uint8_t b_CommandAndStatusValue = 0;	
	volatile unsigned long l_ReadValue = 0;
	
	if (APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_Counter3Enabled == APCI1500_ENABLE) 	    
	{
		b_CommandAndStatusValue = (uint8_t) 0xC;
	}
	else 
	{
		b_CommandAndStatusValue = (uint8_t) 0x8;
	}
	
	outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
	outb_mb(b_CommandAndStatusValue, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
	outb_mb(APCI1500_R_CPT_TMR3_VALUE_HIGH, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	b_HighValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	outb_mb(APCI1500_R_CPT_TMR3_VALUE_LOW,GET_BAR1(pdev) +APCI1500_Z8536_CONTROL_REGISTER);
	
	l_ReadValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	l_ReadValue = (l_ReadValue & 0xFF) + (uint32_t) ((uint32_t) (b_HighValue) << 8);
	
	*arg = l_ReadValue;
		
	return 0;
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------


