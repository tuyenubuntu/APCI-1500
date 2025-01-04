unit TimerInterruptUnit;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ExtCtrls, Vcl.StdCtrls, pci1500;

type
  TSampleForm = class(TForm)
    GroupBox1: TGroupBox;
    Information1Label: TLabel;
    MemoInformation: TMemo;
    GroupBox2: TGroupBox;
    ExecutionLabel1: TLabel;
    ExecutionLabel2: TLabel;
    ExecutionLabel3: TLabel;
    ExecutionLabel4: TLabel;
    ExecutionLabel5: TLabel;
    ErrorLabel1: TLabel;
    ErrorLabel2: TLabel;
    StartButton: TButton;
    StopButton: TButton;
    ExecutionTimer: TTimer;
    procedure v_ErrorMsgBox   (s_FunctionName : String; s_ErrorMsg:String; i_ErrorNbr:Integer);
    procedure v_ErrorMsgCaption   (i_SelectedLine:Integer; s_FunctionName:String; s_ErrorMsg:String; i_ErrorNbr:Integer);
    function i_Initialisation     (Var h_BoardHandle : THANDLE):Integer;
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure ExecutionTimerTimer(Sender: TObject);
    procedure StartButtonClick(Sender: TObject);
    procedure StopButtonClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  SampleForm: TSampleForm;
  b_InitialisationOk : Boolean;
  h_BoardHandle      : THandle;
  l_ReceiveInterrupt : LongWord;

implementation

{$R *.dfm}
procedure TSampleForm.v_ErrorMsgBox   (s_FunctionName : String;
			               s_ErrorMsg     : String;
			               i_ErrorNbr     : Integer);
	  var
	     s_MessageString : String;
	  Begin

	     {* Make the error message string *}
	     If (s_ErrorMsg <> '') Then
		s_MessageString := s_FunctionName        +
				   ' error.'             +
				   Chr (13)              +
				   'Error = '            +
				   IntToStr (i_ErrorNbr) +
				   '. '                  +
				   s_ErrorMsg
	     Else
		s_MessageString := s_FunctionName        +
				   ' error.'             +
				   Chr (13)              +
				   'Error = '            +
				   IntToStr (i_ErrorNbr) +
				   '.';

	     {* Print the error message box *}
	     MessageDlg (s_MessageString, MtError,[mbok],0);
	  End;


procedure TSampleForm.v_ErrorMsgCaption   (i_SelectedLine : Integer;
                                           s_FunctionName : String;
                                           s_ErrorMsg     : String;
                                           i_ErrorNbr     : Integer);
	  var
	     s_MessageString : String;
	  Begin

	     {* Make the error message string *}

	     If (s_ErrorMsg <> '') Then
		s_MessageString := s_FunctionName        +
				   ' error. '            +
				   'Error = '            +
				   IntToStr (i_ErrorNbr) +
				   '. '                  +
				   s_ErrorMsg
	     Else
		s_MessageString := s_FunctionName        +
				   ' error. '            +
				   'Error = '            +
				   IntToStr (i_ErrorNbr) +
				   '.';

	     {* Print the error message box *}

	     If (i_SelectedLine = 1) Then
		SampleForm.ErrorLabel1.Caption := s_MessageString
	     Else
		SampleForm.ErrorLabel2.Caption := s_MessageString
	  End;


function  TSampleForm.i_Initialisation     (Var h_BoardHandle : THANDLE):Integer;
Var
    b_NbrOfBoardFound : Byte;
    i_ReturnValue     : Int16;
    pc_Identifier : Array [0..255] of AnsiChar;
    dw_UINumber : LongWord;
    dw_DeviceNumber : LongWord;
    dw_BusNumber : LongWord;
    dw_BaseAddress0 : LongWord;
    dw_BaseAddress1 : LongWord;
    dw_BaseAddress2 : LongWord;
    b_Interrupt : Byte;

