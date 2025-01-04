namespace ReadDigitalInputs
{
    partial class ReadDigitalInputs
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ReadDigitalInputs));
            this.readTimer = new System.Windows.Forms.Timer(this.components);
            this.input0StatusBox = new System.Windows.Forms.PictureBox();
            this.helpBox = new System.Windows.Forms.GroupBox();
            this.helpLabel = new System.Windows.Forms.Label();
            this.input1StatusBox = new System.Windows.Forms.PictureBox();
            this.input2StatusBox = new System.Windows.Forms.PictureBox();
            this.input3StatusBox = new System.Windows.Forms.PictureBox();
            this.input7StatusBox = new System.Windows.Forms.PictureBox();
            this.input6StatusBox = new System.Windows.Forms.PictureBox();
            this.input5StatusBox = new System.Windows.Forms.PictureBox();
            this.input4StatusBox = new System.Windows.Forms.PictureBox();
            this.input15StatusBox = new System.Windows.Forms.PictureBox();
            this.input14StatusBox = new System.Windows.Forms.PictureBox();
            this.input13StatusBox = new System.Windows.Forms.PictureBox();
            this.input12StatusBox = new System.Windows.Forms.PictureBox();
            this.input11StatusBox = new System.Windows.Forms.PictureBox();
            this.input10StatusBox = new System.Windows.Forms.PictureBox();
            this.input9StatusBox = new System.Windows.Forms.PictureBox();
            this.input8StatusBox = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.pictureBox16 = new System.Windows.Forms.PictureBox();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.pictureBox17 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.input0StatusBox)).BeginInit();
            this.helpBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.input1StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input2StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input3StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input7StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input6StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input5StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input4StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input15StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input14StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input13StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input12StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input11StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input10StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input9StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.input8StatusBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox16)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox17)).BeginInit();
            this.SuspendLayout();
            // 
            // readTimer
            // 
            this.readTimer.Tick += new System.EventHandler(this.readTimer_Tick);
            // 
            // input0StatusBox
            // 
            this.input0StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input0StatusBox.Location = new System.Drawing.Point(41, 128);
            this.input0StatusBox.Name = "input0StatusBox";
            this.input0StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input0StatusBox.TabIndex = 0;
            this.input0StatusBox.TabStop = false;
            // 
            // helpBox
            // 
            this.helpBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.helpBox.Controls.Add(this.label18);
            this.helpBox.Controls.Add(this.pictureBox17);
            this.helpBox.Controls.Add(this.label17);
            this.helpBox.Controls.Add(this.pictureBox16);
            this.helpBox.Controls.Add(this.helpLabel);
            this.helpBox.Location = new System.Drawing.Point(12, 12);
            this.helpBox.Name = "helpBox";
            this.helpBox.Size = new System.Drawing.Size(502, 81);
            this.helpBox.TabIndex = 1;
            this.helpBox.TabStop = false;
            this.helpBox.Text = "Help";
            // 
            // helpLabel
            // 
            this.helpLabel.AutoSize = true;
            this.helpLabel.Location = new System.Drawing.Point(6, 25);
            this.helpLabel.Name = "helpLabel";
            this.helpLabel.Size = new System.Drawing.Size(297, 13);
            this.helpLabel.TabIndex = 0;
            this.helpLabel.Text = "Display the status of the inputs of the first board in the system.";
            // 
            // input1StatusBox
            // 
            this.input1StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input1StatusBox.Location = new System.Drawing.Point(68, 128);
            this.input1StatusBox.Name = "input1StatusBox";
            this.input1StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input1StatusBox.TabIndex = 2;
            this.input1StatusBox.TabStop = false;
            // 
            // input2StatusBox
            // 
            this.input2StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input2StatusBox.Location = new System.Drawing.Point(95, 128);
            this.input2StatusBox.Name = "input2StatusBox";
            this.input2StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input2StatusBox.TabIndex = 3;
            this.input2StatusBox.TabStop = false;
            // 
            // input3StatusBox
            // 
            this.input3StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input3StatusBox.Location = new System.Drawing.Point(122, 128);
            this.input3StatusBox.Name = "input3StatusBox";
            this.input3StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input3StatusBox.TabIndex = 4;
            this.input3StatusBox.TabStop = false;
            // 
            // input7StatusBox
            // 
            this.input7StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input7StatusBox.Location = new System.Drawing.Point(230, 128);
            this.input7StatusBox.Name = "input7StatusBox";
            this.input7StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input7StatusBox.TabIndex = 8;
            this.input7StatusBox.TabStop = false;
            // 
            // input6StatusBox
            // 
            this.input6StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input6StatusBox.Location = new System.Drawing.Point(203, 128);
            this.input6StatusBox.Name = "input6StatusBox";
            this.input6StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input6StatusBox.TabIndex = 7;
            this.input6StatusBox.TabStop = false;
            // 
            // input5StatusBox
            // 
            this.input5StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input5StatusBox.Location = new System.Drawing.Point(176, 128);
            this.input5StatusBox.Name = "input5StatusBox";
            this.input5StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input5StatusBox.TabIndex = 6;
            this.input5StatusBox.TabStop = false;
            // 
            // input4StatusBox
            // 
            this.input4StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input4StatusBox.Location = new System.Drawing.Point(149, 128);
            this.input4StatusBox.Name = "input4StatusBox";
            this.input4StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input4StatusBox.TabIndex = 5;
            this.input4StatusBox.TabStop = false;
            // 
            // input15StatusBox
            // 
            this.input15StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input15StatusBox.Location = new System.Drawing.Point(446, 128);
            this.input15StatusBox.Name = "input15StatusBox";
            this.input15StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input15StatusBox.TabIndex = 16;
            this.input15StatusBox.TabStop = false;
            // 
            // input14StatusBox
            // 
            this.input14StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input14StatusBox.Location = new System.Drawing.Point(419, 128);
            this.input14StatusBox.Name = "input14StatusBox";
            this.input14StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input14StatusBox.TabIndex = 15;
            this.input14StatusBox.TabStop = false;
            // 
            // input13StatusBox
            // 
            this.input13StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input13StatusBox.Location = new System.Drawing.Point(392, 128);
            this.input13StatusBox.Name = "input13StatusBox";
            this.input13StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input13StatusBox.TabIndex = 14;
            this.input13StatusBox.TabStop = false;
            // 
            // input12StatusBox
            // 
            this.input12StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input12StatusBox.Location = new System.Drawing.Point(365, 128);
            this.input12StatusBox.Name = "input12StatusBox";
            this.input12StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input12StatusBox.TabIndex = 13;
            this.input12StatusBox.TabStop = false;
            // 
            // input11StatusBox
            // 
            this.input11StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input11StatusBox.Location = new System.Drawing.Point(338, 128);
            this.input11StatusBox.Name = "input11StatusBox";
            this.input11StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input11StatusBox.TabIndex = 12;
            this.input11StatusBox.TabStop = false;
            // 
            // input10StatusBox
            // 
            this.input10StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input10StatusBox.Location = new System.Drawing.Point(311, 128);
            this.input10StatusBox.Name = "input10StatusBox";
            this.input10StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input10StatusBox.TabIndex = 11;
            this.input10StatusBox.TabStop = false;
            // 
            // input9StatusBox
            // 
            this.input9StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input9StatusBox.Location = new System.Drawing.Point(284, 128);
            this.input9StatusBox.Name = "input9StatusBox";
            this.input9StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input9StatusBox.TabIndex = 10;
            this.input9StatusBox.TabStop = false;
            // 
            // input8StatusBox
            // 
            this.input8StatusBox.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.input8StatusBox.Location = new System.Drawing.Point(257, 128);
            this.input8StatusBox.Name = "input8StatusBox";
            this.input8StatusBox.Size = new System.Drawing.Size(17, 16);
            this.input8StatusBox.TabIndex = 9;
            this.input8StatusBox.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(38, 112);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(13, 13);
            this.label1.TabIndex = 17;
            this.label1.Text = "0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(65, 112);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(13, 13);
            this.label2.TabIndex = 18;
            this.label2.Text = "1";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(92, 112);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(13, 13);
            this.label3.TabIndex = 19;
            this.label3.Text = "2";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(119, 112);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(13, 13);
            this.label4.TabIndex = 20;
            this.label4.Text = "3";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(146, 112);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(13, 13);
            this.label5.TabIndex = 21;
            this.label5.Text = "4";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(173, 112);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(13, 13);
            this.label6.TabIndex = 22;
            this.label6.Text = "5";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(200, 112);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(13, 13);
            this.label7.TabIndex = 23;
            this.label7.Text = "6";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(227, 112);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(13, 13);
            this.label8.TabIndex = 24;
            this.label8.Text = "7";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(254, 112);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(13, 13);
            this.label9.TabIndex = 25;
            this.label9.Text = "8";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(281, 112);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(13, 13);
            this.label10.TabIndex = 26;
            this.label10.Text = "9";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(308, 112);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(19, 13);
            this.label11.TabIndex = 27;
            this.label11.Text = "10";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(335, 112);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(19, 13);
            this.label12.TabIndex = 28;
            this.label12.Text = "11";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(362, 112);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(19, 13);
            this.label13.TabIndex = 29;
            this.label13.Text = "12";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(389, 112);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(19, 13);
            this.label14.TabIndex = 30;
            this.label14.Text = "13";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(416, 112);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(19, 13);
            this.label15.TabIndex = 31;
            this.label15.Text = "14";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(443, 112);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(19, 13);
            this.label16.TabIndex = 32;
            this.label16.Text = "15";
            // 
            // pictureBox16
            // 
            this.pictureBox16.Image = global::ReadDigitalInputs.Properties.Resources.led_off;
            this.pictureBox16.Location = new System.Drawing.Point(9, 52);
            this.pictureBox16.Name = "pictureBox16";
            this.pictureBox16.Size = new System.Drawing.Size(17, 16);
            this.pictureBox16.TabIndex = 1;
            this.pictureBox16.TabStop = false;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(32, 55);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(71, 13);
            this.label17.TabIndex = 2;
            this.label17.Text = "Status 0 (low)";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(211, 55);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(75, 13);
            this.label18.TabIndex = 4;
            this.label18.Text = "Status 1 (high)";
            // 
            // pictureBox17
            // 
            this.pictureBox17.Image = global::ReadDigitalInputs.Properties.Resources.led_on;
            this.pictureBox17.Location = new System.Drawing.Point(188, 52);
            this.pictureBox17.Name = "pictureBox17";
            this.pictureBox17.Size = new System.Drawing.Size(17, 16);
            this.pictureBox17.TabIndex = 3;
            this.pictureBox17.TabStop = false;
            // 
            // ReadDigitalInputs
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(526, 176);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.input15StatusBox);
            this.Controls.Add(this.input14StatusBox);
            this.Controls.Add(this.input13StatusBox);
            this.Controls.Add(this.input12StatusBox);
            this.Controls.Add(this.input11StatusBox);
            this.Controls.Add(this.input10StatusBox);
            this.Controls.Add(this.input9StatusBox);
            this.Controls.Add(this.input8StatusBox);
            this.Controls.Add(this.input7StatusBox);
            this.Controls.Add(this.input6StatusBox);
            this.Controls.Add(this.input5StatusBox);
            this.Controls.Add(this.input4StatusBox);
            this.Controls.Add(this.input3StatusBox);
            this.Controls.Add(this.input2StatusBox);
            this.Controls.Add(this.input1StatusBox);
            this.Controls.Add(this.helpBox);
            this.Controls.Add(this.input0StatusBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "ReadDigitalInputs";
            this.Text = "Sample: Read digital inputs";
            this.Load += new System.EventHandler(this.ReadDigitalInputs_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ReadDigitalInputs_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.input0StatusBox)).EndInit();
            this.helpBox.ResumeLayout(false);
            this.helpBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.input1StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input2StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input3StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input7StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input6StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input5StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input4StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input15StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input14StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input13StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input12StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input11StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input10StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input9StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.input8StatusBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox16)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox17)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer readTimer;
        private System.Windows.Forms.PictureBox input0StatusBox;
        private System.Windows.Forms.GroupBox helpBox;
        private System.Windows.Forms.Label helpLabel;
        private System.Windows.Forms.PictureBox input1StatusBox;
        private System.Windows.Forms.PictureBox input2StatusBox;
        private System.Windows.Forms.PictureBox input3StatusBox;
        private System.Windows.Forms.PictureBox input7StatusBox;
        private System.Windows.Forms.PictureBox input6StatusBox;
        private System.Windows.Forms.PictureBox input5StatusBox;
        private System.Windows.Forms.PictureBox input4StatusBox;
        private System.Windows.Forms.PictureBox input15StatusBox;
        private System.Windows.Forms.PictureBox input14StatusBox;
        private System.Windows.Forms.PictureBox input13StatusBox;
        private System.Windows.Forms.PictureBox input12StatusBox;
        private System.Windows.Forms.PictureBox input11StatusBox;
        private System.Windows.Forms.PictureBox input10StatusBox;
        private System.Windows.Forms.PictureBox input9StatusBox;
        private System.Windows.Forms.PictureBox input8StatusBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.PictureBox pictureBox17;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.PictureBox pictureBox16;
    }
}

