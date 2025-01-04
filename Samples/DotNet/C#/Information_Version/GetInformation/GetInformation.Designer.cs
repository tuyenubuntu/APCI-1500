namespace GetInformation
{
    partial class GetInformation
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(GetInformation));
            this.getInformationGroupBox = new System.Windows.Forms.GroupBox();
            this.valueFirmwareVersion = new System.Windows.Forms.Label();
            this.labelFirmwareVersion = new System.Windows.Forms.Label();
            this.valueSerialNumber = new System.Windows.Forms.Label();
            this.labelSerialNumber = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.serialNumberVersion = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.getInformationGroupBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.serialNumberVersion)).BeginInit();
            this.SuspendLayout();
            // 
            // getInformationGroupBox
            // 
            this.getInformationGroupBox.Controls.Add(this.valueFirmwareVersion);
            this.getInformationGroupBox.Controls.Add(this.labelFirmwareVersion);
            this.getInformationGroupBox.Controls.Add(this.valueSerialNumber);
            this.getInformationGroupBox.Controls.Add(this.labelSerialNumber);
            this.getInformationGroupBox.Location = new System.Drawing.Point(68, 12);
            this.getInformationGroupBox.Name = "getInformationGroupBox";
            this.getInformationGroupBox.Size = new System.Drawing.Size(283, 80);
            this.getInformationGroupBox.TabIndex = 0;
            this.getInformationGroupBox.TabStop = false;
            this.getInformationGroupBox.Text = "Version Informations";
            // 
            // valueFirmwareVersion
            // 
            this.valueFirmwareVersion.AutoSize = true;
            this.valueFirmwareVersion.Location = new System.Drawing.Point(149, 53);
            this.valueFirmwareVersion.Name = "valueFirmwareVersion";
            this.valueFirmwareVersion.Size = new System.Drawing.Size(13, 13);
            this.valueFirmwareVersion.TabIndex = 5;
            this.valueFirmwareVersion.Text = "0";
            // 
            // labelFirmwareVersion
            // 
            this.labelFirmwareVersion.AutoSize = true;
            this.labelFirmwareVersion.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelFirmwareVersion.Location = new System.Drawing.Point(6, 53);
            this.labelFirmwareVersion.Name = "labelFirmwareVersion";
            this.labelFirmwareVersion.Size = new System.Drawing.Size(99, 13);
            this.labelFirmwareVersion.TabIndex = 4;
            this.labelFirmwareVersion.Text = "FirmwareVersion";
            // 
            // valueSerialNumber
            // 
            this.valueSerialNumber.AutoSize = true;
            this.valueSerialNumber.Location = new System.Drawing.Point(149, 27);
            this.valueSerialNumber.Name = "valueSerialNumber";
            this.valueSerialNumber.Size = new System.Drawing.Size(13, 13);
            this.valueSerialNumber.TabIndex = 1;
            this.valueSerialNumber.Text = "0";
            // 
            // labelSerialNumber
            // 
            this.labelSerialNumber.AutoSize = true;
            this.labelSerialNumber.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelSerialNumber.Location = new System.Drawing.Point(6, 27);
            this.labelSerialNumber.Name = "labelSerialNumber";
            this.labelSerialNumber.Size = new System.Drawing.Size(82, 13);
            this.labelSerialNumber.TabIndex = 0;
            this.labelSerialNumber.Text = "SerialNumber";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.serialNumberVersion);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Location = new System.Drawing.Point(12, 98);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(418, 84);
            this.groupBox1.TabIndex = 9;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Version Informations";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(260, 28);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(138, 37);
            this.button1.TabIndex = 6;
            this.button1.Text = "Change Serial Number";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.setSerialNumber_click);
            // 
            // serialNumberVersion
            // 
            this.serialNumberVersion.Location = new System.Drawing.Point(112, 39);
            this.serialNumberVersion.Maximum = new decimal(new int[] {
            999999,
            0,
            0,
            0});
            this.serialNumberVersion.Minimum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.serialNumberVersion.Name = "serialNumberVersion";
            this.serialNumberVersion.Size = new System.Drawing.Size(142, 20);
            this.serialNumberVersion.TabIndex = 5;
            this.serialNumberVersion.Value = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(41, 42);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(28, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "A-D";
            // 
            // GetInformation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(442, 189);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.getInformationGroupBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "GetInformation";
            this.Text = "Sample: Counter with interrupt";
            this.getInformationGroupBox.ResumeLayout(false);
            this.getInformationGroupBox.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.serialNumberVersion)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox getInformationGroupBox;
        private System.Windows.Forms.Label labelSerialNumber;
        private System.Windows.Forms.Label valueSerialNumber;
        private System.Windows.Forms.Label labelFirmwareVersion;
        private System.Windows.Forms.Label valueFirmwareVersion;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown serialNumberVersion;
        private System.Windows.Forms.Button button1;
    }
}

