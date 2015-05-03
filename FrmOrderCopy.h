//---------------------------------------------------------------------------

#ifndef FrmOrderCopyH
#define FrmOrderCopyH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sPanel.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "acAlphaHints.hpp"
#include "sLabel.hpp"
#include <Vcl.Grids.hpp>
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
#include "sCheckBox.hpp"
#include "sSpeedButton.hpp"
#include <Vcl.Buttons.hpp>
using namespace std;
//---------------------------------------------------------------------------
class TFormOrderCopy : public TForm
{
__published:	// IDE-managed Components
	TsPanel *sPanelM;
	TQuery *Query1;
	TsPanel *sPanel16;
	TsPanel *sPanel9;
	TDBGridEh *DBGridEh9;
	TsCheckBox *sCheckBox9;
	TsPanel *sPanel10;
	TDBGridEh *DBGridEh10;
	TsCheckBox *sCheckBox10;
	TsPanel *sPanel11;
	TDBGridEh *DBGridEh11;
	TsCheckBox *sCheckBox11;
	TsPanel *sPanel12;
	TDBGridEh *DBGridEh12;
	TsCheckBox *sCheckBox12;
	TsPanel *sPanel14;
	TsPanel *sPanel1;
	TDBGridEh *DBGridEh1;
	TsCheckBox *sCheckBox1;
	TsPanel *sPanel2;
	TDBGridEh *DBGridEh2;
	TsCheckBox *sCheckBox2;
	TsPanel *sPanel3;
	TDBGridEh *DBGridEh3;
	TsCheckBox *sCheckBox3;
	TsPanel *sPanel4;
	TDBGridEh *DBGridEh4;
	TsCheckBox *sCheckBox4;
	TsPanel *sPanel15;
	TsPanel *sPanel5;
	TDBGridEh *DBGridEh5;
	TsCheckBox *sCheckBox5;
	TsPanel *sPanel6;
	TDBGridEh *DBGridEh6;
	TsCheckBox *sCheckBox6;
	TsPanel *sPanel7;
	TDBGridEh *DBGridEh7;
	TsCheckBox *sCheckBox7;
	TsPanel *sPanel8;
	TDBGridEh *DBGridEh8;
	TsCheckBox *sCheckBox8;
	TMemTableEh *MemTableEh1;
	TMemTableEh *MemTableEh2;
	TMemTableEh *MemTableEh3;
	TMemTableEh *MemTableEh4;
	TMemTableEh *MemTableEh5;
	TMemTableEh *MemTableEh6;
	TMemTableEh *MemTableEh7;
	TMemTableEh *MemTableEh8;
	TMemTableEh *MemTableEh9;
	TMemTableEh *MemTableEh10;
	TMemTableEh *MemTableEh11;
	TMemTableEh *MemTableEh12;
	TDataSource *DataSource1;
	TDataSource *DataSource2;
	TDataSource *DataSource3;
	TDataSource *DataSource4;
	TDataSource *DataSource5;
	TDataSource *DataSource6;
	TDataSource *DataSource7;
	TDataSource *DataSource8;
	TDataSource *DataSource9;
	TDataSource *DataSource10;
	TDataSource *DataSource11;
	TDataSource *DataSource12;
	TQuery *Query2;
	TsSpeedButton *sSpeedButton2;
	TsSpeedButton *sSpeedButton1;
	TsSpeedButton *sSpeedButton3;
	TsCheckBox *sCheckBox13;
	TsCheckBox *sCheckBox14;
	TsCheckBox *sCheckBox15;
	TsCheckBox *sCheckBox16;
	TsCheckBox *sCheckBox17;
	TsCheckBox *sCheckBox18;
	TsCheckBox *sCheckBox19;
	TQuery *Query3;
	TsCheckBox *sCheckBox20;
	TsCheckBox *sCheckBox21;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MemTableEhFilterRecord(TDataSet *DataSet, bool &Accept);
	void __fastcall sCheckBoxClick(TObject *Sender);
	void __fastcall DBGridEh1GetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont,
          TColor &Background, TGridDrawStateEh State);
	void __fastcall DBGridEh1TitleBtnClick(TObject *Sender, int ACol, TColumnEh *Column);
	void __fastcall DBGridEh1DblClick(TObject *Sender);
	void __fastcall sSpeedButtonClick(TObject *Sender);
	void __fastcall sCheckBoxShowClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	int CurMonth;
	int SrcOrderID;
	int NCopy;
	TDateTime DTBeg;
	TDateTime DTEnd;
	TDateTime Today;
	vector<TDBGridEh*> GridsArr;
	vector<TsPanel*>   PanelArr;
	multimap<TDateTime,int> DateOrd;
	AnsiString SelGridNum;

  __fastcall TFormOrderCopy::TFormOrderCopy(TComponent* Owner, int SrcOrderID);
	void __fastcall TFormOrderCopy::InitData();
	void __fastcall TFormOrderCopy::CreateVect();
	void __fastcall TFormOrderCopy::FillMonthPanels();
	void __fastcall TFormOrderCopy::ShowExistngCopies();

   int __fastcall TFormOrderCopy::AnalyzeCellDT(TDateTime DT);

	void __fastcall TFormOrderCopy::ClearSelDates();
	void __fastcall TFormOrderCopy::ApplySelDates();
	void __fastcall TFormOrderCopy::CopyOrders();
	void __fastcall TFormOrderCopy::ApplySelDates(TDBGridEh* Grid);
	bool __fastcall TFormOrderCopy::CopyOrder(TDateTime DT);
	AnsiString TFormOrderCopy::GetOrdersList(TDateTime DT);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormOrderCopy *FormOrderCopy;
//---------------------------------------------------------------------------
#endif
