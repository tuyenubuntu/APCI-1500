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

EXPORT_SYMBOL(i_APCI1500_Read1DigitalInput);
EXPORT_SYMBOL(i_APCI1500_Read8DigitalInput);
EXPORT_SYMBOL(i_APCI1500_Read16DigitalInput);

EXPORT_SYMBOL(i_APCI1500_Set1DigitalOutputOn);
EXPORT_SYMBOL(i_APCI1500_Set1DigitalOutputOff);
EXPORT_SYMBOL(i_APCI1500_Set8DigitalOutputOn);
EXPORT_SYMBOL(i_APCI1500_Set8DigitalOutputOff);
EXPORT_SYMBOL(i_APCI1500_Set16DigitalOutputOn);
EXPORT_SYMBOL(i_APCI1500_Set16DigitalOutputOff);

EXPORT_SYMBOL(i_APCI1500_SetOutputMemoryOn);
EXPORT_SYMBOL(i_APCI1500_SetOutputMemoryOff);

EXPORT_NO_SYMBOLS;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/** Read the status from selected digital input (chan).
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] chan				     : Selection from digital input (1 to 16).
 *
 * @param [out] status				 : Digital input channel status <br>
 *                                     0 : Channle is not active <br>
 *                                     1 : Channle is active    
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: The selected digital input is wrong.                     
 */
int i_APCI1500_Read1DigitalInput(	struct pci_dev * pdev, 
									uint8_t   chan,
									uint8_t *  status)
{
	unsigned int ui_TmpValue = 0;

	/* legal values for channels are 1 to 16 included */
	if ( (chan == 0 ) || (chan > 16) )
	{
		return -EINVAL;
	}
	
	/* Reads the input value from the board */
	ui_TmpValue = inw_mb(GET_BAR2(pdev));
	/* Shifts the input value for the decided channel */
	*status = (uint8_t)(ui_TmpValue >> (chan - 1)) & 1;
	
	return 0;	
	
}

//------------------------------------------------------------------------------

/** Read 8 digital input status.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] port				     : Digital input port (1 to 2).
 *
 * @param [out] status				 : Digital input port status.  
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: The selected digital port is wrong.                     
 */
int i_APCI1500_Read8DigitalInput(	struct pci_dev * pdev, 
									uint8_t   port,
									uint8_t * status)
{
	volatile uint32_t ui_TmpValue = 0;

	/* legal values for port are 1 to 2 included */
	if ( (port == 0 ) || (port > 2) )
	{
		return -EINVAL;
	}		

	/* Reads the input value from the board */
	ui_TmpValue = inw_mb(GET_BAR2(pdev));	
			
	/* Shifts the input value for the decided port */
	*status = (uint8_t)(ui_TmpValue >> (8 * (port - 1)));
		
	return 0;

}

//------------------------------------------------------------------------------

/** Read 16 digital input status.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @param [out] status				 : Digital input status.  
 *
 * @retval 		 0: No error.                                                             
 */
int i_APCI1500_Read16DigitalInput(	struct pci_dev * pdev, uint16_t*  status)
{	
	/* Reads the input value from the board */
	*status = inw_mb(GET_BAR2(pdev));
	
	return 0;
}

//------------------------------------------------------------------------------

/** Read 16 digital output status.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @param [out] status				 : Digital output status.  
 *
 * @retval 		 0: No error.                                                             
 */
int i_APCI1500_Get16DigitalOutput(	struct pci_dev * pdev, uint32_t*  status)
{	
	/* Get the state of port 0 */
	// APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister = inw_mb(GET_BAR2(pdev)+ APCI1500_DIGITAL_OUTPUT);      

	*status = APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister;

	return 0;
}


//------------------------------------------------------------------------------

/** Set 1 digital output on.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] chan                  : The digital output to set (1 to 16). 
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: The selected digital output is wrong.                     
 */
int i_APCI1500_Set1DigitalOutputOn(	struct pci_dev * pdev, uint8_t chan)
{
	/* correct values are 1 to 16 included */
	if ( (chan == 0) || (chan>16)  )
	{
		return -EINVAL;
	} 
	if (APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.b_OutputMemoryStatus == APCI1500_ENABLE) 
	 {
		APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister = 
		APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister | (uint32_t) (1 << (chan - 1));
	}	
	else 
	{
		APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister = 1U << (uint8_t) ((uint8_t) chan - 1);
	}
	outw_mb(APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister,
		GET_BAR2(pdev) + APCI1500_DIGITAL_OUTPUT);	
	
	return 0;
}

//------------------------------------------------------------------------------

