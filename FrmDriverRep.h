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
	TsCheckBox *sCheckBox21;
	TsCheckBox *sCheckBox6;
	TsPanel *sPanel2;
	TsSplitter *sSplitter1;
	TDBGridEh *DBGridEh2;
	TDBGridEh *DBGridEh3;
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
	TsSplitter *sSplitter2;
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
	TDBGridEh *DBGridEh1;
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
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall sSpeedButtonClick(TObject *Sender);
	void __fastcall sComboEdit1ButtonClick(TObject *Sender);
	void __fastcall sDateEditAcceptDate(TObject *Sender, TDateTime &aDate, bool &CanAccept);

private:	// User declarations
public:		// User declarations
	int DriverID;
	int CurMM, CurYY,SelMM;
	int MaxMM, MaxYY,SelYY;
	TDateTime DT_Beg;
	TDateTime DT_End;
	GridData GDataOrders;
	GridData GDataOutlay;
	GridData GDataMonCng;
	__fastcall TFormDriverRep(TComponent* Owner);

	void __fastcall TFormDriverRep::SetDriver(int DriverID, AnsiString DriverName);
	void __fastcall TFormDriverRep::InitGData();
	void __fastcall TFormDriverRep::InitCommon();
	void __fastcall TFormDriverRep::ProcRefresh();
	void __fastcall TFormDriverRep::SetButtonCaption(int Mon);
	void __fastcall TFormDriverRep::SetDates(int MM,int YY);

   bool __fastcall TFormDriverRep::SetSQL(TDataSet* DSet);
	void __fastcall TFormDriverRep::ShowMonth(int Shift);


//	void __fastcall TFormDriverRep::SetCommonExtParams(GridData& GData);

};
void ShowDriverReport(int DriverID, AnsiString DriverName);
//---------------------------------------------------------------------------
extern PACKAGE TFormDriverRep *FormDriverRep;
//---------------------------------------------------------------------------
#endif
