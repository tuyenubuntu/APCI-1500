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

EXPORT_SYMBOL(i_APCI1500_SetInputEventMask);
EXPORT_SYMBOL(i_APCI1500_StartInputEvent);
EXPORT_SYMBOL(i_APCI1500_StopInputEvent);


EXPORT_NO_SYMBOLS;

/* These fonctions extract configuration values encoded in the 32 bit argument */
static __inline__ uint8_t GET_PATTERN_POLARITY(uint32_t arg)
{
	return HIBYTE(HIWORD(arg));
	
}

static __inline__ uint8_t GET_PATTERN_TRANSITION(uint32_t arg)
{
	return LOBYTE(HIWORD(arg));
}

static __inline__ uint8_t GET_PATTERN_MASK(uint32_t arg)
{
	return HIBYTE(LOWORD(arg));
}

/* logic conf is used in Port Mode configuration register, bit D1 and D2
* 0 0 disable pattern match
* 0 1 "and mode" 
* 1 0 "or mode" 
* 1 1 "or priority"
*/
static __inline__ uint8_t GET_LOGIC(uint32_t arg)
{
	return (LOBYTE(LOWORD(arg)) & 0x6);
}

/* returns 1 or 2 */
static __inline__ uint8_t GET_PORT_NUMBER(uint32_t arg)
{
	return ( ( ( (LOBYTE(LOWORD(arg))) >> 7) & 0x1) + 1);
}
//-------------------------------------------------------------------
/* these functions set or unset bits related to port in the Master Configuration Control Register 
* Bit D2 controls enable/disable of port A
* Bit D7 controls enable/disable of port A
* when writing a bit, all other configuration bits are assumed to be set (including counter/timer1, counter/timer2, portC and countertimer3 )
* bits D0, D1 and D3 are assumed to be always set to 0
* (the normal value of APCI1500_RW_MASTER_CONFIGURATION_CONTROL is 0xF4 at run time)
*/
static void apci1500_disable_port_A(struct pci_dev * pdev)
{
	/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL register*/		  
	outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	/* Disable Port A */

	outb_mb(0xF0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);	
}

