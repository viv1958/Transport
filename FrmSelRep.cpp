//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DModT.h"
#include "ComProc.h"
#include "FrmSelSimpleEh.h"


#include "FrmSelRep.h"
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
#pragma link "sComboBoxes"
#pragma link "sComboBox"
#pragma resource "*.dfm"
void ShowSelReport(int SelIndex, int SelID, AnsiString SelName)
{
	TFormSelRep* Form = new TFormSelRep(Application, SelIndex, SelID, SelName);
	Form->Show();
}

//---------------------------------------------------------------------------
__fastcall TFormSelRep::TFormSelRep(TComponent* Owner,int SelIndex, int SelID, AnsiString SelName)
	: TForm(Owner)
{
	 this->SelIndex   = SelIndex;
	 this->SelID      = SelID;
	 this->SelName    = SelName;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::FormCreate(TObject *Sender)
{
	sPageControl1->ActivePage = sTabSheet1;
	FillComboBoxTypeRep();
	InitCommon();
	InitGData();
	SetPage();
	if (!SelID)
	  SelectID();
	else SetSelID(SelID,SelName);

}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::SetSelID(int SelID, AnsiString SelName)
{
	if (SelID != this->SelID || !WrkGData->WrkDSet->Active)  {
		this->SelID = SelID;
		ProcRefreshPage();
	}
	sComboEdit1->Text = SelName;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::InitCommon()
{
//	SetFormPosStd(this,1300,750,0,true);
	SetFormPosStd(this,Screen->Width,750,0,true);
	sComboBox1->ItemIndex = SelIndex;
	TDateTime DT = Date();
	SelYY = MaxYY = CurYY = StrToInt(DT.FormatString("yy"));
	SelMM = MaxMM = CurMM = StrToInt(DT.FormatString("m"));
	SetDates(CurMM, CurYY);
	SetButtonCaption(CurMM);
	ToggleShowCost(false);
	SetGridColumns();

}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::SetDates(int MM,int YY)
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
void __fastcall TFormSelRep::SetButtonCaption(int Mon)
{
	Mon +=1;
	sSpeedButton34->Caption = MonList[Mon];
	sSpeedButton33->Caption = MonList[Mon-1];
	sSpeedButton32->Caption = MonList[Mon-2];
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::SetGridColumns()
{
	DBGridEh1->Columns->Items[4]->Visible  = SelIndex != 0;
	DBGridEh1->Columns->Items[8]->Visible  = SelIndex != 1;
	DBGridEh1->Columns->Items[10]->Visible = SelIndex != 1;
	DBGridEh1->Columns->Items[7]->Visible  = SelIndex != 2;
	DBGridEh1->Columns->Items[9]->Visible  = SelIndex != 3;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::InitGData()
{
// ==== заказы =================================================================
	GDataOrders.Flags =  STD_STATUSBAR | FILTER_BY_NAME | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL;
	GDataOrders.WrkSBar = sStatusBar1;
	GDataOrders.FieldKey      = "Orders_ID";

	GDataOrders.SetSQL         = SetSQL;
	GDataOrders.FunAddRow      = AddCurrentRow;
	GDataOrders.FilterFldMask = -1;

	GDataOrders.SrcDSet       = Query1;
	GDataOrders.WrkGrid       = DBGridEh1;
	GDataOrders.WrkDBase      = DModT->Database1;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::FormClose(TObject *Sender, TCloseAction &Action)
{
//	WriteMemo();
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
bool __fastcall TFormSelRep::SetSQL(TDataSet* DSet)
{
	AnsiString SQL, Tail;
	switch (DSet->Tag) {
		case 1:  SQL = "select * from Sel_Orders("  + IntToStr(SelIndex + 10) + ",'" +
							GetDateStr(DT_Beg) + "','" + GetDateStr(DT_End+1)       + "'," +	IntToStr(SelID) + ")";
					Query1->SQL->Text = SQL;
					break;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::CloseAll()
{
	MemTableEh1->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::ProcRefreshPage()
{
	SavePosStd(*WrkGData);
	CloseAll();
	if (SelID)
		ProcRefreshStd(*WrkGData,true);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormSelRep::TranslateName(AnsiString FldName)
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
void __fastcall TFormSelRep::ProcHistory(bool All)
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
void __fastcall TFormSelRep::sSpeedButton1Click(TObject *Sender)
{
	switch (GetComponentTag(Sender)) {
		case  1:	ProcRefreshPage();                   break;
		case  4: ProcSelAllStd(*WrkGData, NULL);	break;
		case  5: ClearSums();
					ProcUnsAllStd(*WrkGData, NULL);
					break;
		case  6: OutReport(false);
					break;
		case  7: OutReport(true);
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
void __fastcall TFormSelRep::ShowMonth(int Shift)
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
void __fastcall TFormSelRep::sComboEdit1ButtonClick(TObject *Sender)
{
	SelectID();
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::SelectID()
{
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	int ID = SelID;
	AnsiString SelectResultStr;
	int TransTypeId    = 0;
	int TransCompanyID = 0;
	switch (SelIndex) {
		 case 0:	if (SimpleSelEhClientID(this,0,ID,&SelectResultStr)) {
						 SetSelID(ID, GetPiece(SelectResultStr,"/",1));
					}
					break;
		 case 1:	if (SimpleSelEhTransportID(this,0,ID,TransTypeId, TransCompanyID,Params, &SelectResultStr)) {
						 SetSelID(ID, GetPiece(SelectResultStr,"/",1) + " -- " + GetPiece(SelectResultStr,"/",2) + " -- мест: " +
													  GetPiece(SelectResultStr,"/",3) + " -- " +  GetPiece(SelectResultStr,"/",4));
					}
					break;
		 case 2:	if (SimpleSelEhTransCompanyID(this,0,ID,0,&SelectResultStr)) {
						 SetSelID(ID, GetPiece(SelectResultStr,"/",1));
					}
					break;
		 case 3:	if (SimpleSelEhDriverID(this,0,ID,0,Params,&SelectResultStr)) {
						 SetSelID(ID, GetPiece(SelectResultStr,"/",1));
					}
					break;
		 case 4:	if (SimpleSelEhMoneyReceiverID(this,0,ID,Params,&SelectResultStr)) {
						 SetSelID(ID, GetPiece(SelectResultStr,"/",1));
					}
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::sDateEditAcceptDate(TObject *Sender, TDateTime &aDate,
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
GridData& __fastcall TFormSelRep::GetGDataRef(TObject* Sender)
{
	GridData* Ref = WrkGData;
	switch (GetComponentTag(Sender)) {
		case 1: Ref = &GDataOrders; 	break;
	}
	return *Ref;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::DBGridEhDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumnEh *Column, TGridDrawStateEh State)
{
	DrawColumnCellStd(GetGDataRef(Sender),Rect,DataCol,Column,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::DBGridEhEnter(TObject *Sender)
{
	WrkGData = &GetGDataRef(Sender);
	SetStatusBarStd(*WrkGData);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::DBGridEhExit(TObject *Sender)
{
	int Cnt = sStatusBar1->Panels->Count;
	for (int i=0; i < Cnt; i++)
		sStatusBar1->Panels->Items[i]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::DBGridEhGetCellParams(TObject *Sender, TColumnEh *Column,
			 TFont *AFont, TColor &Background, TGridDrawStateEh State)
{
	GetCellParamsStd(GetGDataRef(Sender), AFont,Background,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::DBGridEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
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
void __fastcall TFormSelRep::DBGridEhKeyPress(TObject *Sender, System::WideChar &Key)
{
	ProcKeyPressStd(GetGDataRef(Sender),Key);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::SetPage()
{
	PageTag = sPageControl1->ActivePage->Tag;
	WrkGData = &GetGDataRef(sPageControl1->ActivePage);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::ShowLowFooter(TDBGridEh* Grid,TDataSet *DataSet, int Item)
{
	TColumnEh* Column = Grid->Columns->Items[Item];
	Column->Footers->Items[1]->Value = DataSet->FieldByName(Column->FieldName)->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::ShowLowFooter(TDataSet *DataSet)
{
	switch (DataSet->Tag) {
		case 1: ShowLowFooter(DBGridEh1, DataSet, 12);
				  ShowLowFooter(DBGridEh1, DataSet, 13);
				  ShowLowFooter(DBGridEh1, DataSet, 15);
				  ShowLowFooter(DBGridEh1, DataSet, 18);
				  ShowLowFooter(DBGridEh1, DataSet, 21);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::ShowHighFooter(TDataSet *DataSet)
{
	switch (DataSet->Tag) {
		case 1: DBGridEh1->Columns->Items[12]->Footers->Items[0]->Value = IntToStr(SumPayCalc);
				  DBGridEh1->Columns->Items[13]->Footers->Items[0]->Value = IntToStr(SumPayRes);
				  DBGridEh1->Columns->Items[15]->Footers->Items[0]->Value = IntToStr(SumPayAvc);
				  DBGridEh1->Columns->Items[18]->Footers->Items[0]->Value = IntToStr(SumPayRest);
				  DBGridEh1->Columns->Items[21]->Footers->Items[0]->Value = IntToStr(SumIncome);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::ClearSums()
{
	switch(PageTag) {
		case 1: SumPayCalc = SumPayRes = SumPayAvc = SumPayRest = SumIncome  = 0;
				  ShowHighFooter(GDataOrders.WrkDSet);
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::AddCurrentRow(GridData& GData,int Mul, bool Show, bool Clear)
{
//	bool Selected;
	TDataSet* DSet = GData.WrkDSet;
	if (Clear) {
		ClearSums();
	}
	else {
		int ID;
		switch (PageTag) {
			case 1:	SumPayCalc += Mul*DSet->FieldByName("PAY_CALC")->AsInteger;
						SumPayRes  += Mul*DSet->FieldByName("PAY_RES")->AsInteger;
						SumPayAvc  += Mul*DSet->FieldByName("PAY_AVC")->AsInteger;
						SumPayRest += Mul*DSet->FieldByName("PAY_REST")->AsInteger;
						SumIncome  += Mul*DSet->FieldByName("INCOME")->AsInteger;
						break;
		}
		if (Show) ShowHighFooter(GData.WrkDSet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::OutReport(bool Preview)
{
	TfrxReport* Rep = frxReport1;
	switch (SelIndex) {
		case  0:	switch (sComboBox2->ItemIndex) {
						case 1: Rep = frxReport2; break;
						case 2: Rep = frxReport3; break;
					}
					break;
		case 2:  Rep = frxReport4;  break;
	}
	if (Preview)
		Rep->ShowReport(true);
	else
		Rep->Print();
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::sComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key) {
		case VK_ESCAPE: sComboBox1->ItemIndex = SelIndex;
							 break;
		case VK_RETURN: sComboEdit1->SetFocus();
							 break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::MemTableEh1AfterClose(TDataSet *DataSet)
{
	AfterCloseStd(GetGDataRef(DataSet));
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::MemTableEh1AfterOpen(TDataSet *DataSet)
{
	RestorePosStd(GetGDataRef(DataSet),false);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::MemTableEh1AfterScroll(TDataSet *DataSet)
{
	AfterScrollStd(GetGDataRef(DataSet));
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::MemTableEh1BeforeScroll(TDataSet *DataSet)
{
	BeforeScrollStd(GetGDataRef(DataSet));
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::MemTableEh1FilterRecord(TDataSet *DataSet, bool &Accept)
{
	if (MemTableEh1->FieldByName("ORDERS_ID")->IsNull) {
		Accept = false;
     ShowLowFooter(DataSet);

	}
	else
	  Accept = FilterRecordStd(GetGDataRef(DataSet));
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::sCheckBoxClick(TObject *Sender)
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
		case 3: 	DBGridEh1->AutoFitColWidths = !DBGridEh1->AutoFitColWidths;
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::ToggleShowCost(bool Show)
{
	 TDBGridColumnsEh* Columns = DBGridEh1->Columns;
	 AnsiString DF = "###0";
	 if (Show) DF += ".00";
	 Columns->Items[12]->DisplayFormat = DF;   // расчетная
	 Columns->Items[13]->DisplayFormat = DF;   // Итогоая
	 Columns->Items[18]->DisplayFormat = DF;   // Доплатить
	 Columns->Items[21]->DisplayFormat = DF;   // прибыль
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::sComboBoxCloseUp(TObject *Sender)
{
	if (SelIndex != sComboBox1->ItemIndex) {
		 SelIndex = sComboBox1->ItemIndex;
		 SelID    = 0;
		 sComboEdit1->Text = "";
		 CloseAll();
		 SetGridColumns();
		 SelectID();
		 FillComboBoxTypeRep();;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::FillComboBoxTypeRep()
{
	switch (SelIndex) {
		case  0: sComboBox2->Enabled = true;
					sComboBox2->Enabled = true;
					sComboBox2->AddItem("Полный",NULL);
					sComboBox2->AddItem("По тарифу", NULL);
					sComboBox2->AddItem("По договору", NULL);
					sComboBox2->ItemIndex = 0;
					break;
		default: sComboBox2->Enabled = false;
					sComboBox2->Enabled = false;
					sComboBox2->Clear();
					break;
	}
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormSelRep::GetReportTitle()
{
	AnsiString S,S1;
	S = "Отчет по ";
	switch(SelIndex) {
		case 0: S1 = "клиенту ";                break;
		case 1: S1 = "транспортному средству "; break;
		case 2: S1 = "транспортной компании ";  break;
		case 3: S1 = "водителю ";               break;
		case 4: S1 = "получателю денег ";       break;
	}
	S += S1 + sComboEdit1->Text +
		  " за период с " + sDateEdit1->Text + " по " + sDateEdit2->Text;
	if (sCheckBox1->Checked || GDataOrders.Filter != "") {
		S += "(частичный)";
	}
	return S;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormSelRep::GetWrkPeriodStr()
{
	AnsiString S = MemTableEh1->FieldByName("DT_BEG")->AsDateTime.FormatString("dd.mmm")  + " " +
						MemTableEh1->FieldByName("TIME_BEG")->AsDateTime.FormatString("hh:nn") + "-";
	if (!(MemTableEh1->FieldByName("Wrk_Minut")->AsInteger + MemTableEh1->FieldByName("Wrk_Day")->AsInteger)) {
		S += "???";
	}
	else {
		if (MemTableEh1->FieldByName("DT_BEG")->AsDateTime != MemTableEh1->FieldByName("DAY_END")->AsDateTime) {
			 S += MemTableEh1->FieldByName("DAY_END")->AsDateTime.FormatString("dd.mmm") + " ";
		}
		S += MemTableEh1->FieldByName("DT_END")->AsDateTime.FormatString("hh:nn");
	}
	return S;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormSelRep::GetFromToStr()
{
	AnsiString S, S1;

	S1 = MemTableEh1->FieldByName("BEG_TOWN_NAME")->AsString;
	if (S1 != "СПб") S = S1 + +", ";
	S +=  MemTableEh1->FieldByName("BEG_STREET_NAME")->AsString +", "  +
			MemTableEh1->FieldByName("BEG_ADDR_NAME")->AsString + "->\n";
	S1 =  MemTableEh1->FieldByName("END_TOWN_NAME")->AsString;
	if (S1 != "СПб") S += S1 + ", ";
	S +=  MemTableEh1->FieldByName("END_STREET_NAME")->AsString +", "  +
			MemTableEh1->FieldByName("END_ADDR_NAME")->AsString;
	if (MemTableEh1->FieldByName("RET_TO_START")->AsInteger)
	S += " и обратно";
	return S;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormSelRep::GetDriverNameStr()
{
	AnsiString S, S1, S2;
	S  = MemTableEh1->FieldByName("DRIVER_NAME")->AsString;
	S1 = GetPiece(S," ",2);
	if (S1 != "")  S1 = " " + S1.SubString(1,1) + ".";
	S2 = GetPiece(S," ",3);
	if (S2 != "")  S2 = S2.SubString(1,1) + ".";;
	S = GetPiece(S," ",1) + S1 + S2;
	return S;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::frxReport1BeforePrint(TfrxReportComponent *Sender)
{
	if (!Sender->Tag) return;
	AnsiString FName = Sender->Name;
	if (FName.Pos("Memo")) {
		TfrxMemoView* MV = dynamic_cast<TfrxMemoView *>(frxReport1->FindObject(FName));
		if (!MV || !MV->Tag) return;
		AnsiString S;
		switch (Sender->Tag) {
			case  1: S = GetReportTitle();
						break;
			case  2: S = GetWrkPeriodStr() + "\n"+ MemTableEh1->FieldByName("ORDER_STATE_STR")->AsString;
						break;
			case  3: S = MemTableEh1->FieldByName("WORK_TYPE_NAME")->AsString + "\n" +
							 MemTableEh1->FieldByName("CLIENT_NAME")->AsString;
						break;
			case  4: S = MemTableEh1->FieldByName("TRANS_COMPANY_NAME")->AsString + " " +
							 MemTableEh1->FieldByName("TRANSPORT_NAME")->AsString     + " " +
							 MemTableEh1->FieldByName("REG_NUMBER")->AsString;
						break;
			case  5: S = GetFromToStr();
						break;
			case  6: S = GetDriverNameStr();
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
AnsiString  __fastcall TFormSelRep::GetReportTextStr(TfrxReportComponent *Sender)
{
	AnsiString S;
	int Min;
	switch (Sender->Tag) {
		case  1: S = GetReportTitle();
					break;
		case  2: S = GetWrkPeriodStr();
					break;
		case  3: S = GetFromToStr();
					break;
		case  4: Min = MemTableEh1->FieldByName("WRK_MINUT")->AsInteger +
							MemTableEh1->FieldByName("Bef_Minut")->AsInteger;
					if (MemTableEh1->FieldByName("FLAG_CALC_INCOME")->AsInteger == 1) {
						TDateTime DT = MemTableEh1->FieldByName("TIME_MIN")->AsDateTime;
						int Min2 = StrToInt(DT.FormatString("h"))*60 + StrToInt(DT.FormatString("n")) +
									  MemTableEh1->FieldByName("Bef_Minut")->AsInteger;
						if (Min2 > Min) Min = Min2;
					}
					S = FloatToStrF(((Min*1.)/60. + MemTableEh1->FieldByName("WRK_DAY")->AsInteger*24),ffFixed, 13,2);
					break;
	}
	return S;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::frxReport2BeforePrint(TfrxReportComponent *Sender)
{
	if (!Sender->Tag) return;
	AnsiString FName = Sender->Name;
	if (FName.Pos("Memo")) {
		TfrxMemoView* MV = dynamic_cast<TfrxMemoView *>(frxReport2->FindObject(FName));
		if (!MV || !MV->Tag) return;
		MV->Text = GetReportTextStr(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::frxReport3BeforePrint(TfrxReportComponent *Sender)
{
	if (!Sender->Tag) return;
	AnsiString FName = Sender->Name;
	if (FName.Pos("Memo")) {
		TfrxMemoView* MV = dynamic_cast<TfrxMemoView *>(frxReport3->FindObject(FName));
		if (!MV || !MV->Tag) return;
		MV->Text = GetReportTextStr(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelRep::frxReport4BeforePrint(TfrxReportComponent *Sender)
{
	if (!Sender->Tag) return;
	AnsiString FName = Sender->Name;
	if (FName.Pos("Memo")) {
		TfrxMemoView* MV = dynamic_cast<TfrxMemoView *>(frxReport4->FindObject(FName));
		if (!MV || !MV->Tag) return;
		AnsiString S;
		switch (Sender->Tag) {
			case  1: S = GetReportTitle();
					break;
			case  2: S = GetWrkPeriodStr();
						break;
			case  3: S = GetFromToStr();
						break;
			case  4: S = GetDriverNameStr();
						break;
		}
		MV->Text = S;
		return;
	}
}
//---------------------------------------------------------------------------

