using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SetDigitalOutputs
{
    public partial class SetDigitalOutputs : Form
    {
        /// <summary>
        /// Handle to the first board
        /// </summary>
        PCI1500_NET.PCI1500 board;

        /// <summary>
        /// Usefull variable used to access the input status picture
        /// </summary>
        PictureBox[] outputStatusBox;

        /// <summary>
        /// Store the status of the outputs
        /// </summary>
        ushort outputStatus;

        /// <summary>
        /// Store the status of the digital output memory
        /// </summary>
        int digitalOutputMemoryStatus;

        /// <summary>
        /// Constructor of the form
        /// </summary>
        public SetDigitalOutputs()
        {
            InitializeComponent();
            outputStatusBox = new PictureBox[16];
            outputStatusBox[0] = output0StatusBox;
            outputStatusBox[1] = output1StatusBox;
            outputStatusBox[2] = output2StatusBox;
            outputStatusBox[3] = output3StatusBox;
            outputStatusBox[4] = output4StatusBox;
            outputStatusBox[5] = output5StatusBox;
            outputStatusBox[6] = output6StatusBox;
            outputStatusBox[7] = output7StatusBox;
            outputStatusBox[8] = output8StatusBox;
            outputStatusBox[9] = output9StatusBox;
            outputStatusBox[10] = output10StatusBox;
            outputStatusBox[11] = output11StatusBox;
            outputStatusBox[12] = output12StatusBox;
            outputStatusBox[13] = output13StatusBox;
            outputStatusBox[14] = output14StatusBox;
            outputStatusBox[15] = output15StatusBox;
        }

        /// <summary>
        /// Click on one input
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void outputStatusBox_Click(object sender, EventArgs e)
        {
            int ret = 0;

            for (int i = 0; i < 16; i++)
            {
                if (sender == outputStatusBox[i])
                {
                    // Get the status
                    int status = (this.outputStatus >> i) & 1;
                    // Check digital output memory status
                    if ((this.digitalOutputMemoryStatus == 0) && (status == 1))
                    {
                        // The user want to set the output to 0 but the digital output memory is off
                        MessageBox.Show("To set an output to low, you must activate the digital output memory.");
                        return;
                    }
                    // Update the output status
                    if ( (this.digitalOutputMemoryStatus == 0) && ( status == 0) )
                    {
                        this.outputStatus = (ushort)(1 << i);
                        if ((ret = this.board.Set16DigitalOutputsOn(this.outputStatus)) != 0)
                        {
                            MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOn");
                            return;
                        }
                    }
                    else if ((this.digitalOutputMemoryStatus == 1) && (status == 0))
                    {
                        this.outputStatus = (ushort)(this.outputStatus | (ushort)(1 << i));
                        if ((ret = this.board.Set16DigitalOutputsOn(this.outputStatus)) != 0)
                        {
                            MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOn");
                            return;
                        }
                    }
                    else if ((this.digitalOutputMemoryStatus == 1) && (status == 1))
                    {
                        this.outputStatus = (ushort)(this.outputStatus & (ushort)(~(1 << i)));
                        if ((ret = this.board.Set16DigitalOutputsOff((ushort)(~this.outputStatus))) != 0)
                        {
                            MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOff");
                            return;
                        }
                    }
                }
            }

            // We then update the graphics
            for (int i = 0; i < 16; i++)
            {
                if (((this.outputStatus >> i) & 1) == 1)
                {
                    outputStatusBox[i].Image = global::SetDigitalOutputs.Properties.Resources.led_on;
                }
                else
                {
                    outputStatusBox[i].Image = global::SetDigitalOutputs.Properties.Resources.led_off;
                }
            }

            this.ResumeLayout(false);
            this.PerformLayout();
        }

        /// <summary>
        /// Call at the first load
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SetDigitalOutputs_Load(object sender, EventArgs e)
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
            // Set digital output memory to off
            if ((ret = this.board.SetDigitalOutputMemoryOff()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOff");
                this.Close();
                return;
            }
            // Set all the output to high
            if ((ret = this.board.Set16DigitalOutputsOn(0xFFFF)) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOn");
                this.Close();
                return;
            }
            // Store the status
            this.outputStatus = 0xFFFF;
            this.digitalOutputMemoryStatus = 0;
        }

        /// <summary>
        /// Occurs when the form is being closed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SetDigitalOutputs_FormClosing(object sender, FormClosingEventArgs e)
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
        }

        /// <summary>
        /// Click on the on button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void digitalOutputMemoryOnButton_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Set the digital output memory to on
            if ((ret = this.board.SetDigitalOutputMemoryOn()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOn");
            }
            // Disable/Enable button
            digitalOutputMemoryOnButton.Enabled = false;
            digitalOutputMemoryOffButton.Enabled = true;
            // Store the status
            this.digitalOutputMemoryStatus = 1;
        }

        /// <summary>
        /// Click on the off button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void digitalOutputMemoryOffButton_Click(object sender, EventArgs e)
        {
            int ret = 0;
            // Set the digital output memory to off
            if ((ret = this.board.SetDigitalOutputMemoryOff()) != 0)
            {
                MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOff");
            }
            // Disable/Enable button
            digitalOutputMemoryOffButton.Enabled = false;
            digitalOutputMemoryOnButton.Enabled = true;
            // Store the status
            this.digitalOutputMemoryStatus = 0;
        }
    }
}