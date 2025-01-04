// Here goes constant declarations

#ifndef __PCI1500_H
#define __PCI1500_H

/** \defgroup Constants xPCI-1500 constants */


/** 
 * @}
 * \addtogroup GeneralConstants xPCI-1500 general constants
 * \ingroup Constants
 * @{
 *	Can be used for flags such as \b uc_EnableInterrupt, or every flag that has value 0 as "Disabled", and any other value as "Enabled"
 */
 
 /** Constant value always set to 0 */
 #define PCI1500_DISABLED	0x0
 
 /** Constant value always set != 0 */
 #define PCI1500_ENABLED	0x1
/**
 * @}
 * \addtogroup TimerModes xPCI-1500 timer modes
 * \ingroup Constants
 * @{
 *	Values used in the InitTimer functions
 */
 
/** For internal use only */
#define PCI1500_UNDEFINED	0x00

/** Timer is used as a timer */
#define	PCI1500_TIMER		0x01

/** Timer is used as a counter */
#define	PCI1500_COUNTER		0x02

/** Timer is used as a watchdog */
#define	PCI1500_WATCHDOG	0x03

/** 
 * @}
 * \addtogroup Ports xPCI-1500 ports
 * \ingroup Constants
 * @{
 *	Used for initializing port logic and setting or getting digital inputs/outputs
 */
 
/** Use port 0 (channels 0 to 7) */
#define PCI1500_PORT_0		0x0

/** Use port 1 (channels 8 to 15) */
#define PCI1500_PORT_1		0x1

/** 
 * @}
 * \addtogroup Logics xPCI-1500 event logics
 * \ingroup Constants
 * @{
 *	Used for initializing port logic
 */
 
/** Use the OR logic */
#define PCI1500_LOGIC_OR	0x0

/** Use the AND logic */
#define PCI1500_LOGIC_AND	0x1

/** 
 * @}
 * \addtogroup Clocks xPCI-1500 input clocks
 * \ingroup Constants
 * @{
 *	Selects the input clock for the timers
 */

/** Selects 115,2kHz input clock  */
#define	PCI1500_115_KHZ	0x10

/** Selects 3,6kHz input clock */
#define	PCI1500_3_6_KHZ	0x11

/** Selects 1,8kHz input clock */
#define	PCI1500_1_8_KHZ	0x12

/** 
 * @}
 */
 
// Internal use only
#define TIMER_1		0x0
#define TIMER_2		0x1
#define TIMER_3		0x2

#endif