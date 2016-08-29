//---------------------------------------------------------------------------
#include <vcl.h>
#include "DModT.h"
#include "ComProc.h"
#pragma hdrstop

#include "FrmSummaryRep.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAxisGridsEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "DBGridEhToolCtrls"
#pragma link "GridsEh"
#pragma link "sCheckBox"
#pragma link "sComboBox"
#pragma link "sComboEdit"
#pragma link "sCustomComboEdit"
#pragma link "sLabel"
#pragma link "sMaskEdit"
#pragma link "sPageControl"
#pragma link "sPanel"
#pragma link "sSpeedButton"
#pragma link "sStatusBar"
#pragma link "sTooledit"
#pragma link "ToolCtrlsEh"
#pragma link "DataDriverEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma resource "*.dfm"
TFormSummaryRep *FormSummaryRep;
void ShowSummaryReport(int SelIndex)
{
	TFormSummaryRep* Form = new TFormSummaryRep(Application, SelIndex);
	Form->Show();
}

//---------------------------------------------------------------------------
__fastcall TFormSummaryRep::TFormSummaryRep(TComponent* Owner, int SelIndex)
	: TForm(Owner)
{
	this->SelIndex = SelIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::FormCreate(TObject *Sender)
{
	sPageControl1->ActivePage = (!SelIndex) ? sTabSheet1 : sTabSheet2;
	InitCommon();
	InitGData();
	SetPage();
	ProcRefreshPage();
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::InitCommon()
{
	SetFormPosStd(this,Screen->Width,750,0,true);

	TDateTime DT = Date();
	SelYY = MaxYY = CurYY = StrToInt(DT.FormatString("yy"));
	SelMM = MaxMM = CurMM = StrToInt(DT.FormatString("m"));
	SetDates(CurMM, CurYY);
	SetButtonCaption(CurMM);
	SetColumns();
	ToggleShowCost(false);
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::SetDates(int MM,int YY)
{
	DT_Beg = "01."+IntToStr(MM) + "." + IntToStr(YY);
	DT_End = DT_Beg + 32;
	DT_End = "01."+DT_End.FormatString("mm.yy");
	--DT_End;
	sDateEdit1->Date = DT_Beg;
	sDateEdit2->Date = DT_End;
}
static AnsiString MonList[] =
	 {"Ќо€брь","ƒекабрь","январь","‘евраль","ћарт","јпрель","ћай","»юнь","»юль",
	  "јвгуст","—ент€брь","ќкт€брь","Ќо€брь","ƒекабрь","январь","‘евраль"};
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::SetButtonCaption(int Mon)
{
	Mon +=1;
	sSpeedButton34->Caption = MonList[Mon];
	sSpeedButton33->Caption = MonList[Mon-1];
	sSpeedButton32->Caption = MonList[Mon-2];
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::SetColumns()
{
	int Year_B = StrToInt(DT_Beg.FormatString("yyyy"));
	int Mont_B = StrToInt(DT_Beg.FormatString("m"));
	int Year_E = StrToInt(DT_End.FormatString("yyyy"));
	int Mont_E = StrToInt(DT_End.FormatString("m"));
	int N_Columns = (Year_E - Year_B)*2014 + Mont_E - Mont_B;

	TDBGridColumnsEh* Columns = DBGridEh1->Columns;
	int N_Mon = Mont_B + 1;
	int Year_C = Year_B;
	for (int i = 1; i < 13; ++i) {
		if (N_Mon == 14) {
			++Year_C;
			N_Mon = 2;
		}
		AnsiString S = MonList[N_Mon];
		if (S.Length() <= 6) {
			S = "    " + S + "    ";
		}
		Columns->Items[i]->Title->Caption = S + " " + IntToStr(Year_C);
		Columns->Items[i]->Visible = (i < N_Columns + 2);
		++N_Mon;
	}
	Columns->Items[13]->Visible  = N_Columns > 0;

	Columns = DBGridEh2->Columns;
	N_Mon  = Mont_B + 1;
	Year_C = Year_B;
	for (int i = 1; i < 13; ++i) {
		if (N_Mon == 14) {
			++Year_C;
			N_Mon = 2;
		}
		for (int j = 0; j < 3; j++) {
			int N_Col = i*3 + j - 1;
			AnsiString S = Columns->Items[N_Col]->Title->Caption;
			Columns->Items[N_Col]->Title->Caption = SetPiece(S,MonList[N_Mon] + " " + IntToStr(Year_C),"|",1);
			Columns->Items[N_Col]->Visible = (i < N_Columns + 2);
		}
		++N_Mon;
	}
	Columns->Items[38]->Visible = N_Columns > 0;
	Columns->Items[39]->Visible = N_Columns > 0;
	Columns->Items[40]->Visible = N_Columns > 0;

}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::InitGData()
{
// ==== заказы =================================================================
	GDataClient.Flags =	STD_STATUSBAR  | CAN_SEE_DELETED     | INC_SEARCH   | FILTER_BY_NAME      |
								MULTIPLE_SEL   | MOVE_DOWN_AFTER_SEL;

	GDataClient.WrkSBar = sStatusBar1;
	GDataClient.FieldKey      = "Client_ID";

	GDataClient.SetSQL        = SetSQL;
	GDataClient.FunAddRow     = AddCurrentRow;


	GDataClient.SrcDSet       = Query1;
	GDataClient.WrkGrid       = DBGridEh1;
	GDataClient.WrkDBase      = DModT->Database1;

	GDataClient.FilterFldMask = 1;


// ==== расходы ================================================================
	GDataTransp.Flags         =  STD_STATUSBAR  | CAN_SEE_DELETED     | INC_SEARCH   | FILTER_BY_NAME      |
										  MULTIPLE_SEL   | MOVE_DOWN_AFTER_SEL;

	GDataTransp.WrkSBar       = sStatusBar1;
	GDataTransp.FieldKey      = "Transport_ID";

	GDataTransp.SetSQL        = SetSQL;
	GDataTransp.FunAddRow     = AddCurrentRow;

	GDataTransp.SrcDSet       = Query2;
	GDataTransp.WrkGrid       = DBGridEh2;
	GDataTransp.WrkDBase      = DModT->Database1;

	GDataTransp.FilterFldMask = 0x0003;

}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::FormClose(TObject *Sender, TCloseAction &Action)
{
//
}
void __fastcall TFormSummaryRep::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key) {
		case VK_F5:  ProcRefreshPage();
						 break;
	}
	FormKeyDownStd(*WrkGData,Key,Shift);

}
//---------------------------------------------------------------------------
bool __fastcall TFormSummaryRep::SetSQL(TDataSet* DSet)
{
	AnsiString SQL, Tail;
	switch (DSet->Tag) {
		case 1:  SQL = "select * from Sel_Clients_Summary('" + GetDateStr(DT_Beg) +
							"','" + GetDateStr(DT_End+1) + "') order by Flag_Mes, Client_Name";
					Query1->SQL->Text = SQL;
					break;
		case 2:  SQL = "select * from Sel_Transport_Summary('" + GetDateStr(DT_Beg) +
							"','" + GetDateStr(DT_End+1) + "') order by Flag_Mes, Transport_Name";
					Query2->SQL->Text = SQL;
					break;

	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::EnableControls()
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::CloseAll()
{
	MemTableEh1->Active = false;
	MemTableEh2->Active = false;
	ProcUnsAllStd(GDataClient, NULL);
	ProcUnsAllStd(GDataTransp, NULL);
	ClearSums(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::ProcRefreshPage()
{
	SavePosStd(*WrkGData);
	CloseAll();
	ProcRefreshStd(*WrkGData,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::sSpeedButtonClick(TObject *Sender)
{
	switch (GetComponentTag(Sender)) {
		case  1:	ProcRefreshPage();                   break;
		case  4: ClearSums(PageTag);
					ProcUnsAllStd(*WrkGData, NULL);
					ProcSelAllStd(*WrkGData, NULL);
					break;
		case  5: ClearSums(PageTag);
					ProcUnsAllStd(*WrkGData, NULL);
					break;
		case  6: //OutReport(false);
					break;
		case  7: //OutReport(true);
					break;
		case  8: //ProcHistory(false);
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
void __fastcall TFormSummaryRep::ShowMonth(int Shift)
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
	// и не превышают текущего мес€ца
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
		SetColumns();
		ProcRefreshPage();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::sDateEditAcceptDate(TObject *Sender, TDateTime &aDate,
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
		 SetColumns();
		 ProcRefreshPage();
	 }
}
//---------------------------------------------------------------------------
GridData& __fastcall TFormSummaryRep::GetGDataRef(TObject* Sender)
{
	GridData* Ref = WrkGData;
	switch (GetComponentTag(Sender)) {
		case 1: Ref = &GDataClient; 	break;
		case 2: Ref = &GDataTransp; 	break;
	}
	return *Ref;
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::sPageControl1Change(TObject *Sender)
{
	SetPage();
	OpenDSetStd(*WrkGData);
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::DBGridEhEnter(TObject *Sender)
{
	WrkGData = &GetGDataRef(Sender);
	SetStatusBarStd(*WrkGData);
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::DBGridEhExit(TObject *Sender)
{
	int Cnt = sStatusBar1->Panels->Count;
	for (int i=0; i < Cnt; i++)
		sStatusBar1->Panels->Items[i]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::DBGridEh1GetCellParams(TObject *Sender, TColumnEh *Column,
			 TFont *AFont, TColor &Background, TGridDrawStateEh State)
{
	GetCellParamsStd(GetGDataRef(Sender),AFont,Background,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::DBGridEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	ProcKeyDownStd(GetGDataRef(Sender),Key);
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::DBGridEhKeyPress(TObject *Sender, System::WideChar &Key)
{
	ProcKeyPressStd(GetGDataRef(Sender),Key);
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::SetPage()
{
	PageTag = sPageControl1->ActivePage->Tag;
	WrkGData = &GetGDataRef(sPageControl1->ActivePage);
	EnableControls();
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::ShowLowFooter(TDBGridEh* Grid,TDataSet *DataSet, int Item)
{
	TColumnEh* Column = Grid->Columns->Items[Item];
	Column->Footers->Items[1]->Value = DataSet->FieldByName(Column->FieldName)->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::ShowLowFooter(TDataSet *DataSet)
{
	TDBGridColumnsEh* Columns;
	switch (DataSet->Tag) {
		case 1: Columns = DBGridEh1->Columns;
				  for (int i = 1; i < 14; i++) {
						TColumnEh* Column = Columns->Items[i];
						Column->Footers->Items[1]->Value = DataSet->FieldByName(Column->FieldName)->AsString;
				  }
				  break;
		case 2: Columns = DBGridEh2->Columns;
				  for (int i = 2; i < 41; i++) {
						TColumnEh* Column = Columns->Items[i];
						Column->Footers->Items[1]->Value = DataSet->FieldByName(Column->FieldName)->AsString;
				  }
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::ShowHighFooter(TDataSet *DataSet)
{
	TDBGridColumnsEh* Columns;
	switch (DataSet->Tag) {
		case 1: Columns = DBGridEh1->Columns;
				  for (int i = 1; i < 14; i++) {
					  Columns->Items[i]->Footers->Items[0]->Value = FloatToStr(Sum1[i]);
				  }
				  break;
		case 2: Columns = DBGridEh2->Columns;
				  for (int i = 2; i < 41; i++) {
					  Columns->Items[i]->Footers->Items[0]->Value = IntToStr(Sum2[i]);
				  }
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::ClearSums(int Tag)
{
	switch(Tag) {
		case 0: ClearSums(1);
				  ClearSums(2);
				  break;
		case 1: for (int i = 0; i < 14; i++) {
					  Sum1[i] = 0.0;
				  }
				  ShowHighFooter(GDataClient.WrkDSet);
				  break;
		case 2: for (int i = 0; i < 41; i++) {
					  Sum2[i] = 0;
				  }
				  ShowHighFooter(GDataTransp.WrkDSet);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::AddCurrentRow(GridData& GData,int Mul, bool Show, bool Clear)
{
//	bool Selected;
	TDataSet* DSet = GData.WrkDSet;
	if (Clear) {
		ClearSums(PageTag);
	}
	else {
		int ID;
		TDBGridColumnsEh* Columns;
		switch (PageTag) {
			case 1:	Columns = DBGridEh1->Columns;
						for (int i = 1; i < 14; i++) {
							Sum1[i] += Mul * DSet->FieldByName(Columns->Items[i]->FieldName)->AsFloat;
						}
						break;
			case 2:	Columns = DBGridEh2->Columns;
						for (int i = 2; i < 41; i++) {
							Sum2[i] += Mul * DSet->FieldByName(Columns->Items[i]->FieldName)->AsInteger;
						}
						break;
		}
		if (Show) ShowHighFooter(GData.WrkDSet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::MemTableEh1AfterClose(TDataSet *DataSet)
{
	AfterCloseStd(GetGDataRef(DataSet));
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::MemTableEh1AfterOpen(TDataSet *DataSet)
{
	RestorePosStd(GetGDataRef(DataSet),false);
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::MemTableEh1AfterScroll(TDataSet *DataSet)
{
	AfterScrollStd(GetGDataRef(DataSet));
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::MemTableEh1BeforeScroll(TDataSet *DataSet)
{
	BeforeScrollStd(GetGDataRef(DataSet));
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::MemTableEh1FilterRecord(TDataSet *DataSet, bool &Accept)
{
	if (!DataSet->FieldByName("FLAG_MES")->AsInteger) {
		Accept = false;
		ShowLowFooter(DataSet);
	}
	else
		Accept = FilterRecordStd(GetGDataRef(DataSet));

}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::sCheckBoxClick(TObject *Sender)
{
	TsCheckBox* CBox = dynamic_cast<TsCheckBox*>(Sender);
	switch (CBox->Tag) {
		case 1:	if (CBox->Checked) {
						WrkGData->Flags |= SHOW_SELECTED;
					}
					else {
						WrkGData->Flags ^= SHOW_SELECTED;
					}
					PulseFilterStd(*WrkGData);
					break;
		case 2: 	ToggleShowCost(CBox->Checked);
					break;
		case 3: 	DBGridEh2->AutoFitColWidths = !DBGridEh1->AutoFitColWidths;
					break;
	}

}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::ToggleShowCost(bool Show)
{
	 TDBGridColumnsEh* Columns = DBGridEh1->Columns;
	 AnsiString DF = "###0";
	 if (Show) DF += ".00";
	 for (int i = 1; i < 14; i++) {
		 Columns->Items[i]->DisplayFormat = DF;
	 }
}
//---------------------------------------------------------------------------
void __fastcall TFormSummaryRep::DBGridEh1SortMarkingChanged(TObject *Sender)
{
	TDBGridEh* DBGridEh = dynamic_cast<TDBGridEh*>(Sender);
	AnsiString s = " ";
	AnsiString SS;
	for (int i = 0; i < DBGridEh->SortMarkedColumns -> Count; ++i)  {
		TColumnEh* Column = DBGridEh->SortMarkedColumns->Items[i];
		SS = Column->FieldName;
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

