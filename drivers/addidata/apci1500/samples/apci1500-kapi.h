 /* @file apci1500-kapi.h
  * 
  * @brief Define the kernel API for the apci1500 ADDI-DATA board. 
  * 
  * @author Sylvain Nahas, Julien Krauth
  * 
  */

/** @par LICENCE
 * 
 *  @verbatim
  Copyright (C) 2004,2005,2006,2007,2008 ADDI-DATA GmbH for the source code of this module.
  
         ADDI-DATA GmbH
         Dieselstrasse 3
         D-77833 Ottersweier
         Tel: +19(0)7223/9493-0
         Fax: +49(0)7223/9493-92
         http://www.addi-data-com
         info@addi-data.com
 
 This library is free software; you can redistribute it and/or modify it under 
 the terms of the GNU Lesser General Public License as published by the 
 Free Software Foundation; either version 2.1 of the License, 
 or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful, 
 but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 or FITNESS FOR A PARTICULAR PURPOSE. 
 See the GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License 
 along with this library; if not, write to the Free Software Foundation, 
 Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 
 
 You also shoud find the complete LGPL in the LGPL.txt file accompanying 
 this source code.
 
 @endverbatim
**/

#ifndef __APCI1500_KAPI_H__
#define __APCI1500_KAPI_H__

#ifdef __KERNEL__

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
									uint8_t *  status);

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
									uint8_t * status);

//------------------------------------------------------------------------------

/** Read 16 digital input status.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @param [out] status				 : Digital input status.  
 *
 * @retval 		 0: No error.                                                             
 */
int i_APCI1500_Read16DigitalInput(	struct pci_dev * pdev, uint16_t * status);

//------------------------------------------------------------------------------

/** Read 16 digital output status.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @param [out] status				 : Digital output status.  
 *
 * @retval 		 0: No error.                                                             
 */
int i_APCI1500_Get16DigitalOutput(	struct pci_dev * pdev, uint32_t * status);

//------------------------------------------------------------------------------

/** Set 1 digital output on.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] chan                  : The digital output to set (1 to 16). 
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: The selected digital output is wrong.                     
 */
int i_APCI1500_Set1DigitalOutputOn(	struct pci_dev * pdev, uint8_t chan);

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
int i_APCI1500_Set1DigitalOutputOff(	struct pci_dev * pdev, uint8_t chan);

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
int i_APCI1500_Set8DigitalOutputOn(struct pci_dev * pdev, uint8_t port, uint8_t status);

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
int i_APCI1500_Set8DigitalOutputOff(struct pci_dev * pdev, uint8_t port, uint8_t status);

//------------------------------------------------------------------------------

/** Set 16 digital output on.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] status                : Value to set on the port.  
 *
 * @retval 		 0: No error.                                                                
 */
int i_APCI1500_Set16DigitalOutputOn(struct pci_dev * pdev, uint32_t status);

//------------------------------------------------------------------------------

/** Set 16 digital output off.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] status                : Value to set on the port.  
 *
 * @retval 		 0: No error.    
 * @retval  -EPERM: Output memory is not enabled.                                                               
 */
int i_APCI1500_Set16DigitalOutputOff(struct pci_dev * pdev, uint32_t status);

//------------------------------------------------------------------------------

/** Set digital output memory off.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                                   
 */
int i_APCI1500_SetOutputMemoryOff(struct pci_dev * pdev);

//------------------------------------------------------------------------------

/** Set digital output memory on.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                                   
 */
int i_APCI1500_SetOutputMemoryOn(struct pci_dev * pdev);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/** Set input event mask.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Please use   MAKE_APCI1500_INPUT_EVENT_ARG_PORT1 or <br>
 * 													MAKE_APCI1500_INPUT_EVENT_ARG_PORT2
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: arg is false.                     
 */
int i_APCI1500_SetInputEventMask(struct pci_dev* pdev, unsigned long arg);

//------------------------------------------------------------------------------

/** Start input event mask.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : e.g.: APCI1500_INPUT_PORT_1 | APCI1500_INPUT_PORT_2.
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: arg is false.                     
 */
int i_APCI1500_StartInputEvent(struct pci_dev* pdev, unsigned long arg);

