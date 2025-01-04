
#include "define.h" /* this include file stores typedef that can be easily used */

 
short int __stdcall i_PCI1500_GetNumberOfBoards (PBYTE	pb_NbrOfBoards );

short int __stdcall i_PCI1500_GetBoardInformation(BYTE		b_BoardIndex,
									DWORD		dw_IdentifierStringSize,
									PCHAR		pc_Identifier,
									PDWORD		pdw_UINumber,
									PDWORD		pdw_DeviceNumber,
									PDWORD		pdw_BusNumber,
									PDWORD		pdw_BaseAddress0,
									PDWORD		pdw_BaseAddress1,
									PDWORD		pdw_BaseAddress2,
									PBYTE		pb_Interrupt );

short int __stdcall i_PCI1500_OpenBoardViaIndex (BYTE	b_BoardIndex,  unsigned long int *DeviceHandle);

short int __stdcall i_PCI1500_OpenBoardViaIdentifier (PCHAR	pc_Identifier, unsigned long int *DeviceHandle);

short int __stdcall i_PCI1500_CloseBoard (unsigned long int	h_DeviceHandle );

short int __stdcall i_PCI1500_GetDLLVersion (PDWORD	pdw_Version);

short int __stdcall i_PCI1500_GetDeviceDriverVersion(unsigned long int h_DeviceHandle, PDWORD pdw_Version);

short int __stdcall i_PCI1500_SetBoardIntRoutine (unsigned long int	h_DeviceHandle,
									void  cdecl  (* v_FunctionName )(unsigned long int	h_DeviceHandle,
																BYTE	b_FIFOOverflow,
																BYTE	b_InterruptMask,
																WORD	w_InputValues ));

short int __stdcall i_PCI1500_ResetBoardIntRoutine (unsigned long int	h_DeviceHandle );

short int __stdcall i_PCI1500_Read1DigitalInput (unsigned long int h_DeviceHandle,
								   BYTE b_Channel,
								   PBYTE pb_Value );

short int __stdcall i_PCI1500_Read8DigitalInputs (unsigned long int	h_DeviceHandle,
									BYTE	b_Port,
									PBYTE	pb_Value );

short int __stdcall  i_PCI1500_Read16DigitalInputs (unsigned long int	h_DeviceHandle,
									 PWORD	pw_Value );

short int __stdcall  i_PCI1500_Get16DigitalOutputsStatus  (unsigned long int	deviceHandle,
											PWORD	status);

short int __stdcall  i_PCI1500_SetDigitalOutputMemoryOn (unsigned long int h_DeviceHandle );

short int __stdcall  i_PCI1500_SetDigitalOutputMemoryOff (unsigned long int h_DeviceHandle );

short int __stdcall  i_PCI1500_Set1DigitalOutputOn (unsigned long int	h_DeviceHandle,
									 BYTE	b_Channel );

short int __stdcall  i_PCI1500_Set1DigitalOutputOff (unsigned long int	h_DeviceHandle,
									  BYTE		b_Channel );

short int __stdcall  i_PCI1500_Set8DigitalOutputsOn (unsigned long int	h_DeviceHandle,
									  BYTE		b_Port,
									  BYTE		b_Mask );

short int __stdcall  i_PCI1500_Set8DigitalOutputsOff (unsigned long int	h_DeviceHandle,
									   BYTE		b_Port,
									   BYTE		b_Mask );

short int __stdcall  i_PCI1500_Set16DigitalOutputsOn (unsigned long int h_DeviceHandle,
									   WORD w_Mask );

short int __stdcall  i_PCI1500_Set16DigitalOutputsOff (unsigned long int h_DeviceHandle,
										WORD w_Mask );

short int __stdcall  i_PCI1500_InitEventLogic (unsigned long int	h_DeviceHandle,
								BYTE	b_PortNbr,
								BYTE	b_EventLogic,
								PCHAR	pc_EventMask );

short int __stdcall  i_PCI1500_StartEventLogic (unsigned long int h_DeviceHandle,
								 BYTE b_PortNbr );

short int __stdcall  i_PCI1500_StopEventLogic (unsigned long int h_DeviceHandle,
								BYTE b_PortNbr );

short int __stdcall  i_PCI1500_InitTimerInputClock(unsigned long int h_DeviceHandle,
									BYTE b_InputClockSelected);

short int __stdcall  i_PCI1500_InitTimerCounter1(unsigned long int h_DeviceHandle,
								  BYTE	b_ComponentMode,
								  WORD	w_ReloadValue,
								  BYTE	b_EnableContinuousCycle,
								  BYTE	b_EnableInterrupt);
	
short int __stdcall  i_PCI1500_StartTimerCounter1(unsigned long int h_DeviceHandle);

short int __stdcall  i_PCI1500_StopTimerCounter1(unsigned long int h_DeviceHandle);

short int __stdcall  i_PCI1500_TriggerTimerCounter1(unsigned long int h_DeviceHandle );

short int __stdcall  i_PCI1500_ReadTimerCounter1(unsigned long int h_DeviceHandle,
								  PWORD pw_TimerValue );

short int __stdcall i_PCI1500_InitTimerCounter2(unsigned long int	h_DeviceHandle,
									BYTE	b_ComponentMode,
									WORD	w_ReloadValue,
									BYTE	b_EnableContinuousCycle,
									BYTE	b_EnableHardwareTrigger,
									BYTE	b_EnableHardwareGate,
									BYTE	b_EnableInterrupt);

short int __stdcall  i_PCI1500_StartTimerCounter2(unsigned long int h_DeviceHandle);

short int __stdcall  i_PCI1500_StopTimerCounter2(unsigned long int h_DeviceHandle);

short int __stdcall  i_PCI1500_TriggerTimerCounter2(unsigned long int h_DeviceHandle );

short int __stdcall  i_PCI1500_ReadTimerCounter2(unsigned long int h_DeviceHandle,
								  PWORD pw_TimerValue );

short int __stdcall  i_PCI1500_InitWatchdogCounter3 (unsigned long int	h_DeviceHandle,
									  BYTE	b_ComponentMode,
									  WORD	w_ReloadValue,
									  BYTE	b_EnableContinuousCycle,
									  BYTE	b_EnableHardwareGate,
									  BYTE	b_EnableInterrupt);

short int __stdcall  i_PCI1500_StartWatchdogCounter3(unsigned long int h_DeviceHandle);

short int __stdcall  i_PCI1500_StopWatchdogCounter3(unsigned long int h_DeviceHandle);

short int __stdcall  i_PCI1500_TriggerWatchdogCounter3(unsigned long int h_DeviceHandle );

short int __stdcall  i_PCI1500_ReadWatchdogCounter3(unsigned long int h_DeviceHandle,
									 PWORD pw_TimerValue );
