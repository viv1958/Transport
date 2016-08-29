//---------------------------------------------------------------------------

#ifndef FrmSummaryRepH
#define FrmSummaryRepH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DBAxisGridsEh.hpp"
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "DBGridEhToolCtrls.hpp"
#include "GridsEh.hpp"
#include "sCheckBox.hpp"
#include "sComboBox.hpp"
#include "sComboEdit.hpp"
#include "sCustomComboEdit.hpp"
#include "sLabel.hpp"
#include "sMaskEdit.hpp"
#include "sPageControl.hpp"
#include "sPanel.hpp"
#include "sSpeedButton.hpp"
#include "sStatusBar.hpp"
#include "sTooledit.hpp"
#include "ToolCtrlsEh.hpp"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include "DataDriverEh.hpp"
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
#include <Bde.DBTables.hpp>
#include <Data.DB.hpp>
//---------------------------------------------------------------------------
class TFormSummaryRep : public TForm
{
__published:	// IDE-managed Components
	TsStatusBar *sStatusBar1;
	TsPageControl *sPageControl1;
	TsTabSheet *sTabSheet1;
	TDBGridEh *DBGridEh1;
	TsPanel *sPanel2;
	TsCheckBox *sCheckBox1;
	TsCheckBox *sCheckBox2;
	TsPanel *sPanel1;
	TsSpeedButton *sSpeedButton1;
	TsSpeedButton *sSpeedButton4;
	TsSpeedButton *sSpeedButton5;
	TsSpeedButton *sSpeedButton6;
	TsSpeedButton *sSpeedButton7;
	TsSpeedButton *sSpeedButton31;
	TsSpeedButton *sSpeedButton32;
	TsSpeedButton *sSpeedButton33;
	TsSpeedButton *sSpeedButton34;
	TsSpeedButton *sSpeedButton35;
	TsLabel *sLabel2;
	TsLabel *sLabel3;
	TsDateEdit *sDateEdit1;
	TsDateEdit *sDateEdit2;
	TDataSource *DataSource1;
	TQuery *Query1;
	TMemTableEh *MemTableEh1;
	TDataSetDriverEh *DataSetDriverEh1;
	TIntegerField *MemTableEh1FLAG_MES;
	TIntegerField *MemTableEh1CLIENT_ID;
	TStringField *MemTableEh1CLIENT_NAME;
	TFloatField *MemTableEh1INCOME_01;
	TFloatField *MemTableEh1INCOME_02;
	TFloatField *MemTableEh1INCOME_03;
	TFloatField *MemTableEh1INCOME_04;
	TFloatField *MemTableEh1INCOME_05;
	TFloatField *MemTableEh1INCOME_06;
	TFloatField *MemTableEh1INCOME_07;
	TFloatField *MemTableEh1INCOME_08;
	TFloatField *MemTableEh1INCOME_09;
	TFloatField *MemTableEh1INCOME_10;
	TFloatField *MemTableEh1INCOME_11;
	TFloatField *MemTableEh1INCOME_12;
	TFloatField *MemTableEh1INCOME_13;
	TsTabSheet *sTabSheet2;
	TsPanel *sPanel3;
	TsCheckBox *sCheckBox4;
	TDBGridEh *DBGridEh2;
	TQuery *Query2;
	TDataSetDriverEh *DataSetDriverEh2;
	TMemTableEh *MemTableEh2;
	TDataSource *DataSource2;
	TIntegerField *MemTableEh2FLAG_MES;
	TIntegerField *MemTableEh2TRANSPORT_ID;
	TStringField *MemTableEh2TRANSPORT_NAME;
	TStringField *MemTableEh2REG_NUMBER;
	TIntegerField *MemTableEh2EXC_PAY_01;
	TIntegerField *MemTableEh2EXC_PAY_02;
	TIntegerField *MemTableEh2EXC_PAY_03;
	TIntegerField *MemTableEh2EXC_PAY_04;
	TIntegerField *MemTableEh2EXC_PAY_05;
	TIntegerField *MemTableEh2EXC_PAY_06;
	TIntegerField *MemTableEh2EXC_PAY_07;
	TIntegerField *MemTableEh2EXC_PAY_08;
	TIntegerField *MemTableEh2EXC_PAY_09;
	TIntegerField *MemTableEh2EXC_PAY_10;
	TIntegerField *MemTableEh2EXC_PAY_11;
	TIntegerField *MemTableEh2EXC_PAY_12;
	TIntegerField *MemTableEh2EXC_PAY_13;
	TIntegerField *MemTableEh2OUT_VAL_01;
	TIntegerField *MemTableEh2OUT_VAL_02;
	TIntegerField *MemTableEh2OUT_VAL_03;
	TIntegerField *MemTableEh2OUT_VAL_04;
	TIntegerField *MemTableEh2OUT_VAL_05;
	TIntegerField *MemTableEh2OUT_VAL_06;
	TIntegerField *MemTableEh2OUT_VAL_07;
	TIntegerField *MemTableEh2OUT_VAL_08;
	TIntegerField *MemTableEh2OUT_VAL_09;
	TIntegerField *MemTableEh2OUT_VAL_10;
	TIntegerField *MemTableEh2OUT_VAL_11;
	TIntegerField *MemTableEh2OUT_VAL_12;
	TIntegerField *MemTableEh2OUT_VAL_13;
	TIntegerField *MemTableEh2TRP_VAL_01;
	TIntegerField *MemTableEh2TRP_VAL_02;
	TIntegerField *MemTableEh2TRP_VAL_03;
	TIntegerField *MemTableEh2TRP_VAL_04;
	TIntegerField *MemTableEh2TRP_VAL_05;
	TIntegerField *MemTableEh2TRP_VAL_06;
	TIntegerField *MemTableEh2TRP_VAL_07;
	TIntegerField *MemTableEh2TRP_VAL_08;
	TIntegerField *MemTableEh2TRP_VAL_09;
	TIntegerField *MemTableEh2TRP_VAL_10;
	TIntegerField *MemTableEh2TRP_VAL_11;
	TIntegerField *MemTableEh2TRP_VAL_12;
	TIntegerField *MemTableEh2TRP_VAL_13;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sSpeedButtonClick(TObject *Sender);
	void __fastcall sDateEditAcceptDate(TObject *Sender, TDateTime &aDate, bool &CanAccept);
	void __fastcall DBGridEhEnter(TObject *Sender);
	void __fastcall DBGridEhExit(TObject *Sender);
	void __fastcall DBGridEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEhKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall MemTableEh1AfterClose(TDataSet *DataSet);
	void __fastcall MemTableEh1AfterOpen(TDataSet *DataSet);
	void __fastcall MemTableEh1BeforeScroll(TDataSet *DataSet);
	void __fastcall MemTableEh1FilterRecord(TDataSet *DataSet, bool &Accept);
	void __fastcall sCheckBoxClick(TObject *Sender);
	void __fastcall DBGridEh1GetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont,
          TColor &Background, TGridDrawStateEh State);
	void __fastcall DBGridEh1SortMarkingChanged(TObject *Sender);
	void __fastcall MemTableEh1AfterScroll(TDataSet *DataSet);
	void __fastcall sPageControl1Change(TObject *Sender);



