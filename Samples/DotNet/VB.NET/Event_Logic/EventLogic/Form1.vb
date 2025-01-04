Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms

Public Class EventLogic

    Dim board As PCI1500_NET.PCI1500

    Private Delegate Sub AddEventDelegate(ByVal eventInfo As [String])

    Public Sub New()
        InitializeComponent()
    End Sub


    Private Sub EventLogic_Load(ByVal sender As Object, ByVal e As EventArgs)
        Dim ret As Integer = 0

        ' Open the first board of the system
        Me.board = PCI1500_NET.PCI1500.OpenBoard(0)
        ' Error handling
        If Me.board Is Nothing Then
            MessageBox.Show("Error OpenBoard returned null")
            Me.Close()
            Return
        End If

        ' Stop the event logic
        Me.board.StopEventLogic(0)
        Me.board.StopEventLogic(1)

        ' Enable the interruption
        If (InlineAssignHelper(ret, Me.board.SetBoardIntRoutine())) <> 0 Then
            MessageBox.Show("Error " & ret.ToString() & " in SetBoardIntRoutine")
            Me.Close()
            Return
        End If

        ' Select the first index for all the combo boxes
        logicType.SelectedIndex = 0
        channelLogic0.SelectedIndex = 0
        channelLogic1.SelectedIndex = 0
        channelLogic2.SelectedIndex = 0
        channelLogic3.SelectedIndex = 0
        channelLogic4.SelectedIndex = 0
        channelLogic5.SelectedIndex = 0
        channelLogic6.SelectedIndex = 0
        channelLogic7.SelectedIndex = 0
        channelLogic8.SelectedIndex = 0
        channelLogic9.SelectedIndex = 0
        channelLogic10.SelectedIndex = 0
        channelLogic11.SelectedIndex = 0
        channelLogic12.SelectedIndex = 0
        channelLogic13.SelectedIndex = 0

        ' Add a listener to the event logic
        AddHandler Me.board.EventLogicEventReceived, New PCI1500_NET.PCI1500.EventLogicEventHandler(AddressOf board_EventLogicEventReceived)
    End Sub

    ''' Add an event in the event box
    Private Sub AddEvent(ByVal eventInfo As [String])
        eventBox.Text += DateTime.Now.ToString() & " : " & eventInfo & vbCr & vbLf
        eventBox.SelectionStart = eventBox.Text.Length
        eventBox.ScrollToCaret()
    End Sub

    ''' Event logic event received
    Private Sub board_EventLogicEventReceived(ByVal source As Object, ByVal args As PCI1500_NET.EventLogicEventArgs)
        If args.port = 0 Then
            Me.Invoke(New AddEventDelegate(AddressOf Me.AddEvent), "Port A generated an interrupt")
        ElseIf args.port = 1 Then
            Me.Invoke(New AddEventDelegate(AddressOf Me.AddEvent), "Port B generated an interrupt")
        End If
    End Sub

    ''' Occurs while the form is closing
    Private Sub EventLogic_FormClosing(ByVal sender As Object, ByVal e As FormClosingEventArgs)
        Dim ret As Integer = 0
        ' Stop the event logic
        Me.board.StopEventLogic(0)
        Me.board.StopEventLogic(1)

        ' Disable the interruption
        If (InlineAssignHelper(ret, Me.board.ResetBoardIntRoutine())) <> 0 Then
            MessageBox.Show("Error " & ret.ToString() & " in ResetBoardIntRoutine")
            Return
        End If
    End Sub


    ''' Click on the start event logic button (port A)
    Private Sub startPortALogic_Click(ByVal sender As Object, ByVal e As EventArgs)
        Dim tmp As Byte = 0
        Dim ret As Integer = 0
        ' Compute the logic string
        Dim logic As String = channelLogic7.SelectedItem.ToString() + channelLogic6.SelectedItem.ToString() + channelLogic5.SelectedItem.ToString() + channelLogic4.SelectedItem.ToString() + channelLogic3.SelectedItem.ToString() + channelLogic2.SelectedItem.ToString() + channelLogic1.SelectedItem.ToString() + channelLogic0.SelectedItem.ToString()

        ' Init the logic
        If (logicType.SelectedIndex) <> 0 Then
            tmp = 1
        Else
            tmp = 0
        End If

        If (InlineAssignHelper(ret, Me.board.InitEventLogic(0, tmp, logic))) <> 0 Then
            MessageBox.Show("Error " & ret.ToString() & " in InitEventLogic")
            Return
        End If

        ' Start it
        If (InlineAssignHelper(ret, Me.board.StartEventLogic(0))) <> 0 Then
            MessageBox.Show("Error " & ret.ToString() & " in StartEventLogic")
            Return
        End If
        ' Enable/disable button
        startPortALogic.Enabled = False
        stopPortALogic.Enabled = True
    End Sub



    ''' Click on the stop event logic button (port A)
    Private Sub stopPortALogic_Click(ByVal sender As Object, ByVal e As EventArgs)
        Dim ret As Integer = 0
        ' Stop the logic
        If (InlineAssignHelper(ret, Me.board.StopEventLogic(0))) <> 0 Then
            MessageBox.Show("Error " & ret.ToString() & " in StopEventLogic")
            Return
        End If
        ' Enable/disable button
        startPortALogic.Enabled = True
        stopPortALogic.Enabled = False
    End Sub

    ''' Click on the start event logic button (port B)
    Private Sub startPortBLogic_Click(ByVal sender As Object, ByVal e As EventArgs)
        Dim ret As Integer = 0
        ' Compute the logic string
        Dim logic As String = channelLogic13.SelectedItem.ToString() + channelLogic12.SelectedItem.ToString() + channelLogic11.SelectedItem.ToString() + channelLogic10.SelectedItem.ToString() + channelLogic9.SelectedItem.ToString() + channelLogic8.SelectedItem.ToString()
        ' Init the logic
        If (InlineAssignHelper(ret, Me.board.InitEventLogic(1, 0, logic))) <> 0 Then
            MessageBox.Show("Error " & ret.ToString() & " in InitEventLogic")
            Return
        End If
        ' Start it
        If (InlineAssignHelper(ret, Me.board.StartEventLogic(1))) <> 0 Then
            MessageBox.Show("Error " & ret.ToString() & " in StartEventLogic")
            Return
        End If
        ' Enable/disable button
        startPortBLogic.Enabled = False
        stopPortBLogic.Enabled = True
    End Sub


    ''' Click on the stop event logic button (port B)
    Private Sub stopPortBLogic_Click(ByVal sender As Object, ByVal e As EventArgs)
        Dim ret As Integer = 0
        ' Stop the logic
        If (InlineAssignHelper(ret, Me.board.StopEventLogic(1))) <> 0 Then
            MessageBox.Show("Error " & ret.ToString() & " in StopEventLogic")
            Return
        End If
        ' Enable/disable button
        startPortBLogic.Enabled = True
        stopPortBLogic.Enabled = False
    End Sub
    Private Shared Function InlineAssignHelper(Of T)(ByRef target As T, ByVal value As T) As T
        target = value
        Return value
    End Function
End Class
