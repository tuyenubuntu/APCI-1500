Public Class Form1
    Dim board As PCI1500_NET.PCI1500

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' Open the first board of the system
        board = PCI1500_NET.PCI1500.OpenBoard(0)
        ' Error handling
        If (IsDBNull(board)) Then
            MessageBox.Show("Error OpenBoard returned null")
            Close()
            Exit Sub
        End If

        ' Start the timer
        readTimer.Start()
    End Sub

    Private Sub readTimer_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles readTimer.Tick
        Dim returnValue As Integer, i As Integer
        Dim inputValue As UShort

        ' We read the status of the outputs
        returnValue = board.Read16DigitalInputs(inputValue)
        If (returnValue <> 0) Then
            MessageBox.Show("Error " + returnValue.ToString() + " in Read16DigitalInputs")
            Close()
            Exit Sub
        End If

        ' Create a helper array
        Dim LEDs(2) As Image
        LEDs(0) = Global.ReadDigitalInputs.My.Resources.led_off
        LEDs(1) = Global.ReadDigitalInputs.My.Resources.led_on

        ' Change the image given the new status
        i = 0
        input0StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input1StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input2StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input3StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input4StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input5StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input6StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input7StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input8StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input9StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input10StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input11StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input12StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input13StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input14StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1
        input15StatusBox.Image = LEDs((inputValue >> i) And 1)
        i = i + 1

        ResumeLayout(False)
        PerformLayout()
    End Sub
End Class
