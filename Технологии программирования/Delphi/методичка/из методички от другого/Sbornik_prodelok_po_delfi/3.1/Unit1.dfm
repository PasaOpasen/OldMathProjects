object Form1: TForm1
  Left = 235
  Top = 121
  Width = 540
  Height = 279
  Caption = '3.1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 48
    Width = 19
    Height = 13
    Caption = 'X = '
  end
  object Label2: TLabel
    Left = 112
    Top = 48
    Width = 19
    Height = 13
    Caption = 'Y = '
  end
  object Label3: TLabel
    Left = 48
    Top = 16
    Width = 92
    Height = 13
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1079#1085#1072#1095#1077#1085#1080#1103
  end
  object EditX: TEdit
    Left = 40
    Top = 44
    Width = 57
    Height = 21
    TabOrder = 0
    Text = '1'
  end
  object EditY: TEdit
    Left = 136
    Top = 44
    Width = 57
    Height = 21
    TabOrder = 1
    Text = '2,7'
  end
  object GroupBox1: TGroupBox
    Left = 24
    Top = 88
    Width = 169
    Height = 137
    Caption = #1060#1086#1088#1084#1091#1083#1072
    TabOrder = 2
    object CheckBoxA: TCheckBox
      Left = 16
      Top = 24
      Width = 145
      Height = 17
      Caption = 'u = sin(x^2+y^2)+e^(y-x)'
      TabOrder = 0
    end
    object CheckBoxB: TCheckBox
      Left = 16
      Top = 48
      Width = 137
      Height = 17
      Caption = 'u = tg(x+y^2)+ylnx'
      TabOrder = 1
    end
    object CheckBoxV: TCheckBox
      Left = 16
      Top = 72
      Width = 129
      Height = 17
      Caption = 'u = |cosx|+arctg(1/y)'
      TabOrder = 2
    end
    object CheckBoxG: TCheckBox
      Left = 16
      Top = 96
      Width = 137
      Height = 17
      Caption = 'u = (cosx)^2+|y|/arctgx'
      TabOrder = 3
    end
  end
  object Button1: TButton
    Left = 328
    Top = 16
    Width = 75
    Height = 25
    Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
    TabOrder = 3
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 225
    Top = 56
    Width = 280
    Height = 169
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssBoth
    TabOrder = 4
  end
end
