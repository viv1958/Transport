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
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "frxDesgn.hpp"
#include "frxDMPExport.hpp"
#include "sMemo.hpp"
#include "DBCtrlsEh.hpp"
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
	TsSpeedButton *sSpeedButton6;
	TsSpeedButton *sSpeedButton8;
	TsSpeedButton *sSpeedButton7;
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
	TDBGridEh *DBGridEh2;
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
	TfrxReport *frxReport1;
	TfrxDBDataset *frxDBDataset1;
	TfrxDBDataset *frxDBDataset2;
	TsPanel *sPanel2;
	TsCheckBox *sCheckBox1;
	TsPanel *sPanel3;
	TsCheckBox *sCheckBox2;
	TQuery *Query61;
	TDataSetDriverEh *DataSetDriverEh4;
	TMemTableEh *MemTableEh4;
	TDataSource *DataSource4;
	TsTabSheet *sTabSheet4;
	TsMemo *sMemo2;
	TsPanel *sPanel4;
	TsCheckBox *sCheckBox3;
	TDBGridEh *DBGridEh4;
	TsMemo *sMemo1;
	TsPanel *sPanel7;
	TsCheckBox *sCheckBox4;
	TDBGridEh *DBGridEh3;
	TDBEditEh *DBEditEh;
	TDBDateTimeEditEh *DBDateTimeEditEh;
	TComboBox *ComboBox;
	TDBNumberEditEh *DBNumberEditEh;
	TQuery *Query4;
	TQuery *Query51;
	TfrxDBDataset *frxDBDataset3;
	TfrxDBDataset *frxDBDataset4;
	TIntegerField *MemTableEh3FLAG_MES;
	TIntegerField *MemTableEh3MONEY_MOVE_ID;
	TIntegerField *MemTableEh3OBJECT_ID_SRC;
	TStringField *MemTableEh3NAME_SRC;
	TStringField *MemTableEh3NAME_TYPE_SRC;
	TIntegerField *MemTableEh3INDEX_ID_SRC;
	TIntegerField *MemTableEh3OBJECT_TYPE_SRC;
	TDateTimeField *MemTableEh3DATESET;
	TIntegerField *MemTableEh3OBJECT_ID_TAG;
	TIntegerField *MemTableEh3INDEX_ID_TAG;
	TStringField *MemTableEh3NAME_TAG;
	TIntegerField *MemTableEh3OBJECT_TYPE_TAG;
	TStringField *MemTableEh3NAME_TYPE_TAG;
	TIntegerField *MemTableEh3MONEY_VALUE;
	TIntegerField *MemTableEh3EMPLOYEE_ID;
	TStringField *MemTableEh3FULL_NAME;
	TDateTimeField *MemTableEh3DATE_CONFIRM;
	TStringField *MemTableEh3COMMENT;
	TDateTimeField *MemTableEh3DATECHANGE;
	TIntegerField *MemTableEh3STATUS;
	TIntegerField *MemTableEh4FLAG_MES;
	TIntegerField *MemTableEh4MONEY_MOVE_ID;
	TIntegerField *MemTableEh4OBJECT_ID_SRC;
	TStringField *MemTableEh4NAME_SRC;
	TStringField *MemTableEh4NAME_TYPE_SRC;
	TIntegerField *MemTableEh4INDEX_ID_SRC;
	TIntegerField *MemTableEh4OBJECT_TYPE_SRC;
	TDateTimeField *MemTableEh4DATESET;
	TIntegerField *MemTableEh4OBJECT_ID_TAG;
	TIntegerField *MemTableEh4INDEX_ID_TAG;
	TStringField *MemTableEh4NAME_TAG;
	TIntegerField *MemTableEh4OBJECT_TYPE_TAG;
	TStringField *MemTableEh4NAME_TYPE_TAG;
	TIntegerField *MemTableEh4MONEY_VALUE;
	TIntegerField *MemTableEh4EMPLOYEE_ID;
	TStringField *MemTableEh4FULL_NAME;
	TDateTimeField *MemTableEh4DATE_CONFIRM;
	TStringField *MemTableEh4COMMENT;
	TDateTimeField *MemTableEh4DATECHANGE;
	TIntegerField *MemTableEh4STATUS;
	TIntegerField *MemTableEh1FLAG_MES;
	TIntegerField *MemTableEh1ORDERS_ID;
	TDateTimeField *MemTableEh1DT_MAKE;
	TDateTimeField *MemTableEh1DT_BEG;
	TDateTimeField *MemTableEh1TIME_BEG;
	TIntegerField *MemTableEh1BEF_MINUT;
	TDateTimeField *MemTableEh1TIME_BEF;
	TIntegerField *MemTableEh1WRK_DAY;
	TIntegerField *MemTableEh1WRK_MINUT;
	TDateTimeField *MemTableEh1TIME_WRK;
	TDateTimeField *MemTableEh1DAY_END;
	TDateTimeField *MemTableEh1DT_END;
	TIntegerField *MemTableEh1DAY_SUM;
	TDateTimeField *MemTableEh1TIME_SUM;
	TStringField *MemTableEh1TIME_SUM_STR;
	TStringField *MemTableEh1TIME_SUM_STR_F;
	TIntegerField *MemTableEh1ORDER_STATE;
	TStringField *MemTableEh1ORDER_STATE_STR;
	TIntegerField *MemTableEh1ORDER_TYPE;
	TStringField *MemTableEh1ORDER_TYPE_STR;
	TIntegerField *MemTableEh1CLIENT_ID;
	TStringField *MemTableEh1CLIENT_NAME;
	TIntegerField *MemTableEh1WORK_TYPE_ID;
	TStringField *MemTableEh1WORK_TYPE_NAME;
	TIntegerField *MemTableEh1CONTACT_ID;
	TStringField *MemTableEh1CONTACT_NAME;
	TStringField *MemTableEh1CONTACT_PHONE;
	TIntegerField *MemTableEh1TRANS_TYPE_ID;
	TStringField *MemTableEh1TRANS_TYPE_NAME;
	TIntegerField *MemTableEh1PASS_NEED;
	TIntegerField *MemTableEh1TRANSPORT_ID;
	TStringField *MemTableEh1TRANSPORT_NAME;
	TStringField *MemTableEh1REG_NUMBER;
	TIntegerField *MemTableEh1PASS_NUMBER;
	TIntegerField *MemTableEh1DRIVER_ID;
	TStringField *MemTableEh1DRIVER_NAME;
	TStringField *MemTableEh1DRIVER_PHONE;
	TIntegerField *MemTableEh1DRIVER_HAND_MONEY;
	TIntegerField *MemTableEh1BEG_TOWN_ID;
	TIntegerField *MemTableEh1END_TOWN_ID;
	TIntegerField *MemTableEh1BEG_STREET_ID;
	TIntegerField *MemTableEh1END_STREET_ID;
	TStringField *MemTableEh1BEG_ADDR_NAME;
	TStringField *MemTableEh1END_ADDR_NAME;
	TIntegerField *MemTableEh1RET_TO_START;
	TStringField *MemTableEh1RET_TO_START_STR;
	TIntegerField *MemTableEh1CLIENT_TAX_ID;
	TDateTimeField *MemTableEh1TIME_ADD;
	TDateTimeField *MemTableEh1TIME_MIN;
	TIntegerField *MemTableEh1HOUR_TAX;
	TIntegerField *MemTableEh1DIST_TAX;
	TIntegerField *MemTableEh1DOG_TAX;
	TIntegerField *MemTableEh1DIST_RES;
	TFloatField *MemTableEh1PAY_CALC;
	TFloatField *MemTableEh1PAY_RES;
	TIntegerField *MemTableEh1PAY_TYPE;
	TStringField *MemTableEh1PAY_TYPE_STR;
	TIntegerField *MemTableEh1PAY_AVC;
	TIntegerField *MemTableEh1PAY_AVC_STATE;
	TStringField *MemTableEh1PAY_AVC_STATE_STR;
	TIntegerField *MemTableEh1PAY_AVC_RECEIVER;
	TStringField *MemTableEh1PAY_AVC_RECEIVER_STR;
	TFloatField *MemTableEh1PAY_REST;
	TIntegerField *MemTableEh1PAY_REST_STATE;
	TStringField *MemTableEh1PAY_REST_STATE_STR;
	TIntegerField *MemTableEh1PAY_REST_RECEIVER;
	TStringField *MemTableEh1PAY_REST_RECEIVER_STR;
	TIntegerField *MemTableEh1ORDER_FLAG;
	TIntegerField *MemTableEh1EXC_PAY;
	TDateTimeField *MemTableEh1EXC_PAY_DATE;
	TIntegerField *MemTableEh1MNG_PAY;
	TDateTimeField *MemTableEh1MNG_PAY_DATE;
	TIntegerField *MemTableEh1DRV_PAY;
	TIntegerField *MemTableEh1MANAGER_ID;
	TIntegerField *MemTableEh1NDOG_ID;
	TStringField *MemTableEh1COMMENT;
	TDateTimeField *MemTableEh1DATECHANGE;
	TIntegerField *MemTableEh1STATUS;
	TDateTimeField *MemTableEh1TRANS_TIME_MIN;
	TDateTimeField *MemTableEh1TRANS_TIME_ADD;
	TIntegerField *MemTableEh1TRANS_HOUR_TAX;
	TIntegerField *MemTableEh1TRANS_DIST_TAX;
	TStringField *MemTableEh1BEG_STREET_NAME;
	TStringField *MemTableEh1BEG_TOWN_NAME;
	TStringField *MemTableEh1END_STREET_NAME;
	TStringField *MemTableEh1END_TOWN_NAME;
	TStringField *MemTableEh1FULL_NAME;
	TIntegerField *MemTableEh1TRANS_COMPANY_ID;
	TStringField *MemTableEh1TRANS_COMPANY_NAME;
	TIntegerField *MemTableEh1TRANS_COMPANY_FLAG;
	TIntegerField *MemTableEh1SUM_MINUT;
	TFloatField *MemTableEh1INCOME;
	TIntegerField *MemTableEh1SRC_ORDER_ID;
	TIntegerField *MemTableEh1FLAG_CALC_INCOME;
	TStringField *MemTableEh1FLAG_CALC_INCOME_STR;
	TStringField *MemTableEh1TAX_TAKE_STR;
	TStringField *MemTableEh1NDOG_ID_STR;
	TStringField *MemTableEh1TRANS_COMMENT;
	TStringField *MemTableEh1BEG_FULL_ADDR;
	TStringField *MemTableEh1END_FULL_ADDR;
	TsTabSheet *sTabSheet5;
	TsTabSheet *sTabSheet6;
	TDBGridEh *DBGridEh5;
	TQuery *Query5;
	TDataSetDriverEh *DataSetDriverEh5;
	TMemTableEh *MemTableEh5;
	TDataSource *DataSource5;
	TIntegerField *MemTableEh5FLAG_MES;
	TIntegerField *MemTableEh5DRIVER_ID;
	TStringField *MemTableEh5DRIVER_NAME;
	TIntegerField *MemTableEh5DRIVER_HAND_MONEY;
	TIntegerField *MemTableEh5DRV_PAY;
	TIntegerField *MemTableEh5OUTLAY_VALUE;
	TIntegerField *MemTableEh5GET_MONEY;
	TIntegerField *MemTableEh5GIVE_MONEY;
	TIntegerField *MemTableEh5SALARY;
	TIntegerField *MemTableEh5TRANS_COMPANY_FLAG;
	TStringField *MemTableEh5TRANS_COMPANY_NAME;
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
	void __fastcall sCheckBoxClick(TObject *Sender);
	void __fastcall frxReport1BeforePrint(TfrxReportComponent *Sender);
	void __fastcall DBEditExit(TObject *Sender);
	void __fastcall DBEditEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sPageControl1Changing(TObject *Sender, bool &AllowChange);
	void __fastcall sMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sMemoExit(TObject *Sender);



