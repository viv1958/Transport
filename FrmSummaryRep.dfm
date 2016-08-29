object FormSummaryRep: TFormSummaryRep
  Left = 0
  Top = 0
  Caption = #1057#1091#1084#1084#1072#1088#1085#1099#1077' '#1086#1090#1095#1077#1090#1099
  ClientHeight = 504
  ClientWidth = 1192
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object sStatusBar1: TsStatusBar
    Left = 0
    Top = 485
    Width = 1192
    Height = 19
    Panels = <
      item
        Width = 150
      end
      item
        Width = 250
      end
      item
        Width = 150
      end
      item
        Width = 150
      end
      item
        Width = 2000
      end>
    SkinData.SkinSection = 'STATUSBAR'
  end
  object sPageControl1: TsPageControl
    Left = 0
    Top = 40
    Width = 1192
    Height = 445
    ActivePage = sTabSheet2
    Align = alClient
    TabOrder = 1
    OnChange = sPageControl1Change
    SkinData.SkinSection = 'PAGECONTROL'
    object sTabSheet1: TsTabSheet
      Tag = 1
      Caption = '1. '#1050#1083#1080#1077#1085#1090#1099
      SkinData.CustomColor = False
      SkinData.CustomFont = False
      object DBGridEh1: TDBGridEh
        Tag = 1
        Left = 0
        Top = 34
        Width = 1184
        Height = 383
        Align = alClient
        DataSource = DataSource1
        DynProps = <>
        FooterRowCount = 2
        FooterParams.Color = clMoneyGreen
        FrozenCols = 1
        GridLineParams.DataHorzLines = True
        IndicatorOptions = [gioShowRowIndicatorEh, gioShowRecNoEh]
        Options = [dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
        OptionsEh = [dghFixed3D, dghClearSelection, dghAutoSortMarking, dghMultiSortMarking, dghDialogFind, dghShowRecNo, dghColumnResize, dghExtendVertLines]
        ParentShowHint = False
        RowDetailPanel.Height = 510
        SearchPanel.Enabled = True
        SearchPanel.FilterOnTyping = True
        ShowHint = True
        SortLocal = True
        STFilter.Local = True
        TabOrder = 0
        TitleParams.MultiTitle = True
        OnEnter = DBGridEhEnter
        OnExit = DBGridEhExit
        OnGetCellParams = DBGridEh1GetCellParams
        OnKeyDown = DBGridEhKeyDown
        OnKeyPress = DBGridEhKeyPress
        OnSortMarkingChanged = DBGridEh1SortMarkingChanged
        Columns = <
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'CLIENT_NAME'
            Footers = <>
            Title.Caption = #1050#1083#1080#1077#1085#1090
            Title.TitleButton = True
            Title.ToolTips = True
            ToolTips = True
            Width = 425
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_01'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.TitleButton = True
            Title.ToolTips = True
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_02'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_03'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_04'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_05'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_06'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_07'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_08'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_09'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_10'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_11'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_12'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            ToolTips = True
          end
          item
            Color = clCream
            DynProps = <>
            EditButtons = <>
            FieldName = 'INCOME_13'
            Footers = <
              item
                Color = clSkyBlue
                ValueType = fvtStaticText
              end
              item
                Color = clSkyBlue
                ValueType = fvtStaticText
              end>
            Title.Caption = #1057#1091#1084#1084#1072
            ToolTips = True
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sPanel2: TsPanel
        Left = 0
        Top = 0
        Width = 1184
        Height = 34
        Align = alTop
        TabOrder = 1
        SkinData.SkinSection = 'PANEL'
        object sCheckBox1: TsCheckBox
          Tag = 1
          Left = 19
          Top = 7
          Width = 246
          Height = 20
          Caption = #1055#1086#1082#1072#1079#1072#1090#1100' '#1090#1086#1083#1100#1082#1086' '#1074#1099#1073#1088#1072#1085#1085#1099#1077' '#1089#1090#1088#1086#1082#1080
          TabOrder = 0
          OnClick = sCheckBoxClick
          SkinData.SkinSection = 'CHECKBOX'
          ImgChecked = 0
          ImgUnchecked = 0
        end
        object sCheckBox2: TsCheckBox
          Tag = 2
          Left = 296
          Top = 7
          Width = 136
          Height = 20
          Caption = #1055#1086#1082#1072#1079#1072#1090#1100' '#1082#1086#1087#1077#1081#1082#1080
          TabOrder = 1
          OnClick = sCheckBoxClick
          SkinData.SkinSection = 'CHECKBOX'
          ImgChecked = 0
          ImgUnchecked = 0
        end
      end
    end
    object sTabSheet2: TsTabSheet
      Tag = 2
      Caption = '2. '#1058#1088#1072#1085#1089#1087#1086#1088#1090#1085#1099#1077' '#1089#1088#1077#1076#1089#1090#1074#1072
      SkinData.CustomColor = False
      SkinData.CustomFont = False
      object sPanel3: TsPanel
        Left = 0
        Top = 0
        Width = 1184
        Height = 34
        Align = alTop
        TabOrder = 0
        SkinData.SkinSection = 'PANEL'
        object sCheckBox4: TsCheckBox
          Tag = 1
          Left = 19
          Top = 7
          Width = 246
          Height = 20
          Caption = #1055#1086#1082#1072#1079#1072#1090#1100' '#1090#1086#1083#1100#1082#1086' '#1074#1099#1073#1088#1072#1085#1085#1099#1077' '#1089#1090#1088#1086#1082#1080
          TabOrder = 0
          OnClick = sCheckBoxClick
          SkinData.SkinSection = 'CHECKBOX'
          ImgChecked = 0
          ImgUnchecked = 0
        end
      end
      object DBGridEh2: TDBGridEh
        Tag = 2
        Left = 0
        Top = 34
        Width = 1184
        Height = 383
        Align = alClient
        DataSource = DataSource2
        DynProps = <>
        FooterRowCount = 2
        FooterParams.Color = clMoneyGreen
        FrozenCols = 2
        GridLineParams.DataHorzLines = True
        IndicatorOptions = [gioShowRowIndicatorEh, gioShowRecNoEh]
        Options = [dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
        OptionsEh = [dghFixed3D, dghClearSelection, dghAutoSortMarking, dghMultiSortMarking, dghDialogFind, dghShowRecNo, dghColumnResize, dghExtendVertLines]
        ParentShowHint = False
        RowDetailPanel.Height = 510
        SearchPanel.Enabled = True
        SearchPanel.FilterOnTyping = True
        ShowHint = True
        SortLocal = True
        STFilter.Local = True
        TabOrder = 1
        TitleParams.MultiTitle = True
        OnEnter = DBGridEhEnter
        OnExit = DBGridEhExit
        OnGetCellParams = DBGridEh1GetCellParams
        OnKeyDown = DBGridEhKeyDown
        OnKeyPress = DBGridEhKeyPress
        OnSortMarkingChanged = DBGridEh1SortMarkingChanged
        Columns = <
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRANSPORT_NAME'
            Footers = <>
            Title.Caption = #1058#1088#1072#1085#1089#1087#1086#1088#1090
            Title.TitleButton = True
            Title.ToolTips = True
            ToolTips = True
            Width = 191
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'REG_NUMBER'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = #1056#1077#1075'-'#1099#1081' '#1085#1086#1084#1077#1088
            Title.TitleButton = True
            Title.ToolTips = True
            ToolTips = True
            Width = 75
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_01'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '1|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_01'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '1|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_01'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '1|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_02'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '2|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_02'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '2|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_02'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '2|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_03'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '3|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_03'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '3|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_03'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '3|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_04'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '4|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_04'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '4|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_04'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '4|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_05'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '5|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_05'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '5|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_05'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '5|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_06'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '6|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_06'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '6|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_06'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '6|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_07'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '7|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_07'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '7|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_07'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '7|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_08'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '8|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_08'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '8|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_08'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '8|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_09'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '9|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_09'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '9|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_09'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '9|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_10'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '10|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_10'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '10|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_10'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '10|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_11'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '11|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_11'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '11|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_11'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '11|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_12'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '12|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_12'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '12|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_12'
            Footers = <
              item
                ValueType = fvtStaticText
              end
              item
                ValueType = fvtStaticText
              end>
            Title.Caption = '12|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end
          item
            Color = clCream
            DynProps = <>
            EditButtons = <>
            FieldName = 'EXC_PAY_13'
            Footers = <
              item
                Color = clSkyBlue
                ValueType = fvtStaticText
              end
              item
                Color = clSkyBlue
                ValueType = fvtStaticText
              end>
            Title.Caption = #1057#1091#1084#1084#1072'|'#1048#1089#1087#1086#1083#1085'.'
            ToolTips = True
            Width = 57
          end
          item
            Color = clCream
            DynProps = <>
            EditButtons = <>
            FieldName = 'OUT_VAL_13'
            Footers = <
              item
                Color = clSkyBlue
                ValueType = fvtStaticText
              end
              item
                Color = clSkyBlue
                ValueType = fvtStaticText
              end>
            Title.Caption = #1057#1091#1084#1084#1072'|'#1056#1072#1089#1093#1086#1076#1099
            ToolTips = True
            Width = 57
          end
          item
            Color = clCream
            DynProps = <>
            EditButtons = <>
            FieldName = 'TRP_VAL_13'
            Footers = <
              item
                Color = clSkyBlue
                ValueType = fvtStaticText
              end
              item
                Color = clSkyBlue
                ValueType = fvtStaticText
              end>
            Title.Caption = #1057#1091#1084#1084#1072'|'#1056#1072#1079#1085#1080#1094#1072
            ToolTips = True
            Width = 57
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
    end
  end
  object sPanel1: TsPanel
    Left = 0
    Top = 0
    Width = 1192
    Height = 40
    Align = alTop
    TabOrder = 2
    SkinData.SkinSection = 'PANEL'
    object sSpeedButton1: TsSpeedButton
      Tag = 1
      Left = 23
      Top = 6
      Width = 95
      Height = 22
      Hint = #1054#1073#1085#1086#1074#1080#1090#1100' '#1076#1072#1085#1085#1099#1077' '#1080#1079' '#1073#1072#1079#1099' (F5)'
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000000000000000
        000000000000000000000000000A000000250000003300000033000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000022251B0E5C876132C9B88444FFB98545FF000000000000
        0000000000330000003300000033000000330000003300000032000000000000
        00000000001E7B582EBBBE8A4AFFDEAC66FFF4C57BFFB88343FF000000000000
        0000B98545FFB78343FFB68142FFB78242FFB98444FFB78445FB000000000000
        00066D4E29AAC18C4CFFECBC72FFF1C581FFF8D39DFFB78242FF000000000000
        0000B78343FFF9C97EFFF6C67BFFF5CC8CFFC49963F100000000000000001710
        093DBA8646FFE9B86DFFEDC07DFFEFCE9CFFD5AC71FFB88343FF000000000000
        0000B68141FFF2C47EFFF0C482FFEAB86FFFBC8947FF0000001A000000007A58
        2EB9D2A059FFE6B368FFEDCC9AFFC08F51FF6749258F1A120923000000000000
        0000B78241FFF5D9ACFFF0CF9FFFEAB86CFFD4A25CFF5D43229900000000B884
        44FFDDAB61FFE2B167FFD4AB77FF6648248E0000000000000000000000000000
        0000B98443FFC1945AFAD7B282FFE6B266FFE0AE65FFB37F41F900000000B883
        44FFDFAB5FFFE2B774FFC6995FFF040301050000000100000000000000000000
        0000B38143F506050209C6975FFFE6BB79FFE5B36AFFB78344FF00000000B883
        43FFDFB373FFDBA85EFFB78243FF000000020302013400000000000000000000
        00000202010300000001B68242FFDFAC63FFE4B877FFB78243FF00000000B883
        42FFE2BB83FFD59F52FFBF8B48FF07050332B58244F800000000000000000000
        00000000000004030120C08C49FFD9A557FFE5C087FFB78242FF00000000B27E
        40F8E1C192FFCF9A4AFFC18C48FF9B7039DABA8545FF00000000000000000000
        00070000001D674A27A5C7924BFFD39E4FFFE3C395FFB88241FF000000005E43
        2181D6B386FFD4A661FFC99243FFE4C79DFFB98443FF00000000000000001A13
        0A4F684B27A5BC8746FFCD984AFFD8AC6DFFD9B98EFF7A562BAA000000000000
        0000BD8D4FFFD1A668FFC48B39FFD9B580FFB88241FF0000000000000000BA86
        46FFC28D45FFC99344FFD09E56FFE7CEAAFFBD8B4FFF1610081F000000000000
        0032BE9664F1E6CFACFFE9D3B2FFEAD5B4FFB88341FF0000000000000000B984
        44FFCD9C54FFDAB57FFFEAD5B5FFC69A64FF6C4D27950000000000000000B884
        45FBB98444FFB88241FFB8813FFFB88241FFBA8545FF0000000000000000B983
        42FFEAD5B6FFDBBD95FFC09054FF7B572CAA0000000000000000000000000000
        000000000000000000000000000000000000000000000000000000000000BA85
        44FFBB8849FF875F30BB251B0E33000000000000000000000000}
      ParentShowHint = False
      ShowHint = True
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton4: TsSpeedButton
      Tag = 4
      Left = 697
      Top = 6
      Width = 95
      Height = 22
      Hint = #1042#1099#1073#1088#1072#1090#1100' '#1074#1089#1077' '#1079#1072#1087#1080#1089#1080' '#1074' '#1090#1077#1082#1091#1097#1077#1081' '#1090#1072#1073#1083#1080#1094#1077' (Grey+)'
      Caption = #1042#1099#1073#1086#1088
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000330000003300000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000230000003300000026979492FF8B8785FF00000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000625F5FBE8D8A88FF686664CDDBDADAFF797776E300000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00008F8D8BFFBCBAB9FF9F9C9BFFE0DFDEFF4949479D0000002F000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000908E8CFFD8D6D5FFDEDCDBFFA9A7A6FF8F8D8BFF898785EF000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000092908EFFE0DEDDFFD1D0CFFFDFDDDCFFC8C6C4FFA09E9CFF000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000959390FFEBEAE9FFDEDDDCFFCAC9C9FFA09E9CFF00000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000999795FFF9FAF9FFCBCBCAFFA09E9CFF0000000000000000000000000000
        0033000000000000003300000000000000330000000000000033000000000000
        0033A09E9CFFC4C4C1FFA09E9CFF000000000000000000000000000000008181
        81FF00000000818181FF00000000818181FF00000000818181FF000000007E7E
        7EFFA09E9CFFA09E9CFF00000000000000000000000000000000000000330000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000330000000000000000000000000000000000000000818181FF0000
        0000000000000000000000000000000000000000000000000000000000000000
        00007F7F7FFF0000000000000000000000000000000000000000000000330000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000330000000000000000000000000000000000000000818181FF0000
        0000000000000000000000000000000000000000000000000000000000000000
        0000818181FF0000000000000000000000000000000000000000000000000000
        0033000000000000003300000000000000330000000000000033000000000000
        0033000000000000000000000000000000000000000000000000000000008181
        81FF00000000818181FF00000000818181FF00000000818181FF000000008181
        81FF000000000000000000000000000000000000000000000000}
      ParentShowHint = False
      ShowHint = True
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton5: TsSpeedButton
      Tag = 5
      Left = 802
      Top = 6
      Width = 95
      Height = 22
      Hint = #1054#1084#1077#1085#1080#1090#1100' '#1074#1099#1073#1086#1088' '#1074#1089#1077#1093' '#1079#1072#1087#1080#1089#1077#1081' '#1074' '#1090#1077#1082#1091#1097#1077#1081' '#1090#1072#1073#1083#1080#1094#1077' (Grey-)'
      Caption = #1054#1090#1084#1077#1085#1072
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000000000000000001B0000
        0033000000330000001B00000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000524337A0957A
        63FF957A63FF5142369E00000000000000330000003300000033000000330000
        00330000000000000033000000330000003300000033000000339C816BFFE4CC
        B3FFE4CCB3FF9D826CFF0000000097765EFFBDA48EFFBAA18BFFBAA18BFFBDA4
        8EFF0000000097765EFFBDA48EFFBAA18BFFBAA08AFFBAA08AFFA28973FFFAEE
        DEFFFAEEDEFFA38A74FF00000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000594D4285AA91
        7CFFAA917DFF584C428300000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000000000000000002F0000
        0033000000330000003300000033000000330000000000000000000000000000
        0000000000000000000000000000000000000000000000000000AE7B3BF1B981
        3BFFB8803CFFB8813EFFB98240FFBA8544FF0000000000000000000000000000
        0000000000000000000000000000000000000000002400000031B7813FFFFDE5
        C2FFECBA6DFFEDBC6FFFEBD2AFFF795933AF0000000000000000000000000000
        000000000000000000000000000000000021825E31C1B68344F9B6803EFFF4DB
        B5FFDDA859FFDFAB5EFFC7934DFF7E592EBF00000030000000150000000A0000
        000A0000000A00000015000000317B582EB9BB8747FFBB8747FFB6803EFFF9ED
        D9FFEFD9B8FFDCAE6CFFD7A050FFC48E47FFAE7A3EF44C361B8623190D59241A
        0D5B23190D594C361B87B27E3FF6C29357FFBB8646FF34261447B88241FFDFC0
        91FFC69454FFEDDABCFFE6CBA3FFDCB47BFFCFA060FFC6995FFFC4965EFFC597
        5EFFC5975FFFCEA571FFE2C7A0FFC5975DFF7C592EAA00000000BA8545FF7755
        2AA37351289FBD8B4EFFD9B98FFFE9D4B7FFECDBBFFFEDDBBFFFEDDBBFFFEDDC
        C0FFE7D1B0FFD3B081FFBC8948FF6D4E28960000000000000000000000000000
        000000000000251B0E3379562BA8B07C3DF5B7813EFFB7803EFFB7813EFFB781
        3EFFB8823FFF7A572BA80705030A000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000}
      ParentShowHint = False
      ShowHint = True
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton6: TsSpeedButton
      Tag = 6
      Left = 907
      Top = 6
      Width = 95
      Height = 22
      Hint = #1055#1077#1095#1072#1090#1100' '#1090#1077#1082#1091#1097#1077#1081' '#1090#1072#1073#1083#1080#1094#1099
      Caption = #1055#1077#1095#1072#1090#1100
      Enabled = False
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000000000000000
        0000000000000000000000000023000000330000003300000033000000330000
        0033000000330000002300000000000000000000000000000000000000000000
        00000000000000000000805E39BFB5844EFFB3824BFFB3814BFFB3814BFFB382
        4BFFB5844EFF805E39BF00000000000000000000000000000000000000230000
        00330000003300000033BA854BFFFFFFFCFFFFFFF5FFFFFFF4FFFFFFF4FFFFFF
        F5FFFFFFFCFFBA854BFF000000330000003300000033000000235B5B5BC08181
        81FF818182FF7F8386FFBD8546FFFFFFF7FFFFF3DAFFFFF2D9FFFFF2D9FFFFF3
        DAFFFFFFF7FFBD8546FF7F8386FF818182FF818181FF5B5B5BC0818181FFD5D2
        D1FFCBC9C9FF7D7C7CFF676768FFA8A6A8FFA4A2A4FFA3A2A3FFA3A2A3FFA4A2
        A4FFA8A6A8FF676768FF7D7C7CFFCBC9C9FFD5D2D1FF818181FF7F7F7FFFDAD7
        D6FFC2BFBEFFC8C5C4FFAFACACFFAFACABFFADAAAAFFADAAAAFFADAAAAFFADAA
        AAFFAFACABFFAFACACFFC8C5C4FFC2BFBEFFDAD7D6FF7F7F7FFF7E7E7EFFE1E0
        DFFFBDBBB9FF92908EFF7B7977FF7D7B78FF7D7B78FF7D7B78FF7D7B78FF7D7B
        78FF7D7B78FF7B7977FF92908EFFBDBBB9FFE1E0DFFF7E7E7EFF7D7D7DFFEDEB
        EBFFB8B5B3FF646261FF6B6968FF6C6A69FF6C6A69FF6C6A69FF6C6A69FF6C6A
        69FF6C6A69FF6B6968FF646261FFB8B5B3FFEDEBEBFF7D7D7DFF7C7C7DFFF9F8
        F8FFF3F4F2FF949190FF9B9897FF9C9998FF9C9998FF9C9998FF9C9998FF9C99
        98FF9C9998FF9B9897FF949190FFF3F4F2FFF9F8F8FF7C7C7DFF7C7C7DFFF4F3
        F2FFD3D1D0FF827F7EFF888685FF898686FF898685FF898685FF898685FF8986
        85FF898686FF888685FF827F7EFFD3D1D0FFF4F3F2FF7C7C7DFF7E7E7EFFFFFF
        FFFFFFFFFFFF6D6B6AFF706F6FFF6C6B6BFF6A6867FF6A6867FF6A6867FF6A68
        67FF6C6B6BFF706F6FFF6D6B6AFFFFFFFFFFFFFFFFFF7E7E7EFF5A5A5AB07F7F
        7FFF7F7F80FF808387FFBF8648FFFFFFF8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFF8FFBF8648FF808387FF7F7F80FF7F7F7FFF5A5A5AB0000000000000
        00000000000075777AFFBA8347FFFFFFF3FFFFF0DDFFFFEFDCFFFFEFDCFFFFF0
        DDFFFFFFF3FFBA8347FF75777AFF000000000000000000000000000000000000
        00000000000000000000B78349FFFFFFF4FFFFE1C0FFFFE0BFFFFFE0BFFFFFE1
        C0FFFFFFF4FFB78349FF00000000000000000000000000000000000000000000
        00000000000000000000B7854EFFFFFFFDFFFFFFF5FFFFFEF4FFFFFEF4FFFFFF
        F5FFFFFFFDFFB7854EFF00000000000000000000000000000000000000000000
        000000000000000000007F5F3BB0B5844FFFB3824BFFB3814BFFB3814BFFB382
        4BFFB5844FFF7F5F3BB000000000000000000000000000000000}
      ParentShowHint = False
      ShowHint = True
      Visible = False
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton7: TsSpeedButton
      Tag = 7
      Left = 1034
      Top = 6
      Width = 93
      Height = 22
      Hint = #1055#1088#1086#1089#1084#1086#1090#1088' '#1080' '#1087#1077#1095#1072#1090#1100' '#1086#1090#1095#1077#1090#1086#1074' '
      Caption = #1055#1088#1086#1089#1084#1086#1090#1088
      Enabled = False
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000000000000000
        002F000000330000003300000033000000330000003300000033000000330000
        003300000033000000330000003300000033000000300000000000000000AB80
        51F0B88956FFB88A57FFB88955FFB58550FFB4834CFFB4834CFFB4834CFFB483
        4CFFB4834CFFB4834CFFB4834CFFB58550FFAD8050F20000000000000033BA88
        51FFFFDFAAFFBC8D58FFB5844FFFFFF9EDFFFEF2E4FFFDF1E3FFFDF1E3FFFDF1
        E3FFFDF1E3FFFDF1E3FFFEF2E4FFFFF9EDFFB58550FF00000000888E97FFC3CA
        D4FF57616EFFC6975EFFB4824BFFFEF2E4FFF8E7D4FFF7E6D3FFF7E6D3FFF7E6
        D3FFF7E6D3FFF7E6D3FFF8E7D4FFFEF2E4FFB4834CFF0000000000000000BC89
        51FFAA7A3FFFCB9F65FFB2814BFFFCF1E3FFF6E3CEFFF5E2CDFFF5E2CCFFF5E2
        CCFFF5E2CCFFF5E2CDFFF6E3CEFFFCF1E3FFB4834CFF0000000000000033BA88
        50FFFFDFA4FFD0A568FFB2804AFFFDF1E3FFF4E0C7FFF4DEC4FFF4DEC3FFF4DE
        C3FFF4DEC3FFF4DEC4FFF4E0C7FFFEF1E3FFB4834CFF00000000888E97FFC3CA
        D4FF555F6DFFD9AE6FFFB2804AFFFCF1E4FFF3DBC1FFFEF6EEFFFFFFFFFFFFFF
        FFFFFFFFFFFFFEF7EFFFF3DCC1FFFCF1E4FFB4834CFF0000000000000000BC88
        51FFA67B3AFFDEB576FFB17F49FFFDF2E4FFF2D9BBFFFFFFFFFFBABBBCFFBDBE
        BEFF818283FFFFFFFFFFF2D9BBFFFEF3E4FFB4834CFF0000000000000033BA87
        50FFFFE09FFFE3BB7AFFB17E49FFFDF3E7FFF2D6B6FFFFFFFFFF818384FFBDBE
        BEFFBABBBCFFFFFFFFFFF2D6B6FFFEF4E7FFB4834CFF00000000888E97FFC3CA
        D4FF545E6DFFEBC47FFFB17E49FFFEF5EAFFF1D3B3FFFEF4EBFFFFFFFFFFFFFF
        FFFFFFFFFFFFFDF4EAFFF1D3B3FFFFF6EAFFB4834CFF0000000000000000BC89
        51FFA47C36FFECC581FFB07E49FFFEF8EEFFF0D2B1FFF1D3B1FFF3D5B3FFF2D4
        B2FFF2D4B1FFF0D2B0FFF0D2B1FFFFF9EFFFB4824CFF0000000000000033BA87
        50FFF9D18BFFEBC47FFFB07D48FFFFFAF2FFEFD0ADFFF1D4B2FFAB773EFFCFA6
        7AFFCDA477FFF0D2B0FFEFD0ACFFFFFBF3FFB4824CFF00000000888D97FFC1C8
        D2FF525A67FFEBC37BFFB07D46FFFFFDF8FFEECCA6FFEFCEA9FFF0D1ACFFF0D1
        ACFFF0CFABFFEECDA8FFEECCA6FFFFFEF9FFB4834CFF0000000000000000BA86
        4EFFFFF2D4FFFEF1D4FFB27F49FFFFFFFFFFFFFEFAFFFFFEFAFFFFFFFBFFFFFF
        FBFFFFFEFAFFFFFEFAFFFFFEFAFFFFFFFFFFB5844FFF00000000000000009C74
        49D7B78752FFB68652FFB78752FFB5844EFFB4824CFFB4824BFFB4824BFFB482
        4BFFB4824BFFB4824BFFB4824CFFB5844FFFAC8050EF00000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000}
      ParentShowHint = False
      ShowHint = True
      Visible = False
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton31: TsSpeedButton
      Tag = 31
      Left = 135
      Top = 6
      Width = 35
      Height = 22
      Hint = #1053#1072#1079#1072#1076' '#1085#1072' '#1086#1076#1080#1085' '#1076#1077#1085#1100
      Glyph.Data = {
        16050000424D160500000000000036040000280000000E0000000E0000000100
        080000000000E000000000000000000000000001000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
        A6000020400000206000002080000020A0000020C0000020E000004000000040
        20000040400000406000004080000040A0000040C0000040E000006000000060
        20000060400000606000006080000060A0000060C0000060E000008000000080
        20000080400000806000008080000080A0000080C0000080E00000A0000000A0
        200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
        200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
        200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
        20004000400040006000400080004000A0004000C0004000E000402000004020
        20004020400040206000402080004020A0004020C0004020E000404000004040
        20004040400040406000404080004040A0004040C0004040E000406000004060
        20004060400040606000406080004060A0004060C0004060E000408000004080
        20004080400040806000408080004080A0004080C0004080E00040A0000040A0
        200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
        200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
        200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
        20008000400080006000800080008000A0008000C0008000E000802000008020
        20008020400080206000802080008020A0008020C0008020E000804000008040
        20008040400080406000804080008040A0008040C0008040E000806000008060
        20008060400080606000806080008060A0008060C0008060E000808000008080
        20008080400080806000808080008080A0008080C0008080E00080A0000080A0
        200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
        200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
        200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
        2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
        2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
        2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
        2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
        2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
        2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
        2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00F7F7F7F7F7F7
        F7F7F7F7F7F7F7F70000F7F7F7F7F7F7F7F7F7F7F7F700F70000F7F7F7F7F7F7
        F7F7F7F7000000F70000F7F7F7F7F7F7F7F70000000000F70000F7F7F7F7F7F7
        00000000000000F70000F7F7F7F7000000000000000000F70000F7F700000000
        00000000000000F7000000000000000000000000000000F70000F7F700000000
        00000000000000F70000F7F7F7F7000000000000000000F70000F7F7F7F7F7F7
        00000000000000F70000F7F7F7F7F7F7F7F70000000000F70000F7F7F7F7F7F7
        F7F7F7F7000000F70000F7F7F7F7F7F7F7F7F7F7F7F700F70000}
      ParentShowHint = False
      ShowHint = True
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton32: TsSpeedButton
      Tag = 32
      Left = 178
      Top = 6
      Width = 65
      Height = 22
      Hint = #1047#1072#1082#1072#1079#1099', '#1080#1089#1087#1086#1083#1085#1103#1077#1084#1099#1077' '#1074#1095#1077#1088#1072
      Caption = #1042#1095#1077#1088#1072
      ParentShowHint = False
      ShowHint = True
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton33: TsSpeedButton
      Tag = 33
      Left = 255
      Top = 6
      Width = 65
      Height = 22
      Hint = #1047#1072#1082#1072#1079#1099', '#1080#1089#1087#1086#1083#1085#1103#1077#1084#1099#1077' '#1089#1077#1075#1086#1076#1085#1103
      Caption = #1057#1077#1075#1086#1076#1085#1103
      ParentShowHint = False
      ShowHint = True
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton34: TsSpeedButton
      Tag = 34
      Left = 331
      Top = 6
      Width = 65
      Height = 22
      Hint = #1047#1072#1082#1072#1079#1099', '#1080#1089#1087#1086#1083#1085#1103#1077#1084#1099#1077' '#1079#1072#1074#1090#1088#1072
      Caption = #1047#1072#1074#1090#1088#1072
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton35: TsSpeedButton
      Tag = 35
      Left = 405
      Top = 6
      Width = 35
      Height = 22
      Hint = #1042#1087#1077#1088#1077#1076' '#1085#1072' '#1086#1076#1080#1085' '#1076#1077#1085#1100
      Glyph.Data = {
        16050000424D160500000000000036040000280000000E0000000E0000000100
        080000000000E000000000000000000000000001000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
        A6000020400000206000002080000020A0000020C0000020E000004000000040
        20000040400000406000004080000040A0000040C0000040E000006000000060
        20000060400000606000006080000060A0000060C0000060E000008000000080
        20000080400000806000008080000080A0000080C0000080E00000A0000000A0
        200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
        200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
        200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
        20004000400040006000400080004000A0004000C0004000E000402000004020
        20004020400040206000402080004020A0004020C0004020E000404000004040
        20004040400040406000404080004040A0004040C0004040E000406000004060
        20004060400040606000406080004060A0004060C0004060E000408000004080
        20004080400040806000408080004080A0004080C0004080E00040A0000040A0
        200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
        200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
        200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
        20008000400080006000800080008000A0008000C0008000E000802000008020
        20008020400080206000802080008020A0008020C0008020E000804000008040
        20008040400080406000804080008040A0008040C0008040E000806000008060
        20008060400080606000806080008060A0008060C0008060E000808000008080
        20008080400080806000808080008080A0008080C0008080E00080A0000080A0
        200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
        200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
        200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
        2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
        2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
        2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
        2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
        2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
        2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
        2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00F700F7F7F7F7
        F7F7F7F7F7F7F7F70000F7000000F7F7F7F7F7F7F7F7F7F70000F70000000000
        F7F7F7F7F7F7F7F70000F700000000000000F7F7F7F7F7F70000F70000000000
        00000000F7F7F7F70000F70000000000000000000000F7F70000F70000000000
        00000000000000000000F70000000000000000000000F7F70000F70000000000
        00000000F7F7F7F70000F700000000000000F7F7F7F7F7F70000F70000000000
        F7F7F7F7F7F7F7F70000F7000000F7F7F7F7F7F7F7F7F7F70000F700F7F7F7F7
        F7F7F7F7F7F7F7F70000F7F7F7F7F7F7F7F7F7F7F7F7F7F70000}
      ParentShowHint = False
      ShowHint = True
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sLabel2: TsLabel
      Left = 462
      Top = 10
      Width = 7
      Height = 13
      Caption = #1057
      ParentFont = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
    end
    object sLabel3: TsLabel
      Left = 567
      Top = 10
      Width = 14
      Height = 13
      Caption = #1087#1086
      ParentFont = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
    end
    object sDateEdit1: TsDateEdit
      Tag = 1
      Left = 472
      Top = 7
      Width = 93
      Height = 21
      AutoSize = False
      Color = clWhite
      EditMask = '!99/99/9999;1; '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 10
      ParentFont = False
      TabOrder = 0
      Text = '  .  .    '
      BoundLabel.Indent = 0
      BoundLabel.Font.Charset = DEFAULT_CHARSET
      BoundLabel.Font.Color = clWindowText
      BoundLabel.Font.Height = -11
      BoundLabel.Font.Name = 'Tahoma'
      BoundLabel.Font.Style = []
      BoundLabel.Layout = sclLeft
      BoundLabel.MaxWidth = 0
      BoundLabel.UseSkinColor = True
      SkinData.SkinSection = 'EDIT'
      GlyphMode.Blend = 0
      GlyphMode.Grayed = False
      OnAcceptDate = sDateEditAcceptDate
    end
    object sDateEdit2: TsDateEdit
      Tag = 2
      Left = 582
      Top = 7
      Width = 93
      Height = 21
      AutoSize = False
      Color = clWhite
      EditMask = '!99/99/9999;1; '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 10
      ParentFont = False
      TabOrder = 1
      Text = '  .  .    '
      BoundLabel.Indent = 0
      BoundLabel.Font.Charset = DEFAULT_CHARSET
      BoundLabel.Font.Color = clWindowText
      BoundLabel.Font.Height = -11
      BoundLabel.Font.Name = 'Tahoma'
      BoundLabel.Font.Style = []
      BoundLabel.Layout = sclLeft
      BoundLabel.MaxWidth = 0
      BoundLabel.UseSkinColor = True
      SkinData.SkinSection = 'EDIT'
      GlyphMode.Blend = 0
      GlyphMode.Grayed = False
      OnAcceptDate = sDateEditAcceptDate
    end
  end
  object DataSource1: TDataSource
    DataSet = MemTableEh1
    Left = 192
    Top = 368
  end
  object Query1: TQuery
    Tag = 1
    DatabaseName = 'TransDB'
    SQL.Strings = (
      'select * from sel_clients_Summary('#39'1.1.16'#39','#39'1.2.16'#39')')
    Left = 192
    Top = 208
  end
  object MemTableEh1: TMemTableEh
    Tag = 1
    Filtered = True
    Params = <>
    DataDriver = DataSetDriverEh1
    SortOrder = 'Client_Name'
    AfterOpen = MemTableEh1AfterOpen
    AfterClose = MemTableEh1AfterClose
    BeforeScroll = MemTableEh1BeforeScroll
    AfterScroll = MemTableEh1AfterScroll
    OnFilterRecord = MemTableEh1FilterRecord
    Left = 192
    Top = 320
    object MemTableEh1FLAG_MES: TIntegerField
      FieldName = 'FLAG_MES'
    end
    object MemTableEh1CLIENT_ID: TIntegerField
      FieldName = 'CLIENT_ID'
    end
    object MemTableEh1CLIENT_NAME: TStringField
      FieldName = 'CLIENT_NAME'
      Size = 64
    end
    object MemTableEh1INCOME_01: TFloatField
      FieldName = 'INCOME_01'
    end
    object MemTableEh1INCOME_02: TFloatField
      FieldName = 'INCOME_02'
    end
    object MemTableEh1INCOME_03: TFloatField
      FieldName = 'INCOME_03'
    end
    object MemTableEh1INCOME_04: TFloatField
      FieldName = 'INCOME_04'
    end
    object MemTableEh1INCOME_05: TFloatField
      FieldName = 'INCOME_05'
    end
    object MemTableEh1INCOME_06: TFloatField
      FieldName = 'INCOME_06'
    end
    object MemTableEh1INCOME_07: TFloatField
      FieldName = 'INCOME_07'
    end
    object MemTableEh1INCOME_08: TFloatField
      FieldName = 'INCOME_08'
    end
    object MemTableEh1INCOME_09: TFloatField
      FieldName = 'INCOME_09'
    end
    object MemTableEh1INCOME_10: TFloatField
      FieldName = 'INCOME_10'
    end
    object MemTableEh1INCOME_11: TFloatField
      FieldName = 'INCOME_11'
    end
    object MemTableEh1INCOME_12: TFloatField
      FieldName = 'INCOME_12'
    end
    object MemTableEh1INCOME_13: TFloatField
      FieldName = 'INCOME_13'
    end
  end
  object DataSetDriverEh1: TDataSetDriverEh
    ProviderDataSet = Query1
    Left = 192
    Top = 264
  end
  object Query2: TQuery
    Tag = 2
    DatabaseName = 'TransDB'
    SQL.Strings = (
      'select * from sel_transport_summary('#39'1.1.16'#39','#39'1.2.16'#39')'
      'order by Flag_mes, Transport_Name')
    Left = 328
    Top = 208
  end
  object DataSetDriverEh2: TDataSetDriverEh
    ProviderDataSet = Query2
    Left = 328
    Top = 264
  end
  object MemTableEh2: TMemTableEh
    Tag = 2
    Filtered = True
    Params = <>
    DataDriver = DataSetDriverEh2
    SortOrder = 'Transport_Name,Reg_Number'
    AfterOpen = MemTableEh1AfterOpen
    AfterClose = MemTableEh1AfterClose
    BeforeScroll = MemTableEh1AfterScroll
    AfterScroll = MemTableEh1AfterScroll
    OnFilterRecord = MemTableEh1FilterRecord
    Left = 328
    Top = 320
    object MemTableEh2FLAG_MES: TIntegerField
      FieldName = 'FLAG_MES'
    end
    object MemTableEh2TRANSPORT_ID: TIntegerField
      FieldName = 'TRANSPORT_ID'
    end
    object MemTableEh2TRANSPORT_NAME: TStringField
      FieldName = 'TRANSPORT_NAME'
      Size = 64
    end
    object MemTableEh2REG_NUMBER: TStringField
      FieldName = 'REG_NUMBER'
      Size = 16
    end
    object MemTableEh2EXC_PAY_01: TIntegerField
      FieldName = 'EXC_PAY_01'
    end
    object MemTableEh2EXC_PAY_02: TIntegerField
      FieldName = 'EXC_PAY_02'
    end
    object MemTableEh2EXC_PAY_03: TIntegerField
      FieldName = 'EXC_PAY_03'
    end
    object MemTableEh2EXC_PAY_04: TIntegerField
      FieldName = 'EXC_PAY_04'
    end
    object MemTableEh2EXC_PAY_05: TIntegerField
      FieldName = 'EXC_PAY_05'
    end
    object MemTableEh2EXC_PAY_06: TIntegerField
      FieldName = 'EXC_PAY_06'
    end
    object MemTableEh2EXC_PAY_07: TIntegerField
      FieldName = 'EXC_PAY_07'
    end
    object MemTableEh2EXC_PAY_08: TIntegerField
      FieldName = 'EXC_PAY_08'
    end
    object MemTableEh2EXC_PAY_09: TIntegerField
      FieldName = 'EXC_PAY_09'
    end
    object MemTableEh2EXC_PAY_10: TIntegerField
      FieldName = 'EXC_PAY_10'
    end
    object MemTableEh2EXC_PAY_11: TIntegerField
      FieldName = 'EXC_PAY_11'
    end
    object MemTableEh2EXC_PAY_12: TIntegerField
      FieldName = 'EXC_PAY_12'
    end
    object MemTableEh2EXC_PAY_13: TIntegerField
      FieldName = 'EXC_PAY_13'
    end
    object MemTableEh2OUT_VAL_01: TIntegerField
      FieldName = 'OUT_VAL_01'
    end
    object MemTableEh2OUT_VAL_02: TIntegerField
      FieldName = 'OUT_VAL_02'
    end
    object MemTableEh2OUT_VAL_03: TIntegerField
      FieldName = 'OUT_VAL_03'
    end
    object MemTableEh2OUT_VAL_04: TIntegerField
      FieldName = 'OUT_VAL_04'
    end
    object MemTableEh2OUT_VAL_05: TIntegerField
      FieldName = 'OUT_VAL_05'
    end
    object MemTableEh2OUT_VAL_06: TIntegerField
      FieldName = 'OUT_VAL_06'
    end
    object MemTableEh2OUT_VAL_07: TIntegerField
      FieldName = 'OUT_VAL_07'
    end
    object MemTableEh2OUT_VAL_08: TIntegerField
      FieldName = 'OUT_VAL_08'
    end
    object MemTableEh2OUT_VAL_09: TIntegerField
      FieldName = 'OUT_VAL_09'
    end
    object MemTableEh2OUT_VAL_10: TIntegerField
      FieldName = 'OUT_VAL_10'
    end
    object MemTableEh2OUT_VAL_11: TIntegerField
      FieldName = 'OUT_VAL_11'
    end
    object MemTableEh2OUT_VAL_12: TIntegerField
      FieldName = 'OUT_VAL_12'
    end
    object MemTableEh2OUT_VAL_13: TIntegerField
      FieldName = 'OUT_VAL_13'
    end
    object MemTableEh2TRP_VAL_01: TIntegerField
      FieldName = 'TRP_VAL_01'
    end
    object MemTableEh2TRP_VAL_02: TIntegerField
      FieldName = 'TRP_VAL_02'
    end
    object MemTableEh2TRP_VAL_03: TIntegerField
      FieldName = 'TRP_VAL_03'
    end
    object MemTableEh2TRP_VAL_04: TIntegerField
      FieldName = 'TRP_VAL_04'
    end
    object MemTableEh2TRP_VAL_05: TIntegerField
      FieldName = 'TRP_VAL_05'
    end
    object MemTableEh2TRP_VAL_06: TIntegerField
      FieldName = 'TRP_VAL_06'
    end
    object MemTableEh2TRP_VAL_07: TIntegerField
      FieldName = 'TRP_VAL_07'
    end
    object MemTableEh2TRP_VAL_08: TIntegerField
      FieldName = 'TRP_VAL_08'
    end
    object MemTableEh2TRP_VAL_09: TIntegerField
      FieldName = 'TRP_VAL_09'
    end
    object MemTableEh2TRP_VAL_10: TIntegerField
      FieldName = 'TRP_VAL_10'
    end
    object MemTableEh2TRP_VAL_11: TIntegerField
      FieldName = 'TRP_VAL_11'
    end
    object MemTableEh2TRP_VAL_12: TIntegerField
      FieldName = 'TRP_VAL_12'
    end
    object MemTableEh2TRP_VAL_13: TIntegerField
      FieldName = 'TRP_VAL_13'
    end
  end
  object DataSource2: TDataSource
    DataSet = MemTableEh2
    Left = 328
    Top = 360
  end
end
