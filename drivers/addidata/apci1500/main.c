/** @file main.c
*
* - SN: removed global variables excepted iMajorNumber
* - SN: the logic of the card is now in other files.
* - SN: Adapted the module to the new PCI infrastructure (hotplug)
* - SN: added resources allocation/deallocation
* - SN: added check of user's arguments
*/

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

#include "api.h"

#include "apci1500-proc.h"
#include "knowndev.h"


//------------------------------------------------------------------------------

EXPORT_SYMBOL(APCI1500_SetIntCallback);
EXPORT_SYMBOL(APCI1500_ResetIntCallback);
EXPORT_SYMBOL(apci1500_get_lock);

EXPORT_NO_SYMBOLS;

#ifndef __devinit
#define __devinit
#define __devexit
#define __devinitdata
#define __devexit_p
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
#include <linux/sysfs.h>
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
#if LINUX_VERSION_CODE == KERNEL_VERSION(2,6,9)
	static struct class_simple * apci1500_class = NULL;
#else
	static struct class * apci1500_class = NULL;
#endif
#endif

//------------------------------------------------------------------------------
spinlock_t * apci1500_get_lock(struct pci_dev *pdev)
{
	return &(APCI1500_PRIVDATA(pdev)->lock);
}
//------------------------------------------------------------------------------
/** Global declarations for major number */
unsigned int apci1500_majornumber = 0;

//------------------------------------------------------------------------------
/* number of board managed by the driver */
atomic_t apci1500_count = ATOMIC_INIT(0);

//------------------------------------------------------------------------------
static struct file_operations APCI1500_fops =
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
		.ioctl		= APCI1500_ioctl,
#else
		.unlocked_ioctl	= APCI1500_ioctl,
#endif
		.open		= APCI1500_open,
		.release	= APCI1500_release,
		.fasync		= APCI1500_fasync,
};

//----------------------------------------------------------------------------------------------------------------------
static int __devinit apci1500_probe_one(struct pci_dev *dev,
		const struct pci_device_id *ent);

static void __devexit apci1500_remove_one(struct pci_dev *dev);


//------------------------------------------------------------------------------
/** The ID table is an array of struct pci_device_id ending with a all-zero entry.
Each entry consists of:

- vendor, device	Vendor and device ID to match (or PCI_ANY_ID)
- subvendor,	Subsystem vendor and device ID to match (or PCI_ANY_ID)
- subdevice class,		Device class to match. The class_mask tells which bits
- class_mask	of the class are honored during the comparison.
- driver_data	Data private to the driver.
*/

static struct pci_device_id apci1500_pci_tbl[] __devinitdata = {
				#include "devices.ids"
				{ 0 },	/* terminate list */

};

MODULE_DEVICE_TABLE (pci, apci1500_pci_tbl);

//----------------------------------------------------------------------------------------------------------------------

static struct pci_driver apci1500_pci_driver =
{
		.name		= __DRIVER_NAME,
		.probe		= apci1500_probe_one,
		.remove		= __devexit_p(apci1500_remove_one),
		.id_table	= apci1500_pci_tbl,
};
//----------------------------------------------------------------------------------------------------------------------

//BEGIN JK 06.12.2004: Module informatIon
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ADDI-DATA GmbH <info@addi-data.com>");
MODULE_DESCRIPTION("APCI-1500 IOCTL driver");

//END JK 06.12.2004: Module informtaion

//------------------------------------------------------------------------------
/** This function registers the driver with register_chrdev.
*
* @todo For kernel 2.6, use udev
*  */

static int apci1500_register(void)
{

	//Registration of driver
	apci1500_majornumber = register_chrdev(0, __DRIVER_NAME, &APCI1500_fops);

	if (apci1500_majornumber < 0)
	{
		printk (KERN_ERR "%s: register_chrdev returned %d ... aborting\n",__DRIVER_NAME,apci1500_majornumber);
		return -ENODEV;
	}
	return 0;
}


//------------------------------------------------------------------------------
/** This function unregisters the driver with unregister_chrdev.
*
* @todo For kernel 2.6, use udev
*  */

