//---------------------------------------------------------------------------

#ifndef FrmGetFieldFilterH
#define FrmGetFieldFilterH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Mask.hpp>
#include "sPanel.hpp"
#include "sSpeedButton.hpp"
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "DBCtrlsEh.hpp"
#include "sCheckBox.hpp"
//---------------------------------------------------------------------------
class TFormGetFieldFilter : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TsPanel *sPanel1;
	TsSpeedButton *sSpeedButton1;
	TsSpeedButton *sSpeedButton2;
	TsSpeedButton *sSpeedButton3;
	TsSpeedButton *sSpeedButton4;
	TDBNumberEditEh *DBNumberEditEh1;
	TDBEditEh *DBEditEh1;
	TDBDateTimeEditEh *DBDateTimeEditEh1;
	TsSpeedButton *sSpeedButton5;
	TsCheckBox *sCheckBox1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall StringGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sSpeedButtonClick(TObject *Sender);
	void __fastcall DBEditEh1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBEditEh1Exit(TObject *Sender);
	void __fastcall StringGrid1DblClick(TObject *Sender);
	void __fastcall DBDateTimeEditEh1CloseUp(TObject *Sender, bool Accept);



private:	// User declarations
public:		// User declarations
	int EditCol;
	int EditRow;
	bool HourMin;
	const FieldInRow* FldRowPtr ;
	std::vector<FieldFilter> FieldFilterSet;
//	__fastcall TFormGetFieldFilter::TFormGetFieldFilter(TComponent* Owner,std::vector<FieldFilter> FieldFilterSet,
//																		  const FieldInRow& FldDsc, AnsiString FName);
	__fastcall TFormGetFieldFilter::TFormGetFieldFilter(TComponent* Owner,std::vector<FieldFilter> FieldFilterSet,
																		 const FieldInRow* FldDsc, AnsiString FName);
	void __fastcall TFormGetFieldFilter::AddEmptyElement();
	void __fastcall TFormGetFieldFilter::ClearSGRow(int Row);


	void __fastcall TFormGetFieldFilter::CreateColumns();
	void __fastcall TFormGetFieldFilter::CreateRows();
	void __fastcall TFormGetFieldFilter::ShowRow(int i);
	void __fastcall TFormGetFieldFilter::ClearCell();
	void __fastcall TFormGetFieldFilter::EditCell();

//	AnsiString __fastcall TFormGetFieldFilter::GetVariantString(Variant& V);


	void __fastcall TFormGetFieldFilter::DeleteCurRow();
	void __fastcall TFormGetFieldFilter::CreateNewRow();
	void __fastcall TFormGetFieldFilter::ClearCurRow();
	void __fastcall TFormGetFieldFilter::DeleteAllRows();
	void __fastcall TFormGetFieldFilter::AddRowIfNeed();


   void __fastcall TFormGetFieldFilter::SaveEditValue(TObject *Sender);
   void __fastcall TFormGetFieldFilter::SelectFilter();


};
//---------------------------------------------------------------------------
extern PACKAGE TFormGetFieldFilter *FormGetFieldFilter;
bool GetFieldFilter(std::vector<FieldFilter>& FieldFilter, const FieldInRow* FldDsc, AnsiString FName);

//---------------------------------------------------------------------------
#endif
