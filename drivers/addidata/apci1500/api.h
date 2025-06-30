#ifndef __APCI1500_API_H_
#define __APCI1500_API_H_

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

#include <linux/delay.h>

#include "apci1500-private.h"



//------------------------------------------------------------------------------
/* deprecated */
extern int do_CMD_APCI1500_CheckAndGetPCISlotNumber(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);
extern int do_CMD_APCI1500_GetHardwareInformation(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

//------------------------------------------------------------------------------
int do_CMD_APCI1500_SetBoardInformation(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);
//------------------------------------------------------------------------------


int apci1500_register_interrupt(struct pci_dev * pdev);

extern int
do_CMD_APCI1500_SetBoardIntRoutine(struct pci_dev * pdev, unsigned int cmd, unsigned long arg );

extern int
do_CMD_APCI1500_ResetBoardIntRoutine(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_WaitInterrupt(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int 
do_CMD_APCI1500_EnableDisableTimerCounter1Interrupt(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int 
do_CMD_APCI1500_EnableDisableTimerCounter2Interrupt(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int 
do_CMD_APCI1500_EnableDisableWatchdogCounter3Interrupt(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_SetInputEventMask(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

int do_CMD_APCI1500_InitTimerInputClock(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

// WATCHDOG/COUNTER 3 

extern int
do_CMD_APCI1500_InitWatchdogCounter3(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_ReadCounter3(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_TriggerWatchdog(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_TriggerCounter3(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_StopCounter3(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_StartCounter3(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

int
do_CMD_APCI1500_GetWatchdogStatus(struct pci_dev* pdev, unsigned int cmd, unsigned long arg);

// TIMER/COUNTER 1

extern int
do_CMD_APCI1500_InitTimerCounter1(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_ReadTimerCounter1(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_StartTimerCounter1(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_TriggerTimerCounter1(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_StopTimerCounter1(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

// TIMER/COUNTER 2

extern int
do_CMD_APCI1500_InitTimerCounter2(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_StartTimerCounter2(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_TriggerTimerCounter2(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_ReadTimerCounter2(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_StopTimerCounter2(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

// DIGITAL INPUT
extern int
do_CMD_APCI1500_Read1DigitalInput(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_Read8DigitalInput(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_Read16DigitalInput(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_StartInputEvent(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_StopInputEvent(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

// OUTPUTS

extern int 
do_CMD_APCI1500_SetOutputMemoryOn(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int 
do_CMD_APCI1500_SetOutputMemoryOff(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_Set1DigitalOutputOn(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_Set1DigitalOutputOff(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_Set8DigitalOutputOn(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_Set8DigitalOutputOff(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_Set16DigitalOutputOn(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_Set16DigitalOutputOff(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int
do_CMD_APCI1500_Get16DigitalOutput(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int 
apci1500_do_dummy(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);

extern int 
do_CMD_APCI1500_GetWatchdogReloadValue(struct pci_dev * pdev, unsigned int cmd, unsigned long arg);


void do_watchdog_interrupt(struct pci_dev * pdev, uint8_t * b_InterruptMask);
#endif // __APCI1500_API_H_
