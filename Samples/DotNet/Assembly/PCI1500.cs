using System;
using System.Collections.Generic;
using System.Text;

namespace PCI1500_NET
{
    public class PCI1500
    {
        /// <summary>
        /// Some constants definition
        /// </summary>
        public const int TIMER_MODE = 1;
        public const int COUNTER_MODE = 2;
        public const int WATCHDOG_MODE = 3;
        public const int KHZ_115 = 0x10;
        public const int KHZ_3_6 = 0x11;
        public const int KHZ_1_8 = 0x12;

        /// <summary>
        /// Store the index of the board
        /// </summary>
        private int index;

        /// <summary>
        /// Store an handle to the board. Will be used for interrupt routine for example
        /// </summary>
        private IntPtr handle;

        /// <summary>
        /// Handler to the interrupt function of the board
        /// The function pointed by this delegate will be called each time the board interrupts
        /// </summary>
        private DllImport.InterruptFunctionEventHandler interruptFunctionHandler;

        /// <summary>
        /// An object that will contains the diagnostic event args
        /// Created only once, because the new command takes a lot of resources
        /// </summary>
        private DiagnosticEventArgs diagnosticEventArgs;

        /// <summary>
        /// An object that will contains the counter timer watchdog event args
        /// Created only once, because the new command takes a lot of resources
        /// </summary>
        private CounterTimerWatchdogEventArgs counterTimerWatchdogEventArgs;

        /// <summary>
        /// An object that will contains the event logic event args
        /// Created only once, because the new command takes a lot of resources
        /// </summary>
        private EventLogicEventArgs eventLogicEventArgs;

        /// <summary>
        /// Delegate to provide to listen to the diagnostic changes
        /// </summary>
        /// <param name="source"></param>
        /// <param name="args"></param>
        public delegate void DiagnosticEventHandler(object source, DiagnosticEventArgs args);

        /// <summary>
        /// Delegate to provide to listen to the diagnostic changes
        /// </summary>
        /// <param name="source"></param>
        /// <param name="args"></param>
        public delegate void CounterTimerWatchdogEventHandler(object source, CounterTimerWatchdogEventArgs args);

        /// <summary>
        /// Delegate to provide to listen to the event logic changes
        /// </summary>
        /// <param name="source"></param>
        /// <param name="args"></param>
        public delegate void EventLogicEventHandler(object source, EventLogicEventArgs args);

        /// <summary>
        /// The diagnostic event
        /// </summary>
        public event DiagnosticEventHandler DiagnosticEventReceived;

        /// <summary>
        /// The counter timer watchdog event
        /// </summary>
        public event CounterTimerWatchdogEventHandler CounterTimerWatchdogEventReceived;

        /// <summary>
        /// The event logic event
        /// </summary>
        public event EventLogicEventHandler EventLogicEventReceived;

        /// <summary>
        /// Constructor of the board
        /// Cannot be called; initialize the internal variables
        /// </summary>
        private PCI1500()
        {
            this.index = -1;
            this.handle = IntPtr.Zero;

            // Create the event args
            this.diagnosticEventArgs = new DiagnosticEventArgs();
            this.counterTimerWatchdogEventArgs = new CounterTimerWatchdogEventArgs();
            this.eventLogicEventArgs = new EventLogicEventArgs();

            // Create the interrupt handler (once by board)
            this.interruptFunctionHandler = new DllImport.InterruptFunctionEventHandler(InterruptFunction);

            // Tell the garbage collector to keep the pointer
            GC.KeepAlive(this.interruptFunctionHandler);
        }

        /// <summary>
        /// Destructor of the board
        /// Free all the ressources
        /// </summary>
        ~PCI1500()
        {
            DllImport.i_PCI1500_CloseBoard(handle);
            this.index = -1;
            this.handle = IntPtr.Zero;
        }

        /// <summary>
        /// Enables to get an instance of a PCI1500 board
        /// </summary>
        /// <param name="index">The index of the board you want to open</param>
        /// <returns>null on error, instance of PCI1500 on success</returns>
        public static PCI1500 OpenBoard(int index)
        {
            PCI1500 boardInstance = null;
            int nbBoard = 0;
            IntPtr handle = IntPtr.Zero;

            // Get the number of boards
            if ((nbBoard = GetBoardNumber()) == -1)
            {
                Console.WriteLine("GetBoardNumber failed");
                return null;
            }

            // Check that the index is in the range
            if (index < 0 || index > nbBoard)
            {
                Console.WriteLine("index not valid");
                return null;
            }

            // Try to open the board
            if (DllImport.i_PCI1500_OpenBoardViaIndex((byte)index, ref handle) != 0)
            {
                Console.WriteLine("i_PCI1500_OpenBoardViaIndex failed");
                return null;
            }

            // Create a new instance of the board
            boardInstance = new PCI1500();

            // Set its parameters
            boardInstance.index = index;
            boardInstance.handle = handle;

            // Return the instance
            return boardInstance;
        }

