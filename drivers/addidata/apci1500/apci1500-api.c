/** @file apci1500-api.c
*
* @author Sylvain Nahas
*
* 
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

#include <linux/module.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,12,0)
	#include <asm/uaccess.h>
#else
	#include <linux/uaccess.h>
#endif
#include <asm/io.h>

#include <linux/pci.h>
#include "apci1500-private.h"

EXPORT_NO_SYMBOLS;

//-------------------------------------------------------------------
/** Previously used to initialize the Zilog.
 * 
 * This function is now deprectade.
 * The Zilog initialization is done 
 * in apci1500_probe_one one a board
 * is detected.
 */
int
do_CMD_APCI1500_SetBoardInformation(struct pci_dev* pdev, unsigned int cmd, unsigned long arg)
{
	return (0);
}
//------------------------------------------------------------------------------
int do_CMD_APCI1500_InitTimerInputClock(struct pci_dev * pdev, unsigned int cmd, unsigned long arg)
{
	/* no need to lock - PRIVDATA not used in i_APCI1500_InitTimerInputClock */
	return (i_APCI1500_InitTimerInputClock(pdev, arg));	
}

