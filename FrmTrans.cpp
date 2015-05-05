//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DModT.h"
#include "ComProc.h"
#include "FrmPassWord.h"
#include "FrmSelSimpleEh.h"
#include "StructDef.h"

#include "FrmTrans.h"
#include "FrmFilter.h"
#include "FrmOrderCopy.h"
#include "FrmDriverGraph.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sPageControl"
#pragma link "sPanel"
#pragma link "sStatusBar"
#pragma link "DBAxisGridsEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "DBGridEhToolCtrls"
#pragma link "GridsEh"
#pragma link "sSplitter"
#pragma link "ToolCtrlsEh"
#pragma link "DataDriverEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "DBCtrlsEh"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGraphics"
#pragma link "cxInplaceContainer"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxOI"
#pragma link "cxStyles"
#pragma link "cxVGrid"
#pragma link "dxSkinsCore"
#pragma link "dxSkinsDefaultPainters"
#pragma link "sCustomComboEdit"
#pragma link "sMaskEdit"
#pragma link "sTooledit"
#pragma link "sComboBox"
#pragma link "sSpeedButton"
#pragma link "sCheckBox"
#pragma link "sGroupBox"
#pragma link "sLabel"
#pragma link "sComboEdit"
#pragma link "sRadioButton"
#pragma link "PrnDbgeh"
#pragma link "sEdit"
#pragma link "sButton"
#pragma resource "*.dfm"
namespace XXX {
TFormTrans *FormTrans;
}
using namespace XXX;
using Gridseh::TGridCoord;

