namespace VccCcInterrupt
{
    partial class VccCcInterrupt
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(VccCcInterrupt));
            this.helpGroupBox = new System.Windows.Forms.GroupBox();
            this.helpLabel = new System.Windows.Forms.Label();
            this.eventBox = new System.Windows.Forms.TextBox();
            this.helpGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // helpGroupBox
            // 
            this.helpGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.helpGroupBox.Controls.Add(this.helpLabel);
            this.helpGroupBox.Location = new System.Drawing.Point(12, 12);
            this.helpGroupBox.Name = "helpGroupBox";
            this.helpGroupBox.Size = new System.Drawing.Size(361, 64);
            this.helpGroupBox.TabIndex = 0;
            this.helpGroupBox.TabStop = false;
            this.helpGroupBox.Text = "Help";
            // 
            // helpLabel
            // 
            this.helpLabel.Location = new System.Drawing.Point(6, 16);
            this.helpLabel.Name = "helpLabel";
            this.helpLabel.Size = new System.Drawing.Size(338, 31);
            this.helpLabel.TabIndex = 0;
            this.helpLabel.Text = "Detect if the board loose the supply voltage, or if a short circuit on the output" +
                "s occurs.";
            // 
            // eventBox
            // 
            this.eventBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.eventBox.Location = new System.Drawing.Point(12, 82);
            this.eventBox.Multiline = true;
            this.eventBox.Name = "eventBox";
            this.eventBox.ReadOnly = true;
            this.eventBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.eventBox.Size = new System.Drawing.Size(361, 55);
            this.eventBox.TabIndex = 1;
            // 
            // VccCcInterrupt
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(385, 149);
            this.Controls.Add(this.eventBox);
            this.Controls.Add(this.helpGroupBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "VccCcInterrupt";
            this.Text = "Sample: voltage lost/short circuit detection";
            this.Load += new System.EventHandler(this.VccCcInterrupt_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.VccCcInterrupt_FormClosing);
            this.helpGroupBox.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox helpGroupBox;
        private System.Windows.Forms.Label helpLabel;
        private System.Windows.Forms.TextBox eventBox;
    }
}

