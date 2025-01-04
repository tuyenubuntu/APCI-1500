using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace EventLogic
{
    public partial class EventLogic : Form
    {
        /// <summary>
        /// Handle to the first board
        /// </summary>
        PCI1500_NET.PCI1500 board;

        /// <summary>
        /// Delegate that enables to add an event in the box in another thread
        /// </summary>
        /// <param name="eventInfo"></param>
        private delegate void AddEventDelegate(String eventInfo);

        /// <summary>
        /// Constructor of the form
        /// </summary>
        public EventLogic()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Called at the first load
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void EventLogic_Load(object sender, EventArgs e)
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

            // Stop the event logic
            this.board.StopEventLogic(0);
            this.board.StopEventLogic(1);

            // Enable the interruption
            if ((ret = this.board.SetBoardIntRoutine()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in SetBoardIntRoutine");
                this.Close();
                return;
            }

            // Select the first index for all the combo boxes
            logicType.SelectedIndex = 0;
            channelLogic0.SelectedIndex = 0;
            channelLogic1.SelectedIndex = 0;
            channelLogic2.SelectedIndex = 0;
            channelLogic3.SelectedIndex = 0;
            channelLogic4.SelectedIndex = 0;
            channelLogic5.SelectedIndex = 0;
            channelLogic6.SelectedIndex = 0;
            channelLogic7.SelectedIndex = 0;
            channelLogic8.SelectedIndex = 0;
            channelLogic9.SelectedIndex = 0;
            channelLogic10.SelectedIndex = 0;
            channelLogic11.SelectedIndex = 0;
            channelLogic12.SelectedIndex = 0;
            channelLogic13.SelectedIndex = 0;

            // Add a listener to the event logic
            this.board.EventLogicEventReceived += new PCI1500_NET.PCI1500.EventLogicEventHandler(board_EventLogicEventReceived);
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
        /// Event logic event received
        /// </summary>
        /// <param name="source"></param>
        /// <param name="args"></param>
        void board_EventLogicEventReceived(object source, PCI1500_NET.EventLogicEventArgs args)
        {
            if (args.port == 0 )
            {
                this.Invoke(new AddEventDelegate(this.AddEvent), "Port A generated an interrupt");
            }
            else if (args.port == 1)
            {
                this.Invoke(new AddEventDelegate(this.AddEvent), "Port B generated an interrupt");
            }
        }

        /// <summary>
        /// Occurs while the form is closing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void EventLogic_FormClosing(object sender, FormClosingEventArgs e)
        {
            int ret = 0;
            // Stop the event logic
            this.board.StopEventLogic(0);
            this.board.StopEventLogic(1);

            // Disable the interruption
            if ((ret = this.board.ResetBoardIntRoutine()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in ResetBoardIntRoutine");
                return;
            }
        }

        /// <summary>
        /// Click on the start event logic button (port A)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void startPortALogic_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Compute the logic string
            string logic = channelLogic7.SelectedItem.ToString() + channelLogic6.SelectedItem.ToString() + channelLogic5.SelectedItem.ToString() + channelLogic4.SelectedItem.ToString() + channelLogic3.SelectedItem.ToString() + channelLogic2.SelectedItem.ToString() + channelLogic1.SelectedItem.ToString() + channelLogic0.SelectedItem.ToString();
            // Init the logic
            if ((ret = this.board.InitEventLogic(0, (byte)((logicType.SelectedIndex == 0) ? 0 : 1), logic)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitEventLogic");
                return;
            }
            // Start it
            if ((ret = this.board.StartEventLogic(0)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StartEventLogic");
                return;
            }
            // Enable/disable button
            startPortALogic.Enabled = false;
            stopPortALogic.Enabled = true;
        }

        /// <summary>
        /// Click on the stop event logic button (port A)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void stopPortALogic_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Stop the logic
            if ((ret = this.board.StopEventLogic(0)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StopEventLogic");
                return;
            }
            // Enable/disable button
            startPortALogic.Enabled = true;
            stopPortALogic.Enabled = false;
        }

        /// <summary>
        /// Click on the start event logic button (port B)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void startPortBLogic_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Compute the logic string
            string logic = channelLogic13.SelectedItem.ToString() + channelLogic12.SelectedItem.ToString() + channelLogic11.SelectedItem.ToString() + channelLogic10.SelectedItem.ToString() + channelLogic9.SelectedItem.ToString() + channelLogic8.SelectedItem.ToString();
            // Init the logic
            if ((ret = this.board.InitEventLogic(1, 0, logic)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in InitEventLogic");
                return;
            }
            // Start it
            if ((ret = this.board.StartEventLogic(1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StartEventLogic");
                return;
            }
            // Enable/disable button
            startPortBLogic.Enabled = false;
            stopPortBLogic.Enabled = true;
        }

        /// <summary>
        /// Click on the stop event logic button (port B)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void stopPortBLogic_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Stop the logic
            if ((ret = this.board.StopEventLogic(1)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in StopEventLogic");
                return;
            }
            // Enable/disable button
            startPortBLogic.Enabled = true;
            stopPortBLogic.Enabled = false;
        }
    }
}