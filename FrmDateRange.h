//---------------------------------------------------------------------------

#ifndef FrmDateRangeH
#define FrmDateRangeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sButton.hpp"
#include "sCustomComboEdit.hpp"
#include "sLabel.hpp"
#include "sMaskEdit.hpp"
#include "sTooledit.hpp"
#include <Vcl.Mask.hpp>
#include "DBCtrlsEh.hpp"
//---------------------------------------------------------------------------
class TFormDateRange : public TForm
{
__published:	// IDE-managed Components
	TsLabel *sLabel1;
	TsLabel *sLabel2;
	TsButton *sButton1;
	TsButton *sButton2;
	TDBDateTimeEditEh *DBDateTimeEditEh1;
	TDBDateTimeEditEh *DBDateTimeEditEh2;
	TDBDateTimeEditEh *DBDateTimeEditEh3;
	TDBDateTimeEditEh *DBDateTimeEditEh4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall sButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	 TDateTime DT1, DT2;
	 __fastcall TFormDateRange::TFormDateRange(TComponent* Owner,TDateTime DT1,TDateTime DT2);
};
bool GetDateRange(TComponent* Owner,TDateTime& DT1,TDateTime& DT2);

//---------------------------------------------------------------------------
extern PACKAGE TFormDateRange *FormDateRange;
//---------------------------------------------------------------------------
#endif
