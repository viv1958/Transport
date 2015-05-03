object FormPassWord: TFormPassWord
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1056#1077#1075#1080#1089#1090#1088#1072#1094#1080#1103' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
  ClientHeight = 98
  ClientWidth = 236
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OldCreateOrder = False
  OnCreate = FormCreate
  DesignSize = (
    236
    98)
  PixelsPerInch = 96
  TextHeight = 13
  object sLabel1: TsLabel
    Left = 24
    Top = 29
    Width = 46
    Height = 13
    Caption = #1055#1072#1088#1086#1083#1100':'
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
  end
  object sButton1: TsButton
    Left = 24
    Top = 64
    Width = 78
    Height = 25
    Caption = 'Ok'
    Default = True
    TabOrder = 1
    OnClick = sButton1Click
    SkinData.SkinSection = 'BUTTON'
  end
  object sButton2: TsButton
    Left = 136
    Top = 64
    Width = 78
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 2
    OnClick = sButton2Click
    SkinData.SkinSection = 'BUTTON'
  end
  object sEdit1: TsEdit
    Left = 83
    Top = 25
    Width = 121
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    PasswordChar = '*'
    TabOrder = 0
    SkinData.SkinSection = 'EDIT'
    BoundLabel.Indent = 0
    BoundLabel.Font.Charset = DEFAULT_CHARSET
    BoundLabel.Font.Color = clWindowText
    BoundLabel.Font.Height = -11
    BoundLabel.Font.Name = 'Tahoma'
    BoundLabel.Font.Style = []
    BoundLabel.Layout = sclLeft
    BoundLabel.MaxWidth = 0
    BoundLabel.UseSkinColor = True
  end
  object Query1: TQuery
    DatabaseName = 'TransDB'
    SQL.Strings = (
      'SELECT * FROM CHECK_PASSWORD(:PASSWRD)')
    Left = 144
    Top = 8
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'PASSWRD'
        ParamType = ptUnknown
      end>
  end
end
