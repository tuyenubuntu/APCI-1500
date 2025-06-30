 /* @file apci1500.h
  * 
  * @brief Define the public API for the apci1500 ADDI-DATA board. 
  * 
  * @author Sylvain Nahas, Julien Krauth
  *
  */

/** @par LICENCE
 * 
 *  @verbatim
  Copyright (C) 2004,2005,2006,2007,2008 ADDI-DATA GmbH for the source code of this module.
  
         ADDI-DATA GmbH
         Dieselstrasse 3
         D-77833 Ottersweier
         Tel: +19(0)7223/9493-0
         Fax: +49(0)7223/9493-92
         http://www.addi-data-com
         info@addi-data.com
 
 This library is free software; you can redistribute it and/or modify it under 
 the terms of the GNU Lesser General Public License as published by the 
 Free Software Foundation; either version 2.1 of the License, 
 or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful, 
 but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 or FITNESS FOR A PARTICULAR PURPOSE. 
 See the GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License 
 along with this library; if not, write to the Free Software Foundation, 
 Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 
 
 You also shoud find the complete LGPL in the LGPL.txt file accompanying 
 this source code.
 
 @endverbatim
**/

#ifndef __APCI1500__H_
#define __APCI1500__H_



/** @verbatim
  +-----------------------------------------------------------------------+
  | (C) ADDI-DATA GmbH          Dieselstrasse 3      D-77833 Ottersweier  |
  +-----------------------------------------------------------------------+
  | Tel : +49 (0) 7223/9493-0     | email    : info@addi-data.com         |
  | Fax : +49 (0) 7223/9493-92    | Internet : http://www.addi-data.com   |
  +-----------------------------------------------------------------------+
  | Project   : API APCI1500      | Compiler : GCC                        |
  | Modulname : APCI1500.H        | Version  : 3.3.4 (Debian 1:3.3.4-9)   |
  +-------------------------------+---------------------------------------+
  | Author    : STOLZ, Eric       | Date     : 22.08.2001                 |
  +-----------------------------------------------------------------------+
  |                   Description : APCI1500 main module                  |
  +-----------------------------------------------------------------------+
  |                             UPDATE'S                                  |
  +----------------------------------------------------------+------------+
  |   Date   |   Author  | Description of updates            | Version    |
  +----------+-----------+-----------------------------------+------------+
  | 14.12.04 | J. Krauth | - Updates about event and watchdog|            |
  +----------------------------------------------------------+------------+    
  | 10.02.05 | J. Krauth | - Updates                         |    2.01    |  
  +----------------------------------------------------------+------------+  
  | 11.05.05 | J. Nahas  | - Added card lock mgmnt macros    |            |  
  +----------------------------------------------------------+------------+
  | 09.03.16 | L. Bakali | - APCIe1500 added 			     |            |
  +----------------------------------------------------------+------------+
* @endverbatim
*/

/* Note on the behavior of the counters

For all three counters, when a counter (1,2,3) is first initialized, 
or reinitialized using a software trigger, the counter needs two (2) pulses 
on its input for the ReloadValue to be actually loaded.  
During this time slot, the value returned by reading the counter back is undefined. 

* Behavior after first initialization *
After a CounterInit(), the counter needs two pulses before the ReloadValue is 
already active. It means that effectively the actual reload value is (ReloadValue + 2) 
between the initialization and the moment the counter reach 0.  (see diagram below)

When the counter reaches 0, the ReloadValue is automatically reloaded. No further pulse is needed.

* Behavior after a Software Trigger *

After a software trigger the counter needs two pulses for the ReloadValue to be loaded.
During this phase, it behaves as if each pulse decrements the counter, 
the last pulse being immediately followed by the reload of the ReloadValue.

This means that in the case when a counter is configured with interrupts 
and its current value is 2, even when a software trigger has been performed 
an interrupt will be generated. Said otherwise, a software trigger performed 
when the counter value is 2 or 1 will have no effect. 

Please refer to the documentation of the board for more information.
*/

#include <apci.h>

//GENERAL DEFINE

#define APCI1500_BOARD_NAME                      "APCI1500" // APCIE1500

#define APCIE1500_BOARD_VENDOR_ID                 0x15B8
#define APCIE1500_BOARD_DEVICE_ID                 0x1021


#ifdef CONFIG_APCI1500_UNIVERSAL_WATCHDOG
	#define APCI1500_BOARD_VENDOR_ID                 0x15B8
	#define APCI1500_BOARD_DEVICE_ID                 0x100D
