namespace CounterInterrupt
{
    partial class CounterInterrupt
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CounterInterrupt));
            this.counter1GroupBox = new System.Windows.Forms.GroupBox();
            this.counter1Trigger = new System.Windows.Forms.Button();
            this.counter1Stop = new System.Windows.Forms.Button();
            this.counter1Start = new System.Windows.Forms.Button();
            this.counter1Interrupt = new System.Windows.Forms.Label();
            this.counter1InterruptLabel = new System.Windows.Forms.Label();
            this.counter1Value = new System.Windows.Forms.Label();
            this.counter1ValueLabel = new System.Windows.Forms.Label();
            this.counter1DisplayTimer = new System.Windows.Forms.Timer(this.components);
            this.counter2GroupBox = new System.Windows.Forms.GroupBox();
            this.counter2Trigger = new System.Windows.Forms.Button();
            this.counter2Stop = new System.Windows.Forms.Button();
            this.counter2Start = new System.Windows.Forms.Button();
            this.counter2Interrupt = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.counter2Value = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.counter3Trigger = new System.Windows.Forms.Button();
            this.counter3Stop = new System.Windows.Forms.Button();
            this.counter3Start = new System.Windows.Forms.Button();
            this.counter3Interrupt = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.counter3Value = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.counter2DisplayTimer = new System.Windows.Forms.Timer(this.components);
            this.counter3DisplayTimer = new System.Windows.Forms.Timer(this.components);
            this.counter1GroupBox.SuspendLayout();
            this.counter2GroupBox.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // counter1GroupBox
            // 
            this.counter1GroupBox.Controls.Add(this.counter1Trigger);
            this.counter1GroupBox.Controls.Add(this.counter1Stop);
            this.counter1GroupBox.Controls.Add(this.counter1Start);
            this.counter1GroupBox.Controls.Add(this.counter1Interrupt);
            this.counter1GroupBox.Controls.Add(this.counter1InterruptLabel);
            this.counter1GroupBox.Controls.Add(this.counter1Value);
            this.counter1GroupBox.Controls.Add(this.counter1ValueLabel);
            this.counter1GroupBox.Location = new System.Drawing.Point(12, 12);
            this.counter1GroupBox.Name = "counter1GroupBox";
            this.counter1GroupBox.Size = new System.Drawing.Size(251, 123);
            this.counter1GroupBox.TabIndex = 0;
            this.counter1GroupBox.TabStop = false;
            this.counter1GroupBox.Text = "Counter 1 : Input 14";
            // 
            // counter1Trigger
            // 
            this.counter1Trigger.Enabled = false;
            this.counter1Trigger.Location = new System.Drawing.Point(168, 85);
            this.counter1Trigger.Name = "counter1Trigger";
            this.counter1Trigger.Size = new System.Drawing.Size(75, 23);
            this.counter1Trigger.TabIndex = 8;
            this.counter1Trigger.Text = "Trigger";
            this.counter1Trigger.UseVisualStyleBackColor = true;
            this.counter1Trigger.Click += new System.EventHandler(this.counter1Trigger_Click);
            // 
            // counter1Stop
            // 
            this.counter1Stop.Enabled = false;
            this.counter1Stop.Location = new System.Drawing.Point(87, 85);
            this.counter1Stop.Name = "counter1Stop";
            this.counter1Stop.Size = new System.Drawing.Size(75, 23);
            this.counter1Stop.TabIndex = 7;
            this.counter1Stop.Text = "Stop";
            this.counter1Stop.UseVisualStyleBackColor = true;
            this.counter1Stop.Click += new System.EventHandler(this.counter1Stop_Click);
            // 
            // counter1Start
            // 
            this.counter1Start.Location = new System.Drawing.Point(6, 85);
            this.counter1Start.Name = "counter1Start";
            this.counter1Start.Size = new System.Drawing.Size(75, 23);
            this.counter1Start.TabIndex = 6;
            this.counter1Start.Text = "Start";
            this.counter1Start.UseVisualStyleBackColor = true;
            this.counter1Start.Click += new System.EventHandler(this.counter1Start_Click);
            // 
            // counter1Interrupt
            // 
            this.counter1Interrupt.AutoSize = true;
            this.counter1Interrupt.Location = new System.Drawing.Point(108, 58);
            this.counter1Interrupt.Name = "counter1Interrupt";
            this.counter1Interrupt.Size = new System.Drawing.Size(13, 13);
            this.counter1Interrupt.TabIndex = 5;
            this.counter1Interrupt.Text = "0";
            // 
            // counter1InterruptLabel
            // 
            this.counter1InterruptLabel.AutoSize = true;
            this.counter1InterruptLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.counter1InterruptLabel.Location = new System.Drawing.Point(6, 58);
            this.counter1InterruptLabel.Name = "counter1InterruptLabel";
            this.counter1InterruptLabel.Size = new System.Drawing.Size(55, 13);
            this.counter1InterruptLabel.TabIndex = 4;
            this.counter1InterruptLabel.Text = "Interrupt";
            // 
            // counter1Value
            // 
            this.counter1Value.AutoSize = true;
            this.counter1Value.Location = new System.Drawing.Point(108, 32);
            this.counter1Value.Name = "counter1Value";
            this.counter1Value.Size = new System.Drawing.Size(13, 13);
            this.counter1Value.TabIndex = 1;
            this.counter1Value.Text = "0";
            // 
            // counter1ValueLabel
            // 
            this.counter1ValueLabel.AutoSize = true;
            this.counter1ValueLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.counter1ValueLabel.Location = new System.Drawing.Point(6, 32);
            this.counter1ValueLabel.Name = "counter1ValueLabel";
            this.counter1ValueLabel.Size = new System.Drawing.Size(39, 13);
            this.counter1ValueLabel.TabIndex = 0;
            this.counter1ValueLabel.Text = "Value";
            // 
            // counter1DisplayTimer
            // 
            this.counter1DisplayTimer.Tick += new System.EventHandler(this.counter1DisplayTimer_Tick);
            // 
            // counter2GroupBox
            // 
            this.counter2GroupBox.Controls.Add(this.counter2Trigger);
            this.counter2GroupBox.Controls.Add(this.counter2Stop);
            this.counter2GroupBox.Controls.Add(this.counter2Start);
            this.counter2GroupBox.Controls.Add(this.counter2Interrupt);
            this.counter2GroupBox.Controls.Add(this.label2);
            this.counter2GroupBox.Controls.Add(this.counter2Value);
            this.counter2GroupBox.Controls.Add(this.label4);
            this.counter2GroupBox.Location = new System.Drawing.Point(268, 12);
            this.counter2GroupBox.Name = "counter2GroupBox";
            this.counter2GroupBox.Size = new System.Drawing.Size(251, 123);
            this.counter2GroupBox.TabIndex = 1;
            this.counter2GroupBox.TabStop = false;
            this.counter2GroupBox.Text = "Counter 2 : Input 10";
            // 
            // counter2Trigger
            // 
            this.counter2Trigger.Enabled = false;
            this.counter2Trigger.Location = new System.Drawing.Point(168, 85);
            this.counter2Trigger.Name = "counter2Trigger";
            this.counter2Trigger.Size = new System.Drawing.Size(75, 23);
            this.counter2Trigger.TabIndex = 8;
            this.counter2Trigger.Text = "Trigger";
            this.counter2Trigger.UseVisualStyleBackColor = true;
            this.counter2Trigger.Click += new System.EventHandler(this.counter2Trigger_Click);
            // 
            // counter2Stop
            // 
            this.counter2Stop.Enabled = false;
            this.counter2Stop.Location = new System.Drawing.Point(87, 85);
            this.counter2Stop.Name = "counter2Stop";
            this.counter2Stop.Size = new System.Drawing.Size(75, 23);
            this.counter2Stop.TabIndex = 7;
            this.counter2Stop.Text = "Stop";
            this.counter2Stop.UseVisualStyleBackColor = true;
            this.counter2Stop.Click += new System.EventHandler(this.counter2Stop_Click);
            // 
            // counter2Start
            // 
            this.counter2Start.Location = new System.Drawing.Point(6, 85);
            this.counter2Start.Name = "counter2Start";
            this.counter2Start.Size = new System.Drawing.Size(75, 23);
            this.counter2Start.TabIndex = 6;
            this.counter2Start.Text = "Start";
            this.counter2Start.UseVisualStyleBackColor = true;
            this.counter2Start.Click += new System.EventHandler(this.counter2Start_Click);
            // 
            // counter2Interrupt
            // 
            this.counter2Interrupt.AutoSize = true;
            this.counter2Interrupt.Location = new System.Drawing.Point(108, 58);
            this.counter2Interrupt.Name = "counter2Interrupt";
            this.counter2Interrupt.Size = new System.Drawing.Size(13, 13);
            this.counter2Interrupt.TabIndex = 5;
            this.counter2Interrupt.Text = "0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(6, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(55, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Interrupt";
            // 
            // counter2Value
            // 
            this.counter2Value.AutoSize = true;
            this.counter2Value.Location = new System.Drawing.Point(108, 32);
            this.counter2Value.Name = "counter2Value";
            this.counter2Value.Size = new System.Drawing.Size(13, 13);
            this.counter2Value.TabIndex = 1;
            this.counter2Value.Text = "0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(6, 32);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(39, 13);
            this.label4.TabIndex = 0;
            this.label4.Text = "Value";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.counter3Trigger);
            this.groupBox2.Controls.Add(this.counter3Stop);
            this.groupBox2.Controls.Add(this.counter3Start);
            this.groupBox2.Controls.Add(this.counter3Interrupt);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.counter3Value);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Location = new System.Drawing.Point(525, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(251, 123);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Counter 3 : Input 15";
            // 
            // counter3Trigger
            // 
            this.counter3Trigger.Enabled = false;
            this.counter3Trigger.Location = new System.Drawing.Point(168, 85);
            this.counter3Trigger.Name = "counter3Trigger";
            this.counter3Trigger.Size = new System.Drawing.Size(75, 23);
            this.counter3Trigger.TabIndex = 8;
            this.counter3Trigger.Text = "Trigger";
            this.counter3Trigger.UseVisualStyleBackColor = true;
            this.counter3Trigger.Click += new System.EventHandler(this.counter3Trigger_Click);
            // 
            // counter3Stop
            // 
            this.counter3Stop.Enabled = false;
            this.counter3Stop.Location = new System.Drawing.Point(87, 85);
            this.counter3Stop.Name = "counter3Stop";
            this.counter3Stop.Size = new System.Drawing.Size(75, 23);
            this.counter3Stop.TabIndex = 7;
            this.counter3Stop.Text = "Stop";
            this.counter3Stop.UseVisualStyleBackColor = true;
            this.counter3Stop.Click += new System.EventHandler(this.counter3Stop_Click);
            // 
            // counter3Start
            // 
            this.counter3Start.Location = new System.Drawing.Point(6, 85);
            this.counter3Start.Name = "counter3Start";
            this.counter3Start.Size = new System.Drawing.Size(75, 23);
            this.counter3Start.TabIndex = 6;
            this.counter3Start.Text = "Start";
            this.counter3Start.UseVisualStyleBackColor = true;
            this.counter3Start.Click += new System.EventHandler(this.counter3Start_Click);
            // 
            // counter3Interrupt
            // 
            this.counter3Interrupt.AutoSize = true;
            this.counter3Interrupt.Location = new System.Drawing.Point(108, 58);
            this.counter3Interrupt.Name = "counter3Interrupt";
            this.counter3Interrupt.Size = new System.Drawing.Size(13, 13);
            this.counter3Interrupt.TabIndex = 5;
            this.counter3Interrupt.Text = "0";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(6, 58);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(55, 13);
            this.label6.TabIndex = 4;
            this.label6.Text = "Interrupt";
            // 
            // counter3Value
            // 
            this.counter3Value.AutoSize = true;
            this.counter3Value.Location = new System.Drawing.Point(108, 32);
            this.counter3Value.Name = "counter3Value";
            this.counter3Value.Size = new System.Drawing.Size(13, 13);
            this.counter3Value.TabIndex = 1;
            this.counter3Value.Text = "0";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(6, 32);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(39, 13);
            this.label8.TabIndex = 0;
            this.label8.Text = "Value";
            // 
            // counter2DisplayTimer
            // 
            this.counter2DisplayTimer.Tick += new System.EventHandler(this.counter2DisplayTimer_Tick);
            // 
            // counter3DisplayTimer
            // 
            this.counter3DisplayTimer.Tick += new System.EventHandler(this.counter3DisplayTimer_Tick);
            // 
            // CounterInterrupt
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(786, 147);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.counter2GroupBox);
            this.Controls.Add(this.counter1GroupBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "CounterInterrupt";
            this.Text = "Sample: Counter with interrupt";
            this.Load += new System.EventHandler(this.CounterInterrupt_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.CounterInterrupt_FormClosing);
            this.counter1GroupBox.ResumeLayout(false);
            this.counter1GroupBox.PerformLayout();
            this.counter2GroupBox.ResumeLayout(false);
            this.counter2GroupBox.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox counter1GroupBox;
        private System.Windows.Forms.Label counter1ValueLabel;
        private System.Windows.Forms.Label counter1Value;
        private System.Windows.Forms.Label counter1InterruptLabel;
        private System.Windows.Forms.Label counter1Interrupt;
        private System.Windows.Forms.Button counter1Stop;
        private System.Windows.Forms.Button counter1Start;
        private System.Windows.Forms.Button counter1Trigger;
        private System.Windows.Forms.Timer counter1DisplayTimer;
        private System.Windows.Forms.GroupBox counter2GroupBox;
        private System.Windows.Forms.Button counter2Trigger;
        private System.Windows.Forms.Button counter2Stop;
        private System.Windows.Forms.Button counter2Start;
        private System.Windows.Forms.Label counter2Interrupt;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label counter2Value;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button counter3Trigger;
        private System.Windows.Forms.Button counter3Stop;
        private System.Windows.Forms.Button counter3Start;
        private System.Windows.Forms.Label counter3Interrupt;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label counter3Value;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Timer counter2DisplayTimer;
        private System.Windows.Forms.Timer counter3DisplayTimer;
    }
}

