object Form1: TForm1
  Left = 192
  Top = 124
  Width = 928
  Height = 480
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Courier New'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 21
  object Label1: TLabel
    Left = 64
    Top = 8
    Width = 22
    Height = 21
    Caption = 'N='
  end
  object Label2: TLabel
    Left = 440
    Top = 8
    Width = 22
    Height = 21
    BiDiMode = bdRightToLeft
    Caption = 'I='
    ParentBiDiMode = False
  end
  object Label3: TLabel
    Left = 440
    Top = 40
    Width = 22
    Height = 21
    Caption = 'J='
  end
  object StringGrid1: TStringGrid
    Left = 64
    Top = 40
    Width = 73
    Height = 393
    ColCount = 1
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 0
  end
  object Edit1: TEdit
    Left = 88
    Top = 8
    Width = 137
    Height = 29
    TabOrder = 1
    Text = 'Edit1'
  end
  object Button1: TButton
    Left = 232
    Top = 8
    Width = 201
    Height = 25
    Caption = #1056#1072#1079#1084#1077#1088#1085#1086#1089#1090#1100
    TabOrder = 2
    OnClick = Button1Click
  end
  object StringGrid2: TStringGrid
    Left = 152
    Top = 40
    Width = 73
    Height = 393
    ColCount = 1
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 3
  end
  object RadioGroup1: TRadioGroup
    Left = 232
    Top = 40
    Width = 201
    Height = 105
    Caption = 'RadioGroup1'
    Items.Strings = (
      #1040
      #1041)
    TabOrder = 4
  end
  object Button2: TButton
    Left = 232
    Top = 152
    Width = 201
    Height = 25
    Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
    TabOrder = 5
    OnClick = Button2Click
  end
  object Edit2: TEdit
    Left = 456
    Top = 8
    Width = 121
    Height = 29
    TabOrder = 6
    Text = 'Edit2'
  end
  object Edit3: TEdit
    Left = 456
    Top = 40
    Width = 121
    Height = 29
    TabOrder = 7
    Text = 'Edit3'
  end
  object MainMenu1: TMainMenu
    Left = 680
    Top = 88
    object N1: TMenuItem
      Caption = #1054#1090#1082#1088#1099#1090#1100
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      OnClick = N2Click
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'in|*.txt'
    Left = 680
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    Filter = 'save|*.txt'
    Left = 680
    Top = 48
  end
end
