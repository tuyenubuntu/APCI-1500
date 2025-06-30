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

#include "apci1500-private.h"

/** @file fs.c
 * 
 * This file holds the FS related functions (open,close, ioctl)
 * 
 * @note We must be especially prudent here. A special device entry has a field 
 * <b>i_rdev</b> that encodes the major and minor number.
 * 
 * The major number is used by the VFS to redirect calls to out functions, 
 * we can consider it as correct. 
 * 
 * Minor number is used to indentify the board - it is the ordinal in the OS'ses struct pci_dev list.
 * It is already possible that a file has a minor number which corresponds to 
 * a non configured card. We use the macro APCI1500_INDEX_NOT_VALID to check that.
 * 
 * 
 */

EXPORT_NO_SYMBOLS;
 
//------------------------------------------------------------------------------
/** Used for asynchronous notification.
*/
int
APCI1500_fasync(int fd, struct file *filp, int mode)
{
	return fasync_helper(fd, filp, mode, & (APCI1500_PRIVDATA(filp->private_data)->async_queue) );
}

//------------------------------------------------------------------------------

/** This function is called when the device node is opened by the system call open().
*/
int
APCI1500_open(struct inode *inode, struct file *filp)
{	
	if ( APCI1500_INDEX_NOT_VALID(&apci1500_count,MINOR(inode->i_rdev)) )
	{
		printk("%s: %d > %d index not valid\n",__DRIVER_NAME,MINOR(inode->i_rdev),atomic_read(&apci1500_count));
		return -ENODEV;
	}
	
	/* associate the FS entry with the driver structure */
	filp->private_data = apci1500_lookup_board_by_index(MINOR(inode->i_rdev) );  

	MOD_INC_USE_COUNT;
	return 0;
}

//------------------------------------------------------------------------------

/** This function is called when the device node is closed by the system call close().
*/
int
APCI1500_release(struct inode *inode, struct file *filp)
{
	if ( APCI1500_INDEX_NOT_VALID(&apci1500_count,MINOR(inode->i_rdev)) )
	{
		return -ENODEV;
	}	
	
	if ( (filp->f_flags) & FASYNC)
	{
		APCI1500_fasync(-1, filp, 0);
	}
	
	MOD_DEC_USE_COUNT;
	return 0;
}



//------------------------------------------------------------------------------
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
int
APCI1500_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
#else
long
APCI1500_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
#endif
{
	if (! filp->private_data)
	{
		printk(KERN_CRIT "%s: %s: board data should be affected but is not (did you call open() before ioctl() ?)\n", __DRIVER_NAME,__FUNCTION__);
		return -EBADFD;
	}	

	return apci1500_do_ioctl(VOID_TO_PCIDEV(filp->private_data),cmd,arg);
		

}