static void apci1500_enable_port_A(struct pci_dev * pdev)
{
	/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL */
	/* register                                             */

	outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Enable Port A */

	outb_mb(0xF4,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
}

static void apci1500_disable_port_B(struct pci_dev * pdev)
{
	/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL */
	/* register                                             */

	outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Disable Port B */

	outb_mb(0x74,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
}

static void apci1500_enable_port_B(struct pci_dev * pdev)
{
	/* Selects the APCI1500_RW_MASTER_CONFIGURATION_CONTROL */
	/* register                                             */

	outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);


	/* Enable Port B */

	outb_mb(0xF4,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
}

//-------------------------------------------------------------------

int i_APCI1500_SetInputEventMask_PortNumber1(struct pci_dev* pdev, unsigned long arg)
{
	apci1500_disable_port_A(pdev);
	{
		/* set polarity */
		{
			/* Selects the polarity register of port 1    */
		
			outb_mb(APCI1500_RW_PORT_A_PATTERN_POLARITY, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
			/* Writes the new value in the polarity   */
			/* register of port 1                     */

			outb_mb(GET_PATTERN_POLARITY(arg),GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		}
		/* set pattern mask */
		{
			/* Selects the pattern mask register of      */
			/* port 1                                    */
		
			outb_mb(APCI1500_RW_PORT_A_PATTERN_MASK,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
			/* Writes the new value in the pattern mask   */
			/* register of port 1                         */
		
			outb_mb(GET_PATTERN_MASK(arg), GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		}
		/* set transition */
		{
			/* Selects the pattern transition register  */
			/* of port 1                                */
		
			outb_mb(APCI1500_RW_PORT_A_PATTERN_TRANSITION, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Writes the new value in the pattern   */
			/* transition register of port 1         */

			outb_mb(GET_PATTERN_TRANSITION(arg), GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		}
		/* set logic configuration */
		{
			volatile uint8_t b_RegValue = 0;
			/* Selects the mode specification mask    */
			/* register of port 1                     */
		
			outb_mb(APCI1500_RW_PORT_A_SPECIFICATION, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Reads the value */
		
			b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Selects the mode specification mask    */
			/* register of port 1                     */
		
			outb_mb(APCI1500_RW_PORT_A_SPECIFICATION,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Port A new logic mode    */		
			outb_mb((uint8_t) ((b_RegValue & 0xF9) | GET_LOGIC(arg) ), GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		}
		
		
		APCI1500_PRIVDATA(pdev)->s_EventInformations.b_SetEventMaskPort1 = APCI1500_ENABLE;
		APCI1500_PRIVDATA(pdev)->s_EventInformations.b_Port1Logik = GET_LOGIC(arg);
	}	
	apci1500_enable_port_A(pdev);
	
	return 0;
}

//-------------------------------------------------------------------

int i_APCI1500_SetInputEventMask_PortNumber2(struct pci_dev* pdev, unsigned long arg)
{
	/* logic must always be APCI1500_OR for Port 2 */	
	if (GET_LOGIC(arg) != APCI1500_OR)
		return -EINVAL;

	apci1500_disable_port_B(pdev);
	{

		/*write a default mode specification value for port B */
		{
			volatile uint8_t b_RegValue = 0;
			
			/* Selects the mode specification mask  */
			/* register of port B                   */
		
			outb_mb(APCI1500_RW_PORT_B_SPECIFICATION,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Reads the value */
		
			b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Selects the mode specification mask    */
			/* register of port B                     */
		
			outb_mb(APCI1500_RW_PORT_B_SPECIFICATION, GET_BAR1(pdev)+ APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Port B new mode    */
		
			outb_mb((uint8_t) (b_RegValue & 0xF9), GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
		}
					
		/* Selects error channels 1 and 2 */		
		/* b_PatternMask = (uint8_t) (b_PatternMask | 0xC0);
		b_PatternPolarity = (uint8_t) (b_PatternPolarity | 0xC0);
		b_PatternTransition = (uint8_t) (b_PatternTransition | 0xC0); */
	
		/* set polarity */
		{
			/* Selects the polarity register of port 2    */
		
			outb_mb(APCI1500_RW_PORT_B_PATTERN_POLARITY, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Writes the new value in the polarity    */
			/* register of port 2                      */
		
			outb_mb( 
				(GET_PATTERN_POLARITY(arg) | 0xC0),
				GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER
				);
				
		}
	
		/* set transition */
		{
			/* Selects the pattern transition register    */
			/* of port 2                                  */
		
			outb_mb(APCI1500_RW_PORT_B_PATTERN_TRANSITION, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Write the new value in the pattern     */
			/* transition register of port 2          */
		
			outb_mb(
				( GET_PATTERN_TRANSITION(arg) | 0xC0 ), 
				GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER
				);
				
		}
	
		/* set pattern mask */
		{
			/* Selects the pattern transition register    */
			/* of port 2                                  */
		
			outb_mb(APCI1500_RW_PORT_B_PATTERN_MASK,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Writes the new value in the pattern mask  */
			/* register of port 2                        */
		
			outb_mb(
				( GET_PATTERN_MASK(arg) | 0xC0), 
				GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER
				);
				
		}
		/* set logic configuration */
		{
			volatile uint8_t b_RegValue = 0;
			
			/* Selects the mode specification mask    */
			/* register of port 2                     */
		
			outb_mb(APCI1500_RW_PORT_B_SPECIFICATION, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Reads the value */
		
			b_RegValue = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Selects the mode specification mask    */
			/* register of port 2                     */
		
			outb_mb(APCI1500_RW_PORT_B_SPECIFICATION,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		
		
			/* Port B new mode    */
			/* logic is always APCI1500_OR (0x4)  */
			outb_mb((uint8_t) ( (b_RegValue & 0xF9) | APCI1500_OR), GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
		}
		
	}	
	apci1500_enable_port_B(pdev);

	APCI1500_PRIVDATA(pdev)->s_EventInformations.b_SetEventMaskPort2 = APCI1500_ENABLE;
	APCI1500_PRIVDATA(pdev)->s_EventInformations.b_Port2Logik = APCI1500_OR;
	
	return 0;
}

//-------------------------------------------------------------------

/** Set input event mask.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Please use   MAKE_APCI1500_INPUT_EVENT_ARG_PORT1 or <br>
 * 													MAKE_APCI1500_INPUT_EVENT_ARG_PORT2
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: arg is false.                     
 */
int i_APCI1500_SetInputEventMask(struct pci_dev* pdev, unsigned long arg)
{
	DELAY();

	/*an argument of 0 is obviously false */
	if (!arg)
		return -EINVAL;
	
	/* test logic configuration (can not be 0) */
	switch (GET_LOGIC(arg))
	{
		case APCI1500_AND:
		case APCI1500_OR:
		case APCI1500_OR_PRIORITY:
		/* OK */
		break;
		
		default:
			return -EINVAL;
	}
	
	switch(GET_PORT_NUMBER(arg))
	{
	case 1:			

		return i_APCI1500_SetInputEventMask_PortNumber1(pdev, arg);  
		break;
	case 2:
  		return i_APCI1500_SetInputEventMask_PortNumber2(pdev, arg);
		break;
	default:
		return -EINVAL;
		break;
	}
	return 0;	
}


//------------------------------------------------------------------------------
/* access to the card is locked by the callee function */
/* Note: bit D2 of the Master Configuration Control Register should have been be set by initialisation function */
static void apci1500_start_input_port_1(struct pci_dev * pdev)
{
	apci1500_enable_port_A(pdev);
	{
		/* Selects the command and status register of port1 */
	
		outb_mb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	
		/* Enable port interrupt logic  */
	
		outb_mb(0xC0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);	
	}
	apci1500_enable_port_A(pdev);
}

//------------------------------------------------------------------------------
/* access to the card is locked by the callee function.
 * Note: bit D7 of the Master Configuration Control Register should have been be set by initialisation function
 */
static void apci1500_start_input_port_2(struct pci_dev * pdev)
{	
	apci1500_disable_port_B(pdev);	
	{
		/* Selects the command and status register of port1 */
	
		outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

	
		/* Enable port interrupt logic  */
	
		outb_mb(0xC0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);	
	}
	apci1500_enable_port_B(pdev);
}

//------------------------------------------------------------------------------

/** Start input event mask.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : e.g.: APCI1500_INPUT_PORT_1 | APCI1500_INPUT_PORT_2.
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: arg is false.        
 * 
 * LOCK() this function             
 */
int i_APCI1500_StartInputEvent(struct pci_dev* pdev, unsigned long arg)
{
	 

	/* check arg */
	switch (arg)
	{
		case APCI1500_INPUT_PORT_1:
		case APCI1500_INPUT_PORT_2:
		case ( APCI1500_INPUT_PORT_1 | APCI1500_INPUT_PORT_2):
			// OK
			break;
		default:
			return -EINVAL;
			break;
	}
	

	if ( arg & APCI1500_INPUT_PORT_1 )
	{
		apci1500_start_input_port_1(pdev);
	}
	if ( arg & APCI1500_INPUT_PORT_2 )
	{
		apci1500_start_input_port_2(pdev);
	}

	return 0;	
}

//------------------------------------------------------------------------------
/* access to the card is locked by the callee function */
/* Note: bit D2 of the Master Configuration Control Register should have been be set by initialisation function */
static void apci1500_stop_input_port_1(struct pci_dev * pdev)
{
	apci1500_disable_port_A(pdev);
	{
		/* Selects the command and status register of port1 */
	
		outb_mb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	
		/* Inhibits port interrupt logic */
	
		outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);		
	}
	apci1500_enable_port_A(pdev);
}
//------------------------------------------------------------------------------
/* access to the card is locked by the callee function */
/* Note: bit D2 of the Master Configuration Control Register should have been be set by initialisation function */
static void apci1500_stop_input_port_2(struct pci_dev * pdev)
{
	apci1500_disable_port_B(pdev);
	{
		/* Selects the command and status register of port1 */
	
		outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	
	
		/* Inhibits port interrupt logic */
	
		outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
	}
	apci1500_enable_port_B(pdev);
}
//------------------------------------------------------------------------------

/** Stop input event mask.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : e.g.: APCI1500_INPUT_PORT_1 | APCI1500_INPUT_PORT_2.
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: arg is false.                     
 */
int i_APCI1500_StopInputEvent(struct pci_dev * pdev, unsigned long arg)
{
	/* check arg */
	switch (arg)
	{
		case APCI1500_INPUT_PORT_1:
		case APCI1500_INPUT_PORT_2:
		case ( APCI1500_INPUT_PORT_1 | APCI1500_INPUT_PORT_2):
			// OK
			break;
		default:
			return -EINVAL;
			break;
	}

	if ( arg & APCI1500_INPUT_PORT_1 )
	{
		apci1500_stop_input_port_1(pdev);
	}
	if ( arg & APCI1500_INPUT_PORT_2 )
	{
		apci1500_stop_input_port_2(pdev);
	}		
	
	return 0;	
}