Begin
  {* Get the number of xPCI-1500 found  *}
	i_ReturnValue := i_PCI1500_GetNumberOfBoards (b_NbrOfBoardFound);

	{* Test the return value *}
	If (i_ReturnValue <> 0) Then
  Begin
    i_Initialisation := -1;
    exit;
  end
  else
  Begin
    {* Prints the number of boards *}
    ExecutionLabel1.caption := IntToStr (b_NbrOfBoardFound) + '  board(s) found';

		{* Get the board handle *}
		i_ReturnValue := i_PCI1500_OpenBoardViaIndex (0,h_BoardHandle);

    if (i_ReturnValue <> 0) then
    begin
      v_ErrorMsgBox ('i_PCI1500_OpenBoardViaIndex','',i_ReturnValue);
      i_Initialisation := -1;
      exit;
    end
    else
    begin
      //pc_Identifier := '\0';
      i_ReturnValue := i_PCI1500_GetBoardInformation (0,
                                                      255,
                                                      @pc_Identifier[0],
                                                      dw_UINumber,
                                                      dw_DeviceNumber,
                                                      dw_BusNumber,
                                                      dw_BaseAddress0,
                                                      dw_BaseAddress1,
                                                      dw_BaseAddress2,
                                                      b_Interrupt);

  		{* Test the return value *}
      if (i_ReturnValue = 0) then
      Begin
        {* Prints the hardware informations *}
        MemoInformation.Text := MemoInformation.Text +
                                Chr(13) + Chr(10)+
                                'Board information : ' +
                                Chr(13) + Chr(10)+
                                'Identifier :' + string(pc_Identifier) +
                                Chr(13) + Chr(10)+
                                'UI number : ' + IntToStr(dw_UINumber) +
                                Chr(13) + Chr(10)+
                                'Device number :' + IntToStr(dw_DeviceNumber) +
                                Chr(13) + Chr(10)+
                                'Bus number :' + IntToStr(dw_BusNumber) +
                                Chr(13) + Chr(10)+
                                'Base address 0 :' + IntToHex(dw_BaseAddress0,8) +
                                Chr(13) + Chr(10)+
                                'Base address 1 :' + IntToHex(dw_BaseAddress1,8) +
                                Chr(13) + Chr(10)+
                                'Base address 2 :' + IntToHex(dw_BaseAddress2,8) +
                                Chr(13) + Chr(10)+
                                'Interrupt :' + inttostr(b_Interrupt);


       End;

    End;


  end;

  i_Initialisation := 0;



End;
Procedure v_InterruptRoutine   (h_BoardHandle      : Byte;
                                b_FIFOOverflow    : Byte;
                                b_InterruptMask  : Byte;
                                w_InputValues  : Word);cdecl;

	Begin

    if(b_InterruptMask = 4) then
      l_ReceiveInterrupt := l_ReceiveInterrupt + 1;


	End;

procedure TSampleForm.ExecutionTimerTimer(Sender: TObject);
Var
     w_ReadValue : Uint16;
     s_ReadValue : String;
     i_ReturnValue : Int16;
begin
    (*************************************************
     * The function ReadTimerCounter reads the value *
     * of the Timer/Counter 1 of the APCI-1500 board.*
     *************************************************)

     i_ReturnValue := i_PCI1500_ReadTimerCounter1(h_BoardHandle,
                                                   w_ReadValue);
     s_ReadValue := IntToStr (w_ReadValue);
     ExecutionLabel5.caption := 'Timer value: ' + s_ReadValue + '    Number of interrupts:  ' + IntToStr(l_ReceiveInterrupt);

end;

procedure TSampleForm.FormClose(Sender: TObject; var Action: TCloseAction);
var
  i_ReturnValue : Int16;
begin
     ExecutionLabel1.caption:='';
     ExecutionLabel2.caption:='';
     ExecutionLabel3.caption:='';
     ExecutionLabel4.caption:='';
     ExecutionLabel5.caption:='';

     (* Close the programm *)

     If (b_InitialisationOk = True) Then
	Begin
	   (* Stop the test *)

	   ExecutionTimer.Enabled := False;

	   (**************************************************
	    * This function deinstalls the Interrupt Routine *
	    **************************************************)

	   i_ReturnValue := i_PCI1500_ResetBoardIntRoutine(h_BoardHandle);


	   CASE i_ReturnValue OF

	       0 : ExecutionLabel2.caption := 'i_PCI1500_ResetBoardIntRoutine OK';

	   Else
	       v_ErrorMsgBox ('i_PCI1500_ResetBoardIntRoutine error',
			      '',
			      i_ReturnValue);
	   End;

	   (**************************)
	   (* Close the board handle *)
	   (**************************)

	   i_ReturnValue := i_PCI1500_CloseBoard (h_BoardHandle);

	   (*************************)
	   (* Test the return value *)
	   (*************************)

	   Case (i_ReturnValue) Of
	      0:
	      Begin
	      End;

	   Else
	      Begin
		 v_ErrorMsgBox ('i_PCI1500_CloseBoard', '', i_ReturnValue);
	      End;
	   End; (* Case (i_ReturnValue) Of *)

	End;

end;

procedure TSampleForm.FormCreate(Sender: TObject);
var
  i_ReturnValue : Int16;
