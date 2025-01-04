using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace PCI1500_NET
{
    /// <summary>
    /// Contains the call to the DLL functions
    /// </summary>
    public class DllImport
    {
        /// <summary>
        /// Definition of the function that must be given to use the interruption of the board
        /// </summary>
        /// <param name="handle"></param>
        /// <param name="fifoOverflow"></param>
        /// <param name="mask"></param>
        /// <param name="values"></param>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void InterruptFunctionEventHandler(IntPtr  handle,
                                                            byte   fifoOverflow,
                                                            byte   mask,
                                                            ushort values);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_GetNumberOfBoards(ref byte nbBoard);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_GetBoardInformation(Byte       index,
	                                                             UInt32  	identifierStringSize,
	                                                             Byte[]     identifier,
	                                                             out UInt32 uiNumber,
                                                                 out UInt32 deviceNumber,
                                                                 out UInt32 busNumber,
                                                                 out UInt32 baseAddress0,
                                                                 out UInt32 baseAddress1,
                                                                 out UInt32 baseAddress2,
                                                                 out Byte   interrupt);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_OpenBoardViaIndex(byte index, ref IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_CloseBoard(IntPtr deviceHandle);

        #region "InformationVersion"

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_SetSerialNumber(IntPtr deviceHandle, UInt32 serialNumber);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_GetSerialNumber(IntPtr deviceHandle, out UInt32 serialNumber);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_GetFirmwareVersion(IntPtr deviceHandle, out UInt32 firmwareVersion);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_GetDeviceDriverVersion(IntPtr deviceHandle, out UInt32 version);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_GetDLLVersion(out UInt32 version);

        #endregion

        #region "Interrupt"

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_SetBoardIntRoutine(IntPtr deviceHandle, [MarshalAs(UnmanagedType.FunctionPtr)] InterruptFunctionEventHandler interruptFunction);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_ResetBoardIntRoutine(IntPtr deviceHandle);

        #endregion

        #region "Digital inputs"

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Read1DigitalInput(IntPtr deviceHandle,byte channel, ref byte value);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Read8DigitalInputs(IntPtr deviceHandle, byte port, ref byte value);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Read16DigitalInputs(IntPtr deviceHandle, ref ushort value);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Get16DigitalOutputsStatus(IntPtr deviceHandle, ref ushort value);

        #endregion

        #region "Digital outputs"

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_SetDigitalOutputMemoryOn(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_SetDigitalOutputMemoryOff(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Set1DigitalOutputOn(IntPtr deviceHandle, byte channel);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Set1DigitalOutputOff(IntPtr deviceHandle, byte channel);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Set8DigitalOutputsOn(IntPtr deviceHandle, byte port, byte mask);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Set8DigitalOutputsOff(IntPtr deviceHandle, byte port, byte mask);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Set16DigitalOutputsOn(IntPtr deviceHandle, ushort mask);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_Set16DigitalOutputsOff(IntPtr deviceHandle, ushort mask);

        #endregion

        #region "Event logic"

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_InitEventLogic(IntPtr deviceHandle, byte port, byte eventLogic, string mask);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_StartEventLogic(IntPtr deviceHandle, byte port);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_StopEventLogic(IntPtr deviceHandle, byte port);

        #endregion

        #region "Clock"

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_InitTimerInputClock(IntPtr deviceHandle, byte clock);

        #endregion

        #region "Counter Timer 1"

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_InitTimerCounter1(IntPtr deviceHandle, byte mode, ushort reloadValue, byte enableContinuousCycle, byte enableInterrupt );

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_StartTimerCounter1(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_StopTimerCounter1(IntPtr deviceHandle);
        
        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_TriggerTimerCounter1(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_ReadTimerCounter1(IntPtr deviceHandle, ref ushort value);

        #endregion

        #region "Counter Timer 2"

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_InitTimerCounter2(IntPtr deviceHandle, byte mode, ushort reloadValue, byte enableContinuousCycle, byte enablehardwareTrigger, byte enableHardwareGate, byte enableInterrupt);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_StartTimerCounter2(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_StopTimerCounter2(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_TriggerTimerCounter2(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_ReadTimerCounter2(IntPtr deviceHandle, ref ushort value);

        #endregion

        #region "Counter Timer 3"

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_InitWatchdogCounter3(IntPtr deviceHandle, byte mode, ushort reloadValue, byte enableContinuousCycle, byte enableHardwareGate, byte enableInterrupt);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_StartWatchdogCounter3(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_StopWatchdogCounter3(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_TriggerWatchdogCounter3(IntPtr deviceHandle);

        [DllImport("PCI1500.dll")]
        public static extern short i_PCI1500_ReadWatchdogCounter3(IntPtr deviceHandle, ref ushort value);

        #endregion
    }
}
