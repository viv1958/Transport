//---------------------------------------------------------------------------

#ifndef DModTr
#define DModTr
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include "sSkinManager.hpp"
#include "frxClass.hpp"
#include "frxExportText.hpp"
#include "frxExportXLS.hpp"
//---------------------------------------------------------------------------
class TDModT : public TDataModule
{
__published:	// IDE-managed Components
	TDatabase *Database1;
	TQuery *Query1;
	TStoredProc *StoredProc1;
	TsSkinManager *sSkinManager1;
	TfrxXLSExport *frxXLSExport1;
	TfrxSimpleTextExport *frxSimpleTextExport1;
	void __fastcall DataModuleCreate(TObject *Sender);
	void __fastcall Database1Login(TDatabase *Database, TStrings *LoginParams);
	void __fastcall DataModuleDestroy(TObject *Sender);
private:	// User declarations
public:
	int CurEmpID;
	int Empl_Rights;

	int DefTownID;
	int DefCompID;

	bool ForceClose;
	bool ClearMode;
	AnsiString Full_Name;
	AnsiString ComputerName;
	Variant ExApp,ExSheet;
public:		// User declarations
// -----------------------------
		__fastcall TDModT::TDModT(TComponent* Owner);
	void __fastcall Start();
	bool __fastcall CheckDateFormat();
	void __fastcall TerminateApplication();
	bool __fastcall SetInitialParams();
	bool __fastcall OpenMainDB();
	void __fastcall ClearCurrentEmployee();

	void __fastcall TDModT::WriteSpyMessage(int Table_Key, AnsiString Msg_Type,
		 AnsiString Table_Name, AnsiString Field_Name, AnsiString Msg_Text,
       AnsiString Comp_Name);
};
//---------------------------------------------------------------------------
extern PACKAGE TDModT *DModT;
//---------------------------------------------------------------------------
#endif
