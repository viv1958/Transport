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
#pragma resource "*.dfm"
void ShowDriverReport(int DriverID, AnsiString DriverName)
{
	TFormDriverRep* Form = new TFormDriverRep(Application);
	Form->SetDriver(DriverID,DriverName);
	Form->Show();
}
//---------------------------------------------------------------------------
__fastcall TFormDriverRep::TFormDriverRep(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::SetDriver(int DriverID, AnsiString DriverName)
{
	if (DriverID != this->DriverID) {
		this->DriverID = DriverID;
		sComboEdit1->Text = DriverName;
		ProcRefresh();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::FormCreate(TObject *Sender)
{
	InitCommon();
	InitGData();
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::InitCommon()
{
//	SetFormPosStd(this,Screen->Width,750,0,true);
	SetFormPosStd(this,1280,750,0,true);

	sPanel2->Width = Width/2;
	DBGridEh2->Height = sPanel2->Height/2;
	TDateTime DT = Date();
	SelYY = MaxYY = CurYY = StrToInt(DT.FormatString("yy"));
	SelMM = MaxMM = CurMM = StrToInt(DT.FormatString("m"));
	SetDates(CurMM, CurYY);
	SetButtonCaption(CurMM);
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
	  "Август","Сентябрь","Октябрь","Ноябрь","Декабрь","Январь"};
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
	GDataOrders.Flags =  STD_STATUSBAR | INC_SEARCH | FILTER_BY_NAME | MULTIPLE_SEL | MOVE_DOWN_AFTER_SEL;
	GDataOrders.WrkSBar = sStatusBar1;
	GDataOrders.FieldKey      = "Orders_ID";

	GDataOrders.SetSQL        = SetSQL;

	GDataOrders.SrcDSet       = Query1;
	GDataOrders.WrkGrid       = DBGridEh1;
	GDataOrders.WrkDBase      = DModT->Database1;

}
//---------------------------------------------------------------------------
bool __fastcall TFormDriverRep::SetSQL(TDataSet* DSet)
{
	AnsiString SQL;
	switch (DSet->Tag) {
		case 1:  SQL = "select * from Sel_orders_Driver("  + IntToStr(DriverID) + ",'" +
							GetDateStr(DT_Beg) + "','" + GetDateStr(DT_End) + "')";
					Query3->SQL->Text = SQL;
					break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::ProcRefresh()
{
   ProcRefreshStd(GDataOrders,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
//
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::FormClose(TObject *Sender, TCloseAction &Action)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sSpeedButtonClick(TObject *Sender)
{
	 switch (GetComponentTag(Sender)) {
		 case  1: ProcRefresh(); break;
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
void __fastcall TFormDriverRep::ShowMonth(int Shift)
{
	int MM = SelMM;
	int YY = SelYY;
	MM += Shift;
	if (MM < 0) {
		--YY;
		MM += 12;
	}
	else if (MM > 12) {
		++YY;
		MM -=12;
	}
	if ((MM > MaxMM && YY == MaxYY) || YY > MaxYY) {
		MM = MaxMM;
		YY = MaxYY;
	}
	if ((MM > CurMM && YY == CurMM) || YY > CurYY) {
		SelMM = CurMM = MM;
		SelYY = CurYY = YY;
	}
	else if ( (CurYY-YY)*12 + CurMM - MM > 2) {
		CurMM = MM + 2;
		if (CurMM > 12) {
			CurMM - 12;
			CurYY++;
		}
		SelMM = CurMM;
		SelYY = CurYY;
	}
	else {
		SelMM = MM;
		SelYY = YY;
	}
	TDateTime DT_B = "01."+IntToStr(SelMM) + "." + IntToStr(SelYY);
	TDateTime DT_E = DT_B + 32;
	DT_E = "01."+DT_E.FormatString("mm.yy");
	--DT_E;
	if (DT_B != DT_Beg || DT_E != DT_End) {
		SetButtonCaption(CurMM);
		SetDates(SelMM, SelYY);
		ProcRefresh();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverRep::sComboEdit1ButtonClick(TObject *Sender)
{
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	int ID = DriverID;
	AnsiString SelectResultStr;
	if (SimpleSelEhDriverID(this,0,DriverID,0,Params,&SelectResultStr)) {
		if (ID != DriverID) {
			sComboEdit1->Text = GetPiece(SelectResultStr,"/",1);
			ProcRefresh();
		}
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
		 ProcRefresh();
	 }
}
//---------------------------------------------------------------------------

