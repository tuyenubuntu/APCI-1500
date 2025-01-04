using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace TimerInterrupt
{
    public partial class TimerInterrupt : Form
    {
        /// <summary>
        /// Handle to the first board
        /// </summary>
        PCI1500_NET.PCI1500 board;

        /// <summary>
        /// Some internal value. Store the number of interrupt per component
        /// </summary>
        private int timer1InterruptNb = 0;
        private int timer2InterruptNb = 0;

        /// <summary>
        /// Constructor of the form
        /// </summary>
        public TimerInterrupt()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Called at the first load
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TimerInterrupt_Load(object sender, EventArgs e)
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
            if (args.source == 0)
            {
                // Counter timer 1
                this.timer1InterruptNb++;
            }
            else if (args.source == 1)
            {
                // Counter timer 2
                this.timer2InterruptNb++;
            }
        }

        /// <summary>
        /// Display timer for timer 1 ticks
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer1DisplayTimer_Tick(object sender, EventArgs e)
        {
            int ret = 0;
            ushort value = 0;
            // Read the value
            if ((ret = this.board.ReadTimerCounter1(ref value)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ReadTimerCounter1");
                return;
            }
            timer1Value.Text = value.ToString();
            timer1Interrupt.Text = this.timer1InterruptNb.ToString();
        }

        /// <summary>
        /// Click on the start button for the timer 1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer1Start_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Initialize the component as a timer
            if ((ret = this.board.InitTimerCounter1(PCI1500_NET.PCI1500.TIMER_MODE, 5000, 1, 1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitTimerCounter1");
                return;
            }
            // Start the timer
            if ((ret = this.board.StartTimerCounter1()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StartTimerCounter1");
                return;
            }
            // Disable/enable button
            timer1Start.Enabled = false;
            timer1Stop.Enabled = true;
            timer1Trigger.Enabled = true;
            // Start the display timer
            timer1DisplayTimer.Start();
        }

        /// <summary>
        /// Click on the stop button for the timer 1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer1Stop_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Stop the timer
            if ((ret = this.board.StopTimerCounter1()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StopTimerCounter1");
                return;
            }
            // Disable/enable button
            timer1Start.Enabled = true;
            timer1Stop.Enabled = false;
            timer1Trigger.Enabled = false;
            // Stop the display timer
            timer1DisplayTimer.Stop();
        }

        /// <summary>
        /// Click on the trigger button for the timer 1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer1Trigger_Click(object sender, EventArgs e)
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
        /// Click on the start button for the timer 2
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer2Start_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Initialize the component as a timer
            if ((ret = this.board.InitTimerCounter2(PCI1500_NET.PCI1500.TIMER_MODE, 5000, 1,0,0, 1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitTimerCounter2");
                return;
            }
            // Start the timer
            if ((ret = this.board.StartTimerCounter2()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StartTimerCounter2");
                return;
            }
            // Disable/enable button
            timer2Start.Enabled = false;
            timer2Stop.Enabled = true;
            timer2Trigger.Enabled = true;
            // Start the display timer
            timer2DisplayTimer.Start();
        }

        /// <summary>
        /// Display timer for timer 2 ticks
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer2DisplayTimer_Tick(object sender, EventArgs e)
        {
            int ret = 0;
            ushort value = 0;
            // Read the value
            if ((ret = this.board.ReadTimerCounter2(ref value)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ReadTimerCounter2");
                return;
            }
            timer2Value.Text = value.ToString();
            timer2Interrupt.Text = this.timer2InterruptNb.ToString();
        }

        /// <summary>
        /// Occurs while the form is closing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TimerInterrupt_FormClosing(object sender, FormClosingEventArgs e)
        {
            int ret = 0;
            // Stop the timers
            this.board.StopTimerCounter1();
            this.board.StopTimerCounter2();
            // Disable the interruption
            if ((ret = this.board.ResetBoardIntRoutine()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ResetBoardIntRoutine");
                return;
            }
        }

        /// <summary>
        /// Click on the stop button for the timer 2
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer2Stop_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Stop the timer
            if ((ret = this.board.StopTimerCounter2()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StopTimerCounter2");
                return;
            }
            // Disable/enable button
            timer2Start.Enabled = true;
            timer2Stop.Enabled = false;
            timer2Trigger.Enabled = false;
            // Stop the display timer
            timer2DisplayTimer.Stop();
        }

        /// <summary>
        /// Click on the trigger button for the timer 2
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer2Trigger_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Read the value
            if ((ret = this.board.TriggerTimerCounter2()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in TriggerTimerCounter2");
                return;
            }
        }
    }
}