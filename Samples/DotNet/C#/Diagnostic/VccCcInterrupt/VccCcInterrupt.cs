using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace VccCcInterrupt
{
    public partial class VccCcInterrupt : Form
    {
        /// <summary>
        /// Handle to the first board
        /// </summary>
        PCI1500_NET.PCI1500 board;

        /// Delegate that enables to add an event in the box in another thread
        private delegate void AddEventDelegate(String eventInfo);

        /// <summary>
        /// Constructor of the form
        /// </summary>
        public VccCcInterrupt()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Add an event in the event box
        /// </summary>
        /// <param name="eventInfo"></param>
        private void AddEvent(String eventInfo)
        {
            eventBox.Text += DateTime.Now.ToString() + " : " + eventInfo + "\r\n";
            eventBox.SelectionStart = eventBox.Text.Length;
            eventBox.ScrollToCaret();
        }

        /// <summary>
        /// Call at the first load
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void VccCcInterrupt_Load(object sender, EventArgs e)
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

            // Listen to the diagnostic event
            this.board.DiagnosticEventReceived += new PCI1500_NET.PCI1500.DiagnosticEventHandler(board_DiagnosticEventReceived);

            // Set all the output to high (to generate output interrupt)
            if ((ret = this.board.Set16DigitalOutputsOn(0xFFFF)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOn");
                this.Close();
                return;
            }
            // Set the interrupt routine
            if ((ret = this.board.SetBoardIntRoutine()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in SetBoardIntRoutine");
                this.Close();
                return;
            }
            // Enable the event logic on port 1 in order to receive CC and VCC diagnostic
            if ((ret = this.board.InitEventLogic(1, 0, "xxxxxx")) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitEventLogic");
                this.Close();
                return;
            }
            // Start the event logic
            if ((ret = this.board.StartEventLogic(1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StartEventLogic");
                this.Close();
                return;
            }
        }

        /// <summary>
        /// Occurs when we get a diagnostic event
        /// </summary>
        /// <param name="source"></param>
        /// <param name="args"></param>
        void board_DiagnosticEventReceived(object source, PCI1500_NET.DiagnosticEventArgs args)
        {
            if (args.source == 0)
            {
                this.Invoke(new AddEventDelegate(this.AddEvent), "Short-circuit occured");
            }
            else if (args.source == 1)
            {
                this.Invoke(new AddEventDelegate(this.AddEvent), "Supply voltage lost");
            }
        }

        /// <summary>
        /// Occurs when the form is being closed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void VccCcInterrupt_FormClosing(object sender, FormClosingEventArgs e)
        {
            int ret = 0;
            // First set the digital output memory to on
            if ((ret = this.board.SetDigitalOutputMemoryOn()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOn");
            }
            // Then set all the output to off
            if ((ret = this.board.Set16DigitalOutputsOff(0xFFFF)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOff");
            }
            // Reset the digital output memory to off 
            if ((ret = this.board.SetDigitalOutputMemoryOff()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOff");
            }
            // Stop the event logic
            if ((ret = this.board.StopEventLogic(1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StopEventLogic");
            }
            // Reset the board interrupt routine
            if ((ret = this.board.ResetBoardIntRoutine()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ResetBoardIntRoutine");
            }
        }
    }
}