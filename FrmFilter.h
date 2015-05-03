//---------------------------------------------------------------------------

#ifndef FrmFilterH
#define FrmFilterH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sPanel.hpp"
#include "sStatusBar.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "sSpeedButton.hpp"
#include <Vcl.Buttons.hpp>
#include "sComboEdit.hpp"
#include "sCustomComboEdit.hpp"
#include "sMaskEdit.hpp"
#include <Vcl.Mask.hpp>
#include <Bde.DBTables.hpp>
#include <Data.DB.hpp>
//---------------------------------------------------------------------------
class TFormFilter : public TForm
{
__published:	// IDE-managed Components
	TsPanel *sPanel1;
	TsStatusBar *sStatusBar1;
	TStringGrid *StringGrid1;
	TsSpeedButton *sSpeedButton1;
	TsSpeedButton *sSpeedButton2;
	TsSpeedButton *sSpeedButton3;
	TsSpeedButton *sSpeedButton4;
	TsSpeedButton *sSpeedButton6;
	TsComboEdit *sComboEdit1;
	TsSpeedButton *sSpeedButton5;
	TQuery *Query1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall sSpeedButtonClick(TObject *Sender);
	void __fastcall StringGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall StringGrid1DblClick(TObject *Sender);
	void __fastcall sComboEdit1ButtonClick(TObject *Sender);
	void __fastcall sComboEdit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations
public:		// User declarations
   int SelFilterID;
	TDBGridEh* OrderGrid;
	FilterCols  OrderFilter;

	std::vector<FieldInRow> FilteredFields;

	__fastcall TFormFilter::TFormFilter(TComponent* Owner,FilterCols& OrderFilter,TDBGridEh* OrderGrid,int SelFilterID,AnsiString FilterName);

	void __fastcall TFormFilter::AddEmptyElement();
	void __fastcall TFormFilter::FillFirstColumn();
	void __fastcall TFormFilter::FillCells();


	void __fastcall TFormFilter::DeleteCurColumn();
	void __fastcall TFormFilter::CreateNewColumn();
	void __fastcall TFormFilter::ClearCurColumn();
	void __fastcall TFormFilter::DeleteAllColumns();
	void __fastcall TFormFilter::SaveCurFilterSet();
	void __fastcall TFormFilter::AddColIfNeed();
	void __fastcall TFormFilter::ClearSGCol(int Col);

	void __fastcall TFormFilter::EditCell();
	void __fastcall TFormFilter::ClearCell();

	AnsiString __fastcall TFormFilter::GetFilterSetString(std::vector<FieldFilter>& FieldFilterSet,FieldInRow* FR);

	void __fastcall TFormFilter::SaveCurrentFilter();
	void __fastcall TFormFilter::SaveFilterCont();
	bool __fastcall TFormFilter::SelCurrentFilter(bool SaveCurState);
	void __fastcall TFormFilter::ProcResultFilterSel(bool SaveCurState);

	void __fastcall TFormFilter::RestoreFilterCont();
	void __fastcall TFormFilter::ClearSelFilter();
	bool __fastcall TFormFilter::FilterIsEmpty();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormFilter *FormFilter;
bool GetFilter(FilterCols& OrderFilter,TDBGridEh* OrderGrid,int& SelFilterID,AnsiString& FilterName);

//---------------------------------------------------------------------------
#endif
