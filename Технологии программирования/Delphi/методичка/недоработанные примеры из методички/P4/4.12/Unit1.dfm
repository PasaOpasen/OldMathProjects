object Form1: TForm1
  Left = 343
  Top = 192
  Width = 921
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
    Left = 8
    Top = 24
    Width = 11
    Height = 21
    Caption = 'N'
  end
  object Label3: TLabel
    Left = 128
    Top = 232
    Width = 77
    Height = 21
    Caption = #1054#1090#1074#1077#1090': '
  end
  object Label4: TLabel
    Left = 208
    Top = 232
    Width = 11
    Height = 21
  end
  object StringGrid1: TStringGrid
    Left = 128
    Top = 48
    Width = 425
    Height = 169
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 0
  end
  object Edit1: TEdit
    Left = 24
    Top = 24
    Width = 97
    Height = 29
    TabOrder = 1
    Text = 'Edit1'
  end
  object Button1: TButton
    Left = 128
    Top = 16
    Width = 121
    Height = 25
    Caption = #1056#1072#1079#1084#1077#1088#1085#1086#1089#1090#1100
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 256
    Top = 16
    Width = 121
    Height = 25
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
    TabOrder = 3
    OnClick = Button2Click
  end
  object RadioGroup1: TRadioGroup
    Left = 560
    Top = 48
    Width = 185
    Height = 105
    Caption = 'RadioGroup1'
    ItemIndex = 0
    Items.Strings = (
      #1040
      #1041
      #1042
      #1043
      #1044)
    TabOrder = 4
  end
  object MainMenu1: TMainMenu
    Left = 816
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
    Left = 816
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    Filter = 'save|*.txt'
    Left = 816
    Top = 48
  end
end
