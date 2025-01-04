// Here goes prototypes declaration and documentation

#include <windows.h>
#include "define.h" /* this include file stores typedef that can be easily used */

#ifdef __cplusplus
	extern "C" {
#endif

/**
 * \defgroup General xPCI-1500 general functions
 * @{
 */

/**  Enables to get the number of xPCI-1500 boards present in the system. \n
 * The function fill the value pointed by pb_NbrOfBoards with the number of boards present.
 *                                                                            
 * @param[out] pb_NbrOfBoards Value that will be filled with the number of boards     
 * @return	0 : No error \n
 *		   -1 : Error while getting the number of boards \n
 */
_INT_ i_PCI1500_GetNumberOfBoards (PBYTE	pb_NbrOfBoards );


/** Get device information of the board.
 *                                                                   
 * @param[in] b_BoardIndex : Index of the board
 * @param[in] dw_IdentifierStringSize : size of the identifier parameter 
 * @param[out] pc_Identifier: Identifier of the board
 * @param[out] pdw_UINumber : This number is typically a user-perceived slot number, such as a number printed next to the slot on the board, or some other number that makes locating the physical device easier for the user. If the device is on a bus that has no UI number convention, or if the bus driver for the device cannot determine the UI number, this value is 0xFFFFFFFF.
 * @param[out] pdw_DeviceNumber : Device number.
 * @param[out] pdw_BusNumber : Bus number.
 * @param[out] pdw_BaseAddress0 : Base address 0 of the board
 * @param[out] pdw_BaseAddress1 : Base address 1 of the board
 * @param[out] pdw_BaseAddress2 : Base address 2 of the board
 * @param[out] pb_Interrupt : Interrupt line of the board
 * @return	 0 : No error \n
 *			-1 : Unable to open the board via index \n
 *			-2 : Error when calling driver's IOCTL \n
 */
_INT_ i_PCI1500_GetBoardInformation(BYTE		b_BoardIndex,
									DWORD		dw_IdentifierStringSize,
									PCHAR		pc_Identifier,
									PDWORD		pdw_UINumber,
									PDWORD		pdw_DeviceNumber,
									PDWORD		pdw_BusNumber,
									PDWORD		pdw_BaseAddress0,
									PDWORD		pdw_BaseAddress1,
									PDWORD		pdw_BaseAddress2,
									PBYTE		pb_Interrupt );

/*Function's Name   : i_PCI1500_ClearInterruptFIFO*/
/** Clear the Interrupt fifo
 *                                                                   
 * @param[in] h_DeviceHandle  : Handle of the board
 * @return	 0 : No error \n
 *			-1 : Error when calling driver's IOCTL \n
 */
INT i_PCI1500_ClearInterruptFIFO(HANDLE h_DeviceHandle);

/*Function's Name   : i_PCI1500_GetSerialNumber*/
/** Return the serial number of the board.
*                                                                   
* @param[in] h_DeviceHandle  : Handle of the board                
* @param[out] pdw_SerialNumber  : Serial number of the board in decimal
* @retval 0 : No Error \n
* @retval -1 : timeout \n
* @retval -100 : Error while calling IOCTL function \n
*/
_INT_ i_PCI1500_GetSerialNumber(HANDLE h_DeviceHandle, DWORD *pdw_SerialNumber);

/*Function's Name   : i_PCI1500_GetFirmwareVersion*/
/** Return the firmware version of the board.
*                                                                   
* @param[in] h_DeviceHandle  : Handle of the board                
* @param[out] pdw_FirmwareVersion  : Firmware Version of the Board  Contains the 4 ASCII codes of the configuration
 *               \li bits 0 -> 7   ASCII code (version low)
 *               \li bits 8 -> 15  ASCII code (version high)
 *               \li bits 16 -> 23 ASCII code (functionality name second digit)
 *               \li bits 24 -> 31 ASCII code (functionality name first digit)
 *				 \li to read them select one of the four bits and print it using a char printf("%c", )
* @retval 0 : No Error \n
* @retval -1 : timeout \n
* @retval -100 : Error while calling IOCTL function \n
*/
_INT_ i_PCI1500_GetFirmwareVersion (HANDLE h_DeviceHandle, PDWORD pdw_FirmwareVersion);

/*Function's Name   : i_PCI1500_SetSerialNumber*/
/** Set the serial number of the board.
*                                                                   
* @param[in] h_DeviceHandle  : Handle of the board                
* @param[in] dw_SerialNumber : Serial number of the board in decimal
* @retval 0 : No Error \n
* @retval -1 : timeout \n
* @retval -100 : Error while calling IOCTL function \n
*/
_INT_ i_PCI1500_SetSerialNumber(HANDLE h_DeviceHandle, DWORD dw_SerialNumber);

/** Open the board with the index : b_BoardIndex. A handle is returned to the \n    
 * user which allows to use the driver functions. \n 
 *                                                                                  
 * @param[in] b_BoardIndex : Index of the board to open                             
 * @param[out] ph_DeviceHandle : Handle of the selected xPCI-1500 board for using the functions
 * @return		0 : No error \n
 *             -1 : Unable to get the number of available boards \n                                    
 *             -2 : Wrong device index parameter. The parameter is too high \n
 *             -3 : Error while getting the device's class \n
 *             -4 : Error while getting informations about the device \n
 *             -5 : Memory allocation error \n
 *             -6 : Get device interface detail error \n
 *             -7 : Error while creating communication handle \n
 *			   -8 : Error in the initialization callback function \n
 */
_INT_ i_PCI1500_OpenBoardViaIndex (BYTE	b_BoardIndex,
								   PHANDLE	ph_DeviceHandle );  


/** Open the board with the indentifier : pc_Identifier. A handle is returned to the \n    
 * user which allows to use the following functions. \n                                                         
 *                                                                                  
 * @param[in] pc_Identifier : Identifier of the board to open
 * @param[out] ph_DeviceHandle : Handle of the board xPCI-1500 for using the functions
 * @return	 0 : No Error \n
			-1 : Unable to get the number of available boards \n  
			-2 : Unable to get the board identifier \n
			-3 : Unable to open the board \n
			-4 : Identifier not found \n
 */
_INT_ i_PCI1500_OpenBoardViaIdentifier (PCHAR	pc_Identifier,
										PHANDLE	ph_DeviceHandle );


/** Release the handle of the board. Block the access to the board.
 *                                                                   
 * @param[in] h_DeviceHandle    : Handle of the board                
 * @return	 0 : No Error \n
 *			-1 : The device handle parameter is wrong \n
 */
_INT_ i_PCI1500_CloseBoard (HANDLE	h_DeviceHandle );


/** Return the version of the DLL.
 *                                                                   
 * @param[out] pdw_Version  : Version. sample : 0x01010910 -> version 1.01 september 2010       
 * @return	0 : No Error \n
 */
_INT_ i_PCI1500_GetDLLVersion (PDWORD	pdw_Version);

/*Function's Name   : i_PCI1500_GetDeviceDriverVersion*/
/** Return the version of the device driver.
*                                                                   
* @param[in] h_DeviceHandle  : Handle of the board                
* @param[out] pdw_Version  : Version. sample : 0x01011211 -> version 1.01 - 12/2011
* @return    0 : No Error \n                                                     
*             -1 : Error while calling IOCTL function \n
*/
_INT_ i_PCI1500_GetDeviceDriverVersion(HANDLE h_DeviceHandle, PDWORD pdw_Version);


/**
 * @}
 * \defgroup Interrupt xPCI-1500 interrupt management functions
 * @{
 */

/** Install an interrupt callback function.
 * This function will be called each time the board generate an interruption. \n
 * The value of b_InterruptMask will enable you to determine the source of the interruption:
 *
 * @param[in] h_DeviceHandle    : Handle of the board                
 * @param[in] v_FunctionName    : Address of the callback function
 *		\n	\b h_DeviceHandle	: Handle of the board
 *		\n	\b b_FIFOOverflow	: If uc_FIFOOverflow != 0, there are too many untreated interrupts in the kernel FIFO, and any new information is lost
 *		\n	\b dw_InterruptMask	: Source of the interrupt
 *		\n	\b w_InputValues	: Values of the input
 *
 * The source of the interrupt can be:
 * \li 0x1: Port A interrupt
 * \li 0x2: Port B interrupt
 * \li 0x4: Timer 1 interrupt
 * \li 0x8: Timer 2 interrupt
 * \li 0x10: Timer 3 interrupt
 * \li 0x20: Watchdog interrupt
 * \li 0x40: Low voltage detected
 * \li 0x80: Short circuit detected
 *
 * @return	 0 : No Error \n
 *			-1 : The device handle parameter is wrong \n
 *			-2 : An interrupt routine was still isntalled. Remove it with i_PCI1500_ResetBoardIntRoutine and retry \n
 *			-3 : Error while creating kill event \n
 *			-4 : Error while creating interrupt event \n
 *			-5 : Error while creating interrupt thread \n
 *			-6 : Error while changing the priority class of the thread \n
 *			-7 : Error while changing the priority of the thread \n
 *			-8 : Error while calling the IOCTL command \n
 *			-9 : Error in the interrupt callback function \n
 */
_INT_ i_PCI1500_SetBoardIntRoutine (HANDLE	h_DeviceHandle,
									void	(*v_FunctionName)(	HANDLE	h_DeviceHandle,
																BYTE	b_FIFOOverflow,
																BYTE	b_InterruptMask,
																WORD	w_InputValues )
);
		
/** Deinstall the interrupt callback function.
 *
 * @param[in] h_DeviceHandle    : Handle of the board                
 * @return	 0 : No Error \n
 *			-1 : The device handle parameter is wrong \n
 *			-2 : No interrupt routine installed \n
 *			-3 : Error in the reset interrupt callback function \n
 */
_INT_ i_PCI1500_ResetBoardIntRoutine (HANDLE	h_DeviceHandle );


/** 
 * @}
 * \defgroup DigIO xPCI-1500 digital input/output functions
 * \addtogroup DigInp Digital inputs
 * \ingroup DigIO
 * @{
 */

/** Read 1 digital inputs of the board xPCI-1500
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_Channel The index of the channel to read (0 to 15)
 * @param[out] pb_Value Status of the digital input
 *
 * @return	 0 : No Error \n
 *			-1 : The channel index is wrong \n
 *			-2 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_Read1DigitalInput (HANDLE h_DeviceHandle,
								   BYTE b_Channel,
								   PBYTE pb_Value );


/** Read 8 digital inputs of the board xPCI-1500
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_Port Port to read ( \b PCI1500_PORT_0 : channels 0-7, \b PCI1500_PORT_1 : channels 8-15)
 * @param[out] pb_Value Status of the digital inputs
 *
 * @return	 0 : No Error \n
 *			-1 : The port index is wrong \n
 *			-2 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_Read8DigitalInputs (HANDLE	h_DeviceHandle,
									BYTE	b_Port,
									PBYTE	pb_Value );


/** Read 16 digital inputs of the board xPCI-1500
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[out] pw_Value Status of the digital inputs
 *
 * @return	 0 : No Error \n
 *			-1 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_Read16DigitalInputs (HANDLE	h_DeviceHandle,
									 PWORD	pw_Value );


_INT_ i_PCI1500_Get16DigitalOutputsStatus  (HANDLE	deviceHandle,
											PWORD	status);


/**
 * @} 
 * \addtogroup DigOutMemory Digital output memory
 * \ingroup DigIO
 * @{
 */

/** Activate the digital output memory of the board xPCI-1500
 * When using the digital output memory, when setting the value of one digital output, the value of the other digital output is kept.
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_SetDigitalOutputMemoryOn (HANDLE h_DeviceHandle );


/** Deactivate the digital output memory of the board xPCI-1500
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_SetDigitalOutputMemoryOff (HANDLE h_DeviceHandle );

/**
 * @} 
 * \addtogroup DigOut Digital outputs
 * \ingroup DigIO
 * @{
 */
	
/** Permits to set a digital output of the board xPCI-1500 to ON (high state)
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_Channel Digital output channel to set (0 to 15)
 *
 * @return	 0 : No Error \n
 *			-1 : The value of the channel index is wrong \n
 *			-2 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_Set1DigitalOutputOn (HANDLE	h_DeviceHandle,
									 BYTE	b_Channel );


/** Permits to reset a digital output of the board xPCI-1500 \n
 * Digital output memory must be enabled
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_Channel Digital output channel to reset (0 to 15)
 *
 * @return	 0 : No Error \n
 *			-1 : The value of the channel index is wrong \n
 *			-2 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_Set1DigitalOutputOff (HANDLE	h_DeviceHandle,
									  BYTE		b_Channel );


/** Sets a digital output port (8 bits) of the board xPCI-1500 to 1 (high state)
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_Port Port to set ( \b PCI1500_PORT_0 : channels 0-7, \b PCI1500_PORT_1 : channels 8-15)
 * @param[in] b_Mask Mask of channels to set on the port ( 0x0 to 0xFF)
 *
 * @return	 0 : No Error \n
 *			-1 : The value of the port index is wrong \n
 *			-2 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_Set8DigitalOutputsOn (HANDLE	h_DeviceHandle,
									  BYTE		b_Port,
									  BYTE		b_Mask );


/** Resets a digital output port (8 bits) of the board xPCI-1500 \n
 * Digital output memory must be enabled
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_Port Port to set ( \b PCI1500_PORT_0 : channels 0-7, \b PCI1500_PORT_1 : channels 8-15)
 * @param[in] b_Mask Mask of channels to reset on the port ( 0x0 to 0xFF)
 *
 * @return	 0 : No Error \n
 *			-1 : The value of the port index is wrong \n
 *			-2 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_Set8DigitalOutputsOff (HANDLE	h_DeviceHandle,
									   BYTE		b_Port,
									   BYTE		b_Mask );


/** Sets several digital outputs of the board xPCI-1500
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] w_Mask Digital output mask value to set (0x0 to 0xFFFF)
 *
 * @return	 0 : No Error \n
 *			-1 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_Set16DigitalOutputsOn (HANDLE h_DeviceHandle,
									   WORD w_Mask );


/** Resets several digital outputs of the board xPCI-1500 \n
* Digital output memory must be enabled
*
* @param[in] h_DeviceHandle Handle of the board
* @param[in] w_Mask Digital output mask value to reset (0x0 to 0xFFFF)
*
 * @return	 0 : No Error \n
 *			-1 : Error while calling IOCTL function (wrong handle ?) \n
*/
_INT_ i_PCI1500_Set16DigitalOutputsOff (HANDLE h_DeviceHandle,
										WORD w_Mask );

/**
 * @}
 * \defgroup Event xPCI-1500 event logic functions
 * @{
 */

/** Permits to initialize the event logic of the board xPCI-1500 \n
 * The event logic enables you to receive interrupt when a certain state is reached by the board. \n
 * You can also use this function to receive interruption when a short-circuit occurs, or when there is no more supply voltage. \n
 * To detect short-circuit and lost of supply voltage, use the event of port 1. If you do not want to listen to the input of port 1, just give the event mask "xxxxxx".
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_PortNbr Port number to initialize ( \b PCI1500_PORT_0 : channels 0-7 or \b PCI1500_PORT_1 : channels 8-13)
 * @param[in] b_EventLogic Event logic mode. Values are \b PCI1500_LOGIC_AND or \b PCI1500_LOGIC_OR. Port 1 only supports OR logic.
 * @param[in] pc_EventMask An 8-character string for port 0, or 6-character string for port 1, to set the mask of the event. \n
 *	Each character gives the state of the input channels and can have one of the following values :
 *	\li "X" or "x" : This input is not used for event
 *	\li "0" : This input must be low
 *	\li "1" : This input must be high
 *	\li "2" : This input reacts to a falling edge
 *	\li "3" : This input reacts to a rising edge
 *	\li "4" : This input reacts to both edges
 *	\n
 *	Port 0 : from the left to the right, the first digit of the character string is input 7 and the last digit is input 0. \n
 *	Port 1 : from the left to the right, the first digit of the character string is input 13 and the last digit is input 8. \n
 *	\b IMPORTANT : If you use the AND logic, only one input can use the edge event.
 *
 * @return	  0 : No Error \n
 *			 -1 : wrong device handle \n
 *			 -2 : The port number parameter is wrong \n
 *			 -3 : The event logic parameter is wrong \n
 *			 -4 : AND logic is not available on port 1 \n
 *			 -5 : Event logic is NULL \n
 *			 -6 : The length of the string is invalid \n
 *			 -7 : Unrecognized character in the string \n
 *			 -8 : It is not possible to have more than one edge with AND logic \n
 *			 -9 : The interrupt routine is not installed \n
 *			-10 : Error while calling IOCTL function (wrong handle ?) \n
*/
_INT_ i_PCI1500_InitEventLogic (HANDLE	h_DeviceHandle,
								BYTE	b_PortNbr,
								BYTE	b_EventLogic,
								PCHAR	pc_EventMask );


/** Starts the event logic of the board xPCI-1500 \n
* You  must call the function i_PCI1500_InitEventLogic before calling this function
*
* @param[in] h_DeviceHandle Handle of the board
* @param[in] b_PortNbr Port number ( \b PCI1500_PORT_0 : channels 0-7 or \b PCI1500_PORT_1 : channels 8-13)
*
* @return	 0 : No Error \n
*			-1 : wrong device handle \n
 *			-2 : The port number parameter is wrong \n
 *			-3 : The interrupt routine is not installed \n
 *			-4 : Error while calling IOCTL function (wrong handle ?) \n
*/
_INT_ i_PCI1500_StartEventLogic (HANDLE h_DeviceHandle,
								 BYTE b_PortNbr );

	
/** Stops the event logic of the board xPCI-1500
*
* @param[in] h_DeviceHandle Handle of the board
* @param[in] b_PortNbr Port number ( \b PCI1500_PORT_0 : channels 0-7 or \b PCI1500_PORT_1 : channels 8-13)
*
* @return	 0 : No Error \n
*			-1 : wrong device handle \n
 *			-2 : The port number parameter is wrong \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
*/
_INT_ i_PCI1500_StopEventLogic (HANDLE h_DeviceHandle,
								BYTE b_PortNbr );


/**
 * @}
 * \defgroup Timer xPCI-1500 timer/counter/watchdog functions
 * @{
 */

 /** Initializes the input clock used for timers and watchdog
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_InputClockSelected Clock selection 
 *	\li \b PCI1500_115_KHZ => 115,2kHz
 *	\li \b PCI1500_3_6_KHZ => 3,6kHz
 *	\li \b PCI1500_1_8_KHZ => 1,8kHz
 * @return	 0 : No Error \n
 *			-1 : The selected clock index is wrong \n
 *			-2 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_InitTimerInputClock(HANDLE h_DeviceHandle,
									BYTE b_InputClockSelected);

/**
 * @}
 * \addtogroup Timer1 Timer Counter 1
 * \ingroup Timer
 * @{
 */
 
/** Initializes the component 1 as a timer or a counter \n
 *	\b Important! The timer component internally operates with half of the input frequency \n
 *	If the timer is set as a timer, the time period is defined by (2*w_ReloadValue)/InputClock, where InputClock is the value of the input clock in Hz \n \n
 *	If the counter is used, input 14 acts as the counter input
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_ComponentMode Selects the component mode ( \b PCI1500_TIMER or \b PCI1500_COUNTER )
 * @param[in] w_ReloadValue Defines the starting value of the timer, and maximum value of the counter
 * @param[in] b_EnableContinuousCycle Reset the timer to us_ReloadValue after each interrupt, and continue counting (0,1)
 * @param[in] b_EnableInterrupt An interrupt is generated each time the timer or counter expires (0,1)
 *
 * @return	 0 : No Error \n
 *			-1 : Invalid mode \n
 *			-2 : Wrong device handle \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_InitTimerCounter1(HANDLE h_DeviceHandle,
								  BYTE	b_ComponentMode,
								  WORD	w_ReloadValue,
								  BYTE	b_EnableContinuousCycle,
								  BYTE	b_EnableInterrupt);

	
/** Starts the counter timer 1 as a timer or a counter (depending on how you initialized it)
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : The component is still started, stop it before trying to restart it \n
 *			-3 : The component is not initialized \n
 *			-4 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_StartTimerCounter1(HANDLE h_DeviceHandle);

/** Stops the counter timer 1
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : Nothing is started on the component (so nothing to stop) \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_StopTimerCounter1(HANDLE h_DeviceHandle);

	
/** Triggers the counter timer 1, resetting its value
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : Nothing is started on the component (so nothing to trigger) \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_TriggerTimerCounter1(HANDLE h_DeviceHandle );

	
/** Reads the timer 1 current value
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[out] pw_TimerValue Current value of the counter timer
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : Nothing is started on the component (so nothing to read) \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_ReadTimerCounter1(HANDLE h_DeviceHandle,
								  PWORD pw_TimerValue );

/**
 * @} 
 * \addtogroup Timer2 Timer Counter 2
 * \ingroup Timer
 * @{
 */
 
 /** Initializes the component 2 as a timer or a counter. \n
 *	\b Important! The timer component internally operates with half of the input frequency. \n
 *	If the timer is set as a timer, the time period is defined by (2*w_ReloadValue)/InputClock, where InputClock is the value of the input clock in Hz. \n \n
 *	This timer/counter supports hardware trigger, i.e. the value is reloaded if the trigger input is high. \n
 *	This timer/counter also supports hardware gate, i.e. the timer is only counting if the gate input is high. \n \n
 *	If the counter is used, input 10 acts as the counter input \n
 *	If the hardware trigger is enabled, input 11 acts as the trigger input \n
 *	If the hardware gate is enabled, input 12 acts as the gate input \n
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_ComponentMode Selects the component mode ( \b PCI1500_TIMER or \b PCI1500_COUNTER )
 * @param[in] w_ReloadValue Defines the starting value of the timer
 * @param[in] b_EnableContinuousCycle Reset the timer to us_ReloadValue after each interrupt, and continue counting (0,1)
 * @param[in] b_EnableHardwareTrigger Enable the hardware trigger on pin 11 (0,1)
 * @param[in] b_EnableHardwareGate Enable the hardware gate on pin 12 (0,1)
 * @param[in] b_EnableInterrupt An interrupt is generated each time the timer or counter expires (0,1)
 *
 * @return	 0 : No Error \n
 *			-1 : Invalid mode \n
 *			-2 : Wrong device handle \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_	i_PCI1500_InitTimerCounter2(HANDLE	h_DeviceHandle,
									BYTE	b_ComponentMode,
									WORD	w_ReloadValue,
									BYTE	b_EnableContinuousCycle,
									BYTE	b_EnableHardwareTrigger,
									BYTE	b_EnableHardwareGate,
									BYTE	b_EnableInterrupt);

	
/** Starts the counter timer 2 as a timer or a counter (depending on how you initialized it)
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : The component is still started, stop it before trying to restart it \n
 *			-3 : The component is not initialized \n
 *			-4 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_StartTimerCounter2(HANDLE h_DeviceHandle);

	
/** Stops the counter timer 2
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : Nothing is started on the component (so nothing to stop) \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_StopTimerCounter2(HANDLE h_DeviceHandle);


/** Triggers the counter timer 2, resetting its value
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : Nothing is started on the component (so nothing to trigger) \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_TriggerTimerCounter2(HANDLE h_DeviceHandle );

	
/** Reads the timer 2 current value
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[out] pw_TimerValue Current value of the counter timer
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : Nothing is started on the component (so nothing to read) \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_ReadTimerCounter2(HANDLE h_DeviceHandle,
								  PWORD pw_TimerValue );

/**
 * @} 
 * \addtogroup Timer3 Watchdog Counter 3
 * \ingroup Timer
 * @{
 */
 
 /** Initializes the component 3 as a watchdog or a counter. \n
 *	\b Important! The WatchdogCounter component internally operates with half of the input frequency. \n
 *	If the WatchdogCounter is set as a watchdog, the time period is defined by (2*w_ReloadValue)/InputClock, where InputClock is the value of the input clock in Hz. \n \n
 *	This WatchdogCounter, when configured as a counter supports hardware gate. When hardware gate is enabled, then the counter is only counting if the gate input is high. \n \n
 *	If the counter is used, input 15 acts as the counter input \n
 *	If the hardware gate is enabled, input 16 acts as the gate input \n
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[in] b_ComponentMode Selects the component mode ( \b PCI1500_WATCHDOG or \b PCI1500_COUNTER )
 * @param[in] w_ReloadValue Defines the starting value of the WatchdogCounter
 * @param[in] b_EnableContinuousCycle Reset the WatchdogCounter to us_ReloadValue after each interrupt, and continue counting (0 disable, 1 enable)
 * @param[in] b_EnableHardwareGate Enable the hardware gate on pin 27 input 16 (0 disable, 1 enable)
 * @param[in] b_EnableInterrupt An interrupt is generated each time the watchdog or the counter expires (0 disable, 1 enable)
 *
 * @return	 0 : No Error \n
 *			-1 : Invalid mode \n
 *			-2 : Wrong device handle \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_InitWatchdogCounter3 (HANDLE	h_DeviceHandle,
									  BYTE	b_ComponentMode,
									  WORD	w_ReloadValue,
									  BYTE	b_EnableContinuousCycle,
									  BYTE	b_EnableHardwareGate,
									  BYTE	b_EnableInterrupt);

	
/** Starts the watchdog counter 3 as a watchdog or a counter (depending on how you initialized it)
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : The component is still started, stop it before trying to restart it \n
 *			-3 : The component is not initialized \n
 *			-4 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_StartWatchdogCounter3(HANDLE h_DeviceHandle);

	
/** Stops the watchdog counter 3
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : Nothing is started on the component (so nothing to stop) \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_StopWatchdogCounter3(HANDLE h_DeviceHandle);


/** Triggers the watchdog counter 3, resetting its value
 *
 * @param[in] h_DeviceHandle Handle of the board
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : Nothing is started on the component (so nothing to trigger) \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_TriggerWatchdogCounter3(HANDLE h_DeviceHandle );

	
/** Reads the watchdog counter 3 current value
 *
 * @param[in] h_DeviceHandle Handle of the board
 * @param[out] pw_TimerValue Current value of the watchdog counter
 *
 * @return	 0 : No Error \n
 *			-1 : Wrong device handle \n
 *			-2 : Nothing is started on the component (so nothing to read) \n
 *			-3 : Error while calling IOCTL function (wrong handle ?) \n
 */
_INT_ i_PCI1500_ReadWatchdogCounter3(HANDLE h_DeviceHandle,
									 PWORD pw_TimerValue );


/**
 * @}
 */

#ifdef __cplusplus
	}
#endif


