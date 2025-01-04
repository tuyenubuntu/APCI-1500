using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WatchdogInterrupt
{
    public partial class WatchdogInterruptForm : Form
    {
        /// <summary>
        /// Handle to the first board
        /// </summary>
        PCI1500_NET.PCI1500 board;

        /// <summary>
        /// Some internal value. Store the number of interrupt per component
        /// </summary>
        private int watchdogInterruptNb = 0;

        /// <summary>
        /// Constructor of the form
        /// </summary>
        public WatchdogInterruptForm()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Called at the first load
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WatchdogInterruptForm_Load(object sender, EventArgs e)
        {
            int ret = 0;

            // Open the first board of the system
            this.board = PCI1500_NET.PCI1500.OpenBoard(0);
            // Error handling
            if (this.board == null)
            {
                MessageBox.Show("Error OpenBoard returned null");
                this.Close();
                return;
            }

            // Enable the interruption
            if ((ret = this.board.SetBoardIntRoutine()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in SetBoardIntRoutine");
                this.Close();
                return;
            }

            // Stop the components. No check since if nothing is started the function will failed
            this.board.StopWatchdogCounter3();

            // Initialize the clock
            if ((ret = this.board.InitTimerInputClock(PCI1500_NET.PCI1500.KHZ_1_8)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitTimerInputClock");
                this.Close();
                return;
            }

            // Listen to the counter timer watchdog interruption
            this.board.CounterTimerWatchdogEventReceived += new PCI1500_NET.PCI1500.CounterTimerWatchdogEventHandler(board_CounterTimerWatchdogEventReceived);
        }

        /// <summary>
        /// Counter timer watchdog interruption
        /// </summary>
        /// <param name="source"></param>
        /// <param name="args"></param>
        void board_CounterTimerWatchdogEventReceived(object source, PCI1500_NET.CounterTimerWatchdogEventArgs args)
        {
            if (args.source == 3)
            {
                // Watchdog
                this.watchdogInterruptNb++;
            }
        }

        /// <summary>
        /// Occurs while the form is closing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WatchdogInterruptForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            int ret = 0;
            // Stop the watchdog
            this.board.StopWatchdogCounter3();
            // Disable the interruption
            if ((ret = this.board.ResetBoardIntRoutine()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ResetBoardIntRoutine");
                return;
            }
        }

        /// <summary>
        /// Display timer for watchdog ticks
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void watchdogDisplayTimer_Tick(object sender, EventArgs e)
        {
            int ret = 0;
            ushort value = 0;
            // Read the value
            if ((ret = this.board.ReadWatchdogCounter3(ref value)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ReadWatchdogCounter3");
                return;
            }
            watchdogValue.Text = value.ToString();
            watchdogInterrupt.Text = this.watchdogInterruptNb.ToString();
        }

        /// <summary>
        /// Click on the start button for the watchdog
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void watchdogStart_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Initialize the component as a watchdog
            if ((ret = this.board.InitWatchdogCounter3(PCI1500_NET.PCI1500.WATCHDOG_MODE, 5000, 1, 0, 1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitWatchdogCounter3");
                return;
            }
            // Start the watchdog
            if ((ret = this.board.StartWatchdogCounter3()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StartWatchdogCounter3");
                return;
            }
            // Disable/enable button
            watchdogStart.Enabled = false;
            watchdogStop.Enabled = true;
            watchdogTrigger.Enabled = true;
            // Start the display timer
            watchdogDisplayTimer.Start();
        }

        /// <summary>
        /// Click on the stop button for the watchdog
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void watchdogStop_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Stop the watchdog
            if ((ret = this.board.StopWatchdogCounter3()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StopWatchdogCounter3");
                return;
            }
            // Disable/enable button
            watchdogStart.Enabled = true;
            watchdogStop.Enabled = false;
            watchdogTrigger.Enabled = false;
            // Stop the display timer
            watchdogDisplayTimer.Stop();
        }

        /// <summary>
        /// Click on the trigger button for the watchdog
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void watchdogTrigger_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Read the value
            if ((ret = this.board.TriggerWatchdogCounter3()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in TriggerWatchdogCounter3");
                return;
            }
        }

        /// <summary>
        /// Set all the digital outputs to high
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void setOutputButton_Click(object sender, EventArgs e)
        {
            int ret = 0;
            if ((ret = this.board.Set16DigitalOutputsOn(0xFFFF)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOn");
                return;
            }
        }
    }
}