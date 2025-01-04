object SampleForm: TSampleForm
  Left = 0
  Top = 0
  Caption = 'xPCI-1500 Timer interrupt sample'
  ClientHeight = 486
  ClientWidth = 490
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 24
    Top = 8
    Width = 441
    Height = 217
    Caption = 'Information'
    TabOrder = 0
    object Information1Label: TLabel
      Left = 16
      Top = 16
      Width = 3
      Height = 13
    end
    object MemoInformation: TMemo
      Left = 16
      Top = 80
      Width = 409
      Height = 129
      Lines.Strings = (
        '')
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object GroupBox2: TGroupBox
    Left = 24
    Top = 240
    Width = 441
    Height = 169
    Caption = 'Execution'
    TabOrder = 1
    object ExecutionLabel1: TLabel
      Left = 8
      Top = 16
      Width = 3
      Height = 13
    end
    object ExecutionLabel2: TLabel
      Left = 8
      Top = 32
      Width = 3
      Height = 13
    end
    object ExecutionLabel3: TLabel
      Left = 8
      Top = 48
      Width = 3
      Height = 13
    end
    object ExecutionLabel4: TLabel
      Left = 8
      Top = 64
      Width = 3
      Height = 13
    end
    object ExecutionLabel5: TLabel
      Left = 8
      Top = 80
      Width = 3
      Height = 13
    end
    object TLabel
      Left = 8
      Top = 120
      Width = 3
      Height = 13
    end
    object ErrorLabel1: TLabel
      Left = 8
      Top = 120
      Width = 3
      Height = 13
    end
    object ErrorLabel2: TLabel
      Left = 11
      Top = 144
      Width = 3
      Height = 13
    end
  end
  object StartButton: TButton
    Left = 8
    Top = 440
    Width = 97
    Height = 33
    Caption = 'Start'
    Enabled = False
    TabOrder = 2
    OnClick = StartButtonClick
  end
  object StopButton: TButton
    Left = 384
    Top = 440
    Width = 97
    Height = 33
    Caption = 'Stop'
    Enabled = False
    TabOrder = 3
    OnClick = StopButtonClick
  end
  object ExecutionTimer: TTimer
    Enabled = False
    Interval = 1
    OnTimer = ExecutionTimerTimer
    Left = 232
    Top = 440
  end
end
