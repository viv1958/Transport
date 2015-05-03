//---------------------------------------------------------------------------

#ifndef FrmPassWordH
#define FrmPassWordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "sButton.hpp"
#include "sEdit.hpp"
#include "sLabel.hpp"
#include "sPanel.hpp"
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
#define RGT_REGISTRY 				0xFFFF

#define RGT_SEE_TRANSPORT 			0x0001
#define RGT_EDIT_TRANSPORT 		0x0002
#define RGT_SEE_CLIENT 				0x0004
#define RGT_EDIT_CLIENT 			0x0008

#define RGT_SEE_ORDERS 				0x0010
#define RGT_EDIT_ORDERS 			0x0020
#define RGT_SEE_GRAPH 				0x0040
#define RGT_EDIT_GRAPH   			0x0080

#define RGT_SEE_INFO 				0x0100
#define RGT_EDIT_INFO 				0x0200
#define RGT_SEE_EMPLOYEE			0x0400
#define RGT_EDIT_EMPLOYEE			0x0800


class TFormPassWord : public TForm
{
__published:	// IDE-managed Components
	TsButton *sButton1;
	TsButton *sButton2;
	TQuery *Query1;
	TsLabel *sLabel1;
	TsEdit *sEdit1;
	void __fastcall sButton1Click(TObject *Sender);
	void __fastcall sButton2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	 __fastcall TFormPassWord(TComponent* Owner);
	 __fastcall TFormPassWord(TComponent* Owner,AnsiString Caption);
};

bool __fastcall  ActionAllowed(int Lev);
bool __fastcall  ItemIsAllowed(int Lev,AnsiString Msg);
bool __fastcall  ActionAllowedEx(int Lev,bool Out=true);
bool __fastcall  ItemIsAllowedEx(int Lev,bool Out=true);
/*
bool __fastcall  ActionAllowed2(int Lev);
bool __fastcall  ItemIsAllowed2(int Lev,AnsiString Msg);
*/

//---------------------------------------------------------------------------
extern PACKAGE TFormPassWord *FormPassWord;
//---------------------------------------------------------------------------
#endif