private:	// User declarations
public:		// User declarations
	int PageTag;
	int DriverID;
	int Drv_Object_ID;
	int CurMM, CurYY,SelMM;
	int MaxMM, MaxYY,SelYY;

	TDateTime DT_Beg;
	TDateTime DT_End;
	GridData *WrkGData;
	GridData GDataOrders;
	GridData GDataOutlay;
	GridData GDataMonInp;
	GridData GDataMonOut;
	GridData GDataSalary;

	int SumHand1,   SumDrvPay1, SumOutlay2, SumMonInp, SumMonOut;
	int SumHand5,   SumDrvPay5, SumOutlay5, SumSalary;

	AnsiString DriverName;
	__fastcall TFormDriverRep(TComponent* Owner,int DriverID, AnsiString DriverName);

	void __fastcall TFormDriverRep::SetDriver(int DriverID, AnsiString DriverName);
	void __fastcall TFormDriverRep::InitGData();
	void __fastcall TFormDriverRep::InitCommon();
	void __fastcall TFormDriverRep::SelectDriver();

	void __fastcall TFormDriverRep::ProcHistory(bool All);

	AnsiString __fastcall TFormDriverRep::TranslateName(AnsiString FldName);

	bool __fastcall TFormDriverRep::RefreshOneRow(GridData& GData,TDataSet* DSet);
	void __fastcall TFormDriverRep::SetCommonExtParams(GridData& GData);
   bool __fastcall TFormDriverRep::GetObjectID(TForm* Frm, int Left,int &ID,TParams*&);

	void __fastcall TFormDriverRep::SetPage();
	void __fastcall TFormDriverRep::EnableControls();
	void __fastcall TFormDriverRep::CloseAll();
	void __fastcall TFormDriverRep::ProcRefreshPage();
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
	void __fastcall TFormDriverRep::WriteMemo();

	void __fastcall TFormDriverRep::PrintReport();
   void __fastcall TFormDriverRep::GetDrvObjectID();

//	void __fastcall TFormDriverRep::SetCommonExtParams(GridData& GData);

};
void ShowDriverReport(int DriverID, AnsiString DriverName);
//---------------------------------------------------------------------------
extern PACKAGE TFormDriverRep *FormDriverRep;
//---------------------------------------------------------------------------
#endif
