UNIT PCI1500;

INTERFACE

TYPE
	EVENT_STRING = ARRAY [0..8] OF AnsiCHAR;
	PPointer = ^Pointer;

CONST

		
// xPCI-1500 constants 


  //	Can be used for flags such as \b uc_EnableInterrupt, or every flag that has value 0 as "Disabled", and any other value as "Enabled"
  PCI1500_DISABLED	: BYTE = 0;
  PCI1500_ENABLED		: BYTE = 1;

  //	Values used in the InitTimer functions

  // Timer is used as a timer
  PCI1500_TIMER		: BYTE = 1;
  // Timer is used as a counter
  PCI1500_COUNTER		: BYTE  = 2;
  // Timer is used as a watchdog
  PCI1500_WATCHDOG	: BYTE = 3;

  //	Used for initializing port logic and setting or getting digital inputs/outputs
  // Use port 0 (channels 0 to 7)
  PCI1500_PORT_0		: BYTE = 0;
  // Use port 1 (channels 8 to 15)
  PCI1500_PORT_1		: BYTE = 1;

  //	Used for initializing port logic
  // Use the OR logic
  PCI1500_LOGIC_OR	: BYTE = 0;
  // Use the AND logic
  PCI1500_LOGIC_AND	: BYTE  = 1;

  //	Selects the input clock for the timers
  // Selects 115,2kHz input clock
  PCI1500_115_KHZ	 : BYTE = $10;
  // Selects 3,6kHz input clock
  PCI1500_3_6_KHZ	 : BYTE = $11;
  // Selects 1,8kHz input clock
  PCI1500_1_8_KHZ	: BYTE = $12;


 

FUNCTION   i_PCI1500_GetNumberOfBoards (var pb_NbrOfBoards : Byte ): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_GetBoardInformation	(b_BoardIndex : Byte;
											dw_IdentifierStringSize : LongWord;
											pc_Identifier : PAnsiChar;
											var	pdw_UINumber : LongWord;
											var pdw_DeviceNumber : LongWord;
											var pdw_BusNumber : LongWord;
											var	pdw_BaseAddress0 : LongWord;
											var	pdw_BaseAddress1 : LongWord;
											var pdw_BaseAddress2 : LongWord;
											var pb_Interrupt : Byte ): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_OpenBoardViaIndex	(b_BoardIndex : Byte;
								        var ph_DeviceHandle : THANDLE): Int16;FAR;STDCALL;
								   
								   
FUNCTION   i_PCI1500_OpenBoardViaIdentifier	(pc_Identifier : PCHAR;
											var	ph_DeviceHandle : THANDLE ): Int16;FAR;STDCALL;
								   

