object FormOrderCopy: TFormOrderCopy
  Left = 0
  Top = 0
  Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1085#1080#1077' '#1079#1072#1082#1072#1079#1072
  ClientHeight = 663
  ClientWidth = 762
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object sPanelM: TsPanel
    Left = 0
    Top = 0
    Width = 762
    Height = 57
    Align = alTop
    ParentBackground = False
    TabOrder = 0
    SkinData.SkinSection = 'PANEL'
    object sSpeedButton2: TsSpeedButton
      Tag = 2
      Left = 541
      Top = 9
      Width = 100
      Height = 22
      Hint = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1076#1072#1090#1099' '#1074' '#1086#1090#1084#1077#1095#1077#1085#1085#1099#1093' '#1084#1077#1089#1103#1094#1072#1093
      Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '
      Glyph.Data = {
        4E010000424D4E01000000000000760000002800000013000000120000000100
        040000000000D800000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777778007777
        777777700000777770000777777777700000777770F000777777777000007777
        770F000000087770000077777770F0087F780770000077777777008777FF8070
        00007777777708777F77F88000007777777707777F77F7000000777777770877
        F7FF7F00000088888888087F7F7777000000878FFF7F888FF777788000008F8F
        777F7088777780700000878FFF7FFF088888077000008F8F777F77F800087770
        0000878FFF7FFFF8777777700000888888888888777777700000878F77777778
        777777700000888888888888777777700000}
      ParentShowHint = False
      ShowHint = True
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton1: TsSpeedButton
      Tag = 1
      Left = 10
      Top = 9
      Width = 100
      Height = 22
      Hint = #1054#1095#1080#1089#1090#1080#1090#1100' '#1074#1099#1073#1088#1072#1085#1085#1099#1077' '#1076#1072#1090#1099
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '
      Glyph.Data = {
        66010000424D6601000000000000760000002800000014000000140000000100
        040000000000F000000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
        88888888000088888888888888888888000088BFBFB888888888888800008888
        888BF88888888888000088888888000888888888000088888880FBF088888888
        00008888880F7FBF088888880000888880F7F87BF0888888000088880F7F87BF
        B708888800008880F7F87BFB78808888000088000F87BFB78880888800008888
        800BFB7888088888000088888880B78887408888000088888888088804440888
        0000888888888000804440880000888888888888880440880000888888888888
        8880088800008888888888888888888800008888888888888888888800008888
        88888888888888880000}
      ParentShowHint = False
      ShowHint = True
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sSpeedButton3: TsSpeedButton
      Tag = 3
      Left = 652
      Top = 9
      Width = 95
      Height = 22
      Hint = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100' '#1090#1077#1082#1091#1097#1080#1081' '#1079#1072#1082#1072#1079' '#1085#1072' '#1074#1099#1073#1088#1072#1085#1085#1099#1077' '#1076#1072#1090#1099
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777700000000
        00007777877777777770777787777777777077778F888888877000008F888888
        87708FFF8FFF777777708F008F88888887708FFF8FFFF77777708F008F888F70
        00008FFF8FFFFFF8F7078F008FFFFFF870778FFF8FFFFFF807778F0088888888
        77778FFFFFF8707777778FFFFFF8077777778888888877777777}
      OnClick = sSpeedButtonClick
      SkinData.SkinSection = 'SPEEDBUTTON'
    end
    object sCheckBox13: TsCheckBox
      Tag = 1
      Left = 120
      Top = 11
      Width = 52
      Height = 20
      Caption = #1055#1086#1085
      TabOrder = 0
      OnClick = sCheckBoxClick
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
    object sCheckBox14: TsCheckBox
      Tag = 2
      Left = 180
      Top = 11
      Width = 51
      Height = 20
      Caption = #1042#1090#1088
      TabOrder = 1
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
    object sCheckBox15: TsCheckBox
      Tag = 3
      Left = 240
      Top = 11
      Width = 53
      Height = 20
      Caption = #1057#1088#1076
      TabOrder = 2
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
    object sCheckBox16: TsCheckBox
      Tag = 4
      Left = 300
      Top = 11
      Width = 52
      Height = 20
      Caption = #1063#1090#1074
      TabOrder = 3
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
    object sCheckBox17: TsCheckBox
      Tag = 5
      Left = 360
      Top = 11
      Width = 52
      Height = 20
      Caption = #1055#1103#1090
      TabOrder = 4
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
    object sCheckBox18: TsCheckBox
      Tag = 6
      Left = 420
      Top = 11
      Width = 51
      Height = 20
      Caption = #1057#1091#1073
      TabOrder = 5
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
    object sCheckBox19: TsCheckBox
      Tag = 7
      Left = 480
      Top = 11
      Width = 50
      Height = 20
      Caption = #1042#1089#1082
      TabOrder = 6
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
    object sCheckBox20: TsCheckBox
      Left = 12
      Top = 33
      Width = 240
      Height = 20
      Caption = #1056#1072#1079#1088#1077#1096#1080#1090#1100' '#1082#1086#1087#1080#1088#1086#1074#1072#1085#1080#1077' '#1085#1072' '#1089#1077#1075#1086#1076#1085#1103
      TabOrder = 7
      OnClick = sCheckBoxShowClick
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
    object sCheckBox21: TsCheckBox
      Left = 268
      Top = 33
      Width = 295
      Height = 20
      Caption = #1056#1072#1079#1088#1077#1096#1080#1090#1100' '#1082#1086#1087#1080#1088#1086#1074#1072#1085#1080#1077' '#1085#1072' '#1087#1088#1077#1076#1099#1076#1091#1097#1080#1077' '#1076#1085#1080
      TabOrder = 8
      OnClick = sCheckBoxShowClick
      SkinData.SkinSection = 'CHECKBOX'
      ImgChecked = 0
      ImgUnchecked = 0
    end
  end
  object sPanel16: TsPanel
    Left = 0
    Top = 417
    Width = 762
    Height = 180
    Align = alTop
    Caption = 'sPanel16'
    TabOrder = 1
    SkinData.SkinSection = 'PANEL'
    object sPanel9: TsPanel
      Left = 1
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 0
      SkinData.SkinSection = 'PANEL'
      object DBGridEh9: TDBGridEh
        Tag = 9
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource9
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox9: TsCheckBox
        Tag = 9
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
    object sPanel10: TsPanel
      Left = 191
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 1
      SkinData.SkinSection = 'PANEL'
      object DBGridEh10: TDBGridEh
        Tag = 10
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource11
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox10: TsCheckBox
        Tag = 10
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
    object sPanel11: TsPanel
      Left = 381
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 2
      SkinData.SkinSection = 'PANEL'
      object DBGridEh11: TDBGridEh
        Tag = 11
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource11
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox11: TsCheckBox
        Tag = 11
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
    object sPanel12: TsPanel
      Left = 571
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 3
      SkinData.SkinSection = 'PANEL'
      object DBGridEh12: TDBGridEh
        Tag = 12
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource12
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox12: TsCheckBox
        Tag = 12
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
  end
  object sPanel14: TsPanel
    Left = 0
    Top = 57
    Width = 762
    Height = 180
    Align = alTop
    Caption = 'sPanel14'
    TabOrder = 2
    SkinData.SkinSection = 'PANEL'
    object sPanel1: TsPanel
      Left = 1
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 0
      SkinData.SkinSection = 'PANEL'
      object DBGridEh1: TDBGridEh
        Tag = 1
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource1
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox1: TsCheckBox
        Tag = 1
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
    object sPanel2: TsPanel
      Left = 191
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 1
      SkinData.SkinSection = 'PANEL'
      object DBGridEh2: TDBGridEh
        Tag = 2
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource2
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox2: TsCheckBox
        Tag = 2
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
    object sPanel3: TsPanel
      Left = 381
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 2
      SkinData.SkinSection = 'PANEL'
      object DBGridEh3: TDBGridEh
        Tag = 3
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource3
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox3: TsCheckBox
        Tag = 3
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
    object sPanel4: TsPanel
      Left = 571
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 3
      SkinData.SkinSection = 'PANEL'
      object DBGridEh4: TDBGridEh
        Tag = 4
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource4
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox4: TsCheckBox
        Tag = 4
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
  end
  object sPanel15: TsPanel
    Left = 0
    Top = 237
    Width = 762
    Height = 180
    Align = alTop
    Caption = 'sPanel15'
    TabOrder = 3
    SkinData.SkinSection = 'PANEL'
    object sPanel5: TsPanel
      Left = 1
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 0
      SkinData.SkinSection = 'PANEL'
      object DBGridEh5: TDBGridEh
        Tag = 5
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource5
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox5: TsCheckBox
        Tag = 5
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
    object sPanel6: TsPanel
      Left = 191
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 1
      SkinData.SkinSection = 'PANEL'
      object DBGridEh6: TDBGridEh
        Tag = 6
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource6
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox6: TsCheckBox
        Tag = 6
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
    object sPanel7: TsPanel
      Left = 381
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 2
      SkinData.SkinSection = 'PANEL'
      object DBGridEh7: TDBGridEh
        Tag = 7
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource7
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox7: TsCheckBox
        Tag = 7
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
    object sPanel8: TsPanel
      Left = 571
      Top = 1
      Width = 190
      Height = 178
      Align = alLeft
      Caption = 'sPanel1'
      TabOrder = 3
      SkinData.SkinSection = 'PANEL'
      object DBGridEh8: TDBGridEh
        Tag = 8
        Left = 1
        Top = 27
        Width = 188
        Height = 150
        Align = alBottom
        DataSource = DataSource8
        DynProps = <>
        HorzScrollBar.Visible = False
        IndicatorOptions = []
        Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghFixed3D, dghClearSelection, dghDialogFind, dghExtendVertLines]
        TabOrder = 0
        VertScrollBar.VisibleMode = sbNeverShowEh
        OnDblClick = DBGridEh1DblClick
        OnGetCellParams = DBGridEh1GetCellParams
        OnTitleBtnClick = DBGridEh1TitleBtnClick
        Columns = <
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD1'
            Footers = <>
            Title.Caption = #1055#1085
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD2'
            Footers = <>
            Title.Caption = #1042#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD3'
            Footers = <>
            Title.Caption = #1057#1088
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD4'
            Footers = <>
            Title.Caption = #1063#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD5'
            Footers = <>
            Title.Caption = #1055#1090
            Title.TitleButton = True
            Width = 25
          end
          item
            DisplayFormat = 'dd'
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD6'
            Footers = <>
            Title.Caption = #1057#1073
            Title.TitleButton = True
            Width = 25
          end
          item
            DynProps = <>
            EditButtons = <>
            FieldName = 'DD7'
            Footers = <>
            Title.Caption = #1042#1089
            Title.Font.Charset = DEFAULT_CHARSET
            Title.Font.Color = clRed
            Title.Font.Height = -11
            Title.Font.Name = 'Tahoma'
            Title.Font.Style = [fsBold]
            Title.TitleButton = True
            Width = 25
          end>
        object RowDetailData: TRowDetailPanelControlEh
        end
      end
      object sCheckBox8: TsCheckBox
        Tag = 8
        Left = 50
        Top = 4
        Width = 98
        Height = 20
        Caption = 'sCheckBox1'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = sCheckBoxClick
        SkinData.SkinSection = 'CHECKBOX'
        ImgChecked = 0
        ImgUnchecked = 0
      end
    end
  end
  object Query1: TQuery
    DatabaseName = 'TransDB'
    SQL.Strings = (
      'select * from sel_dates(null)')
    Left = 328
    Top = 280
  end
  object MemTableEh1: TMemTableEh
    Tag = 1
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 144
    Top = 144
  end
  object MemTableEh2: TMemTableEh
    Tag = 2
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 328
    Top = 144
  end
  object MemTableEh3: TMemTableEh
    Tag = 3
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 536
    Top = 144
  end
  object MemTableEh4: TMemTableEh
    Tag = 4
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 704
    Top = 136
  end
  object MemTableEh5: TMemTableEh
    Tag = 5
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 144
    Top = 320
  end
  object MemTableEh6: TMemTableEh
    Tag = 6
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 352
    Top = 320
  end
  object MemTableEh7: TMemTableEh
    Tag = 7
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 536
    Top = 328
  end
  object MemTableEh8: TMemTableEh
    Tag = 8
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 712
    Top = 320
  end
  object MemTableEh9: TMemTableEh
    Tag = 9
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 152
    Top = 496
  end
  object MemTableEh10: TMemTableEh
    Tag = 10
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 352
    Top = 496
  end
  object MemTableEh11: TMemTableEh
    Tag = 11
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 528
    Top = 496
  end
  object MemTableEh12: TMemTableEh
    Tag = 12
    Filtered = True
    Params = <>
    OnFilterRecord = MemTableEhFilterRecord
    Left = 704
    Top = 496
  end
  object DataSource1: TDataSource
    DataSet = MemTableEh1
    Left = 80
    Top = 144
  end
  object DataSource2: TDataSource
    DataSet = MemTableEh2
    Left = 256
    Top = 144
  end
  object DataSource3: TDataSource
    DataSet = MemTableEh3
    Left = 456
    Top = 144
  end
  object DataSource4: TDataSource
    DataSet = MemTableEh4
    Left = 648
    Top = 136
  end
  object DataSource5: TDataSource
    DataSet = MemTableEh5
    Left = 80
    Top = 320
  end
  object DataSource6: TDataSource
    DataSet = MemTableEh6
    Left = 288
    Top = 320
  end
  object DataSource7: TDataSource
    DataSet = MemTableEh7
    Left = 464
    Top = 328
  end
  object DataSource8: TDataSource
    DataSet = MemTableEh8
    Left = 656
    Top = 320
  end
  object DataSource9: TDataSource
    DataSet = MemTableEh9
    Left = 72
    Top = 496
  end
  object DataSource10: TDataSource
    DataSet = MemTableEh10
    Left = 288
    Top = 496
  end
  object DataSource11: TDataSource
    DataSet = MemTableEh11
    Left = 456
    Top = 496
  end
  object DataSource12: TDataSource
    DataSet = MemTableEh12
    Left = 656
    Top = 496
  end
  object Query2: TQuery
    DatabaseName = 'TransDB'
    Left = 400
    Top = 280
  end
  object Query3: TQuery
    DatabaseName = 'TransDB'
    Left = 448
    Top = 280
  end
end
