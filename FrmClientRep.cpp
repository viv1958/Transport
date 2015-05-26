//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DModT.h"
#include "ComProc.h"
#include "FrmSelSimpleEh.h"


#include "FrmClientRep.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAxisGridsEh"
#pragma link "DBCtrlsEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "DBGridEhToolCtrls"
#pragma link "GridsEh"
#pragma link "sCheckBox"
#pragma link "sComboEdit"
#pragma link "sCustomComboEdit"
#pragma link "sLabel"
#pragma link "sMaskEdit"
#pragma link "sMemo"
#pragma link "sPageControl"
#pragma link "sPanel"
#pragma link "sSpeedButton"
#pragma link "sStatusBar"
#pragma link "sTooledit"
#pragma link "ToolCtrlsEh"
#pragma link "DataDriverEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
void ShowClientReport(int ClientID, AnsiString ClientName)
{
	TFormClientRep* Form = new TFormClientRep(Application, ClientID, ClientName);
	Form->Show();
}

//---------------------------------------------------------------------------
__fastcall TFormClientRep::TFormClientRep(TComponent* Owner,int ClientID, AnsiString ClientName)
	: TForm(Owner)
{
	 this->ClientID   = ClientID;
	 this->ClientName = ClientName;
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::SetClient(int ClientID, AnsiString ClientName)
{
	if (ClientID != this->ClientID || !WrkGData->WrkDSet->Active)  {
		this->ClientID = ClientID;
		ProcRefreshPage();
	}
	sComboEdit1->Text = ClientName;
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::InitCommon()
{
	SetFormPosStd(this,Screen->Width,750,0,true);

	TDateTime DT = Date();
	SelYY = MaxYY = CurYY = StrToInt(DT.FormatString("yy"));
	SelMM = MaxMM = CurMM = StrToInt(DT.FormatString("m"));
	SetDates(CurMM, CurYY);
	SetButtonCaption(CurMM);
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::SetDates(int MM,int YY)
{
	DT_Beg = "01."+IntToStr(MM) + "." + IntToStr(YY);
	DT_End = DT_Beg + 32;
	DT_End = "01."+DT_End.FormatString("mm.yy");
	--DT_End;
	sDateEdit1->Date = DT_Beg;
	sDateEdit2->Date = DT_End;
}
static AnsiString MonList[] =
	 {"������","�������","������","�������","����","������","���","����","����",
	  "������","��������","�������","������","�������","������","�������"};
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::SetButtonCaption(int Mon)
{
	Mon +=1;
	sSpeedButton34->Caption = MonList[Mon];
	sSpeedButton33->Caption = MonList[Mon-1];
	sSpeedButton32->Caption = MonList[Mon-2];
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::InitGData()
{
// ==== ������ =================================================================
	GDataOrders.Flags =  STD_STATUSBAR | FILTER_BY_NAME | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL;
	GDataOrders.WrkSBar = sStatusBar1;
	GDataOrders.FieldKey      = "Orders_ID";

	GDataOrders.SetSQL        = SetSQL;
	GDataOrders.FunAddRow     = AddCurrentRow;

	GDataOrders.SrcDSet       = Query1;
	GDataOrders.WrkGrid       = DBGridEh1;
	GDataOrders.WrkDBase      = DModT->Database1;
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::FormCreate(TObject *Sender)
{
	sPageControl1->ActivePage = sTabSheet1;
	InitCommon();
	InitGData();
	SetPage();
	if (!ClientID)
	  SelectClient();
	else SetClient(ClientID,ClientName);

}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::FormClose(TObject *Sender, TCloseAction &Action)
{
//	WriteMemo();
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssAlt) || Shift.Contains(ssCtrl)) {
		TsTabSheet* NewSheet = NULL;
		switch (Key) {
			case '1': NewSheet = sTabSheet1; break;
//			case '2': NewSheet = sTabSheet2; break;
//			case '3': NewSheet = sTabSheet3; break;
//			case '4': NewSheet = sTabSheet4; break;
		}
		if (NewSheet && NewSheet != sPageControl1->ActivePage) {
			sPageControl1->ActivePage = NewSheet;
			SetPage();
		}
	}
	switch (Key) {
		case VK_F5:  ProcRefreshPage();
						 break;
		case VK_F11: ProcHistory(Shift.Contains(ssCtrl));
						 break;
	}
	FormKeyDownStd(*WrkGData,Key,Shift);
}
//---------------------------------------------------------------------------
bool __fastcall TFormClientRep::SetSQL(TDataSet* DSet)
{
	AnsiString SQL, Tail;
	switch (DSet->Tag) {
		case 1:  SQL = "select * from Sel_Orders_Client("  + IntToStr(ClientID) + ",'" +
							GetDateStr(DT_Beg) + "','" + GetDateStr(DT_End) + "')";
					Query1->SQL->Text = SQL;
					break;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::CloseAll()
{
	MemTableEh1->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::ProcRefreshPage()
{
	SavePosStd(*WrkGData);
	CloseAll();
	ProcRefreshStd(*WrkGData,true);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormClientRep::TranslateName(AnsiString FldName)
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
void __fastcall TFormClientRep::ProcHistory(bool All)
{
	AnsiString Title  = "�������� ������� ���������";
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
			TitleNames = ",N ������"  + TitleNames + ",���������";
		}
		else {
			FieldNames = FieldNames + ",STATUS";
			TitleNames = TitleNames + ",���������";
		}
		FieldNames  = FieldNames.SubString(2,1000);
		TitleNames  = TitleNames.SubString(2,1000);
		FieldNames = FieldNames.UpperCase();
		FieldNamesList->Add(FieldNames);
		TitleNamesList->Add(TitleNames);
		FieldNames = "";
		TitleNames = "";

		Title = Title + " ���� ������� �����";
	}
	else {
		TColumnEh* Column = Grid->Columns->Items[Grid->Col - 1];
		FieldNames = TranslateName(Column->FieldName);
		SS = Column->Title->Caption;
		TitleNames =  GetPiece(SS, "|",1);
		SS = GetPiece(SS, "|",2);
		if (SS != "")  TitleNames += "-> " + SS;
		Title = Title + " ���� > "+ TitleNames + " <";
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
void __fastcall TFormClientRep::sSpeedButton1Click(TObject *Sender)
{
	switch (GetComponentTag(Sender)) {
		case  1:	ProcRefreshPage();                   break;
		case  4: ProcSelAllStd(*WrkGData, NULL);	break;
		case  5: ClearSums();
					ProcUnsAllStd(*WrkGData, NULL);
					break;
		case  6: frxReport1->Print();
					break;
		case  7: PrintReport();
					break;
		case  8: ProcHistory(false);
					break;
		case 31: ShowMonth(-3);
					break;
		case 32: ShowMonth(-2);
					break;
		case 33: ShowMonth(-1);
					break;
		case 34: ShowMonth(0);
					break;
		case 35: ShowMonth(1);
					break;
	 }

}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::ShowMonth(int Shift)
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
	// ������ SelMM � SelYY ��������
	if ((MM > MaxMM && YY == MaxYY) || YY > MaxYY) {
		MM = MaxMM;
		YY = MaxYY;
	}
	// � �� ��������� �������� ������
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
void __fastcall TFormClientRep::sComboEdit1ButtonClick(TObject *Sender)
{
	SelectClient();
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::SelectClient()
{
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	int ID = ClientID;
	AnsiString SelectResultStr;
	if (SimpleSelEhClientID(this,0,ID,&SelectResultStr)) {
		SetClient(ID, GetPiece(SelectResultStr,"/",1));
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::sDateEditAcceptDate(TObject *Sender, TDateTime &aDate,
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
GridData& __fastcall TFormClientRep::GetGDataRef(TObject* Sender)
{
	GridData* Ref = WrkGData;
	switch (GetComponentTag(Sender)) {
		case 1: Ref = &GDataOrders; 	break;
	}
	return *Ref;
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::DBGridEhDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumnEh *Column, TGridDrawStateEh State)
{
	DrawColumnCellStd(GetGDataRef(Sender),Rect,DataCol,Column,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::DBGridEhEnter(TObject *Sender)
{
	WrkGData = &GetGDataRef(Sender);
	SetStatusBarStd(*WrkGData);
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::DBGridEhExit(TObject *Sender)
{
	int Cnt = sStatusBar1->Panels->Count;
	for (int i=0; i < Cnt; i++)
		sStatusBar1->Panels->Items[i]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::DBGridEhGetCellParams(TObject *Sender, TColumnEh *Column,
			 TFont *AFont, TColor &Background, TGridDrawStateEh State)
{
	GetCellParamsStd(GetGDataRef(Sender), AFont,Background,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::DBGridEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
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
void __fastcall TFormClientRep::DBGridEhKeyPress(TObject *Sender, System::WideChar &Key)
{
	ProcKeyPressStd(GetGDataRef(Sender),Key);
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::SetPage()
{
	PageTag = sPageControl1->ActivePage->Tag;
	WrkGData = &GetGDataRef(sPageControl1->ActivePage);
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::ShowLowFooter(TDBGridEh* Grid,TDataSet *DataSet, int Item)
{
	TColumnEh* Column = Grid->Columns->Items[Item];
	Column->Footers->Items[1]->Value = DataSet->FieldByName(Column->FieldName)->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::ShowLowFooter(TDataSet *DataSet)
{
	switch (DataSet->Tag) {
		case 1: ShowLowFooter(DBGridEh1, DataSet, 9);
				  ShowLowFooter(DBGridEh1, DataSet, 10);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::ShowHighFooter(TDataSet *DataSet)
{
	switch (DataSet->Tag) {
		case 1: DBGridEh1->Columns->Items[9]->Footers->Items[0]->Value = IntToStr(SumPayCalc);
				  DBGridEh1->Columns->Items[10]->Footers->Items[0]->Value = IntToStr(SumPayRes);
				  DBGridEh1->Columns->Items[10]->Footers->Items[0]->Value = IntToStr(SumPayAvc);
				  DBGridEh1->Columns->Items[10]->Footers->Items[0]->Value = IntToStr(SumPayRest);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::ClearSums()
{
	switch(PageTag) {
		case 1: SumPayCalc = SumPayRes = SumPayAvc = SumPayRest =  0;
//				  ShowSummary(DBGridEh1);
              ShowHighFooter(GDataOrders.WrkDSet);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::AddCurrentRow(GridData& GData,int Mul, bool Show, bool Clear)
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

						break;
		}
		if (Show) ShowHighFooter(GData.WrkDSet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormClientRep::PrintReport()
{
//	if (!MemTableEh1-Active) ProcRefreshStd(GDataOrders,true);
//	frxReport1->ShowReport(true);
	ProcRefreshPage();
}

