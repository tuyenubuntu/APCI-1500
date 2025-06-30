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
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,12,0)
	#include <asm/uaccess.h>
#else
	#include <linux/uaccess.h>
#endif
#include <asm/io.h>

#include "apci1500-private.h"

EXPORT_NO_SYMBOLS;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,27)
	#define __user 
#endif
//------------------------------------------------------------------------------
int
do_CMD_APCI1500_Read1DigitalInput(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	volatile uint32_t ui_TmpValue = 0;
	char chan = 0;
	int ret = 0;

	/* Gets the channel number from the user */
	if (get_user(chan, (char __user *) arg))
	{
		return -EFAULT;
	}
	
	// no need to lock board ( PRIVDATA not used in i_APCI1500_Read1DigitalInput )
	ret = i_APCI1500_Read1DigitalInput(pdev, chan, (uint8_t*)&ui_TmpValue);
	if (ret)
		return ret; 

	/* Returns the modified input value to the user */
	if ( put_user((uint8_t) ui_TmpValue, (char __user *) arg) )
		return -EFAULT;
	
	return 0;	
	
}
//------------------------------------------------------------------------------
int
do_CMD_APCI1500_Read8DigitalInput(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	volatile uint32_t ui_TmpValue = 0;
	uint8_t port = 0;	
	int ret = 0;

	/* Gets the port number from the user */
	if (get_user(port, (uint8_t __user * ) arg) )
		return -EFAULT;

	/* no need to lock board ( PRIVDATA not used in i_APCI1500_Read1DigitalInput ) */
	ret = i_APCI1500_Read8DigitalInput(pdev, port, (uint8_t*)&ui_TmpValue);
	if (ret)
		return ret;

	/* Returns the modified input value to the user */
	if ( put_user((char) ui_TmpValue, (char __user *) arg) )
		return -EFAULT;
		
	return 0;

}
//------------------------------------------------------------------------------
int
do_CMD_APCI1500_Read16DigitalInput(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	volatile uint32_t ui_TmpValue = 0;
	
	/* No return value */		
	/* no need to lock board ( PRIVDATA not used in i_APCI1500_Read16DigitalInput ) */
	i_APCI1500_Read16DigitalInput(pdev, (uint16_t*)&ui_TmpValue);

	/* Returns the input value to the user */
	if ( put_user( (uint16_t) ui_TmpValue, (uint16_t __user *) arg) )
		return -EFAULT;
	
	return 0;
}

//------------------------------------------------------------------------------
int
do_CMD_APCI1500_Get16DigitalOutput(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	volatile uint32_t ui_TmpValue = 0;
	
	/* No return value */		
	/* no need to lock board ( PRIVDATA not used in i_APCI1500_Read16DigitalInput ) */
	i_APCI1500_Get16DigitalOutput(pdev, (uint32_t*)&ui_TmpValue);

	/* Returns the input value to the user */
	if ( put_user( (uint32_t) ui_TmpValue, (uint32_t __user *) arg) )
		return -EFAULT;
	
	return 0;
}

// int do_CMD_APCI1500_Get16DigitalOutput(struct pci_dev *pdev, unsigned int cmd, unsigned long arg)
// {
//     uint16_t output_state;
//     void __iomem *base_addr;

//     base_addr = pci_resource_start(pdev, 2); // Giả sử BAR2 là nơi đặt Digital Outputs
//     if (!base_addr) return -ENODEV;

//     output_state = ioread16(base_addr + APCI1500_DIGITAL_OUTPUT);

//     if (copy_to_user((uint16_t __user *)arg, &output_state, sizeof(uint16_t)))
//         return -EFAULT;

//     return 0;
// }