#define EDIT_CONTACT_IS_ALLOWED 0x0001;		// прямое редактирование полей контакта
//---------------------------------------------------------------------------
__fastcall TFormTrans::TFormTrans(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::FormCreate(TObject *Sender)
{
//	SetFormPosStd(this,Screen->Width,750,0,true);
	SetFormPosStd(this,1280,750,0,true);
	Caption = Caption + " > " +DModT->Database1->AliasName + " < ";
	if (ChooseStartPage()) {
		InitGData();
		InitCommon();
		SelectPage();
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::ChooseStartPage()
{
	 int EmplRights = DModT->Empl_Rights;
	 int PageCount  = sPageControl1->PageCount;
	 int PageBits   = 3;
	 bool bFind = false;
	 for (int i = 0; i < PageCount; i++) {
		 TTabSheet* TabSheet  = sPageControl1->Pages[i];
		 TabSheet->TabVisible = EmplRights & PageBits;
		 if (TabSheet->TabVisible) {
			 if (i < 3 || !bFind)  {
				 sPageControl1->ActivePageIndex = i;
				 bFind = true;
			 }
		 }
		 PageBits <<= 2;
	 }
	 PageTag = sPageControl1->ActivePageIndex + 1;
	 return bFind;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::InitCommon()
{
	MaxFrozenCols         = DBGridEh31->FrozenCols;
	sComboBox1->ItemIndex = SelIndex = 1;
	sComboEdit1->Text     = "Не выбран";
	sComboEdit2->Text     = "Не выбран";
//	sDateEdit3->Color     = clRed;
	RestoreEditMulti      = false;
	SData.FieldKey        = GDataGraph.FieldKey;

	RDPWCtrl              = NULL;
//	FirstOpenDetail       = true;

	DT_Beg_Ord = Date();     sDateEdit1->Date = DT_Beg_Ord;
	DT_End_Ord = Date()+1;   sDateEdit2->Date = DT_End_Ord;

//	DT_Beg_Grp = Date() - 1; sDateEdit3->Date = DT_Beg_Grp; TM_Beg_Grp = DT_Beg_Grp - 1./12;
//	DT_End_Grp = Date() + 1; sDateEdit4->Date = DT_End_Grp; TM_End_Grp = DT_Beg_Grp + 1./12;
	DT_Graph = Date(); sDateEdit3->Date = DT_Graph; TM_Beg_Grp = Date() - 1 - 1./12;
																	TM_End_Grp = Date() + 1 + 1./12;
	SetGraphLabels();

	DBDateTimeEditEh1->Value = TM_Beg_Grp;
	DBDateTimeEditEh2->Value = TM_End_Grp;

	DT_Beg_Exp = Date()-7;   sDateEdit5->Date = DT_Beg_Exp;
	DT_End_Exp = Date()+7;   sDateEdit6->Date = DT_End_Exp;

	DefColWidth = GetCurColWidtList();
	EnumtateOrderColums(DBGridEh31);
	CreateGraphColumns();
	sCheckBox1->Checked = false;  // не показывать N и дату приема заказа
	CreateEditList();

}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SetGraphLabels()
{
	sLabelGraphBeg->Caption = "С " +  (DT_Graph - 1).FormatString("dd.mmm.yy");
	sLabelGraphEnd->Caption = "по " + (DT_Graph + 1).FormatString("dd.mmm.yy");
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::CreateGraphColumns()
{
	 TDBGridColumnsEh* Columns = DBGridEh41->Columns;
	 int Cnt = Columns->Count;
	 for (int i = 6; i < Cnt; i++) {
		 Columns->Delete(6);
	 }
	 Cnt = Columns->Count;
	 int Wdt = 0;
	 for (int i = 0; i < Cnt; i++) {
		 Wdt += Columns->Items[0]->Width + 1;
	 }
	 CalcMinutes();
	 if (Minuts_Rnd < 60) return;
	 int N_Hours = Minuts_Rnd / 60;
//	 TDateTime DT_B = TDateTime(GetDateStr(DT_Beg_Grp) + " " + TM_Beg_Grp.FormatString("hh") + ":00");
	 TDateTime DT_B = TDateTime(GetDateStr(DT_Graph - 1) + " " + TM_Beg_Grp.FormatString("hh") + ":00");

	 Wdt = (DBGridEh41->ClientWidth - Wdt)/ N_Hours + 2;
	 AnsiString Lev1, Lev2, Lev3;
	 TDateTime DT_Cur = DT_B;
	 for (int i = 0; i < N_Hours; i++) {
		 Columns->Insert(i+6);
		 Columns->Items[i+6]->Width = Wdt;
		 Lev1 = GetDateStr(DT_Cur);
		 int TypeT = StrToInt(DT_Cur.FormatString("h"))/6;
		 switch (TypeT) {
			 case 0: Lev2 = "Ночь";  break;
			 case 1: Lev2 = "Утро";  break;
			 case 2: Lev2 = "День";  break;
			 case 3: Lev2 = "Вечер"; break;
		 }
		 Lev3 = DT_Cur.FormatString("hh") + ":00";
		 Columns->Items[i+6]->Title->Caption = Lev1 + "|" + Lev2 + "|" + Lev3;
		 Columns->Items[i+6]->FieldName = "DUMMY";
		 DT_Cur = DT_B + (i+1)/24.;
	 }
	 NumerateGridFields(DBGridEh41);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::EnumtateOrderColums(TDBGridEh* Grid)
{
	 TDBGridColumnsEh* Columns = Grid->Columns;
	 int Cnt = Columns->Count;
	 for (int i = 0; i < Cnt; i++) {
		 Columns->Items[i]->Title->Caption = Columns->Items[i]->Title->Caption + "|" + IntToStr(i+1);
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::CreateEditList()
{
	TWinControl* WCtrlArr[] = { 	sComboEdit3, 			sEdit1,       			sComboEdit4, 			DBNumberEditEh1,
											sComboEdit5, 			sComboEdit6,  			sEdit2,
											sComboEdit7, 			sComboEdit8,  			sEdit3,           	ComboBox1,

											sComboEdit9, 			sComboEdit10, 			sEdit4,											// Транспорт
											sComboEdit11,        sEdit5,              DBNumberEditEh2,                       // Водитель

											DBDateTimeEditEh3, 	DBNumberEditEh3,		DBDateTimeEditEh4, 	sEdit6, 				// 1 строка расчета
											DBNumberEditEh4,     DBNumberEditEh5,		DBNumberEditEh6,     ComboBox2,
											DBNumberEditEh7,		DBNumberEditEh8,

											ComboBox3,           DBNumberEditEh9,     ComboBox4,         	ComboBox5,
											DBNumberEditEh10,    ComboBox6,           ComboBox7,


											DBNumberEditEh11,		DBDateTimeEditEh7,	DBNumberEditEh12,		DBDateTimeEditEh8,
											DBNumberEditEh13,	   DBNumberEditEh14,    sMemo2 };
	AllDetailCtrl = sizeof(WCtrlArr)/sizeof(TWinControl*);
	NumDetailCtrl = AllDetailCtrl;
	WCtrlVect.insert(WCtrlVect.begin(),WCtrlArr,WCtrlArr+AllDetailCtrl);

	AnsiString FNameArr[] = { 	"CONTACT_NAME",  			"CONTACT_PHONE",   	"TRANS_TYPE_NAME",	"PASS_NEED",
										"BEG_TOWN_NAME", 			"BEG_STREET_NAME", 	"BEG_ADDR_NAME",
										"END_TOWN_NAME", 			"END_STREET_NAME", 	"END_ADDR_NAME",     "RET_TO_START",

										"TRANS_COMPANY_NAME", 	"TRANSPORT_NAME",		"REG_NUMBER;PASS_NUMBER;TRANS_COMMENT|Рег.N;Мест;>",  // транспорт
										"DRIVER_NAME",          "DRIVER_PHONE",      "DRIVER_HAND_MONEY",												// Водитель

										"TIME_BEF",     			"WRK_DAY",           "TIME_WRK",				"TIME_SUM_STR_F",
										"HOUR_TAX", 				"DIST_RES",	 		   "DIST_TAX",				"FLAG_CALC_INCOME",
										"PAY_CALC",					"PAY_RES",

										"PAY_TYPE",          	"PAY_AVC",           "PAY_AVC_RECEIVER",	"PAY_AVC_STATE",
										"PAY_REST",          	"PAY_REST_RECEIVER", "PAY_REST_STATE",

										"EXC_PAY",              "EXC_PAY_DATE",      "MNG_PAY",	  			"MNG_PAY_DATE",
										"DRV_PAY",              "INCOME",            "COMMENT" };
	FNameVect.insert(FNameVect.begin(),FNameArr,FNameArr+NumDetailCtrl);
	DetailEditCng.insert (DetailEditCng.begin(), AllDetailCtrl,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::CalcMinutes()
{
//	 int DayMin = int(DT_End_Grp - DT_Beg_Grp)*1440;		// полные дни в графике в минутах
	 int DayMin = 2880;		// полные дни в графике в минутах
	 Minuts_All = DayMin +                                // весь график в минутах
					  StrToInt(TM_End_Grp.FormatString("h"))*60 + StrToInt(TM_End_Grp.FormatString("n")) -
					  StrToInt(TM_Beg_Grp.FormatString("h"))*60 - StrToInt(TM_Beg_Grp.FormatString("n"));
	 Minuts_Rnd = DayMin +                                // график с началом и концом расширенных до границ часов
					  StrToInt(TM_End_Grp.FormatString("h"))*60 + (StrToInt(TM_End_Grp.FormatString("n")) ? 60 : 0) -
					  StrToInt(TM_Beg_Grp.FormatString("h"))*60;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormTrans::GetCurColWidtList()
{
	TDBGridEh* Grid = DBGridEh31;
	TDBGridColumnsEh* Columns = Grid->Columns;
	int Cnt = Columns->Count;

	AnsiString S;
	for (int i = 0; i < Cnt; i++) {
		 if (Columns->Items[i]->Visible)
			S += "," + IntToStr(Columns->Items[i]->Width);
		 else
			S += ",";
	}
	return S.SubString(2,1000);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetTransCompanyID(TForm* Frm, int Left,int &ID,TParams*&)
{
	int TransTypeID = 0;
	return SimpleSelEhTransCompanyID(Frm,0,ID,TransTypeID,&SelectResultStr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetTransTypeID(TForm* Frm, int Left,int &ID,TParams*&)
{
	return SimpleSelEhTransTypeID(Frm,0,ID,&SelectResultStr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetEmployeeID(TForm* Frm, int Left,int &ID,TParams*&)
{
	return SimpleSelEhEmployeeID(Frm,0,ID);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormTrans::GetSelEditParams()
{
	return IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetTransportID(TForm* Frm, int Left,int &ID,TParams*&)
{
	AnsiString Params = GetSelEditParams();
	int TransTypeID = 0;
	int TransCompID = 0;
	switch(PageTag) {
		case 3: TransCompID = MemTableEh31->FieldByName("Trans_Company_ID")->AsInteger;  break;
		case 4: TransCompID = -1;

	}
	return SimpleSelEhTransportID(Frm,0,ID,TransTypeID, TransCompID, Params,&SelectResultStr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetClientID(TForm* Frm, int Left,int &ID,TParams*&)
{
	return SimpleSelEhClientID(Frm,0,ID);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetContactID(TForm* Frm, int Left,int &ID,TParams*&)
{
	int ClientID = MemTableEh31->FieldByName("Client_ID")->AsInteger;
	if (!ClientID) return false;
	AnsiString Params = GetSelEditParams();
	return SimpleSelEhContactID(Frm,0,ID,ClientID,Params,&SelectResultStr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetTownID(TForm* Frm, int Left,int &ID,TParams*&)
{
	AnsiString Params = GetSelEditParams();
	return SimpleSelEhTownID(Frm,0,ID,Params,&SelectResultStr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetWorkTypeID(TForm* Frm, int Left,int &ID,TParams*&)
{
	int ClientID = 0;
	switch (PageTag) {
		case 2:  ClientID = MemTableEh21->FieldByName("Client_ID")->AsInteger;
					break;
		default: ClientID = WrkGData->WrkDSet->FieldByName("Client_ID")->AsInteger;
					break;
	}
	if (!ClientID) return false;
	AnsiString Params = IntToStr(ClientID) + ","+GetSelEditParams();
	return SimpleSelEhWorkTypeID(Frm,0,ID,ClientID,Params,&SelectResultStr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetStreetID(TForm* Frm, int Left,int &ID,TParams*&)
{
	int TownID = GDataOrders.EditFldName.Pos("BEG") ? MemTableEh31->FieldByName("BEG_TOWN_ID")->AsInteger:
																	  MemTableEh31->FieldByName("END_TOWN_ID")->AsInteger;
	if (!TownID) return false;
	AnsiString Params = IntToStr(TownID) + "," + GetSelEditParams();
	return SimpleSelEhStreetID(Frm,0,ID,TownID,Params,&SelectResultStr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetDriverID(TForm* Frm, int Left,int &ID,TParams*&)
{
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	int TransCompID = 0;
	switch (PageTag) {
		case 1: TransCompID = MemTableEh13->FieldByName("TRANS_COMPANY_ID")->AsInteger; break;
		case 3: TransCompID = MemTableEh31->FieldByName("TRANS_COMPANY_ID")->AsInteger; break;
		case 4: TransCompID = WrkGData->WrkDSet->FieldByName("TRANS_COMPANY_ID")->AsInteger; break;
		case 5: TransCompID = -1; break;
	}
	if (!TransCompID) return false;
	return SimpleSelEhDriverID(Frm,0,ID,TransCompID,Params,&SelectResultStr);;
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetExpenseID(TForm* Frm, int Left,int &ID,TParams*&)
{
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	return SimpleSelEhExpenseID(Frm,0,ID,Params);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SetCommonExtParams(GridData& GData)
{
	GData.AddExtParam(ftInteger, "USER_ID",     DModT->CurEmpID);
	GData.AddExtParam(ftString,  "COMP_NAME",   DModT->ComputerName);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::InitGData()
{
	int Flags = STD_STATUSBAR    | CAN_SEE_DELETED    | INC_SEARCH | FILTER_BY_NAME |
					UPDATE_IN_MEMORY | DONT_CHECK_KEY_ID;
// ===== Список поставщиков услуг ==============================================
	GDataTransComp.Flags         = Flags | PULSE_AFTER_UPDATE;
	GDataTransComp.WrkSBar       = sStatusBar1;

	GDataTransComp.FieldKey      = "TRANS_COMPANY_ID";
//	GDataTransComp.DefFieldFlt   =
	GDataTransComp.FieldOut      = "TRANS_COMPANY_NAME";
	GDataTransComp.GetErrMsg     = GetErrMsg;
//	GDataTransComp.FunAcceptRec  = AcceptRecord;

	GDataTransComp.SrcDSet       = Query11;
	GDataTransComp.WrkGrid       = DBGridEh11;
	GDataTransComp.WrkDBase      = DModT->Database1;
	GDataTransComp.EditAllowMask =  0x000E;
	GDataTransComp.NullAllowMask =  0x000C;
	GDataTransComp.TextEdit      = DBEditEh;
	GDataTransComp.ListEdit      = ComboBox;

	GDataTransComp.WrkQuery      = Query14;
	GDataTransComp.FunSetSQLOne  = RefreshOneRow;

	GDataTransComp.FldTranslateMap.insert(pair<AnsiString,AnsiString>("Out_Flag","TRANS_COMPANY_FLAG"));
	SetCommonExtParams(GDataTransComp);
// ==== Список типов транспорта ================================================
	GDataTransType.Flags         = Flags;
	GDataTransType.WrkSBar       = sStatusBar1;

	GDataTransType.FieldKey      = "TRANS_TYPE_ID";
	GDataTransType.DefFieldFlt   = "TRANS_TYPE_NAME";
	GDataTransType.GetErrMsg     = GetErrMsg;
//	GDataTransType.FunAcceptRec  = AcceptRecord;

	GDataTransType.SrcDSet       = Query12;
	GDataTransType.WrkGrid       = DBGridEh12;
	GDataTransType.WrkDBase      = DModT->Database1;
	GDataTransType.EditAllowMask =  0x003E;
	GDataTransType.NullAllowMask =  0x003C;

	GDataTransType.TextEdit      = DBEditEh;
	GDataTransType.NumbEdit      = DBNumberEditEh;
	GDataTransType.DateEdit      = DBDateTimeEditEh;

	GDataTransType.WrkQuery      = Query15;
	GDataTransType.FunSetSQLOne  = RefreshOneRow;
	SetCommonExtParams(GDataTransType);
// ==== Транспортные средства ==================================================
	GDataTransport.Flags         = Flags;
	GDataTransport.WrkSBar       = sStatusBar1;

	GDataTransport.FieldKey      = "TRANSPORT_ID";
	GDataTransport.FieldOut      = "TRANSPORT_NAME";
	GDataTransport.GetErrMsg     = GetErrMsg;
//	GDataTransport.FunAcceptRec  = AcceptRecord;

	GDataTransport.SrcDSet       = Query13;
	GDataTransport.WrkGrid       = DBGridEh13;
	GDataTransport.WrkDBase      = DModT->Database1;
	GDataTransport.EditAllowMask =  0x007F;
	GDataTransport.NullAllowMask =  0x0078;
	GDataTransport.Select_IDMask =  0x0025;
	GDataTransport.FilterFldMask =  0x006F;
	GDataTransport.TextEdit      = DBEditEh;
	GDataTransport.NumbEdit      = DBNumberEditEh;
	GDataTransport.DateEdit      = DBDateTimeEditEh;
	GDataTransport.WrkQuery      = Query16;
	GDataTransport.FunSetSQLOne  = RefreshOneRow;

	GDataTransport.AddSelParam(ftInteger,"TRANS_COMPANY_ID",Null);

	GDataTransport.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANS_COMPANY_NAME","TRANS_COMPANY_ID"));
	GDataTransport.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANS_TYPE_NAME",   "TRANS_TYPE_ID"));
	GDataTransport.FldTranslateMap.insert(pair<AnsiString,AnsiString>("DRIVER_NAME",       "TRANS_DRIVER_ID"));

	GDataTransport.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANS_COMPANY_ID"),  GetTransCompanyID));
	GDataTransport.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANS_TYPE_ID"),     GetTransTypeID));
	GDataTransport.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANS_DRIVER_ID"),   GetDriverID));
	SetCommonExtParams(GDataTransport);
// =============================================================================
// ==== список клиентов ========================================================
	GDataClient.Flags         = Flags;
	GDataClient.WrkSBar       = sStatusBar1;

	GDataClient.FieldKey      = "CLIENT_ID";
	GDataClient.FieldOut      = "CLIENT_NAME";
	GDataClient.GetErrMsg     = GetErrMsg;
//	GDataClient.FunAcceptRec  = AcceptRecord;

	GDataClient.SrcDSet       = Query21;
	GDataClient.WrkGrid       = DBGridEh21;
	GDataClient.WrkDBase      = DModT->Database1;
	GDataClient.EditAllowMask =  0x007F;
	GDataClient.NullAllowMask =  0x005E;
	GDataClient.Select_IDMask =  0x0010;
	GDataClient.FilterFldMask =  -1;
	GDataClient.TextEdit      = DBEditEh;
	GDataClient.ListEdit      = ComboBox;
	GDataClient.NumbEdit      = DBNumberEditEh;

	GDataClient.WrkQuery      = Query24;
	GDataClient.FunSetSQLOne  = RefreshOneRow;
	GDataClient.FldTranslateMap.insert(pair<AnsiString,AnsiString>("CLIENT_TYPE_STR", "CLIENT_TYPE"));
	GDataClient.FldTranslateMap.insert(pair<AnsiString,AnsiString>("CLIENT_FLAG_STR", "CLIENT_FLAG"));
	GDataClient.FldTranslateMap.insert(pair<AnsiString,AnsiString>("WORK_TYPE_NAME",  "WORK_TYPE_ID"));

	GDataClient.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("WORK_TYPE_ID"),  GetWorkTypeID));

	SetCommonExtParams(GDataClient);
// ==== список контактов =======================================================
	GDataContact.Flags         =  Flags;
//	GDataContact.WrkSBar       = sStatusBar1;

	GDataContact.FieldKey      = "CONTACT_ID";
	GDataContact.FieldOut      = "CONTACT_NAME";
	GDataContact.GetErrMsg     = GetErrMsg;
//	GDataContact.FunAcceptRec  = AcceptRecord;

//	GDataContact.SrcDSet       = Query22;
	GDataContact.WrkGrid       = DBGridEh22;
	GDataContact.WrkDBase      = DModT->Database1;
	GDataContact.EditAllowMask =  0x03;
	GDataContact.NullAllowMask =  0x02;
	GDataContact.FilterFldMask =  -1;
	GDataContact.TextEdit      = DBEditEh;
	GDataContact.WrkQuery      = Query25;
	GDataContact.FunSetSQLOne  = RefreshOneRow;
	SetCommonExtParams(GDataContact);
// ==== Цены клиента ===========================================================
	GDataClientTax.Flags         = Flags ^ UPDATE_IN_MEMORY;
	GDataClientTax.WrkSBar       = sStatusBar1;

	GDataClientTax.FieldKey      = "CLIENT_TAX_ID";
	GDataClientTax.GetErrMsg     = GetErrMsg;

//	GDataClientTax.SrcDSet       = Query23;
	GDataClientTax.WrkGrid       = DBGridEh23;
	GDataClientTax.WrkDBase      = DModT->Database1;
	GDataClientTax.EditAllowMask =  0x00FF;
	GDataClientTax.NullAllowMask =  0x00FE;
	GDataClientTax.Select_IDMask =  0x0003;

	GDataClientTax.NumbEdit      = DBNumberEditEh;
	GDataClientTax.DateEdit      = DBDateTimeEditEh;
	GDataClientTax.ListEdit      = ComboBox;


	GDataClientTax.WrkQuery      = Query26;
	GDataClientTax.FunSetSQLOne  = RefreshOneRow;

	GDataClientTax.AddSelParam(ftInteger,"TRANS_TYPE_ID",Null);
//	GDataClientTax.AddSelParam(ftInteger,"WORK_TYPE_ID",Null);

	GDataClientTax.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANS_TYPE_ID"),   GetTransTypeID));
	GDataClientTax.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("WORK_TYPE_ID"),    GetWorkTypeID));
	GDataClientTax.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANS_TYPE_NAME",      "TRANS_TYPE_ID"));
	GDataClientTax.FldTranslateMap.insert(pair<AnsiString,AnsiString>("WORK_TYPE_NAME",       "WORK_TYPE_ID"));
	GDataClientTax.FldTranslateMap.insert(pair<AnsiString,AnsiString>("FLAG_CALC_INCOME_STR", "FLAG_CALC_INCOME"));

	SetCommonExtParams(GDataClientTax);
// =============================================================================
// ==== заказы =================================================================
	GDataOrders.Flags =  STD_STATUSBAR       | CAN_SEE_DELETED    | INC_SEARCH   | FILTER_BY_NAME      |
								UPDATE_IN_MEMORY    | DONT_CHECK_KEY_ID  | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL |
								UPDATE_ONLY_CURRENT | SAVE_SELECTION;
	GDataOrders.WrkSBar = sStatusBar1;

	GDataOrders.FieldKey      = "Orders_ID";
	GDataOrders.GetErrMsg     = GetErrMsg;

	GDataOrders.SetSQL        = GetSQL;
	GDataOrders.FunAddRow     = AddCurrentRow;
	GDataOrders.FunSetSQLOne  = RefreshOneRow;

	GDataOrders.SrcDSet       = Query31;
	GDataOrders.WrkGrid       = DBGridEh31;
	GDataOrders.WrkDBase      = DModT->Database1;
//																 7    11   15   19   23   27   31   35   39   43   47   51   55
//                                               8    12   16   20   24   28   32   36   40   44   48   52   56
//																 |    |    |    |    |    |    |    |    |    |    |    |    |
	SetBitMask(GDataOrders.EditAllowMask,"0011 1110 0111 1111 1111 1111 1110 1111 1100 1011 1110 1111 1110");
	SetBitMask(GDataOrders.NullAllowMask,"0011 1110 0111 1111 1111 1111 1110 1111 1100 0011 1110 1111 1100");

	GDataOrders.TextEdit      = DBEditEh;
	GDataOrders.NumbEdit      = DBNumberEditEh;
	GDataOrders.DateEdit      = DBDateTimeEditEh;
	GDataOrders.ListEdit      = ComboBox;
	GDataOrders.WrkQuery      = Query32;

	GDataOrders.AddSelParam(ftInteger,"TRANS_TYPE_ID",Null);

	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("FLAG_CALC_INCOME_STR", "FLAG_CALC_INCOME"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("RET_TO_START_STR",     "RET_TO_START"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("ORDER_STATE_STR",      "ORDER_STATE"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("PAY_TYPE_STR",         "PAY_TYPE"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("PAY_GET_STATE_STR",    "PAY_GET_STATE"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("ORDER_TYPE_STR",       "ORDER_TYPE"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("PAY_AVC_RECEIVER_STR", "PAY_AVC_RECEIVER"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("PAY_AVC_STATE_STR",    "PAY_AVC_STATE"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("PAY_REST_RECEIVER_STR","PAY_REST_RECEIVER"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("PAY_REST_STATE_STR",   "PAY_REST_STATE"));

	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANS_TYPE_NAME",      "TRANS_TYPE_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANS_COMPANY_NAME",   "TRANS_COMPANY_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANSPORT_NAME",       "TRANSPORT_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("REG_NUMBER",           "TRANSPORT_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("CLIENT_NAME",          "CLIENT_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("CONTACT_NAME",         "CONTACT_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("FULL_NAME",            "MANAGER_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("BEG_TOWN_NAME",        "BEG_TOWN_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("END_TOWN_NAME",        "END_TOWN_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("BEG_STREET_NAME",      "BEG_STREET_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("END_STREET_NAME",      "END_STREET_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("DRIVER_NAME",          "DRIVER_ID"));
	GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("WORK_TYPE_NAME",       "WORK_TYPE_ID"));

	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANS_TYPE_ID"),      GetTransTypeID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANSPORT_ID"),       GetTransportID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANS_COMPANY_ID"),   GetTransCompanyID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("CLIENT_ID"),          GetClientID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("CONTACT_ID"),         GetContactID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("MANAGER_ID"),         GetEmployeeID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("BEG_TOWN_ID"),        GetTownID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("END_TOWN_ID"),        GetTownID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("BEG_STREET_ID"),      GetStreetID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("END_STREET_ID"),      GetStreetID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("DRIVER_ID"),          GetDriverID));
	GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("WORK_TYPE_ID"),       GetWorkTypeID));
	SetCommonExtParams(GDataOrders);
// =============================================================================
// ==== график =================================================================
	GDataGraph.Flags        = STD_STATUSBAR  | DONT_CHECK_KEY_ID | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL | UPDATE_ONLY_CURRENT |
									  SAVE_SELECTION | UPDATE_IN_MEMORY;
	GDataGraph.WrkSBar      = sStatusBar1;

	GDataGraph.FieldKey     = "GRAPH_ID";
	GDataGraph.GetErrMsg    = GetErrMsg;
	GDataGraph.SetSQL       = GetSQL;
	GDataGraph.FunAddRow    = AddCurrentRow;

	GDataGraph.SrcDSet      = Query41;
	GDataGraph.WrkGrid      = DBGridEh41;
	GDataGraph.WrkDBase     = DModT->Database1;

	GDataGraph.TextEdit     = DBEditEh;
	GDataGraph.WrkQuery     = Query44;

	SetBitMask(GDataGraph.FilterFldMask,"111");

	SetCommonExtParams(GDataGraph);
// ==== Строка графика =========================================================
	GDataDetail.Flags         = STD_STATUSBAR  | DONT_CHECK_KEY_ID | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL;

	GDataDetail.FieldKey      = "ORDERS_ID";

	GDataDetail.GetErrMsg     = GetErrMsg;
	GDataDetail.EditAllowMask =  -1;
//	GDataDetail.NullAllowMask =  -1;
	GDataDetail.Select_IDMask =  -1;
	GDataDetail.SetSQL        = GetSQL;

	GDataDetail.SrcDSet       = Query43;
	GDataDetail.WrkGrid       = DBGridEh43;
	GDataDetail.WrkDBase      = DModT->Database1;

	GDataDetail.WrkQuery      = Query45;
	GDataDetail.FldTranslateMap.insert(pair<AnsiString,AnsiString>("DRIVER_NAME","DRIVER_ID"));
	GDataDetail.FldTranslateMap.insert(pair<AnsiString,AnsiString>("HINT_STR1",  "DRIVER_ID"));
	GDataDetail.FldTranslateMap.insert(pair<AnsiString,AnsiString>("HINT_STR2",  "DRIVER_ID"));
	GDataDetail.FldTranslateMap.insert(pair<AnsiString,AnsiString>("HINT_STR3",  "DRIVER_ID"));
	GDataDetail.FldTranslateMap.insert(pair<AnsiString,AnsiString>("HINT_STR4",  "DRIVER_ID"));
	GDataDetail.FldTranslateMap.insert(pair<AnsiString,AnsiString>("HINT_STR5",  "DRIVER_ID"));
	GDataDetail.FunGetIDMap.insert(pair<AnsiString,FunGetID>("DRIVER_ID",        GetDriverID));

//	SetBitMask(GDataDetail.FilterFldMask,"111");
	SetCommonExtParams(GDataDetail);

// =============================================================================
// ==== расходы ===============================================================
	GDataOutlay.Flags         =  Flags | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL | UPDATE_ONLY_CURRENT | SAVE_SELECTION;
	GDataOutlay.WrkSBar       = sStatusBar1;

	GDataOutlay.FieldKey      = "Outlay_ID";
	GDataOutlay.SetSQL        = GetSQL;
	GDataOutlay.GetErrMsg     = GetErrMsg;
	GDataOutlay.FunAddRow     = AddCurrentRow;
	GDataOutlay.FunSetSQLOne  = RefreshOneRow;
//	GDataOutlay.FunAcceptRec  = AcceptRecord;


	GDataOutlay.SrcDSet       = Query51;
	GDataOutlay.WrkGrid       = DBGridEh51;
	GDataOutlay.WrkDBase      = DModT->Database1;
//	GDataOutlay.EditAllowMask =  0x03F2;  //0x00FE;
//	GDataOutlay.NullAllowMask =  0x03F0;
	SetBitMask(GDataOutlay.EditAllowMask,"0001 1111 1111");
	SetBitMask(GDataOutlay.NullAllowMask,"0000 0011 1111");
	SetBitMask(GDataOutlay.Select_IDMask,"0000 1000 1111");
	GDataOutlay.FilterFldMask =  0x0F82;
	GDataOutlay.TextEdit      = DBEditEh;
	GDataOutlay.NumbEdit   	  = DBNumberEditEh;
	GDataOutlay.DateEdit      = DBDateTimeEditEh;
	GDataOutlay.ListEdit      = ComboBox;

	GDataOutlay.WrkQuery      = Query52;

	GDataOutlay.AddSelParam(ftInteger,"EXPENSE_ID",Null);

	GDataOutlay.FldTranslateMap.insert(pair<AnsiString,AnsiString>("DRIVER_NAME",           "DRIVER_ID"));
	GDataOutlay.FldTranslateMap.insert(pair<AnsiString,AnsiString>("OUTLAY_TYPE_STR",       "OUTLAY_TYPE"));
	GDataOutlay.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANS_TYPE_NAME",       "TRANSPORT_ID"));
	GDataOutlay.FldTranslateMap.insert(pair<AnsiString,AnsiString>("REG_NUMBER",            "TRANSPORT_ID"));
	GDataOutlay.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANSPORT_NAME",        "TRANSPORT_ID"));
	GDataOutlay.FldTranslateMap.insert(pair<AnsiString,AnsiString>("EXPENSE_NAME",          "EXPENSE_ID"));

	GDataOutlay.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("DRIVER_ID"),       GetDriverID));
	GDataOutlay.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANSPORT_ID"),    GetTransportID));
	GDataOutlay.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("EXPENSE_ID"),      GetExpenseID));

	SetCommonExtParams(GDataOutlay);
// =============================================================================
// ==== список городов =========================================================
	GDataTown.Flags 			= Flags;
	GDataTown.WrkSBar 		= sStatusBar1;


	GDataTown.FieldKey   	= "TOWN_ID";
	GDataTown.FieldOut   	= "TOWN_NAME";
	GDataTown.GetErrMsg  	= GetErrMsg;
//	GDataTown.FunAcceptRec 	= AcceptRecord;
	GDataTown.FunSetSQLOne  = RefreshOneRow;

	GDataTown.SrcDSet    	= Query61;
	GDataTown.WrkGrid    	= DBGridEh61;
	GDataTown.WrkDBase   	= DModT->Database1;
	GDataTown.EditAllowMask = 1;
	GDataTown.TextEdit   	= DBEditEh;

	GDataTown.WrkQuery   	= Query64;
	SetCommonExtParams(GDataTown);
// ==== список улиц ============================================================
	GDataStreet.Flags 		  = Flags;
	GDataStreet.WrkSBar 		  = sStatusBar1;

	GDataStreet.FieldKey   	  = "STREET_ID";
	GDataStreet.FieldOut   	  = "STREET_NAME";
	GDataStreet.GetErrMsg  	  = GetErrMsg;
//	GDataStreet.FunAcceptRec  = AcceptRecord;
	GDataStreet.FunSetSQLOne  = RefreshOneRow;

	GDataStreet.SrcDSet       = Query62;
	GDataStreet.WrkGrid       = DBGridEh62;
	GDataStreet.WrkDBase      = DModT->Database1;
	GDataStreet.EditAllowMask = 1;
	GDataStreet.TextEdit      = DBEditEh;

	GDataStreet.WrkQuery      = Query65;
	SetCommonExtParams(GDataStreet);
// ==== список водителей =======================================================
	GDataDriver.Flags         =  Flags;
	GDataDriver.WrkSBar       = sStatusBar1;

	GDataDriver.FieldKey      = "DRIVER_ID";
	GDataDriver.FieldOut      = "DRIVER_NAME";
	GDataDriver.GetErrMsg     = GetErrMsg;
//	GDataDriver.FunAcceptRec  = AcceptRecord;
	GDataDriver.FunSetSQLOne  = RefreshOneRow;

	GDataDriver.SrcDSet       = Query63;
	GDataDriver.WrkGrid       = DBGridEh63;
	GDataDriver.WrkDBase      = DModT->Database1;
	GDataDriver.EditAllowMask =  7;
	GDataDriver.NullAllowMask =  4;
	GDataDriver.Select_IDMask =  1;
	GDataDriver.TextEdit      = DBEditEh;

	GDataDriver.WrkQuery      = Query66;

	GDataDriver.AddSelParam(ftInteger,"TRANS_COMPANY_ID",Null);

	GDataDriver.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANS_COMPANY_NAME","TRANS_COMPANY_ID"));
	GDataDriver.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANS_COMPANY_ID"),  GetTransCompanyID));
	SetCommonExtParams(GDataDriver);
// =============================================================================
// ==== список сотрудников =====================================================
	GDataEmployee.Flags         =  Flags | PULSE_AFTER_UPDATE;
	GDataEmployee.WrkSBar       = sStatusBar1;

	GDataEmployee.FieldKey      = "EMPLOYEE_ID";
	GDataEmployee.FieldOut      = "FULL_NAME";
	GDataEmployee.GetErrMsg     = GetErrMsg;
//	GDataEmployee.FunAcceptRec  = AcceptRecord;
	GDataEmployee.FunSetSQLOne  = RefreshOneRow;

	GDataEmployee.SrcDSet       = Query71;
	GDataEmployee.WrkGrid       = DBGridEh71;
	GDataEmployee.WrkDBase      = DModT->Database1;
	GDataEmployee.EditAllowMask =  0x0007;
	GDataEmployee.NullAllowMask =  0x0006;
	GDataEmployee.TextEdit      = DBEditEh;

	GDataEmployee.WrkQuery      = Query72;

	for (int i = 1; i < 15; i++) {
		AnsiString S = IntToStr(i);
		if (i < 10) S = "0" + S;
		S = "OUT_R" + S;
		GDataEmployee.FldTranslateMap.insert(pair<AnsiString,AnsiString>(S, "EMPL_RIGHTS"));
	}

	SetCommonExtParams(GDataEmployee);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::FormClose(TObject *Sender, TCloseAction &Action)
{
	WriteMemo();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Shift.Contains(ssAlt) || Shift.Contains(ssCtrl)) {
		TsTabSheet* NewSheet = NULL;
		switch (Key) {
			case '1': NewSheet = sTabSheet1; break;
			case '2': NewSheet = sTabSheet2; break;
			case '3': NewSheet = sTabSheet3; break;
			case '4': NewSheet = sTabSheet4; break;
			case '5': NewSheet = sTabSheet5; break;
			case '6': NewSheet = sTabSheet6; break;
			case '7': NewSheet = sTabSheet6; break;
		}
		if (NewSheet && NewSheet != sPageControl1->ActivePage) {
			WriteMemo();
			sPageControl1->ActivePage = NewSheet;
			SelectPage();
		}
	}
	switch (Key) {
		case VK_F3:  WriteMemo();
						 if (PageTag == 3) {
							 ProcFilter();
							 return;
						 }
						 break;
		case VK_F4:  GoToCurrentOrder();
						 break;
		case VK_F5:  WriteMemo();
						 ProcRefreshPage();
						 break;
		case VK_F11: ProcHistory(Shift.Contains(ssCtrl)); break;
	}
	FormKeyDownStd(*WrkGData,Key,Shift);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormTrans::TranslateName(AnsiString FldName)
{
	if (WrkGData->FldTranslateMap.size()) {
		std::map<AnsiString,AnsiString>::iterator iter = WrkGData->FldTranslateMap.find(FldName);
		if (iter != WrkGData->FldTranslateMap.end()) {
			 FldName = iter->second;
		}
	}
	return FldName;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ProcHistory(bool All)
{
	AnsiString Title  = "Просмотр истории изменения";
	AnsiString FldKey = WrkGData->FieldKey;
	AnsiString TableName = GetPiece(FldKey,"_ID",1).UpperCase();
	int ID = WrkGData->WrkDSet->FieldByName(FldKey)->AsInteger;
	AnsiString FieldNames;
	AnsiString TitleNames;
	AnsiString SS;
	TDBGridEh* Grid = WrkGData->WrkGrid;
	TStringList* FieldNamesList = new TStringList();
	TStringList* TitleNamesList = new TStringList();
	AnsiString AllFieldNames;
	if (All) {
		TDBGridColumnsEh* Columns = Grid->Columns;
		int Cnt = Columns->Count;
		if (Grid->Tag == 31) {
			FieldNames = ",CLIENT_TAX_ID,DOG_TAX";
			TitleNames = ",ID Таблицы тарифов,Сумма по договору";
		}
		AnsiString S;
		bool KeyIncduded = true;
		for (int i = 0; i < Cnt; i++) {
			 TColumnEh* Column = Columns->Items[i];
			 if (Column->Visible) {
				 AnsiString X = ","+TranslateName(Column->FieldName);
				 if (!AllFieldNames.Pos(X)) {
					 AllFieldNames += X;
					 FieldNames += X ;
					 SS = Column->Title->Caption;
					 TitleNames += "," + GetPiece(SS, "|",1);
					 SS = GetPiece(SS, "|",2);
					 if (SS != "")  TitleNames += "-> " + SS;
					 if (FieldNames.Length() > 230 || TitleNames.Length() > 200) {
						 KeyIncduded = KeyIncduded || FieldNames.Pos("," + FldKey);
						 FieldNames  = FieldNames.SubString(2,1000);
						 TitleNames  = TitleNames.SubString(2,1000);
						 FieldNames  = FieldNames.UpperCase();
						 FieldNamesList->Add(FieldNames);
						 TitleNamesList->Add(TitleNames);
						 FieldNames = "";
						 TitleNames = "";
					 }
				 }
			 }
		}
		if (!KeyIncduded) {
			FieldNames = "," +FldKey + FieldNames  + ",STATUS";
			TitleNames = ",N записи"  + TitleNames + ",Состояние";
		}
		else {
			FieldNames = FieldNames + ",STATUS";
			TitleNames = TitleNames + ",Состояние";
		}
		FieldNames  = FieldNames.SubString(2,1000);
		TitleNames  = TitleNames.SubString(2,1000);
		FieldNames = FieldNames.UpperCase();
		FieldNamesList->Add(FieldNames);
		TitleNamesList->Add(TitleNames);
		FieldNames = "";
		TitleNames = "";

		Title = Title + " всех видимых полей";
	}
	else {
		TColumnEh* Column = Grid->Columns->Items[Grid->Col - 1];
		FieldNames = TranslateName(Column->FieldName);
		SS = Column->Title->Caption;
		TitleNames =  GetPiece(SS, "|",1);
		SS = GetPiece(SS, "|",2);
		if (SS != "")  TitleNames += "-> " + SS;
		Title = Title + " поля > "+ TitleNames + " <";
		FieldNames = FieldNames.UpperCase();
		FieldNamesList->Add(FieldNames);
		TitleNamesList->Add(TitleNames);
	}
//	FieldNames = FieldNames.UpperCase();
//	if (SimpleSelHistoryID(this, 0,Title,TableName,ID,FieldNames,TitleNames)) {
	RestValue RestData;
	if (SimpleSelHistoryID(this, 0,Title,TableName,ID,FieldNamesList,TitleNamesList,RestData)) {
		RestoreValue(RestData,!All);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::RestoreValue(RestValue& RestData, bool CurrentCol)
{
	TDBGridEh* Grid = WrkGData->WrkGrid;
	TDBGridColumnsEh* Columns = Grid->Columns;

	int Col = (CurrentCol) ? Grid->Col : FindRestColumn(Columns,RestData);
	if (!Col) return;
	Grid->Col = Col;
	int Action = GetCurColumnEditAction(*WrkGData);
	if (!Action) return;
	TWinControl* WinCtrl = NULL;
	if (Action > 0) {
		WinCtrl = GetEditWinControl(*WrkGData,Action);
		if (!WinCtrl) return;
	}
	switch (Action) {
		case -1: WrkGData->AddCurParam(ftInteger,WrkGData->EditFldName,RestData.NewValue);
					break;
		case  1: WrkGData->TextEdit->Text      = RestData.New_Str_Value;
					break;
		case  2:	WrkGData->ListEdit->ItemIndex = RestData.New_ID_Value;
					break;
		case  3:	WrkGData->NumbEdit->Value     = RestData.New_ID_Value;
	}
}
//---------------------------------------------------------------------------
int __fastcall TFormTrans::FindRestColumn(TDBGridColumnsEh* Columns,RestValue& RestData)
{
	int Cnt = Columns->Count;
	AnsiString FName = RestData.FieldName;
	for (int i = 0; i < Cnt; i++) {
		if (Columns->Items[i]->FieldName == FName) {
			if (!Columns->Items[i]->Visible) {
				Columns->Items[i]->Visible = true;
				ClearSelView();
			}
			return i+1;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearSums()
{
	switch (PageTag) {
		case 3: SumPayCalc = SumPayRes = SumPayAvc = SumPayRest = SumPayExc = SumPayMng = SumPayDrv = SumIncCalc = 0;
				  ShowSummary(DBGridEh31);
				  break;
		case 4: DrawMap.clear();
				  break;
		case 5: SumOutlay  = 0;
				  ShowSummary(DBGridEh51);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sPageControl1Change(TObject *Sender)
{
	ChangePage();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ChangePage()
{
	RestoreEditMultiFlag();
	SelectPage();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SelectPage()
{
	PageTag = sPageControl1->ActivePage->Tag;
	EnablePageCtrl();
	OpenPage();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::OpenPage()
{
	 SetWrkGData();
	 switch (PageTag) {
		 case 1: OpenDSetStd(GDataTransComp);
					OpenDSetStd(GDataTransType);
					OpenDSetStd(GDataTransport);
					break;
		 case 2: OpenDSetStd(GDataClient);
					OpenDSetStd(GDataContact);
					OpenDSetStd(GDataClientTax);
					break;
		 case 3: if (!MemTableEh31->Active)
						ProcRefreshStd(GDataOrders,true);
					ShowSummary(DBGridEh31);
					break;
		 case 4: ProcRefreshStd(GDataGraph,true);
					break;
		 case 5: if (!MemTableEh51->Active)
						ProcRefreshStd(GDataOutlay,true);
					break;
		 case 6: OpenDSetStd(GDataTown);
					OpenDSetStd(GDataStreet);
					OpenDSetStd(GDataDriver);
					break;
		 case 7: OpenDSetStd(GDataEmployee);
					break;
	 }
	 OpenDSetStd(*WrkGData);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SetWrkGData()
{
	 WrkGData = DefGData = NULL;
	 switch (PageTag) {
		 case 1: WrkGData = DefGData = &GDataTransComp;
					if (DBGridEh12->Focused()) WrkGData = &GDataTransType;
					if (DBGridEh13->Focused()) WrkGData = &GDataTransport;
					break;
		 case 2: WrkGData = DefGData = &GDataClient;
					if (DBGridEh22->Focused()) WrkGData = &GDataContact;
					break;
		 case 3: WrkGData = DefGData = &GDataOrders;
					break;
		 case 4: WrkGData = DefGData = &GDataGraph;
					if (DBGridEh43->Focused())  WrkGData = &GDataDetail;
					break;
		 case 5: WrkGData = DefGData = &GDataOutlay;
					break;
		 case 6: WrkGData = DefGData = &GDataTown;
					if (DBGridEh62->Focused()) WrkGData = &GDataStreet;
					if (DBGridEh63->Focused()) WrkGData = &GDataDriver;
					break;
		 case 7: WrkGData = DefGData = &GDataEmployee;
					break;
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::EnablePageCtrl()
{
	bool En = (PageTag == 3);
	sSpeedButton2->Enabled  = (PageTag != 4);  		// удалить
	sSpeedButton3->Enabled  = (PageTag != 4);  		// вставить
	sSpeedButton4->Enabled  = En || (PageTag == 5); // выбор
	sSpeedButton5->Enabled  = En || (PageTag == 5); // отмена
	sSpeedButton7->Enabled  = (PageTag != 4);   		// история
	sSpeedButton8->Enabled  = (PageTag != 4);   		// фильтр
	sSpeedButton9->Enabled  = En;  						// сохранить фильт
//	sSpeedButton10->Enabled = En;  //
	sSpeedButton11->Enabled = En;  //
	sSpeedButton12->Enabled = En;  //
	sSpeedButton13->Enabled = En;  //
	sSpeedButton14->Enabled = En;  //
	sSpeedButton15->Enabled = En;  //
	sSpeedButton16->Enabled  = (PageTag != 4);  // поиск
//	sSpeedButton17->Enabled = En;  //
	sMemo1->Enabled        = En;
	sMemo1->Visible        = En;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sPageControl1Changing(TObject *Sender, bool &AllowChange)
{
	 switch (PageTag) {
		 case 2: WriteMemo();
					break;
		 case 3: if (DBGridEh31->RowDetailPanel->Visible)
						DBGridEh31->RowDetailPanel->Visible = false;
					WriteMemo();
					break;
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sPageControl1Exit(TObject *Sender)
{
	RestoreEditMultiFlag();
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetSQL(TDataSet* DSet)
{
	AnsiString SQL;
	switch (DSet->Tag) {
		case 31: SQL = (SelIndex != 2) ? "select * from Sel_orders("         + IntToStr(sComboBox1->ItemIndex) :
													"select * from Sel_orders_Changed(" + IntToStr(sComboBox1->ItemIndex);
					SQL += ",'" + GetDateStr(DT_Beg_Ord) + "','" + GetDateStr(DT_End_Ord) + "',NULL)";
					Query31->SQL->Text = SQL;
					break;
		case 41: SQL  = "select * from Sel_Graph_Order(null,'" +
							 GetDateStr(DT_Graph - 1) + " " +  TM_Beg_Grp.FormatString("hh:nn") + "','" +
							 GetDateStr(DT_Graph + 1) + " "  + TM_End_Grp.FormatString("hh:nn") + "')";
					Query41->SQL->Text = SQL;
					CalcMinutes();
					break;
		case 43: SQL  = "select * from Sel_Graph_Order(" + IntToStr(MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger) + ",'" +
							 GetDateStr(DT_Graph - 1) + " " +  TM_Beg_Grp.FormatString("hh:nn") + "','" +
							 GetDateStr(DT_Graph + 1) + " "  + TM_End_Grp.FormatString("hh:nn") + "') order by Sort_Order";
					Query43->SQL->Text = SQL;
					break;
		case 51: SQL = "select * from Sel_Outlay(0,'" +
							GetDateStr(DT_Beg_Exp) + "','" + GetDateStr(DT_End_Exp) + "',NULL)";
					Query51->SQL->Text = SQL;
					break;
	}
	return true;
}
//---------------------------------------------------------------------------
GridData& __fastcall TFormTrans::GetGDataRef(TObject* Sender)
{
	GridData* Ref = WrkGData;
	switch (GetComponentTag(Sender)) {
		case 11: Ref = &GDataTransComp; 	break;
		case 12: Ref = &GDataTransType; 	break;
		case 13: Ref = &GDataTransport; 	break;
		case 21: Ref = &GDataClient;    	break;
		case 22: Ref = &GDataContact;   	break;
		case 23: Ref = &GDataClientTax; 	break;
		case 31: Ref = &GDataOrders;    	break;
		case 41: Ref = &GDataGraph;    	break;
		case 43: Ref = &GDataDetail;    	break;
		case 51: Ref = &GDataOutlay;  	break;
		case 61: Ref = &GDataTown; 	  	break;
		case 62: Ref = &GDataStreet; 		break;
		case 63: Ref = &GDataDriver; 		break;
		case 71: Ref = &GDataEmployee;  	break;
	}
	return *Ref;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetRefreshTail(GridData& GData)
{
	return " where " + GData.FieldKey + " = " + GData.WrkQuery->FieldByName("RESULT")->AsString;
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::RefreshOneRow(GridData& GData,TDataSet* DSet)
{
	bool bRes = true;
	AnsiString SQL;
	int IVal;
	int Result;
	switch (GData.WrkDSet->Tag) {
		case 11: SQL = "select * from Trans_Company"  + GetRefreshTail(GData);
					break;
		case 12:	SQL = "select * from Trans_Type"     + GetRefreshTail(GData);
					break;
		case 13: SQL = "select * from Sel_Transport(" + GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
		case 21: SQL = "select * from Sel_Client("+ GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
		case 22: SQL = "select * from Contact"        + GetRefreshTail(GData);
					break;
		case 23: SQL = "select * from Sel_Client_Tax(" + MemTableEh21->FieldByName("CLIENT_ID")->AsString + "," +
																		 GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
		case 31: SQL = "select * from Sel_Orders(99,NULL,NULL," + GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
		case 41: //SQL = "select * from Sel_Graph(" + GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
		case 51: SQL = "select * from Sel_Outlay(1,NULL,NULL," + GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
		case 61: SQL = "select * from Town" 			 + GetRefreshTail(GData);
					break;
		case 62: SQL = "select * from Street"     	 + GetRefreshTail(GData);
					break;
		case 63: SQL = "select * from Sel_Driver("    + GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
		case 71: SQL = "select * from Sel_Employee(" + GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
	}
	TQuery* Qry = dynamic_cast<TQuery*>(DSet);
	Qry->SQL->Text = SQL;
	return bRes;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormTrans::GetErrMsg(GridData& GData,int Error)
{
	 return GetErrMsgBody(GData.WrkQuery->Tag,Error);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormTrans::GetErrMsgBody(int Tag,int Error)
{
	AnsiString S;
//	if (Error == -1) {
//		S = "Данные изменены другим пользователем";
//	}
//	else if (Error == -2) {
//		S = "Данные удалены другим пользователем";
//	}
	switch (Tag) {
		case 43: if (Error == -3) {
						S = "Нельзя заменить водителя - водитель"
							 "выходной во время выполнения заказа";
					}
					break;
		case 66: if (Error == -3)  {
						S = "Нельзя изменить транспортную компанию\n"
							 "водитель привязан к машинам транспортной\n"
							 "компании ''"+ WrkGData->WrkDSet->FieldByName("TRANS_COMPANY_NAME")->AsString+ "''";

					}
					break;
	}
//	if (S == "") {
//		S = "Ошибка " + IntToStr(Error) + ", источник ошибки N " + IntToStr(Tag);
//	}
	return S;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::MemTableEhAfterClose(TDataSet *DataSet)
{
	AfterCloseStd(GetGDataRef(DataSet));
	switch (DataSet->Tag) {
		case 31: sMemo1->Text  = "";
					CurOrderID    = 0;
					break;
		case 41:	for (std::map<int, Vect >::iterator iter = TransWork.begin(); iter != TransWork.end(); iter++) {
						(*iter).second.clear();
					}
					CurGraphID = 0;
					TransWork.clear();
					GraphHint.clear();
					break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::MemTableEhAfterOpen(TDataSet *DataSet)
{
	RestorePosStd(GetGDataRef(DataSet),false);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SetEditBitMask(TDataSet *DataSet)
{
	int Flag;
	switch (DataSet->Tag) {
		case 23: switch (DataSet->FieldByName("FLAG_CALC_INCOME")->AsInteger) {
						case 0: 	GDataClientTax.EditAllowMask =  0x0006;  break;
						case 1:
						case 2:  GDataClientTax.EditAllowMask =  0x007F;  break;
						case 3:  GDataClientTax.EditAllowMask =  0x0087;  break;
					}
					break;
		case 31: Flag = MemTableEh31->FieldByName("ORDER_FLAG")->AsInteger & EDIT_CONTACT_IS_ALLOWED;
					if (Flag) {
//																				    7    11   15   19   23   27   31   35   39   43   47   51
//                   	         			                      8    12   16   20   24   28   32   36   40   44   48   52
//																				    |    |    |    |    |    |    |    |    |    |    |    |
						SetBitMask(GDataOrders.Select_IDMask,"0000 0000 0001 1001 0110 1100 1110 1000 0000 0000 0000 0000 0000");
						std::map<AnsiString,AnsiString>::iterator iter1 = GDataOrders.FldTranslateMap.find("CONTACT_NAME");
						if (iter1 != GDataOrders.FldTranslateMap.end()) {
							GDataOrders.FldTranslateMap.erase(iter1);
						}
						std::map<AnsiString,FunGetID>::iterator iter2 = GDataOrders.FunGetIDMap.find("CONTACT_ID");
						if (iter2 != GDataOrders.FunGetIDMap.end()) {
							GDataOrders.FunGetIDMap.erase(iter2);
						}
					}
					else {
//																				    7    11   15   19   23   27   31   35   39   43   47   51
//                               				                   8    12   16   20   24   28   32   36   40   44   48   52
//																				    |    |    |    |    |    |    |    |    |    |    |    |
						SetBitMask(GDataOrders.Select_IDMask,"0000 0000 0001 1101 0110 1100 1110 1000 0000 0000 0000 0000 0000");

						std::map<AnsiString,AnsiString>::iterator iter1 = GDataOrders.FldTranslateMap.find("CONTACT_NAME");
						if (iter1 == GDataOrders.FldTranslateMap.end()) {
							GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("CONTACT_NAME",  	  "CONTACT_ID"));
						}
						std::map<AnsiString,FunGetID>::iterator iter2 = GDataOrders.FunGetIDMap.find("CONTACT_ID");
						if (iter2 == GDataOrders.FunGetIDMap.end()) {
							GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("CONTACT_ID"), GetContactID));
						}

					}
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SetAfterScroll(TDataSet *DataSet)
{
	switch (DataSet->Tag) {
		case 21: ShowMemoStd(GDataClient, sMemo3);
		case 23: SetEditBitMask(DataSet);
					break;
		case 31:	SetEditBitMask(DataSet);// SetOrdersBitMask();
					ShowMemoStd(GDataOrders, sMemo1);
					CurOrderID    = DataSet->FieldByName("ORDERS_ID")->AsInteger;
					DBGridEh31->Repaint();
					break;
		case 41: PrvGraphID    = CurGraphID;
					CurGraphID    = DataSet->FieldByName("GRAPH_ID")->AsInteger;
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::MemTableEhAfterScroll(TDataSet *DataSet)
{
	AfterScrollStd(GetGDataRef(DataSet));
	switch (DataSet->Tag) {
		case 11:	CurTransCompID = DataSet->FieldByName("Trans_Company_ID")->AsInteger;
					DBGridEh11->Repaint();
					break;
		case 12: CurTransTypeID = DataSet->FieldByName("Trans_Type_ID")->AsInteger;
					DBGridEh12->Repaint();
					break;
		case 13: CurTransportID = DataSet->FieldByName("Transport_ID")->AsInteger;
					DBGridEh13->Repaint();
					break;
		case 21: CurClientID = DataSet->FieldByName("Client_ID")->AsInteger;
		case 23:
		case 31:	SetAfterScroll(DataSet);
					break;
		case 41: SData.Fill(DataSet);
					SetAfterScroll(DataSet);
					CurDriverID = DataSet->FieldByName("TRANS_DRIVER_ID")->AsInteger;
					DBGridEh41->Repaint();
					break;
	}
}
//---------------------------------------------------------------------------
/*
void __fastcall TFormTrans::SetOrdersBitMask()
{
	int Flag = MemTableEh31->FieldByName("ORDER_FLAG")->AsInteger & EDIT_CONTACT_IS_ALLOWED;
	if (Flag) {
//																    7    11   15   19   23   27   31   35   39   43   47   51
//                                                  8    12   16   20   24   28   32   36   40   44   48   52
//																    |    |    |    |    |    |    |    |    |    |    |    |
		SetBitMask(GDataOrders.Select_IDMask,"0000 0000 0001 1001 0110 1100 1110 0000 1000 0000 0000 0000 0000 0001");
		std::map<AnsiString,AnsiString>::iterator iter1 = GDataOrders.FldTranslateMap.find("CONTACT_NAME");
		if (iter1 != GDataOrders.FldTranslateMap.end()) {
			GDataOrders.FldTranslateMap.erase(iter1);
		}
		std::map<AnsiString,FunGetID>::iterator iter2 = GDataOrders.FunGetIDMap.find("CONTACT_ID");
		if (iter2 != GDataOrders.FunGetIDMap.end()) {
			GDataOrders.FunGetIDMap.erase(iter2);
		}
	}
	else {
//																    7    11   15   19   23   27   31   35   39   43   47   51
//                                                  8    12   16   20   24   28   32   36   40   44   48   52
//																    |    |    |    |    |    |    |    |    |    |    |    |
		SetBitMask(GDataOrders.Select_IDMask,"0000 0000 0001 1101 0110 1100 1110 0000 1000 0000 0000 0000 0000 0001");

		std::map<AnsiString,AnsiString>::iterator iter1 = GDataOrders.FldTranslateMap.find("CONTACT_NAME");
		if (iter1 == GDataOrders.FldTranslateMap.end()) {
			GDataOrders.FldTranslateMap.insert(pair<AnsiString,AnsiString>("CONTACT_NAME",  	  "CONTACT_ID"));
		}
		std::map<AnsiString,FunGetID>::iterator iter2 = GDataOrders.FunGetIDMap.find("CONTACT_ID");
		if (iter2 == GDataOrders.FunGetIDMap.end()) {
			GDataOrders.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("CONTACT_ID"), GetContactID));
		}

	}
}
*/
//---------------------------------------------------------------------------
void __fastcall TFormTrans::MemTableEhBeforeScroll(TDataSet *DataSet)
{
	BeforeScrollStd(GetGDataRef(DataSet));
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::MemTableEhCalcFields(TDataSet *DataSet)
{
	switch(DataSet->Tag) {
		case 11: if (DataSet->FieldByName("TRANS_COMPANY_FLAG")->AsInteger) {
						 DataSet->FieldByName("OUT_FLAG")->AsString = "Да";
					}
					break;
		case 71: if (int IVal = DataSet->FieldByName("EMPL_RIGHTS")->AsInteger) {
						int Mask = 1;
						for (int i = 0; i < 14; i++,Mask <<=1 ) {
							if (IVal & Mask) {
								AnsiString Tail = IntToStr(i+1);
								if (Tail.Length() == 1) Tail = "0"+Tail;
								DataSet->FieldByName("OUT_R"+Tail)->AsString = "Да";
							}
						}
					}
					break;
	}
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetHintStr(TDataSet *DataSet)
{
	AnsiString S,Res,FName ;
	for (int i = 1; i < 6; i++) {
		FName = "Hint_Str" + IntToStr(i);
		S = DataSet->FieldByName(FName)->AsString;
		if (S != "") {
			if (Res != "") Res += "\n";
			Res += S;
		}
	}
	return Res;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::MemTableEhFilterRecord(TDataSet *DataSet, bool &Accept)
{
	switch (DataSet->Tag) {
		case 31: Accept = FilterRecordStd(GetGDataRef(DataSet));
					if (Accept && OrderFilter.size()) {
						Accept = CheckOrderFilter();
					}
					break;
		case 41: if (DataSet->FieldByName("FLAG_KIND")->AsInteger) {            // заказы
						Accept = FillHintStructures(DataSet);
					}
					else {
						if (DataSet->FieldByName("TRANS_COMPANY_FLAG")->AsInteger) { // сторонняя компания
							int ID = DataSet->FieldByName("Orders_ID")->AsInteger;
							if (ID) {
								Accept = true;
							}
							else {
								int ID = DataSet->FieldByName("Transport_ID")->AsInteger;
								std::vector<int>::iterator it = find(ShowTransVect.begin(),ShowTransVect.end(),ID);
								Accept = (it != ShowTransVect.end());
							}
						}
						else {                                                      // своя компания
							Accept = FilterRecordStd(GetGDataRef(DataSet));
						}
						if (Accept) {
							Accept = FillHintStructures(DataSet);                    // в обоих случаях заполняем
						}
						if (!sCheckBox41->Checked && DataSet->FieldByName("Orders_ID")->IsNull) {
							Accept = false;
						}
					}
					break;

		case 43: /*Accept = DataSet->FieldByName("TRANSPORT_ID")->AsInteger == MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger &&
								DataSet->FieldByName("FLAG_MES")->AsInteger > 0;
					if (!Accept) {
						RefreshGraphRow(DataSet);
					}
					else FillHintStructures(DataSet);
					*/
					if (DataSet->FieldByName("FLAG_KIND")->AsInteger == 1) {
						Accept = DataSet->FieldByName("GRAPH_ID")->AsInteger == MemTableEh41->FieldByName("GRAPH_ID")->AsInteger;
						FillHintStructures(DataSet);
					}
					else {
						 Accept = DataSet->FieldByName("TRANSPORT_ID")->AsInteger == MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger &&
									 DataSet->FieldByName("FLAG_MES")->AsInteger > 0;
						 if (!Accept) {
							 RefreshGraphRow(DataSet);
						 }
						 else FillHintStructures(DataSet);
					}
					break;
		default: Accept = FilterRecordStd(GetGDataRef(DataSet));
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::RefreshGraphRow(TDataSet* DSet)
{
	int GraphID = DSet->FieldByName("GRAPH_ID")->AsInteger;
	if (GraphID < 0) return;

	TMemoryRecordEh* MemRec = MemTableEh41->Rec;
	MemRec->DataValues["DRIVER_NAME"][dvvValueEh] = DSet->FieldByName("DRIVER_NAME")->Value;
	std::map<int, Vect>::iterator iter = TransWork.find(GraphID);
	if (iter != TransWork.end()) {
		TransWork.erase(iter);
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::FillHintStructures(TDataSet *DataSet)
{
	bool Accept = true;
	int FlagMes  = DataSet->FieldByName("Flag_Mes")->AsInteger;
	int FlagKind = DataSet->FieldByName("Flag_Kind")->AsInteger;
	if (FlagMes || FlagKind == 2) Accept = false;
	if (FlagMes || FlagKind) {
		int GraphID = DataSet->FieldByName(GDataGraph.FieldKey)->AsInteger;  // Transport or Driver ID
		int OrderID = DataSet->FieldByName("Orders_ID")->AsInteger;
		std::map<int, Vect>::iterator iter = TransWork.find(GraphID);
		if (iter == TransWork.end()) {
			std::vector<int> vect;
			vect.push_back(-OrderID);
			vect.push_back(DataSet->FieldByName("Min_Beg")->AsInteger);
			vect.push_back(DataSet->FieldByName("Min_End")->AsInteger);
			vect.push_back(DataSet->FieldByName("DRIVER_ID")->AsInteger);
			vect.push_back(DataSet->FieldByName("ORDER_STATE")->AsInteger);
			TransWork.insert(pair<int,Vect>(GraphID,vect));
		}
		else {
			std::vector<int>::iterator it = find(iter->second.begin(),iter->second.end(),-OrderID);
			if (it == iter->second.end()) {
				iter->second.push_back(-OrderID);
				iter->second.push_back(DataSet->FieldByName("Min_Beg")->AsInteger);
				iter->second.push_back(DataSet->FieldByName("Min_End")->AsInteger);
				iter->second.push_back(DataSet->FieldByName("DRIVER_ID")->AsInteger);
				iter->second.push_back(DataSet->FieldByName("ORDER_STATE")->AsInteger);
			}
			else if (!OrderID) {
				iter->second.push_back(-OrderID);
				iter->second.push_back(DataSet->FieldByName("Min_Beg")->AsInteger);
				iter->second.push_back(DataSet->FieldByName("Min_End")->AsInteger);
				iter->second.push_back(DataSet->FieldByName("DRIVER_ID")->AsInteger);
				iter->second.push_back(DataSet->FieldByName("ORDER_STATE")->AsInteger);
			}
		}
		if (FlagKind != 2) {
			std::map<int,AnsiString>::iterator iterHint = GraphHint.find(OrderID);
			if (iterHint != GraphHint.end()) {
				GraphHint[OrderID] = GetHintStr(DataSet);
			}
			else GraphHint.insert(pair<int,AnsiString>(OrderID,GetHintStr(DataSet)));
		}
	}
//	}
	return Accept;
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::CheckIntValue(int IVal,FieldFilter& FF)
{
	bool bRes = false;
	if (!FF.EqvValue.IsNull() && !FF.EqvValue.IsEmpty()) {
		if (IVal == FF.EqvValue) return true;
	}
	if (!FF.MinValue.IsNull() && !FF.MinValue.IsEmpty()) {
		if (IVal < FF.MinValue) return false;
		bRes = true;
	}
	if (!FF.MaxValue.IsNull() && !FF.MaxValue.IsEmpty()) {
		if (IVal > FF.MaxValue) return false;
		bRes = true;
	}
	return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::CheckStrValue(AnsiString& SVal,FieldFilter& FF)
{
	bool bRes = false;
	SVal = SVal.Trim().UpperCase();
	AnsiString Chk;
	if (!FF.EqvValue.IsNull() && !FF.EqvValue.IsEmpty()) {
		Chk = FF.EqvValue;
		Chk = Chk.Trim().UpperCase();
		if (Chk != "") {
			if (CheckName(SVal,Chk)) return true;
		}
	}
	if (!FF.MinValue.IsNull() && !FF.MinValue.IsEmpty()) {
		Chk = FF.MinValue;
		Chk = Chk.Trim().UpperCase();
		if (Chk != "") {
			if (SVal.Pos(Chk) == 1) bRes = true;
			else                    return false;
		}
	}
	if (!FF.MaxValue.IsNull() && !FF.MaxValue.IsEmpty()) {
		Chk = FF.MaxValue;
		Chk = Chk.Trim().UpperCase();
		if (Chk != "") {
			if (SVal.Pos(Chk) == SVal.Length() - Chk.Length()+1) bRes = true;
			else bRes = false;
		}
	}
	return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::CheckDateValue(TDateTime DT,FieldFilter& FF)
{
	bool bRes = false;
	DT = TDateTime(DT.FormatString("dd.mm.yy"));
	if (!FF.EqvValue.IsNull() && !FF.EqvValue.IsEmpty()) {
		TDateTime DTChk = FF.EqvValue;
		if (DT == DTChk) return true;
	}
	if (!FF.MinValue.IsNull() && !FF.MinValue.IsEmpty()) {
		TDateTime DTChk = FF.MinValue;
		if (DT < DTChk) return false;
		else            bRes = true;
	}
	if (!FF.MaxValue.IsNull() && !FF.MaxValue.IsEmpty()) {
		TDateTime DTChk = FF.MaxValue;
		if (DT > DTChk) return false;
		else            bRes = true;
	}
	return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::CheckTimeValue(TDateTime DT,FieldFilter& FF)
{
	bool bRes = false;
	int H1 = StrToInt(DT.FormatString("h"))*60 + StrToInt(DT.FormatString("n"));
	if (!FF.EqvValue.IsNull() && !FF.EqvValue.IsEmpty()) {
		TDateTime DTChk = FF.EqvValue;
		int H2 = StrToInt(DTChk.FormatString("h"))*60 + StrToInt(DTChk.FormatString("n"));
		if (H1 == H2) return true;
	}
	if (!FF.MinValue.IsNull() && !FF.MinValue.IsEmpty()) {
		TDateTime DTChk = FF.MinValue;
		int H2 = StrToInt(DTChk.FormatString("h"))*60 + StrToInt(DTChk.FormatString("n"));
		if (H1 < H2) return false;
		else         bRes = true;
	}
	if (!FF.MaxValue.IsNull() && !FF.MaxValue.IsEmpty()) {
		TDateTime DTChk = FF.MaxValue;
		int H2 = StrToInt(DTChk.FormatString("h"))*60 + StrToInt(DTChk.FormatString("n"));
		if (H1 > H2) return false;
		else         bRes = true;
	}
	return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetCurFldCheck(AnsiString& FldName,FieldFilter& FF)
{
	bool bRes = false;
	TField* Fld = MemTableEh31->FieldByName(FldName);
	TFieldType FldType = Fld->DataType;
	if (FF.NullCheck == 1) {
		if (MemTableEh31->FieldByName(FldName)->IsNull) return true;
	}
	int IVal;
	AnsiString SVal,Chk;
	TDateTime DT;
	switch (FldType) {
		case ftInteger:  IVal = MemTableEh31->FieldByName(FldName)->AsInteger;
							  bRes = CheckIntValue(IVal,FF);
							  break;
		case ftString:   SVal = MemTableEh31->FieldByName(FldName)->AsString;
							  bRes = CheckStrValue(SVal,FF);
							  break;
		case ftDateTime: DT = MemTableEh31->FieldByName(FldName)->AsDateTime;
							  if (FF.Format == "hh:nn") {
									bRes = CheckTimeValue(DT,FF);
							  }
							  else {
									bRes = CheckDateValue(DT,FF);
							  }
							  break;
	}
	return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::CheckOrderFilter()
{
	bool Res = true;
	for (FilterCols::iterator iter1 = OrderFilter.begin(); iter1 != OrderFilter.end(); ++iter1) {
		Res = true;
		for (FilterRows::iterator iter2 = (*iter1).begin(); iter2!=(*iter1).end(); ++iter2) {
			AnsiString FldName = iter2->first;
			for (vector<FieldFilter>::iterator iter3 = iter2->second.begin(); iter3 != iter2->second.end(); ++iter3) {
				 Res = GetCurFldCheck(FldName,*iter3);
				 if (Res) break;
			}
			if (!Res) break;
		}
		if (Res) break;
	}
	return Res;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBEditEhExit(TObject *Sender)
{
	EditExitStd(*WrkGData,Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::RestoreEditMultiFlag()
{
	if (RestoreEditMulti) {
		sCheckBox21->Checked = true;
		RestoreEditMulti = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBEditEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	EditKeyDownStd(*WrkGData,Sender,Key,Shift);
	if (Key == VK_RETURN || Key == VK_ESCAPE) {
		int EditCol;
		switch (PageTag) {
			case 1:	if (WrkGData != &GDataTransport) {
							SavePosStd(GDataTransport);
							ReOpenDSetStd(GDataTransport);
						}
						break;
			case 3:  RestoreEditMultiFlag();
						if (Key == VK_RETURN && DBGridEh31->RowDetailPanel->Visible)
						   FillRowDetailPanel();
						break;
		  }
	}
}
static int XX;
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhDrawColumnCell(TObject *Sender, const TRect &Rect,
			 int DataCol, TColumnEh *Column, TGridDrawStateEh State)
{
	DrawColumnCellStd(GetGDataRef(Sender),Rect,DataCol,Column,State);
	if (GetComponentTag(Sender) == 41) {
		if (Column->Tag > 6)
			DrawColumnCell(Rect,DataCol,Column,State);
		else
		   DBGridEh41->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
TColor ColorSpringGreen  = TColor(RGB(0,   255, 127)); 		// зеленый потемнее для зоны текущего заказом
TColor ColorPaleGreen    = TColor(RGB(152, 251, 152)); 		// зеленый посветлее для зон выбранных заказов
TColor ColorPeachPuff1   = TColor(RGB(255, 218, 185)); 		// для строки связанной с текущим заказом
//TColor ColorAntiqueWhite = TColor(RGB(250, 235, 215)); 	// для пустой ячейки без заказа
TColor ColorForectGreen  = TColor(RGB(34,  139,  34)); 		// для заказа в графике с водителем по умолчанию
TColor ColorSeeGreen     = TColor(RGB(46, 139, 87));
TColor ColorLimeGreen 	 = TColor(RGB(50, 205, 50));
TColor ColorCornflowerBlue = TColor(RGB(100,149,237));  		// не тот водитель
TColor ColorLavender     = TColor(RGB(230, 230, 250)); 		// зона заказов
TColor ColorLawnGreen 	 = TColor(RGB(124, 252, 0));
//TColor GreenArr[]  = { ColorForectGreen,  ColorSeeGreen, ColorLimeGreen };
TColor GreenArr[]  = { ColorForectGreen,  ColorLawnGreen, ColorLimeGreen };
TColor DarkStateBlue   = TColor(RGB(72,  61,  139));
TColor StateBlue       = TColor(RGB(106, 90,  205));
TColor MediumStateBlue = TColor(RGB(123, 104, 238));
TColor LightStateBlue  = TColor(RGB(132, 112, 255));

TColor BlueArr[]  = { StateBlue,  MediumStateBlue, LightStateBlue };


//TColor BlueArr[]  = { ColorStateGreen,  ColorLawnGreen, ColorLimeGreen };
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DrawZone(DrawData& DD,const TRect &Rect, int MinBeg, int MinEnd, TColor Color)
{
	int TimeWrk  = DD.TimeWrk;
	if (!TimeWrk) return;
	TDateTime DT_Beg_Ord = DD.DT_Beg_Ord;
	TDateTime TM_Beg_Ord = DD.TM_Beg_Ord;
//	int Days = TDateTime(GetDateStr(DT_Beg_Ord)) - DT_Beg_Grp;
	int Days = TDateTime(GetDateStr(DT_Beg_Ord)) - (DT_Graph - 1);

	int BegZone = Days*1440 +
					 StrToInt(TM_Beg_Ord.FormatString("h"))*60 + StrToInt(TM_Beg_Ord.FormatString("n")) -
					 StrToInt(TM_Beg_Grp.FormatString("h"))*60 - StrToInt(TM_Beg_Grp.FormatString("n"));
	int EndZone = BegZone + TimeWrk;

	TRect RcZone;
	if (BegZone < MinEnd && EndZone > MinBeg) {
		RcZone  = Rect;
		if (BegZone > MinBeg) RcZone.Left  = Rect.Left + double((BegZone - MinBeg) * (Rect.Right - Rect.Left))/60;
		if (EndZone < MinEnd) RcZone.Right = Rect.Left + double((EndZone - MinBeg) * (Rect.Right - Rect.Left))/60;
	}
	else return;
	DBGridEh41->Canvas->Brush->Color = Color;
	DBGridEh41->Canvas->FillRect(RcZone);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DrawColumnCell(const TRect &Rect,int DataCol, TColumnEh *Column, TGridDrawStateEh State)
{

	bool Focused = State.Contains(Gridseh::gdFocused);
	int Y = State.ToInt();
	bool T =  Y  & 0x0001;
	TDBGridEh* Grid = DBGridEh41;
	Focused = T && Grid->Focused();
	DataCol -= DBGridEh41->FrozenCols;

	Gridseh::TGridCoord GC = Grid->MouseCoord((Rect.Left+Rect.Right)/2 ,(Rect.Top+Rect.Bottom)/2);
	Grid->DefaultDrawColumnCell(Rect,  DataCol, Column, State);
	AnsiString FldName = Column->FieldName;

	int GraphID       = MemTableEh41->FieldByName(GDataGraph.FieldKey)->AsInteger;
//	int TransDriverID = MemTableEh41->FieldByName("Trans_Driver_ID")->AsInteger;
//	int OrderID  = SData.OrderID;
//	int TimeWrk  = SData.TimeWrk;
	int FlagKind = MemTableEh41->FieldByName("FLAG_KIND")->AsInteger;

	TRect RcFill, RcCross, RcZone;
	int MinBeg = DataCol * 60;  // сдвиг в мин от начала диапазона
	int MinEnd = MinBeg  + 60;

// ==== рисуем зеленую зону для текущего заказа ================================
	Grid->Canvas->Brush->Color = (Focused) ? clRed   :
										  (CurGraphID == GraphID) ?
										  (FlagKind) ? TColor(RGB(173, 216, 230)) : ColorPeachPuff1 :
										  (FlagKind) ? ColorLavender : clWindow;
	Grid->Canvas->FillRect(Rect);
	DrawZone(SData,Rect, MinBeg, MinEnd,ColorSpringGreen);
	for (std::map<int,DrawData>::iterator iter = DrawMap.begin(); iter != DrawMap.end(); ++iter) {
		DrawZone(iter->second,Rect, MinBeg, MinEnd,Focused ? clRed : ColorPaleGreen);
	}
// ==== рисуем зоны заказов ====================================================
	std::map<int, Vect>::iterator iter = TransWork.find(GraphID);   // ищем транспорт или водителя
	if (iter != TransWork.end()) {
		std::vector<int> vect = iter->second;
		std::vector<int>::iterator iter = vect.begin();
		int size = vect.size();
		// ищем заказ в списке связанный с текущим GraphID
		for (int i=0; i < size; i+=5 ) {
			int O_ID  = -*iter++;   // заказ связанный с текущей строкой графика
			int X1    =  *iter++;   // начало в минутах
			int X2    =  *iter++;   // конец в минутах
			int D_ID  =  *iter++;   // водитель или (0)
			int State =  *iter++;
			int C_Idx = (i/5) % 3;
			if (X1 < MinEnd && X2 > MinBeg ) {                      	// если текущая ячейка перемекается с зоной заказа
				RcFill = Rect;
				if (X1 > MinBeg) RcFill.Left  = Rect.Left + double((X1 - MinBeg) * (Rect.Right - Rect.Left))/60;
				if (X2 < MinEnd) RcFill.Right = Rect.Left + double((X2 - MinBeg) * (Rect.Right - Rect.Left))/60;
//				Grid->Canvas->Brush->Color =  (TransDriverID == D_ID && TransDriverID > 0) ?
				TColor OrderColor;
				if (Focused) {
					OrderColor = clRed;
				}
				else {
					if (O_ID) {
						OrderColor  = (CurDriverID == D_ID && CurDriverID > 0 && CurGraphCol <= 6) ?
											TColor(RGB(255, 0, 255)) :               // текущий водитель
											(GraphID > 0) ?  GreenArr[C_Idx] :        // прочие заказы разными зелеными цветами
											 ColorCornflowerBlue;     // нераспределенный заказ
						if (sCheckBox42->Checked && State < 3) {
							OrderColor  = (CurDriverID == D_ID && CurDriverID > 0 && CurGraphCol <= 6) ?
											  TColor(RGB(72, 61, 139)) :               // текущий водитель
											  (GraphID > 0) ?  BlueArr[C_Idx] :           // прочие заказы
												ColorCornflowerBlue;     // нераспределенный заказ
						}
					}
					else {
						OrderColor =  TColor(RGB(139, 137, 137));  // ВЫХОДНОЙ
					}
				}
				Grid->Canvas->Brush->Color = OrderColor;
				Grid->Canvas->FillRect(RcFill);
				std::vector<int>::iterator iter2 = vect.begin();
				// пересекающиеся заказы в графике рисуем желтым
				for (int j = 0; j < size; j+=5) {
					int I_ID = -*iter2++;
					int Y1   =  *iter2++;
					int Y2   =  *iter2++;
					if (Y1 < MinEnd && Y2 > MinBeg && I_ID != O_ID) {
						RcCross = Rect;
						if (Y1 > MinBeg) RcCross.Left  = Rect.Left + double((Y1 - MinBeg) * (Rect.Right - Rect.Left))/60;
						if (Y2 < MinEnd) RcCross.Right = Rect.Left + double((Y2 - MinBeg) * (Rect.Right - Rect.Left))/60;
						if (RcCross.Left < RcFill.Right && RcCross.Right > RcFill.left) {
							RcCross.Left  = max(RcFill.Left,  RcCross.Left);
							RcCross.Right = min(RcFill.Right, RcCross.Right);
							Grid->Canvas->Brush->Color = (Focused) ? TColor(RGB(240, 128, 128)) : clYellow;
							Grid->Canvas->FillRect(RcCross);
						}
					}
					++iter2; ++iter2;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::RecordNotInSelectCondition()
{
	TDateTime DT;
	AnsiString Fld;
	switch (SelIndex) {
		case 0: Fld = "DT_MAKE";      break;
		case 1: Fld = "DT_BEG";       break;
		case 2: return false;
	}
	DT = MemTableEh31->FieldByName(Fld)->AsDateTime;
	return (DT < DT_Beg_Ord || DT > DT_End_Ord + !SelIndex - 1);  //??
}
TColor CurrentLineColor = TColor(RGB(250, 235, 215));   // AntiqueWhite
TColor FocusedLineColor = TColor(RGB(255, 222, 173));   // NavajoWhite
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhGetCellParams(TObject *Sender, TColumnEh *Column,
			 TFont *AFont, TColor &Background, TGridDrawStateEh State)
{
	bool CurrentRec,NotInSelCondition;
	switch(GetComponentTag(Sender)) {
		case 11: if (CurTransCompID && CurTransCompID == MemTableEh11->FieldByName("Trans_Company_ID")->AsInteger)
						if (DBGridEh11->Focused()) Background = FocusedLineColor;
					break;
		case 12: if (CurTransTypeID && CurTransTypeID == MemTableEh12->FieldByName("Trans_Type_ID")->AsInteger)
						if (DBGridEh12->Focused()) Background = FocusedLineColor;
					break;
		case 13: if (CurTransportID && CurTransportID == MemTableEh13->FieldByName("Transport_ID")->AsInteger)
						if (DBGridEh13->Focused()) Background = FocusedLineColor;
					break;
		case 21:	if (CurClientID == MemTableEh21->FieldByName(GDataClient.FieldKey)->AsInteger) {
						Background = (DBGridEh21->Focused()) ? FocusedLineColor : CurrentLineColor;
					}
					break;
		case 31: if (!CurOrderID) break;
					NotInSelCondition = RecordNotInSelectCondition();

					CurrentRec = false;
					if (MemTableEh31->FieldByName(GDataOrders.FieldKey)->AsInteger == CurOrderID) {
						if (NotInSelCondition) Background =  TColor(RGB(255, 228, 225));   // текущий заказ вне фильтра
						else                   Background =  FocusedLineColor;             // текущий заказ
						CurrentRec = true;
					}
					else if (NotInSelCondition)
						Background = TColor(RGB(255, 239, 213));//clInfoBk;               // вне диапазна выборки
					if (MemTableEh31->FieldByName("ORDER_TYPE")->AsInteger == 3) {
						switch(MemTableEh31->FieldByName("ORDER_STATE")->AsInteger) {
							case 5:  if (CurrentRec) Background =  TColor(RGB(  0, 191, 255));
										else            Background =  TColor(RGB(135, 206, 250));
							case 6:  break;
							default: if (CurrentRec) Background = TColor(RGB(  0, 206, 209));
										else            Background = TColor(RGB(175, 238, 238));
										break;
						}
					}
					break;
		case 41: if (CurGraphID && CurGraphID == MemTableEh41->FieldByName(GDataGraph.FieldKey)->AsInteger) {
						Background = MemTableEh41->FieldByName("FLAG_KIND")->AsInteger	? TColor(RGB(173, 216, 230)) : TColor(RGB(255, 218, 185));
					}
					else {
						Background = MemTableEh41->FieldByName("FLAG_KIND")->AsInteger	? TColor(RGB(230, 230, 250)) : clWindow;
					}
					break;

		default:	if (!FilterRecordStd(GetGDataRef(Sender))) {
						Background = clInfoBk;
					}
					break;
	}
	GetCellParamsStd(GetGDataRef(Sender), AFont,Background,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::RestoreMultiFlag()
{
	 switch (PageTag) {
		  case 3: GDataOrders.Flags |= MULTIPLE_SEL;
					 break;
		  case 5: GDataOutlay.Flags |= MULTIPLE_SEL;	break;
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	bool SetMultiFlag = false;
	RestoreEditMulti = false;
	int ID;
	int Col = 0;
	int Tag = GetComponentTag(Sender);

	switch (Key) {
		case VK_DELETE:   switch (Tag) {
									case 31: GDataOrders.Flags &= ~SAVE_SELECTION;
									         break;
									case 41: DetachOuterTransport();
												return;
									case 43: ClearTransportFromDetail();
												return;
								}
								break;
		case VK_SPACE:    switch (Tag) {
									case 41: if (!MemTableEh41->FieldByName("FLAG_KIND")->AsInteger)
													return;
								}
								break;
		case VK_INSERT:	switch (Tag) {
									case 22:
									case 23:
												ID = MemTableEh21->FieldByName("CLIENT_ID")->AsInteger;
												if (!ID) return;
												WrkGData->AddCurParam(ftInteger, "CLIENT_ID", ID);
												if (Tag == 23) {
													Variant V = MemTableEh21->FieldByName("CLIENT_FLAG")->AsVariant;
													WrkGData->AddCurParam(ftInteger, "FLAG_CALC_INCOME", V);
												}
												break;
									case 41: AttachOuterTransport();
												return;
									case 62: ID = MemTableEh61->FieldByName("TOWN_ID")->AsInteger;
												if (!ID) return;
												GetGDataRef(Sender).AddCurParam(ftInteger, "TOWN_ID", ID);
												break;

								}
								break;
		case VK_RETURN:   switch(Tag) {
									case 31:	Col = WrkGData->WrkGrid->Columns->Items[WrkGData->WrkGrid->Col-1]->Tag;
												if ((Col >= 13 && Col <= 15) || Col == 26 || Col == 27 || Col == 33 || Col == 34 || Col == 35 ) {
													if (sCheckBox21->Checked) {
														RestoreEditMulti = true;
														sCheckBox21->Checked = false;  // только по одной строку
													}
												}
												//
									case 51: (*WrkGData).Flags &= ~MULTIPLE_SEL; // не выбирать текущую строку для редактирования
												SetMultiFlag = true;
												break;
									case 41: if (WrkGData->WrkGrid->Col == 6) ChangeDriver();
												else ChangeTransport();
												return;
									case 43: ProcKeyDownStd(GetGDataRef(Sender),Key);
												DBGridEh41->Repaint();
												return;
									case 71:	SwapEmplRightBit();     break;
								}
								break;
		case VK_BACK:     switch(Tag) {
									case 31:  Col = WrkGData->WrkGrid->Columns->Items[WrkGData->WrkGrid->Col-1]->Tag;
												 if (Col == 14) {
													 WrkGData->AddCurParam(ftString,WrkGData->WrkGrid->Columns->Items[WrkGData->WrkGrid->Col-1]->FieldName,Null);
												 }
									case 51:  WrkGData->Flags &= ~MULTIPLE_SEL;
												 SetMultiFlag = true;
												 break;
									case 41:  Col = WrkGData->WrkGrid->Columns->Items[WrkGData->WrkGrid->Col-1]->Tag;
												 if (Col == 6) ClearDriver();
												 else          ClearTransport();
												 return;
								}
								break;
	}
	ProcKeyDownStd(GetGDataRef(Sender),Key);
	if (Tag == 31) {
		SetEditBitMask(MemTableEh31);  //SetOrdersBitMask();
		if (Key == VK_DELETE) GDataOrders.Flags |= SAVE_SELECTION;
		if (DBGridEh31->RowDetailPanel->Visible) {
			if (Key == VK_BACK || (Key == VK_RETURN && DBGridEh31->Focused()) ) {
				FillRowDetailPanel();
			}
		}
	}
	if (SetMultiFlag) RestoreMultiFlag();
	if (RestoreEditMulti && WrkGData->WrkGrid->Focused()) RestoreEditMultiFlag();

	if (GetComponentTag(Sender) == 31) {
		if (GDataOrders.EditCol == 9 || Key == VK_INSERT) SetEditBitMask(MemTableEh31);
		TDBGridEh* Grid = DBGridEh31;
		if (Shift.Contains(ssCtrl) || Shift.Contains(ssAlt)) {
			switch (Key) {
				case 'X' : HideCurrentColumn(Grid);
							  break;
				case 'V' : ShowCurColumnGroup (Grid);
							  break;
				case 'B' : HideCurColumnGroup (Grid);
							  break;
				case 'N' : ShowNeighbours   (Grid);
							  break;
				case 'A' : ShowAllColumns   (Grid, !Shift.Contains(ssShift));  Key = NULL;
							  break;
				case 'D' : SetDefaultValue  (Grid);   break;
			}
		}
		if (Shift.Contains(ssAlt)) {
			switch(Key) {
				case VK_LEFT:   ShowNextColumn(Grid,-1);  break;
				case VK_RIGHT:  ShowNextColumn(Grid, 1);  break;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DetachOuterTransport()
{
	if (MemTableEh41->FieldByName("FLAG_KIND")->AsInteger) return;
	int TransportID = MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger;
	std::vector<int>::iterator it = find(ShowTransVect.begin(),ShowTransVect.end(),TransportID);
	if (it != ShowTransVect.end()) {
		ShowTransVect.erase(it);
		MemTableEh41->Prior();
		PulseFilterStd(GDataGraph);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::AttachOuterTransport()
{
	TParams* Params = new TParams();
	int TransportID = 0;
	if (GetTransportID(this, 0, TransportID,Params)) {
		std::vector<int>::iterator it = find(ShowTransVect.begin(),ShowTransVect.end(),TransportID);
		if (it == ShowTransVect.end()) {
			ShowTransVect.push_back(TransportID);
			PulseFilterStd(GDataGraph);
			GDataGraph.KeyValue = TransportID;
			RestorePosStd(GDataGraph,false);
			SetAfterScroll(MemTableEh41);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhKeyPress(TObject *Sender, System::WideChar &Key)
{
	ProcKeyPressStd(GetGDataRef(Sender),Key);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhSortMarkingChanged(TObject *Sender)
{
	TDBGridEh* DBGridEh = dynamic_cast<TDBGridEh*>(Sender);
	AnsiString s = " ";
	AnsiString SS;
	for (int i = 0; i < DBGridEh->SortMarkedColumns -> Count; ++i)  {
		TColumnEh* Column = DBGridEh->SortMarkedColumns->Items[i];
		SS = Column->FieldName;
		switch (DBGridEh->Tag) {
			case 11:	switch(Column->Tag) {
							case  3: SS = "TRANS_COMPANY_FLAG";      break;
						}
						break;
			case 41: return;

		}
		s += SS;
		if (Column->Title->SortMarker == smUpEh)
		s += " DESC, ";
		else if (Column->Title->SortMarker == smDownEh)
		s += " ASC, ";
	}
	s = s.SubString(1, s.Length()-2).Trim();
	GridData& GData = GetGDataRef(DBGridEh);
	if (s == "") {
		s = GData.DefSortOrder;
	}
	TMemTableEh* MemTableEh = dynamic_cast<TMemTableEh*>(DBGridEh->DataSource->DataSet);
	SavePosStd(GData);
	MemTableEh->SortOrder = s;
	RestorePosStd(GData,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearTransport()
{
	if (MemTableEh41->FieldByName("FLAG_KIND")->AsInteger) return;
	int Col = DBGridEh41->Col -DBGridEh41->FrozenCols - 1;
	int TransportID = MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger;

	int MinBeg = Col * 60;  // сдвиг в мин от начала диапазона
	int MinEnd = MinBeg  + 60;

	std::map<int, Vect>::iterator iter = TransWork.find(TransportID);   // ищем транспорт или водителя
	if (iter != TransWork.end()) {
		std::vector<int> vect = iter->second;
		std::vector<int>::iterator iter = vect.begin();
		int size = vect.size();
		// ищем заказ в списке связанный с текущим GraphID
		for (int i=0; i < size; i+=5 ) {
			int O_ID = -*iter++;   // заказ связанный с текущей строкой графика
			int X1   =  *iter++;   // начало в минутах
			int X2   =  *iter++;   // конец в минутах
			++iter;                // водитель или (0)
			++iter;                // состояние
			if (X1 < MinEnd && X2 > MinBeg ) {                      	// если текущая ячейка перемекается с зоной заказа
				if (X1 == 0) {
					OutputMessage("Нельзя снять с транпорта заказ, у которого время \n"
									  "начала работы не отображается в графике полностью");
				}
				else ClearTransportOne(O_ID);
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearTransportFromDetail()
{
	TDateTime DT1 = TDateTime(GetDateStr(MemTableEh43->FieldByName("DT_Beg")->AsDateTime) +  " " +
									  MemTableEh43->FieldByName("Time_Beg")->AsDateTime.FormatString("hh:nn"));

	TDateTime DT2 = TDateTime(GetDateStr(DT_Graph - 1) + " " +  TM_Beg_Grp.FormatString("hh:nn"));
	if (DT1 < DT2) {
		OutputMessage("Нельзя снять с транпорта заказ, у которого время \n"
						  "начала работы не отображается в графике полностью");
		return;
	}
	GDataDetail.WrkQuery      = Query44;
	Variant V;
	V.Clear();
	GDataDetail.AddCurParam(ftInteger,  "TRANSPORT_ID",V);
	GDataDetail.AddCurParam(ftDateTime,"DT_WRK",DT_Graph);
//	int  TransFlag   = MemTableEh41->FieldByName("TRANS_COMPANY_FLAG")->AsInteger;
	int  TransportID = MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger;
	if (WriteDataStd(GDataDetail,false)) {
		if (MemTableEh43->FieldByName("TRANSPORT_ID")->IsNull &&
			MemTableEh41->FieldByName("TRANS_COMPANY_FLAG")->AsInteger) {
			std::vector<int>::iterator it = find(ShowTransVect.begin(),ShowTransVect.end(),TransportID);
			if (it == ShowTransVect.end()) {
				ShowTransVect.push_back(TransportID);
			}
		}
   }
	GDataDetail.WrkQuery      = Query45;
	ProcRefreshStd(GDataGraph,true);
	DBGridEh41->RowDetailPanel->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::StoreOrdersTbl()
{
	if (MemTableEh31->Active) {
		SavePosStd(GDataOrders);
		MemTableEh31->Active = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearTransportOne(int OrdersID)
{
	GDataGraph.CurKeyPressed = VK_BACK;
	std::map<int,AnsiString>::iterator iterHint = GraphHint.find(OrdersID);
	if (iterHint != GraphHint.end()) {
		AnsiString Hint = iterHint->second;
		int  TransportID = MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger;
		int  TransFlag   = MemTableEh41->FieldByName("TRANS_COMPANY_FLAG")->AsInteger;
		if (AskQuestionStd("Удалить из графика\n"+Hint)) {
			AnsiString SQL      = "select DateChange from Orders where Orders_ID = " + IntToStr(OrdersID);
			Variant V;
			if (OpenTmpQuery(SQL,"DateChange",V,DModT->Database1)) {
				GDataGraph.AddCurParam(ftDateTime,"DATECHANGE",V);
				V.Clear();
				GDataGraph.AddCurParam(ftInteger,"TRANSPORT_ID",V);
				GDataGraph.AddCurParam(ftInteger,"ORDERS_ID", OrdersID);
				ProcUnsAllStd(GDataGraph, NULL);
				if (WriteDataStd(GDataGraph,false)) {
					if (TransFlag) {
						std::vector<int>::iterator it = find(ShowTransVect.begin(),ShowTransVect.end(),TransportID);
						if (it == ShowTransVect.end()) {
							ShowTransVect.push_back(TransportID);
						}
					}
					StoreOrdersTbl();
					ProcRefreshStd(GDataGraph, false);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearDriver()
{
	if (MemTableEh41->FieldByName("FLAG_KIND")->AsInteger) return;
	if (MemTableEh41->FieldByName("DRIVER_NAME")->AsString.Pos("(Изм")) {
		if (AskQuestionStd("Убрать замену водителя по умолчанию ?")) {
			 int TransportID = MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger;
			 AnsiString SQL = "execute procedure EDIT_DEF_DAY_DRIVER('"+GetDateStr(DT_Graph) + "'," +
							  IntToStr(TransportID) + ",null," +GetSelEditParams() + ")";
			 ExecuteQry(SQL,DModT->Database1,true);
			 ProcRefreshStd(GDataGraph, false);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ChangeDriver()
{
	if (MemTableEh41->FieldByName("FLAG_KIND")->AsInteger) return;
	int DriverID = MemTableEh41->FieldByName("Trans_Driver_ID")->AsInteger; //????
	bool ReOpen = false;
	if (GetDriverID(this, 0,DriverID,GDataGraph.CurParams)) {
		int TransportID = MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger;
		std::map<int,Vect>::iterator iter = TransWork.find(TransportID);
		AnsiString SQL = "execute procedure EDIT_DEF_DAY_DRIVER('"+GetDateStr(DT_Graph) + "'," +
							  IntToStr(TransportID) + "," + IntToStr(DriverID) + "," +GetSelEditParams() + ")";
		if (!ExecuteQry(SQL,DModT->Database1,true)) return;
		ReOpen = true;
		if (iter != TransWork.end()) {
			std::vector<int> vect = iter->second;
			std::vector<int>::iterator iter = vect.begin();
			int size = vect.size();
			// ищем заказ в списке связанный с текущим GraphID
			for (int i=0; i < size; i+=5 ) {
				int OrdersID = -*iter++;   // заказ связанный с текущей строкой графика
				++iter; ++iter; ++iter; ++iter;
//		iter += 3;
				GDataGraph.WrkQuery     = Query45;
				AnsiString SQL      = "select DateChange from Orders where Orders_ID = " + IntToStr(OrdersID);
				Variant V;
				if (OrdersID && OpenTmpQuery(SQL,"DateChange",V,DModT->Database1)) {
					GDataGraph.AddCurParam(ftDateTime,"DATECHANGE",V);
					GDataGraph.AddCurParam(ftInteger,"ORDERS_ID",OrdersID);
					GDataGraph.AddCurParam(ftInteger,"DRIVER_ID",DriverID);
					ReOpen = true;
					if (!WriteDataStd(GDataGraph,false))
						break;
				}
			}
		}
	}
	GDataGraph.WrkQuery     = Query44;
	if (ReOpen) {
		ProcRefreshStd(GDataGraph, false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ChangeTransport()
{
	if (MemTableEh41->FieldByName("FLAG_KIND")->AsInteger) return;

	/*
	AnsiString S = TransportCanBeChanged();
	if (S != "")  {
		OutputMessage(S);
		return;
	}
*/
	AnsiString WarnMsg;
	AnsiString TagTransType   = MemTableEh41->FieldByName("TRANS_TYPE_NAME")->AsString;
	AnsiString TransportName  = MemTableEh41->FieldByName("TRANSPORT_NAME")->AsString;
	AnsiString Reg_Number     = MemTableEh41->FieldByName("REG_NUMBER")->AsString;
	int        TagPassNumber  = MemTableEh41->FieldByName("PASS_NUMBER")->AsInteger;
	int        TransportID    = MemTableEh41->FieldByName("TRANSPORT_ID")->AsInteger;

	int Size = GDataGraph.SelArray.size();
	bool ClearSel = false;
	if (!Size) {
		if (PrvGraphID < 0 && MemTableEh41->Locate("GRAPH_ID",PrvGraphID,TLocateOptions())) {
			if (MemTableEh41->FieldByName("ORDER_STATE")->AsInteger < 1) {
				OutputMessage("В график можно ставить только оформленные заказы");
				return;
			}
			ProcSelectStd(GDataGraph,false);
			ClearSel = true;
			DBGridEh41->Repaint();
			AfterScrollStd(*WrkGData);
		}
		else return;
	}
	GDataGraph.CurKeyPressed = VK_RETURN;
	bool ReOpen = false;
	std::vector<GridKeyValue>::reverse_iterator iter = GDataGraph.SelArray.rbegin();
	for (; iter != GDataGraph.SelArray.rend(); ++iter) {
		GDataGraph.KeyValue = *iter;
		if (RestorePosStd(GDataGraph,false)) {
			if (MemTableEh41->FieldByName("ORDER_STATE")->AsInteger < 1) {
				OutputMessage("В график можно ставить только оформленные заказы\nЗаказ => " +
								  MemTableEh41->FieldByName("HINT_STR5")->AsString + "\nне оформлен");
				continue;
			}
			int ID = MemTableEh41->FieldByName("GRAPH_ID")->AsInteger;
			AnsiString SrcTransType  = MemTableEh41->FieldByName("TRANS_TYPE_NAME")->AsString;
			int        SrcPassNumber = MemTableEh41->FieldByName("PASS_NUMBER")->AsInteger;
			if (SrcTransType != TagTransType) {
				WarnMsg = "Тип ТС в заказе  - " + SrcTransType + "\n" +
							 "Тип ТС в графике - " + TagTransType + "\n";
			}
			if (SrcPassNumber > TagPassNumber) {
				WarnMsg += "Требуемое число мест - " + IntToStr(SrcPassNumber) + "\n" +
							  "меньше числа мест ТС - " + IntToStr(TagPassNumber) + "\n";
			}
			AnsiString Hint5 = MemTableEh41->FieldByName("HINT_STR5")->AsString;
//			Hint4 = GetPiece(Hint4,". Вод:",1);
//			Hint4 = "Заказу " + Hint4.SubString(9,100);
			if (AskQuestionStd(WarnMsg+"Приписать ТС '" + TransportName + "' " + Reg_Number + " к заказу " + Hint5 + " ?")) {
				GDataGraph.AddCurParam(ftInteger,"TRANSPORT_ID",TransportID);
				GDataGraph.AddCurParam(ftDateTime,"DT_WRK",DT_Graph);
				ReOpen = true;
				GDataGraph.CurKeyPressed = 0;
				if (WriteDataStd(GDataGraph,false)) {
					StoreOrdersTbl();
					std::map<int,DrawData>::iterator iterD = DrawMap.find(ID);
					if (iterD != DrawMap.end()) {
						DrawMap.erase(iterD);
					}
				}
				else break;
			}
		}
	}
	if (ReOpen) {
		ProcUnsAllStd(GDataGraph, NULL);
		ProcRefreshStd(GDataGraph, false);
		GDataGraph.KeyValue = TransportID;
		RestorePosStd(GDataGraph,false);
	}
	else if (ClearSel) {
		ProcUnsAllStd(GDataGraph, NULL);
		DBGridEh41->Repaint();
	}
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormTrans::TransportCanBeChanged()
{
/*
	int OrderID = MemTableEh31->FieldByName("ORDERS_ID")->AsInteger;
	if (!OrderID)      return "Нет заказов в таблице заказов";
	if (!GraphTransID) return "Нет транспорта в списке ТС";
	if (GraphTransID ==OrderTransID) return "ТС '" + MemTableEh41->FieldByName("TRANSPORT_NAME")->AsString +
														 "уже приписано к заказу " + MemTableEh31->FieldByName("ORDERS_ID")->AsString;

	int TimeWrk = MemTableEh31->FieldByName("Wrk_Minut")->AsInteger;
	if (!TimeWrk) return "Не указано время работы в заказе";
	if (MemTableEh31->FieldByName("DT_BEG")->IsNull) return "Не указано начало работы в заказе";
	TDateTime DT_Beg_Ord = TDateTime(GetDateStr(MemTableEh31->FieldByName("DT_BEG")->AsDateTime));
	TDateTime TM_Beg_Ord = MemTableEh31->FieldByName("TIME_BEG")->AsDateTime;
	int Days = TDateTime(GetDateStr(DT_Beg_Ord)) - DT_Beg_Grp;
	int BegZone = Days*1440 +
				 StrToInt(TM_Beg_Ord.FormatString("h"))*60 + StrToInt(TM_Beg_Ord.FormatString("n")) -
				 StrToInt(TM_Beg_Grp.FormatString("h"))*60 - StrToInt(TM_Beg_Grp.FormatString("n"));
	int EndZone = BegZone + TimeWrk;
	int MaxZone = DBGridEh42->Columns->Count*60;
	if (BegZone >= 0 && EndZone <=MaxZone) { // зона заказа внутри графика
		std::map<int, Vect>::iterator iter = TransWork.find(GraphTransID);
		if (iter != TransWork.end()) {
			std::vector<int> vect = iter->second;
			std::vector<int>::iterator iter = vect.begin();
			int size = vect.size();
			for (int i=0; i < size; i=i+4 ) {
				int O_ID = -*iter++;
				int X1   =  *iter++;
				int X2   =  *iter++;
				*iter++;
				if (X1 < EndZone && X2 > BegZone && O_ID != OrderID) {                      	// если текущая ячейка перемекается с зоной заказа
					return "Нельзя приписать ТС к заказу    \t" + IntToStr(OrderID) + ",\n" +
							 "т.к. оно уже приписано к заказу \t" + IntToStr(O_ID);
				}
			}
		}
		AnsiString S;
		return "";
	}
	else return "Период выполнения заказа не умещается в сетке графика";
	*/
	return "";
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::AddCurrentRow(GridData& GData,int Mul, bool Show, bool Clear)
{
//	bool Selected;
	TDataSet* DSet = GData.WrkDSet;
	if (Clear) {
		ClearSums();
		if (PageTag == 4) {
//			DrawMap.clear();
		}
	}
	else {
		int ID;
		switch (PageTag) {
			case 3:	SumPayCalc += Mul*DSet->FieldByName("PAY_CALC")->AsInteger;
						SumPayRes  += Mul*DSet->FieldByName("PAY_RES")->AsInteger;
						SumPayAvc  += Mul*DSet->FieldByName("PAY_AVC")->AsInteger;
						SumPayRest += Mul*DSet->FieldByName("PAY_REST")->AsInteger;

						SumPayExc  += Mul*DSet->FieldByName("EXC_PAY")->AsInteger;
						SumPayMng  += Mul*DSet->FieldByName("MNG_PAY")->AsInteger;
						SumPayDrv  += Mul*DSet->FieldByName("DRV_PAY")->AsInteger;
						SumIncCalc += Mul*DSet->FieldByName("INCOME")->AsInteger;
						break;
			case 4:  ID = MemTableEh41->FieldByName("GRAPH_ID")->AsInteger;
						if (Mul > 0) {
							 DrawData DD;
							 DD.FieldKey = GDataGraph.FieldKey;
							 DD.Fill(MemTableEh41);
							 DrawMap.insert(pair<int,DrawData>(ID,DD));
						}
						else if (Mul<0) {
							 std::map<int,DrawData>::iterator iter = DrawMap.find(ID);
							 if (iter != DrawMap.end()) {
								 DrawMap.erase(iter);
							 }
						}
						break;
			case 5:	SumOutlay  += Mul*DSet->FieldByName("OUTLAY_VALUE")->AsInteger;
						break;
			default: return;
		}
	}
	if (Show) ShowSummary(GData.WrkGrid);
}
//---------------------------------------------------------------------------
AnsiString EndWordStr(int X)
{
	if (X > 4 && X < 20) return "";
	AnsiString S;
	switch (X % 10) {
		case 1: S = "а"; break;
		case 2:
		case 3:
		case 4: S = "и"; break;
	}
	return S;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ShowSummary(TDBGridEh* Grid)
{
	int Size;
	AnsiString Empty;
	switch (Grid->Tag) {
		case 31: Grid->Columns->Items[37]->Footer->Value = IntToStr(SumPayCalc);
					Grid->Columns->Items[38]->Footer->Value = IntToStr(SumPayRes);
					Grid->Columns->Items[40]->Footer->Value = IntToStr(SumPayAvc);
					Grid->Columns->Items[43]->Footer->Value = IntToStr(SumPayRest);
					Grid->Columns->Items[46]->Footer->Value = IntToStr(SumPayExc);
					Grid->Columns->Items[48]->Footer->Value = IntToStr(SumPayMng);
					Grid->Columns->Items[50]->Footer->Value = IntToStr(SumPayDrv);
					Grid->Columns->Items[51]->Footer->Value = IntToStr(SumIncCalc);
					Size = GDataOrders.SelArray.size();
					if (Size) {
						Grid->Columns->Items[1]->Footer->Value = "Выбрано:";
						Grid->Columns->Items[2]->Footer->Value = IntToStr(Size) + " строк" + EndWordStr(Size);
					}
					else {
						Grid->Columns->Items[1]->Footer->Value = Empty;
						Grid->Columns->Items[2]->Footer->Value = Empty;
					}
					break;
		case 51: Grid->Columns->Items[7]->Footer->Value = IntToStr(SumOutlay);
					Size = GDataOutlay.SelArray.size();
					Grid->Columns->Items[4]->Footer->Value = (Size) ? AnsiString("Выбрано: "+ IntToStr(Size) + " строк" + EndWordStr(Size)) : Empty;
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SetDefaultValue(TDBGridEh* Grid)
{
	int Idx = DBGridEh31->Col - 1;
	SetDefaultValue(Grid,Idx);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SetDefaultValue(TDBGridEh* Grid,int Idx)
{
/*
	if (Grid->Tag != 31) return;
	AnsiString FName = Grid->Columns->Items[Idx]->FieldName;
	if (MemTableEh31->FieldByName(FName)->IsNull) {
		switch (Idx) {
			case 32:	if (!MemTableEh31->FieldByName("TRANS_TIME_ADD")->IsNull)
							GDataOrders.AddCurParam(ftDateTime,FName,MemTableEh31->FieldByName("TIME_BEF")->Value);
						break;
			case 34: if (!MemTableEh31->FieldByName("TRANS_TIME_MIN")->IsNull)
							GDataOrders.AddCurParam(ftDateTime,FName,MemTableEh31->FieldByName("TIME_WRK")->AsDateTime);
						break;
			case 39: if (!MemTableEh31->FieldByName("TRANS_DIST_TAX")->IsNull)
							GDataOrders.AddCurParam(ftInteger,FName,MemTableEh31->FieldByName("DIST_TAX")->AsInteger);
						break;
			case 40: if (!MemTableEh31->FieldByName("TRANS_HOUR_TAX")->IsNull)
							GDataOrders.AddCurParam(ftInteger,FName,MemTableEh31->FieldByName("HOUR_TAX")->AsInteger);
						break;
			case 43: if (!MemTableEh31->FieldByName("PAY_CALC")->IsNull)
							GDataOrders.AddCurParam(ftInteger,FName,MemTableEh31->FieldByName("PAY_CALC")->AsInteger);
						break;
		}
	}
	WriteDataStd(GDataOrders,false);
*/
}
//---------------------------------------------------------------------------
TsCheckBox* __fastcall TFormTrans::GetCurrentCBox()
{
	int Col = DBGridEh31->Col;
	TsCheckBox* CBox = NULL;
	if      (Col > 0   && Col  <  3) CBox = sCheckBox1;  // N и дата приема
	if      (Col == 14 || Col == 15) CBox = sCheckBox2;  // Контакт
	else if (Col == 16 || Col == 17) CBox = sCheckBox3;  // Заказ транспорта
	else if (Col >= 25 && Col < 29)  CBox = sCheckBox3;  // Транспорт
	else if (Col >= 18 && Col < 25)  CBox = sCheckBox5;  // Адреса
	else if (Col >= 29 && Col < 32)  CBox = sCheckBox4;  // Водителя
//	else if (Col >= 33 && Col < 39)  CBox = sCheckBox6;  // Время
	else if (Col >= 32 && Col < 40)  CBox = sCheckBox7;  // расчет
	else if (Col >= 40 && Col < 47)  CBox = sCheckBox8;  // Оплаты
	else if (Col >= 47 && Col < 52)  CBox = sCheckBox9;  // Выплаты
	else if (Col >= 52)              CBox = sCheckBox10; // Прочее
	return CBox;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ShowNeighbours(TDBGridEh* Grid)  // Ctrl\N
{
	TDBGridColumnsEh* Columns = Grid->Columns;

	int Col           = Grid->Col;
	TColumnEh* Column = Columns->Items[Col-1];
	AnsiString Title  = Column->Title->Caption;
	bool ClearView = false;
	if (Title.Pos("|")) {
		Title = GetPiece(Title, "|",1);
		int Cnt = Columns->Count;
		for (int i = Col; i < Cnt; i++) {
			Column = Columns->Items[i];
			if (Column->Title->Caption.Pos(Title) != 1) break;
			if (!Column->Visible) {
			  Column->Visible = true;
			  ClearView = true;
			}
		}
		for (int i = Col - 2; i >= 0; i--) {
			Column = Columns->Items[i];
			if (Column->Title->Caption.Pos(Title) != 1) break;
			if (!Column->Visible) {
			  Column->Visible = true;
			  ClearView = true;
			}
		}
	}
	if (ClearView)	ClearSelView();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ShowNextColumn(TDBGridEh* Grid,int Shift) // Ctrl + {->, <-}
{
	int Cnt = Grid->Columns->Count;
	int Col = Grid->Col;
	int Nxt = Col + Shift;
	if (Nxt > Cnt) return;
	Nxt--;
	if (Nxt < 0) Nxt = 0;
	if (!Grid->Columns->Items[Nxt]->Visible) {
		Grid->Columns->Items[Nxt]->Visible = true;
		if (Shift <0)
		   Grid->Col = Nxt+1;
		ClearSelView();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::HideCurColumnGroup(TDBGridEh* Grid) // Ctrl\B
{
	int Col = DBGridEh31->Col - 1;
	TsCheckBox* CBox = GetCurrentCBox();
	if (CBox) {
		if (!CBox->Checked) {
			CBox->OnClick = NULL;
			CBox->Checked = true;
			CBox->OnClick = sCheckBoxClick;
		}
		CBox->Checked = false;
	}
	for (int i = Col; i > 0; i--) {
		if (Grid->Columns->Items[i]->Visible) {
			Grid->Col = i+1;
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ShowCurColumnGroup(TDBGridEh* Grid)// Ctrl\V
{
	TsCheckBox* CBox = GetCurrentCBox();
	if (CBox) {
		if (CBox->Checked) {
			CBox->OnClick = NULL;
			CBox->Checked = false;
			CBox->OnClick = sCheckBoxClick;
		}
		CBox->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::HideCurrentColumn(TDBGridEh* Grid) // Ctrl\X
{
	int Cnt = Grid->Columns->Count;
	int Col = Grid->Col;
	if (Col > 2 && Col <= Grid->FrozenCols) return;
	ClearSelView();
	TDBGridColumnsEh* Columns = Grid->Columns;
	Columns->Items[Col-1]->Visible = false;
	for (int i = Col; i < Cnt; i++) {
		if (Columns->Items[i]->Visible) {
			Grid->Col = i+1;
			return;
		}
	}
	for (int i = Col - 2; i >= 0; i--) {
		if (Columns->Items[i]->Visible) {
			Grid->Col = i+1;
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ShowAllColumns(TDBGridEh* Grid, bool Show)  // Ctrl\A
{
	int Cnt = Grid->Columns->Count;
	TDBGridColumnsEh* Columns = Grid->Columns;
	bool ClearView = false;
	for (int i = 0; i < Cnt; i++) {
		TColumnEh* Column = Columns->Items[i];
		if (Column->Visible != Show) {
			if (i < 2 || i >= Grid->FrozenCols) {
			  ClearView = true;
			  Column->Visible = Show;
         }
		}
	}
	if (ClearView) ClearSelView();
//	Grid->FrozenCols = MaxFrozenCols;
	TsCheckBox* CBoxes[] = { sCheckBox1, sCheckBox2, sCheckBox3, sCheckBox4, sCheckBox5,
									 sCheckBox7, sCheckBox8, sCheckBox9,  sCheckBox10};
	Cnt = sizeof(CBoxes)/sizeof(TsCheckBox*);

	for (int i = 0; i < Cnt; i++) {
		TsCheckBox* CBox = CBoxes[i];
		CBox->OnClick = NULL;
		CBox->Checked = Show;
		CBox->OnClick = sCheckBoxClick;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SwapEmplRightBit()
{
	GetGridColParam(GDataEmployee,true);
	int EditCol = GDataEmployee.EditCol;
	if (EditCol < 4) return;
	int EmplRights = GDataEmployee.WrkDSet->FieldByName("EMPL_RIGHTS")->AsInteger;
	int Mask = 1 << (EditCol - 4);
	if (EmplRights & Mask) EmplRights -= Mask;
	else                   EmplRights += Mask;
	GDataEmployee.AddCurParam(ftInteger,"EMPL_RIGHTS",EmplRights);
	WriteDataStd(GDataEmployee,false);
}

//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhDblClick(TObject *Sender)
{
	switch (GetComponentTag(Sender)) {
		case 41: if (WrkGData->WrkGrid->Col == 6) ChangeDriver();
					else ChangeTransport();
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhEnter(TObject *Sender)
{
	WrkGData = &GetGDataRef(Sender);
	RestoreMultiFlag();
//	RestoreEditMultiFlag();
	SetStatusBarStd(*WrkGData);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhExit(TObject *Sender)
{
	int Cnt = sStatusBar1->Panels->Count;
	for (int i=0; i < Cnt; i++)
		sStatusBar1->Panels->Items[i]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sCheckBoxClick(TObject *Sender)
{
	TsCheckBox* Cbox = dynamic_cast<TsCheckBox*>(Sender);
	TDBGridEh* Grid  = DBGridEh31;
	TDBGridColumnsEh* Columns= Grid->Columns;
	bool En = Cbox->Checked;
	int nBeg = 0, nEnd = 0;
	bool ClearView = false;
	switch (Cbox->Tag) {
		case  1: nBeg = 0;  nEnd =  2; break;
		case  2: nBeg = 13;  nEnd = 15; break;        			// Контакт
		case  3: if (Columns->Items[15]->Visible != En) {
						Columns->Items[15]->Visible = En;
						ClearView = true;
					}
	  			if (Columns->Items[16]->Visible != En) {
						Columns->Items[16]->Visible = En;
						ClearView = true;
					}
					nBeg = 24; nEnd = 28; break;               // Транспорт
		case 	4: nBeg = 28; nEnd = 31; break;               // Водителя
		case  5: nBeg = 17; nEnd = 24; break;               // Адреcа
//		case  6: nBeg = 32; nEnd = 38; break;               // Время
		case  7: nBeg = 31; nEnd = 39; break;               // Расчет
		case  8: nBeg = 39; nEnd = 46; break;               // Оплата
		case  9: nBeg = 46; nEnd = 51; break;               // Выплаты
		case 10: nBeg = 51; nEnd = Columns->Count; break;
	}
	for (int i = nBeg; i < nEnd; i++) {
		if (Columns->Items[i]->Visible != En) {
			Columns->Items[i]->Visible = En;
			ClearView = true;
		}
	}
	if (ClearView) ClearSelView();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ToggleOrdersEditMode(bool Set)
{
	if (Set)
		 GDataOrders.Flags &= ~UPDATE_ONLY_CURRENT;
	else
		 GDataOrders.Flags |= UPDATE_ONLY_CURRENT;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ToggleShowCost(bool Show)
{
	 TDBGridColumnsEh* Columns = DBGridEh31->Columns;
	 AnsiString DF = "###0";
	 if (Show) DF += ".00";
	 Columns->Items[37]->DisplayFormat = DF;   // расчетная
	 Columns->Items[38]->DisplayFormat = DF;   // Итогоая
	 Columns->Items[43]->DisplayFormat = DF;   // Доплатить
	 Columns->Items[51]->DisplayFormat = DF;   // прибыль
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ToggleShowSelected (GridData& GData)
{
	if (GData.Flags & SHOW_SELECTED) GData.Flags &= ~SHOW_SELECTED;
	else 										GData.Flags |= SHOW_SELECTED;
	PulseFilterStd(GData);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sCheckBoxAddClick(TObject *Sender)
{
	 switch (GetComponentTag(Sender)) {
		 case 51: ToggleShowSelected(GDataOutlay);
					 break;
		 case 20: ToggleShowSelected(GDataOrders);
					 break;
		 case 21: ToggleOrdersEditMode(sCheckBox21->Checked);
					 break;
		 case 22: ToggleShowCost(sCheckBox22->Checked);
					 break;
		 case 41: PulseFilterStd(GDataGraph);
					 break;
		 case 42: DBGridEh41->Repaint();
					 break;

	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::CloseRowDetailPanel()
{
	TRowDetailPanelEh* RDPanel = NULL;
	if (PageTag == 3) RDPanel = DBGridEh31->RowDetailPanel;
	if (!RDPanel) return;
	if (RDPanel->Visible) {
		if (RDPWCtrl) DetailEditChanged(RDPWCtrl);
		RDPWCtrl = NULL;
		RDPanel->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sSpeedButtonClick(TObject *Sender)
{
	 CloseRowDetailPanel();
	 WriteMemo();
	 switch (GetComponentTag(Sender)) {
		  case  1:	ProcRefreshPage();        			break;
		  case  2: 	ProcDeleteStd(*WrkGData); 			break;
		  case  3: 	ProcInsertStd(*WrkGData); 			break;
		  case  4: 	ProcSelAllStd(*WrkGData, NULL);	break;
		  case  5:  ClearSums();
						ProcUnsAllStd(*WrkGData, NULL);
						break;
		  case  6:  PrintGrid();        					break;
		  case  7:  ProcHistory(false);              break;
		  case  8:  if (PageTag == 3)	ProcFilter();
						else 				   ProcFilterStd(*WrkGData);
						break;
		  case  9:	SaveCurrentView();  					break;
		  case 10:  CopyOrder();                     break;

		  case 11:  ShowOrders(DT_Beg_Ord - 1);      break;
		  case 12:  ShowOrders(Date() - 1);          break;
		  case 13:  ShowOrders(Date());              break;
		  case 14:  ShowOrders(Date()+1);            break;
		  case 15:  ShowOrders(DT_Beg_Ord + 1);      break;
		  case 16:  FindOrder();                     break;
		  case 17:  DublicateOrder();                break;

		  case 18:  ShowNextColumn(DBGridEh31,-1);
						DBGridEh31->Col = max(DBGridEh31->Col-1,1);
						break;
		  case 19:  HideCurrentColumn(DBGridEh31);  			break;
		  case 20:  HideCurColumnGroup (DBGridEh31);		  	break;
		  case 21:  ShowNextColumn(DBGridEh31, 1);
						DBGridEh31->Col = min(DBGridEh31->Col+1,DBGridEh31->Columns->Count);
						break;

		  case 22:  ShowNeighbours(DBGridEh31);		  		break;
		  case 23:  ShowCurColumnGroup(DBGridEh31);		   break;
		  case 24:  ShowAllColumns(DBGridEh31,true);	   	break;
		  case 25:  ShowAllColumns(DBGridEh31,false);    	break;
		  case 35:  GoToCurrentOrder();                    break;

		  case 41:  MoveGraphDay(-1);   					break;
		  case 42:  MoveGraphDay(1);    					break;
		  case 43:  ClearGraphDate();    				break;
		  case 44:  EditDriverGraph();					break;
		  case 45:  GoToCurrentOrder();              break;
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::GoToCurrentOrder()
{
	int OrdersID =  0;
	TDateTime DT_Beg;
	switch (PageTag) {
		case 3:  OrdersID = MemTableEh31->FieldByName("ORDERS_ID")->AsInteger;
					if (OrdersID) {
						TDateTime DT    = TDateTime(GetDateStr(MemTableEh31->FieldByName("DT_BEG")->AsDateTime));
						int TransportID = MemTableEh31->FieldByName("TRANSPORT_ID")->AsInteger;
						sPageControl1->ActivePage = sTabSheet4;
						ChangePage();
						MoveGraphDay(DT-DT_Graph);
						if (TransportID) {
							if (MemTableEh41->Locate("GRAPH_ID", TransportID, TLocateOptions()) ) {
								DBGridEh41->RowDetailPanel->Visible = true;
								MemTableEh43->Locate("GRAPH_ID",-OrdersID,TLocateOptions());
							}
						}
						else MemTableEh41->Locate("GRAPH_ID",-OrdersID,TLocateOptions());
						AfterScrollStd(*WrkGData);
					}
					break;
		case 4:	if (DBGridEh41->RowDetailPanel->Visible && DBGridEh43->Focused()) {
						OrdersID = MemTableEh43->FieldByName("ORDERS_ID")->AsInteger;
						DT_Beg   = MemTableEh43->FieldByName("DT_BEG")->AsDateTime;
					}
					else if (MemTableEh41->FieldByName("FLAG_KIND")->AsInteger) {
						OrdersID = MemTableEh41->FieldByName("ORDERS_ID")->AsInteger;
						DT_Beg   = MemTableEh41->FieldByName("DT_BEG")->AsDateTime;
					}
					else {
						int Col     = DBGridEh41->Col - DBGridEh41->FrozenCols - 1;
						if (Col < 0) return;
						int MinBeg  = Col * 60;               // сдвиг в мин от начала диапазона
						int MinEnd  = MinBeg  + 60;
						int GraphID = MemTableEh41->FieldByName(GDataGraph.FieldKey)->AsInteger;
						std::map<int, Vect>::iterator iterTrans = TransWork.find(GraphID);
						if (iterTrans != TransWork.end()) {
							std::vector<int> vect = iterTrans->second;
							std::vector<int>::iterator iter = vect.begin();
							int size = vect.size();
							for (int i=0; i < size; i+=5 ) {
								int O_ID = -*iter++;
								int X1   =  *iter++;		// минуты
								int X2   =  *iter++;    // минуты
								iter++;   // пропускаем водителя
								iter++;    //  состояние
								if (X1 < MinEnd && X2 > MinBeg ) {                      	// если текущая ячейка перемекается с зоной заказа
									if (OrdersID) {
										return;
									}
									OrdersID = O_ID;
								}
							}
						}
					}
					if (OrdersID > 0) {
						sPageControl1->ActivePage = sTabSheet3;
						ChangePage();
						if (!MemTableEh31->Locate("ORDERS_ID",OrdersID, TLocateOptions())) {
							if (DT_Beg > TDateTime("1.1.15"))
								ShowOrders(DT_Beg);
							if (!MemTableEh31->Locate("ORDERS_ID",OrdersID, TLocateOptions())) {
								FindOrder(OrdersID);
								if (MemTableEh31->FieldByName("ORDERS_ID")->AsInteger != OrdersID) {
									OutputMessage("Не удалось найти заказ " + IntToStr(OrdersID));
								}
							}
						}
						AfterScrollStd(*WrkGData);
					 }
					 break;

	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::EditDriverGraph()
{
	AnsiString S;
	if (MemTableEh41->FieldByName("GRAPH_ID")->AsInteger > 0) S = MemTableEh41->FieldByName("DRIVER_NAME")->AsString;
	TFormDriverGraph* Frm  = new TFormDriverGraph(this, MemTableEh41->FieldByName("TRANS_DRIVER_ID")->AsInteger, S);
	Frm->ShowModal();
	delete Frm;
	ProcRefreshStd(GDataGraph,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearGraphDate()
{
	TDateTime DT = sDateEdit3->Date;
	if (DT <= Date()) {
		OutputMessage("Можно удалить все заказы из графика\n"
						  "только, начиная с завтрашнего дня.");
		return;
	}
	if (!AskQuestionStd("Удалить все заказы из графика на " + GetDateStr(DT)) ) {
		return;
	}
	Variant V;
	AnsiString SQL = "select * from REMOVE_ORDERS_FROM_GRAPH('"+ GetDateStr(DT) + "'," +
							IntToStr(DModT->CurEmpID)  + ",'"  + DModT->ComputerName        + "')";
	if (OpenTmpQuery(SQL,"Cnt",V,DModT->Database1)) {
		int X = V;
		OutputMessage("Числ удаленных заказов из графика: "+IntToStr(X));
	}
	ProcRefreshStd(*WrkGData,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::FindOrder()
{
	int OrdersID = 0;
	if (InputInteger("Поиск заказа","Номер заказа",OrdersID)) FindOrder(OrdersID);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::FindOrder(int OrdersID)
{
	std::map<AnsiString,Variant> Result;
	if (OpenTmpQuery("select count(*) as CNT,max(DT_Beg) as DT from orders where orders_id = "+IntToStr(OrdersID),
						  "CNT;DT",Result,DModT->Database1)) {
		std::map<AnsiString,Variant>::iterator iter = Result.find("CNT");
		if (iter != Result.end()) {
			if (iter->second > 0) {
				iter = Result.find("DT");
				if (iter != Result.end()) {
					TDateTime DT = TDateTime(GetDateStr(iter->second));
					GDataOrders.KeyValue = OrdersID;
					ShowOrders(DT);
					MemTableEh31->Locate("ORDERS_ID", OrdersID, TLocateOptions());
					AfterScrollStd(*WrkGData);

				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DublicateOrder()
{
	int OrderID = MemTableEh31->FieldByName("ORDERS_ID")->AsInteger;
	if (!OrderID) return;
	int NCopy = 1;
	if (!InputInteger("Дублировать заказ","Кол-во копий (1-10)",NCopy)) return;
	if (!NCopy) return;
	AnsiString SQL = "select * from Copy_Order(" + IntToStr(OrderID) + ",'" +
							  GetDateStr(MemTableEh31->FieldByName("DT_BEG")->AsDateTime) + "'," +
							  IntToStr(NCopy) + "," + IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "')";
	Variant Result;
	if (OpenTmpQuery(SQL,"RESULT",Result,DModT->Database1)) {
		if (Result <=0 ) {
			OutputMessage("Ошибка копирования заказа " + IntToStr(OrderID) +
							  ". Код :" + IntToStr((int)Result));
			return;
		}
	}
	if (AskQuestionStd("Показать скопированные заказы ?"))
		ShowCopiedOrders(OrderID);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::CopyOrder()
{
	int OrderID = MemTableEh31->FieldByName("ORDERS_ID")->AsInteger;
	if (!OrderID) return;

	TFormOrderCopy* Frm = new TFormOrderCopy(this,OrderID);
	Frm->ShowModal();
	int NCopy = Frm->NCopy;
	delete Frm;
	if (NCopy && AskQuestionStd("Показать скопированные заказы ?"))
		ShowCopiedOrders(OrderID);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ShowCopiedOrders(int OrderID)
{
	TDateTime DTB = Date();
	TDateTime DTE = Date()+1;
	TDateTime DTM = TDateTime(GetDateStr(MemTableEh31->FieldByName("DT_Make")->AsDateTime));

	if (DTM < DTB) DTB = DTM;

	OrderFilter.clear();

	FilterRows Empty;
	OrderFilter.push_back(Empty);
	OrderFilter.push_back(Empty);

	FieldFilter FF;
	FF.EqvValue = MemTableEh31->FieldByName("ORDERS_ID")->AsInteger;

	vector<FieldFilter> FieldFilterSet;
	FieldFilterSet.push_back(FF);

	OrderFilter[0].insert(pair<AnsiString,vector<FieldFilter> >("ORDERS_ID",FieldFilterSet));

	OrderFilter[1].insert(pair<AnsiString,vector<FieldFilter> >("SRC_ORDER_ID",FieldFilterSet));
	sComboBox1->ItemIndex = SelIndex   = 0;
	sDateEdit1->Date      = DT_Beg_Ord = DTB;
	sDateEdit2->Date      = DT_End_Ord = DTE;
	sComboEdit2->Text     = "Копии заказа N " + IntToStr(OrderID);
	ProcRefreshPage();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ShowOrders(TDateTime DT)
{
	 bool RefreshPage = false;
	 if (SelIndex != 1) {
		 RefreshPage = true;
		 SelIndex = 1;
		 sComboBox1->ItemIndex = 1;
	 }
	 if (DT_Beg_Ord != DT) {
		 RefreshPage = true;
		 DT_Beg_Ord = DT;
		 sDateEdit1->Date = DT;
	 }
	 ++DT;
	 if (DT_End_Ord != DT) {
		 RefreshPage = true;
		 DT_End_Ord = DT;
		 sDateEdit2->Date = DT;
	 }
	 if (RefreshPage) {
		 ProcUnsAllStd(GDataOrders, NULL);
		 ProcRefreshStd(GDataOrders, true);

	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::PrintGrid()
{
	TDBGridEh* Grid = WrkGData->WrkGrid;
	PrintDBGridEh1->DBGridEh = Grid;
	PrintDBGridEh1->Preview();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::CheckRecordByFilter()
{
	bool ClearStdFilter = !FilterRecordStd(*WrkGData);
	bool ClearSpcFilter = false;
	bool ChangeSelCond  = false;
	switch (PageTag) {
		case 3: ClearSpcFilter = !CheckOrderFilter();
				  if (!MemTableEh31->FieldByName("ORDERS_ID")->IsNull)
					  ChangeSelCond  = RecordNotInSelectCondition();
				  break;
	}
	if (ClearStdFilter || ClearSpcFilter || ChangeSelCond) {
		if (AskQuestionStd("Текущая запись не удовлетворяет условиям фильтра\n"
								 "и после обновления набора данных не будет видна.\n"
								 "Отменить фильтр и\или изменить условия выборки ?")) {

			if (ClearStdFilter) WrkGData->Filter = "";
			if (ClearSpcFilter) {
				OrderFilter.clear();
				sComboEdit2->Text = "Не выбран";
			}
			if (ChangeSelCond) {
				if (MemTableEh31->FieldByName("DT_BEG")->IsNull) {
					TDateTime DT = TDateTime(GetDateStr(MemTableEh31->FieldByName("DT_MAKE")->AsDateTime));
					sComboBox1->ItemIndex = SelIndex = 0;
					DT_Beg_Ord = DT;       sDateEdit1->Date = DT_Beg_Ord; // ?? НА 1 ДЕНЬ
					DT_End_Ord = DT + 1;   sDateEdit2->Date = DT_End_Ord;
				}
				else {
					TDateTime DT = TDateTime(GetDateStr(MemTableEh31->FieldByName("DT_BEG")->AsDateTime));
					sComboBox1->ItemIndex = SelIndex = 1;
					DT_Beg_Ord = DT;       sDateEdit1->Date = DT_Beg_Ord; // ?? НА 1 ДЕНЬ
					DT_End_Ord = DT + 1;   sDateEdit2->Date = DT_End_Ord;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ProcRefreshPage()
{
//	CheckRecordByFilter();
	switch(PageTag) {
		case 1:	ProcRefreshStd(GDataTransComp,true);
					ProcRefreshStd(GDataTransType,true);
					ProcRefreshStd(GDataTransport,true);
					break;
		case 2:  SavePosStd(GDataContact);
					SavePosStd(GDataClientTax);
					MemTableEh22->Active = false;
					ProcRefreshStd(GDataClient,true);
					ProcRefreshStd(GDataContact,true);
					ProcRefreshStd(GDataClientTax,false);
					break;
		case 3:  CloseRowDetailPanel();
		         ProcUnsAllStd(GDataOrders, NULL);
					ProcRefreshStd(GDataOrders,true);
					break;
		case 4:  ProcRefreshStd(GDataGraph,true);
					break;
		case 5: 	ProcRefreshStd(GDataOutlay,true);
					break;
		case 6:  SavePosStd(GDataStreet);
					MemTableEh62->Active = false;
					ProcRefreshStd(GDataTown,true);
					ProcRefreshStd(GDataStreet,true);
					ProcRefreshStd(GDataDriver,true);
					break;
		case 7: 	ProcRefreshStd(GDataEmployee,true);
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SaveCurrentView()
{
	SelCurrentView(true);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::MoveGraphDay(int Shift)
{
	DT_Graph += Shift;
	sDateEdit3->Date = DT_Graph;
	ShowTransVect.clear();
	CreateGraphColumns();
	SetGraphLabels();
	ProcRefreshStd(GDataGraph,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ProcFilter()
{
	 if (GetFilter(OrderFilter,DBGridEh31,SelFilterID,FilterName)) {
		 sComboEdit2->Text = FilterName;
		 PulseFilterStd(GDataOrders);
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sDateEditAcceptDate(TObject *Sender, TDateTime &aDate,
			 bool &CanAccept)
{
	 int Shift = 0;

	 switch (GetComponentTag(Sender)) {
		 case 1: Shift = aDate - DT_Beg_Ord;
					if (Shift) {
						 DT_Beg_Ord = aDate;
						 if (DT_Beg_Ord >= DT_End_Ord) {
							 sDateEdit2->Date = DT_End_Ord = DT_Beg_Ord + 1;
						 }
					}
					break;
		 case 2: Shift =  DT_End_Ord - aDate;
					if (Shift) {
						DT_End_Ord = aDate;
						 if (DT_Beg_Ord >= DT_End_Ord) {
							 sDateEdit1->Date = DT_Beg_Ord = DT_End_Ord - 1;
						 }
					}
					break;
		 case 3: //Ref = (DT_Beg_Grp != aDate);
					Shift = DT_Graph - aDate;
					if (Shift) {
						DT_Graph = aDate;
						SetGraphLabels();
						CreateGraphColumns();
					}
					break;
		 case 5: Shift = DT_Beg_Exp - aDate;
					if (Shift) {
						DT_Beg_Exp = aDate;
						if (DT_Beg_Exp > DT_End_Exp) {
							sDateEdit6->Date = DT_End_Exp = DT_Beg_Exp;
						}
					}
					break;
		 case 6: Shift = DT_End_Exp - aDate;
					if (Shift) {
						DT_End_Exp = aDate;
						if (DT_Beg_Exp > DT_End_Exp) {
							sDateEdit5->Date = DT_Beg_Exp = DT_End_Exp;
						}
					}
					break;
	 }
	 if (Shift) {
		 ProcRefreshPage();
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key) {
		case VK_ESCAPE: sComboBox1->ItemIndex   = SelIndex;
		case VK_RETURN: sComboBox1->DroppedDown = false;   break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sComboBox1CloseUp(TObject *Sender)
{
	if (sComboBox1->ItemIndex != SelIndex) {
		SelIndex = sComboBox1->ItemIndex;
		ProcRefreshPage();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBDateTimeEditEhChange(TObject *Sender)
{
  if (PageTag == 4 ) {
	  Timer1->Enabled = false;
	  Timer1->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false;
	TWinControl* WCtrl = ActiveControl;
	DBGridEh41->SetFocus();
	TDateTime DT1 = DBDateTimeEditEh1->Value;
	TDateTime DT2 = DBDateTimeEditEh2->Value;
	if (TM_Beg_Grp.FormatString("h") != DT1.FormatString("h") || TM_End_Grp.FormatString("h") != DT2.FormatString("h")) {
		TM_Beg_Grp = DT1;
		TM_End_Grp = DT2;
		CreateGraphColumns();
		ProcRefreshStd(GDataGraph,true);
	}
	WCtrl->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sComboEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch(Key) {
		case VK_BACK:	switch (GetComponentTag(Sender)) {
								case 1:	ClearSelView(); break;
								case 2:  ClearFilter();  break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearSelView()
{
	if (SelViewID) {
		SelViewID = 0; sComboEdit1->Text = "Не выбран";
		sSpeedButton6->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearFilter()
{
	if (OrderFilter.size()) {
		OrderFilter.clear();
		sComboEdit2->Text = "Не выбран";
		PulseFilterStd(GDataOrders);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sComboEditButtonClick(TObject *Sender)
{
	 switch(GetComponentTag(Sender)) {
		 case 1:	SelCurrentView(false);	break;
		 case 2: ProcFilter();           break;
	 }

}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::SelCurrentView(bool SaveCurState)
{
	 bool bRes = false;
	 AnsiString S,Params,ResWdt;
	 Params = IntToStr(Screen->Width) + "," + IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	 if (SimpleSelSpecViewID(this, Left + sComboEdit1->Left + sComboEdit1->Width + 5, SelViewID, &S,&ResWdt,Params)) {
		 sComboEdit1->Text = S;
		 sSpeedButton6->Enabled = false;
		 ProcResultViewWidth(ResWdt, SaveCurState);
		 bRes = true;
	 }
	 return bRes;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SaveViewWidth()
{
	Variant Result;
	AnsiString SQL = "select count(*) from Spec_View where Spec_View_id = "+ IntToStr(SelViewID) +
						 " and Employee_ID = " + IntToStr(DModT->CurEmpID);
	if (OpenTmpQuery(SQL,"COUNT",Result,DModT->Database1)) {
		if (Result != 1) {
			OutputMessage("Этот вид принаджежит не Вам./\n"
							  "Вы не можете его изменять.");
			ClearSelView();
			return;
		}
	}
	AnsiString WdtList = GetCurColWidtList();
	SQL = "update Spec_View set Col_Wdt = '" + WdtList + "'," +
			"User_id = "    + IntToStr(DModT->CurEmpID)  + ","  +
			"Comp_Name = '" + DModT->ComputerName        + "'," +
			"DateChange = 'now' where Spec_View_ID = "   + IntToStr(SelViewID);
	ExecuteQry(SQL,DModT->Database1,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ProcResultViewWidth(AnsiString& WdtList,bool SaveCurState)
{
	TDBGridEh* Grid = DBGridEh31;
	int Cnt = Grid->Columns->Count;

	if (WdtList == "" || SaveCurState) {
		if (WdtList != "") {
			if (!AskQuestionStd("Сохранить текущее состояние просмотра как вид\n '"+sComboEdit1->Text+"'?")) {
				ClearSelView();
				return;
			}
		}
		SaveViewWidth();
	}
	else {
		for (int i = 0; i < Cnt; i++) {
			AnsiString S = GetPiece(WdtList,",",i+1);
			if (S == "") {
				Grid->Columns->Items[i]->Visible = false;
			}
			else {
				Grid->Columns->Items[i]->Visible = true;
				int DefWdt = StrToInt(GetPiece(DefColWidth,",",i+1));
				Grid->Columns->Items[i]->Width   = StrToIntDef(S,DefWdt);
			}
		}
	}
}
//---------------------------------------------------------------------------
namespace XXX {
using Gridseh::TGridCoord;
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhColumnsDataHintShow(TCustomDBGridEh *Sender,
			 TPoint &CursorPos, TGridCoord &Cell, TPoint &InCellCursorPos,
			 TColumnEh *Column, TDBGridEhDataHintParams *&Params, bool &Processed)

{
	int Col = (int)Cell.X;
	int Row = (int)Cell.Y;
	if (Col > DBGridEh41->FrozenCols && Row >=0) {
		AnsiString Hint = GetHintStrByPoint(Col,Row,Column,InCellCursorPos);
		if (Hint == "") {
			Hint = GetHintStrByPointInDrawData(Col,Row,Column,InCellCursorPos);
		}
		if (Hint != "") {
			Params->HideTimeout = 5000;
			Params->HintStr = Hint;
			Processed = true;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhCellMouseClick(TCustomGridEh *Grid, TGridCoord &Cell,
			 TMouseButton Button, TShiftState Shift, int X, int Y, bool &Processed)

{
	if (Shift.Contains(ssShift)) {
		int Col = DBGridEh41->Col;
		int Row = DBGridEh41->Row;
		TColumnEh *Column = DBGridEh41->Columns->Items[Col-1];
		TPoint Point = TPoint(X,10);
		AnsiString Hint = GetHintStrByPoint(Col,Row,Column,Point);
		if (Hint == "") {
			Hint = GetHintStrByPointInDrawData(Col,Row,Column,Point);
		}
		if (Hint != "") {
			OutputMessage(Hint);
		}
	}
	Processed = true;
}
};
//---------------------------------------------------------------------------
AnsiString __fastcall TFormTrans::GetHintStrByPoint(int Col,int Row,TColumnEh *Column,TPoint &InCellCursorPos)
{
	AnsiString Hint;
	Col = Col - DBGridEh41->FrozenCols - 1;
	int GraphID = MemTableEh41->FieldByName(GDataGraph.FieldKey)->AsInteger;
	std::map<int, Vect>::iterator iterTrans = TransWork.find(GraphID);

	if (iterTrans != TransWork.end()) {
		std::vector<int> vect = iterTrans->second;
		std::vector<int>::iterator iter = vect.begin();
		int size = vect.size();
		for (int i=0; i < size; i+=5 ) {
			int O_ID = -*iter++;
			int X1   =  *iter++;		// минуты
			int X2   =  *iter++;    // минуты
			iter++;   // пропускаем водителя
			iter++;    //  состояние
			int MouseMin = Col*60 + InCellCursorPos.X*60/Column->Width;
			if (X1 < MouseMin && X2 > MouseMin ) {                      	// если текущая ячейка перемекается с зоной заказа
				std::map<int,AnsiString>::iterator iterHint = GraphHint.find(O_ID);
				if (iterHint != GraphHint.end()) {
					if (Hint != "") Hint += "\n\n";
					Hint += iterHint->second;
				}
			}
		}
	}
	return Hint;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormTrans::GetHintStrByPointInDrawData(int Col,int Row,TColumnEh *Column,TPoint &InCellCursorPos)
{
	AnsiString Hint;
	Hint = GetDrawDataHint(SData,Col,Column,InCellCursorPos);
	AnsiString Hint2;
	for (std::map<int,DrawData>::iterator iter = DrawMap.begin(); iter != DrawMap.end(); ++iter) {
		DrawData& DD = iter->second;
		AnsiString H = GetDrawDataHint(DD,Col,Column,InCellCursorPos);
		if (H != "" && H != Hint) {
			if (Hint2 != "") Hint2 += "\n\n";
			Hint2 += H;
		}
	}
	if (Hint == "") Hint = Hint2;
	else {
		if (Hint2 != "") {
			Hint += "\n\n" + Hint2;
		}
   }
	return Hint;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormTrans::GetDrawDataHint(DrawData& DD, int Col,TColumnEh *Column,TPoint &InCellCursorPos)
{
	Col = Col - DBGridEh41->FrozenCols - 1;
	int TimeWrk  = DD.TimeWrk;
	AnsiString Hint;
	if (TimeWrk) {
		TDateTime DT_Beg_Ord = DD.DT_Beg_Ord;
		TDateTime TM_Beg_Ord = DD.TM_Beg_Ord;
//		int Days = TDateTime(GetDateStr(DT_Beg_Ord)) - DT_Beg_Grp;
		int Days = TDateTime(GetDateStr(DT_Beg_Ord)) - (DT_Graph - 1);

		int BegZone = Days*1440 +
				 StrToInt(TM_Beg_Ord.FormatString("h"))*60 + StrToInt(TM_Beg_Ord.FormatString("n")) -
				 StrToInt(TM_Beg_Grp.FormatString("h"))*60 - StrToInt(TM_Beg_Grp.FormatString("n"));
		int EndZone = BegZone + TimeWrk;
		int MouseMin = Col*60 + InCellCursorPos.X*60/Column->Width;
		if (BegZone < MouseMin && EndZone > MouseMin) {
			if (DD.Hint1 != "") Hint += DD.Hint1;
			if (DD.Hint2 != "") Hint += "\n" + DD.Hint2;
			if (DD.Hint3 != "") Hint += "\n" + DD.Hint3;
			if (DD.Hint4 != "") Hint += "\n" + DD.Hint4;
			if (DD.Hint5 != "") Hint += "\n" + DD.Hint5;
		}
	}
	return Hint;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEh31ApplyFilter(TObject *Sender)
{
	TDBGridEh* Grid = dynamic_cast<TDBGridEh*>(Sender);
	AnsiString f,f1,f2,f3,expr;

	for (int i=0; i<Grid->Columns->Count; i++) {
		expr = Grid->Columns->Items[i]->STFilter->ExpressionStr;
		if (expr.Length()==0) continue;
		f2 = expr.SubString(1,1); f3 = expr.SubString(1,2);
		if( i>=1 && f.Length()>0)  f = f + " and ";
		if (Grid->Columns->Items[i]->Field->DataType == ftString) {
			if (f2 == "=" || f2 == "<" || f3 == "in") f1 = " " + expr;
			else f1 = " like '%"+ expr + "%'";
		}
		else if (Grid->Columns->Items[i]->Field->DataType == ftDateTime) {
			if (f2 == "=" || f2 == ">" || f2 == "<" || f3 == "in") f1 = " " + expr;
			else f1 = "='"+expr+"'";
		}
		else {
			if (f2 == "=" || f2 == ">" || f2 == "<" || f3 == "in") f1 = " " + expr;
			else                                     f1 = " =" + expr;
		}
		f = f + Grid->Columns->Items[i]->FieldName + f1;
  }
  TDataSet* DSet = Grid->DataSource->DataSet;
  DSet->Filter = f;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch(Key) {
		case VK_ESCAPE: switch (PageTag) {
								 case 2: ShowMemoStd(GDataClient,  sMemo3); break;
								 case 3: ShowMemoStd(GDataOrders,  sMemo1); break;
							 }
							 break;
		case VK_RETURN: //WriteMemo();
	                   break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sMemoExit(TObject *Sender)
{
	WriteMemo();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::WriteMemo()
{
	switch (PageTag) {
		case 2:  WriteMemoStd(GDataClient,sMemo3); break;
		case 3:	WriteMemoStd(GDataOrders,sMemo1); break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhRowDetailPanelHide(TCustomDBGridEh *Sender,
			 bool &CanHide)
{
	switch (Sender->Tag) {
		case 31:	if (GDataOrders.CurParams) {
						if (GDataOrders.CurParams->Count)
							if (AskQuestionStd("Сохранить изменения в заказе ?"))
								SaveDetailPanel();
					 }
					 break;
		 case 41: MemTableEh43->Active = false;
					 WrkGData = &GDataGraph;
	 }
	 RowDetailPanelHideStd(*WrkGData);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DBGridEhRowDetailPanelShow(TCustomDBGridEh *Sender,
			 bool &CanShow)
{
	RowDetailPanelShowStd(*WrkGData);
	switch (Sender->Tag) {
		case 31: FillRowDetailPanel();
					break;
		case 41: ProcRefreshStd(GDataDetail,true);
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearDetailParam(AnsiString FName)
{
	if (!GDataOrders.CurParams)  return;
	TParam* Param = GDataOrders.CurParams->FindParam(FName);
	if (Param) GDataOrders.CurParams->RemoveParam(Param);

	AnsiString FNameT = TranslateName(FName);
	Param = GDataOrders.CurParams->FindParam(FNameT);
	if (Param) GDataOrders.CurParams->RemoveParam(Param);
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::FillDetailEdit(TWinControl* WCtrl)
{
	int Tag = WCtrl->Tag;
	AnsiString FName = FNameVect[Tag-1];

	DetailEditCng[Tag - 1] = 0;
	ClearDetailParam(FName);
	SetDetailEditColor(WCtrl,clWindow);

	TsComboEdit* CEdit = dynamic_cast<TsComboEdit*>(WCtrl);
	if (CEdit) {
		CEdit->Text  = MemTableEh31->FieldByName(FName)->AsString;
	}
	TsEdit* Edit = dynamic_cast<TsEdit*>(WCtrl);
	if (Edit) {
		AnsiString HdrList = GetPiece(FName,"|",2);
		if (HdrList == "") {
			Edit->Text  = MemTableEh31->FieldByName(FName)->AsString;
			return;
		}
		int i = 1;
		AnsiString FNameList = GetPiece(FName,"|",1);
		AnsiString Res;
		while (true) {
			FName = GetPiece(FNameList,";",i);
			if (FName == "") break;
			if (!MemTableEh31->FieldByName(FName)->IsNull) {
				Res += GetPiece(HdrList,";",i) + ": " + MemTableEh31->FieldByName(FName)->AsString + "    ";
			}
			++i;
		}
		Edit->Text = Res;
		return;
	}
	TsMemo* Memo = dynamic_cast<TsMemo*>(WCtrl);
	if (Memo) {
		Memo->Text  = MemTableEh31->FieldByName(FName)->AsString;
	}
	TDBNumberEditEh* NEdit = dynamic_cast<TDBNumberEditEh*>(WCtrl);
	if (NEdit) {
		NEdit->Value = MemTableEh31->FieldByName(FName)->AsVariant;
		return;
	}
	TDBDateTimeEditEh* DEdit = dynamic_cast<TDBDateTimeEditEh*>(WCtrl);
	if (DEdit) {
		if (DEdit->EditFormat == "HH:NN")
			DEdit->Value = MemTableEh31->FieldByName(FName)->AsDateTime;
		else
			DEdit->Value = MemTableEh31->FieldByName(FName)->AsVariant;
		return;
	}
	TComboBox* CBox = dynamic_cast<TComboBox*>(WCtrl);
	if (CBox) {
		CBox->ItemIndex = MemTableEh31->FieldByName(FName)->AsInteger;
		CBox->SelStart = 0;
		CBox->SelLength = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::FillRowDetailPanel()
{
	sComboEdit11->ReadOnly = false;
	sEdit5->ReadOnly       = false;
	for (std::vector<TWinControl*>::iterator iter = WCtrlVect.begin(); iter != WCtrlVect.end() ; ++iter) {
		FillDetailEdit(*iter);
//		TComboBox* CBox = dynamic_cast<TComboBox*>(*iter);
	}
	bool En = MemTableEh31->FieldByName("ORDER_FLAG")->AsInteger & EDIT_CONTACT_IS_ALLOWED;

	TsComboEdit* CEdit = dynamic_cast<TsComboEdit*>(WCtrlVect[0]);
	if (CEdit) {
	  CEdit->DirectInput = En;
	  CEdit->ShowButton  = !En;
	}
	AnsiString S = "Заказ N " + MemTableEh31->FieldByName("ORDERS_ID")->AsString +
						" принят " + MemTableEh31->FieldByName("DT_MAKE")->AsString;
	sLabel7->Caption = S;
	DetailEditCng.clear();
	DetailEditCng.insert (DetailEditCng.begin(), AllDetailCtrl,false);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetDetailStreetID(bool Beg, int &ID)
{
	int TownID = 0;
	AnsiString TownFName;
	if (Beg) TownFName = "BEG_TOWN_ID";
	else     TownFName = "END_TOWN_ID";
	TownID = MemTableEh31->FieldByName(TownFName)->AsInteger;
	TParam*    Param = NULL;
	if (GDataOrders.CurParams) Param = GDataOrders.CurParams->FindParam(TownFName);
	if (Param) TownID = Param->AsInteger;
	if (!TownID) return false;
	AnsiString Params = IntToStr(TownID) + "," + IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	return SimpleSelEhStreetID(this,0,ID,TownID,Params,&SelectResultStr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetDetailTransportID(int &ID)
{
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	int TransTypeID = 0;
	int TransCompID = MemTableEh31->FieldByName("Trans_Company_ID")->AsInteger;

	TParam*    Param = NULL;
	if (GDataOrders.CurParams) {
		 Param = GDataOrders.CurParams->FindParam("TRANS_COMPANY_ID");
		 if (Param) TransCompID = Param->AsInteger;
	}
	return SimpleSelEhTransportID(this,0,ID,TransTypeID, TransCompID, Params,&SelectResultStr);
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::GetDetailDriverID(int &ID)
{
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	int TransCompID = MemTableEh31->FieldByName("Trans_Company_ID")->AsInteger;

	TParam*    Param = NULL;
	if (GDataOrders.CurParams) {
		 Param = GDataOrders.CurParams->FindParam("TRANS_COMPANY_ID");
		 if (Param) TransCompID = Param->AsInteger;
	}
	return SimpleSelEhDriverID(this,0,ID,TransCompID, Params,&SelectResultStr);
}
//---------------------------------------------------------------------------
int __fastcall TFormTrans::GetCurrentID(TObject *Sender, int* BaseID)
{
	int ID;
	int Tag = GetComponentTag(Sender);
	int Idx = Tag - 1;
	AnsiString FName = FNameVect[Idx];
	AnsiString IName = TranslateName(FName);
	return GetCurrentID(IName, BaseID);
}
//---------------------------------------------------------------------------
int __fastcall TFormTrans::GetCurrentID(AnsiString IName, int* BaseID)
{
	int ID;
	TParam*    Param = NULL;
	if (GDataOrders.CurParams) Param = GDataOrders.CurParams->FindParam(IName);
	int                       IBase = MemTableEh31->FieldByName(IName)->AsInteger;

	if (Param)
		ID = Param->AsInteger;
	else
		ID = IBase;
	if (BaseID) *BaseID = IBase;
	return ID;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sComboEditDetailButtonClick(TObject *Sender)
{
	int ID;
	int Tag = GetComponentTag(Sender);
	int Idx = Tag - 1;
	AnsiString FName = FNameVect[Idx];
	AnsiString IName = TranslateName(FName);

	TParam*    Param = NULL;
	if (GDataOrders.CurParams) Param = GDataOrders.CurParams->FindParam(IName);
	int                        IBase = MemTableEh31->FieldByName(IName)->AsInteger;
	if (Param)
		ID = Param->AsInteger;
	else
		ID = IBase;

//	ID    = GetCurrentID(Sender,&IBase);
//	int IBase = MemTableEh31->FieldByName(IName)->AsInteger;
	bool bRes = false;
	TsComboEdit* CEdit = dynamic_cast<TsComboEdit*>(Sender);
	switch (Tag) {
		case  1:	bRes = GetContactID(this,0,ID,GDataOrders.CurParams);
					break;
		case  3: bRes = GetTransTypeID(this,0,ID,GDataOrders.CurParams);
					break;
		case  5: bRes = GetTownID(this,0,ID,GDataOrders.CurParams);
					break;
		case  6: bRes = GetDetailStreetID(true,ID);
					break;
		case  8: bRes = GetTownID(this,0,ID,GDataOrders.CurParams);
					break;
		case  9: bRes = GetDetailStreetID(false,ID);
					break;
		case 12: bRes = GetTransCompanyID(this,0,ID,GDataOrders.CurParams);
					break;
		case 13: bRes = GetDetailTransportID(ID);
					break;
		case 15: bRes = GetDetailDriverID(ID);
					break;
	}
	if (!bRes) return;
	if (ID != IBase) {
		GDataOrders.AddCurParam(ftInteger,IName,ID);
		CEdit->Text  = GetPiece(SelectResultStr,"/",1);
		SetDetailEditColor(Sender,clAqua);
		DetailEditCng[Idx] = true;
		switch (Tag) {
			case 	1:	SetDetailEditText(WCtrlVect[1],GetPiece(SelectResultStr,"/",2));  // sEdit1
						SetDetailEditColor(WCtrlVect[1],clAqua);
						DetailEditCng[0] = true;
						DetailEditCng[1] = true;
						break;
			case  5: SetDetailEditText(WCtrlVect[5],"");											// sComboEdit6->Text = "";
						if (MemTableEh31->FieldByName("BEG_STREET_ID")->AsInteger) {
							SetDetailEditColor(WCtrlVect[5],clAqua);
							DetailEditCng[Tag] = true;
						}
						break;
			case  8: SetDetailEditText(WCtrlVect[8],"");											// sComboEdit8->Text = "";
						if (MemTableEh31->FieldByName("END_STREET_ID")->AsInteger) {
							SetDetailEditColor(WCtrlVect[8],clAqua);
							DetailEditCng[Tag] = true;
						}
						break;
			case 12: SetDetailEditText(WCtrlVect[12],"");			//	=== Перевозчик	   	// sComboEdit10->Text = ""; транспорт
						SetDetailEditText(WCtrlVect[13],"");											// sEdit4->Text       = ""; примечание
						if (MemTableEh31->FieldByName("TRANSPORT_ID")->AsInteger) {
							SetDetailEditColor(WCtrlVect[12],clAqua);
							SetDetailEditColor(WCtrlVect[13],clAqua);
							DetailEditCng[12] = true;
							DetailEditCng[13] = true;
						}
						SetDetailEditText(WCtrlVect[14],"");   										// sComboEdit11->Text       = ""; Водитель
						SetDetailEditText(WCtrlVect[15],"");											// sEdit5->Text             = ""; Телефон
						sComboEdit11->ReadOnly = true;
						sEdit5->ReadOnly       = true;
						if (MemTableEh31->FieldByName("DRIVER_ID")->AsInteger) {
							SetDetailEditColor(WCtrlVect[14],clAqua);
							SetDetailEditColor(WCtrlVect[15],clAqua);
							DetailEditCng[14] = true;
							DetailEditCng[15] = true;
						}
						break;
			case 13: SetDetailEditText(WCtrlVect[13],             // ==== Транспорт =====
											  "Рег.N: "   + GetPiece(SelectResultStr,"/",2) + "   " + //sEdit4->Text =
											  "Мест: "    + GetPiece(SelectResultStr,"/",3) +
											  " > "       + GetPiece(SelectResultStr,"/",4));
						SetDetailEditColor(WCtrlVect[13],clAqua);
						DetailEditCng[Tag] = true;
						SetDetailEditText(WCtrlVect[14],"");   										// sComboEdit11->Text       = ""; Водитель
						SetDetailEditText(WCtrlVect[15],"");											// sEdit5->Text             = ""; Телефон
						sComboEdit11->ReadOnly = true;
						sEdit5->ReadOnly       = true;
						if (MemTableEh31->FieldByName("DRIVER_ID")->AsInteger) {
							SetDetailEditColor(WCtrlVect[14],clAqua);
							SetDetailEditColor(WCtrlVect[15],clAqua);
							DetailEditCng[14] = true;
							DetailEditCng[15] = true;
						}
						break;
			case 15: SetDetailEditText(WCtrlVect[15],GetPiece(SelectResultStr,"/",2));
						SetDetailEditColor(WCtrlVect[15],clAqua);
						DetailEditCng[Tag] = true;
						sEdit5->ReadOnly   = true;
						break;
		}
	}
	else {
		ClearDetailParam(FName);
		FillDetailEdit(CEdit);
		switch (Tag) {
			case  1:	FillDetailEdit(WCtrlVect[1]);
						break;
			case  5: FillDetailEdit(WCtrlVect[5]);
						break;
			case  8: FillDetailEdit(WCtrlVect[8]);
						break;
			case 12: sComboEdit11->ReadOnly = false;  // Перевезчик
						sEdit5->ReadOnly       = false;
						FillDetailEdit(WCtrlVect[12]);
						FillDetailEdit(WCtrlVect[13]);
						FillDetailEdit(WCtrlVect[14]);
						FillDetailEdit(WCtrlVect[15]);
						break;
			case 13: sComboEdit11->ReadOnly = false;  // Транспорт
						sEdit5->ReadOnly       = false;
						FillDetailEdit(WCtrlVect[13]);
						FillDetailEdit(WCtrlVect[14]);
						FillDetailEdit(WCtrlVect[15]);
						break;
			case 15: FillDetailEdit(WCtrlVect[15]);
						sComboEdit11->ReadOnly = false;
						break;
		}
	}
	CEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::GoToNext(TObject *Sender, bool Forward)
{
	int Tag = GetComponentTag(Sender);
	TDBDateTimeEditEh* DTEdit = dynamic_cast<TDBDateTimeEditEh*>(Sender);
	if (DTEdit) {
		if (DTEdit->CalendarVisible) return;
	}
	if (Forward && Tag < NumDetailCtrl) {
		WCtrlVect[Tag]->SetFocus();
	}
	if (!Forward && Tag > 1) {
		WCtrlVect[Tag-2]->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DetailEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key) {
		case VK_RETURN:	GoToNext(Sender, !Shift.Contains(ssCtrl));
								break;
		case VK_ESCAPE:   RestoreDetailEditText(Sender);
								break;
		case VK_BACK:     ClearDetailComboEdit(Sender);
								break;
		case VK_INSERT:   ShowDetailEditPopup(Sender);
								break;
		case VK_F7:       DBGridEh31->RowDetailPanel->Visible = false;
								DBGridEh31->SetFocus();
		                  break;
	}
	if (Key == 'S' && Shift.Contains(ssCtrl)) {
		if (RDPWCtrl) DetailEditChanged(RDPWCtrl);
		SaveDetailPanel();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ShowDetailEditPopup(TObject *Sender)
{
	TDBDateTimeEditEh* DEdit = dynamic_cast<TDBDateTimeEditEh*>(Sender);
	if (DEdit) {
		if (!DEdit->CalendarVisible) DEdit->DropDown();
	}
	TComboBox* CBox = dynamic_cast<TComboBox*>(Sender);
	if (CBox) {
		if (!CBox->DroppedDown) {
			CBox->DroppedDown = true;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::RestoreDetailEditText(TObject *Sender)
{
	switch (GetComponentTag(Sender)) {
		case 14: case 21: case 26: case 40:
					return;
		case 15:	if (sComboEdit11->ReadOnly) return;
					break;
		case 16:	if (sEdit5->ReadOnly) return;
					break;
	}
	FillDetailEdit(dynamic_cast<TWinControl*>(Sender));

	TsComboEdit* CEdit = dynamic_cast<TsComboEdit*>(Sender);
	if (CEdit) {
		switch (CEdit->Tag) {
			case  1: FillDetailEdit(WCtrlVect[0]);  break;
			case  5: FillDetailEdit(WCtrlVect[5]);  break;
			case  6: if (MemTableEh31->FieldByName("Beg_Street_ID")->AsInteger)
							FillDetailEdit(WCtrlVect[4]);
						break;
			case  8: FillDetailEdit(WCtrlVect[8]);  break;
			case  9: if (MemTableEh31->FieldByName("End_Street_ID")->AsInteger)
							FillDetailEdit(WCtrlVect[7]);
                  break;
			case 12: FillDetailEdit(WCtrlVect[12]); // не надо Break;   // Перевозчик -> Транспорт
			case 13: sComboEdit11->ReadOnly = false;                    // Транспрорт ->
						sEdit5->ReadOnly       = false;
						FillDetailEdit(WCtrlVect[13]);                     //               Примечание
						FillDetailEdit(WCtrlVect[14]);                     //            -> Водитель
						FillDetailEdit(WCtrlVect[15]);                     // Водитель   -> Телефон

						break;
			case 15: FillDetailEdit(WCtrlVect[15]);                     // Водитель   -> Телефон
			         sEdit5->ReadOnly = false;
//						FillDetailEdit(WCtrlVect[16]);

		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearDetailEditText(TObject *Sender)
{
	int Idx = GetComponentTag(Sender) - 1;
	if (Idx < 0) return;
	AnsiString FName   = FNameVect[Idx];
	AnsiString IName   = TranslateName(FName);
	DetailEditCng[Idx] = true;
	TsComboEdit* CEdit = dynamic_cast<TsComboEdit*>(Sender);
	if (CEdit) {
		CEdit->Text = "";
		CEdit->Color = clAqua;
		Variant V;
		V.Clear();
		GDataOrders.AddCurParam(ftInteger,IName,V);
		return;
	}
	TsEdit* Edit = dynamic_cast<TsEdit*>(Sender);
	if (Edit) {
		Edit->Text = "";
		Edit->Color = clAqua;
		Variant V;
		V.Clear();
		if (!Edit->ReadOnly)
			GDataOrders.AddCurParam(ftString,FName,V);
		return;
	}
	TsMemo* Memo = dynamic_cast<TsMemo*>(Sender);
	if (Memo) {
		Memo->Text = "";
		Memo->Color = clAqua;
		Variant V;
		V.Clear();
		if (!Memo->ReadOnly)
			GDataOrders.AddCurParam(ftString,FName,V);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ClearDetailComboEdit(TObject *Sender)
{
	int Idx = GetComponentTag(Sender) - 1;
	if (Idx < 0) return;
	TWinControl* WCtrl = WCtrlVect[Idx];
	AnsiString FName   = FNameVect[Idx];
	AnsiString IName = TranslateName(FName);
	TsComboEdit* CEdit = dynamic_cast<TsComboEdit*>(WCtrl);
	if (!CEdit) return;
	if (CEdit->DirectInput) return;
	if (MemTableEh31->FieldByName(IName)->IsNull) return;
	ClearDetailEditText(Sender);
	switch (CEdit->Tag) {
		case  1: ClearDetailEditText(WCtrlVect[0]);
					break;
		case  3:
					break;
		case  5: ClearDetailEditText(WCtrlVect[5]);
					break;
		case  6:
					break;
		case  8: ClearDetailEditText(WCtrlVect[8]);
					break;
		case 12: // перевозчик
					ClearDetailEditText(WCtrlVect[12]);  // транспорт
					ClearDetailEditText(WCtrlVect[13]);  // примечание
					break;
		case 13: // транспорт
					ClearDetailEditText(WCtrlVect[13]);  // примечание
					ClearDetailEditText(WCtrlVect[14]);  // водитель
					ClearDetailEditText(WCtrlVect[15]);  // телефон
					break;
		case 15: // водитель
					ClearDetailEditText(WCtrlVect[15]);  // телефон
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SetDetailEditText(TObject *Sender,AnsiString Txt)
{
	int Idx = GetComponentTag(Sender) - 1;
	if (Idx < 0) return;
	TWinControl* WCtrl = WCtrlVect[Idx];
	AnsiString FName   = FNameVect[Idx];
	TsComboEdit* CEdit = dynamic_cast<TsComboEdit*>(WCtrl);
	if (CEdit) {
		CEdit->Text = Txt;
		return;
	}
	TsEdit* Edit = dynamic_cast<TsEdit*>(WCtrl);
	if (Edit) {
		Edit->Text = Txt;
		return;
	}
	TsMemo* Memo = dynamic_cast<TsMemo*>(WCtrl);
	if (Memo) {
		Memo->Text = Txt;
		return;
	}
	TDBNumberEditEh* NEdit = dynamic_cast<TDBNumberEditEh*>(WCtrl);
	if (NEdit) {
		NEdit->Value = StrToIntDef(Txt,0);
		return;
	}
/*
	TDBDateTimeEditEh* DEdit = dynamic_cast<TDBDateTimeEditEh*>(WCtrl);
	if (DEdit) {
		DEdit->Color = Color;
	}
	TComboBox* CBox = dynamic_cast<TComboBox*>(WCtrl);
	if (CBox) {
		CBox->Color = Color;
		return;
	}
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SetDetailEditColor(TObject *Sender,TColor Color)
{
	int Idx = GetComponentTag(Sender) - 1;
	if (Idx < 0) return;
	TWinControl* WCtrl = WCtrlVect[Idx];
	AnsiString FName   = FNameVect[Idx];
	TsComboEdit* CEdit = dynamic_cast<TsComboEdit*>(WCtrl);
	if (CEdit) {
		CEdit->Color = Color;
		return;
	}
	TsEdit* Edit = dynamic_cast<TsEdit*>(WCtrl);
	if (Edit) {
		Edit->Color = Color;
		return;
	}
	TsMemo* Memo = dynamic_cast<TsMemo*>(WCtrl);
	if (Memo) {
		Memo->Color = Color;
		return;
	}
	TDBNumberEditEh* NEdit = dynamic_cast<TDBNumberEditEh*>(WCtrl);
	if (NEdit) {
		NEdit->Color = Color;
		return;
	}
	TDBDateTimeEditEh* DEdit = dynamic_cast<TDBDateTimeEditEh*>(WCtrl);
	if (DEdit) {
		DEdit->Color = Color;
	}
	TComboBox* CBox = dynamic_cast<TComboBox*>(WCtrl);
	if (CBox) {
		CBox->Color = Color;
		return;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormTrans::DetailEditChanged(TObject *Sender)
{
	int Idx = GetComponentTag(Sender) - 1;
	if (Idx < 0) return false;
	TWinControl* WCtrl = WCtrlVect[Idx];
	AnsiString FName   = FNameVect[Idx];
	TsComboEdit* CEdit = dynamic_cast<TsComboEdit*>(WCtrl);
	bool bRes = false;
	if (CEdit) {
		if (CEdit->Tag == 1) {
			bool En = MemTableEh31->FieldByName("ORDER_FLAG")->AsInteger & EDIT_CONTACT_IS_ALLOWED;
			if (En) {
				Trunc(MemTableEh31,CEdit,FName);
				AnsiString S  = CEdit->Text;
				if (S != MemTableEh31->FieldByName(FName)->AsString) {
					GDataOrders.AddCurParam(ftString,FName,S);
					bRes = true;
				}
			}
			else bRes = DetailEditCng[Idx];
		}
		else bRes = DetailEditCng[Idx];
		return bRes;
	}
	TsEdit* Edit = dynamic_cast<TsEdit*>(WCtrl);
	if (Edit) {
		AnsiString HdrList = GetPiece(FName,"|",2);
		if (HdrList != "") return DetailEditCng[Idx];
		Trunc(MemTableEh31,Edit,FName);
		AnsiString S  = Edit->Text;
		if (S != MemTableEh31->FieldByName(FName)->AsString) {
			GDataOrders.AddCurParam(ftString,FName,S);
			bRes = true;
		}
		return bRes;
	}

	TsMemo* Memo = dynamic_cast<TsMemo*>(WCtrl);
	if (Memo) {
		Trunc(MemTableEh31,Memo,FName);
		AnsiString S  = Memo->Text;
		if (S != MemTableEh31->FieldByName(FName)->AsString) {
			GDataOrders.AddCurParam(ftString,FName,S);
			bRes = true;
		}
		return bRes;
	}

	TDBNumberEditEh* NEdit = dynamic_cast<TDBNumberEditEh*>(WCtrl);
	if (NEdit) {
		if (NEdit->Value != MemTableEh31->FieldByName(FName)->Value) {
			GDataOrders.AddCurParam(ftInteger,FName,NEdit->Value);
			bRes = true;
		}
		return bRes;
	}
	TDBDateTimeEditEh* DEdit = dynamic_cast<TDBDateTimeEditEh*>(WCtrl);
	if (DEdit) {
		AnsiString NV;
		if (!DEdit->Value.IsNull() && !DEdit->Value.IsEmpty()) {
			TDateTime DT = DEdit->Value;
			NV = DT.FormatString(DEdit->EditFormat);
		}

		AnsiString OV;
		if (!MemTableEh31->FieldByName(FName)->IsNull)
		  OV = MemTableEh31->FieldByName(FName)->AsDateTime.FormatString(DEdit->EditFormat);
		if (OV != NV) {
			GDataOrders.AddCurParam(ftDateTime,FName,DEdit->Value);
			bRes = true;
		}
		return bRes;
	}
	TComboBox* CBox = dynamic_cast<TComboBox*>(WCtrl);
	if (CBox) {
		if (CBox->ItemIndex != MemTableEh31->FieldByName(FName)->AsInteger) {
			FName = TranslateName(FName);
			GDataOrders.AddCurParam(ftInteger,FName,CBox->ItemIndex);
			bRes = true;
		}
		return bRes;
	}
	return bRes;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DetailEditEnter(TObject *Sender)
{
	RDPWCtrl = Sender;
}
//---------------------------------------------------------------------------
bool __fastcall GetWCtrlMinuts(TWinControl* WCtrl,int& Min)
{
	TDBDateTimeEditEh* DTEdit = dynamic_cast<TDBDateTimeEditEh*>(WCtrl);
	if (!DTEdit->Value.IsNull() && !DTEdit->Value.IsEmpty()) {
		TDateTime DT = DTEdit->Value;
		Min  = StrToIntDef(DT.FormatString("h"),0)*60 + StrToIntDef(DT.FormatString("n"),0);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall GetWCtrlNumber(TWinControl* WCtrl,int& Num)
{
	TDBNumberEditEh*   NEdit  = dynamic_cast<TDBNumberEditEh*>  (WCtrl);
	if (!NEdit->Value.IsNull() && !NEdit->Value.IsEmpty()) {
		Num = NEdit->Value;
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ShowCalcFields()
{
	int SumMinut  = 0;
	int Add       = 0;

	GetWCtrlMinuts(WCtrlVect[17], Add);                    // Подача
	if (GetWCtrlMinuts(WCtrlVect[19], SumMinut))
		 SumMinut+= Add;     // Часы работы

	int NDay      = 0;
	GetWCtrlNumber(WCtrlVect[18],NDay);                         // Дни работы
	if (SumMinut > 1440) {
		++NDay;
		SumMinut -= 1440;
	}

	if (ComboBox2->ItemIndex == 1 && !MemTableEh31->FieldByName("TIME_MIN")->IsNull) {
		TDateTime DT = MemTableEh31->FieldByName("TIME_MIN")->AsDateTime;
		int MinTime  = StrToInt(DT.FormatString("h"))*60 + Add + StrToInt(DT.FormatString("n"));
		if (MinTime > NDay*1440 + SumMinut) {
			SumMinut = MinTime %1440;
			NDay     = MinTime /1440;
		}
	}

	AnsiString S;
	if (NDay) S = IntToStr(NDay) + " ";
	int H = SumMinut / 60;
	if (H < 9) S += "0";
	S += IntToStr(H) + ":";
	int M = SumMinut % 60;
	if (M < 9) S += "0";
	S += IntToStr(M);


	TWinControl* WCtrl = WCtrlVect[20]; // ==> Сумма Дни + Часы
	SetDetailEditText(WCtrl,S);

	bool Cng = DetailEditChanged(WCtrl);
	StoreChanges(WCtrl,20,Cng);
// ====

	SumMinut += (NDay*1440);

	int TimeTax = 0;
	int CalcSum = 0;
	if (SumMinut && GetWCtrlNumber(WCtrlVect[21],TimeTax)) {  // За 1 час
		CalcSum = (SumMinut)*TimeTax/60;
	}
	int DistVal = 0;
	int DistTax = 0;   // Пробег                           За 1км
	if (GetWCtrlNumber(WCtrlVect[22],DistVal) && GetWCtrlNumber(WCtrlVect[23],DistTax)) {
		CalcSum += DistVal*DistTax;
	}
	if (ComboBox2->ItemIndex == 3) {
		CalcSum = MemTableEh31->FieldByName("DOG_TAX")->AsInteger;
	}
	WCtrl = WCtrlVect[25];							// расчет
	SetDetailEditText(WCtrl,IntToStr(CalcSum));
	Cng = CalcSum != MemTableEh31->FieldByName("PAY_CALC")->AsInteger;
	if (Cng) StoreChanges(WCtrl,25,Cng);
	else     FillDetailEdit(WCtrl);
	CalcIncomeField();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::CalcIncomeField()
{
	int Income = 0;

	GetWCtrlNumber(WCtrlVect[26],Income);               // итоговая
	if (!Income) GetWCtrlNumber(WCtrlVect[25],Income);  // расчет
	if (Income) {
		int Avc = 0;
		GetWCtrlNumber(WCtrlVect[28],Avc);
		SetDetailEditText(WCtrlVect[31],IntToStr(Income-Avc));
	}
	int Exc = 0;
	int Mng = 0;
	GetWCtrlNumber(WCtrlVect[34],Exc);
	GetWCtrlNumber(WCtrlVect[36],Mng);
	Income -= (Exc+Mng);
//	if (Income < 0) Income = 0;
	TWinControl* WCtrl = WCtrlVect[39];
	SetDetailEditText(WCtrl,IntToStr(Income));
	bool Cng = Income != MemTableEh31->FieldByName("INCOME")->AsInteger;
	if (Cng) StoreChanges(WCtrl,39,Cng);
	else     FillDetailEdit(WCtrl);

}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::StoreChanges(TObject *Sender,int Idx,bool Cng)
{
	TColor Color;
	if (Cng) {
		DetailEditCng[Idx] = true;
		Color = clAqua;
	}
	else {
		DetailEditCng[Idx] = false;
		Color = clWindow;
	}
	SetDetailEditColor(Sender,Color);

}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::DetailEditExit(TObject *Sender)
{
	bool Cng = DetailEditChanged(Sender);
	int Tag  = GetComponentTag(Sender);
	int Idx  = Tag - 1;
	StoreChanges(Sender,Idx,Cng);
	AnsiString S;
	switch (Tag) {
		case 18:                      // подача
		case 19:                      // дни
		case 20:                      // часы

		case 22:								// 1 час
		case 23:								// пробег
		case 24:								// 1 км
		case 25:                      // способ расчета

					ShowCalcFields();
					break;
		case 27:			               // итоговая
		case 29:                      // аванс
		case 35:
		case 37:	CalcIncomeField();
					break;
	}

}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::SaveDetailPanel()
{
	if (!GDataOrders.CurParams) return;
	bool Chk =  sCheckBox21->Checked;
	sCheckBox21->Checked = false;
	GDataOrders.AddCurParam(ftString,"CONTACT_PHONE_ADD",sEdit1->Text);
	WriteDataStd(GDataOrders,   false);
	SetAfterScroll(MemTableEh31);
	ResetDetailPanel();
	DBGridEh31->RowDetailPanel->Visible = true;
	sCheckBox21->Checked = Chk;
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::ResetDetailPanel()
{
	FillRowDetailPanel();
	if (GDataOrders.CurParams)
		GDataOrders.CurParams->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormTrans::sButtonClick(TObject *Sender)
{
	switch (GetComponentTag(Sender)) {
		case 1: SaveDetailPanel();  break;
		case 2: ResetDetailPanel(); break;
	}
}
//---------------------------------------------------------------------------
/*
MESSAGE void TFormTrans::MyMouseMove(TWMMouse& Msg) {
	TForm::Dispatch(&Msg);
//	Label1->Caption = IntToStr(Msg.XPos) + " " + IntToStr(Msg.YPos);
};
MESSAGE void TFormTrans::MyMouseWheel(TWMMouseWheel& Msg) {
	TForm::Dispatch(&Msg);
	if (PageTag == 4)
		PulseFilterStd(GDataGraph);
//abel1->Caption = Label1->Caption + ">";
};
MESSAGE void TFormTrans::MyCommand(TMessage& Msg) {
	TForm::Dispatch(&Msg);
//abel1->Caption = Label1->Caption + ">";
};
*/
void __fastcall TFormTrans::DBGridEh41CellClick(TColumnEh *Column)
{
	WrkGData = &GDataGraph;
}
//---------------------------------------------------------------------------


void __fastcall TFormTrans::DBGridEh41ColEnter(TObject *Sender)
{
	CurGraphCol = DBGridEh41->Col;
	if ((CurGraphCol > 6 && PrvGraphCol <= 6) || (CurGraphCol <= 6 && PrvGraphCol > 6)){
//      DBGridEh41->Repaint();
	}
	PrvGraphCol = CurGraphCol;
}
//---------------------------------------------------------------------------

