object FormDriverGraphDay: TFormDriverGraphDay
  Left = 0
  Top = 0
  Caption = 'FormDriverGraphDay'
  ClientHeight = 170
  ClientWidth = 509
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object sLabel1: TsLabel
    Left = 344
    Top = 43
    Width = 16
    Height = 13
    Caption = #1076#1086
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
  end
  object sLabel2: TsLabel
    Left = 154
    Top = 76
    Width = 73
    Height = 13
    Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077':'
    ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
  end
  object sComboBox1: TsComboBox
    Left = 48
    Top = 40
    Width = 184
    Height = 21
    Alignment = taLeftJustify
    BoundLabel.Indent = 0
    BoundLabel.Font.Charset = DEFAULT_CHARSET
    BoundLabel.Font.Color = clWindowText
    BoundLabel.Font.Height = -11
    BoundLabel.Font.Name = 'Tahoma'
    BoundLabel.Font.Style = []
    BoundLabel.Layout = sclLeft
    BoundLabel.MaxWidth = 0
    BoundLabel.UseSkinColor = True
    SkinData.SkinSection = 'COMBOBOX'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ItemIndex = -1
    ParentFont = False
    TabOrder = 0
    Text = 'sComboBox1'
    OnCloseUp = sComboBox1CloseUp
    OnExit = sComboBox1Exit
    OnKeyDown = sComboBox1KeyDown
    Items.Strings = (
      #1056#1072#1073#1086#1095#1080#1081' '#1076#1077#1085#1100
      #1042#1099#1093#1086#1076#1085#1086#1081' '#1076#1077#1085#1100
      #1042#1099#1093#1086#1076#1085#1086#1081' '#1076#1086
      #1042#1099#1093#1086#1076#1085#1086#1081' '#1089
      #1042#1099#1093#1086#1076#1085#1086#1081' '#1087#1086#1089#1083#1077
      #1056#1072#1073#1086#1095#1080#1081' '#1089)
  end
  object DBDateTimeEditEh1: TDBDateTimeEditEh
    Left = 249
    Top = 40
    Width = 64
    Height = 21
    DynProps = <>
    EditButton.Enabled = False
    EditButton.Visible = False
    EditButtons = <>
    TabOrder = 1
    Visible = True
    OnKeyDown = DBDateTimeEditEh1KeyDown
    EditFormat = 'HH:NN'
  end
  object DBDateTimeEditEh2: TDBDateTimeEditEh
    Left = 377
    Top = 40
    Width = 73
    Height = 21
    DynProps = <>
    EditButton.Enabled = False
    EditButton.Visible = False
    EditButtons = <>
    TabOrder = 2
    Visible = True
    OnKeyDown = DBDateTimeEditEh2KeyDown
    EditFormat = 'HH:NN'
  end
  object sEdit1: TsEdit
    Left = 248
    Top = 72
    Width = 202
    Height = 21
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    Text = 'sEdit1'
    OnKeyDown = sEdit1KeyDown
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
  object sButton1: TsButton
    Tag = 1
    Left = 104
    Top = 109
    Width = 75
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 4
    OnClick = sButtonClick
    OnKeyDown = sButton1KeyDown
    SkinData.SkinSection = 'BUTTON'
  end
  object sButton2: TsButton
    Tag = 2
    Left = 330
    Top = 109
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 5
    OnClick = sButtonClick
    SkinData.SkinSection = 'BUTTON'
  end
  object Query1: TQuery
    DatabaseName = 'TransDB'
    Left = 168
  end
  object Query2: TQuery
    DatabaseName = 'TransDB'
    Left = 224
  end
end
