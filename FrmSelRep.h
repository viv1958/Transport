//---------------------------------------------------------------------------

#ifndef FrmSelRepH
#define FrmSelRepH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DBAxisGridsEh.hpp"
#include "DBCtrlsEh.hpp"
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "DBGridEhToolCtrls.hpp"
#include "GridsEh.hpp"
#include "sCheckBox.hpp"
#include "sComboEdit.hpp"
#include "sCustomComboEdit.hpp"
#include "sLabel.hpp"
#include "sMaskEdit.hpp"
#include "sMemo.hpp"
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
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "sComboBoxes.hpp"
#include "sComboBox.hpp"
//---------------------------------------------------------------------------
class TFormSelRep : public TForm
{
__published:	// IDE-managed Components
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
	TsLabel *sLabel2;
	TsLabel *sLabel3;
	TsDateEdit *sDateEdit1;
	TsDateEdit *sDateEdit2;
	TsComboEdit *sComboEdit1;
	TsStatusBar *sStatusBar1;
	TsPageControl *sPageControl1;
	TsTabSheet *sTabSheet1;
	TDBGridEh *DBGridEh1;
	TsPanel *sPanel2;
	TsCheckBox *sCheckBox1;
	TQuery *Query1;
	TDataSetDriverEh *DataSetDriverEh1;
	TMemTableEh *MemTableEh1;
	TDataSource *DataSource1;
	TfrxReport *frxReport1;
	TfrxDBDataset *frxDBDataset1;
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
	TStringField *MemTableEh1TRANS_COMMENT;
	TsComboBox *sComboBox1;
	TsCheckBox *sCheckBox2;
	TsCheckBox *sCheckBox3;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sSpeedButton1Click(TObject *Sender);
	void __fastcall sComboEdit1ButtonClick(TObject *Sender);
	void __fastcall sDateEditAcceptDate(TObject *Sender, TDateTime &aDate, bool &CanAccept);
	void __fastcall DBGridEhDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumnEh *Column, TGridDrawStateEh State);
	void __fastcall DBGridEhGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont,
          TColor &Background, TGridDrawStateEh State);
	void __fastcall DBGridEhEnter(TObject *Sender);
	void __fastcall DBGridEhExit(TObject *Sender);
	void __fastcall DBGridEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEhKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall sComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MemTableEh1AfterOpen(TDataSet *DataSet);
	void __fastcall MemTableEh1AfterScroll(TDataSet *DataSet);
	void __fastcall MemTableEh1BeforeScroll(TDataSet *DataSet);
	void __fastcall MemTableEh1FilterRecord(TDataSet *DataSet, bool &Accept);
	void __fastcall MemTableEh1AfterClose(TDataSet *DataSet);
	void __fastcall sCheckBoxClick(TObject *Sender);
	void __fastcall sComboBoxCloseUp(TObject *Sender);
	void __fastcall frxReport1BeforePrint(TfrxReportComponent *Sender);



private:	// User declarations
public:		// User declarations
	int PageTag;
	int SelIndex;
	int SelID;
	int CurMM, CurYY,SelMM;
	int MaxMM, MaxYY,SelYY;

	TDateTime DT_Beg;
	TDateTime DT_End;
	GridData *WrkGData;
	GridData GDataOrders;
	int SumPayCalc, SumPayRes, SumPayAvc, SumPayRest, SumIncome;
	AnsiString SelName;
	__fastcall TFormSelRep::TFormSelRep(TComponent* Owner,int SelIndex, int SelID, AnsiString SelName);

	void __fastcall TFormSelRep::SetSelID(int SelID, AnsiString SelName);
	void __fastcall TFormSelRep::SetDates(int MM,int YY);
	void __fastcall TFormSelRep::InitCommon();
	void __fastcall TFormSelRep::SetGridColumns();

	void __fastcall TFormSelRep::SetButtonCaption(int Mon);
	void __fastcall TFormSelRep::InitGData();
	bool __fastcall TFormSelRep::SetSQL(TDataSet* DSet);
	void __fastcall TFormSelRep::CloseAll();
	void __fastcall TFormSelRep::ProcRefreshPage();
	void __fastcall TFormSelRep::ProcHistory(bool All);
	void __fastcall TFormSelRep::ShowMonth(int Shift);
	void __fastcall TFormSelRep::SelectID();
	void __fastcall TFormSelRep::SetPage();

	AnsiString __fastcall TFormSelRep::TranslateName(AnsiString FldName);
	GridData&  __fastcall TFormSelRep::GetGDataRef(TObject* Sender);

	void __fastcall TFormSelRep::ShowLowFooter(TDBGridEh* Grid,TDataSet *DataSet, int Item);
	void __fastcall TFormSelRep::ShowLowFooter(TDataSet *DataSet);
	void __fastcall TFormSelRep::ShowHighFooter(TDataSet *DataSet);

	void __fastcall TFormSelRep::OutReport(bool PreView);
	void __fastcall TFormSelRep::ClearSums();
	void __fastcall TFormSelRep::AddCurrentRow(GridData& GData,int Mul, bool Show, bool Clear);
	void __fastcall TFormSelRep::ToggleShowCost(bool Show);


};
void ShowSelReport(int SelIndex, int SelID, AnsiString SelName);

//---------------------------------------------------------------------------
extern PACKAGE TFormSelRep *FormSelRep;
//---------------------------------------------------------------------------
#endif
