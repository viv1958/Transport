//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmPassWord.h"
#include "DModT.h"
#include "ComProc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sButton"
#pragma link "sEdit"
#pragma link "sLabel"
#pragma link "sPanel"
#pragma resource "*.dfm"
TFormPassWord *FormPassWord;
//---------------------------------------------------------------------------
__fastcall TFormPassWord::TFormPassWord(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TFormPassWord::TFormPassWord(TComponent* Owner,AnsiString Caption)
    : TForm(Owner)
{
   this->Caption = Caption;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetNoRightsMsg(int Lev)
{
	AnsiString Res;
	//??
	return Res;
}
//---------------------------------------------------------------------------
bool __fastcall CheckItem(int Lev,bool Out)
{
	bool Res = DModT->Empl_Rights & Lev;
	if (!Res && Out) {
	  AnsiString Msg = GetNoRightsMsg(Lev);
	  if (Msg == "") Msg = "Права доступа недостаточны.\nДействие не разрешено";
	  OutputMessage(Msg);
	}
	return Res;
}
//---------------------------------------------------------------------------
bool __fastcall ActionAllowedEx(int Lev,bool Out)
{
	TFormPassWord* Frm = new TFormPassWord(Application);
	bool Result  = false;
	if (Frm->ShowModal() == mrOk) {
	  Result = CheckItem(Lev,Out);
	}
	delete Frm;
	return Result;
}
//---------------------------------------------------------------------------
bool __fastcall ItemIsAllowedEx(int Lev,bool Out)
{
	bool Res = CheckItem(Lev,false);
	if (!Res && !ActionAllowedEx(Lev,Out)) {
	  return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormPassWord::sButton1Click(TObject *Sender)
{
	bool bRes = false;
	if (!Query1->Prepared)   Query1->Prepare();
	AnsiString LatText = GetLatinText(sEdit1->Text);
	AnsiString S = LatText.UpperCase();
	Query1->ParamByName("PASSWRD")->AsString = S;
	int FlagExit = 0;
	AnsiString Msg;
	if (ReOpenDSetStd(Query1)) {
	  FlagExit = Query1->FieldByName("Flag_Exit")->AsInteger;
	  int Cnt  = Query1->FieldByName("CNT")->AsInteger;
		switch (FlagExit) {
			case -1: Msg  = "Нет данных о пользователе с таким паролем"; break;
			case -2: Msg  = "В базе находятся "+IntToStr(Cnt)+" пользователей с таким паролем"; break;
			default: bRes = (Cnt == 1); break;
      }
	}
	if (bRes) {
		DModT->CurEmpID       = Query1->FieldByName("EMPLOYEE_ID")->AsInteger;
		DModT->Full_Name      = Query1->FieldByName("FULL_NAME")->AsString;
		DModT->Empl_Rights    = Query1->FieldByName("Empl_Rights")->AsInteger;
		ModalResult = mrOk;
	}
	else {
	  if (Msg != "") OutputMessage(Msg);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormPassWord::sButton2Click(TObject *Sender)
{
	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormPassWord::FormCreate(TObject *Sender)
{
	Top = (600-Height)/2; Left = (800-Width)/2;
}
//---------------------------------------------------------------------------
/*
bool __fastcall ItemIsAllowed(int Lev,AnsiString Msg)
{
	if (DModUjut->EmpLevel & Lev) return true;
	if (!ActionAllowed(Lev)) {
	  if (Msg == "")
		 Msg = "Права доступа недостаточны.\nДействие не разрешено";
      OutputMessage(Msg);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall ItemIsAllowed2(int Lev,AnsiString Msg)
{
   if (DModUjut->EmpLevel2 & Lev) return true;
   if (!ActionAllowed2(Lev)) {
      if (Msg == "")
         Msg = "Права доступа недостаточны.\nДействие не разрешено";
      OutputMessage(Msg);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall ActionAllowed(int Lev)
{
   TFormPassWord* Frm = new TFormPassWord(Application);
   bool Result  = false;
   if (Frm->ShowModal() == mrOk) {
      Result = DModUjut->EmpLevel & Lev;
   }
   delete Frm;
   return Result;
}
//---------------------------------------------------------------------------
bool __fastcall ActionAllowed2(int Lev)
{
   TFormPassWord* Frm = new TFormPassWord(Application);
   bool Result  = false;
   if (Frm->ShowModal() == mrOk) {
	  Result = DModUjut->EmpLevel2 & Lev;
   }
   delete Frm;
   return Result;
}
*/
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
