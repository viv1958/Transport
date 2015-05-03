//---------------------------------------------------------------------------

#ifndef FrmDriverGraphDayH
#define FrmDriverGraphDayH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DBCtrlsEh.hpp"
#include "sComboBox.hpp"
#include <Vcl.Mask.hpp>
#include <Bde.DBTables.hpp>
#include <Data.DB.hpp>
#include "sLabel.hpp"
#include "sEdit.hpp"
#include "sButton.hpp"
//---------------------------------------------------------------------------
class TFormDriverGraphDay : public TForm
{
__published:	// IDE-managed Components
	TsComboBox *sComboBox1;
	TDBDateTimeEditEh *DBDateTimeEditEh1;
	TDBDateTimeEditEh *DBDateTimeEditEh2;
	TQuery *Query1;
	TsLabel *sLabel1;
	TsEdit *sEdit1;
	TsLabel *sLabel2;
	TsButton *sButton1;
	TsButton *sButton2;
	TQuery *Query2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall sComboBox1Exit(TObject *Sender);
	void __fastcall sComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sButtonClick(TObject *Sender);
	void __fastcall DBDateTimeEditEh1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBDateTimeEditEh2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sEdit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sComboBox1CloseUp(TObject *Sender);
	void __fastcall sButton1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);




private:	// User declarations
public:		// User declarations
	int       DriverID;
	TDateTime DT_Wrk,DT_Beg_Out, DT_End_Out;
	AnsiString FIO;
	GridData GData;
	__fastcall TFormDriverGraphDay(TComponent* Owner, AnsiString FIO, int DriverID, TDateTime DT_Wrk);
	void __fastcall TFormDriverGraphDay::InitCommon();
	void __fastcall TFormDriverGraphDay::ProcRefresh();
	void __fastcall TFormDriverGraphDay::SetControls(int Flag_Wrk);
	bool __fastcall TFormDriverGraphDay::WriteData()
;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDriverGraphDay *FormDriverGraphDay;
//---------------------------------------------------------------------------
#endif