#else // !CONFIG_APCI1500_UNIVERSAL_WATCHDOG
	#define APCI1500_BOARD_VENDOR_ID                 0x10E8  // Zilog
	#define APCI1500_BOARD_DEVICE_ID                 0x80FC	 // Zilog
#endif



/* Maximum number of board managed by the driver  */
#ifndef CONFIG_APCI1500_MAX_BOARD_NBR		
#define CONFIG_APCI1500_MAX_BOARD_NBR                   (3)
#endif // APCI1500_MAX_BOARD_NBR

// for compatibility with older drivers (deprecated)
#define APCI1500_MAX_BOARD_NBR CONFIG_APCI1500_MAX_BOARD_NBR

#define APCI1500_IO_ADDRESS_RANGE                8
#define APCI1500_ZILLOG_ADDRESS_RANGE            4
#define APCI1500_INTERRUPT_ADDRESS_RANGE         0x42

#define APCI1500_DISABLE                         0
#define APCI1500_ENABLE                          1

#define APCI1500_TIMER                           0
#define APCI1500_COUNTER                         0x20
#define APCI1500_WATCHDOG                        0
#define APCI1500_SINGLE                          0
#define APCI1500_CONTINUOUS                      0x80
#define APCI1500_SOFTWARE_TRIGGER                0x4
#define APCI1500_HARDWARE_TRIGGER                0x10
#define APCI1500_SOFTWARE_GATE                   0
#define APCI1500_HARDWARE_GATE                   0x8
#define APCI1500_RETRIGGER_ENABLE				 0x4
/* internal use */
#define APCI1500_TIMERCOUNTER_ODC				 0x3

/* base frequency: 1747 Hz +/- 100 ppm */
/* note the frequency is halfed */
/* actual internal frequency: 55930Hz - tick is 17.9 microseconds */
#define APCI1500_1_8_KHZ                         2

/* base frequency: 3490 Hz +/- 100 ppm */
/* note the frequency is halfed */
/* actual internal frequency: 1745Hz - tick is 574 microseconds */
#define APCI1500_3_6_KHZ                         1

/* base frequency: 111860 Hz +/- 100 ppm */
/* note the frequency is halfed */
/* actual internal frequency: 873,5Hz - tick is 1.14 milliseconds */
#define APCI1500_115_KHZ                         0


//DIGITAL OUTPUT OFFSET DEFINE
#define APCI1500_DIGITAL_OUTPUT                  0x02 
 
// IOCTL define part
#define APCI1500_MAGIC (char) 'A'

#define CMD_APCI1500_Dummy						_IO(APCI1500_MAGIC,0)

/**
 * @param (char*) area of size CONFIG_APCI1500_MAX_BOARD_NBR+1
 * 
 * @deprecated
 * 
 */
#define CMD_APCI1500_CheckAndGetPCISlotNumber   _IOR(APCI1500_MAGIC,1,char*)

/** Initialize the board.
 * This the first function to call!
 */
#define CMD_APCI1500_SetBoardInformation        _IOW(APCI1500_MAGIC, 2,uint16_t)
/**
 * @deprecated
 */
#define CMD_APCI1500_GetHardwareInformation     _IOR(APCI1500_MAGIC,3,str_BaseInformations*)
/** 
* @param unsigned char* chan Pointer to a 8 bit value containing the number of the channel to read (1 to 16 included)
* @return (*chan) the state of the channel (0 or 1)
*
*/
#define CMD_APCI1500_Read1DigitalInput          _IOR(APCI1500_MAGIC, 4,uint8_t)
/** 
* @param unsigned char* port Pointer to a 8 bit value containing the number of the port to read (1 to 2 included)
* @return (*chan) the state of the 8 channels of the port (0 or 1)
*
*/
#define CMD_APCI1500_Read8DigitalInput          _IOR(APCI1500_MAGIC, 5,uint8_t)
/**
* @param uint16_t * A pointer to a unsigned 16 bit wide variable
* @return the values of the 16 channels
*/
#define CMD_APCI1500_Read16DigitalInput         _IOR(APCI1500_MAGIC, 6,uint32_t)
/**
* @param uint16_t * A pointer to a unsigned 16 bit wide variable
* @return the values of the 16 channels
*/
#define CMD_APCI1500_Get16DigitalOutput _IOR(APCI1500_MAGIC, 43, uint32_t)


/** specify input port 1 (used for input event functions) */
#define APCI1500_INPUT_PORT_1		 	0x1
/** specify input port 2 (used for input event functions) */
#define APCI1500_INPUT_PORT_2		 	0x2

