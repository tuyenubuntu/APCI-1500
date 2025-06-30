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

EXPORT_SYMBOL(i_APCI1500_InitTimerCounter1);
EXPORT_SYMBOL(i_APCI1500_ReadTimerCounter1);
EXPORT_SYMBOL(i_APCI1500_EnableDisableTimerCounter1Interrupt);
EXPORT_SYMBOL(i_APCI1500_StartTimerCounter1);
EXPORT_SYMBOL(i_APCI1500_TriggerTimerCounter1);
EXPORT_SYMBOL(i_APCI1500_StopTimerCounter1);

EXPORT_NO_SYMBOLS;

//------------------------------------------------------------------------------

/** Init timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Initialisation parameters.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_InitTimerCounter1(struct pci_dev * pdev, unsigned long arg)
{

	volatile uint8_t b_MasterConfiguration = 0;
		
	DELAY();
  
	/* Selects the mode register of timer/counter 1 */

	outb_mb(APCI1500_RW_CPT_TMR1_MODE_SPECIFICATION, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Writes the new mode (the last two bits must always be set (ref. Zilog docu. 2.9.1)) */

	outb_mb( ( LOBYTE(GET_TIMERMODE(arg) | APCI1500_RETRIGGER_ENABLE | APCI1500_TIMERCOUNTER_ODC) ), GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the constant register of timer/counter 1 */

	outb_mb(APCI1500_RW_CPT_TMR1_TIME_CST_LOW, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Writes the low value  */

	outb_mb( LOBYTE(GET_RELOADVALUE(arg)), GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the constant register of timer/counter 1 */

	outb_mb(APCI1500_RW_CPT_TMR1_TIME_CST_HIGH, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Writes the high value  */

	outb_mb( HIBYTE(GET_RELOADVALUE(arg)),GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the master configuration register */

	outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Reads the register */

	b_MasterConfiguration =	inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Enables timer/counter 1 and triggers timer/counter 1 */

	b_MasterConfiguration =	(uint8_t) (b_MasterConfiguration | 0x40);


	/* Selects the master configuration register */

	outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Writes the new configuration */

	outb_mb(b_MasterConfiguration,GET_BAR1(pdev) + 	APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the commands register of     */
	/* timer/counter 1                      */

	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Disable timer/counter 1 */

	outb_mb(0x0, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the commands register of     */
	/* timer/counter 1                      */

	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Trigger timer/counter 1 */

	outb_mb(0x2,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Stores the selection (timer or counter) */

	APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_TimerCounter1Init = APCI1500_ENABLE;
	
	if ((((uint8_t) HISHORT(arg) & APCI1500_COUNTER) >> 6) == APCI1500_ENABLE) 
	{
		APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_TimerCounter1Select = APCI1500_COUNTER;
	}

	else 
	{
		APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_TimerCounter1Select = APCI1500_TIMER;
	}
	
	// CHECK THAT
	APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_TimerCounter1Enabled = APCI1500_DISABLE;

	return 0;
}

//------------------------------------------------------------------------------

/** Read timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Timer / counter value.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_ReadTimerCounter1(struct pci_dev * pdev, unsigned long *arg)
{

	uint8_t b_CommandAndStatusValue = 0;	
	
	volatile uint32_t l_ReadValue = 0;	

		uint8_t b_HighValue = 0;

		if (APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.
		b_TimerCounter1Enabled == APCI1500_ENABLE) 
		{
			b_CommandAndStatusValue = (uint8_t) 0xC;
		}
		else 
		{
			b_CommandAndStatusValue = (uint8_t) 0x8;
		}		
				
		outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		outb_mb(b_CommandAndStatusValue,GET_BAR1(pdev)+	APCI1500_Z8536_CONTROL_REGISTER);
		outb_mb(APCI1500_R_CPT_TMR1_VALUE_HIGH,GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER);
		
		b_HighValue = inb_mb( GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);	
		outb_mb(APCI1500_R_CPT_TMR1_VALUE_LOW,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		l_ReadValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		l_ReadValue = (l_ReadValue & 0xFF) + (uint32_t) ((uint32_t) (b_HighValue) << 8);

	*arg = l_ReadValue;
	
	return 0;
}

//------------------------------------------------------------------------------

/** Enable / Disable timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : APCI1500_ENABLE or APCI1500_DISABLE.
 *
 * @retval 		 0: No error.     
 * @retval -EINVAL: Interrupt already enable or argument is wrong.                                                            
 */
int i_APCI1500_EnableDisableTimerCounter1Interrupt(struct pci_dev * pdev, unsigned long arg)
{
	/* Test if the interrupt is set */
	if ( ! apci1500_interrupt_is_enabled(pdev) )
		return -EINVAL;
	
	/* Test the argument */
	if ((arg != APCI1500_ENABLE) && (arg != APCI1500_DISABLE))
		return -EINVAL;
		
	if (arg == APCI1500_ENABLE)
		APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_TimerCounter1UseInterrupt = APCI1500_ENABLE;
	else
		APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_TimerCounter1UseInterrupt = APCI1500_DISABLE;	
		
	return 0;
}

//------------------------------------------------------------------------------

/** Start timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.     
 * @retval -EINVAL: TimerCounter1 not initialised.                                                            
 */
int i_APCI1500_StartTimerCounter1(struct pci_dev * pdev)
{
	uint8_t b_CommandAndStatusValue = 0;
	
	DELAY();

	/* TimerCounter1 not initialised ? */
	if (APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_TimerCounter1Init != APCI1500_ENABLE) 
	{
		return -EINVAL;
	}

	if ( apci1500_interrupt_is_enabled(pdev) &&
	    (APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_TimerCounter1UseInterrupt == APCI1500_ENABLE)) 
	{	
		// interrupt activated	
		b_CommandAndStatusValue = (uint8_t) 0xC4;
	}
	else
	{
		b_CommandAndStatusValue = (uint8_t) 0xE4;
	}	
	/* Selects the command and status register */
	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Writes the new command */
	outb_mb(b_CommandAndStatusValue,GET_BAR1(pdev)+	APCI1500_Z8536_CONTROL_REGISTER);

	/* Sets the "TimerCounter1Enabled" flag */  	
	APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_TimerCounter1Enabled = APCI1500_ENABLE;

	return 0;
}

//------------------------------------------------------------------------------

/** Trigger timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                            
 */
int i_APCI1500_TriggerTimerCounter1(struct pci_dev * pdev)
{
	uint8_t b_CommandAndStatusValue = 0;	
	
	if (APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_TimerCounter1Enabled == APCI1500_ENABLE) 
	{
		b_CommandAndStatusValue = (uint8_t) 0x6;
	}
	else 
	{
		b_CommandAndStatusValue = (uint8_t) 0x2;
	}
	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	outb_mb(b_CommandAndStatusValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	return 0;	
}
//------------------------------------------------------------------------------

/** Stop timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                            
 */
int i_APCI1500_StopTimerCounter1(struct pci_dev * pdev)
{

	volatile uint8_t b_RegValue = 0;	
	uint8_t b_CommandAndStatusValue = 0;	
		
	b_CommandAndStatusValue = (uint8_t) 0x00;

  
	/* Selects the command and status register */

	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Stop  the timer */

	outb_mb(b_CommandAndStatusValue,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Selects the command and status register of timer 1 */

	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Reads the register */

	b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	if ((b_RegValue & 0x60) == 0x60) 
	{
		/* Selects the command and status register of timer 1 */	
		outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Deletes the interrupt of timer 1 */	
		outb_mb(0x20,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	}


	/* Selects the command and status register of timer 1 */

	outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Disable the interrupt */

	outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
	APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_TimerCounter1Enabled = APCI1500_DISABLE;		

	return 0;
}			
