//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DModT.h"
#include "ComProc.h"

#include "FrmDriverGraph.h"
#include "FrmSelSimpleEh.h"
#include "FrmDriverGraphDay.h"
#include "FrmDateRange.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sComboEdit"
#pragma link "sCustomComboEdit"
#pragma link "sMaskEdit"
#pragma link "sPanel"
#pragma link "sComboBox"
#pragma link "sEdit"
#pragma link "sLabel"
#pragma link "sSpinEdit"
#pragma link "DataDriverEh"
#pragma link "DBAxisGridsEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "DBGridEhToolCtrls"
#pragma link "GridsEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "ToolCtrlsEh"
#pragma link "sSpeedButton"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFormDriverGraph::TFormDriverGraph(TComponent* Owner, int DriverID, AnsiString FIO)
	: TForm(Owner)
{
	 this->DriverID = DriverID;
	 while (int P = FIO.Pos(")")) FIO = FIO.SubString(P+1,1000);
	 this->FIO      = FIO;

}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::FormCreate(TObject *Sender)
{
	InitCommon();
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::InitCommon()
{
	sComboEdit1->Text = FIO;
	TDateTime DT = Date();
	CurMM = StrToInt(DT.FormatString("m"));     sComboBox1->ItemIndex = CurMM -1;
	CurYY = StrToInt(DT.FormatString("yyyy"));  sDecimalSpinEdit1->Value = CurYY;

// ===== Список поставщиков услуг ==============================================
	GData.Flags         = DONT_CHECK_KEY_ID | USE_SAVEPOSSTD;

	GData.FieldKey      = "WEEK_NUM";
//	GDataTransComp.FunAcceptRec  = AcceptRecord;

	GData.SrcDSet       = Query1;
	GData.WrkGrid       = DBGridEh1;
	GData.WrkDBase      = DModT->Database1;

	GData.WrkQuery      = Query2;
	GData.SetSQL        = SetSQL;

	GData.AddExtParam(ftInteger, "USER_ID",     DModT->CurEmpID);
	GData.AddExtParam(ftString,  "COMP_NAME",   DModT->ComputerName);
	if (DriverID) {
		ProcRefreshStd(GData,true);
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormDriverGraph::SetSQL(TDataSet* DSet)
{
	AnsiString SQL = "select * from SEL_DRIVER_GRAPH("+IntToStr(DriverID) + "," + IntToStr(CurYY) + "," + IntToStr(CurMM) + ")";
	Query1->SQL->Text = SQL;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::FormClose(TObject *Sender, TCloseAction &Action)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_ESCAPE) ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::sComboEdit1ButtonClick(TObject *Sender)
{
	AnsiString Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	AnsiString S;
	if (SimpleSelEhDriverID(this,Left,DriverID, 0,Params,&S)) {
		sComboEdit1->Text = GetPiece(S, "/", 1);
		ProcRefreshStd(GData,true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::sComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch(Key) {
		case VK_ESCAPE: sComboBox1->ItemIndex = CurMM -1;
							 break;
		case VK_RETURN: sDecimalSpinEdit1->SetFocus();
							 break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::sComboBox1Exit(TObject *Sender)
{
	if (sComboBox1->ItemIndex != CurMM - 1) {
		CurMM = sComboBox1->ItemIndex + 1;
		ProcRefreshStd(GData,true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::sDecimalSpinEdit1Exit(TObject *Sender)
{
	if ((int)sDecimalSpinEdit1->Value != CurYY) {
		CurYY = sDecimalSpinEdit1->Value;
		ProcRefreshStd(GData,true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::sDecimalSpinEdit1KeyDown(TObject *Sender, WORD &Key,
			 TShiftState Shift)
{
	switch(Key) {
		case VK_ESCAPE: sDecimalSpinEdit1->Value = CurYY;
							 break;
		case VK_RETURN: DBGridEh1->SetFocus();
							 break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::DBGridEh1DblClick(TObject *Sender)
{
	ProcReturn();
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::DBGridEh1GetCellParams(TObject *Sender, TColumnEh *Column,
			 TFont *AFont, TColor &Background, TGridDrawStateEh State)
{
	AnsiString FName = Column->FieldName;
	AnsiString S = MemTableEh1->FieldByName(FName)->AsString;
	if (S.Pos("Вых"))
		Background = TColor(RGB(240, 128, 128));
	GetCellParamsStd(GData, AFont,Background,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::DBGridEh1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) ProcReturn();
}
//---------------------------------------------------------------------------
TDateTime __fastcall TFormDriverGraph::GetDate()
{
	int Col = DBGridEh1->Col;
	AnsiString FName = "DAY_STR_"+IntToStr(Col);
	AnsiString Str   = MemTableEh1->FieldByName(FName)->AsString;
	TDateTime DT;
	if (Str == "") {
		if (DBGridEh1->Row == 1) Str = "01";
		else {
			DT = TDateTime("01." + IntToStr(CurMM) + "."+ IntToStr(CurYY));
			DT = DT + 32;
			while (StrToInt(DT.FormatString("m")) != CurMM)
				--DT;
		}
	}
   DT = TDateTime(GetPiece(Str," ",1) + "." + IntToStr(CurMM) + "."+ IntToStr(CurYY));
	return DT;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::ProcReturn()
{
	TDateTime DT = GetDate();

	TFormDriverGraphDay* Frm = new TFormDriverGraphDay(this, sComboEdit1->Text, DriverID, DT);
	if (Frm->ShowModal() ==  mrOk) {
		ProcRefreshStd(GData,true);
	}
	delete Frm;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::sSpeedButton1Click(TObject *Sender)
{
	if (!DriverID) return;
	UnicodeString S;
	TDateTime DT1 = GetDate();
	TDateTime DT2 = GetDate();
	if (GetDateRange(this,DT1,DT2)) {
		if (InputQuery(Caption,"Примечание: ", S)) {
			S = S.SubString(1,32);
			if (S == "") S = "null";
			else               S = "'" + S + "'";
			AnsiString SQL = "select * from SET_WEEKEND_DAY(" + IntToStr(DriverID) + ",'" +
						  DT1.FormatString("dd.mm.yy hh:nn") + "','" +
						  DT2.FormatString("dd.mm.yy hh:nn") + "',"  +  S + ")";
		  Query2->SQL->Text = SQL;
		  WriteDataStd(GData,false);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraph::sSpeedButton2Click(TObject *Sender)
{
	ProcRefreshStd(GData,true);
}
//---------------------------------------------------------------------------

