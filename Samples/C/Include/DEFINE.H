 /** @file DEFINE.H
 * Define list 
 * 
 * 
 *  @author C. Guinot
 *  @date 13.07.2009
 *  
 *  
 *  @par LICENCE
 *  @verbatim
 *  Copyright (C) 2009  ADDI-DATA GmbH for the source code of this module.
 *       
*  ADDI-DATA GmbH
*  Airpark Business Center
*  Airport Boulevard B210
*  77836 Rheinmünster
*  Germany
*  Tel: +49(0)7229/1847-0
*  Fax: +49(0)7229/1847-200
*  http://www.addi-data-com
*  info@addi-data.com   
 *       
 * @endverbatim   
 */

#ifndef __COMPILER__

   /*********************************************************/
   /* DEFINE the type for the compilation of user's program */
   /*********************************************************/

   /* define the type for the intern variable of a function */
   #define	 CHAR	   char
   #define	 BYTE	   unsigned char
   //#define	 INT	   short int
   #define	 WORD	   unsigned short int
   #define	 LONG	   long
   #define	 DWORD	   unsigned long
   #define	 VOID	   void

   #define	 PCHAR	   CHAR *
   #define	 PBYTE	   BYTE *
   #define	 PINT	   INT *
   #define	 PWORD	   WORD *
   #define	 PLONG	   LONG *
   #define	 PDWORD	   DWORD *
   #define	 PVOID	   VOID *
   #define  QWORD      unsigned __int64

   /* define the type for the parameter of the function */
   #define	 CHAR_	   CHAR
   #define	 BYTE_	   BYTE
   #define	 INT_	   INT
   #define	 WORD_	   WORD  
   #define	 LONG_	   LONG
   #define	 DWORD_	   DWORD
   #define	 VOID_	   VOID

   #define	 PCHAR_	   PCHAR
   #define	 PBYTE_	   PBYTE
   #define	 PINT_	   PINT
   #define	 PWORD_	   PWORD
   #define	 PLONG_	   PLONG
   #define	 PDWORD_   PDWORD	  
   #define	 PVOID_	   PVOID

   /* define the type for the return of the function */
   #ifdef _BORLANDC_
      #ifdef __cplusplus
         #define	 _CHAR_	   extern "C" _import CHAR far _stdcall
         #define	 _BYTE_	   extern "C" _import BYTE far _stdcall
         #define	 _INT_	   extern "C" _import INT far _stdcall
         #define	 _WORD_	   extern "C" _import WORD far _stdcall
         #define	 _LONG_	   extern "C" _import LONG far _stdcall
         #define	 _DWORD_   extern "C" _import DWORD far _stdcall	  
         #define	 _VOID_	   extern "C" _import VOID far _stdcall

         #define	 _PCHAR_   extern "C" _import PCHAR far _stdcall	  
         #define	 _PBYTE_   extern "C" _import PBYTE far _stdcall	  
         #define	 _PINT_	   extern "C" _import PINT far _stdcall
         #define	 _PWORD_   extern "C" _import PWORD far _stdcall	  
         #define	 _PLONG_   extern "C" _import PLONG far _stdcall	  
         #define	 _PDWORD_  extern "C" _import PDWORD far _stdcall	  
         #define	 _PVOID_   extern "C" _import PVOID far _stdcall	  
      #else
         #define	 _CHAR_	   _import CHAR far _stdcall
         #define	 _BYTE_	   _import BYTE far _stdcall
         #define	 _INT_	   _import INT far _stdcall
         #define	 _WORD_	   _import WORD far _stdcall
         #define	 _LONG_	   _import LONG far _stdcall
         #define	 _DWORD_   _import DWORD far _stdcall	  
         #define	 _VOID_	   _import VOID far _stdcall

         #define	 _PCHAR_   _import PCHAR far _stdcall	  
         #define	 _PBYTE_   _import PBYTE far _stdcall	  
         #define	 _PINT_	   _import PINT far _stdcall
         #define	 _PWORD_   _import PWORD far _stdcall	  
         #define	 _PLONG_   _import PLONG far _stdcall	  
         #define	 _PDWORD_  _import PDWORD far _stdcall	  
         #define	 _PVOID_   _import PVOID far _stdcall	  
      #endif
   #else
      #ifdef __cplusplus
         #define	 _CHAR_	   CHAR far _stdcall
         #define	 _BYTE_	   BYTE far _stdcall
         #define	 _INT_	   INT far _stdcall 
         #define	 _WORD_	   WORD far _stdcall
         #define	 _LONG_	   LONG far _stdcall
         #define	 _DWORD_   DWORD far _stdcall	  
         #define	 _VOID_	   far _stdcall

         #define	 _PCHAR_   PCHAR far _stdcall	  
         #define	 _PBYTE_   PBYTE far _stdcall	  
         #define	 _PINT_	   PINT far _stdcall
         #define	 _PWORD_   PWORD far _stdcall	  
         #define	 _PLONG_   PLONG far _stdcall	  
         #define	 _PDWORD_  PDWORD far _stdcall	  
         #define	 _PVOID_   PVOID far _stdcall	  
      #else
         #define	 _CHAR_	   CHAR far _stdcall
         #define	 _BYTE_	   BYTE far _stdcall
         #define	 _INT_	   INT far _stdcall
         #define	 _WORD_	   WORD far _stdcall
         #define	 _LONG_	   LONG far _stdcall
         #define	 _DWORD_   DWORD far _stdcall	  
         #define	 _VOID_	   VOID far _stdcall

         #define	 _PCHAR_   PCHAR far _stdcall	  
         #define	 _PBYTE_   PBYTE far _stdcall	  
         #define	 _PINT_	   PINT far _stdcall
         #define	 _PWORD_   PWORD far _stdcall	  
         #define	 _PLONG_   PLONG far _stdcall	  
         #define	 _PDWORD_  PDWORD far _stdcall	  
         #define	 _PVOID_   PVOID far _stdcall	  

      #endif
   #endif


#endif



