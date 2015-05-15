//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DModT.h"
#include "ComProc.h"
#include "FrmPassWord.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sSkinManager"
#pragma link "frxClass"
#pragma link "frxExportText"
#pragma link "frxExportXLS"
#pragma resource "*.dfm"
TDModT *DModT;
int AppTerminate;
//---------------------------------------------------------------------------
__fastcall TDModT::TDModT(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDModT::DataModuleCreate(TObject *Sender)
{
	Start();
	Application->HintPause     = 400;
	Application->HintHidePause = 20000;
}
//---------------------------------------------------------------------------
void __fastcall TDModT::Start()
{
	if (!CheckDateFormat() || !OpenMainDB()) {
	  TerminateApplication();
	}
	else if (!SetInitialParams()) {
	  TerminateApplication();
	}
}
//---------------------------------------------------------------------------
bool __fastcall TDModT::CheckDateFormat()
{
	if (Date().DateString() != Date().FormatString("dd.mm.yyyy")) {
	  OutputMessage("На вашем компьютере неверный формат даты.\n"
						 "Правильный формат даты: \"дд.мм.гггг\"");
	  return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TDModT::TerminateApplication()
{
	AppTerminate = 1;
	Application->Terminate();
}
//---------------------------------------------------------------------------
bool __fastcall TDModT::SetInitialParams()
{
	wchar_t Tmp[128];
	unsigned long sz = sizeof(Tmp);
	GetComputerName(Tmp,&sz);
	ComputerName = Tmp;
	Application->HintHidePause = 4000;
	Application->HintPause = 1000;

	if (!OpenDSetStd(Query1)) return false;

	if (Query1->FieldByName("CUR_DATE")->AsDateTime.DateString() != Date().DateString()) {
	  OutputMessage("Дата на вашем компьютере отличается от даты на сервере");
	  Query1->Close();
	  return false;
	}

	DefTownID = Query1->FieldByName("TOWN_ID")->AsInteger;
	DefCompID = Query1->FieldByName("TRANS_COMPANY_ID")->AsInteger;
	Query1->Close();

	if (!ActionAllowedEx(RGT_REGISTRY)) return false;
	WriteSpyMessage(NULL,NULL,NULL,NULL,"Регистрация "+Full_Name,1);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TDModT::OpenMainDB()
{
	return OpenDB(Database1,true);
}
//---------------------------------------------------------------------------
void __fastcall TDModT::ClearCurrentEmployee()
{
	CurEmpID     = -1;
	Empl_Rights  = 0;
	Full_Name    = "";
}
// ==========================================================================
//---------------------------------------------------------------------------
void __fastcall TDModT::Database1Login(TDatabase *Database, TStrings *LoginParams)

{
	AnsiString S = "S";
	LoginParams->Values["USERNAME"] = S+"Y"+S+"DBA";
	S = "m"; S = S+"a"; S = S+"ster";
	LoginParams->Values["PASSWORD"]  = S;
}
//---------------------------------------------------------------------------
void __fastcall TDModT::DataModuleDestroy(TObject *Sender)
{
	Database1->Close();
}
//----------------------------------------------------------------------------
void __fastcall TDModT::WriteSpyMessage(int Table_Key, AnsiString Msg_Type,
AnsiString Table_Name, AnsiString Field_Name, AnsiString Msg_Text,
AnsiString Comp_Name)
{
	try {
		if (!StoredProc1->Prepared) StoredProc1->Prepare();
		SetProcParamVal(StoredProc1,Table_Key,    "TABLE_KEY",   1, true);
		SetProcParamVal(StoredProc1,Msg_Type,     "MSG_TYPE",    2, true);
		SetProcParamVal(StoredProc1,Table_Name,   "TABLE_NAME",  2, true);
		SetProcParamVal(StoredProc1,Field_Name,   "FIELD_NAME",  2, true);
		SetProcParamVal(StoredProc1,Msg_Text,     "MSG_TEXT",    2, true);
		SetProcParamVal(StoredProc1,CurEmpID,     "EMPLOYEE_ID", 1,true);
		SetProcParamVal(StoredProc1,ComputerName, "COMP_NAME",   2,true);
		StoredProc1->ExecProc();
	}
	catch (Exception &E) {
//      OutputMessage(E.Message);
	}
}

