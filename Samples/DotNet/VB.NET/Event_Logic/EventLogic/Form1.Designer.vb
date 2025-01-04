<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class EventLogic
	Inherits System.Windows.Forms.Form
	
    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
	Protected Overrides Sub Dispose(disposing As Boolean)
		If disposing AndAlso (components IsNot Nothing) Then
			components.Dispose()
		End If
		MyBase.Dispose(disposing)
	End Sub

	
	   'Required by the Windows Form Designer
	Private components As System.ComponentModel.IContainer = Nothing

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
	Private Sub InitializeComponent()
		Dim resources As New System.ComponentModel.ComponentResourceManager(GetType(EventLogic))
		Me.portAGroupBox = New System.Windows.Forms.GroupBox()
		Me.channelLogic0 = New System.Windows.Forms.ComboBox()
		Me.channelLogic1 = New System.Windows.Forms.ComboBox()
		Me.channelLogic2 = New System.Windows.Forms.ComboBox()
		Me.channelLogic3 = New System.Windows.Forms.ComboBox()
		Me.channelLogic4 = New System.Windows.Forms.ComboBox()
		Me.channelLogic5 = New System.Windows.Forms.ComboBox()
		Me.channelLogic6 = New System.Windows.Forms.ComboBox()
		Me.channelLogic7 = New System.Windows.Forms.ComboBox()
		Me.label1 = New System.Windows.Forms.Label()
		Me.label2 = New System.Windows.Forms.Label()
		Me.label3 = New System.Windows.Forms.Label()
		Me.label4 = New System.Windows.Forms.Label()
		Me.label5 = New System.Windows.Forms.Label()
		Me.label6 = New System.Windows.Forms.Label()
		Me.label7 = New System.Windows.Forms.Label()
		Me.label8 = New System.Windows.Forms.Label()
		Me.startPortALogic = New System.Windows.Forms.Button()
		Me.stopPortALogic = New System.Windows.Forms.Button()
		Me.logicType = New System.Windows.Forms.ComboBox()
		Me.label9 = New System.Windows.Forms.Label()
		Me.eventBox = New System.Windows.Forms.TextBox()
		Me.helpBox = New System.Windows.Forms.GroupBox()
		Me.label10 = New System.Windows.Forms.Label()
		Me.label11 = New System.Windows.Forms.Label()
		Me.label12 = New System.Windows.Forms.Label()
		Me.label13 = New System.Windows.Forms.Label()
		Me.label14 = New System.Windows.Forms.Label()
		Me.label15 = New System.Windows.Forms.Label()
		Me.label16 = New System.Windows.Forms.Label()
		Me.portBGroupBox = New System.Windows.Forms.GroupBox()
		Me.label17 = New System.Windows.Forms.Label()
		Me.label18 = New System.Windows.Forms.Label()
		Me.label19 = New System.Windows.Forms.Label()
		Me.label20 = New System.Windows.Forms.Label()
		Me.label21 = New System.Windows.Forms.Label()
		Me.label22 = New System.Windows.Forms.Label()
		Me.channelLogic13 = New System.Windows.Forms.ComboBox()
		Me.channelLogic12 = New System.Windows.Forms.ComboBox()
		Me.channelLogic11 = New System.Windows.Forms.ComboBox()
		Me.channelLogic10 = New System.Windows.Forms.ComboBox()
		Me.channelLogic9 = New System.Windows.Forms.ComboBox()
		Me.channelLogic8 = New System.Windows.Forms.ComboBox()
		Me.stopPortBLogic = New System.Windows.Forms.Button()
		Me.startPortBLogic = New System.Windows.Forms.Button()
		Me.portAGroupBox.SuspendLayout()
		Me.helpBox.SuspendLayout()
		Me.portBGroupBox.SuspendLayout()
		Me.SuspendLayout()
		' 
		' portAGroupBox
		' 
		Me.portAGroupBox.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.portAGroupBox.Controls.Add(Me.label9)
		Me.portAGroupBox.Controls.Add(Me.logicType)
		Me.portAGroupBox.Controls.Add(Me.stopPortALogic)
		Me.portAGroupBox.Controls.Add(Me.startPortALogic)
		Me.portAGroupBox.Controls.Add(Me.label8)
		Me.portAGroupBox.Controls.Add(Me.label7)
		Me.portAGroupBox.Controls.Add(Me.label6)
		Me.portAGroupBox.Controls.Add(Me.label5)
		Me.portAGroupBox.Controls.Add(Me.label4)
		Me.portAGroupBox.Controls.Add(Me.label3)
		Me.portAGroupBox.Controls.Add(Me.label2)
		Me.portAGroupBox.Controls.Add(Me.label1)
		Me.portAGroupBox.Controls.Add(Me.channelLogic7)
		Me.portAGroupBox.Controls.Add(Me.channelLogic6)
		Me.portAGroupBox.Controls.Add(Me.channelLogic5)
		Me.portAGroupBox.Controls.Add(Me.channelLogic4)
		Me.portAGroupBox.Controls.Add(Me.channelLogic3)
		Me.portAGroupBox.Controls.Add(Me.channelLogic2)
		Me.portAGroupBox.Controls.Add(Me.channelLogic1)
		Me.portAGroupBox.Controls.Add(Me.channelLogic0)
		Me.portAGroupBox.Location = New System.Drawing.Point(12, 153)
		Me.portAGroupBox.Name = "portAGroupBox"
		Me.portAGroupBox.Size = New System.Drawing.Size(770, 77)
		Me.portAGroupBox.TabIndex = 0
		Me.portAGroupBox.TabStop = False
		Me.portAGroupBox.Text = "Port A"
		' 
		' channelLogic0
		' 
		Me.channelLogic0.FormattingEnabled = True
		Me.channelLogic0.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic0.Location = New System.Drawing.Point(6, 35)
		Me.channelLogic0.Name = "channelLogic0"
		Me.channelLogic0.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic0.TabIndex = 0
		' 
		' channelLogic1
		' 
		Me.channelLogic1.FormattingEnabled = True
		Me.channelLogic1.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic1.Location = New System.Drawing.Point(57, 35)
		Me.channelLogic1.Name = "channelLogic1"
		Me.channelLogic1.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic1.TabIndex = 1
		' 
		' channelLogic2
		' 
		Me.channelLogic2.FormattingEnabled = True
		Me.channelLogic2.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic2.Location = New System.Drawing.Point(108, 35)
		Me.channelLogic2.Name = "channelLogic2"
		Me.channelLogic2.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic2.TabIndex = 2
		' 
		' channelLogic3
		' 
		Me.channelLogic3.FormattingEnabled = True
		Me.channelLogic3.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic3.Location = New System.Drawing.Point(159, 35)
		Me.channelLogic3.Name = "channelLogic3"
		Me.channelLogic3.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic3.TabIndex = 3
		' 
		' channelLogic4
		' 
		Me.channelLogic4.FormattingEnabled = True
		Me.channelLogic4.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic4.Location = New System.Drawing.Point(210, 35)
		Me.channelLogic4.Name = "channelLogic4"
		Me.channelLogic4.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic4.TabIndex = 4
		' 
		' channelLogic5
		' 
		Me.channelLogic5.FormattingEnabled = True
		Me.channelLogic5.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic5.Location = New System.Drawing.Point(261, 35)
		Me.channelLogic5.Name = "channelLogic5"
		Me.channelLogic5.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic5.TabIndex = 5
		' 
		' channelLogic6
		' 
		Me.channelLogic6.FormattingEnabled = True
		Me.channelLogic6.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic6.Location = New System.Drawing.Point(312, 35)
		Me.channelLogic6.Name = "channelLogic6"
		Me.channelLogic6.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic6.TabIndex = 6
		' 
		' channelLogic7
		' 
		Me.channelLogic7.FormattingEnabled = True
		Me.channelLogic7.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic7.Location = New System.Drawing.Point(363, 35)
		Me.channelLogic7.Name = "channelLogic7"
		Me.channelLogic7.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic7.TabIndex = 7
		' 
		' label1
		' 
		Me.label1.AutoSize = True
		Me.label1.Location = New System.Drawing.Point(6, 19)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(32, 13)
		Me.label1.TabIndex = 1
		Me.label1.Text = "Ch. 0"
		' 
		' label2
		' 
		Me.label2.AutoSize = True
		Me.label2.Location = New System.Drawing.Point(54, 19)
		Me.label2.Name = "label2"
		Me.label2.Size = New System.Drawing.Size(32, 13)
		Me.label2.TabIndex = 8
		Me.label2.Text = "Ch. 1"
		' 
		' label3
		' 
		Me.label3.AutoSize = True
		Me.label3.Location = New System.Drawing.Point(108, 19)
		Me.label3.Name = "label3"
		Me.label3.Size = New System.Drawing.Size(32, 13)
		Me.label3.TabIndex = 9
		Me.label3.Text = "Ch. 2"
		' 
		' label4
		' 
		Me.label4.AutoSize = True
		Me.label4.Location = New System.Drawing.Point(159, 19)
		Me.label4.Name = "label4"
		Me.label4.Size = New System.Drawing.Size(32, 13)
		Me.label4.TabIndex = 10
		Me.label4.Text = "Ch. 3"
		' 
		' label5
		' 
		Me.label5.AutoSize = True
		Me.label5.Location = New System.Drawing.Point(207, 19)
		Me.label5.Name = "label5"
		Me.label5.Size = New System.Drawing.Size(32, 13)
		Me.label5.TabIndex = 11
		Me.label5.Text = "Ch. 4"
		' 
		' label6
		' 
		Me.label6.AutoSize = True
		Me.label6.Location = New System.Drawing.Point(258, 19)
		Me.label6.Name = "label6"
		Me.label6.Size = New System.Drawing.Size(32, 13)
		Me.label6.TabIndex = 12
		Me.label6.Text = "Ch. 5"
		' 
		' label7
		' 
		Me.label7.AutoSize = True
		Me.label7.Location = New System.Drawing.Point(309, 19)
		Me.label7.Name = "label7"
		Me.label7.Size = New System.Drawing.Size(32, 13)
		Me.label7.TabIndex = 13
		Me.label7.Text = "Ch. 6"
		' 
		' label8
		' 
		Me.label8.AutoSize = True
		Me.label8.Location = New System.Drawing.Point(360, 19)
		Me.label8.Name = "label8"
		Me.label8.Size = New System.Drawing.Size(32, 13)
		Me.label8.TabIndex = 14
		Me.label8.Text = "Ch. 7"
		' 
		' startPortALogic
		' 
		Me.startPortALogic.Location = New System.Drawing.Point(522, 33)
		Me.startPortALogic.Name = "startPortALogic"
		Me.startPortALogic.Size = New System.Drawing.Size(118, 23)
		Me.startPortALogic.TabIndex = 15
		Me.startPortALogic.Text = "Start event logic"
		Me.startPortALogic.UseVisualStyleBackColor = True
		AddHandler Me.startPortALogic.Click, New System.EventHandler(AddressOf Me.startPortALogic_Click)
		' 
		' stopPortALogic
		' 
		Me.stopPortALogic.Enabled = False
		Me.stopPortALogic.Location = New System.Drawing.Point(646, 33)
		Me.stopPortALogic.Name = "stopPortALogic"
		Me.stopPortALogic.Size = New System.Drawing.Size(118, 23)
		Me.stopPortALogic.TabIndex = 16
		Me.stopPortALogic.Text = "Stop event logic"
		Me.stopPortALogic.UseVisualStyleBackColor = True
		AddHandler Me.stopPortALogic.Click, New System.EventHandler(AddressOf Me.stopPortALogic_Click)
		' 
		' logicType
		' 
		Me.logicType.FormattingEnabled = True
		Me.logicType.Items.AddRange(New Object() {"or", "and"})
		Me.logicType.Location = New System.Drawing.Point(414, 35)
		Me.logicType.Name = "logicType"
		Me.logicType.Size = New System.Drawing.Size(102, 21)
		Me.logicType.TabIndex = 17
		' 
		' label9
		' 
		Me.label9.AutoSize = True
		Me.label9.Location = New System.Drawing.Point(411, 19)
		Me.label9.Name = "label9"
		Me.label9.Size = New System.Drawing.Size(56, 13)
		Me.label9.TabIndex = 18
		Me.label9.Text = "Logic type"
		' 
		' eventBox
		' 
		Me.eventBox.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) Or System.Windows.Forms.AnchorStyles.Left) Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.eventBox.Location = New System.Drawing.Point(12, 331)
		Me.eventBox.Multiline = True
		Me.eventBox.Name = "eventBox"
		Me.eventBox.[ReadOnly] = True
		Me.eventBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
		Me.eventBox.Size = New System.Drawing.Size(770, 149)
		Me.eventBox.TabIndex = 1
		' 
		' helpBox
		' 
		Me.helpBox.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.helpBox.Controls.Add(Me.label16)
		Me.helpBox.Controls.Add(Me.label15)
		Me.helpBox.Controls.Add(Me.label14)
		Me.helpBox.Controls.Add(Me.label13)
		Me.helpBox.Controls.Add(Me.label12)
		Me.helpBox.Controls.Add(Me.label11)
		Me.helpBox.Controls.Add(Me.label10)
		Me.helpBox.Location = New System.Drawing.Point(12, 12)
		Me.helpBox.Name = "helpBox"
		Me.helpBox.Size = New System.Drawing.Size(770, 135)
		Me.helpBox.TabIndex = 2
		Me.helpBox.TabStop = False
		Me.helpBox.Text = "Help"
		' 
		' label10
		' 
		Me.label10.Location = New System.Drawing.Point(6, 25)
		Me.label10.Name = "label10"
		Me.label10.Size = New System.Drawing.Size(758, 43)
		Me.label10.TabIndex = 0
		Me.label10.Text = "Set an event logic and receive interruption. For each channel you can select a le" & "vel or a transition. Remeber that if you use AND logic, you can only use one edg" & "e event. "
		' 
		' label11
		' 
		Me.label11.AutoSize = True
		Me.label11.Location = New System.Drawing.Point(6, 55)
		Me.label11.Name = "label11"
		Me.label11.Size = New System.Drawing.Size(182, 13)
		Me.label11.TabIndex = 1
		Me.label11.Text = "X: The input is not used for the event"
		' 
		' label12
		' 
		Me.label12.AutoSize = True
		Me.label12.Location = New System.Drawing.Point(6, 68)
		Me.label12.Name = "label12"
		Me.label12.Size = New System.Drawing.Size(123, 13)
		Me.label12.TabIndex = 2
		Me.label12.Text = "0: The input must be low"
		' 
		' label13
		' 
		Me.label13.AutoSize = True
		Me.label13.Location = New System.Drawing.Point(6, 81)
		Me.label13.Name = "label13"
		Me.label13.Size = New System.Drawing.Size(127, 13)
		Me.label13.TabIndex = 3
		Me.label13.Text = "1: The input must be high"
		' 
		' label14
		' 
		Me.label14.AutoSize = True
		Me.label14.Location = New System.Drawing.Point(218, 55)
		Me.label14.Name = "label14"
		Me.label14.Size = New System.Drawing.Size(174, 13)
		Me.label14.TabIndex = 4
		Me.label14.Text = "2: The input reacts to a falling edge"
		' 
		' label15
		' 
		Me.label15.AutoSize = True
		Me.label15.Location = New System.Drawing.Point(218, 68)
		Me.label15.Name = "label15"
		Me.label15.Size = New System.Drawing.Size(171, 13)
		Me.label15.TabIndex = 5
		Me.label15.Text = "3: The input reacts to a rising edge"
		' 
		' label16
		' 
		Me.label16.AutoSize = True
		Me.label16.Location = New System.Drawing.Point(218, 81)
		Me.label16.Name = "label16"
		Me.label16.Size = New System.Drawing.Size(164, 13)
		Me.label16.TabIndex = 6
		Me.label16.Text = "4: The input reacts to both edges"
		' 
		' portBGroupBox
		' 
		Me.portBGroupBox.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
		Me.portBGroupBox.Controls.Add(Me.stopPortBLogic)
		Me.portBGroupBox.Controls.Add(Me.startPortBLogic)
		Me.portBGroupBox.Controls.Add(Me.label17)
		Me.portBGroupBox.Controls.Add(Me.label18)
		Me.portBGroupBox.Controls.Add(Me.label19)
		Me.portBGroupBox.Controls.Add(Me.label20)
		Me.portBGroupBox.Controls.Add(Me.label21)
		Me.portBGroupBox.Controls.Add(Me.label22)
		Me.portBGroupBox.Controls.Add(Me.channelLogic13)
		Me.portBGroupBox.Controls.Add(Me.channelLogic12)
		Me.portBGroupBox.Controls.Add(Me.channelLogic11)
		Me.portBGroupBox.Controls.Add(Me.channelLogic10)
		Me.portBGroupBox.Controls.Add(Me.channelLogic9)
		Me.portBGroupBox.Controls.Add(Me.channelLogic8)
		Me.portBGroupBox.Location = New System.Drawing.Point(12, 236)
		Me.portBGroupBox.Name = "portBGroupBox"
		Me.portBGroupBox.Size = New System.Drawing.Size(770, 89)
		Me.portBGroupBox.TabIndex = 3
		Me.portBGroupBox.TabStop = False
		Me.portBGroupBox.Text = "Port B"
		' 
		' label17
		' 
		Me.label17.AutoSize = True
		Me.label17.Location = New System.Drawing.Point(258, 25)
		Me.label17.Name = "label17"
		Me.label17.Size = New System.Drawing.Size(38, 13)
		Me.label17.TabIndex = 24
		Me.label17.Text = "Ch. 13"
		' 
		' label18
		' 
		Me.label18.AutoSize = True
		Me.label18.Location = New System.Drawing.Point(207, 25)
		Me.label18.Name = "label18"
		Me.label18.Size = New System.Drawing.Size(38, 13)
		Me.label18.TabIndex = 23
		Me.label18.Text = "Ch. 12"
		' 
		' label19
		' 
		Me.label19.AutoSize = True
		Me.label19.Location = New System.Drawing.Point(159, 25)
		Me.label19.Name = "label19"
		Me.label19.Size = New System.Drawing.Size(38, 13)
		Me.label19.TabIndex = 22
		Me.label19.Text = "Ch. 11"
		' 
		' label20
		' 
		Me.label20.AutoSize = True
		Me.label20.Location = New System.Drawing.Point(108, 25)
		Me.label20.Name = "label20"
		Me.label20.Size = New System.Drawing.Size(38, 13)
		Me.label20.TabIndex = 21
		Me.label20.Text = "Ch. 10"
		' 
		' label21
		' 
		Me.label21.AutoSize = True
		Me.label21.Location = New System.Drawing.Point(54, 25)
		Me.label21.Name = "label21"
		Me.label21.Size = New System.Drawing.Size(32, 13)
		Me.label21.TabIndex = 20
		Me.label21.Text = "Ch. 9"
		' 
		' label22
		' 
		Me.label22.AutoSize = True
		Me.label22.Location = New System.Drawing.Point(6, 25)
		Me.label22.Name = "label22"
		Me.label22.Size = New System.Drawing.Size(32, 13)
		Me.label22.TabIndex = 14
		Me.label22.Text = "Ch. 8"
		' 
		' channelLogic13
		' 
		Me.channelLogic13.FormattingEnabled = True
		Me.channelLogic13.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic13.Location = New System.Drawing.Point(261, 41)
		Me.channelLogic13.Name = "channelLogic13"
		Me.channelLogic13.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic13.TabIndex = 19
		' 
		' channelLogic12
		' 
		Me.channelLogic12.FormattingEnabled = True
		Me.channelLogic12.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic12.Location = New System.Drawing.Point(210, 41)
		Me.channelLogic12.Name = "channelLogic12"
		Me.channelLogic12.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic12.TabIndex = 18
		' 
		' channelLogic11
		' 
		Me.channelLogic11.FormattingEnabled = True
		Me.channelLogic11.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic11.Location = New System.Drawing.Point(159, 41)
		Me.channelLogic11.Name = "channelLogic11"
		Me.channelLogic11.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic11.TabIndex = 17
		' 
		' channelLogic10
		' 
		Me.channelLogic10.FormattingEnabled = True
		Me.channelLogic10.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic10.Location = New System.Drawing.Point(108, 41)
		Me.channelLogic10.Name = "channelLogic10"
		Me.channelLogic10.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic10.TabIndex = 16
		' 
		' channelLogic9
		' 
		Me.channelLogic9.FormattingEnabled = True
		Me.channelLogic9.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic9.Location = New System.Drawing.Point(57, 41)
		Me.channelLogic9.Name = "channelLogic9"
		Me.channelLogic9.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic9.TabIndex = 15
		' 
		' channelLogic8
		' 
		Me.channelLogic8.FormattingEnabled = True
		Me.channelLogic8.Items.AddRange(New Object() {"X", "0", "1", "2", "3", "4"})
		Me.channelLogic8.Location = New System.Drawing.Point(6, 41)
		Me.channelLogic8.Name = "channelLogic8"
		Me.channelLogic8.Size = New System.Drawing.Size(45, 21)
		Me.channelLogic8.TabIndex = 13
		' 
		' stopPortBLogic
		' 
		Me.stopPortBLogic.Enabled = False
		Me.stopPortBLogic.Location = New System.Drawing.Point(646, 41)
		Me.stopPortBLogic.Name = "stopPortBLogic"
		Me.stopPortBLogic.Size = New System.Drawing.Size(118, 23)
		Me.stopPortBLogic.TabIndex = 26
		Me.stopPortBLogic.Text = "Stop event logic"
		Me.stopPortBLogic.UseVisualStyleBackColor = True
		AddHandler Me.stopPortBLogic.Click, New System.EventHandler(AddressOf Me.stopPortBLogic_Click)
		' 
		' startPortBLogic
		' 
		Me.startPortBLogic.Location = New System.Drawing.Point(522, 41)
		Me.startPortBLogic.Name = "startPortBLogic"
		Me.startPortBLogic.Size = New System.Drawing.Size(118, 23)
		Me.startPortBLogic.TabIndex = 25
		Me.startPortBLogic.Text = "Start event logic"
		Me.startPortBLogic.UseVisualStyleBackColor = True
		AddHandler Me.startPortBLogic.Click, New System.EventHandler(AddressOf Me.startPortBLogic_Click)
		' 
		' EventLogic
		' 
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6F, 13F)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(794, 492)
		Me.Controls.Add(Me.portBGroupBox)
		Me.Controls.Add(Me.helpBox)
		Me.Controls.Add(Me.eventBox)
		Me.Controls.Add(Me.portAGroupBox)
		Me.Icon = DirectCast(resources.GetObject("$this.Icon"), System.Drawing.Icon)
		Me.Name = "EventLogic"
		Me.Text = "Sample: Event logic"
		AddHandler Me.Load, New System.EventHandler(AddressOf Me.EventLogic_Load)
		AddHandler Me.FormClosing, New System.Windows.Forms.FormClosingEventHandler(AddressOf Me.EventLogic_FormClosing)
		Me.portAGroupBox.ResumeLayout(False)
		Me.portAGroupBox.PerformLayout()
		Me.helpBox.ResumeLayout(False)
		Me.helpBox.PerformLayout()
		Me.portBGroupBox.ResumeLayout(False)
		Me.portBGroupBox.PerformLayout()
		Me.ResumeLayout(False)
		Me.PerformLayout()

	End Sub



	Private portAGroupBox As System.Windows.Forms.GroupBox
	Private channelLogic0 As System.Windows.Forms.ComboBox
	Private channelLogic4 As System.Windows.Forms.ComboBox
	Private channelLogic3 As System.Windows.Forms.ComboBox
	Private channelLogic2 As System.Windows.Forms.ComboBox
	Private channelLogic1 As System.Windows.Forms.ComboBox
	Private channelLogic7 As System.Windows.Forms.ComboBox
	Private channelLogic6 As System.Windows.Forms.ComboBox
	Private channelLogic5 As System.Windows.Forms.ComboBox
	Private label8 As System.Windows.Forms.Label
	Private label7 As System.Windows.Forms.Label
	Private label6 As System.Windows.Forms.Label
	Private label5 As System.Windows.Forms.Label
	Private label4 As System.Windows.Forms.Label
	Private label3 As System.Windows.Forms.Label
	Private label2 As System.Windows.Forms.Label
	Private label1 As System.Windows.Forms.Label
	Private stopPortALogic As System.Windows.Forms.Button
	Private startPortALogic As System.Windows.Forms.Button
	Private logicType As System.Windows.Forms.ComboBox
	Private label9 As System.Windows.Forms.Label
	Private eventBox As System.Windows.Forms.TextBox
	Private helpBox As System.Windows.Forms.GroupBox
	Private label10 As System.Windows.Forms.Label
	Private label11 As System.Windows.Forms.Label
	Private label12 As System.Windows.Forms.Label
	Private label13 As System.Windows.Forms.Label
	Private label14 As System.Windows.Forms.Label
	Private label15 As System.Windows.Forms.Label
	Private label16 As System.Windows.Forms.Label
	Private portBGroupBox As System.Windows.Forms.GroupBox
	Private label17 As System.Windows.Forms.Label
	Private label18 As System.Windows.Forms.Label
	Private label19 As System.Windows.Forms.Label
	Private label20 As System.Windows.Forms.Label
	Private label21 As System.Windows.Forms.Label
	Private label22 As System.Windows.Forms.Label
	Private channelLogic13 As System.Windows.Forms.ComboBox
	Private channelLogic12 As System.Windows.Forms.ComboBox
	Private channelLogic11 As System.Windows.Forms.ComboBox
	Private channelLogic10 As System.Windows.Forms.ComboBox
	Private channelLogic9 As System.Windows.Forms.ComboBox
	Private channelLogic8 As System.Windows.Forms.ComboBox
	Private stopPortBLogic As System.Windows.Forms.Button
	Private startPortBLogic As System.Windows.Forms.Button

End Class

