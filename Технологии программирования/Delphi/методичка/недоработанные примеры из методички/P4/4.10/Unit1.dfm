object Form1: TForm1
  Left = 336
  Top = 192
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
    Left = 16
    Top = 48
    Width = 22
    Height = 21
    Caption = 'N='
  end
  object Label2: TLabel
    Left = 16
    Top = 80
    Width = 22
    Height = 21
    Caption = 'M='
  end
  object StringGrid1: TStringGrid
    Left = 120
    Top = 48
    Width = 425
    Height = 169
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 0
  end
  object StringGrid2: TStringGrid
    Left = 120
    Top = 224
    Width = 425
    Height = 177
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 40
    Top = 48
    Width = 81
    Height = 29
    TabOrder = 2
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 40
    Top = 80
    Width = 81
    Height = 29
    TabOrder = 3
    Text = 'Edit2'
  end
  object Button1: TButton
    Left = 16
    Top = 24
    Width = 137
    Height = 25
    Caption = #1056#1072#1079#1084#1077#1088#1085#1086#1089#1090#1100
    TabOrder = 4
  end
  object Button2: TButton
    Left = 160
    Top = 24
    Width = 121
    Height = 25
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
    TabOrder = 5
    OnClick = Button2Click
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
