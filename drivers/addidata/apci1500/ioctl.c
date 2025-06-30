/** @file ioctl.c
*
* @author Sylvain Nahas
*
* This module implements the apci1500_do_ioctl function
*/

/** @par LICENCE
* @verbatim
 Copyright (C) 2004,2005  ADDI-DATA GmbH for the source code and the documentation.
        
        ADDI-DATA GmbH
        Dieselstrasse 3 
        D-77833 Ottersweier
        Tel: +19(0)7223/9493-0
        Fax: +49(0)7223/9493-92
        http://www.addi-data-com
        info@addi-data.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details. 
        
    You shoud find the complete GPL in the COPYING file accompanying 
    this source code. 
* @endverbatim
*/

#include "apci1500-private.h"

EXPORT_NO_SYMBOLS;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,27)
	#define __user 
#endif

//------------------------------------------------------------------------------
/** dummy command to be called when a ioctl command is incorrect */
int apci1500_do_dummy(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	printk (KERN_WARNING "%s: %d: invalid ioctl\n",__DRIVER_NAME,_IOC_NR(cmd));
	return -EINVAL;
}
//------------------------------------------------------------------------------
/** add new ioctl handlers here */
void apci1500_init_vtable(vtable_t vtable)
{
		
	apci1500_dummyze_vtable(vtable, apci1500_do_dummy);

	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_CheckAndGetPCISlotNumber,do_CMD_APCI1500_CheckAndGetPCISlotNumber);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_GetHardwareInformation,do_CMD_APCI1500_GetHardwareInformation);	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_SetBoardInformation,do_CMD_APCI1500_SetBoardInformation);			

	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_SetBoardIntRoutine,do_CMD_APCI1500_SetBoardIntRoutine);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_ResetBoardIntRoutine,do_CMD_APCI1500_ResetBoardIntRoutine);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_WaitInterrupt,do_CMD_APCI1500_WaitInterrupt);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_SetInputEventMask,do_CMD_APCI1500_SetInputEventMask);
	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_EnableDisableTimerCounter1Interrupt,do_CMD_APCI1500_EnableDisableTimerCounter1Interrupt);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_EnableDisableTimerCounter2Interrupt,do_CMD_APCI1500_EnableDisableTimerCounter2Interrupt);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_EnableDisableWatchdogCounter3Interrupt,do_CMD_APCI1500_EnableDisableWatchdogCounter3Interrupt);

	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_InitTimerInputClock,do_CMD_APCI1500_InitTimerInputClock);

	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_InitTimerCounter1,do_CMD_APCI1500_InitTimerCounter1);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_ReadTimerCounter1,do_CMD_APCI1500_ReadTimerCounter1);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_StartTimerCounter1,do_CMD_APCI1500_StartTimerCounter1);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_TriggerTimerCounter1,do_CMD_APCI1500_TriggerTimerCounter1);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_StopTimerCounter1,do_CMD_APCI1500_StopTimerCounter1);
	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_InitTimerCounter2,do_CMD_APCI1500_InitTimerCounter2);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_StartTimerCounter2,do_CMD_APCI1500_StartTimerCounter2);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_ReadTimerCounter2,do_CMD_APCI1500_ReadTimerCounter2);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_TriggerTimerCounter2,do_CMD_APCI1500_TriggerTimerCounter2);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_StopTimerCounter2,do_CMD_APCI1500_StopTimerCounter2);

	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_Read1DigitalInput,do_CMD_APCI1500_Read1DigitalInput);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_Read8DigitalInput,do_CMD_APCI1500_Read8DigitalInput);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_Read16DigitalInput,do_CMD_APCI1500_Read16DigitalInput);
		
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_StartInputEvent,do_CMD_APCI1500_StartInputEvent);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_StopInputEvent,do_CMD_APCI1500_StopInputEvent);
	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_SetOutputMemoryOn,do_CMD_APCI1500_SetOutputMemoryOn);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_SetOutputMemoryOff,do_CMD_APCI1500_SetOutputMemoryOff);	
	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_Set1DigitalOutputOn,do_CMD_APCI1500_Set1DigitalOutputOn);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_Set1DigitalOutputOff,do_CMD_APCI1500_Set1DigitalOutputOff);
	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_Set8DigitalOutputOn,do_CMD_APCI1500_Set8DigitalOutputOn);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_Set8DigitalOutputOff,do_CMD_APCI1500_Set8DigitalOutputOff);
	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_Set16DigitalOutputOn,do_CMD_APCI1500_Set16DigitalOutputOn);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable, CMD_APCI1500_Set16DigitalOutputOff, do_CMD_APCI1500_Set16DigitalOutputOff);	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable, CMD_APCI1500_Get16DigitalOutput, do_CMD_APCI1500_Get16DigitalOutput);

	
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_InitWatchdogCounter3,do_CMD_APCI1500_InitWatchdogCounter3);

	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_ReadCounter3,do_CMD_APCI1500_ReadCounter3);

	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_TriggerWatchdog,do_CMD_APCI1500_TriggerWatchdog);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_TriggerCounter3,do_CMD_APCI1500_TriggerCounter3);

	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable, CMD_APCI1500_StopCounter3, do_CMD_APCI1500_StopCounter3);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_StartCounter3,do_CMD_APCI1500_StartCounter3);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_GetWatchdogStatus,do_CMD_APCI1500_GetWatchdogStatus);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_GetWatchdogStatus,do_CMD_APCI1500_GetWatchdogStatus);
	__APCI_1500_DECLARE_IOCTL_HANDLER(vtable,CMD_APCI1500_GetWatchdogReloadValue,do_CMD_APCI1500_GetWatchdogReloadValue);
	
}

