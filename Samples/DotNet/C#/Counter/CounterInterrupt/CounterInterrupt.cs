using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CounterInterrupt
{
    public partial class CounterInterrupt : Form
    {
        /// <summary>
        /// Handle to the first board
        /// </summary>
        PCI1500_NET.PCI1500 board;

        /// <summary>
        /// Some internal value. Store the number of interrupt per component
        /// </summary>
        private int counter1InterruptNb = 0;
        private int counter2InterruptNb = 0;
        private int counter3InterruptNb = 0;

        /// <summary>
        /// Constructor of the form
        /// </summary>
        public CounterInterrupt()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Called at the first load
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CounterInterrupt_Load(object sender, EventArgs e)
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
            this.board.StopTimerCounter1();
            this.board.StopTimerCounter2();
            this.board.StopWatchdogCounter3();

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
            if (args.source == 0)
            {
                // Counter timer 1
                this.counter1InterruptNb++;
            }
            else if (args.source == 1)
            {
                // Counter timer 2
                this.counter2InterruptNb++;
            }
            else if (args.source == 2)
            {
                // Counter watchdog 3
                this.counter3InterruptNb++;
            }
        }

        /// <summary>
        /// Click on the start button for the counter 1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter1Start_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Initialize the component as a counter
            if ((ret = this.board.InitTimerCounter1(PCI1500_NET.PCI1500.COUNTER_MODE, 100, 1, 1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitTimerCounter1");
                return;
            }
            // Start the counter
            if ((ret = this.board.StartTimerCounter1()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StartTimerCounter1");
                return;
            }
            // Disable/enable button
            counter1Start.Enabled = false;
            counter1Stop.Enabled = true;
            counter1Trigger.Enabled = true;
            // Start the display timer
            counter1DisplayTimer.Start();
        }

        /// <summary>
        /// Click on the stop button for the counter 1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter1Stop_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Stop the counter
            if ((ret = this.board.StopTimerCounter1()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StopTimerCounter1");
                return;
            }
            // Disable/enable button
            counter1Start.Enabled = true;
            counter1Stop.Enabled = false;
            counter1Trigger.Enabled = false;
            // Stop the display timer
            counter1DisplayTimer.Stop();
        }

        /// <summary>
        /// Display timer for counter 1 ticks
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter1DisplayTimer_Tick(object sender, EventArgs e)
        {
            int ret = 0;
            ushort value = 0;
            // Read the value
            if ((ret = this.board.ReadTimerCounter1(ref value)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ReadTimerCounter1");
                return;
            }
            counter1Value.Text = value.ToString();
            counter1Interrupt.Text = this.counter1InterruptNb.ToString();
        }

        /// <summary>
        /// Click on the trigger button for the counter 1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter1Trigger_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Read the value
            if ((ret = this.board.TriggerTimerCounter1()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in TriggerTimerCounter1");
                return;
            }
        }

        /// <summary>
        /// Occurs while the form is closing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CounterInterrupt_FormClosing(object sender, FormClosingEventArgs e)
        {
            int ret = 0;
            // Stop the counter
            this.board.StopTimerCounter1();
            this.board.StopTimerCounter2();
            this.board.StopWatchdogCounter3();
            // Disable the interruption
            if ((ret = this.board.ResetBoardIntRoutine()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ResetBoardIntRoutine");
                return;
            }
        }

        /// <summary>
        /// Click on the start button for the counter 2
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter2Start_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Initialize the component as a counter
            if ((ret = this.board.InitTimerCounter2(PCI1500_NET.PCI1500.COUNTER_MODE, 100, 1,0,0, 1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitTimerCounter2");
                return;
            }
            // Start the counter
            if ((ret = this.board.StartTimerCounter2()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StartTimerCounter2");
                return;
            }
            // Disable/enable button
            counter2Start.Enabled = false;
            counter2Stop.Enabled = true;
            counter2Trigger.Enabled = true;
            // Start the display timer
            counter2DisplayTimer.Start();
        }

        /// <summary>
        /// Display timer for counter 2 ticks
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter2DisplayTimer_Tick(object sender, EventArgs e)
        {
            int ret = 0;
            ushort value = 0;
            // Read the value
            if ((ret = this.board.ReadTimerCounter2(ref value)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ReadTimerCounter2");
                return;
            }
            counter2Value.Text = value.ToString();
            counter2Interrupt.Text = this.counter2InterruptNb.ToString();
        }

        /// <summary>
        /// Click on the stop button for the counter 2
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter2Stop_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Stop the counter
            if ((ret = this.board.StopTimerCounter2()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StopTimerCounter2");
                return;
            }
            // Disable/enable button
            counter2Start.Enabled = true;
            counter2Stop.Enabled = false;
            counter2Trigger.Enabled = false;
            // Stop the display timer
            counter2DisplayTimer.Stop();
        }

        /// <summary>
        /// Click on the trigger button for the counter 2
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter2Trigger_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Read the value
            if ((ret = this.board.TriggerTimerCounter2()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in TriggerTimerCounter2");
                return;
            }
        }

        /// <summary>
        /// Click on the start button for the counter 3
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter3Start_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Initialize the component as a counter
            if ((ret = this.board.InitWatchdogCounter3(PCI1500_NET.PCI1500.COUNTER_MODE,100,1,0,1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitWatchdogCounter3");
                return;
            }
            // Start the counter
            if ((ret = this.board.StartWatchdogCounter3()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StartWatchdogCounter3");
                return;
            }
            // Disable/enable button
            counter3Start.Enabled = false;
            counter3Stop.Enabled = true;
            counter3Trigger.Enabled = true;
            // Start the display timer
            counter3DisplayTimer.Start();
        }

        /// <summary>
        /// Click on the stop button for the counter 3
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter3Stop_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Stop the counter
            if ((ret = this.board.StopWatchdogCounter3()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StopWatchdogCounter3");
                return;
            }
            // Disable/enable button
            counter3Start.Enabled = true;
            counter3Stop.Enabled = false;
            counter3Trigger.Enabled = false;
            // Stop the display timer
            counter3DisplayTimer.Stop();
        }

        /// <summary>
        /// Display timer for counter 3 ticks
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter3DisplayTimer_Tick(object sender, EventArgs e)
        {
            int ret = 0;
            ushort value = 0;
            // Read the value
            if ((ret = this.board.ReadWatchdogCounter3(ref value)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ReadWatchdogCounter3");
                return;
            }
            counter3Value.Text = value.ToString();
            counter3Interrupt.Text = this.counter3InterruptNb.ToString();
        }

        /// <summary>
        /// Click on the trigger button for the counter 3
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void counter3Trigger_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Read the value
            if ((ret = this.board.TriggerWatchdogCounter3()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in TriggerWatchdogCounter3");
                return;
            }
        }
    }
}