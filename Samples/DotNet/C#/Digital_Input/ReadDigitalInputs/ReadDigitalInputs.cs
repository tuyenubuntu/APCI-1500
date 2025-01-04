using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ReadDigitalInputs
{
    public partial class ReadDigitalInputs : Form
    {
        /// <summary>
        /// Handle to the first board
        /// </summary>
        PCI1500_NET.PCI1500 board;

        /// <summary>
        /// Usefull variable used to access the input status picture
        /// </summary>
        PictureBox[] inputStatusBox;

        /// <summary>
        /// Constructor of the form
        /// </summary>
        public ReadDigitalInputs()
        {
            InitializeComponent();
            inputStatusBox = new PictureBox[16];
            inputStatusBox[0] = input0StatusBox;
            inputStatusBox[1] = input1StatusBox;
            inputStatusBox[2] = input2StatusBox;
            inputStatusBox[3] = input3StatusBox;
            inputStatusBox[4] = input4StatusBox;
            inputStatusBox[5] = input5StatusBox;
            inputStatusBox[6] = input6StatusBox;
            inputStatusBox[7] = input7StatusBox;
            inputStatusBox[8] = input8StatusBox;
            inputStatusBox[9] = input9StatusBox;
            inputStatusBox[10] = input10StatusBox;
            inputStatusBox[11] = input11StatusBox;
            inputStatusBox[12] = input12StatusBox;
            inputStatusBox[13] = input13StatusBox;
            inputStatusBox[14] = input14StatusBox;
            inputStatusBox[15] = input15StatusBox;
        }

        /// <summary>
        /// Call at the first load
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ReadDigitalInputs_Load(object sender, EventArgs e)
        {
             // Open the first board of the system
            this.board = PCI1500_NET.PCI1500.OpenBoard(0);
            // Error handling
            if (this.board == null)
            {
                MessageBox.Show("Error OpenBoard returned null");
                this.Close();
                return;
            }
            // Start the timer
            this.readTimer.Start();
        }

        /// <summary>
        /// The read timer ticks
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void readTimer_Tick(object sender, EventArgs e)
        {
            int returnValue = 0;
            ushort inputValue = 0;
            // We read the status of the outputs
            if ( (returnValue = this.board.Read16DigitalInputs(ref inputValue)) != 0)
            {
                MessageBox.Show("Error " + returnValue.ToString() + " in Read16DigitalInputs");
                this.Close();
                return;
            }

            // We change the image given the new status
            for (int i = 0; i < 16; i++)
            {
                if (((inputValue >> i) & 1) == 1)
                {
                    inputStatusBox[i].Image = global::ReadDigitalInputs.Properties.Resources.led_on;
                }
                else
                {
                    inputStatusBox[i].Image = global::ReadDigitalInputs.Properties.Resources.led_off;
                }
            }

            this.ResumeLayout(false);
            this.PerformLayout();
        }

        /// <summary>
        /// Occurs when the user closes the form
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ReadDigitalInputs_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Stop the timer
            this.readTimer.Stop();
        }
    }
}