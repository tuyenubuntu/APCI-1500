/** @file sample02.c
*
* @author Krauth Julien
*
* Demonstrate how to use the driver in kernel mode with APCI-1500 and timer 1 interrupt.
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
#include <linux/spinlock.h>
#include <linux/ioctl.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/pci.h> // struct pci_dev
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
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

#include <apci1500.h>
#include <apci1500-kapi.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ADDI-DATA");
MODULE_DESCRIPTION("APCI-1500 sample");

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,12,0)
MODULE_SUPPORTED_DEVICE("APCI-1500");
#endif

EXPORT_NO_SYMBOLS;

/** The name of the modul. */
#define MODULE_NAME "ksample02 apci1500"

#define NUMBER_OF_BOARDS	1

/* Global pointer on the board structure. Global because it is used in module init and cleanup */
static struct pci_dev * _pdev[NUMBER_OF_BOARDS]; 

//--------------------------------------------------------------------------------
/* The user callback interrupt */
static void interrupt_callback (struct pci_dev * pdev, char dummy)
{
	static unsigned long info[2];
	static unsigned long counter = 0;

		/* Get interrupt informations */
		i_APCI1500_TestInterrupt(pdev, info);
		
		printk (KERN_DEBUG "Interrupt counter: %lu - ", counter++);
  					
   		/* Test if FIFO not empty */
   		if 	(0x7ffffffe != info[0])
   			{   	
	   			/* Event on port 1 */	
		   		if (info[0] & 0x1) {	
		   			printk (KERN_DEBUG "Event interrupt on port 1: %lx\n", info[1]);   						
	   			}
	   			
	   			/* Event on port 2 */	
		   		if (info[0] & 0x2) {	   						
		   			printk (KERN_DEBUG "Event interrupt on port 2: %lx\n", info[1]);
	   			}
	   			
	   			/* Timer 1 */	
		   		if (info[0] & 0x4) {	   						
		   			printk (KERN_DEBUG "Timer 1 interrupt\n");
	   			}	   			

	   			/* Timer 2 */	
		   		if (info[0] & 0x8) {	   						
		   			printk (KERN_DEBUG "Timer 2 interrupt\n");
	   			}	   			
  			}

		/* Driver fifo is full */	
   		if (0x7fffffff == info[0])
   			printk (KERN_DEBUG "Driver fifo is full\n");
  			
  		/* Driver fifo is empty */	
	   	if (0x7ffffffe == info[0])
	   		printk (KERN_DEBUG "Driver fifo is empty\n");
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

static int ksample02_init(struct pci_dev * pdev)
{
	int error = 0;
	unsigned long arg = 0;

	/* Set the interrupt callback and initialise the board interrupt */	
	error = i_APCI1500_SetBoardIntRoutine(pdev, interrupt_callback); 
                                            		
	printk (KERN_DEBUG "i_APCI1500_SetBoardIntRoutine :");   
	switch (error) {
		case 0: printk (KERN_DEBUG "OK\n");
		break;
	}            
	
	/* Set the clock to use */
	arg = APCI1500_1_8_KHZ;
	error = i_APCI1500_InitTimerInputClock(pdev, arg);
	                                           		
	printk (KERN_DEBUG "i_APCI1500_InitTimerInputClock:");   
	switch (error) {
		case 0: printk (KERN_DEBUG "OK\n");
		break;
		case -EINVAL: printk (KERN_DEBUG "arg value is wrong\n");
		break;		
	}

	arg = APCI1500_ENABLE;
	error = i_APCI1500_EnableDisableTimerCounter1Interrupt(pdev, arg);
	
	printk (KERN_DEBUG "i_APCI1500_EnableDisableTimerCounter1Interrupt:");   
	switch (error) {
		case 0: printk (KERN_DEBUG "OK\n");
		break;
		case -EINVAL: printk (KERN_DEBUG "Interrupt already enable or argument is wrong\n");
		break;		
	}	
	
	{
		short us_TimerMode = APCI1500_TIMER | APCI1500_CONTINUOUS;
		short us_ReloadValue = 1747; // 2 seconde
		unsigned long argInit = MAKELONG( us_TimerMode, us_ReloadValue );	
		
		error = i_APCI1500_InitTimerCounter1(pdev, argInit);
		
		printk (KERN_DEBUG "i_APCI1500_InitTimerCounter1:");   
		switch (error) {
			case 0: printk (KERN_DEBUG "OK\n");
			break;
		}
	}
	
	error = i_APCI1500_StartTimerCounter1(pdev);
	
	printk (KERN_DEBUG "i_APCI1500_StartTimerCounter1:");   
	switch (error) {
		case 0: printk (KERN_DEBUG "OK\n");
		break;
		case -EINVAL: printk (KERN_DEBUG "TimerCounter1 not initialised\n");
		break;			
	}	
	
	return error;
}
	
//-------------------------------------------------------------------------------- 

static void ksample02_release(struct pci_dev * pdev)
{				
	int error = 0;
	unsigned long arg = 0;
		
	error = i_APCI1500_StopTimerCounter1(pdev);
	
	printk (KERN_DEBUG "i_APCI1500_StopTimerCounter1");   
	switch (error) {
		case 0: printk (KERN_DEBUG "OK\n");
		break;
	}
	
	arg = APCI1500_DISABLE;
	error = i_APCI1500_EnableDisableTimerCounter1Interrupt(pdev, arg);
	
	printk (KERN_DEBUG "i_APCI1500_EnableDisableTimerCounter1Interrupt:");   
	switch (error) {
		case 0: printk (KERN_DEBUG "OK\n");
		break;
		case -EINVAL: printk (KERN_DEBUG "Interrupt already enable or argument is wrong\n");
		break;		
	}	
	
	i_APCI1500_ResetBoardIntRoutine(pdev);
	
	printk (KERN_DEBUG "i_APCI1500_ResetBoardIntRoutine");   
	switch (error) {
		case 0: printk (KERN_DEBUG "OK\n");
		break;
	}
}


//--------------------------------------------------------------------------------

/** Called when the driver is loaded.*/
static int __init _init_module(void)
{	
	int index = 0; /* Index of the board to use (here the fisrt board) */
		
	/* Get a pointer on the board to use */
	for (index=0; index < NUMBER_OF_BOARDS; index++) 
	{
		if ((_pdev[index] = apci1500_lookup_board_by_index(index)) == NULL) 
		{
			printk ( KERN_DEBUG "Board index %i not found\n", index);			
			return -ENODEV;
		}
		printk ( KERN_DEBUG "Board index %i found (slot: %s)\n", index,pci_name(_pdev[index]));
		
	} 
	
	/* Test the first board found */
	for (index=0; index<NUMBER_OF_BOARDS; index++)
	{
		register struct pci_dev * pdev = _pdev[index];
		unsigned long irqstate;
		/* get exclusive access to the board (local interruptions are deactivated) */ 
		apci1500_lock(pdev,&irqstate);
		{
			if ( ksample02_init (pdev) )
			{
				/* Reset the user interrupt callback */
				ksample02_release (pdev);
				apci1500_unlock(pdev,irqstate);
				return -EIO;
			}
		}
		apci1500_unlock(pdev,irqstate);
	}	
	
	return 0;
}		

//--------------------------------------------------------------------------------

/** Called when the driver is unloaded.*/
static void __exit _cleanup_module(void)
{
	int index = 0;
	
	for (index=0; index<NUMBER_OF_BOARDS; index++)
	{
		register struct pci_dev * pdev = _pdev[index];
		unsigned long irqstate;
		/* get exclusive access to the board (local interruptions are deactivated) */ 
		apci1500_lock(pdev,&irqstate);
		{
			ksample02_release (pdev);
		}
		apci1500_unlock(pdev,irqstate);
	}
}

//--------------------------------------------------------------------------------

module_init(_init_module);
module_exit(_cleanup_module);