static void apci1500_unregister(void)
{
	unregister_chrdev(apci1500_majornumber, __DRIVER_NAME);
}

//-------------------------------------------------------------------

/**
 *
 * @param pdev
 * @retval 0: No error
 * @retval 1: Zilog access problem or not found
 */
static int ZilogInitialization (struct pci_dev* pdev)
{

	unsigned long irqstate = 0; /**< save local interrupt flag*/
	volatile uint8_t b_DummyRead = 0;
	volatile uint8_t b_ControlReg = 0;
	int ret = 0;

	DELAY();

	/* Software reset of the ZiLOG */
	APCI1500_LOCK(pdev,&irqstate);
	{
		/* The following functions prepares the ZiLOG I/O ports and */
		/* the used registers for the right directions and contents */

		// For apci1500
		b_DummyRead = inb_mb( (GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER) ); // GET_BAR3 for apcie1500
		outb_mb(0, (GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER) );			// GET_BAR3 for apcie1500
		b_DummyRead = inb_mb(GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);		// GET_BAR3 for apcie1500
		outb_mb(0, ( GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER) );			// GET_BAR3 for apcie1500
		outb_mb(1, (GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER) );			// GET_BAR3 for apcie1500
		outb_mb(0, (GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER) );			// GET_BAR3 for apcie1500

		/* Selects the master configuration control register */
		outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, ( GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER) );
		outb_mb(0x10, ( GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER) );

		/* Selects the master configuration control register */
		outb_mb(APCI1500_RW_MASTER_CONFIGURATION_CONTROL, ( GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER) );

		/* Reads configuration of port A, B, C and watchdog / counter */
		b_ControlReg = inb_mb( GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		/* Tests if board is present */
		if (b_ControlReg == 0x10)
		{
			/* Selects the master interrupt control register */
			outb_mb(APCI1500_RW_MASTER_INTERRUPT_CONTROL,GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER);

			/* Deletes all interrupts */
			outb_mb(0, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the mode specification register of port A */
			outb_mb(APCI1500_RW_PORT_A_SPECIFICATION, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
			outb_mb(0x10, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the data path polarity of port A */
			outb_mb(APCI1500_RW_PORT_A_DATA_PCITCH_POLARITY, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* High level on port A means 1 */
			outb_mb(0xFF,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the data direction register of port A */
			outb_mb(APCI1500_RW_PORT_A_DATA_DIRECTION, GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER);

			/* All bits are used as inputs */
			outb_mb(0xFF, GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of port A */
			outb_mb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Clear IP and IUS */
			outb_mb(0x20, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of port A */
			outb_mb(APCI1500_RW_PORT_A_COMMAND_AND_STATUS, GET_BAR1(pdev) +	APCI1500_Z8536_CONTROL_REGISTER);
			outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the handshake specification register of port A */
			outb_mb(APCI1500_RW_PORT_A_HANDSHAKE_SPECIFICATION, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Clear the register */
			outb_mb(0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the mode specification register of port B */
			outb_mb(APCI1500_RW_PORT_B_SPECIFICATION, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
			outb_mb(0x10,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the data path polarity of port B */
			outb_mb(APCI1500_RW_PORT_B_DATA_PCITCH_POLARITY, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* High level on port B means 1 */
			outb_mb(0x7F, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the data direction register of port B */
			outb_mb(APCI1500_RW_PORT_B_DATA_DIRECTION,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* All bits are used as inputs */
			outb_mb(0xFF,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of port B */
			outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Delete IP and IUS */
			outb_mb(0x20,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of port B */
			outb_mb(APCI1500_RW_PORT_B_COMMAND_AND_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
			outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the handshake specification register of port A */
			outb_mb(APCI1500_RW_PORT_B_HANDSHAKE_SPECIFICATION,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Deletes the register */
			outb_mb(0, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the data path polarity of port C */
			outb_mb(APCI1500_RW_PORT_C_DATA_PCITCH_POLARITY, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* High level on port C means 1 */
			outb_mb(0x9,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the data direction register of port C */
			outb_mb(APCI1500_RW_PORT_C_DATA_DIRECTION,GET_BAR1(pdev) +APCI1500_Z8536_CONTROL_REGISTER);

			/* All bits are used as inputs except channel 1 */
			outb_mb(0x0E,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the special I/O register of port C */
			outb_mb(APCI1500_RW_PORT_C_SPECIAL_IO_CONTROL,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Deletes the register */
			outb_mb(0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of timer 1 */
			outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Deletes IP and IUS */
			outb_mb(0x20, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of timer 1 */
			outb_mb(APCI1500_RW_CPT_TMR1_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
			outb_mb(0xE0, GET_BAR1(pdev)+ APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of timer 2 */
			outb_mb(APCI1500_RW_CPT_TMR2_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Deletes IP and IUS */
			outb_mb(0x20, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of timer 2 */
			outb_mb(APCI1500_RW_CPT_TMR2_CMD_STATUS,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
			outb_mb(0xE0,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of timer 3 */
			outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Deletes IP and IUS */
			outb_mb(0x20, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the command and status register of timer 3 */
			outb_mb(APCI1500_RW_CPT_TMR3_CMD_STATUS, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
			outb_mb(0xE0, GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

			/* Selects the master interrupt control register */
			outb_mb(APCI1500_RW_MASTER_INTERRUPT_CONTROL,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);
			outb_mb(0xF4,GET_BAR1(pdev) + APCI1500_Z8536_CONTROL_REGISTER);

		}
		else
		{
			printk(KERN_ERR "%s : debug Zilog access problem or not found  \n",__DRIVER_NAME);
			ret = 1;

		}

	}
	APCI1500_UNLOCK(pdev,irqstate);

	return ret;
}

//-------------------------------------------------------------------
/** called when a new card is detected.
*
* Historically - in former ADDI-DATA drivers data about a board has been stored
* in a static structure.
* This led to huge duplication of information since most of these information
* are already present in the pci_dev struct.
*
* Now the apci1500_str_BoardInformations contains a field "dev", a pointer to
* the OS PCI device structure.
*
*  */
static int __devinit apci1500_probe_one(struct pci_dev * pdev, const struct pci_device_id *ent)
{

	struct apci1500_str_BoardInformations * newboard_data = NULL;

	{
		int ret = pci_enable_device(pdev);
		if (ret)
		{
			printk(KERN_ERR "%s: pci_enable_device failed\n",__DRIVER_NAME);
			return ret;
		}
	}

	/* register interrupt handler to OS */
	{


		/* register interrupt */
		if ( apci1500_register_interrupt(pdev) )
		{
			printk(KERN_ERR "%s: Can't register IRQ for board %s\n", __DRIVER_NAME,pci_name(pdev));
			pci_disable_device(pdev);
			return -EBUSY;
		}
	}
	/* KERNEL 2.4 --------------------------------------------- */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
	/* check if BAR 0 is free */
	if ( check_region(pdev->resource[0].start, pci_resource_len(pdev,0)) )
	{
		printk(KERN_WARNING "%s: BAR 0 (%lX) is already in use\n",__DRIVER_NAME,pdev->resource[0].start);
		return -EBUSY;
	}
	/* check if BAR 1 is free */
	if ( check_region(pdev->resource[1].start, pci_resource_len(pdev,1)) )
	{
		printk(KERN_WARNING "%s: BAR 1 (%lX) is already in use\n",__DRIVER_NAME,pdev->resource[1].start);
		return -EBUSY;
	}
	/* check if BAR 2 is free */
	if ( check_region(pdev->resource[2].start, pci_resource_len(pdev,2)) )
	{
		printk(KERN_WARNING "%s: BAR 2 (%lX) is already in use\n",__DRIVER_NAME,pdev->resource[2].start);
		return -EBUSY;
	}
#endif

	/* allocate a new data structure for the board */
	{
		newboard_data = kmalloc( sizeof( struct apci1500_str_BoardInformations) , GFP_ATOMIC);
		if (!newboard_data)
		{
			printk(KERN_CRIT "Can't allocate memory for new board %s\n",pci_name(pdev));
			return -ENOMEM;
		}
	}

	pci_set_drvdata(pdev,newboard_data);

	/* requests BAR 0 to 2 memory regions */
	{
		int ret = pci_request_regions(pdev,__DRIVER_NAME);
		if (ret)
		{
			printk(KERN_ERR "%s: pci_request_regions failed\n",__DRIVER_NAME);
			/* free all allocated ressources here*/
			kfree(newboard_data);
			return ret;
		}
	}

	apci1500_init_priv_data(newboard_data);

	newboard_data->s_DigitalOutputInformations.l_DigitalOutputRegister = 0;
	newboard_data->s_DigitalOutputInformations.b_OutputMemoryStatus = 0;
	newboard_data->async_queue = NULL;

	/* associate board with OS PCI structure */
	newboard_data->dev = pdev;

	/* increase the global board count */
	{
		atomic_inc(&apci1500_count);
		printk(KERN_INFO "%s: minor number of board %s [%X:%X] will be %d\n",
				__DRIVER_NAME,
				pci_name(pdev),
				APCI1500_BOARD_VENDOR_ID,
				APCI1500_BOARD_DEVICE_ID,
				atomic_read(&apci1500_count)-1);
	}

	/* create board entry in /proc */
	apci1500_proc_create_device(pdev, atomic_read(&apci1500_count)-1);

	apci1500_known_dev_append(pdev);

	/* Save the minor number */
	APCI1500_PRIVDATA(pdev)->i_MinorNumber = atomic_read(&apci1500_count)-1;

	/* Initialize the Zilog.
	 * This was done by the do_CMD_APCI1500_SetBoardInformation function.
	 * Sometimes call to do_CMD_APCI1500_SetBoardInformation function was forgotten
	 * and some functionalities of the APCI-1500 don't work.
	 * It is better to do this initialization automatically when the
	 * board is detected.
	 */

	if (ZilogInitialization (pdev))
		return -ENODEV;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
	while(1)
	{
		#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
				struct class_device *cdev;
		#else
				struct device *cdev;
		#endif

		int minor = (atomic_read(&apci1500_count)-1);

		/* don't execute if class not exists */
		if (IS_ERR(apci1500_class))
			break;

		#if LINUX_VERSION_CODE == KERNEL_VERSION(2,6,9)
				cdev = class_simple_device_add (apci1500_class, MKDEV(apci1500_majornumber, minor), NULL, "%s_%d", __DRIVER_NAME, minor);
		#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
				cdev = class_device_create (apci1500_class, NULL, MKDEV(apci1500_majornumber, minor), NULL, "%s_%d", __DRIVER_NAME, minor);
		#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,27)
				cdev = device_create (apci1500_class, NULL, MKDEV(apci1500_majornumber, minor), "%s_%d", __DRIVER_NAME, minor);
		#else
				cdev = device_create (apci1500_class, NULL, MKDEV(apci1500_majornumber, minor), NULL, "%s_%d", __DRIVER_NAME, minor);
		#endif

		if (IS_ERR(cdev))
		{
			printk (KERN_WARNING "%s: class_device_create error\n", __DRIVER_NAME);
		}
		break;
	}
#endif

	return 0;
}

//------------------------------------------------------------------------------
/** stop all the activities of the board.
* Important : deactivate interrupt
* TODO : don't deactivate interrupt when it is already deactivated

*/
static void apci1500_stop_board(struct pci_dev * ptr)
{
	do_CMD_APCI1500_StopTimerCounter1( ptr,CMD_APCI1500_StopTimerCounter1,0);
	do_CMD_APCI1500_StopTimerCounter2( ptr , CMD_APCI1500_StopTimerCounter2, 0);
	do_CMD_APCI1500_StopCounter3( ptr ,CMD_APCI1500_StopCounter3, 0);
	do_CMD_APCI1500_StopInputEvent( ptr, CMD_APCI1500_StopInputEvent, 1 );
	do_CMD_APCI1500_StopInputEvent( ptr, CMD_APCI1500_StopInputEvent, 2 );
	do_CMD_APCI1500_ResetBoardIntRoutine(ptr,CMD_APCI1500_ResetBoardIntRoutine, 0);
}

//-------------------------------------------------------------------
/** a card is removed */
static void __devexit apci1500_remove_one(struct pci_dev * pdev)
{

	if (!pdev) return;

	if (!APCI1500_PRIVDATA(pdev) )
	{
		printk(KERN_WARNING "%s: %s: driver should manage board %s but it doesn't appear to be configured \n", __DRIVER_NAME, __FUNCTION__, pci_name(pdev));
		return;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
	while(1)
	{
		int minor = (atomic_read(&apci1500_count)-1);

		/* don't execute if class not exists */
		if(IS_ERR(apci1500_class))
			break;

#if LINUX_VERSION_CODE == KERNEL_VERSION(2,6,9)
		class_simple_device_remove(MKDEV(apci1500_majornumber, minor));
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
		class_device_destroy (apci1500_class, MKDEV(apci1500_majornumber, minor));
#else
		device_destroy (apci1500_class, MKDEV(apci1500_majornumber, minor));
#endif

		break;
	}
#endif

	/* stop all card activities  */
	apci1500_stop_board(pdev);

	pci_disable_device(pdev);

	/* release BAR 0 to 2 memory regions */
	pci_release_regions(pdev);

	/* release IRQ */
	free_irq( pdev->irq , pdev);
	printk(KERN_DEBUG "%s: freed interrupt handler of board %s\n",__DRIVER_NAME,pci_name(pdev));

	/* free data associated with device */
	kfree(APCI1500_PRIVDATA(pdev));

	atomic_dec(&apci1500_count);

	/* delete board entry in /proc */
	apci1500_proc_release_device(pdev);

	printk("%s: board %s unloaded \n",__DRIVER_NAME,pci_name(pdev));

}

//------------------------------------------------------------------------------
/** module initialisation */
static int __init apci1500_init(void)
{

	apci1500_init_vtable(apci1500_vtable);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
	//Detection PCI Bus
	if (!pci_present())
	{
		printk (KERN_WARNING "%s: NO PCI BUS PRESENT.\n",__DRIVER_NAME);
		return -ENODEV;
	}
#endif

	if( apci1500_register() )
	{
		return -ENODEV;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)

	#if LINUX_VERSION_CODE == KERNEL_VERSION(2,6,9)

		apci1500_class = class_simple_create(THIS_MODULE, __DRIVER_NAME);
		if (IS_ERR(apci1500_class))
		{
			printk (KERN_WARNING "%s: class create error\n",__DRIVER_NAME );
		}

	#else

		apci1500_class = ADDI_CLASS_CREATE(THIS_MODULE, __DRIVER_NAME);
		if (IS_ERR(apci1500_class))
		{
			printk (KERN_WARNING "%s: class_create error\n",__DRIVER_NAME );
		}

	#endif

#endif

	apci1500_proc_init();

	printk(KERN_INFO "%s: loaded\n",__DRIVER_NAME);

	/** @note The module will load anyway even if the call to pci_module_init() fails */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)
	if ( pci_module_init (&apci1500_pci_driver) != 0 )
#else
		if ( pci_register_driver (&apci1500_pci_driver) != 0)
#endif
		{
			printk("%s: no device found\n",__DRIVER_NAME);
			apci1500_pci_driver.name = "";
		}



	return 0;
}

//-------------------------------------------------------------------
/** Called when module is unloaded. */
static void __exit apci1500_exit(void)
{
	if (apci1500_pci_driver.name[0])
		pci_unregister_driver (&apci1500_pci_driver);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
	#if LINUX_VERSION_CODE == KERNEL_VERSION(2,6,9)
		if ( !IS_ERR(apci1500_class) )
			class_simple_destroy(apci1500_class);
	#else
        /* don't execute if class not exists */
        if ( !IS_ERR(apci1500_class) )
            class_destroy (apci1500_class);
	#endif
#endif

	apci1500_unregister();
	apci1500_proc_release();
}
//-------------------------------------------------------------------

module_exit(apci1500_exit);
module_init(apci1500_init);


