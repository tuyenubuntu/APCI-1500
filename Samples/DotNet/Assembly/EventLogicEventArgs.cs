using System;
using System.Collections.Generic;
using System.Text;

namespace PCI1500_NET
{
    /// <summary>
    /// Store the data of the event logic event
    /// </summary>
    public class EventLogicEventArgs
    {
        /// <summary>
        /// 0 for port A, 1 for port B
        /// </summary>
        public int port;
    }
}
