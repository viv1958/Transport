object FormSelSimpleEh: TFormSelSimpleEh
  Left = 2089
  Top = 325
  Caption = 'FormSelSimpleEh'
  ClientHeight = 661
  ClientWidth = 976
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = [fsBold]
  KeyPreview = True
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 590
    Width = 976
    Height = 3
    Cursor = crVSplit
    Align = alBottom
  end
  object DBGridEh1: TDBGridEh
    Left = 0
    Top = 55
    Width = 976
    Height = 535
    Align = alClient
    DataSource = DataSource1
    DynProps = <>
    FooterParams.Color = clWindow
    GridLineParams.VertEmptySpaceStyle = dessNonEh
    IndicatorOptions = [gioShowRowIndicatorEh]
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    OptionsEh = [dghFixed3D, dghIncSearch, dghPreferIncSearch, dghDialogFind, dghColumnResize, dghColumnMove]
    ParentShowHint = False
    RowHeight = 4
    RowLines = 1
    SearchPanel.Enabled = True
    SearchPanel.FilterOnTyping = True
    ShowHint = True
    TabOrder = 0
    OnDblClick = DBGridEh1DblClick
    OnDrawColumnCell = DBGridEh1DrawColumnCell
    OnGetCellParams = DBGridEh1GetCellParams
    OnKeyDown = DBGridEh1KeyDown
    object RowDetailData: TRowDetailPanelControlEh
    end
  end
  object Memo1: TMemo
    Left = 0
    Top = 593
    Width = 976
    Height = 49
    Align = alBottom
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'Memo1')
    ParentFont = False
    TabOrder = 1
    OnExit = Memo1Exit
  end
  object DBEditEh1: TDBEditEh
    Left = 160
    Top = 256
    Width = 121
    Height = 19
    Ctl3D = False
    DynProps = <>
    EditButtons = <>
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 2
    Text = 'DBEditEh1'
    Visible = False
    OnExit = EditExit
    OnKeyDown = EditKeyDown
  end
  object DBDateTimeEditEh1: TDBDateTimeEditEh
    Left = 472
    Top = 256
    Width = 121
    Height = 19
    Ctl3D = False
    DynProps = <>
    Enabled = False
    EditButtons = <>
    Kind = dtkDateEh
    ParentCtl3D = False
    TabOrder = 3
    Visible = False
    OnExit = EditExit
    OnKeyDown = EditKeyDown
  end
  object DBNumberEditEh1: TDBNumberEditEh
    Left = 304
    Top = 256
    Width = 121
    Height = 19
    Ctl3D = False
    DecimalPlaces = 0
    DynProps = <>
    Enabled = False
    EditButtons = <>
    ParentCtl3D = False
    TabOrder = 4
    Visible = False
    OnExit = EditExit
    OnKeyDown = EditKeyDown
  end
  object sPanel1: TsPanel
    Left = 0
    Top = 0
    Width = 976
    Height = 55
    Align = alTop
    TabOrder = 5
    SkinData.SkinSection = 'PANEL'
    DesignSize = (
      976
      55)
    object sLabel2: TsLabel
      Left = 12
      Top = 10
      Width = 42
      Height = 13
      Caption = #1055#1086#1080#1089#1082':'
      ParentFont = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
    end
    object SBtn1: TsSpeedButton
      Tag = 1
      Left = 905
      Top = 5
      Width = 66
      Height = 22
      Anchors = [akTop, akRight]
      Caption = #1042#1099#1073#1086#1088
      OnClick = SBtnClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object EditSearch: TsEdit
      Left = 60
      Top = 3
      Width = 839
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnChange = EditSearchChange
      OnClick = EditSearchClick
      OnEnter = EditSearchEnter
      OnExit = EditSearchExit
      OnKeyDown = EditSearchKeyDown
      OnKeyUp = EditSearchKeyUp
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
    object sCheckBox1: TsCheckBox
      Left = 16
      Top = 30
      Width = 343
      Height = 20
      Caption = #1056#1077#1078#1080#1084' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1080#1103' (<F4> -'#1087#1077#1088#1077#1082#1083#1102#1095#1077#1085#1080#1077' '#1088#1077#1078#1080#1084#1072')'
      TabOrder = 1
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
  end
  object sStatusBar1: TsStatusBar
    Left = 0
    Top = 642
    Width = 976
    Height = 19
    Panels = <
      item
        Width = 100
      end
      item
        Width = 150
      end
      item
        Width = 250
      end
      item
        Width = 60
      end
      item
        Width = 200
      end>
    SkinData.SkinSection = 'STATUSBAR'
  end
  object ComboBox1: TComboBox
    Left = 472
    Top = 304
    Width = 145
    Height = 21
    Ctl3D = False
    Enabled = False
    ParentCtl3D = False
    TabOrder = 7
    Text = 'ComboBox1'
    Visible = False
    OnExit = EditExit
    OnKeyDown = EditKeyDown
  end
  object DataSource1: TDataSource
    DataSet = MemTableEh1
    Left = 152
    Top = 120
  end
  object Query1: TQuery
    AfterClose = RxQuery1AfterClose
    DatabaseName = 'TransDB'
    Filtered = True
    Left = 216
    Top = 120
  end
  object MemTableEh1: TMemTableEh
    Filtered = True
    Params = <>
    AfterScroll = RxQuery1AfterScroll
    OnCalcFields = MemTableEh1CalcFields
    OnFilterRecord = RxQuery1FilterRecord
    Left = 296
    Top = 120
  end
  object DataSetDriverEh1: TDataSetDriverEh
    Left = 200
    Top = 432
  end
  object Query2: TQuery
    DatabaseName = 'TransDB'
    Left = 472
    Top = 120
  end
end
