using System;
using System.Collections.Generic;
using System.Text;

namespace PCI1500_NET
{
    /// <summary>
    /// Store the data of the counter timer watchdog event
    /// </summary>
    public class CounterTimerWatchdogEventArgs
    {
        /// <summary>
        /// 0: counter timer 1
        /// 1: counter timer 2
        /// 2: counter timer 3
        /// 3: watchdog
        /// </summary>
        public int source;
    }
}
