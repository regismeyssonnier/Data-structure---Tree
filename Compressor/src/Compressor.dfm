object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Compressor'
  ClientHeight = 389
  ClientWidth = 794
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  DesignSize = (
    794
    389)
  PixelsPerInch = 96
  TextHeight = 13
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 339
    Width = 792
    Height = 33
    Anchors = [akLeft, akRight, akBottom]
    TabOrder = 0
  end
  object TabControl1: TTabControl
    Left = 0
    Top = 0
    Width = 792
    Height = 333
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
  end
  object MainMenu1: TMainMenu
    Left = 120
    Top = 216
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
    Left = 568
    Top = 232
  end
  object CDTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = CDTimerTimer
    Left = 656
    Top = 216
  end
end
