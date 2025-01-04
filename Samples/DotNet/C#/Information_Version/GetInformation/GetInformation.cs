using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace GetInformation
{
    public partial class GetInformation : Form
    {
        /// <summary>
        /// Handle to the first board
        /// </summary>
        PCI1500_NET.PCI1500 board;

        /// <summary>
        /// Constructor of the form
        /// </summary>
        public GetInformation()
        {
            InitializeComponent();//Init the visual coponent
            fill();// getSerial number and firmware version
        }

        private void fill()
        {
            //values for the labels
            UInt32 firmwareVersion, serialNumberVersion;

            // Open the first board of the system
            this.board = PCI1500_NET.PCI1500.OpenBoard(0);
            // Error handling
            if (this.board == null)
            {
                MessageBox.Show("Error OpenBoard returned null");
                this.Close();
                return;
            }
            //Get the values
            if (this.board.GetFirmwareVersion(out firmwareVersion) != 0)
            {
                MessageBox.Show("Error i_PCI1500_GetFirmwareVersion returned null");
                this.Close();
                return;
            }
            if (this.board.GetSerialNumber(out serialNumberVersion) != 0)
            {
                MessageBox.Show("Error i_PCI1500_GetSerialNumber returned null");
                this.Close();
                return;
            }
            //fill the labels
            valueSerialNumber.Text = "A-D " + serialNumberVersion.ToString();
            valueFirmwareVersion.Text = string.Format("{0}{1} {2}{3}", (char)(firmwareVersion >> 24 & 0xFF), (char)(firmwareVersion >> 16 & 0xFF), (char)(firmwareVersion >> 8 & 0xFF), (char)(firmwareVersion & 0xFF));
        }

        private void setSerialNumber_click(object sender, EventArgs e)
        {
            // Open the first board of the system
            this.board = PCI1500_NET.PCI1500.OpenBoard(0);
            //set the serial board number
            if (this.board.SetSerialNumber(Decimal.ToUInt32(serialNumberVersion.Value)) != 0)
            {
                MessageBox.Show("Error i_PCI1500_GetSerialNumber returned null");
                this.Close();
                return;
            }
            //refresh values
            fill();
        }

    }
}
