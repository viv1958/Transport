object FormDateRange: TFormDateRange
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1044#1080#1072#1087#1072#1079#1086#1085' '#1076#1072#1090
  ClientHeight = 127
  ClientWidth = 454
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object sLabel1: TsLabel
    Left = 32
    Top = 24
    Width = 10
    Height = 13
    Caption = #1057':'
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
  end
  object sLabel2: TsLabel
    Left = 217
    Top = 24
    Width = 17
    Height = 13
    Caption = #1087#1086':'
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
  end
  object sButton1: TsButton
    Left = 104
    Top = 64
    Width = 75
    Height = 25
    Caption = 'Ok'
    Default = True
    TabOrder = 3
    OnClick = sButton1Click
    SkinData.SkinSection = 'BUTTON'
  end
  object sButton2: TsButton
    Left = 288
    Top = 64
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 5
    SkinData.SkinSection = 'BUTTON'
  end
  object DBDateTimeEditEh1: TDBDateTimeEditEh
    Tag = 1
    Left = 48
    Top = 21
    Width = 90
    Height = 21
    DynProps = <>
    EditButton.ShortCut = 45
    EditButtons = <>
    TabOrder = 0
    Visible = True
    EditFormat = 'DD/MM/YY'
  end
  object DBDateTimeEditEh2: TDBDateTimeEditEh
    Tag = 2
    Left = 149
    Top = 21
    Width = 55
    Height = 21
    DynProps = <>
    EditButton.ShortCut = 0
    EditButton.Visible = False
    EditButtons = <>
    TabOrder = 1
    Visible = True
    EditFormat = 'HH:NN'
  end
  object DBDateTimeEditEh3: TDBDateTimeEditEh
    Tag = 3
    Left = 242
    Top = 21
    Width = 89
    Height = 21
    DynProps = <>
    EditButton.ShortCut = 45
    EditButtons = <>
    TabOrder = 2
    Visible = True
    EditFormat = 'DD/MM/YY'
  end
  object DBDateTimeEditEh4: TDBDateTimeEditEh
    Tag = 4
    Left = 343
    Top = 21
    Width = 55
    Height = 21
    DynProps = <>
    EditButton.ShortCut = 0
    EditButton.Visible = False
    EditButtons = <>
    TabOrder = 4
    Visible = True
    EditFormat = 'HH:NN'
  end
end
