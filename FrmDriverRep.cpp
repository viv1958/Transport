//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DModT.h"
#include "ComProc.h"
#include "FrmSelSimpleEh.h"

#include "FrmDriverRep.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAxisGridsEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "DBGridEhToolCtrls"
#pragma link "GridsEh"
#pragma link "sCheckBox"
#pragma link "sComboBox"
#pragma link "sCustomComboEdit"
#pragma link "sLabel"
#pragma link "sMaskEdit"
#pragma link "sPanel"
#pragma link "sSpeedButton"
#pragma link "sSplitter"
#pragma link "sStatusBar"
#pragma link "sTooledit"
#pragma link "ToolCtrlsEh"
#pragma link "sComboEdit"
#pragma link "DataDriverEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "sPageControl"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "frxDesgn"
#pragma link "frxDMPExport"
#pragma link "sMemo"
#pragma link "DBCtrlsEh"
#pragma resource "*.dfm"
void ShowDriverReport(int DriverID, AnsiString DriverName)
{
	TFormDriverRep* Form = new TFormDriverRep(Application, DriverID, DriverName);
	Form->Show();
}
//---------------------------------------------------------------------------
__fastcall TFormDriverRep::TFormDriverRep(TComponent* Owner,int DriverID, AnsiString DriverName)
	: TForm(Owner)
{
	 this->DriverID   = DriverID;
	 this->DriverName = DriverName;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::SetDriver(int DriverID, AnsiString DriverName)
{
	if (DriverID != this->DriverID || !WrkGData->WrkDSet->Active) {
		this->DriverID = DriverID;
		ProcRefreshPage();
	}
	sComboEdit1->Text = DriverName;
	GDataMonInp.AddExtParam(ftInteger, "INDEX_ID_TAG", DriverID);
	GDataMonOut.AddExtParam(ftInteger, "INDEX_ID_SRC", DriverID);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::FormCreate(TObject *Sender)
{
	sPageControl1->ActivePage = sTabSheet1;
	InitCommon();
	InitGData();
	SetPage();
	if (!DriverID) {
	  SelectDriver();
	}
	else SetDriver(DriverID,DriverName);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::InitCommon()
{
	SetFormPosStd(this,1330,750,0,true);

	TDateTime DT = Date();
	SelYY = MaxYY = CurYY = StrToInt(DT.FormatString("yy"));
	SelMM = MaxMM = CurMM = StrToInt(DT.FormatString("m"));
	SetDates(CurMM, CurYY);
	SetButtonCaption(CurMM);
	sMemo1->Text = "";
	sMemo2->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::SetDates(int MM,int YY)
{
	DT_Beg = "01."+IntToStr(MM) + "." + IntToStr(YY);
	DT_End = DT_Beg + 32;
	DT_End = "01."+DT_End.FormatString("mm.yy");
	--DT_End;
	sDateEdit1->Date = DT_Beg;
	sDateEdit2->Date = DT_End;
}
static AnsiString MonList[] =
	 {"Ноябрь","Декабрь","Январь","Февраль","Март","Апрель","Май","Июнь","Июль",
	  "Август","Сентябрь","Октябрь","Ноябрь","Декабрь","Январь","Февраль"};
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::SetButtonCaption(int Mon)
{
	Mon +=1;
	sSpeedButton34->Caption = MonList[Mon];
	sSpeedButton33->Caption = MonList[Mon-1];
	sSpeedButton32->Caption = MonList[Mon-2];
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::InitGData()
{
// ==== заказы =================================================================
	GDataOrders.Flags =  STD_STATUSBAR | FILTER_BY_NAME | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL;
	GDataOrders.WrkSBar = sStatusBar1;
	GDataOrders.FieldKey      = "Orders_ID";

	GDataOrders.SetSQL        = SetSQL;
	GDataOrders.FunAddRow     = AddCurrentRow;

	GDataOrders.SrcDSet       = Query1;
	GDataOrders.WrkGrid       = DBGridEh1;
	GDataOrders.WrkDBase      = DModT->Database1;

// ==== расходы ================================================================
	GDataOutlay.Flags         =  STD_STATUSBAR | FILTER_BY_NAME | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL;
										  //| UPDATE_ONLY_CURRENT | SAVE_SELECTION;
	GDataOutlay.WrkSBar       = sStatusBar1;

	GDataOutlay.FieldKey      = "Outlay_ID";
	GDataOutlay.SetSQL        = SetSQL;
	GDataOutlay.FunAddRow     = AddCurrentRow;


	GDataOutlay.SrcDSet       = Query2;
	GDataOutlay.WrkGrid       = DBGridEh2;
	GDataOutlay.WrkDBase      = DModT->Database1;
	GDataOutlay.FilterFldMask =  0x0F70;
// ==== полученные деньги ======================================================
	GDataMonInp.Flags         =  STD_STATUSBAR | FILTER_BY_NAME | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL | CAN_SEE_DELETED;
										 UPDATE_ONLY_CURRENT;
	GDataMonInp.WrkSBar       = sStatusBar1;

	GDataMonInp.FieldKey      = "Money_Move_ID";
	GDataMonInp.SetSQL        = SetSQL;
	GDataMonInp.FunAddRow     = AddCurrentRow;
	GDataMonInp.FunSetSQLOne  = RefreshOneRow;


	GDataMonInp.SrcDSet       = Query3;
	GDataMonInp.WrkGrid       = DBGridEh3;
	GDataMonInp.WrkDBase      = DModT->Database1;
	GDataMonInp.EditAllowMask = 0x001F;
	GDataMonInp.NullAllowMask = 0x001B;
	GDataMonInp.FilterFldMask = 0x0012;
	GDataMonInp.Select_IDMask = 0x0003;

	GDataMonInp.TextEdit      = DBEditEh;
	GDataMonInp.NumbEdit   	  = DBNumberEditEh;
	GDataMonInp.DateEdit      = DBDateTimeEditEh;
	GDataMonInp.ListEdit      = ComboBox;

	GDataMonInp.WrkQuery      = Query5;

	GDataMonInp.FldTranslateMap.insert(pair<AnsiString,AnsiString>("NAME_TYPE_SRC", "OBJECT_ID_SRC"));
	GDataMonInp.FldTranslateMap.insert(pair<AnsiString,AnsiString>("NAME_SRC", "OBJECT_ID_SRC"));
	GDataMonInp.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("OBJECT_ID_SRC"), GetObjectID));

	SetCommonExtParams(GDataMonInp);
// ==== переданные деньги ======================================================
	GDataMonOut.Flags         =  STD_STATUSBAR | FILTER_BY_NAME | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL | CAN_SEE_DELETED;
										 UPDATE_ONLY_CURRENT;
	GDataMonOut.WrkSBar       = sStatusBar1;

	GDataMonOut.FieldKey      = "Money_Move_ID";
	GDataMonOut.SetSQL        = SetSQL;
	GDataMonOut.FunAddRow     = AddCurrentRow;
	GDataMonOut.FunSetSQLOne  = RefreshOneRow;


	GDataMonOut.SrcDSet       = Query4;
	GDataMonOut.WrkGrid       = DBGridEh4;
	GDataMonOut.WrkDBase      = DModT->Database1;
	GDataMonOut.EditAllowMask = 0x001F;
	GDataMonOut.NullAllowMask = 0x001B;
	GDataMonOut.FilterFldMask = 0x0012;
	GDataMonOut.Select_IDMask = 0x0003;

	GDataMonOut.TextEdit      = DBEditEh;
	GDataMonOut.NumbEdit   	  = DBNumberEditEh;
	GDataMonOut.DateEdit      = DBDateTimeEditEh;
	GDataMonOut.ListEdit      = ComboBox;

	GDataMonOut.WrkQuery      = Query6;

	GDataMonOut.FldTranslateMap.insert(pair<AnsiString,AnsiString>("NAME_TYPE_TAG", "OBJECT_ID_TAG"));
	GDataMonOut.FldTranslateMap.insert(pair<AnsiString,AnsiString>("NAME_TAG", "OBJECT_ID_TAG"));
	GDataMonOut.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("OBJECT_ID_TAG"), GetObjectID));

	SetCommonExtParams(GDataMonOut);

}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::WriteMemo()
{
	switch (PageTag) {
		case 3:  WriteMemoStd(GDataMonInp,sMemo1); break;
		case 4:	WriteMemoStd(GDataMonOut,sMemo2); break;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormDriverRep::GetObjectID(TForm* Frm, int Left,int &ID,TParams*&)
{
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	AnsiString SelectResultStr;
	bool bRes = SimpleSelEhMoneyReceiverID(Frm,0,ID,Params,&SelectResultStr);
	if (bRes) {
		switch (PageTag) {
			case 3: GDataMonInp.AddCurParam(ftInteger,"OBJECT_TYPE_SRC",StrToIntDef(GetPiece(SelectResultStr,"/",2),0));
					  GDataMonInp.AddCurParam(ftInteger,"INDEX_ID_SRC",   StrToIntDef(GetPiece(SelectResultStr,"/",3),0));
					  break;
			case 4: GDataMonInp.AddCurParam(ftInteger,"OBJECT_TYPE_TAG",StrToIntDef(GetPiece(SelectResultStr,"/",2),0));
					  GDataMonInp.AddCurParam(ftInteger,"INDEX_ID_TAG",   StrToIntDef(GetPiece(SelectResultStr,"/",3),0));
					  break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::SetCommonExtParams(GridData& GData)
{
	GData.AddExtParam(ftInteger, "USER_ID",     DModT->CurEmpID);
	GData.AddExtParam(ftString,  "COMP_NAME",   DModT->ComputerName);
}
//---------------------------------------------------------------------------
bool __fastcall TFormDriverRep::SetSQL(TDataSet* DSet)
{
	AnsiString SQL, Tail;
	switch (DSet->Tag) {
		case 1:  SQL = "select * from Sel_Orders_Driver("  + IntToStr(DriverID) + ",'" +
							GetDateStr(DT_Beg) + "','" + GetDateStr(DT_End) + "')";
					Query1->SQL->Text = SQL;
					break;
		case 2:  SQL = "select * from Sel_Outlay_Driver("  + IntToStr(DriverID) + ",'" +
							GetDateStr(DT_Beg) + "','" + GetDateStr(DT_End) + "')";
					Query2->SQL->Text = SQL;
					break;
		case 3:  SQL = "select * from Sel_Money_Move(0,'" + GetDateStr(DT_Beg) + "','" +
							 GetDateStr(DT_End) + "'," + IntToStr(Drv_Object_ID) +")";
					Query3->SQL->Text = SQL;
					break;
		case 4:  SQL = "select * from Sel_Money_Move(1,'" + GetDateStr(DT_Beg) + "','" +
							 GetDateStr(DT_End) + "'," + IntToStr(Drv_Object_ID) +")";
					Query4->SQL->Text = SQL;
					break;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFormDriverRep::RefreshOneRow(GridData& GData,TDataSet* DSet)
{
	bool bRes = true;
	AnsiString SQL;
	int IVal;
	int Result;
	switch (GData.WrkDSet->Tag) {
		case 3:	SQL = "select * from Sel_Money_Move(99,null,null," + GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
		case 4: 	SQL = "select * from Sel_Money_Move(99,null,null," + GData.WrkQuery->FieldByName("RESULT")->AsString + ")";
					break;
	}
	TQuery* Qry = dynamic_cast<TQuery*>(DSet);
	Qry->SQL->Text = SQL;
	return bRes;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::CloseAll()
{
	MemTableEh1->Active = false;
	MemTableEh2->Active = false;
	MemTableEh3->Active = false;
	MemTableEh4->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::ProcRefreshPage()
{
	SavePosStd(*WrkGData);
	CloseAll();
	ProcRefreshStd(*WrkGData,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Shift.Contains(ssAlt) || Shift.Contains(ssCtrl)) {
		TsTabSheet* NewSheet = NULL;
		switch (Key) {
			case '1': NewSheet = sTabSheet1; break;
			case '2': NewSheet = sTabSheet2; break;
			case '3': NewSheet = sTabSheet3; break;
			case '4': NewSheet = sTabSheet4; break;
		}
		if (NewSheet && NewSheet != sPageControl1->ActivePage) {
			WriteMemo();
			sPageControl1->ActivePage = NewSheet;
			SetPage();
		}
	}
	switch (Key) {
		case VK_ADD:
		case VK_SUBTRACT:
						 if (sMemo1->Focused() || sMemo2->Focused()) {
							 return;
						 }
						 break;
		case VK_F3:  WriteMemo();
						 break;
		case VK_F5:  WriteMemo();
						 ProcRefreshPage();
						 break;
		case VK_F11: ProcHistory(Shift.Contains(ssCtrl));
						 break;
	}
	FormKeyDownStd(*WrkGData,Key,Shift);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormDriverRep::TranslateName(AnsiString FldName)
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
void __fastcall TFormDriverRep::ProcHistory(bool All)
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
	RestValue RestData;
	if (SimpleSelHistoryID(this, 0,Title,TableName,ID,FieldNamesList,TitleNamesList,RestData)) {
//		RestoreValue(RestData,!All);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::FormClose(TObject *Sender, TCloseAction &Action)
{
	WriteMemo();
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sSpeedButtonClick(TObject *Sender)
{
 	WriteMemo();
	switch (GetComponentTag(Sender)) {
		case  1:	ProcRefreshPage();               break;
		case  2:	ProcDeleteStd(*WrkGData); 			break;
		case  3: ProcInsertStd(*WrkGData);        break;

		case  4: ProcSelAllStd(*WrkGData, NULL);	break;
		case  5: ClearSums();
					ProcUnsAllStd(*WrkGData, NULL);
					break;
		case  6: frxReport1->Print();					break;
		case  7: PrintReport();      					break;
		case  8: ProcHistory(false); 					break;
		case 31: ShowMonth(-3);      					break;
		case 32: ShowMonth(-2);      					break;
		case 33: ShowMonth(-1);      					break;
		case 34: ShowMonth(0);       					break;
		case 35: ShowMonth(1);       					break;
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::ShowMonth(int Shift)
{
	int MM = SelMM;
	int YY = SelYY;
	int Add = (CurYY - SelYY)*12 + CurMM - SelMM;
	Shift += Add;
	MM += Shift;
	if (MM <=0) {
		--YY;
		MM += 12;
	}
	else if (MM > 12) {
		++YY;
		MM -=12;
	}
	// теперь SelMM и SelYY корректы
	if ((MM > MaxMM && YY == MaxYY) || YY > MaxYY) {
		MM = MaxMM;
		YY = MaxYY;
	}
	// и не превышают текущего месяца
	int Dist = (CurYY-YY)*12 + CurMM - MM;

	if (Dist < 0) {
		CurMM = MM;
		CurYY = YY;
	}
	else if (Dist > 2) {
		CurMM = MM + 2;
		CurYY = YY;
		if (CurMM > 12) {
			CurMM -= 12;
			CurYY++;
		}
	}
	SelMM = MM;
	SelYY = YY;
	TDateTime DT_B = "01."+IntToStr(SelMM) + "." + IntToStr(SelYY);
	TDateTime DT_E = DT_B + 32;
	DT_E = "01."+DT_E.FormatString("mm.yy");
	--DT_E;
	if (DT_B != DT_Beg || DT_E != DT_End) {
		SetButtonCaption(CurMM);
		SetDates(SelMM, SelYY);
		ProcRefreshPage();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sComboEdit1ButtonClick(TObject *Sender)
{
	SelectDriver();
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::SelectDriver()
{
	WriteMemo();
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	int ID = DriverID;
	AnsiString SelectResultStr;
	if (SimpleSelEhDriverID(this,0,ID,0,Params,&SelectResultStr)) {
		Drv_Object_ID = StrToIntDef(GetPiece(SelectResultStr,"/",3),-1);
		if (Drv_Object_ID != -1) {
			GDataMonInp.AddExtParam(ftInteger, "OBJECT_ID_TAG", Drv_Object_ID);
			GDataMonOut.AddExtParam(ftInteger, "OBJECT_ID_SRC", Drv_Object_ID);
		}
		else {
			GDataMonInp.ClearExtParams();
			GDataMonOut.ClearExtParams();
		}
		SetDriver(ID, GetPiece(SelectResultStr,"/",1));
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sDateEditAcceptDate(TObject *Sender, TDateTime &aDate,
			 bool &CanAccept)
{
	 int Shift = 0;
	 switch (GetComponentTag(Sender)) {
		 case 1: Shift = aDate - DT_Beg;
					if (Shift) {
						 DT_Beg = aDate;
						 if (DT_Beg >= DT_End) {
							 DT_End = DT_Beg + 32;
							 DT_End = "01."+DT_End.FormatString("mm.yy");
							 --DT_End;
							 sDateEdit2->Date = DT_End;
						 }
					}
					break;
		 case 2: Shift =  DT_End - aDate;
					if (Shift) {
						DT_End = aDate;
						 if (DT_Beg >= DT_End) {
							 DT_Beg = "01."+ DT_End.FormatString("mm.yy");
							 sDateEdit1->Date = DT_Beg;
						 }
					}
					break;
	 }
	 if (Shift) {
		 ProcRefreshPage();
	 }
}
//---------------------------------------------------------------------------
GridData& __fastcall TFormDriverRep::GetGDataRef(TObject* Sender)
{
	GridData* Ref = WrkGData;
	switch (GetComponentTag(Sender)) {
		case 1: Ref = &GDataOrders; 	break;
		case 2: Ref = &GDataOutlay; 	break;
		case 3: Ref = &GDataMonInp; 	break;
		case 4: Ref = &GDataMonOut; 	break;
	}
	return *Ref;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::DBGridEhDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumnEh *Column, TGridDrawStateEh State)
{
	DrawColumnCellStd(GetGDataRef(Sender),Rect,DataCol,Column,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::DBGridEhEnter(TObject *Sender)
{
	WrkGData = &GetGDataRef(Sender);
	SetStatusBarStd(*WrkGData);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::DBGridEhExit(TObject *Sender)
{
	int Cnt = sStatusBar1->Panels->Count;
	for (int i=0; i < Cnt; i++)
		sStatusBar1->Panels->Items[i]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::DBGridEhGetCellParams(TObject *Sender, TColumnEh *Column,
			 TFont *AFont, TColor &Background, TGridDrawStateEh State)
{
	GetCellParamsStd(GetGDataRef(Sender), AFont,Background,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::DBGridEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (PageTag > 2 && Key == VK_INSERT) {
		TDateTime DateSet = Date();
		if (DateSet < DT_Beg)
			DateSet = DT_Beg;
		else if (DateSet > DT_End)
			DateSet = DT_End;
		WrkGData->AddCurParam(ftDateTime,"DATESET",DateSet);
	}
	ProcKeyDownStd(GetGDataRef(Sender),Key);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::DBGridEhKeyPress(TObject *Sender, System::WideChar &Key)
{
	ProcKeyPressStd(GetGDataRef(Sender),Key);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::MemTableEh1AfterClose(TDataSet *DataSet)
{
	AfterCloseStd(GetGDataRef(DataSet));
	ProcUnsAllStd(GetGDataRef(DataSet), NULL);
	switch (DataSet->Tag) {
		case 3: sMemo1->Text = ""; break;
		case 4: sMemo2->Text = ""; break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::MemTableEh1AfterOpen(TDataSet *DataSet)
{
	RestorePosStd(GetGDataRef(DataSet),false);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::MemTableEh1AfterScroll(TDataSet *DataSet)
{
	AfterScrollStd(GetGDataRef(DataSet));
	switch (DataSet->Tag) {
		case 3: ShowMemoStd(GDataMonInp,sMemo1); break;
		case 4: ShowMemoStd(GDataMonOut,sMemo2); break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::MemTableEh1BeforeScroll(TDataSet *DataSet)
{
	BeforeScrollStd(GetGDataRef(DataSet));
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::MemTableEhFilterRecord(TDataSet *DataSet, bool &Accept)
{
	Accept = FilterRecordStd(GetGDataRef(DataSet));
	if (Accept) {
		switch (DataSet->Tag) {
			case 1: case 2:  case 3: case 4:
					  Accept = !DataSet->FieldByName("FLAG_MES")->AsInteger;
					  if (!Accept) {
						  ShowLowFooter(DataSet);
					  }
					  break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::ShowLowFooter(TDBGridEh* Grid,TDataSet *DataSet, int Item)
{
	TColumnEh* Column = Grid->Columns->Items[Item];
	Column->Footers->Items[1]->Value = DataSet->FieldByName(Column->FieldName)->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::ShowLowFooter(TDataSet *DataSet)
{
	switch (DataSet->Tag) {
		case 1: ShowLowFooter(DBGridEh1, DataSet, 9);
				  ShowLowFooter(DBGridEh1, DataSet, 10);
				  break;
		case 2: ShowLowFooter(DBGridEh2, DataSet, 7);
				  break;
		case 3: ShowLowFooter(DBGridEh3, DataSet, 2);
				  break;
		case 4: ShowLowFooter(DBGridEh4, DataSet, 2);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::ShowHighFooter(TDataSet *DataSet)
{
	switch (DataSet->Tag) {
		case 1: DBGridEh1->Columns->Items[9]->Footers->Items[0]->Value = IntToStr(SumHand);
				  DBGridEh1->Columns->Items[10]->Footers->Items[0]->Value = IntToStr(SumPay);
				  break;
		case 2: DBGridEh2->Columns->Items[7]->Footers->Items[0]->Value = IntToStr(SumOutlay);
				  break;
		case 3: DBGridEh3->Columns->Items[2]->Footers->Items[0]->Value = IntToStr(SumMonInp);
				  break;
		case 4: DBGridEh4->Columns->Items[2]->Footers->Items[0]->Value = IntToStr(SumMonOut);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::SetPage()
{
	PageTag = sPageControl1->ActivePage->Tag;
	WrkGData = &GetGDataRef(sPageControl1->ActivePage);
	EnableControls();
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::EnableControls()
{
	bool En = PageTag > 2;
	sSpeedButton2->Enabled = En;
	sSpeedButton3->Enabled = En;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sPageControl1Change(TObject *Sender)
{
	SetPage();
	if (!WrkGData->WrkDSet->Active)
		ProcRefreshStd(*WrkGData,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sPageControl1Changing(TObject *Sender, bool &AllowChange)
{
	 switch (PageTag) {
		 case 3:
		 case 4: WriteMemo();
					break;
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::ClearSums()
{
	switch (PageTag) {
		case 1: SumHand = SumPay = 0;
				  ShowHighFooter(MemTableEh1);
				  break;
		case 2: SumOutlay = 0;
				  ShowHighFooter(MemTableEh2);
				  break;
		case 3: SumMonInp = 0;
				  ShowHighFooter(MemTableEh3);
				  break;
		case 4: SumMonOut = 0;
				  ShowHighFooter(MemTableEh4);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::AddCurrentRow(GridData& GData,int Mul, bool Show, bool Clear)
{
//	bool Selected;
	TDataSet* DSet = GData.WrkDSet;
	if (Clear) {
		ClearSums();
	}
	else {
		int ID;
		switch (PageTag) {
			case 1:	SumHand   += Mul*DSet->FieldByName("DRIVER_HAND_MONEY")->AsInteger;
						SumPay    += Mul*DSet->FieldByName("DRV_PAY")->AsInteger;
						break;
			case 2:	SumOutlay += Mul*DSet->FieldByName("OUTLAY_VALUE")->AsInteger;
						break;
			case 3:	SumMonInp += Mul*DSet->FieldByName("MONEY_VALUE")->AsInteger;
						break;
			case 4:	SumMonOut += Mul*DSet->FieldByName("MONEY_VALUE")->AsInteger;
						break;
			default: return;
		}
	}
	if (Show) ShowHighFooter(GData.WrkDSet);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::PrintReport()
{
	if (!MemTableEh1-Active) ProcRefreshStd(GDataOrders,true);
	if (!MemTableEh2-Active) ProcRefreshStd(GDataOutlay,true);
	if (!MemTableEh3-Active) ProcRefreshStd(GDataMonInp,true);
	if (!MemTableEh4-Active) ProcRefreshStd(GDataMonOut,true);
	frxReport1->ShowReport(true);
	ProcRefreshPage();

}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sCheckBoxClick(TObject *Sender)
{
	TsCheckBox* CBox = dynamic_cast<TsCheckBox*>(Sender);
	if (CBox->Checked) {
		WrkGData->Flags |= SHOW_SELECTED;
	}
	else {
		WrkGData->Flags ^= SHOW_SELECTED;
	}
	PulseFilterStd(*WrkGData);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::frxReport1BeforePrint(TfrxReportComponent *Sender)
{
	if (!Sender->Tag) return;
	AnsiString FName = Sender->Name;
	if (FName.Pos("Memo")) {
		TfrxMemoView* MV = dynamic_cast<TfrxMemoView *>(frxReport1->FindObject(FName));
		if (!MV || !MV->Tag) return;
		AnsiString S;
		switch (Sender->Tag) {
			case  1: S = "Отчет по водителю " + sComboEdit1->Text +
							  " за период с " + sDateEdit1->Text + " по " + sDateEdit2->Text;
						if (sCheckBox1->Checked || sCheckBox1->Checked || sCheckBox3->Checked ) {
							S += "(частичный)";
						}
						break;
			case 21: if (sCheckBox1->Checked) S = "Выборочно";
						break;
			case 22: if (sCheckBox2->Checked) S = "Выборочно";
						break;

		}
		MV->Text = S;
		return;
	}
	if (FName.Pos("Picture")) {
		TfrxPictureView* PV = dynamic_cast<TfrxPictureView *>(frxReport1->FindObject(FName));
		if (!PV || !PV->Tag) return;
		bool En = false;
		int IVal;
		AnsiString S;
		switch (PV->Tag) {
			case  1:
						break;
		}
		PV->Visible = En;
		return;
	}
	if (FName.Pos("Line")) {
		TfrxLineView* Lin = dynamic_cast<TfrxLineView *>(frxReport1->FindObject(FName));
		if (!Lin || !Lin->Tag) return;
		Lin->Visible = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::DBEditExit(TObject *Sender)
{
	EditExitStd(*WrkGData,Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::DBEditEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_RETURN) {
		if (DBDateTimeEditEh->Visible) {
			DBDateTimeEditEh->CloseUp(true);
			TDateTime DateSet = DBDateTimeEditEh->Value;
			if (DateSet < DT_Beg || DateSet > DT_End) {
				OutputMessage("Дата должна находится в диапазоне " + sDateEdit1->Text + " - " + sDateEdit2->Text);
				DBDateTimeEditEh->DropDown();
				return;
         }
		}
	}
	EditKeyDownStd(*WrkGData,Sender,Key,Shift);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch(Key) {
		case VK_ESCAPE: switch (PageTag) {
								 case 3: ShowMemoStd(GDataMonInp,  sMemo1); break;
								 case 4: ShowMemoStd(GDataMonOut,  sMemo2); break;
							 }
							 break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sMemoExit(TObject *Sender)
{
	WriteMemo();
}
//---------------------------------------------------------------------------

