#ifndef __APCI1500_PRIVATE_H__
#define __APCI1500_PRIVATE_H__

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
#include <linux/wait.h>
#include <linux/spinlock.h>
#include <linux/ioctl.h>
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
#include <linux/proc_fs.h>

#include <apci.h>
#include <apci1500.h>
#include <apci1500-kapi.h>

#define APCI1500_MAX_EVENT_COUNTER	100

// CONTROL REGISTER DEFINE
enum
{
   APCI1500_Z8536_PORT_C,
   APCI1500_Z8536_PORT_B,
   APCI1500_Z8536_PORT_A,
   APCI1500_Z8536_CONTROL_REGISTER
};
//TIMER DEFINE
enum
{
   // 0
   APCI1500_RW_MASTER_INTERRUPT_CONTROL,
   APCI1500_RW_MASTER_CONFIGURATION_CONTROL,
   APCI1500_RW_PORT_A_INTERRUPT_CONTROL,
   APCI1500_RW_PORT_B_INTERRUPT_CONTROL,
   APCI1500_RW_TIMER_COUNTER_INTERRUPT_VECTOR,
   APCI1500_RW_PORT_C_DATA_PCITCH_POLARITY,
   APCI1500_RW_PORT_C_DATA_DIRECTION,
   APCI1500_RW_PORT_C_SPECIAL_IO_CONTROL,
   //7
   
   APCI1500_RW_PORT_A_COMMAND_AND_STATUS,
   APCI1500_RW_PORT_B_COMMAND_AND_STATUS,
   APCI1500_RW_CPT_TMR1_CMD_STATUS,
   APCI1500_RW_CPT_TMR2_CMD_STATUS,
   APCI1500_RW_CPT_TMR3_CMD_STATUS,
   APCI1500_RW_PORT_A_DATA,
   APCI1500_RW_PORT_B_DATA,
   APCI1500_RW_PORT_C_DATA,
   //15
   
   APCI1500_R_CPT_TMR1_VALUE_HIGH,
   APCI1500_R_CPT_TMR1_VALUE_LOW,
   APCI1500_R_CPT_TMR2_VALUE_HIGH,
   APCI1500_R_CPT_TMR2_VALUE_LOW,
   APCI1500_R_CPT_TMR3_VALUE_HIGH,
   APCI1500_R_CPT_TMR3_VALUE_LOW,
   APCI1500_RW_CPT_TMR1_TIME_CST_HIGH,
   APCI1500_RW_CPT_TMR1_TIME_CST_LOW,
   APCI1500_RW_CPT_TMR2_TIME_CST_HIGH,
   APCI1500_RW_CPT_TMR2_TIME_CST_LOW,
   APCI1500_RW_CPT_TMR3_TIME_CST_HIGH,
   //26
   APCI1500_RW_CPT_TMR3_TIME_CST_LOW,
   //27
   APCI1500_RW_CPT_TMR1_MODE_SPECIFICATION,
   APCI1500_RW_CPT_TMR2_MODE_SPECIFICATION,
   APCI1500_RW_CPT_TMR3_MODE_SPECIFICATION,
   APCI1500_R_CURRENT_VECTOR,
   //31
   
   APCI1500_RW_PORT_A_SPECIFICATION,
   APCI1500_RW_PORT_A_HANDSHAKE_SPECIFICATION,
   APCI1500_RW_PORT_A_DATA_PCITCH_POLARITY,
   APCI1500_RW_PORT_A_DATA_DIRECTION,
   APCI1500_RW_PORT_A_SPECIAL_IO_CONTROL,
   APCI1500_RW_PORT_A_PATTERN_POLARITY,
   APCI1500_RW_PORT_A_PATTERN_TRANSITION,
   APCI1500_RW_PORT_A_PATTERN_MASK,

   APCI1500_RW_PORT_B_SPECIFICATION,
   APCI1500_RW_PORT_B_HANDSHAKE_SPECIFICATION,
   APCI1500_RW_PORT_B_DATA_PCITCH_POLARITY,
   APCI1500_RW_PORT_B_DATA_DIRECTION,
   APCI1500_RW_PORT_B_SPECIAL_IO_CONTROL,
   APCI1500_RW_PORT_B_PATTERN_POLARITY,
   APCI1500_RW_PORT_B_PATTERN_TRANSITION,
   APCI1500_RW_PORT_B_PATTERN_MASK
};


	 /************************/
         /*  PCI BUS board infos */
	 /************************/

struct apci1500_str_TimerCounterInformations
{
   uint8_t   b_TimerCounter1Init;
   uint8_t   b_TimerCounter1Select;
   uint8_t   b_TimerCounter1Enabled;
   uint8_t   b_TimerCounter2Init;
   uint8_t   b_TimerCounter2Select;
   uint8_t   b_TimerCounter2Enabled;
   uint8_t   b_WatchdogCounter3Init;
   uint8_t   b_WatchdogCounter3Select;
   uint8_t   b_Counter3Enabled;
}
;

struct apci1500_str_DigitalOutputInformations
{
   uint32_t   l_DigitalOutputRegister;   /* Digital Output Register */
   uint8_t   b_OutputMemoryStatus;
}
;

