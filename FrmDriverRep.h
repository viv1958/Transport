//---------------------------------------------------------------------------

#ifndef FrmDriverRepH
#define FrmDriverRepH
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
#include "sCustomComboEdit.hpp"
#include "sLabel.hpp"
#include "sMaskEdit.hpp"
#include "sPanel.hpp"
#include "sSpeedButton.hpp"
#include "sSplitter.hpp"
#include "sStatusBar.hpp"
#include "sTooledit.hpp"
#include "ToolCtrlsEh.hpp"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include "sComboEdit.hpp"
#include "DataDriverEh.hpp"
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
#include <Bde.DBTables.hpp>
#include <Data.DB.hpp>
#include "sPageControl.hpp"
//---------------------------------------------------------------------------
class TFormDriverRep : public TForm
{
__published:	// IDE-managed Components
	TsStatusBar *sStatusBar1;
	TsPanel *sPanel1;
	TsSpeedButton *sSpeedButton1;
	TsSpeedButton *sSpeedButton2;
	TsSpeedButton *sSpeedButton3;
	TsSpeedButton *sSpeedButton4;
	TsSpeedButton *sSpeedButton5;
	TsSpeedButton *sSpeedButton8;
	TsSpeedButton *sSpeedButton6;
	TsSpeedButton *sSpeedButton7;
	TsSpeedButton *sSpeedButton9;
	TsCheckBox *sCheckBox6;
	TsSpeedButton *sSpeedButton31;
	TsSpeedButton *sSpeedButton32;
	TsSpeedButton *sSpeedButton33;
	TsSpeedButton *sSpeedButton34;
	TsSpeedButton *sSpeedButton35;
	TsLabel *sLabel1;
	TsLabel *sLabel2;
	TsDateEdit *sDateEdit1;
	TsLabel *sLabel3;
	TsDateEdit *sDateEdit2;
	TsComboEdit *sComboEdit1;
	TQuery *Query1;
	TQuery *Query2;
	TQuery *Query3;
	TDataSource *DataSource1;
	TDataSource *DataSource2;
	TDataSource *DataSource3;
	TMemTableEh *MemTableEh1;
	TMemTableEh *MemTableEh2;
	TMemTableEh *MemTableEh3;
	TDataSetDriverEh *DataSetDriverEh1;
	TDataSetDriverEh *DataSetDriverEh2;
	TDataSetDriverEh *DataSetDriverEh3;
	TsPageControl *sPageControl1;
	TsTabSheet *sTabSheet1;
	TsTabSheet *sTabSheet2;
	TsTabSheet *sTabSheet3;
	TDBGridEh *DBGridEh1;
	TDBGridEh *DBGridEh3;
	TDBGridEh *DBGridEh2;
	TQuery *Query4;
	TQuery *Query5;
	TIntegerField *MemTableEh1FLAG_MES;
	TIntegerField *MemTableEh1ORDERS_ID;
	TDateTimeField *MemTableEh1DT_MAKE;
	TDateTimeField *MemTableEh1DT_BEG;
	TDateTimeField *MemTableEh1TIME_BEG;
	TIntegerField *MemTableEh1WRK_DAY;
	TIntegerField *MemTableEh1WRK_MINUT;
	TDateTimeField *MemTableEh1TIME_WRK;
	TDateTimeField *MemTableEh1DAY_END;
	TDateTimeField *MemTableEh1DT_END;
	TIntegerField *MemTableEh1DAY_SUM;
	TIntegerField *MemTableEh1CLIENT_ID;
	TStringField *MemTableEh1CLIENT_NAME;
	TIntegerField *MemTableEh1WORK_TYPE_ID;
	TStringField *MemTableEh1WORK_TYPE_NAME;
	TIntegerField *MemTableEh1TRANSPORT_ID;
	TStringField *MemTableEh1TRANSPORT_NAME;
	TStringField *MemTableEh1REG_NUMBER;
	TIntegerField *MemTableEh1DRIVER_ID;
	TStringField *MemTableEh1DRIVER_NAME;
	TIntegerField *MemTableEh1DRIVER_HAND_MONEY;
	TIntegerField *MemTableEh1BEG_TOWN_ID;
	TIntegerField *MemTableEh1END_TOWN_ID;
	TIntegerField *MemTableEh1BEG_STREET_ID;
	TIntegerField *MemTableEh1END_STREET_ID;
	TStringField *MemTableEh1BEG_ADDR_NAME;
	TStringField *MemTableEh1END_ADDR_NAME;
	TIntegerField *MemTableEh1DRV_PAY;
	TStringField *MemTableEh1BEG_STREET_NAME;
	TStringField *MemTableEh1BEG_TOWN_NAME;
	TStringField *MemTableEh1END_STREET_NAME;
	TStringField *MemTableEh1END_TOWN_NAME;
	TIntegerField *MemTableEh2FLAG_MES;
	TIntegerField *MemTableEh2OUTLAY_ID;
	TIntegerField *MemTableEh2YY;
	TIntegerField *MemTableEh2MM;
	TIntegerField *MemTableEh2EXPENSE_ID;
	TStringField *MemTableEh2EXPENSE_NAME;
	TDateTimeField *MemTableEh2DATEMAKE;
	TStringField *MemTableEh2OUTLAY_NAME;
	TIntegerField *MemTableEh2OUTLAY_TYPE;
	TStringField *MemTableEh2OUTLAY_TYPE_STR;
	TIntegerField *MemTableEh2OUTLAY_VALUE;
	TIntegerField *MemTableEh2TRANSPORT_ID;
	TIntegerField *MemTableEh2DRIVER_ID;
	TDateTimeField *MemTableEh2DATECHANGE;
	TIntegerField *MemTableEh2STATUS;
	TStringField *MemTableEh2TRANSPORT_NAME;
	TStringField *MemTableEh2REG_NUMBER;
	TStringField *MemTableEh2TRANS_TYPE_NAME;
	TStringField *MemTableEh2DRIVER_NAME;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall sSpeedButtonClick(TObject *Sender);
	void __fastcall sComboEdit1ButtonClick(TObject *Sender);
	void __fastcall sDateEditAcceptDate(TObject *Sender, TDateTime &aDate, bool &CanAccept);
	void __fastcall DBGridEhDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumnEh *Column, TGridDrawStateEh State);
	void __fastcall DBGridEhEnter(TObject *Sender);
	void __fastcall DBGridEhExit(TObject *Sender);
	void __fastcall DBGridEhGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont,
          TColor &Background, TGridDrawStateEh State);
	void __fastcall MemTableEh1AfterClose(TDataSet *DataSet);
	void __fastcall MemTableEh1AfterOpen(TDataSet *DataSet);
	void __fastcall MemTableEh1AfterScroll(TDataSet *DataSet);
	void __fastcall MemTableEh1BeforeScroll(TDataSet *DataSet);
	void __fastcall MemTableEhFilterRecord(TDataSet *DataSet, bool &Accept);
	void __fastcall DBGridEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEhKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall sPageControl1Change(TObject *Sender);


