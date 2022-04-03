object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Compressor'
  ClientHeight = 424
  ClientWidth = 794
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  Position = poDesktopCenter
  DesignSize = (
    794
    424)
  PixelsPerInch = 96
  TextHeight = 13
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 374
    Width = 792
    Height = 33
    Anchors = [akLeft, akRight, akBottom]
    TabOrder = 0
  end
  object TabControl1: TTabControl
    Left = 0
    Top = 0
    Width = 792
    Height = 368
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 1
    Tabs.Strings = (
      'Compress'
      'Decompress')
    TabIndex = 0
    OnChange = TabControl1Change
    object Label1: TLabel
      Left = 56
      Top = 55
      Width = 126
      Height = 19
      Caption = 'File to compress :'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 56
      Top = 112
      Width = 119
      Height = 19
      Caption = 'File Destination :'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object CompressButt: TButton
      Left = 199
      Top = 184
      Width = 362
      Height = 33
      Caption = 'Compress'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = CompressButtClick
    end
    object FilePathlab: TEdit
      Left = 199
      Top = 54
      Width = 362
      Height = 26
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object FileDestlab: TEdit
      Left = 199
      Top = 109
      Width = 362
      Height = 26
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object FileDestbutt: TButton
      Left = 567
      Top = 111
      Width = 75
      Height = 26
      Caption = 'Path'
      TabOrder = 3
      OnClick = FileDestbuttClick
    end
    object OpenFileButt: TButton
      Left = 567
      Top = 54
      Width = 75
      Height = 27
      Caption = 'Open'
      TabOrder = 4
      OnClick = OpenFileButtClick
    end
    object upButt: TButton
      Left = 680
      Top = 72
      Width = 25
      Height = 25
      Caption = '/\'
      TabOrder = 5
      OnClick = upButtClick
    end
    object downButt: TButton
      Left = 680
      Top = 103
      Width = 25
      Height = 25
      Caption = '\/'
      TabOrder = 6
      OnClick = downButtClick
    end
    object RadioGroupOpt: TRadioGroup
      Left = 40
      Top = 240
      Width = 210
      Height = 113
      Caption = 'Option'
      ItemIndex = 1
      Items.Strings = (
        'Huffman'
        'LZW')
      TabOrder = 7
    end
    object RadioGroupTim: TRadioGroup
      Left = 280
      Top = 240
      Width = 209
      Height = 113
      Caption = 'Time'
      ItemIndex = 2
      Items.Strings = (
        'Lent '
        'Moyen '
        'Rapide')
      TabOrder = 8
    end
    object Selectcheckopt: TCheckBox
      Left = 168
      Top = 240
      Width = 65
      Height = 17
      Caption = 'Select'
      Checked = True
      State = cbChecked
      TabOrder = 9
      OnClick = SelectcheckoptClick
    end
    object Selectchecktim: TCheckBox
      Left = 416
      Top = 240
      Width = 65
      Height = 17
      Caption = 'Select'
      TabOrder = 10
      OnClick = SelectchecktimClick
    end
    object Powergroup: TRadioGroup
      Left = 520
      Top = 240
      Width = 201
      Height = 113
      Caption = 'Power'
      ItemIndex = 1
      Items.Strings = (
        'Low '
        'Strong '
        'Huge')
      TabOrder = 11
    end
    object Selectpoweropt: TCheckBox
      Left = 632
      Top = 240
      Width = 73
      Height = 17
      Caption = 'Select'
      TabOrder = 12
      OnClick = SelectpoweroptClick
    end
  end
  object MainMenu1: TMainMenu
    Left = 120
    Top = 160
    object File1: TMenuItem
      Caption = 'File'
      object New1: TMenuItem
        Caption = 'New'
        OnClick = New1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object About1: TMenuItem
      Caption = 'About'
      object Author1: TMenuItem
        Caption = 'Author'
        OnClick = Author1Click
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 584
    Top = 160
  end
  object CDTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = CDTimerTimer
    Left = 664
    Top = 168
  end
  object PopupMenu1: TPopupMenu
    Left = 728
    Top = 168
    object New2: TMenuItem
      Caption = 'New'
      OnClick = New2Click
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object Selectoption1: TMenuItem
      Caption = 'Select Option'
      OnClick = Selectoption1Click
    end
    object SelectTime1: TMenuItem
      Caption = 'Select Time'
      OnClick = SelectTime1Click
    end
    object SelectPower1: TMenuItem
      Caption = 'Select Power'
      OnClick = SelectPower1Click
    end
    object N3: TMenuItem
      Caption = '-'
    end
    object Open1: TMenuItem
      Caption = 'Chose file (Open)'
      OnClick = Open1Click
    end
    object Path1: TMenuItem
      Caption = 'Path destination'
      OnClick = Path1Click
    end
  end
end