/** define AND logic (used for input event configuration)  */
#define APCI1500_AND 				0x2
/** define OR logic (used for input event configuration)  */
#define APCI1500_OR 				0x4
/** define OR PRIORITY logic (used for input event configuration)  */
#define APCI1500_OR_PRIORITY 			0x6

/**
*

@param b_Port Port to configure ( APCI1500_INPUT_PORT_1 or APCI1500_INPUT_PORT_2) 


@param b_Logik Event logic
             Three possibilities for the first port:
             APCI1500_PORT_LOGIC_AND: This logic connects the
             input channels with an AND logic.
             APCI1500_PORT_LOGIC_OR: This logic connects the
             input channels with an OR logic.
             APCI1500_PORT_LOGIC_PRIORITY: This logic
             connects the input channels with a priority OR
             logic. Input 1 has the highest priority Input 8
             has the lowest priority


*@param pc_EventMask 
	This 8 characters string (port 1) defines the
	mask of the event. Each digit indicates the
	state of the input channel. The state is
	identified by one of the following characters:
	"X": This input channel is not used for event
	"0": The input channel must be on "0"
	"1": The input channel must be on "1"
	"2": The input channel reacts to a falling edge (one to zero transition)
	"3": The input channel reacts to a rising edge (zero to one transition)
	"4": The input channel reacts to both edges
	Port 1: from the left to the right, the first digit
	of the character string is input 8 and the last
	digit is input 1.

@return The encoded arguments or 0 when error
*/

static __inline__ long MAKE_APCI1500_INPUT_EVENT_ARG_PORT1(uint8_t b_Port, uint8_t b_Logic, char pc_EventMask[8] )
{
	uint8_t mask_pattern = 0;
	uint8_t transition_pattern = 0;
	uint8_t polarity_pattern = 0;
			
	/* parse pc_EventMask */
	{
		int i = 0;
		for ( i=0; i < 8; i++)
		{
			switch(pc_EventMask[i])
			{
				case 'X': /* channel not used */
					break;
				case '0': /* 100 */
					mask_pattern |= (  0x80 >> i );
					//transition_pattern 
					//polarity_pattern 
					break;
				case '1': /* 101 */
					mask_pattern |= (  0x80 >> i );
					//transition_pattern 
					polarity_pattern |= (  0x80 >> i );
					break;
				case '2': /* 110 */
					mask_pattern |= (  0x80 >> i );
					transition_pattern |= (  0x80 >> i );
					//polarity_pattern 
					break;
				case '3': /* 111 */
					mask_pattern |= (  0x80 >> i );					
					transition_pattern |= (  0x80 >> i );
					polarity_pattern |= (  0x80 >> i );
					break;
				case '4': /* 010 */
					//mask_pattern 
					transition_pattern |= (  0x80 >> i );
					//polarity_pattern 
					break;
				default: /* bad param */
					return 0;
			}
		}
	}
	/* encodes  */

	return MAKELONG( 
			MAKEWORD(polarity_pattern,transition_pattern), 
			MAKEWORD(mask_pattern, ( ( (b_Port-1) << 7) | b_Logic) )   
			);

}

/**

@param b_Port Port to configure ( APCI1500_INPUT_PORT_1 or APCI1500_INPUT_PORT_2) 

@param b_Logik  APCI1500_OR Only one possibility for the second port: This logic connects the input channels with a OR logic.
	
@param pc_EventMask 
	6 characters string (port 2) defines the
	mask of the event. Each digit indicates the
	state of the input channel. The state is
	identified by one of the following characters:
	"X": This input channel is not used for event
	"0": The input channel must be on "0"
	"1": The input channel must be on "1"
	"2": The input channel reacts to a falling edge
	"3": The input channel reacts to a rising edge
	"4": The input channel reacts to both edges
	Port 2: from the left to the right, the first digit
	of the character string is input 14 and the last
	digit is input 9.
	
@return The encoded arguments or 0 when error

*/

