//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DModT.h"
#include "ComProc.h"


#include "FrmDateRange.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sButton"
#pragma link "sCustomComboEdit"
#pragma link "sLabel"
#pragma link "sMaskEdit"
#pragma link "sTooledit"
#pragma link "DBCtrlsEh"
#pragma resource "*.dfm"
TFormDateRange *FormDateRange;
bool GetDateRange(TComponent* Owner,TDateTime& DT1,TDateTime& DT2)
{
	TFormDateRange* Frm =  new TFormDateRange(Owner, DT1, DT2);
	if (Frm->ShowModal() == mrOk) {
		if (Frm->DT1 <= Frm->DT2) {
			DT1 = Frm->DT1;
			DT2 = Frm->DT2;
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------
__fastcall TFormDateRange::TFormDateRange(TComponent* Owner,TDateTime DT1,TDateTime DT2)
	: TForm(Owner)
{
	this->DT1 = DT1;
	this->DT2 = DT2;
}
//---------------------------------------------------------------------------
void __fastcall TFormDateRange::FormCreate(TObject *Sender)
{
	 DBDateTimeEditEh1->Value = DT1;
	 DBDateTimeEditEh2->Value = DT1;
	 DBDateTimeEditEh3->Value = DT2;
	 DBDateTimeEditEh4->Value = DT2;
}
//---------------------------------------------------------------------------
void __fastcall TFormDateRange::sButton1Click(TObject *Sender)
{
	 TDateTime D1  = DBDateTimeEditEh1->Value;
	 TDateTime D2  = DBDateTimeEditEh2->Value;
	 TDateTime D3  = DBDateTimeEditEh3->Value;
	 TDateTime D4  = DBDateTimeEditEh4->Value;

	 DT1 = D1.FormatString("dd.mm.yy") + " " + D2.FormatString("hh:nn");
	 DT2 = D3.FormatString("dd.mm.yy") + " " + D4.FormatString("hh:nn");
	 if (DT1 <= DT2) {
		 ModalResult = mrOk;
	 }
	 else {
		 AnsiString S1  = D1.FormatString("dd.mm.yy") + " " + D2.FormatString("hh:nn");
		 AnsiString S2  = D3.FormatString("dd.mm.yy") + " " + D4.FormatString("hh:nn");
		 OutputMessage("ƒата окончани€ - " + S2 + " раньше даты начала периода - " + S1);
	 }
}
//---------------------------------------------------------------------------
