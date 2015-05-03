//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "DModT.h"
#include "ComProc.h"

#include "FrmDriverGraphDay.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBCtrlsEh"
#pragma link "sComboBox"
#pragma link "sLabel"
#pragma link "sEdit"
#pragma link "sButton"
#pragma resource "*.dfm"
TFormDriverGraphDay *FormDriverGraphDay;
//---------------------------------------------------------------------------
__fastcall TFormDriverGraphDay::TFormDriverGraphDay(TComponent* Owner, AnsiString FIO, int DriverID, TDateTime DT_Wrk)
	: TForm(Owner)
{
	 this->FIO      = FIO;
	 this->DriverID = DriverID;
	 this->DT_Wrk   = DT_Wrk;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::FormCreate(TObject *Sender)
{
	InitCommon();
	ProcRefresh();
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::InitCommon()
{
	Caption = "Режим работы водителя "+FIO + " на " + GetDateStr(DT_Wrk);
	sEdit1->Text = "";
	sComboBox1->ItemIndex = 0;
	GData.WrkQuery = Query2;
	GData.WrkDBase = DModT->Database1;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::ProcRefresh()
{
	AnsiString SQL  = "Select * from Driver_Graph where Dt_Driver_Wrk ='" + GetDateStr(DT_Wrk) +
							"' and Driver_Id = " + IntToStr(DriverID);
	Query1->SQL->Text = SQL;
	if (OpenDSetStd(Query1)) {
		if (!Query1->FieldByName("Driver_ID")->IsNull) {
			sComboBox1->ItemIndex    = Query1->FieldByName("Flag_Wrk")->AsInteger;
			DBDateTimeEditEh1->Value = Query1->FieldByName("DT_Out_Beg")->AsDateTime;
			DBDateTimeEditEh2->Value = Query1->FieldByName("DT_Out_End")->AsDateTime;
			sEdit1->Text             = Query1->FieldByName("COMMENT")->AsString;
		}
		else {
			DBDateTimeEditEh1->Value = DT_Wrk;
			DBDateTimeEditEh2->Value = DT_Wrk+1;
		}
		SetControls(Query1->FieldByName("FLAG_WRK")->AsInteger);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::SetControls(int Flag_Wrk)
{
	bool En1, En2;
	switch (Flag_Wrk) {
		case 0:  En1 = false; En2 = false; break;  // рабочий
		case 1:  En1 = false; En2 = false; break;  // выходной
		case 2:  En1 = false; En2 = true; break;  // выходной до
		case 3:  En1 = true;  En2 = true;  break;  // выходной с - по
		case 4:  En1 = true;  En2 = false; break;  // выходной после
		case 5:  En1 = true;  En2 = true;  break;  // рабочие часы
		default: En1 = false; En2 = false; break;
	}
	DBDateTimeEditEh1->Enabled = En1;	DBDateTimeEditEh1->Visible = En1;
	DBDateTimeEditEh2->Enabled = En2;	DBDateTimeEditEh2->Visible = En2;
	sLabel1 ->Visible = En2 && Flag_Wrk != 2;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::sComboBox1CloseUp(TObject *Sender)
{
	SetControls(sComboBox1->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::sComboBox1Exit(TObject *Sender)
{
//	 SetControls(sComboBox1->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::sComboBox1KeyDown(TObject *Sender, WORD &Key,
			 TShiftState Shift)
{
	switch(Key) {
		case VK_ESCAPE: if (sComboBox1->DroppedDown) {
								 sComboBox1->DroppedDown = false;
							 }
							 else if (sComboBox1->ItemIndex == Query1->FieldByName("FLAG_WRK")->AsInteger) {
								 ModalResult = mrCancel;
								 break;
							 }
							 sComboBox1->ItemIndex = Query1->FieldByName("FLAG_WRK")->AsInteger;
							 SetControls(sComboBox1->ItemIndex);
							 break;
		case VK_RETURN: SetControls(sComboBox1->ItemIndex);
							 if      (DBDateTimeEditEh1->Visible) DBDateTimeEditEh1->SetFocus();
							 else if (DBDateTimeEditEh2->Visible) DBDateTimeEditEh2->SetFocus();
							 else     sEdit1->SetFocus();
							 break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::DBDateTimeEditEh1KeyDown(TObject *Sender, WORD &Key,
			 TShiftState Shift)
{
	switch (Key) {
		case VK_ESCAPE: if (!Query1->FieldByName("Driver_ID")->IsNull) {
								 if (DBDateTimeEditEh1->Text != Query1->FieldByName("DT_Out_Beg")->AsDateTime.FormatString("hh:nn"))
									 DBDateTimeEditEh1->Value = Query1->FieldByName("DT_Out_Beg")->AsDateTime;
								 else
									 ModalResult = mrCancel;
							 }
							 else {
								 if (DBDateTimeEditEh1->Text  !=  "00:00")
									  DBDateTimeEditEh1->Value = DT_Wrk;
								 else
									  ModalResult = mrCancel;
							 }
							 break;
		case VK_RETURN: if (!Shift.Contains(ssCtrl)) {
								 if (DBDateTimeEditEh2->Visible) DBDateTimeEditEh2->SetFocus();
								 else sEdit1->SetFocus();
							 }
							 else sComboBox1->SetFocus();
							 break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::DBDateTimeEditEh2KeyDown(TObject *Sender, WORD &Key,
			 TShiftState Shift)
{
	switch (Key) {
		case VK_ESCAPE: if (!Query1->FieldByName("Driver_ID")->IsNull) {
								 if (DBDateTimeEditEh2->Text != Query1->FieldByName("DT_Out_End")->AsDateTime.FormatString("hh:nn"))
									 DBDateTimeEditEh2->Value = Query1->FieldByName("DT_Out_End")->AsDateTime;
								 else
									 ModalResult = mrCancel;
							 }
							 else {
								 if (DBDateTimeEditEh2->Text !=  "00:00")
									  DBDateTimeEditEh2->Value = DT_Wrk+1;
								 else
									  ModalResult = mrCancel;
							 }
							 break;
		case VK_RETURN: if (!Shift.Contains(ssCtrl)) {
								 sEdit1->SetFocus();
							 }
							 else if (DBDateTimeEditEh1->Visible) DBDateTimeEditEh1->SetFocus();
							 else sComboBox1->SetFocus();
							 break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::sEdit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key) {
		case VK_ESCAPE: if (sEdit1->Text != Query1->FieldByName("Comment")->AsString)
									 sEdit1->Text = Query1->FieldByName("Comment")->AsString;
							 else
									 ModalResult = mrCancel;
							 break;
		case VK_RETURN: if (!Shift.Contains(ssCtrl)) {
								 sButton1->SetFocus();
							 }
							 else {
								 if      (DBDateTimeEditEh2->Visible) DBDateTimeEditEh2->SetFocus();
								 else if (DBDateTimeEditEh1->Visible) DBDateTimeEditEh1->SetFocus();
								 else    sComboBox1->SetFocus();
							 }
							 break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::sButtonClick(TObject *Sender)
{
	switch (GetComponentTag(Sender)) {
		case 1: if (WriteData())
					  ModalResult = mrOk;
				  break;
		case 2: ModalResult = mrCancel;
				  break;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormDriverGraphDay::WriteData()
{
	int Flag_Wrk = sComboBox1->ItemIndex;
	AnsiString D1_S = GetDateStr(DT_Wrk);
	AnsiString D2_S = GetDateStr(DT_Wrk+1);
	TDateTime  DT1  = DBDateTimeEditEh1->Value;
	TDateTime  DT2  = DBDateTimeEditEh2->Value;
	switch (Flag_Wrk) {
		case 0:  break;  										// рабочий
		case 1:  break;  										// выходной
		case 2:  D2_S = D1_S + " " + DT2.FormatString("hh:nn"); // выходной до
					break;
		case 3:  D2_S = D1_S + " " + DT2.FormatString("hh:nn"); // выходной с - по Не переставлять !!
					D1_S = D1_S + " " + DT1.FormatString("hh:nn");
					break;
		case 4:  D1_S = D1_S + " " + DT1.FormatString("hh:nn"); // выходной после
					break;
		case 5:  D2_S = D1_S + " " + DT2.FormatString("hh:nn");  // рабочие часы
					D1_S = D1_S + " " + DT1.FormatString("hh:nn");

					break;
		default: return false;
	}
	if (TDateTime(D2_S) < TDateTime(D1_S)) {
		OutputMessage("Дата окончания - " + D2_S + " раньше даты начала периода - "+D1_S);
		return false;
	}
	AnsiString Сomment = sEdit1->Text;
	AnsiString DC_Str;
	Trunc(Query1,"COMMENT", Сomment);
	if (Сomment == "") Сomment = "null";
	else               Сomment = "'" + Сomment + "'";
	if (!Query1->FieldByName("Driver_ID")->IsNull)
		DC_Str = "'" + Query1->FieldByName("DateChange")->AsDateTime.FormatString("dd.mm.yy hh:nn:ss") + "'";
	else
		DC_Str = "null";
	AnsiString SQL = "select * from EDIT_DRIVER_GRAPH('" + GetDateStr(DT_Wrk) + "'," +
						  IntToStr(DriverID) + ",'" + D1_S +"','" + D2_S + "'," +
						  IntToStr(Flag_Wrk) + ","  +Сomment + "," + DC_Str + ",null)";
	Query2->SQL->Text = SQL;
	if (OpenExecQueryStd(GData))
		return true;
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TFormDriverGraphDay::sButton1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_ESCAPE) ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