private:	// User declarations
public:		// User declarations
   int PageTag;
	int DriverID;
	int CurMM, CurYY,SelMM;
	int MaxMM, MaxYY,SelYY;
	TDateTime DT_Beg;
	TDateTime DT_End;
	GridData *WrkGData;
	GridData GDataOrders;
	GridData GDataOutlay;
	GridData GDataMonCng;
	int SumHand, SumPay, SumOutlay;
	__fastcall TFormDriverRep(TComponent* Owner);

	void __fastcall TFormDriverRep::SetDriver(int DriverID, AnsiString DriverName);
	void __fastcall TFormDriverRep::InitGData();
	void __fastcall TFormDriverRep::InitCommon();
   void __fastcall TFormDriverRep::SetPage();
	void __fastcall TFormDriverRep::CloseAll();
	void __fastcall TFormDriverRep::ProcRefresh();
	void __fastcall TFormDriverRep::SetButtonCaption(int Mon);
	void __fastcall TFormDriverRep::SetDates(int MM,int YY);

	bool __fastcall TFormDriverRep::SetSQL(TDataSet* DSet);
	void __fastcall TFormDriverRep::ShowMonth(int Shift);

	GridData& __fastcall TFormDriverRep::GetGDataRef(TObject* Sender);

   void __fastcall TFormDriverRep::ShowLowFooter(TDataSet *DataSet);
	void __fastcall TFormDriverRep::ShowLowFooter(TDBGridEh* Grid,TDataSet *DataSet, int Item);
   void __fastcall TFormDriverRep::ShowHighFooter(TDataSet *DataSet);

	void __fastcall TFormDriverRep::ClearSums();
	void __fastcall TFormDriverRep::AddCurrentRow(GridData& GData,int Mul, bool Show, bool Clear);


//	void __fastcall TFormDriverRep::SetCommonExtParams(GridData& GData);

};
void ShowDriverReport(int DriverID, AnsiString DriverName);
//---------------------------------------------------------------------------
extern PACKAGE TFormDriverRep *FormDriverRep;
//---------------------------------------------------------------------------
#endif