begin
    {* Start the programm *}
    b_InitialisationOk := False;

    {* Print sample information *}
    Information1Label.Caption := 'Uses the Timer/Counter1 of the board as TIMER with interrupt';

    MemoInformation.Text := 'The timer beginns at 2000.' +
                            Chr(13) + Chr(10)+
                            ' After he had count down, the start value will be reloaded and an interrupt generated.' +
                            Chr(13) + Chr(10);


    {* Search an initialise the first xPCI-1500 *}
    i_ReturnValue := i_Initialisation (h_BoardHandle);
    if ( i_ReturnValue = 0 )then
    Begin


      {* Test if no error occur *}
      if (i_ReturnValue = 0) then
         i_ReturnValue := i_PCI1500_SetBoardIntRoutine(h_BoardHandle,
                                                       @v_InterruptRoutine);

	    b_InitialisationOk  := True;
  	  StartButton.Enabled := True;
    End
    Else
    Begin
      b_InitialisationOk := False;
    End;
end;

procedure TSampleForm.StartButtonClick(Sender: TObject);
Var
     b_InputClockSelect              : Byte;
     b_ComponentMode          : Byte;
     w_ReloadValue                   : Uint16;
     b_EnableContinuousCycle : Byte;
     b_InterruptHandling             : Byte;
     i_ReturnValue : Int16;


begin

     ExecutionLabel1.caption:='';
     ExecutionLabel2.caption:='';
     ExecutionLabel3.caption:='';
     ExecutionLabel4.caption:='';
     ExecutionLabel5.caption:='';

     StartButton.enabled := False;
     StopButton.enabled := True;

     b_InputClockSelect       := PCI1500_1_8_KHZ;    // Input frequency,fixed on 1.8kHz
     b_ComponentMode          := PCI1500_TIMER;      // Operation mode of the timer 1
     w_ReloadValue            := 2000;                // Division factor for the timer 1
     b_EnableContinuousCycle := PCI1500_ENABLED; // Cycle mode of the timer
     b_InterruptHandling      := PCI1500_ENABLED;     // Selects if interrupts are used or not
     l_ReceiveInterrupt       := 0;

    (**************************************************
     * The function InitTimerInputClock selects input *
     * clock timing for all timers                    *
     **************************************************)

     i_ReturnValue := i_PCI1500_InitTimerInputClock (h_BoardHandle,
                                                      b_InputClockSelect);

     (*************************
      * Test the return value *
      *************************)

     CASE i_ReturnValue OF

         0 : ExecutionLabel1.caption := 'i_PCI1500_InitTimerInputClock OK';

     Else
         v_ErrorMsgBox ('i_PCI1500_InitTimerInputClock error',
                        '',
                        i_ReturnValue);
     End;


    (**********************************************
     * The function InitTimerCounter1 selects the *
     * operating mode of the first timer          *
     **********************************************)

     i_ReturnValue := i_PCI1500_InitTimerCounter1 (h_BoardHandle,
                                                   b_ComponentMode,
                                                   w_ReloadValue,
                                                   b_EnableContinuousCycle,
                                                   b_InterruptHandling);

     (*************************
      * Test the return value *
      *************************)

      CASE i_ReturnValue OF

         0 : ExecutionLabel2.caption := 'i_PCI1500_InitTimerCounter1 OK';

        Else
         v_ErrorMsgBox ('i_PCI1500_InitTimerCounter1 error',
                        '',
                        i_ReturnValue);
     End;

    (**********************************************************
     * The function StartTimerCounter1 strats the first timer *
     **********************************************************)

     i_ReturnValue := i_PCI1500_StartTimerCounter1 (h_BoardHandle);

     (*************************
      * Test the return value *
      *************************)

     CASE i_ReturnValue OF

         0 : ExecutionLabel3.caption := 'i_PCI1500_StartTimerCounter1 OK';

     Else
         v_ErrorMsgBox ('i_PCI1500_StartTimerCounter1 error',
                        '',
                        i_ReturnValue);
     End;


     ExecutionTimer.Enabled := True;

End;
procedure TSampleForm.StopButtonClick(Sender: TObject);
var
  i_ReturnValue : Int16;
begin
     ExecutionLabel1.caption:='';
     ExecutionLabel2.caption:='';
     ExecutionLabel3.caption:='';
     ExecutionLabel4.caption:='';
     ExecutionLabel5.caption:='';


     (*******************
      * Stops the timer *
      *******************)

     ExecutionTimer.Enabled   := False;

     (******************************************
      * This function stops the timer/counter1 *
      ******************************************)

     i_ReturnValue := i_PCI1500_StopTimerCounter1 (h_BoardHandle);

     (*************************
      * Test the return value *
      *************************)

     CASE i_ReturnValue OF

         0 : ExecutionLabel1.caption := 'i_PCI1500_StopTimerCounter1 OK';


     Else
         v_ErrorMsgBox ('i_PCI1500_StopTimerCounter1 error',
                        '',
                        i_ReturnValue);
     End;


     StopButton.Enabled       := False;
     StartButton.Enabled      := True;

end;
end.