        /// <summary>
        /// Enables to get the number of PCI1500 boards plugged in the computer
        /// </summary>
        /// <returns>The number of board</returns>
        public static int GetBoardNumber()
        {
            int ret = 0;
            byte nbBoard = 0;

            // Call the DLL function
            ret = DllImport.i_PCI1500_GetNumberOfBoards(ref nbBoard);

            // Error case
            if (ret != 0)
            {
                return -1;
            }

             // Success
            else
            {
                return (int)nbBoard;
            }
        }

        public static int GetBoardInformation(Byte boardIndex,
                                              UInt32 identifierStringSize,
                                              Byte[] identifier,
                                              out UInt32 uiNumber,
                                              out UInt32 deviceNumber,
                                              out UInt32 busNumber,
                                              out UInt32 baseAddress0,
                                              out UInt32 baseAddress1,
                                              out UInt32 baseAddress2,
                                              out Byte interrupt)
        {
            return DllImport.i_PCI1500_GetBoardInformation(boardIndex,
                                                           identifierStringSize,
                                                           identifier,
                                                           out uiNumber,
                                                           out deviceNumber,
                                                           out busNumber,
                                                           out baseAddress0,
                                                           out baseAddress1,
                                                           out baseAddress2,
                                                           out interrupt);
        }

        #region "InformationVersion"

        public int SetSerialNumber(UInt32 serialNumber)
        {
            // Call the function
            return DllImport.i_PCI1500_SetSerialNumber(this.handle, serialNumber);
        }

        public int GetSerialNumber(out UInt32 serialNumber)
        {
            // Call the function
            return DllImport.i_PCI1500_GetSerialNumber(this.handle, out serialNumber);
        }

        public int GetFirmwareVersion(out UInt32 firmwareVersion)
        {
            // Call the function
            return DllImport.i_PCI1500_GetFirmwareVersion(this.handle, out firmwareVersion);
        }

        public int GetDeviceDriverVersion(out UInt32 version)
        {
            // Call the function
            return DllImport.i_PCI1500_GetDeviceDriverVersion(this.handle, out version);
        }

        public int GetDLLVersion(out UInt32 version)
        {
            // Call the function
            return DllImport.i_PCI1500_GetDLLVersion(out version);
        }

        #endregion

        #region "Interrupt"

        /// <summary>
        /// Interrupt function. Called each time the board interrupts
        /// </summary>
        /// <param name="handle">handle to the board</param>
        /// <param name="fifoOverflow"></param>
        /// <param name="mask"></param>
        /// <param name="values"></param>
        private void InterruptFunction(IntPtr handle, byte fifoOverflow, byte mask, ushort values)
        {
            if ((mask & 0x1) == 0x1)
            {
                // Port A (event logic)
                this.eventLogicEventArgs.port = 0;
                this.OnEventLogicEventReceived(this.eventLogicEventArgs);
            }
            if ((mask & 0x2) == 0x2)
            {
                // Port B (event logic)
                this.eventLogicEventArgs.port = 1;
                this.OnEventLogicEventReceived(this.eventLogicEventArgs);
            }
            if ((mask & 0x4) == 0x4)
            {
                // Counter timer 1
                this.counterTimerWatchdogEventArgs.source = 0;
                this.OnCounterTimerWatchdogEventReceived(this.counterTimerWatchdogEventArgs);
            }
            if ((mask & 0x8) == 0x8)
            {
                // Counter timer 2
                this.counterTimerWatchdogEventArgs.source = 1;
                this.OnCounterTimerWatchdogEventReceived(this.counterTimerWatchdogEventArgs);
            }
            if ((mask & 0x10) == 0x10)
            {
                // counter timer 3
                this.counterTimerWatchdogEventArgs.source = 2;
                this.OnCounterTimerWatchdogEventReceived(this.counterTimerWatchdogEventArgs);
            }
            if ((mask & 0x20) == 0x20)
            {
                // watchdog 3
                this.counterTimerWatchdogEventArgs.source = 3;
                this.OnCounterTimerWatchdogEventReceived(this.counterTimerWatchdogEventArgs);
            }
            if ((mask & 0x40) == 0x40)
            {
                // Supply voltage lost
                this.diagnosticEventArgs.source = 1;
                this.OnDiagnosticEventReceived(this.diagnosticEventArgs);
            }
            if ((mask & 0x80) == 0x80)
            {
                // Short circuit
                this.diagnosticEventArgs.source = 0;
                this.OnDiagnosticEventReceived(this.diagnosticEventArgs);
            }
        }