struct apci1500_str_EventInformations
{
   uint8_t   b_SetEventMaskPort1;
   uint8_t   b_SetEventMaskPort2;
   uint8_t   b_Event1Status;
   uint8_t   b_Event2Status;
   uint8_t   b_Port1Logik;
   uint8_t   b_Port2Logik;
   uint8_t   b_UseInterrupt;
}
;

struct apci1500_str_InterruptInformations
{
   uint8_t   b_InterruptStatus;
   uint8_t   b_InterruptInitialised; 
   
   uint8_t   b_TimerCounter1UseInterrupt;
   uint8_t   b_TimerCounter2UseInterrupt;
   uint8_t   b_WatchdogCounter3UseInterrupt;
}
;

//----------------------------------------------------------------------------------------------------------------------
/* Interruption call-back */
/* This function is */
extern void (*apci1500_private_InterruptCallback) (struct pci_dev * pdev, char b_InterruptMask);

//----------------------------------------------------------------------------------------------------------------------


static __inline__ unsigned long GET_BAR0(struct pci_dev * pdev)
{
	//return pdev->resource[0].start;
	if (pdev->device == APCI1500_BOARD_DEVICE_ID)
		return pdev->resource[0].start; // apci1500
	else
		return pdev->resource[2].start; // apciE1500
}

static __inline__ unsigned long GET_BAR1(struct pci_dev * pdev)
{
	if (pdev->device == APCI1500_BOARD_DEVICE_ID)
		return pdev->resource[1].start; // apci1500
	else
		return pdev->resource[3].start; // apciE1500
}

static __inline__ unsigned long GET_BAR2(struct pci_dev * pdev)
{
	//return pdev->resource[2].start;
	if (pdev->device == APCI1500_BOARD_DEVICE_ID)
		return pdev->resource[2].start;	// apci1500
	else
		return pdev->resource[3].start + 4; // apciE1500
}

static __inline__ unsigned long GET_BAR4(struct pci_dev * pdev)
{
		return pdev->resource[1].start; // apciE1500 - for the interruption, plx for the PCIe controller
}


//----------------------------------------------------------------------------------------------------------------------
/** Utility fonction that returns 0 if the given index corresponds to a card already configured.
 * 
 * @param count Number of board 
 * @param index Minor number to check
 * 
 * @return 0 if minor number valid, not 0 otherwise
 * 
 * count ranges from 1 to ...
 * index ranges from 0 to ...
 * 
 * */

static __inline__ int APCI1500_INDEX_NOT_VALID(atomic_t * count , unsigned int index )
{
	volatile unsigned int __count =  atomic_read(count);
	if (index >= __count) return 1;
	return 0;
	
}

//----------------------------------------------------------------------------------------------------------------------
static __inline__ __u16 GET_TIMERMODE(__u32 __arg)
{
	return HISHORT(__arg);
}
static __inline__ __u16 GET_RELOADVALUE(__u32 __arg)
{
	return LOSHORT(__arg);
}

//----------------------------------------------------------------------------------------------------------------------
int APCI1500_fasync(int fd, struct file *filp, int mode);
int APCI1500_open(struct inode *inode, struct file *filp);
int APCI1500_release(struct inode *inode, struct file *filp);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
int APCI1500_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);
#else
long APCI1500_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
#endif

//----------------------------------------------------------------------------------------------------------------------
/** Global declarations for major number */
extern unsigned int apci1500_majornumber;

//----------------------------------------------------------------------------------------------------------------------
extern atomic_t apci1500_count;
//----------------------------------------------------------------------------------------------------------------------
#define __DRIVER_NAME "apci1500"
//----------------------------------------------------------------------------------------------------------------------
/** The following macros add a hardware memory barrier to ensure :
* - the compiler doesn't reorder the accesses.
* - the processsor doesn't reorder the read/write as modern processors may at run time
* Perfect ordering is vital for the chip to work correctly. 
*/
// read 8 bits IO
#define inb_mb(__port) inb(__port); mb();

// write 8 bits IO
#define outb_mb(__val,__port) outb(__val,__port); mb();

// read 16 bits IO
#define inw_mb(__port) inw(__port); mb();

// write 16 bits IO
#define outw_mb(__val,__port) outw(__val,__port); mb();

// read 32 bits IO
#define inl_mb(__port) inl(__port); mb();

// write 32 bits IO
#define outl_mb(__val,__port) outl(__val,__port); mb();



#include "api.h"
#include "apci1500-privdata.h"
#include "vtable.h"

/** introduce a delay before accessing the card */
static __inline__ void DELAY(void)
{
	udelay(50);
}

int i_APCI1500_SetInputEventMask_PortNumber1(struct pci_dev* pdev, unsigned long arg);
int i_APCI1500_SetInputEventMask_PortNumber2(struct pci_dev* pdev, unsigned long arg);
int i_APCI1500_PrivateSetBoardIntRoutine(struct pci_dev * pdev);

/** Execute a command.
*
* @param pdev Pointer to a device.
* @param cmd Command to execute
* @param arg Argument of the command.
*/
extern int 
apci1500_do_ioctl(struct pci_dev * pdev,unsigned int cmd,unsigned long arg);

#endif //__APCI1500_PRIVATE_H__


