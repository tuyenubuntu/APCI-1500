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

EXPORT_SYMBOL(i_APCI1500_InitTimerInputClock);

EXPORT_NO_SYMBOLS;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/** Set the clock to use for timer / counter.
 * 
 * @param [in]	arg		: 	APCI1500_115_KHZ <br> 
 * 							APCI1500_3_6_KHZ <br> 
 * 							APCI1500_1_8_KHZ
 * 
 * @retval -EINVAL		: Wrong arg.
 */
int i_APCI1500_InitTimerInputClock(struct pci_dev * pdev, unsigned long arg)
{
	DELAY();
	switch (arg) 
	{
		case APCI1500_115_KHZ:
			outw_mb(APCI1500_115_KHZ,GET_BAR2(pdev) );
			break;
		case APCI1500_3_6_KHZ:
			outw_mb(APCI1500_3_6_KHZ,GET_BAR2(pdev) );
			break;
		case APCI1500_1_8_KHZ:
			outw_mb(APCI1500_1_8_KHZ,GET_BAR2(pdev ) );
			break;
		default:
			return -EINVAL;
	}
	return 0;	
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
