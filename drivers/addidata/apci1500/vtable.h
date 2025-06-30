/** @file vtable.h
*
* @author Sylvain Nahas
*
* A vtable is an area of pointers to ioctl-implementing functions
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

#ifndef __APCI1500_VTABLE_H__
#define __APCI1500_VTABLE_H__

/** A vtable is an area of pointer to functions implementing the ioctl calls. 
 * The cmd are indexes from 1, the address from 0. 
 * Here we lose the field index 0 [sizeof(void*) of memory], 
 * but it avoid to decrement value during each call.
 * 
 * Type definition : allows latter use in board's private data, if needed
 * 
 * @note __APCI1500_UPPER_IOCTL_CMD must be defined in apci1500.h
 * 
 * */   
 
typedef __do_fcn* vtable_t[__APCI1500_UPPER_IOCTL_CMD+1]; 

/** number of elements in the vtable.
 * 
 * allows to be independant of any macro used in vtable's definition.
 * evaluation is one at compile time.
 * */
#define VTABLE_ELEMENT_NB(__vtable)  ( sizeof(__vtable) / (sizeof(__do_fcn*)) ) 

/** the actual vtable.
 * The actual vtable is declared in ioctl.c
 * */
extern vtable_t apci1500_vtable;

/** to be called in main.c.
 * 
 * defined in ioctl.c
 * add new ioctl handlers in the body of this function
 * */
void apci1500_init_vtable(vtable_t vtable);

/** set all entry of the vtable to apci1500_do_dummy()  */
void apci1500_dummyze_vtable(vtable_t vtable, __do_fcn * dummyfcn );

/** Affect an vtable entry.
 * 
 *  @return 0 if OK, -1 if problem */
extern int __APCI_1500_DECLARE_IOCTL_HANDLER(vtable_t vtable ,unsigned int cmd__,  __do_fcn * handler__ptr);

#endif // __VTABLE_H__