//------------------------------------------------------------------------------

/** Stop input event mask.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : e.g.: APCI1500_INPUT_PORT_1 | APCI1500_INPUT_PORT_2.
 *
 * @retval 		 0: No error.                                            
 * @retval -EINVAL: arg is false.                     
 */
int i_APCI1500_StopInputEvent(struct pci_dev * pdev, unsigned long arg);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/** Init timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Initialisation parameters.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_InitTimerCounter1(struct pci_dev * pdev, unsigned long arg);

//------------------------------------------------------------------------------

/** Read timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Timer / counter value.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_ReadTimerCounter1(struct pci_dev * pdev, unsigned long *arg);

//------------------------------------------------------------------------------

/** Enable / Disable timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : APCI1500_ENABLE or APCI1500_DISABLE.
 *
 * @retval 		 0: No error.     
 * @retval -EINVAL: Interrupt already enable or argument is wrong.                                                            
 */
int i_APCI1500_EnableDisableTimerCounter1Interrupt(struct pci_dev * pdev, unsigned long arg);

//------------------------------------------------------------------------------

/** Start timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.     
 * @retval -EINVAL: TimerCounter1 not initialised.                                                            
 */
int i_APCI1500_StartTimerCounter1(struct pci_dev * pdev);

//------------------------------------------------------------------------------

/** Trigger timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                            
 */
int i_APCI1500_TriggerTimerCounter1(struct pci_dev * pdev);

//------------------------------------------------------------------------------

/** Stop timer counter 1.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                            
 */
int i_APCI1500_StopTimerCounter1(struct pci_dev * pdev);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/** Init timer counter 2.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Initialisation parameters.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_InitTimerCounter2(struct pci_dev * pdev, unsigned long arg);

//------------------------------------------------------------------------------

/** Read timer counter 2.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Timer / counter value.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_ReadTimerCounter2(struct pci_dev * pdev, unsigned long *arg);

//------------------------------------------------------------------------------

/** Enable / Disable timer counter 2.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : APCI1500_ENABLE or APCI1500_DISABLE.
 *
 * @retval 		 0: No error.     
 * @retval -EINVAL: Interrupt already enable or argument is wrong.                                                            
 */
int i_APCI1500_EnableDisableTimerCounter2Interrupt(struct pci_dev * pdev, unsigned long arg);

//------------------------------------------------------------------------------

/** Start timer counter 2.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.     
 * @retval -EINVAL: TimerCounter2 not initialised.                                                            
 */
int i_APCI1500_StartTimerCounter2(struct pci_dev * pdev);

//------------------------------------------------------------------------------

/** Trigger timer counter 2.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                            
 */
int i_APCI1500_TriggerTimerCounter2(struct pci_dev * pdev);

//------------------------------------------------------------------------------

/** Stop timer counter 2.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                            
 */
int i_APCI1500_StopTimerCounter2(struct pci_dev * pdev);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/** Initialize board interrupt
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		 0: No error.                                                            
 * @retval 		 -EBUSY: interrupt routine already used 
 */
int i_APCI1500_SetBoardIntRoutine(struct pci_dev * pdev, void(*InterruptCallback)(struct pci_dev * pdev , char dummy));

//------------------------------------------------------------------------------

/* deactivate interrupt from card */
int i_APCI1500_ResetBoardIntRoutine(struct pci_dev * pdev);

//------------------------------------------------------------------------------

/** Get the interrupt values.
 * 
 * Get the interrupt source. If interrupt source is digital input event,
 * return the status of digital input read in the interrupt function.
 *  
 * @param [in] 	pdev                  : The device to use.
 * @param [out] arg                   : Interrupt informations <br>
 *										arg[0] is the mask of the interrupt source:<br> 										
 *											1: Event on port 1 <br>
 *											2: Event on port 2 <br>
 *											4: Timer 1 <br>								 
 *											8: Timer 2 <br>
 *											0x7fffffff: Driver fifo full <br>
 *											0x7ffffffe: Driver fifo empty
 * 										arg[1] is the gigital inputs status read in the interrupt function.
 * 
 * @retval 		 0: No error. 
 */