private:	// User declarations
public:		// User declarations
   int SelIndex;
	int PageTag;
	int CurMM, CurYY,SelMM;
	int MaxMM, MaxYY,SelYY;

	TDateTime DT_Beg;
	TDateTime DT_End;
	GridData *WrkGData;
	GridData GDataClient;
	GridData GDataTransp;

	double Sum1[14];
	int    Sum2[41];

	__fastcall TFormSummaryRep(TComponent* Owner, int SelIndex);

	void __fastcall TFormSummaryRep::InitCommon();
	void __fastcall TFormSummaryRep::SetDates(int MM,int YY);
	void __fastcall TFormSummaryRep::SetColumns();

	void __fastcall TFormSummaryRep::SetButtonCaption(int Mon);
	void __fastcall TFormSummaryRep::InitGData();
	bool __fastcall TFormSummaryRep::SetSQL(TDataSet* DSet);

	void __fastcall TFormSummaryRep::SetPage();
	void __fastcall TFormSummaryRep::EnableControls();
	void __fastcall TFormSummaryRep::CloseAll();
	void __fastcall TFormSummaryRep::ProcRefreshPage();

   GridData& __fastcall TFormSummaryRep::GetGDataRef(TObject* Sender);

	void __fastcall TFormSummaryRep::ShowMonth(int Shift);
	void __fastcall TFormSummaryRep::ShowLowFooter(TDBGridEh* Grid,TDataSet *DataSet, int Item);
	void __fastcall TFormSummaryRep::ShowLowFooter(TDataSet *DataSet);
	void __fastcall TFormSummaryRep::ShowHighFooter(TDataSet *DataSet);
	void __fastcall TFormSummaryRep::ClearSums(int);
	void __fastcall TFormSummaryRep::AddCurrentRow(GridData& GData,int Mul, bool Show, bool Clear);

	void __fastcall TFormSummaryRep::ToggleShowCost(bool Show);

};
void ShowSummaryReport(int SelIndex);
//---------------------------------------------------------------------------
extern PACKAGE TFormSummaryRep *FormSummaryRep;
//---------------------------------------------------------------------------
#endif
