﻿using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace WatchdogInterrupt
{
    static class Program
    {
        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new WatchdogInterruptForm());
        }
    }
}