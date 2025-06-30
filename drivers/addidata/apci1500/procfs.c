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


#include "apci1500-private.h"
#include "apci1500-proc.h"

EXPORT_NO_SYMBOLS;

// Disable proc
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
static struct proc_dir_entry * apci1500_proc_root = NULL;
static char * __PROC_ROOT_NAME = "sys/apci1500";
#endif

#define APCI1500_PROC_FREE_DATA 0x01
#define APCI1500_PROC_IS_ROOT 0x02

#define APCI1500_PROC_IS_NODE_NO_FREE (0x0)
#define APCI1500_PROC_IS_ROOT_NO_FREE (APCI1500_PROC_IS_ROOT)
#define APCI1500_PROC_IS_NODE_AND_FREE (APCI1500_PROC_FREE_DATA)
#define APCI1500_PROC_IS_ROOT_AND_FREE (APCI1500_PROC_IS_ROOT | APCI1500_PROC_FREE_DATA)

/* APCI1500_PROC_IS_ROOT means the node is the top of the hierarchy and node on the same level won't be deleted
* APCI1500_PROC_FREE_DATA means data associated to the nodes that are deleted must be kfree'd first
*/

//----------------------------------------------------------------------------------------------------------------------

// Disable proc
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)

/** Recursively delete a /proc tree whom top entry is given as parameter.
 * 
 * Release previously allocated ressources and delete entries in /proc.
 * This function implement a simple a go-left-first, go-down-then recursive 
 * algorithm through the given proc entry.
 * If APCI1500_PROC_FREE_DATA is set in flag, the function frees the driver data associated to proc entry 
 * If APCI1500_PROC_IS_ROOT is set in flag, the node at the same level are not gone though.
 * 
 * @arg[in] item A pointer to the proc entry to remove
 * @arg[in] top A flag specifying how to behave
 * 
 * @return void (The function silently fails)
 */

static void proc_release_under(struct proc_dir_entry * item, unsigned int flag)
{
                
        if (!item) return;
                
        // next first
        if ( (! (flag & APCI1500_PROC_IS_ROOT) ) && item->next)
                proc_release_under(item->next, flag & (~APCI1500_PROC_IS_ROOT) );

        // sub dir then
        if (item->subdir)
                proc_release_under(item->subdir, flag & (~APCI1500_PROC_IS_ROOT));
                
        // release data
        if ( (item->data) && ( flag & APCI1500_PROC_FREE_DATA ) )
        {
                kfree(item->data);
                item->data = NULL;
        }
        // release proc item itself
        remove_proc_entry(item->name,item->parent);
        
}

//----------------------------------------------------------------------------------------------------------------------
/** Search an entry by its name in the sub-directory. 
* 
* @param top Pointer to the top entry of the hierarchy.
* @param name String used to identify the node. 
*
* @returns The address of the node or NULL if not found
*
*/
static struct proc_dir_entry * proc_find_entry_by_name(struct proc_dir_entry * top, const char * name)
{
        struct proc_dir_entry * tmp = NULL;     

        if (!top) return NULL;
        if (!name) return NULL;
                                
        tmp=top->subdir;
        
        while(tmp)
        {
                if ( strcmp(tmp->name,name) == 0 ) /* same name, we found it*/
                        return tmp;
                tmp = tmp->next;
        }
        
        /* arrived here, found nothing */
        return NULL;
}

#endif // #if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)

#ifdef CONFIG_APCI_PROC_FS_SIMPLE

#error "Sorry, CONFIG_APCI_PROC_FS_SIMPLE option is deprecated and shouldn't be used!"

//----------------------------------------------------------------------------------------------------------------------
/** Create a simple "device" entry in the /proc/apci1500/ root directory. 
 * 
 * @param dev Pointer to the device entry to be associated to the node.
 * @param major_number The minor number to be associated to this device.
 * 
 */
void apci1500_proc_create_device(struct pci_dev * dev, unsigned int minor_number)
{
	struct proc_dir_entry * entry = NULL;

	if (!apci1500_proc_root) return ;
	// apci1500_proc_create_device is available only for 2.4
	#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
	{
		entry = proc_mknod(	pci_name(dev), 
			S_IFCHR | 0666,
			apci1500_proc_root, 
			MKDEV(apci1500_majornumber, minor_number));
	}
	#else // 2.6 : special device are no more available :( - create a normal proc entry
	{
		entry = create_proc_entry("ctl",0,NULL,NULL);		
	}		
	#endif 
	
	if (!entry) 
	{
		printk(KERN_WARNING "%s: can't create proc entry for board %s(ENOMEM)\n",__DRIVER_NAME,pci_name(dev));
		return;
	}
			
	#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30)
		entry->owner = THIS_MODULE;
	#endif
	entry->data = dev;

	return;
}

