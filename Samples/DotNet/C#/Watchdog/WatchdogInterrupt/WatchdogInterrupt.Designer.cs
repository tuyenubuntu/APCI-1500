namespace WatchdogInterrupt
{
    partial class WatchdogInterruptForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(WatchdogInterruptForm));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.setOutputButton = new System.Windows.Forms.Button();
            this.watchdogTrigger = new System.Windows.Forms.Button();
            this.watchdogStop = new System.Windows.Forms.Button();
            this.watchdogStart = new System.Windows.Forms.Button();
            this.watchdogInterrupt = new System.Windows.Forms.Label();
            this.counter1InterruptLabel = new System.Windows.Forms.Label();
            this.watchdogValue = new System.Windows.Forms.Label();
            this.counter1ValueLabel = new System.Windows.Forms.Label();
            this.watchdogDisplayTimer = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.setOutputButton);
            this.groupBox1.Controls.Add(this.watchdogTrigger);
            this.groupBox1.Controls.Add(this.watchdogStop);
            this.groupBox1.Controls.Add(this.watchdogStart);
            this.groupBox1.Controls.Add(this.watchdogInterrupt);
            this.groupBox1.Controls.Add(this.counter1InterruptLabel);
            this.groupBox1.Controls.Add(this.watchdogValue);
            this.groupBox1.Controls.Add(this.counter1ValueLabel);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(389, 111);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Watchdog";
            // 
            // setOutputButton
            // 
            this.setOutputButton.Location = new System.Drawing.Point(249, 82);
            this.setOutputButton.Name = "setOutputButton";
            this.setOutputButton.Size = new System.Drawing.Size(133, 23);
            this.setOutputButton.TabIndex = 16;
            this.setOutputButton.Text = "Set all the outputs to 1";
            this.setOutputButton.UseVisualStyleBackColor = true;
            this.setOutputButton.Click += new System.EventHandler(this.setOutputButton_Click);
            // 
            // watchdogTrigger
            // 
            this.watchdogTrigger.Enabled = false;
            this.watchdogTrigger.Location = new System.Drawing.Point(168, 82);
            this.watchdogTrigger.Name = "watchdogTrigger";
            this.watchdogTrigger.Size = new System.Drawing.Size(75, 23);
            this.watchdogTrigger.TabIndex = 15;
            this.watchdogTrigger.Text = "Trigger";
            this.watchdogTrigger.UseVisualStyleBackColor = true;
            this.watchdogTrigger.Click += new System.EventHandler(this.watchdogTrigger_Click);
            // 
            // watchdogStop
            // 
            this.watchdogStop.Enabled = false;
            this.watchdogStop.Location = new System.Drawing.Point(87, 82);
            this.watchdogStop.Name = "watchdogStop";
            this.watchdogStop.Size = new System.Drawing.Size(75, 23);
            this.watchdogStop.TabIndex = 14;
            this.watchdogStop.Text = "Stop";
            this.watchdogStop.UseVisualStyleBackColor = true;
            this.watchdogStop.Click += new System.EventHandler(this.watchdogStop_Click);
            // 
            // watchdogStart
            // 
            this.watchdogStart.Location = new System.Drawing.Point(6, 82);
            this.watchdogStart.Name = "watchdogStart";
            this.watchdogStart.Size = new System.Drawing.Size(75, 23);
            this.watchdogStart.TabIndex = 13;
            this.watchdogStart.Text = "Start";
            this.watchdogStart.UseVisualStyleBackColor = true;
            this.watchdogStart.Click += new System.EventHandler(this.watchdogStart_Click);
            // 
            // watchdogInterrupt
            // 
            this.watchdogInterrupt.AutoSize = true;
            this.watchdogInterrupt.Location = new System.Drawing.Point(108, 55);
            this.watchdogInterrupt.Name = "watchdogInterrupt";
            this.watchdogInterrupt.Size = new System.Drawing.Size(13, 13);
            this.watchdogInterrupt.TabIndex = 12;
            this.watchdogInterrupt.Text = "0";
            // 
            // counter1InterruptLabel
            // 
            this.counter1InterruptLabel.AutoSize = true;
            this.counter1InterruptLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.counter1InterruptLabel.Location = new System.Drawing.Point(6, 55);
            this.counter1InterruptLabel.Name = "counter1InterruptLabel";
            this.counter1InterruptLabel.Size = new System.Drawing.Size(55, 13);
            this.counter1InterruptLabel.TabIndex = 11;
            this.counter1InterruptLabel.Text = "Interrupt";
            // 
            // watchdogValue
            // 
            this.watchdogValue.AutoSize = true;
            this.watchdogValue.Location = new System.Drawing.Point(108, 29);
            this.watchdogValue.Name = "watchdogValue";
            this.watchdogValue.Size = new System.Drawing.Size(13, 13);
            this.watchdogValue.TabIndex = 10;
            this.watchdogValue.Text = "0";
            // 
            // counter1ValueLabel
            // 
            this.counter1ValueLabel.AutoSize = true;
            this.counter1ValueLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.counter1ValueLabel.Location = new System.Drawing.Point(6, 29);
            this.counter1ValueLabel.Name = "counter1ValueLabel";
            this.counter1ValueLabel.Size = new System.Drawing.Size(39, 13);
            this.counter1ValueLabel.TabIndex = 9;
            this.counter1ValueLabel.Text = "Value";
            // 
            // watchdogDisplayTimer
            // 
            this.watchdogDisplayTimer.Tick += new System.EventHandler(this.watchdogDisplayTimer_Tick);
            // 
            // WatchdogInterruptForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(406, 135);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "WatchdogInterruptForm";
            this.Text = "Sample: Watchdog with interrupt";
            this.Load += new System.EventHandler(this.WatchdogInterruptForm_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.WatchdogInterruptForm_FormClosing);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button watchdogTrigger;
        private System.Windows.Forms.Button watchdogStop;
        private System.Windows.Forms.Button watchdogStart;
        private System.Windows.Forms.Label watchdogInterrupt;
        private System.Windows.Forms.Label counter1InterruptLabel;
        private System.Windows.Forms.Label watchdogValue;
        private System.Windows.Forms.Label counter1ValueLabel;
        private System.Windows.Forms.Timer watchdogDisplayTimer;
        private System.Windows.Forms.Button setOutputButton;
    }
}