        /// <summary>
        /// Enable to use the interrupt of the board
        /// To receive an interrupt, you have to listen to the event of the object
        /// </summary>
        /// <returns></returns>
        public int SetBoardIntRoutine()
        {
            return DllImport.i_PCI1500_SetBoardIntRoutine(this.handle, interruptFunctionHandler);
        }

        /// <summary>
        /// Reset the board interrupt routine
        /// </summary>
        /// <returns></returns>
        public int ResetBoardIntRoutine()
        {
            return DllImport.i_PCI1500_ResetBoardIntRoutine(this.handle);
        }

        /// <summary>
        /// Enables to signal to all the listeners that an event on the diagnostic occurs
        /// </summary>
        /// <param name="args"></param>
        protected virtual void OnDiagnosticEventReceived(DiagnosticEventArgs args)
        {
            if (this.DiagnosticEventReceived != null)
            {
                this.DiagnosticEventReceived(this, args);
            }
        }

        /// <summary>
        /// Enables to signal to all the listeners that an event on the counter timer watchdog occurs
        /// </summary>
        /// <param name="args"></param>
        protected virtual void OnCounterTimerWatchdogEventReceived(CounterTimerWatchdogEventArgs args)
        {
            if (this.CounterTimerWatchdogEventReceived != null)
            {
                this.CounterTimerWatchdogEventReceived(this, args);
            }
        }

        /// <summary>
        /// Enables to signal to all the listeners that an event on the event logic occurs
        /// </summary>
        /// <param name="args"></param>
        protected virtual void OnEventLogicEventReceived(EventLogicEventArgs args)
        {
            if (this.EventLogicEventReceived != null)
            {
                this.EventLogicEventReceived(this, args);
            }
        }

        #endregion

        #region "Digital inputs "

        /// <summary>
        /// Enables to read one digital
        /// </summary>
        /// <param name="channel">Channel to read (0-15)</param>
        /// <param name="inputValue">A byte that will be filled with the current status of the input (0,1)</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Read1DigitalInput(byte channel, ref byte inputValue)
        {
            // Call the function
            return DllImport.i_PCI1500_Read1DigitalInput(this.handle, channel, ref inputValue);
        }

        /// <summary>
        /// Enables to read 8 digital inputs (per port)
        /// </summary>
        /// <param name="port">The port you want to read. 0 is for the input 0 to 7, and 1 for the inputs 8 to 16 (0,1)</param>
        /// <param name="inputValues">A byte that will be filled with the current status of the port</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Read8DigitalInputs(byte port, ref byte inputValues)
        {
            // Call the function
            return DllImport.i_PCI1500_Read8DigitalInputs(this.handle, port, ref inputValues);
        }

        /// <summary>
        /// Enables to read 16 digital inputs of the board
        /// </summary>
        /// <param name="value">A ushort that will be filled with the current status of the inputs</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Read16DigitalInputs(ref ushort inputValues)
        {
            // Call the function
            return DllImport.i_PCI1500_Read16DigitalInputs(this.handle, ref inputValues);
        }

        /// <summary>
        /// Enables to read 16 digital outputs of the board
        /// </summary>
        /// <param name="value">A ushort that will be filled with the current status of the outputs</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Get16DigitalOutputsStatus(ref ushort value)
        {
            // Call the function
            return DllImport.i_PCI1500_Get16DigitalOutputsStatus(this.handle, ref value);
        }

        #endregion

        #region "Digital outputs"

        /// <summary>
        /// Set the digital output memory to on
        /// If you want to set an output to off, the digital output memory must be set to on
        /// </summary>
        /// <returns>0 on success, != 0 on error</returns>
        public int SetDigitalOutputMemoryOn()
        {
            // Call the function
            return DllImport.i_PCI1500_SetDigitalOutputMemoryOn(this.handle);
        }

        /// <summary>
        /// Set the digital output memory to off
        /// </summary>
        /// <returns>0 on success, != 0 on error</returns>
        public int SetDigitalOutputMemoryOff()
        {
            // Call the function
            return DllImport.i_PCI1500_SetDigitalOutputMemoryOff(this.handle);
        }

