namespace TimerInterrupt
{
    partial class TimerInterrupt
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TimerInterrupt));
            this.counter2GroupBox = new System.Windows.Forms.GroupBox();
            this.timer2Trigger = new System.Windows.Forms.Button();
            this.timer2Stop = new System.Windows.Forms.Button();
            this.timer2Start = new System.Windows.Forms.Button();
            this.timer2Interrupt = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.timer2Value = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.counter1GroupBox = new System.Windows.Forms.GroupBox();
            this.timer1Trigger = new System.Windows.Forms.Button();
            this.timer1Stop = new System.Windows.Forms.Button();
            this.timer1Start = new System.Windows.Forms.Button();
            this.timer1Interrupt = new System.Windows.Forms.Label();
            this.counter1InterruptLabel = new System.Windows.Forms.Label();
            this.timer1Value = new System.Windows.Forms.Label();
            this.counter1ValueLabel = new System.Windows.Forms.Label();
            this.timer1DisplayTimer = new System.Windows.Forms.Timer(this.components);
            this.timer2DisplayTimer = new System.Windows.Forms.Timer(this.components);
            this.counter2GroupBox.SuspendLayout();
            this.counter1GroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // counter2GroupBox
            // 
            this.counter2GroupBox.Controls.Add(this.timer2Trigger);
            this.counter2GroupBox.Controls.Add(this.timer2Stop);
            this.counter2GroupBox.Controls.Add(this.timer2Start);
            this.counter2GroupBox.Controls.Add(this.timer2Interrupt);
            this.counter2GroupBox.Controls.Add(this.label2);
            this.counter2GroupBox.Controls.Add(this.timer2Value);
            this.counter2GroupBox.Controls.Add(this.label4);
            this.counter2GroupBox.Location = new System.Drawing.Point(268, 12);
            this.counter2GroupBox.Name = "counter2GroupBox";
            this.counter2GroupBox.Size = new System.Drawing.Size(251, 123);
            this.counter2GroupBox.TabIndex = 3;
            this.counter2GroupBox.TabStop = false;
            this.counter2GroupBox.Text = "Timer 2";
            // 
            // timer2Trigger
            // 
            this.timer2Trigger.Enabled = false;
            this.timer2Trigger.Location = new System.Drawing.Point(168, 85);
            this.timer2Trigger.Name = "timer2Trigger";
            this.timer2Trigger.Size = new System.Drawing.Size(75, 23);
            this.timer2Trigger.TabIndex = 8;
            this.timer2Trigger.Text = "Trigger";
            this.timer2Trigger.UseVisualStyleBackColor = true;
            this.timer2Trigger.Click += new System.EventHandler(this.timer2Trigger_Click);
            // 
            // timer2Stop
            // 
            this.timer2Stop.Enabled = false;
            this.timer2Stop.Location = new System.Drawing.Point(87, 85);
            this.timer2Stop.Name = "timer2Stop";
            this.timer2Stop.Size = new System.Drawing.Size(75, 23);
            this.timer2Stop.TabIndex = 7;
            this.timer2Stop.Text = "Stop";
            this.timer2Stop.UseVisualStyleBackColor = true;
            this.timer2Stop.Click += new System.EventHandler(this.timer2Stop_Click);
            // 
            // timer2Start
            // 
            this.timer2Start.Location = new System.Drawing.Point(6, 85);
            this.timer2Start.Name = "timer2Start";
            this.timer2Start.Size = new System.Drawing.Size(75, 23);
            this.timer2Start.TabIndex = 6;
            this.timer2Start.Text = "Start";
            this.timer2Start.UseVisualStyleBackColor = true;
            this.timer2Start.Click += new System.EventHandler(this.timer2Start_Click);
            // 
            // timer2Interrupt
            // 
            this.timer2Interrupt.AutoSize = true;
            this.timer2Interrupt.Location = new System.Drawing.Point(108, 58);
            this.timer2Interrupt.Name = "timer2Interrupt";
            this.timer2Interrupt.Size = new System.Drawing.Size(13, 13);
            this.timer2Interrupt.TabIndex = 5;
            this.timer2Interrupt.Text = "0";
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
            // timer2Value
            // 
            this.timer2Value.AutoSize = true;
            this.timer2Value.Location = new System.Drawing.Point(108, 32);
            this.timer2Value.Name = "timer2Value";
            this.timer2Value.Size = new System.Drawing.Size(13, 13);
            this.timer2Value.TabIndex = 1;
            this.timer2Value.Text = "0";
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
            // counter1GroupBox
            // 
            this.counter1GroupBox.Controls.Add(this.timer1Trigger);
            this.counter1GroupBox.Controls.Add(this.timer1Stop);
            this.counter1GroupBox.Controls.Add(this.timer1Start);
            this.counter1GroupBox.Controls.Add(this.timer1Interrupt);
            this.counter1GroupBox.Controls.Add(this.counter1InterruptLabel);
            this.counter1GroupBox.Controls.Add(this.timer1Value);
            this.counter1GroupBox.Controls.Add(this.counter1ValueLabel);
            this.counter1GroupBox.Location = new System.Drawing.Point(12, 12);
            this.counter1GroupBox.Name = "counter1GroupBox";
            this.counter1GroupBox.Size = new System.Drawing.Size(251, 123);
            this.counter1GroupBox.TabIndex = 2;
            this.counter1GroupBox.TabStop = false;
            this.counter1GroupBox.Text = "Timer 1";
            // 
            // timer1Trigger
            // 
            this.timer1Trigger.Enabled = false;
            this.timer1Trigger.Location = new System.Drawing.Point(168, 85);
            this.timer1Trigger.Name = "timer1Trigger";
            this.timer1Trigger.Size = new System.Drawing.Size(75, 23);
            this.timer1Trigger.TabIndex = 8;
            this.timer1Trigger.Text = "Trigger";
            this.timer1Trigger.UseVisualStyleBackColor = true;
            this.timer1Trigger.Click += new System.EventHandler(this.timer1Trigger_Click);
            // 
            // timer1Stop
            // 
            this.timer1Stop.Enabled = false;
            this.timer1Stop.Location = new System.Drawing.Point(87, 85);
            this.timer1Stop.Name = "timer1Stop";
            this.timer1Stop.Size = new System.Drawing.Size(75, 23);
            this.timer1Stop.TabIndex = 7;
            this.timer1Stop.Text = "Stop";
            this.timer1Stop.UseVisualStyleBackColor = true;
            this.timer1Stop.Click += new System.EventHandler(this.timer1Stop_Click);
            // 
            // timer1Start
            // 
            this.timer1Start.Location = new System.Drawing.Point(6, 85);
            this.timer1Start.Name = "timer1Start";
            this.timer1Start.Size = new System.Drawing.Size(75, 23);
            this.timer1Start.TabIndex = 6;
            this.timer1Start.Text = "Start";
            this.timer1Start.UseVisualStyleBackColor = true;
            this.timer1Start.Click += new System.EventHandler(this.timer1Start_Click);
            // 
            // timer1Interrupt
            // 
            this.timer1Interrupt.AutoSize = true;
            this.timer1Interrupt.Location = new System.Drawing.Point(108, 58);
            this.timer1Interrupt.Name = "timer1Interrupt";
            this.timer1Interrupt.Size = new System.Drawing.Size(13, 13);
            this.timer1Interrupt.TabIndex = 5;
            this.timer1Interrupt.Text = "0";
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
            // timer1Value
            // 
            this.timer1Value.AutoSize = true;
            this.timer1Value.Location = new System.Drawing.Point(108, 32);
            this.timer1Value.Name = "timer1Value";
            this.timer1Value.Size = new System.Drawing.Size(13, 13);
            this.timer1Value.TabIndex = 1;
            this.timer1Value.Text = "0";
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
            // timer1DisplayTimer
            // 
            this.timer1DisplayTimer.Interval = 50;
            this.timer1DisplayTimer.Tick += new System.EventHandler(this.timer1DisplayTimer_Tick);
            // 
            // timer2DisplayTimer
            // 
            this.timer2DisplayTimer.Interval = 50;
            this.timer2DisplayTimer.Tick += new System.EventHandler(this.timer2DisplayTimer_Tick);
            // 
            // TimerInterrupt
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(529, 143);
            this.Controls.Add(this.counter2GroupBox);
            this.Controls.Add(this.counter1GroupBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "TimerInterrupt";
            this.Text = "Sample: Timer with interrupt";
            this.Load += new System.EventHandler(this.TimerInterrupt_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.TimerInterrupt_FormClosing);
            this.counter2GroupBox.ResumeLayout(false);
            this.counter2GroupBox.PerformLayout();
            this.counter1GroupBox.ResumeLayout(false);
            this.counter1GroupBox.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox counter2GroupBox;
        private System.Windows.Forms.Button timer2Trigger;
        private System.Windows.Forms.Button timer2Stop;
        private System.Windows.Forms.Button timer2Start;
        private System.Windows.Forms.Label timer2Interrupt;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label timer2Value;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox counter1GroupBox;
        private System.Windows.Forms.Button timer1Trigger;
        private System.Windows.Forms.Button timer1Stop;
        private System.Windows.Forms.Button timer1Start;
        private System.Windows.Forms.Label timer1Interrupt;
        private System.Windows.Forms.Label counter1InterruptLabel;
        private System.Windows.Forms.Label timer1Value;
        private System.Windows.Forms.Label counter1ValueLabel;
        private System.Windows.Forms.Timer timer1DisplayTimer;
        private System.Windows.Forms.Timer timer2DisplayTimer;
    }
}

