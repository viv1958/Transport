//---------------------------------------------------------------------------

#ifndef FrmDriverGraphH
#define FrmDriverGraphH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sComboEdit.hpp"
#include "sCustomComboEdit.hpp"
#include "sMaskEdit.hpp"
#include "sPanel.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include "sComboBox.hpp"
#include "sEdit.hpp"
#include "sLabel.hpp"
#include "sSpinEdit.hpp"
#include "DataDriverEh.hpp"
#include "DBAxisGridsEh.hpp"
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "DBGridEhToolCtrls.hpp"
#include "GridsEh.hpp"
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
#include "ToolCtrlsEh.hpp"
#include <Bde.DBTables.hpp>
#include <Data.DB.hpp>
#include "sSpeedButton.hpp"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TFormDriverGraph : public TForm
{
__published:	// IDE-managed Components
	TsPanel *sPanel1;
	TsComboEdit *sComboEdit1;
	TsLabel *sLabel1;
	TsLabel *sLabel2;
	TsComboBox *sComboBox1;
	TsLabel *sLabel3;
	TsDecimalSpinEdit *sDecimalSpinEdit1;
	TDBGridEh *DBGridEh1;
	TMemTableEh *MemTableEh1;
	TQuery *Query1;
	TDataSource *DataSource1;
	TDataSetDriverEh *DataSetDriverEh1;
	TStringField *MemTableEh1DAY_STR_1;
	TStringField *MemTableEh1DAY_STR_2;
	TStringField *MemTableEh1DAY_STR_3;
	TStringField *MemTableEh1DAY_STR_4;
	TStringField *MemTableEh1DAY_STR_5;
	TStringField *MemTableEh1DAY_STR_6;
	TStringField *MemTableEh1DAY_STR_7;
	TDateTimeField *MemTableEh1DATECHANGE_1;
	TDateTimeField *MemTableEh1DATECHANGE_2;
	TDateTimeField *MemTableEh1DATECHANGE_3;
	TDateTimeField *MemTableEh1DATECHANGE_4;
	TDateTimeField *MemTableEh1DATECHANGE_5;
	TDateTimeField *MemTableEh1DATECHANGE_6;
	TDateTimeField *MemTableEh1DATECHANGE_7;
	TIntegerField *MemTableEh1FLAG_WRK_1;
	TIntegerField *MemTableEh1FLAG_WRK_2;
	TIntegerField *MemTableEh1FLAG_WRK_3;
	TIntegerField *MemTableEh1FLAG_WRK_4;
	TIntegerField *MemTableEh1FLAG_WRK_5;
	TIntegerField *MemTableEh1FLAG_WRK_6;
	TIntegerField *MemTableEh1FLAG_WRK_7;
	TIntegerField *MemTableEh1WEEK_NUM;
	TQuery *Query2;
	TsSpeedButton *sSpeedButton1;
	TsSpeedButton *sSpeedButton2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sComboEdit1ButtonClick(TObject *Sender);
	void __fastcall sComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sComboBox1Exit(TObject *Sender);
	void __fastcall sDecimalSpinEdit1Exit(TObject *Sender);
	void __fastcall sDecimalSpinEdit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEh1DblClick(TObject *Sender);
	void __fastcall DBGridEh1GetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont,
          TColor &Background, TGridDrawStateEh State);
	void __fastcall DBGridEh1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sSpeedButton1Click(TObject *Sender);
	void __fastcall sSpeedButton2Click(TObject *Sender);



private:	// User declarations
public:		// User declarations
	int CurYY,CurMM,DriverID;
	AnsiString FIO;
	GridData GData;
        __fastcall TFormDriverGraph::TFormDriverGraph(TComponent* Owner, int DriverID, AnsiString FIO);
	void __fastcall TFormDriverGraph::InitCommon();
	bool __fastcall TFormDriverGraph::SetSQL(TDataSet* DSet);
   void __fastcall TFormDriverGraph::ProcReturn();

	TDateTime __fastcall TFormDriverGraph::GetDate();

};
//---------------------------------------------------------------------------
extern PACKAGE TFormDriverGraph *FormDriverGraph;
//---------------------------------------------------------------------------
#endif