        /// <summary>
        /// Set one output to on
        /// </summary>
        /// <param name="channel">The channel to set (0-15)</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Set1DigitalOutputOn(byte channel)
        {
            // Call the function
            return DllImport.i_PCI1500_Set1DigitalOutputOn(this.handle, channel);
        }

        /// <summary>
        /// Set one output to off
        /// </summary>
        /// <param name="channel">The channel to set (0-15)</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Set1DigitalOutputOff(byte channel)
        {
            // Call the function
            return DllImport.i_PCI1500_Set1DigitalOutputOff(this.handle, channel);
        }

        /// <summary>
        /// Set a mask of output to on (according to a port)
        /// </summary>
        /// <param name="port">The port you want to set. 0 is for the outputs 0 to 7, and 1 for the outputs 8 to 16 (0,1)</param>
        /// <param name="mask">The mask of output. Each bit represent an output (0-FF)</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Set8DigitalOutputsOn(byte port, byte mask)
        {
            // Call the function
            return DllImport.i_PCI1500_Set8DigitalOutputsOn(this.handle, port, mask);
        }

        /// <summary>
        /// Set a mask of output to off (according to a port)
        /// </summary>
        /// <param name="port">The port you want to set. 0 is for the outputs 0 to 7, and 1 for the outputs 8 to 16 (0,1)</param>
        /// <param name="mask">The mask of output. Each bit represent an output (0-FF)</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Set8DigitalOutputsOff(byte port, byte mask)
        {
            // Call the function
            return DllImport.i_PCI1500_Set8DigitalOutputsOff(this.handle, port, mask);
        }

        /// <summary>
        /// Set a mask of output to on
        /// </summary>
        /// <param name="mask">The mask of output. Each bit represent an output (0-FFFF)</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Set16DigitalOutputsOn(ushort mask)
        {
            // Call the function
            return DllImport.i_PCI1500_Set16DigitalOutputsOn(this.handle, mask);
        }

        /// <summary>
        /// Set a mask of output to off
        /// </summary>
        /// <param name="mask">The mask of output. Each bit represent an output (0-FFFF)</param>
        /// <returns>0 on success, != 0 on error</returns>
        public int Set16DigitalOutputsOff(ushort mask)
        {
            // Call the function
            return DllImport.i_PCI1500_Set16DigitalOutputsOff(this.handle, mask);
        }

        #endregion

        #region "Event logic"

        /// <summary>
        /// Initialize the event logic
        /// See doxygen documentation
        /// </summary>
        /// <param name="port"></param>
        /// <param name="eventLogic"></param>
        /// <param name="eventMask"></param>
        /// <returns></returns>
        public int InitEventLogic(byte port, byte eventLogic, string eventMask)
        {
            // Call the function
            return DllImport.i_PCI1500_InitEventLogic(this.handle, port, eventLogic, eventMask);
        }

        /// <summary>
        /// Enables to start the event logic
        /// </summary>
        /// <param name="port"></param>
        /// <returns></returns>
        public int StartEventLogic(byte port)
        {
            // Call the function
            return DllImport.i_PCI1500_StartEventLogic(this.handle, port);
        }

        /// <summary>
        /// Enables to stop the event logic
        /// </summary>
        /// <param name="port"></param>
        /// <returns></returns>
        public int StopEventLogic(byte port)
        {
            // Call the function
            return DllImport.i_PCI1500_StopEventLogic(this.handle, port);
        }

        #endregion

        #region "Clock"

        /// <summary>
        /// Init the timer clock (used for timer and watchdog)
        /// </summary>
        /// <param name="clock">The clock selection. Use: KHZ_115 for 115,2KHz, KHZ_3_6 for 3,6KHz and KHZ_1_8 for 1,8KHz</param>
        /// <returns></returns>
        public int InitTimerInputClock(byte clock)
        {
            // Call the function
            return DllImport.i_PCI1500_InitTimerInputClock(this.handle, clock);
        }

        #endregion

        #region "Counter Timer 1"

        /// <summary>
        /// Initialize the first component
        /// </summary>
        /// <param name="mode">use TIMER_MODE or COUNTER_MODE</param>
        /// <param name="reloadValue"></param>
        /// <param name="enableContinuousCycle"></param>
        /// <param name="enableInterrupt"></param>
        /// <returns></returns>
        public int InitTimerCounter1(byte mode, ushort reloadValue, byte enableContinuousCycle, byte enableInterrupt)
        {
            // Call the function
            return DllImport.i_PCI1500_InitTimerCounter1(this.handle, mode, reloadValue, enableContinuousCycle, enableInterrupt);
        }