//------------------------------------------------------------------------------
int apci1500_do_ioctl(struct pci_dev * pdev,unsigned int cmd,unsigned long arg)
{

	/* boundaries check 
	 * 
	 * VTABLE_ELEMENT_NB(vtable_t) = __APCI1500_UPPER_IOCTL_CMD +1
	 * maximum index value = __APCI1500_UPPER_IOCTL_CMD = VTABLE_ELEMENT_NB(vtable_t) -1
	 * 
	 * the idea here is to favorize compilation-time 
	 * 
	 * */
	
	if (_IOC_NR(cmd) > (VTABLE_ELEMENT_NB(vtable_t)-1) )
		return apci1500_do_dummy(pdev,cmd,arg);
 
	/* call actual ioctl handler - should be safe now */
	return (apci1500_vtable[_IOC_NR(cmd)]) (pdev, cmd, arg);
}

//------------------------------------------------------------------------------
int do_CMD_APCI1500_CheckAndGetPCISlotNumber(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	int retval = 0; /* return value of this call is the number of boards */
	
    /* this command returns an area of size CONFIG_APCI1500_MAX_BOARD_NBR+1 filled with the PCI_SLOT() value and as last field the major number associated to the device - this is deprecated and should not be used anymore.
	The call returns 0 when memory is too low or the number of boards  */	
   
	char * b_SlotArray = kmalloc(CONFIG_APCI1500_MAX_BOARD_NBR+1 * sizeof(char),GFP_KERNEL);
    if (!b_SlotArray)
	{
		/* bad param. Let output some information for debug */
		printk("%s: CMD_APCI1500_CheckAndGetPCISlotNumber: -EINVAL\n",__DRIVER_NAME);
		return 0;
	}
	    
	memset(b_SlotArray,0,CONFIG_APCI1500_MAX_BOARD_NBR+1 );

	printk("%s: the use of CMD_APCI1500_CheckAndGetPCISlotNumber is deprecated\n",__DRIVER_NAME);

	/* record the PCI_SLOT for each device from 0 to CONFIG_APCI1500_MAX_BOARD_NBR  */
	{	    	
		int i;
		for(i = 0; ( ( i < atomic_read(&apci1500_count) ) || ( i< CONFIG_APCI1500_MAX_BOARD_NBR ) ); i++)
		{
			
			struct pci_dev * dev =  apci1500_lookup_board_by_index(i);
			
			if (!dev) break;
			
			b_SlotArray[i] = PCI_SLOT(dev->devfn);
			
		}
    }
    b_SlotArray[CONFIG_APCI1500_MAX_BOARD_NBR] = apci1500_majornumber;

    if ( copy_to_user ( (char __user *)arg, b_SlotArray, sizeof (uint8_t[CONFIG_APCI1500_MAX_BOARD_NBR+1])) )
	{
    	/* bad address. Let output some information for debug */
    	printk("%s: CMD_APCI1500_CheckAndGetPCISlotNumber: -EFAULT\n",__DRIVER_NAME);
    	kfree(b_SlotArray);
    	return 0;
	}
	/* return the smaller value between CONFIG_APCI1500_MAX_BOARD_NBR and number of board - Note: apci1500_count is assumed to to be always consistent with the system PCI devices list */
    retval = ( atomic_read(&apci1500_count) < CONFIG_APCI1500_MAX_BOARD_NBR ? atomic_read(&apci1500_count) : CONFIG_APCI1500_MAX_BOARD_NBR );

	kfree(b_SlotArray);	            	
	
	return retval;	

}



//------------------------------------------------------------------------------
/** Returns the informations of base address, IRQ to the user.
 * @deprecated: use-space doesn't need it and kernel-space has better means to get it.
 *  */
int do_CMD_APCI1500_GetHardwareInformation(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	str_BaseInformations s_BaseInformations;
	s_BaseInformations.ui_BaseAddress[0] = GET_BAR0(pdev);
	s_BaseInformations.ui_BaseAddress[1] = GET_BAR1(pdev);
	s_BaseInformations.ui_BaseAddress[2] = 0;
	s_BaseInformations.ui_BaseAddress[3] = 0;
	s_BaseInformations.ui_BaseAddress[4] = 0;
	s_BaseInformations.b_Interrupt = pdev->irq;
	s_BaseInformations.b_SlotNumber = PCI_SLOT(pdev->devfn);

    if ( copy_to_user ((str_BaseInformations __user *)arg,&s_BaseInformations, sizeof(s_BaseInformations)) )
		return -EFAULT;
	
	return 0;
}


