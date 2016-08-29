//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DModT.h"
#include "ComProc.h"

#include "FrmOrderCopy.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sPanel"
#pragma link "acAlphaHints"
#pragma link "sLabel"
#pragma link "DataDriverEh"
#pragma link "DBAxisGridsEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "DBGridEhToolCtrls"
#pragma link "GridsEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "ToolCtrlsEh"
#pragma link "sCheckBox"
#pragma link "sSpeedButton"
#pragma resource "*.dfm"
TFormOrderCopy *FormOrderCopy;
//---------------------------------------------------------------------------
__fastcall TFormOrderCopy::TFormOrderCopy(TComponent* Owner, int SrcOrderID)
	: TForm(Owner)
{
	this->SrcOrderID = SrcOrderID;
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::FormCreate(TObject *Sender)
{
   Caption = Caption + " N " + IntToStr(SrcOrderID);
	SetFormPosStd(this,770,600,0,false);
	InitData();
	if (OpenDSetStd(Query1)) {
		TMemTableEh* Arr[12] = {MemTableEh1,  MemTableEh2,  MemTableEh3,  MemTableEh4,
										MemTableEh5,  MemTableEh6,  MemTableEh7,  MemTableEh8,
										MemTableEh9,  MemTableEh10, MemTableEh11, MemTableEh12 };
		for (int i = 0; i < 12; i++) {
			Arr[i]->LoadFromDataSet(Query1,-1,Memtableeh::lmCopy,false);
		}
	}
	ShowExistngCopies();
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::InitData()
{
	Today = Date();
	NCopy = 0;
	DTBeg = Date() + 400;
	CreateVect();
	FillMonthPanels();
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::FillMonthPanels()
{
	CurMonth = StrToInt(Today.FormatString("m"));
//	int Mon  = CurMonth;
	AnsiString MonthStr = "Январь,Февраль,Март,Апрель,Май,Июнь,Июль,Август,Сентябрь,Октябрь,Ноябрь,Декабрь";
	TsCheckBox* Arr[] = { sCheckBox1, sCheckBox2, sCheckBox3, sCheckBox4,  sCheckBox5,  sCheckBox6,
								 sCheckBox7, sCheckBox8, sCheckBox9, sCheckBox10, sCheckBox11, sCheckBox12 };
	for (int i = 0; i < 12; i++) {
		int Shift = (i+CurMonth - 1)%12 + 1;
		Arr[i]->Caption = GetPiece(MonthStr,",",Shift);
		Arr[i]->SkinData->CustomFont = true;
		Arr[i]->Font->Color = clBlue;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::ShowExistngCopies()
{
	Query2->SQL->Text = "select Orders_id,DT_Beg,Status from orders where  Src_Order_ID = " + IntToStr(SrcOrderID);
	if (OpenDSetStd(Query2)) {
		while (!Query2->Eof) {
			int OrderID = Query2->FieldByName("Orders_Id")->AsInteger;
			if (Query2->FieldByName("Orders_Id")->AsInteger < 0) {
				OrderID = -OrderID;
			}
			TDateTime DT = TDateTime(GetDateStr(Query2->FieldByName("DT_BEG")->AsDateTime));
			DateOrd.insert(pair<TDateTime,int>(DT,OrderID));
			Query2->Next();
		}
	}
	Query2->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::FormClose(TObject *Sender, TCloseAction &Action)
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	//
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::CreateVect()
{
	TDBGridEh* GArr[12] 	= {DBGridEh1,  DBGridEh2,  DBGridEh3,  DBGridEh4,
									DBGridEh5,  DBGridEh6,  DBGridEh7,  DBGridEh8,
									DBGridEh9,  DBGridEh10, DBGridEh11, DBGridEh12 };

	GridsArr.insert(GridsArr.begin(), GArr, GArr+12);

	TsPanel* PArr[] 		= {sPanel1,  sPanel2,  sPanel3,  sPanel4,
									sPanel5,  sPanel6,  sPanel7,  sPanel8,
									sPanel9, sPanel10,  sPanel11, sPanel12 };

	PanelArr.insert(PanelArr.begin(), PArr, PArr+12);
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::MemTableEhFilterRecord(TDataSet *DataSet, bool &Accept)
{
	Accept = DataSet->FieldByName("N_MON")->AsInteger == DataSet->Tag;
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::sCheckBoxClick(TObject *Sender)
{
	TsCheckBox* CBox = dynamic_cast<TsCheckBox*>(Sender);
	CBox->Font->Color = (CBox->Checked) ? clRed : clBlue;
	int Idx = CBox->Tag - 1;
	if (CBox->Checked) {
		SelGridNum = SetPiece(SelGridNum,"1","\\",CBox->Tag);
		PanelArr[Idx]->SkinData->CustomColor = true;
		PanelArr[Idx]->Color = clMoneyGreen;
	}
	else {
		SelGridNum = SetPiece(SelGridNum,"0","\\",CBox->Tag);
		PanelArr[Idx]->SkinData->CustomColor = false;
	}
	PanelArr[Idx]->Repaint();
}
//---------------------------------------------------------------------------
int __fastcall TFormOrderCopy::AnalyzeCellDT(TDateTime DT)
{
	int Res = 0;
	pair<multimap<TDateTime, int>::iterator, multimap<TDateTime, int>::iterator> ret;
	ret = DateOrd.equal_range(DT);
	if (ret.first == ret.second) return 0;
	for (multimap<TDateTime,int>::iterator it = ret.first; it != ret.second; ++it) {
		int OrderID = it->second;
		if      (!OrderID)     Res |= 0x0001;
		else if (OrderID > 0)  Res |= 0x0002;
		else                   Res |= 0x0004;
	}
	return Res;
}
//---------------------------------------------------------------------------
AnsiString TFormOrderCopy::GetOrdersList(TDateTime DT)
{
	AnsiString Res = "";
	pair<multimap<TDateTime, int>::iterator, multimap<TDateTime, int>::iterator> ret;
	ret = DateOrd.equal_range(DT);
	if (ret.first == ret.second) return 0;
	int i = 0;
	for (multimap<TDateTime,int>::iterator it = ret.first; it != ret.second; ++it) {
		int OrderID = it->second;
		if      (OrderID) {
			++i;
			if (OrderID > 0)  Res = SetPiece(Res,IntToStr(OrderID),",",i);
			else              Res = SetPiece(Res,IntToStr(OrderID)+" (Удален)",",",i);
		}
	}
	return Res;
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::DBGridEh1GetCellParams(TObject *Sender, TColumnEh *Column,
			 TFont *AFont, TColor &Background, TGridDrawStateEh State)
{
	TDBGridEh* Grid  = dynamic_cast<TDBGridEh*>(Sender);
	TDataSet*  DSet  = Grid->DataSource->DataSet;
	TField*    Fld   = DSet->FieldByName(Column->FieldName);

	if (State.Contains(Gridseh::gdFocused)) {
		Background   = clRed;
		AFont->Color = clWhite;
	}

	if (Fld->IsNull) return;

	TDateTime  DT    = Fld->AsDateTime;
	int        Stt = AnalyzeCellDT(DT);


	if (State.Contains(Gridseh::gdFocused)) {
		switch (Stt) {
			case 0x0000: Background   = clRed;
							 AFont->Color = clWhite;
							 break;
			case 0x0001: Background = TColor(RGB(178, 34, 34)); break; // Firebrick выбран
			case 0x0002:
			case 0x0004:
			case 0x0006: Background = TColor(RGB(255, 99, 71)); break; // Tomato
			default:     Background = clYellow; break;
		}
	}
	else {
		AFont->Color = clBlack;
//		if (DT > Today || sCheckBox21->Checked || (DT == Today && sCheckBox20->Checked)) {
			switch (Stt) {
				case 0x0000: if (!(DT > Today || sCheckBox21->Checked || (DT == Today && sCheckBox20->Checked)) )
									 Background = TColor(RGB(207, 207, 207)); 	  	// gray81
								 break;
				case 0x0001: Background = TColor(RGB(30,  144, 255)); break;  	// DodgerBlue выбран
				case 0x0002: Background = TColor(RGB(64,  224, 208)); break;  	// Turquoise  уже есть
				case 0x0004: Background = TColor(RGB(173, 216, 230));  break;  // LightBlue  есть deleted
				case 0x0006: Background = TColor(RGB(0,   206, 209));  break;  // DarkTurquoise есть active и deleted
				default:     Background = clYellow; break;
			}
//		}
/*
		else {
			switch (Stt) {
				case 0x0000: Background = TColor(RGB(207, 207, 207)); break;  // gray81
				case 0x0001: Background = TColor(RGB(181, 181, 181)); break;  // grey71
				case 0x0002: Background = TColor(RGB(156, 156, 156)); break;  // grey61
				case 0x0004: Background = TColor(RGB(130, 130, 130)); break;  // grey51
				case 0x0006: Background = TColor(RGB(105, 105, 105)); break;  // grey41
				default:     Background = clYellow; break;
			}
		}
*/
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::DBGridEh1TitleBtnClick(TObject *Sender, int ACol,
			 TColumnEh *Column)
{
	int Tag = GetComponentTag(Sender);
	TDBGridEh* Grid = GridsArr[Tag-1];
	TDataSet*  DSet = Grid->DataSource->DataSet;

	Grid->DataSource->Enabled = false;
	int Row  = DSet->FieldByName("N_ROW")->AsInteger;
	DSet->First();
	AnsiString FName = Column->FieldName;
	while (!DSet->Eof) {
		for (int i = 0; i < 7; i++) {
			TField* Fld = DSet->FieldByName(FName);
			if (!Fld->IsNull) {
				TDateTime DT = Fld->AsDateTime;
				if (DT > Today || sCheckBox21->Checked || (DT == Today && sCheckBox20->Checked)) {
					int Stt = AnalyzeCellDT(DT);
					switch (Stt) {
						case 0: DateOrd.insert(pair<TDateTime, int>(DT,0));
								  break;
						case 1: DateOrd.erase(DT);
								  break;
					}
				}
			}
		}
		DSet->Next();
	}
	DSet->Locate("N_Row",Row,TLocateOptions()<< loPartialKey << loCaseInsensitive);
	Grid->DataSource->Enabled = true;
	Grid->Repaint();


}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::DBGridEh1DblClick(TObject *Sender)
{
	int Tag = GetComponentTag(Sender);
	TDBGridEh* Grid = GridsArr[Tag-1];
	TDataSet*  DSet = Grid->DataSource->DataSet;
	int Col = Grid->Col;

	TField*    Fld   = DSet->FieldByName(Grid->Columns->Items[Col]->FieldName);
	if (Fld->IsNull) return;

	TDateTime DT = Fld->AsDateTime;
	if (DT > Today || sCheckBox21->Checked || (DT == Today && sCheckBox20->Checked)) {
		int State = AnalyzeCellDT(DT);
		switch (State) {
			case 0x0000 : DateOrd.insert(pair<TDateTime, int>(DT,0));
							  Grid->Repaint();
							  break;
			case 0x0001:  DateOrd.erase(DT);
							  Grid->Repaint();
							  break;
			default:      OutputMessage("На " + GetDateStr(DT) + " уже есть копия заказа " +
												  IntToStr(SrcOrderID)  + " : " + GetOrdersList(DT));
		}
	}
	else {
		if (DT == Today) {
			 OutputMessage("Копровать заказы на сегодня запрещено");
		}
		else {
			 OutputMessage("Копровать заказы на предыдущие дни запрещено");
      }
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::sSpeedButtonClick(TObject *Sender)
{
	switch (GetComponentTag(Sender)) {
		case 1: ClearSelDates();  break;
		case 2: ApplySelDates();  break;
		case 3: CopyOrders();     break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::ClearSelDates()
{
	DateOrd.clear();
	ShowExistngCopies();
	for (vector<TDBGridEh*>::iterator it = GridsArr.begin(); it != GridsArr.end(); ++it) {
		(*it)->Repaint();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::ApplySelDates()
{
	int i=0;
	for (vector<TsPanel*>::iterator iter = PanelArr.begin(); iter != PanelArr.end(); ++i,++iter) {
		if ((*iter)->Color == clMoneyGreen) {
			TDBGridEh* Grid = GridsArr[i];
			ApplySelDates(Grid);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::ApplySelDates(TDBGridEh* Grid)
{
	TDataSet*  DSet = Grid->DataSource->DataSet;
	Grid->DataSource->Enabled = false;
	int Row  = DSet->FieldByName("N_ROW")->AsInteger;
	DSet->First();
	bool Set[] = { sCheckBox13->Checked,  sCheckBox14->Checked,  sCheckBox15->Checked,  sCheckBox16->Checked,
						sCheckBox17->Checked,  sCheckBox18->Checked,   sCheckBox19->Checked};
	AnsiString FName[] = { "DD1", "DD2", "DD3", "DD4", "DD5", "DD6", "DD7" };
	while (!DSet->Eof) {
		for (int i = 0; i < 7; i++) {
			TField* Fld = DSet->FieldByName(FName[i]);
			if (!Fld->IsNull) {
				TDateTime DT = Fld->AsDateTime;
				if (DT > Today || sCheckBox21->Checked || (DT == Today && sCheckBox20->Checked)) {
					int Stt = AnalyzeCellDT(DT);
					switch (Stt) {
						case 0: if (Set[i]) DateOrd.insert(pair<TDateTime, int>(DT,0));
								  break;
						case 1: if (!Set[i]) DateOrd.erase(DT);
								  break;
					}
				}
			}
		}
		DSet->Next();
	}
	DSet->Locate("N_Row",Row,TLocateOptions()<< loPartialKey << loCaseInsensitive);
	Grid->DataSource->Enabled = true;
	Grid->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::CopyOrders()
{
	TDateTime DT_Prv;
	for (multimap<TDateTime,int>::iterator iter = DateOrd.begin(); iter != DateOrd.end(); ++iter) {
		if (!iter->second) {
			if (!CopyOrder(iter->first)) break;
		}
	}
	ClearSelDates();
}
//---------------------------------------------------------------------------
bool __fastcall TFormOrderCopy::CopyOrder(TDateTime DT)
{
	Query3->SQL->Text = "select * from Copy_Order(" + IntToStr(SrcOrderID)      + ",'" +
							  GetDateStr(DT) + "',1,0,"     + IntToStr(DModT->CurEmpID) + ",'" +
							  DModT->ComputerName + "')";
	bool bRes = ReOpenDSetStd(Query3);
	if (bRes) {
		int Result = Query3->FieldByName("Result")->AsInteger;
		if (Result <=0 ) {
			OutputMessage("Ошибка копирования заказа " + IntToStr(SrcOrderID) +
							  ". Код :" + IntToStr(Result));
			bRes = false;

		}
		else {
			NCopy++;
			if (DT > DTEnd) DTEnd = DT;
			if (DT < DTBeg) DTBeg = DT;
		}
	}
	return bRes;
}
//---------------------------------------------------------------------------
void __fastcall TFormOrderCopy::sCheckBoxShowClick(TObject *Sender)
{
	DBGridEh1->Repaint();
}
//---------------------------------------------------------------------------