static __inline__ long MAKE_APCI1500_INPUT_EVENT_ARG_PORT2(uint8_t b_Port, uint8_t b_Logic, char pc_EventMask[6] )
{
	uint8_t mask_pattern = 0;
	uint8_t transition_pattern = 0;
	uint8_t polarity_pattern = 0;
			
	/* parse pc_EventMask */
	{
		int i = 0;
		for ( i=0; i < 6; i++)
		{
			switch(pc_EventMask[i])
			{
				case 'X': /* channel not used */
					break;
				case '0': /* 100 */
					mask_pattern |= (  0x80 >> (i+2) );
					//transition_pattern 
					//polarity_pattern 
					break;
				case '1': /* 101 */
					mask_pattern |= (  0x80 >> (i+2) );
					//transition_pattern 
					polarity_pattern |= (  0x80 >> (i+2) );
					break;
				case '2': /* 110 */
					mask_pattern |= (  0x80 >> (i+2) );
					transition_pattern |= (  0x80 >> (i+2) );
					//polarity_pattern 
					break;
				case '3': /* 111 */
					mask_pattern |= (  0x80 >> (i+2) );					
					transition_pattern |= (  0x80 >> (i+2) );
					polarity_pattern |= (  0x80 >> (i+2) );
					break;
				case '4': /* 010 */
					//mask_pattern 
					transition_pattern |= (  0x80 >> (i+2) );
					//polarity_pattern 
					break;
				default: /* bad param */
					return 0;
			}
		}
	}
	/* encodes  */

	return MAKELONG( 
			MAKEWORD(polarity_pattern,transition_pattern), 
			MAKEWORD(mask_pattern, ( ( (b_Port-1) << 7) | b_Logic) )   
			);

}

#define CMD_APCI1500_SetInputEventMask          _IOW(APCI1500_MAGIC, 7,uint32_t)
/**
* @param Flags indicating which port to start (APCI1500_INPUT_PORT_1 et/or APCI1500_INPUT_PORT_2)
* 
*/
#define CMD_APCI1500_StartInputEvent            _IOW(APCI1500_MAGIC, 8,uint8_t)
/**
* @param Flags indicating which port to stop (APCI1500_INPUT_PORT_1 et/or APCI1500_INPUT_PORT_2)
* 
*/
#define CMD_APCI1500_StopInputEvent             _IOW(APCI1500_MAGIC, 9,uint8_t)
/** 
* @param long correct value are 1 to 16 included
*
*/
#define CMD_APCI1500_Set1DigitalOutputOn        _IOW(APCI1500_MAGIC, 10,uint8_t)
/** 
* @param long correct value are 1 to 16 included
*
* @note if OutputMemory is Off this command returns an error (errno set to EINVAL)
*/
#define CMD_APCI1500_Set1DigitalOutputOff       _IOW(APCI1500_MAGIC, 11,uint8_t)

/** 
* @param MAKEWORD( port, val ) where port is 1 or 2 and 0 < val < 0xFF
*/
#define CMD_APCI1500_Set8DigitalOutputOn        _IOW(APCI1500_MAGIC, 12,uint16_t)
/** 
* @param MAKEWORD( port, val ) where port is 1 or 2 and 0 < val < 0xFF
*/
#define CMD_APCI1500_Set8DigitalOutputOff       _IOW(APCI1500_MAGIC, 13,uint16_t)
/**
*
*/
#define CMD_APCI1500_Set16DigitalOutputOn       _IOW(APCI1500_MAGIC, 14,uint32_t)

#define CMD_APCI1500_Set16DigitalOutputOff      _IOW(APCI1500_MAGIC, 15,uint32_t)
/** 
* @param NULL
*/
#define CMD_APCI1500_SetOutputMemoryOn          _IOW(APCI1500_MAGIC, 16,uint8_t)
/** 
* @param NULL
*/
#define CMD_APCI1500_SetOutputMemoryOff         _IOW(APCI1500_MAGIC, 17,uint8_t)
/**
*
*/
#define CMD_APCI1500_InitTimerInputClock        _IOW(APCI1500_MAGIC, 18,uint8_t)
/**
* @param MAKELONG( TimerMode, ReloadValue )
*/
#define CMD_APCI1500_InitTimerCounter1          _IOW(APCI1500_MAGIC, 19,uint32_t)
/**
* @param MAKELONG( TimerMode, ReloadValue )
*/
#define CMD_APCI1500_InitTimerCounter2          _IOW(APCI1500_MAGIC, 20,uint32_t)
/**
* @param MAKELONG( TimerMode, ReloadValue )
*/
#define CMD_APCI1500_InitWatchdogCounter3       _IOW(APCI1500_MAGIC, 21,uint32_t)
#define CMD_APCI1500_StartTimerCounter1         _IOW(APCI1500_MAGIC, 22,uint8_t)
#define CMD_APCI1500_StartTimerCounter2         _IOW(APCI1500_MAGIC, 23,uint8_t)