        /// <summary>
        /// Start the first component
        /// </summary>
        /// <returns></returns>
        public int StartTimerCounter1()
        {
            // Call the function
            return DllImport.i_PCI1500_StartTimerCounter1(this.handle);
        }

        /// <summary>
        /// Stop the first component
        /// </summary>
        /// <returns></returns>
        public int StopTimerCounter1()
        {
            // Call the function
            return DllImport.i_PCI1500_StopTimerCounter1(this.handle);
        }

        /// <summary>
        /// Trigger the first component
        /// </summary>
        /// <returns></returns>
        public int TriggerTimerCounter1()
        {
            // Call the function
            return DllImport.i_PCI1500_TriggerTimerCounter1(this.handle);
        }

        /// <summary>
        /// Read the value of the first component
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public int ReadTimerCounter1(ref ushort value)
        {
            // Call the function
            return DllImport.i_PCI1500_ReadTimerCounter1(this.handle, ref value);
        }

        #endregion

        #region "Timer Counter 2"

        /// <summary>
        /// Initialize the second component
        /// </summary>
        /// <param name="mode">use TIMER_MODE or COUNTER_MODE</param>
        /// <param name="reloadValue"></param>
        /// <param name="enableContinuousCycle"></param>
        /// <param name="enableHardwareTrigger"></param>
        /// <param name="enableHardwareGate"></param>
        /// <param name="enableInterrupt"></param>
        /// <returns></returns>
        public int InitTimerCounter2(byte mode, ushort reloadValue, byte enableContinuousCycle,byte enableHardwareTrigger, byte enableHardwareGate, byte enableInterrupt)
        {
            // Call the function
            return DllImport.i_PCI1500_InitTimerCounter2(this.handle, mode, reloadValue, enableContinuousCycle, enableHardwareTrigger, enableHardwareGate, enableInterrupt);
        }

        /// <summary>
        /// Start the second component
        /// </summary>
        /// <returns></returns>
        public int StartTimerCounter2()
        {
            // Call the function
            return DllImport.i_PCI1500_StartTimerCounter2(this.handle);
        }

        /// <summary>
        /// Stop the second component
        /// </summary>
        /// <returns></returns>
        public int StopTimerCounter2()
        {
            // Call the function
            return DllImport.i_PCI1500_StopTimerCounter2(this.handle);
        }

        /// <summary>
        /// Trigger the second component
        /// </summary>
        /// <returns></returns>
        public int TriggerTimerCounter2()
        {
            // Call the function
            return DllImport.i_PCI1500_TriggerTimerCounter2(this.handle);
        }

        /// <summary>
        /// Read the value of the second component
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public int ReadTimerCounter2(ref ushort value)
        {
            // Call the function
            return DllImport.i_PCI1500_ReadTimerCounter2(this.handle, ref value);
        }

        #endregion

        #region "Timer Counter 3"

        /// <summary>
        /// Initialize the third component
        /// </summary>
        /// <param name="mode">use WATCHDOG_MODE or COUNTER_MODE</param>
        /// <param name="reloadValue"></param>
        /// <param name="enableContinuousCycle"></param>
        /// <param name="enableHardwareTrigger"></param>
        /// <param name="enableHardwareGate"></param>
        /// <param name="enableInterrupt"></param>
        /// <returns></returns>
        public int InitWatchdogCounter3(byte mode, ushort reloadValue, byte enableContinuousCycle, byte enableHardwareGate, byte enableInterrupt)
        {
            // Call the function
            return DllImport.i_PCI1500_InitWatchdogCounter3(this.handle, mode, reloadValue, enableContinuousCycle, enableHardwareGate, enableInterrupt);
        }

        /// <summary>
        /// Start the third component
        /// </summary>
        /// <returns></returns>
        public int StartWatchdogCounter3()
        {
            // Call the function
            return DllImport.i_PCI1500_StartWatchdogCounter3(this.handle);
        }

        /// <summary>
        /// Stop the third component
        /// </summary>
        /// <returns></returns>
        public int StopWatchdogCounter3()
        {
            // Call the function
            return DllImport.i_PCI1500_StopWatchdogCounter3(this.handle);
        }

        /// <summary>
        /// Trigger the third component
        /// </summary>
        /// <returns></returns>
        public int TriggerWatchdogCounter3()
        {
            // Call the function
            return DllImport.i_PCI1500_TriggerWatchdogCounter3(this.handle);
        }

        /// <summary>
        /// Read the value of the third component
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public int ReadWatchdogCounter3(ref ushort value)
        {
            // Call the function
            return DllImport.i_PCI1500_ReadWatchdogCounter3(this.handle, ref value);
        }

        #endregion
    }
}