FUNCTION   i_PCI1500_CloseBoard (h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_GetDLLVersion (var pdw_Version : LongWord): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_GetDeviceDriverVersion(h_DeviceHandle : THANDLE; var pdw_Version : LongWord): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_SetBoardIntRoutine	(h_DeviceHandle : THANDLE;
									    v_FunctionName       : Pointer): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_ResetBoardIntRoutine (h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;



FUNCTION   i_PCI1500_Read1DigitalInput (h_DeviceHandle : THANDLE;
								        b_Channel : Byte;
								        var pb_Value : Byte): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_Read8DigitalInputs (h_DeviceHandle : THANDLE;
									     b_Port : Byte;
									     var pb_Value : Byte): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_Read16DigitalInputs (h_DeviceHandle : THANDLE;
									      var pw_Value : UInt16): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_SetDigitalOutputMemoryOn (h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_SetDigitalOutputMemoryOff (h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_Set1DigitalOutputOn (h_DeviceHandle : THANDLE;
									      b_Channel : Byte): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_Set1DigitalOutputOff (h_DeviceHandle : THANDLE;
									       b_Channel : Byte): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_Set8DigitalOutputsOn (h_DeviceHandle : THANDLE;
									       b_Port : Byte;
									       b_Mask : Byte): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_Set8DigitalOutputsOff (h_DeviceHandle : THANDLE;
									        b_Port : Byte;
											b_Mask : Byte): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_Set16DigitalOutputsOn (h_DeviceHandle : THANDLE; w_Mask : UInt16): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_Set16DigitalOutputsOff (h_DeviceHandle : THANDLE; w_Mask : UInt16): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_InitEventLogic	(h_DeviceHandle : THANDLE;
									b_PortNbr : Byte;
									b_EventLogic : Byte;
									pc_EventMask : EVENT_STRING): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_StartEventLogic(h_DeviceHandle : THANDLE;
									b_PortNbr  : Byte): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_StopEventLogic (h_DeviceHandle : THANDLE;
									 b_PortNbr : Byte ): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_InitTimerInputClock(h_DeviceHandle : THANDLE;
										b_InputClockSelected : Byte): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_InitTimerCounter1(h_DeviceHandle : THANDLE;
									   b_ComponentMode : Byte;
									   w_ReloadValue : UInt16;
									   b_EnableContinuousCycle : Byte;
									   b_EnableInterrupt : Byte): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_StartTimerCounter1(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_StopTimerCounter1(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_TriggerTimerCounter1(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_ReadTimerCounter1(h_DeviceHandle : THANDLE; var pw_TimerValue : UInt16 ): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_InitTimerCounter2	(h_DeviceHandle : THANDLE;
										b_ComponentMode : BYTE;
										w_ReloadValue : UInt16;
										b_EnableContinuousCycle : BYTE;
										b_EnableHardwareTrigger : BYTE;
										b_EnableHardwareGate : BYTE;
										b_EnableInterrupt : BYTE): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_StartTimerCounter2(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_StopTimerCounter2(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_TriggerTimerCounter2(h_DeviceHandle : THANDLE ): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_ReadTimerCounter2(h_DeviceHandle : THANDLE;
									   var pw_TimerValue : UInt16 ): Int16;FAR;STDCALL;

FUNCTION   i_PCI1500_InitWatchdogCounter3	(h_DeviceHandle : THANDLE;
											b_ComponentMode : BYTE;
											w_ReloadValue : UInt16;
											b_EnableContinuousCycle : BYTE;
											b_EnableHardwareGate : BYTE;
											b_EnableInterrupt : BYTE): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_StartWatchdogCounter3(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_StopWatchdogCounter3(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;


FUNCTION   i_PCI1500_TriggerWatchdogCounter3(h_DeviceHandle : THANDLE ): Int16;FAR;STDCALL;

	
FUNCTION   i_PCI1500_ReadWatchdogCounter3(h_DeviceHandle : THANDLE;
										  var pw_TimerValue  : UInt16): Int16;FAR;STDCALL;






IMPLEMENTATION

FUNCTION   i_PCI1500_GetNumberOfBoards (var pb_NbrOfBoards : Byte ): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_GetBoardInformation	(b_BoardIndex : Byte;
											dw_IdentifierStringSize : LongWord;
											pc_Identifier : PAnsiChar;
											var	pdw_UINumber : LongWord;
											var pdw_DeviceNumber : LongWord;
											var pdw_BusNumber : LongWord;
											var	pdw_BaseAddress0 : LongWord;
											var	pdw_BaseAddress1 : LongWord;
											var pdw_BaseAddress2 : LongWord;
											var pb_Interrupt : Byte ): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_OpenBoardViaIndex	(b_BoardIndex : Byte;
								        var ph_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';
								   
								   
FUNCTION   i_PCI1500_OpenBoardViaIdentifier	(pc_Identifier : PCHAR;
											var	ph_DeviceHandle : THANDLE ): Int16;FAR;STDCALL;External 'PCI1500.DLL';
								   

FUNCTION   i_PCI1500_CloseBoard (h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_GetDLLVersion (var pdw_Version : LongWord): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_GetDeviceDriverVersion(h_DeviceHandle : THANDLE; var pdw_Version : LongWord): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_SetBoardIntRoutine	(h_DeviceHandle : THANDLE;
									    v_FunctionName       : Pointer): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_ResetBoardIntRoutine (h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';



FUNCTION   i_PCI1500_Read1DigitalInput (h_DeviceHandle : THANDLE;
								        b_Channel : Byte;
								        var pb_Value : Byte): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_Read8DigitalInputs (h_DeviceHandle : THANDLE;
									     b_Port : Byte;
									     var pb_Value : Byte): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_Read16DigitalInputs (h_DeviceHandle : THANDLE;
									      var pw_Value : UInt16 ): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_SetDigitalOutputMemoryOn (h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_SetDigitalOutputMemoryOff (h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_Set1DigitalOutputOn (h_DeviceHandle : THANDLE;
									      b_Channel : Byte): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_Set1DigitalOutputOff (h_DeviceHandle : THANDLE;
									       b_Channel : Byte): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_Set8DigitalOutputsOn (h_DeviceHandle : THANDLE;
									       b_Port : Byte;
									       b_Mask : Byte): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_Set8DigitalOutputsOff (h_DeviceHandle : THANDLE;
									        b_Port : Byte;
											b_Mask : Byte): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_Set16DigitalOutputsOn (h_DeviceHandle : THANDLE; w_Mask : UInt16): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_Set16DigitalOutputsOff (h_DeviceHandle : THANDLE; w_Mask : UInt16): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_InitEventLogic	(h_DeviceHandle : THANDLE;
									b_PortNbr : Byte;
									b_EventLogic : Byte;
									pc_EventMask : EVENT_STRING): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_StartEventLogic(h_DeviceHandle : THANDLE;
									b_PortNbr  : Byte): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_StopEventLogic (h_DeviceHandle : THANDLE;
									 b_PortNbr : Byte ): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_InitTimerInputClock(h_DeviceHandle : THANDLE;
										b_InputClockSelected : Byte): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_InitTimerCounter1(h_DeviceHandle : THANDLE;
									   b_ComponentMode : Byte;
									   w_ReloadValue : UInt16;
									   b_EnableContinuousCycle : Byte;
									   b_EnableInterrupt : Byte): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_StartTimerCounter1(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_StopTimerCounter1(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_TriggerTimerCounter1(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_ReadTimerCounter1(h_DeviceHandle : THANDLE; var pw_TimerValue : UInt16 ): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_InitTimerCounter2	(h_DeviceHandle : THANDLE;
										b_ComponentMode : BYTE;
										w_ReloadValue : UInt16;
										b_EnableContinuousCycle : BYTE;
										b_EnableHardwareTrigger : BYTE;
										b_EnableHardwareGate : BYTE;
										b_EnableInterrupt : BYTE): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_StartTimerCounter2(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_StopTimerCounter2(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_TriggerTimerCounter2(h_DeviceHandle : THANDLE ): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_ReadTimerCounter2(h_DeviceHandle : THANDLE;
									   var pw_TimerValue : UInt16 ): Int16;FAR;STDCALL;External 'PCI1500.DLL';

FUNCTION   i_PCI1500_InitWatchdogCounter3	(h_DeviceHandle : THANDLE;
											b_ComponentMode : BYTE;
											w_ReloadValue : UInt16;
											b_EnableContinuousCycle : BYTE;
											b_EnableHardwareGate : BYTE;
											b_EnableInterrupt : BYTE): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_StartWatchdogCounter3(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_StopWatchdogCounter3(h_DeviceHandle : THANDLE): Int16;FAR;STDCALL;External 'PCI1500.DLL';


FUNCTION   i_PCI1500_TriggerWatchdogCounter3(h_DeviceHandle : THANDLE ): Int16;FAR;STDCALL;External 'PCI1500.DLL';

	
FUNCTION   i_PCI1500_ReadWatchdogCounter3(h_DeviceHandle : THANDLE;
										  var pw_TimerValue  : UInt16): Int16;FAR;STDCALL;External 'PCI1500.DLL';



END.