//------------------------------------------------------------------------------
int
do_CMD_APCI1500_Set1DigitalOutputOn(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	int ret;
	
	/* PRIVDATA is used in i_APCI1500_Set1DigitalOutputOn */
	{
		unsigned long irqstate;
		APCI1500_LOCK(pdev,&irqstate);
		{
			ret = i_APCI1500_Set1DigitalOutputOn(pdev, (uint8_t)arg); 
		}
		APCI1500_UNLOCK(pdev,irqstate);
	}
	return ret;
}
//------------------------------------------------------------------------------
int
do_CMD_APCI1500_Set1DigitalOutputOff(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	
	int ret;
	
	/* PRIVDATA is used in i_APCI1500_Set1DigitalOutputOn */
	{
		unsigned long irqstate;
		APCI1500_LOCK(pdev,&irqstate);
		{
			ret = i_APCI1500_Set1DigitalOutputOff(pdev, (uint8_t)arg); 
		}
		APCI1500_UNLOCK(pdev,irqstate);
	}
	return ret;
}
//------------------------------------------------------------------------------

int
do_CMD_APCI1500_Set8DigitalOutputOn(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	int ret;
	
	/* PRIVDATA is used in i_APCI1500_Set8DigitalOutputOn */
	{
		unsigned long irqstate;
		APCI1500_LOCK(pdev,&irqstate);
		{
			ret = i_APCI1500_Set8DigitalOutputOn(pdev, HIBYTE(arg), LOBYTE(arg));
		}
		APCI1500_UNLOCK(pdev,irqstate);
	}
	return ret;
}
//------------------------------------------------------------------------------

int
do_CMD_APCI1500_Set8DigitalOutputOff(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	int ret;
	
	/* PRIVDATA is used in i_APCI1500_Set8DigitalOutputOff */
	{
		unsigned long irqstate;
		APCI1500_LOCK(pdev,&irqstate);
		{
			ret = i_APCI1500_Set8DigitalOutputOff(pdev, HIBYTE(arg), LOBYTE(arg));
		}
		APCI1500_UNLOCK(pdev,irqstate);
	}	
	return ret;
}
//------------------------------------------------------------------------------
int
do_CMD_APCI1500_Set16DigitalOutputOn(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	int ret;
	
	/* PRIVDATA is used in i_APCI1500_Set16DigitalOutputOn */
	{
		unsigned long irqstate;
		APCI1500_LOCK(pdev,&irqstate);
		{
			ret = i_APCI1500_Set16DigitalOutputOn(pdev, (uint32_t)arg);
		}
		APCI1500_UNLOCK(pdev,irqstate);
	}	
	return ret;
}
//------------------------------------------------------------------------------
int
do_CMD_APCI1500_Set16DigitalOutputOff(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	int ret;
	
	/* PRIVDATA is used in i_APCI1500_Set1DigitalOutputOn */
	{
		unsigned long irqstate;
		APCI1500_LOCK(pdev,&irqstate);
		{
			ret = i_APCI1500_Set16DigitalOutputOff(pdev, (uint32_t)arg);
		}
		APCI1500_UNLOCK(pdev,irqstate);
	}

	return ret;
}

//------------------------------------------------------------------------------
int do_CMD_APCI1500_SetOutputMemoryOff(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	int ret;
	
	/* PRIVDATA is used in i_APCI1500_SetOutputMemoryOff */
	{
		unsigned long irqstate;
		APCI1500_LOCK(pdev,&irqstate);
		{
			ret = i_APCI1500_SetOutputMemoryOff(pdev);
		}
		APCI1500_UNLOCK(pdev,irqstate);
	}

	return ret;
}




//------------------------------------------------------------------------------
int do_CMD_APCI1500_SetOutputMemoryOn(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	int ret;
	
	/* PRIVDATA is used in i_APCI1500_Set1DigitalOutputOn */
	{
		unsigned long irqstate;
		APCI1500_LOCK(pdev,&irqstate);
		{
			ret = i_APCI1500_SetOutputMemoryOn(pdev);
		}
		APCI1500_UNLOCK(pdev,irqstate);
	}

	return ret;
}
