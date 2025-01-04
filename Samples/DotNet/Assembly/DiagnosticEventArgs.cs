using System;
using System.Collections.Generic;
using System.Text;

namespace PCI1500_NET
{
    /// <summary>
    /// Store the data of the diagnostic event
    /// </summary>
    public class DiagnosticEventArgs
    {
        /// <summary>
        /// 0 if short-circuit
        /// 1 if supply voltage lost
        /// </summary>
        public int source;
    }
}