#define CMD_APCI1500_StartCounter3              _IOW(APCI1500_MAGIC, 24,uint8_t)
#define CMD_APCI1500_StopTimerCounter1          _IOW(APCI1500_MAGIC, 25,uint8_t)
#define CMD_APCI1500_StopTimerCounter2          _IOW(APCI1500_MAGIC, 26,uint8_t)
#define CMD_APCI1500_StopCounter3               _IOW(APCI1500_MAGIC, 27,uint8_t)
#define CMD_APCI1500_TriggerTimerCounter1       _IOW(APCI1500_MAGIC, 28,uint8_t)
#define CMD_APCI1500_TriggerTimerCounter2       _IOW(APCI1500_MAGIC, 29,uint8_t)
#define CMD_APCI1500_TriggerCounter3            _IOW(APCI1500_MAGIC, 30,uint8_t)
#define CMD_APCI1500_TriggerWatchdog            _IOW(APCI1500_MAGIC, 31,uint8_t)
/** read the current value of the watchdog/counter 1
 * 
 * @param (unsigned long*)
 * 
 */
#define CMD_APCI1500_ReadTimerCounter1          _IOR(APCI1500_MAGIC, 32,unsigned long*)
/** read the current value of the watchdog/counter 2
 * 
 * @param (unsigned long*)
 * 
 */
#define CMD_APCI1500_ReadTimerCounter2          _IOR(APCI1500_MAGIC, 33,unsigned long*)

/** read the current value of watchdog/counter 3
 * 
 * @param (unsigned long*)
 * 
 */
#define CMD_APCI1500_ReadCounter3               _IOR(APCI1500_MAGIC, 34,unsigned long*)

/*
 * no argument
 */
#define CMD_APCI1500_SetBoardIntRoutine         _IO(APCI1500_MAGIC, 35)

/*
 * no argument
 */
#define CMD_APCI1500_ResetBoardIntRoutine       _IO(APCI1500_MAGIC, 36)

#define CMD_APCI1500_WaitInterrupt             _IOR(APCI1500_MAGIC, 39, unsigned long*)

/** Enable / disable interrupt of counter / timer 1.
 * 
 * @param [in]	arg	APCI1500_ENABLE or APCI1500_DISABLE.
 * 
 * @retval	-EINVAL	Interrupt not initialized or arg is not<br>
 * 					APCI1500_ENABLE or APCI1500_DISABLE.
 */ 	  
#define CMD_APCI1500_EnableDisableTimerCounter1Interrupt	_IOW(APCI1500_MAGIC, 40,uint8_t)

/** Enable / disable interrupt of counter / timer 2.
 * 
 * @param [in]	arg	APCI1500_ENABLE or APCI1500_DISABLE.
 * 
 * @retval	-EINVAL	Interrupt not initialized or arg is not<br>
 * 					APCI1500_ENABLE or APCI1500_DISABLE.
 */
#define CMD_APCI1500_EnableDisableTimerCounter2Interrupt	_IOW(APCI1500_MAGIC, 41,uint8_t)

/** Enable / disable interrupt of counter / watchdog 3.
 * 
 * @param [in]	arg	APCI1500_ENABLE or APCI1500_DISABLE.
 * 
 * @retval	-EINVAL	Interrupt not initialized or arg is not<br>
 * 					APCI1500_ENABLE or APCI1500_DISABLE.
 */
#define CMD_APCI1500_EnableDisableWatchdogCounter3Interrupt	_IOW(APCI1500_MAGIC, 42,uint8_t)

enum {APCI1500_WATCHDOG_STATE_OVERFLOWED=0x1 /** watchdog is in overflowed state */
	, APCI1500_WATCHDOG_STATE_ENABLED=0x2 /** enable bit is set  */
	};
	
/*
 * @param (unsigned long*) Watchdog Status 0, APCI1500_WATCHDOG_STATE_OVERFLOWED, 
 * APCI1500_WATCHDOG_STATE_ENABLED
 * 
 * @note This command is available only for WATCHDOG UNIVERSAL
 * 
 * APCI1500_WATCHDOG_STATE_ENABLED means watchdog waits for a trigger OR is
 * already running
 * 
 */
#define CMD_APCI1500_GetWatchdogStatus       _IOR(APCI1500_MAGIC, 37,long*)

/*
 * @param (unsigned long*) ReloadValue (16 bits significant)
 * 
 * @note This command is available only for WATCHDOG UNIVERSAL
 * 
 */
#define CMD_APCI1500_GetWatchdogReloadValue   _IOR(APCI1500_MAGIC, 38,long*)

/** value of the biggest ioctl number */
#define __APCI1500_UPPER_IOCTL_CMD 44

#endif //__APCI1500__H_#
