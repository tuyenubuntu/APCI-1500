 /* @file apci1500-privadata.h
  * 
  * @brief Holds definition for driver's private data and its manipulation functions. 
  * 
  * 
  * 
  */

/** @par LICENCE
 * 
 *  @verbatim
  Copyright (C) 2004,2005 ADDI-DATA GmbH for the source code of this module.
  
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

#ifndef __APCI1500_PRIVDATA_H_
#define __APCI1500_PRIVDATA_H_


/* internal driver data */
struct apci1500_str_BoardInformations
{
   struct apci1500_str_DigitalOutputInformations   s_DigitalOutputInformations;
   struct apci1500_str_TimerCounterInformations    s_TimerCounterInformations;
   struct apci1500_str_InterruptInformations       s_InterruptInformations;
   struct apci1500_str_EventInformations           s_EventInformations;
   struct fasync_struct * async_queue; /* asynchronous readers */	
   spinlock_t lock; /**< protect the board data */
   struct pci_dev *dev; /**< associate a board field in the card with the OSes PCI device structure. */	
	/* field used to implement linked list */
	struct pci_dev * previous; /**< previous in known-devices linked list */
	struct pci_dev * next; /**< next in known-devices linked list */
   atomic_t atom_EventCounterWrite;
   atomic_t atom_EventCounterRead;
   uint32_t dw_InterruptSource [APCI1500_MAX_EVENT_COUNTER];
   uint32_t dw_ValueArray [APCI1500_MAX_EVENT_COUNTER];
   uint32_t dw_BoardID [APCI1500_MAX_EVENT_COUNTER];	
   int i_MinorNumber;
   wait_queue_head_t wq; 
};


/** initialise board's private data - fill it when adding new members and ioctl handlers */
static __inline__ void apci1500_init_priv_data(struct apci1500_str_BoardInformations * data)
{
	memset(data,0,sizeof(struct apci1500_str_BoardInformations));
	data->async_queue = NULL;	
	
	/* 
	 * By default, interrupts are enable. 
	 * This is because previous versions of the driver
	 * have always activated interrupts. From the point when 
	 * interrupt was initialized.
	 */ 
	data->s_InterruptInformations.b_TimerCounter1UseInterrupt = APCI1500_ENABLE;
	data->s_InterruptInformations.b_TimerCounter2UseInterrupt = APCI1500_ENABLE;
	data->s_InterruptInformations.b_WatchdogCounter3UseInterrupt = APCI1500_ENABLE;	
	
	spin_lock_init(& (data->lock) );	
	init_waitqueue_head (&data->wq);
}

//----------------------------------------------------------------------------------------------------------------------

/** Get the event read counter.
 * 
 * Event counter are managed with 
 * atomic type so they are 
 * protected against concurent access.
 * 
 * @param[in]	dev	Device to use. 	
 */  
#define GET_EVENT_CPTR(dev)		atomic_read(&APCI1500_PRIVDATA(dev)->atom_EventCounterRead)

/** Get the event write counter.
 * 
 * Event counter are managed with 
 * atomic type so they are 
 * protected against concurent access.
 * 
 * @param[in]	dev	Device to use. 	
 */
#define GET_EVENT_CPTW(dev)		atomic_read(&APCI1500_PRIVDATA(dev)->atom_EventCounterWrite)

/** Set the event read counter.
 * 
 * Event counter are managed with 
 * atomic type so they are 
 * protected against concurent access.
 * 
 * @param[in]	dev	Device to use. 	
 * @param[in]	val	Interger value to set. 	
 */
#define SET_EVENT_CPTR(dev,val)	atomic_set(&APCI1500_PRIVDATA(dev)->atom_EventCounterRead,val)

/** Set the event write counter.
 * 
 * Event counter are managed with 
 * atomic type so they are 
 * protected against concurent access.
 * 
 * @param[in]	dev	Device to use. 	
 * @param[in]	val	Interger value to set. 	
 */
#define SET_EVENT_CPTW(dev,val)	atomic_set(&APCI1500_PRIVDATA(dev)->atom_EventCounterWrite,val)

/** Increase the event read counter (+1).
 * 
 * Event counter are managed with 
 * atomic type so they are 
 * protected against concurent access.
 * 
 * @param[in]	dev	Device to use. 	
 */
#define INC_EVENT_CPTR(dev)		atomic_inc(&APCI1500_PRIVDATA(dev)->atom_EventCounterRead)

/** Increase the event write counter (+1).
 * 
 * Event counter are managed with 
 * atomic type so they are 
 * protected against concurent access.
 * 
 * @param[in]	dev	Device to use. 	
 */
#define INC_EVENT_CPTW(dev)		atomic_inc(&APCI1500_PRIVDATA(dev)->atom_EventCounterWrite)

//----------------------------------------------------------------------------------------------------------------------
/* typed cast (safer to use) */
static __inline__ struct apci1500_str_BoardInformations * APCI1500_PRIVDATA(struct pci_dev * pdev)
{	
	return (struct apci1500_str_BoardInformations *) pci_get_drvdata(pdev);
}

//----------------------------------------------------------------------------------------------------------------------

/** Lock the card. On UP computer, just deactivate interrupts.
 * 
 * @param __pdev pointer to a struct pci_dev 
 * @param __flag area to store interrupt flags 
 * @note It is recommanded that flag may be local to the calling function
 *  */
 
static inline void APCI1500_LOCK(struct pci_dev * __pdev, unsigned long * flags)
{ 
	spin_lock_irqsave(& (APCI1500_PRIVDATA(__pdev)->lock), *flags);
} 

/** Unlock the card. On UP computer, just reactivate interrupts */
static inline void APCI1500_UNLOCK(struct pci_dev * __pdev, unsigned long flags)
{
	spin_unlock_irqrestore(& (APCI1500_PRIVDATA(__pdev)->lock), flags);
}

//----------------------------------------------------------------------------------------------------------------------
/** return 1 if interrupts are enabled 0 otherwise */
static inline int apci1500_interrupt_is_enabled(struct pci_dev * pdev)
{
	return APCI1500_PRIVDATA(pdev)->s_InterruptInformations.b_InterruptStatus == APCI1500_ENABLE;
}
//----------------------------------------------------------------------------------------------------------------------
/* return 1 if the counter 3 was configured as a watchdog. 0 if it is a counter */
static inline int IS_COUNTER3_WATCHDOG(struct pci_dev * pdev)
{
	return APCI1500_PRIVDATA(pdev)->s_TimerCounterInformations.b_WatchdogCounter3Select == APCI1500_WATCHDOG;
}

#endif // __APCI1500_PRIVDATA_H_