int i_APCI1500_TestInterrupt(struct pci_dev * pdev, unsigned long *arg);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/** Set the clock to use for timer / counter.
 * 
 * @param [in]	arg		: 	APCI1500_115_KHZ <br> 
 * 							APCI1500_3_6_KHZ <br> 
 * 							APCI1500_1_8_KHZ
 * 
 * @retval -EINVAL		: Wrong arg.
 */
int i_APCI1500_InitTimerInputClock(struct pci_dev * pdev, unsigned long arg);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/** Init watchdog / counter 3.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Initialisation parameters.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_InitWatchdogCounter3(struct pci_dev * pdev , unsigned long arg);

//------------------------------------------------------------------------------

/** Trigger watchdog.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		  0: No error.
 * @retval 	-EINVAL: Watchdog not initialized.                                                                   
 */
int i_APCI1500_TriggerWatchdog(struct pci_dev * pdev);

//------------------------------------------------------------------------------

/** Trigger counter 3.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		  0: No error.                                                                  
 */
int i_APCI1500_TriggerCounter3(struct pci_dev * pdev);

//------------------------------------------------------------------------------

/** Stop counter 3.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		  0: No error.                                                                  
 */
int i_APCI1500_StopCounter3(struct pci_dev * pdev);

//------------------------------------------------------------------------------

/** Enable / Disable watchdog / counter 3.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : APCI1500_ENABLE or APCI1500_DISABLE.
 *
 * @retval 		 0: No error.     
 * @retval -EINVAL: Interrupt already enable or argument is wrong.                                                            
 */
int i_APCI1500_EnableDisableWatchdogCounter3Interrupt(struct pci_dev * pdev, unsigned long arg);

//------------------------------------------------------------------------------

/** Start counter 3.
 *
 * @param [in] pdev                  : The device to use.
 *
 * @retval 		  0: No error.                                                                  
 */
int i_APCI1500_StartCounter3(struct pci_dev * pdev);

//-------------------------------------------------------------------

/** Read timer counter 3.
 *
 * @param [in] pdev                  : The device to use.
 * @param [in] arg				     : Counter value.
 *
 * @retval 		 0: No error.                                                                 
 */
int i_APCI1500_ReadCounter3(struct pci_dev* pdev, unsigned long *arg);

//----------------------------------------------------------------------------
/** return a pointer to the lock protecting the board */
extern spinlock_t * apci1500_get_lock(struct pci_dev *pdev);
//----------------------------------------------------------------------------
/** lock the board using spin_lock_irqsave(), disabling local software and hardware interrupts
 * @param[in] pdev The device to acquire.
 * @param[out] flags interuption flag used with unlock() 
 *
 * This function is to be used before calling any kAPI function; BUT not in user interrupt handler where the board is already acquired.
 *  
 * @warning lock aren't reentrant, that means that you can not nest call to lock() 
 *  
 */
static inline void apci1500_lock(struct pci_dev *pdev, unsigned long * flags)
{
        spin_lock_irqsave(apci1500_get_lock(pdev), *flags);
}

//----------------------------------------------------------------------------
/** unlock the board using spin_lock_irqrestore()
 * @param[in] pdev The device to acquire.
 * @param[out] flags interuption flag initialised by lock() 
 *
 * This function is to be used before calling any kAPI function; BUT not in user interrupt handler where the board is already acquired.
 * 
 *  
 *  
 */
static inline void apci1500_unlock(struct pci_dev *pdev, unsigned long flags)
{
        spin_unlock_irqrestore(apci1500_get_lock(pdev), flags);
}

//----------------------------------------------------------------------------------------------------------------------
/** find a apci 1500 device of a given index in the system PCI device list.
 * @param index The index (minor number) to lookup
 * @return A pointer to the device or NULL
 *
 * This function is used to map a minor number to an actual device.
 */
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


//struct pci_dev * apci1500_lookup_board_by_index(unsigned int index);
struct pci_dev * apci1500_lookup_board_by_index(unsigned int index);


/* functions exported by module */
int APCI1500_SetIntCallback(void (*) (struct pci_dev * pdev, char b_InterruptMask));

int APCI1500_ResetIntCallback(void);


#endif // __KERNEL__

#endif // __APCI1500_KAPI_H__