/** Set 1 digital output off.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] chan                  : The digital output to set (1 to 16). 
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: The selected digital output is wrong
 * @retval  -EPERM: Output memory is not enabled.                     
 */
int i_APCI1500_Set1DigitalOutputOff(	struct pci_dev * pdev, uint8_t chan)
{

	if (APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.b_OutputMemoryStatus != APCI1500_ENABLE) 
	{
		return -EPERM;
	}
	/* correct values are 1 to 16 included */
	if ( (chan ==0) || (chan>16)  )
	{
		return -EINVAL;
	} 	
	APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister =
	APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister & (0xFFFF - (uint32_t) (1 << (chan - 1)));
	outw_mb(APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister,
	GET_BAR2(pdev) + APCI1500_DIGITAL_OUTPUT);

	return 0;
}

//------------------------------------------------------------------------------

/** Set 8 digital output on.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] chan                  : The digital output port to set (1 to 2).
 * @param [in] status                : Value to set on the port.  
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: The selected digital output port is wrong.                     
 */
int i_APCI1500_Set8DigitalOutputOn(struct pci_dev * pdev, uint8_t port, uint8_t status)
{
	/* valid port value is 1 and 2 */
	if ((port == 0) || (port > 2))
	{
		return -EINVAL;
	}
	 
	if (APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.b_OutputMemoryStatus == APCI1500_ENABLE) 
	{
		APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister =
		    APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister | ((status) << (8 * ((port) - 1)));
	}
	else 
	{
		APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister =
		    (uint32_t) ((uint32_t) (status) << (8 * ((port) - 1)));
	}
	
	outw_mb(APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister, GET_BAR2(pdev) + APCI1500_DIGITAL_OUTPUT);	
	
	return 0;
}

//------------------------------------------------------------------------------

/** Set 8 digital output off.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] chan                  : The digital output port to set (1 to 2).
 * @param [in] status                : Value to set on the port.  
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: The selected digital output port is wrong.  
 * @retval  -EPERM: Output memory is not enabled.                    
 */
int i_APCI1500_Set8DigitalOutputOff(struct pci_dev * pdev, uint8_t port, uint8_t status)
{

	if (APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.b_OutputMemoryStatus != APCI1500_ENABLE) 
	{
		return -EPERM;
	}
	/* valid port value is 1 and 2 */
	if (( port == 0) || (port > 2) )
	{
		return -1;
	}	
	APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister =
	APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister 
		& (0xFFFF - ((status) << (8 * ((port) - 1))));
		
	outw_mb(APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister,
			GET_BAR2(pdev) + APCI1500_DIGITAL_OUTPUT);
			
	return 0;
}

//------------------------------------------------------------------------------

/** Set 16 digital output on.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] status                : Value to set on the port.  
 *
 * @retval 		 0: No error.                                                                
 */
int i_APCI1500_Set16DigitalOutputOn(struct pci_dev * pdev, uint32_t status)
{

	if (APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.b_OutputMemoryStatus == APCI1500_ENABLE) 
	{
		APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister =
		APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister | status;
	}
	else 
	{
		APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister = status;
	}
	outw_mb(APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister,GET_BAR2(pdev) + APCI1500_DIGITAL_OUTPUT);
		
	return 0;	
}

//------------------------------------------------------------------------------

/** Set 16 digital output off.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] status                : Value to set on the port.  
 *
 * @retval 		 0: No error.    
 * @retval  -EPERM: Output memory is not enabled.                                                               
 */
int i_APCI1500_Set16DigitalOutputOff(struct pci_dev * pdev, uint32_t status)
{

	if (APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.b_OutputMemoryStatus != APCI1500_ENABLE) 
	{
		return -EPERM;
	}
	
	APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister =
	APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister & (0xFFFF - status);
	
	outw_mb(APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.l_DigitalOutputRegister, GET_BAR2(pdev) + APCI1500_DIGITAL_OUTPUT);

	return 0;
}

//------------------------------------------------------------------------------

/** Set digital output memory off.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                                   
 */
int i_APCI1500_SetOutputMemoryOff(struct pci_dev * pdev)
{
	APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.b_OutputMemoryStatus = APCI1500_DISABLE;
	return 0;
}

//------------------------------------------------------------------------------

/** Set digital output memory on.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                                   
 */
int i_APCI1500_SetOutputMemoryOn(struct pci_dev * pdev)
{
	APCI1500_PRIVDATA(pdev)->s_DigitalOutputInformations.b_OutputMemoryStatus = APCI1500_ENABLE;
	return 0;
}
