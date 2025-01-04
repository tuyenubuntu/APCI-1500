Public Class Form1

    Dim board As PCI1500_NET.PCI1500
    Dim outputStatus As UShort
    Dim outputMemoryStatus As UShort

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Dim ret As Integer

        ' Open the first board of the system
        board = PCI1500_NET.PCI1500.OpenBoard(0)
        ' Error handling
        If (IsDBNull(board)) Then
            MessageBox.Show("Error OpenBoard returned null")
            Close()
            Exit Sub
        End If

        ' Set digital output memory to off
        ret = board.SetDigitalOutputMemoryOff()
        If (ret <> 0) Then
            MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOff")
            Close()
            Exit Sub
        End If

        ' Set all the output to high
        ret = board.Set16DigitalOutputsOn(&HFFFF)
        If ret <> 0 Then
            MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOn")
            Close()
            Exit Sub
        End If

        outputStatus = &HFFFF
        outputMemoryStatus = 0

        digitalOutputMemoryOnButton_Click(sender, e)
    End Sub

    Private Sub Form1_FormClosing(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
        Dim ret As Integer

        ' First set the digital output memory to on
        ret = board.SetDigitalOutputMemoryOn()
        If (ret <> 0) Then
            MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOn")
        End If

        ' Then set all the output to off
        ret = board.Set16DigitalOutputsOff(&HFFFF)
        If (ret <> 0) Then
            MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOff")
        End If

        ' Reset the digital output memory to off 
        ret = board.SetDigitalOutputMemoryOff()
        If (ret <> 0) Then
            MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOff")
        End If
    End Sub

    Private Sub digitalOutputMemoryOnButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles digitalOutputMemoryOnButton.Click
        Dim ret As Integer

        ' Set the digital output memory to on
        ret = board.SetDigitalOutputMemoryOn()
        If (ret <> 0) Then
            MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOn")
        End If

        ' Disable/Enable button
        digitalOutputMemoryOnButton.Enabled = False
        digitalOutputMemoryOffButton.Enabled = True

        ' Store the status
        outputMemoryStatus = 1
    End Sub

    Private Sub digitalOutputMemoryOffButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles digitalOutputMemoryOffButton.Click
        Dim ret As Integer

        ' Set the digital output memory to off
        ret = board.SetDigitalOutputMemoryOff()
        If (ret <> 0) Then
            MessageBox.Show("Error " + ret.ToString() + " in SetDigitalOutputMemoryOff")
        End If

        ' Disable/Enable button
        digitalOutputMemoryOnButton.Enabled = True
        digitalOutputMemoryOffButton.Enabled = False

        ' Store the status
        outputMemoryStatus = 0
    End Sub

    Private Sub outputStatusBox_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles output0StatusBox.Click, output9StatusBox.Click, output8StatusBox.Click, output7StatusBox.Click, output6StatusBox.Click, output5StatusBox.Click, output4StatusBox.Click, output3StatusBox.Click, output2StatusBox.Click, output1StatusBox.Click, output15StatusBox.Click, output14StatusBox.Click, output13StatusBox.Click, output12StatusBox.Click, output11StatusBox.Click, output10StatusBox.Click
        Dim ret As Integer, i As Integer
        Dim index As Integer, status As Integer

        ' Find out which button was clicked
        index = DirectCast(sender, PictureBox).TabIndex - output0StatusBox.TabIndex
        status = (outputStatus >> index) And 1

        ' Update the output status
        If (outputMemoryStatus = 0) Then
            If (status = 1) Then
                MessageBox.Show("To set an output to low, you must activate the digital output memory.")
                Exit Sub
            Else
                outputStatus = 1 << index
                ret = board.Set16DigitalOutputsOn(outputStatus)
                If (ret <> 0) Then
                    MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOn")
                    Exit Sub
                End If
            End If
        Else
            outputStatus = outputStatus Xor (1 << index)
            ret = board.Set16DigitalOutputsOff(&HFFFF)
            If (ret <> 0) Then
                MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOff")
                Exit Sub
            End If
            ret = board.Set16DigitalOutputsOn(outputStatus)
            If (ret <> 0) Then
                MessageBox.Show("Error " + ret.ToString() + " in Set16DigitalOutputsOn")
                Exit Sub
            End If
        End If

        ' Create a helper array
        Dim LEDs(2) As Image
        LEDs(0) = Global.SetDigitalOutputs.My.Resources.led_off
        LEDs(1) = Global.SetDigitalOutputs.My.Resources.led_on

        ' Change the image given the new status
        i = 0
        output0StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output1StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output2StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output3StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output4StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output5StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output6StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output7StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output8StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output9StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output10StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output11StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output12StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output13StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output14StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1
        output15StatusBox.Image = LEDs((outputStatus >> i) And 1)
        i = i + 1

        ResumeLayout(False)
        PerformLayout()
    End Sub
End Class