#else //CONFIG_APCI_PROC_FS_SIMPLE

//----------------------------------------------------------------------------------------------------------------------
/** Create a directory in the /proc/apci1500/ root directory named after the board slot. 
 *
 * @param dev Pointer to the device entry to be associated to the node.
 * @param major_number The minor number to be associated to this device.
 * 
 */
void apci1500_proc_create_device(struct pci_dev * dev, unsigned int minor_number)
{
// Disable proc
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	return;
#else

	struct proc_dir_entry * entry = NULL;

	if (!apci1500_proc_root) return ;

	/* create the board directory */
	{	
		entry = proc_mkdir(	pci_name(dev), apci1500_proc_root);
	
		if (!entry) 
		{
			printk("%s: can't create proc entry for board %s(ENOMEM)\n",__DRIVER_NAME,pci_name(dev));
			return;
		}
				
		#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30)
			entry->owner = THIS_MODULE;
		#endif
		entry->data = dev;
	}
	/* create a control special device file */
	{	
		#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
		{			
			entry = proc_mknod(	"ctrl", 
					S_IFCHR | 0666,
					entry, 
					MKDEV(apci1500_majornumber, minor_number));
					
			entry->owner = THIS_MODULE;
			entry->data = dev;	// TODO: remove ?
		}
		#else // 2.6 : special device are no more available :( - create a normal proc entry
		{	
			 /* 
			  * Devices files are not allowed under /proc with kernel > 2.6. 
			  * So a link on a device node is set.
			  * mkdevs.sh or udev script can be used to set the 
			  * /dev/apci1500/minor_number file.
			  */						
			char path[100];						
			sprintf(path, "/dev/apci1500/%i", minor_number);
			entry = proc_symlink("ctrl",entry,path);
			#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30)
				entry->owner = THIS_MODULE;
			#endif
			 					
		}		
		#endif
		
		if (!entry) 
		{
			printk(KERN_WARNING "%s: can't create proc entry for board %s(ENOMEM)\n",__DRIVER_NAME,pci_name(dev));
			return;
		}				
	}
	return;	
#endif
}


#endif //CONFIG_APCI_PROC_FS_SIMPLE


//----------------------------------------------------------------------------------------------------------------------
/** Remove a "device" entry in the /proc/apci1500/ root directory. 
 * 
 * The function search for a device named after the pci_name(pdev)
 * This function silently fails.
 */
void apci1500_proc_release_device(struct pci_dev * pdev)
{
// Disable proc
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	return;
#else

	struct proc_dir_entry * entry = NULL;

	entry = proc_find_entry_by_name(apci1500_proc_root, pci_name(pdev));
	if (!entry) return;

	proc_release_under(entry,APCI1500_PROC_IS_ROOT_NO_FREE);
	
	return;
#endif
}

//------------------------------------------------------------------------------
/** Create the main root directory /proc/apciXXXX.
 * 
 * @return 0 if OK, non zero if failed
 *
 * If the function fails to create the entry, it outputs a warning message in system logs 
 */
int apci1500_proc_init(void)
{
// Disable proc
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	return 0;
#else

    apci1500_proc_root = proc_mkdir(__PROC_ROOT_NAME, NULL );
        
	if (!apci1500_proc_root) 
	{
		printk(KERN_WARNING "%s: can't create /proc/%s\n", __DRIVER_NAME,__PROC_ROOT_NAME);
		return 1;
	}
	
	#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30)
		apci1500_proc_root->owner = THIS_MODULE;
	#endif
	apci1500_proc_root->data = NULL;

	return 0;

#endif
}

//------------------------------------------------------------------------------
/** Delete the entry /proc/apciXXXX and all of its childs.
 * 
 * @return 
 * */
void apci1500_proc_release(void)
{	
// Disable proc
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
	return;
#else
	proc_release_under(apci1500_proc_root,APCI1500_PROC_IS_ROOT_NO_FREE);
#endif
}
