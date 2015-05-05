//---------------------------------------------------------------------------

#ifndef FrmTransH
#define FrmTransH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sPageControl.hpp"
#include "sPanel.hpp"
#include "sStatusBar.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "DBAxisGridsEh.hpp"
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "DBGridEhToolCtrls.hpp"
#include "GridsEh.hpp"
#include "sSplitter.hpp"
#include "ToolCtrlsEh.hpp"
#include "DataDriverEh.hpp"
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
#include <Bde.DBTables.hpp>
#include <Data.DB.hpp>
#include "DBCtrlsEh.hpp"
#include <Vcl.Mask.hpp>
#include "cxControls.hpp"
#include "cxEdit.hpp"
#include "cxGraphics.hpp"
#include "cxInplaceContainer.hpp"
#include "cxLookAndFeelPainters.hpp"
#include "cxLookAndFeels.hpp"
#include "cxOI.hpp"
#include "cxStyles.hpp"
#include "cxVGrid.hpp"
#include "dxSkinsCore.hpp"
#include "dxSkinsDefaultPainters.hpp"
#include "sCustomComboEdit.hpp"
#include "sMaskEdit.hpp"
#include "sTooledit.hpp"
#include "sComboBox.hpp"
#include "sSpeedButton.hpp"
#include <Vcl.Buttons.hpp>
#include "sCheckBox.hpp"
#include "sGroupBox.hpp"
#include "sLabel.hpp"
#include "sComboEdit.hpp"
#include "sRadioButton.hpp"
#include "PrnDbgeh.hpp"
#include "sMemo.hpp"
#include "sEdit.hpp"
#include "sButton.hpp"
//---------------------------------------------------------------------------
struct DrawData {
	int GraphID;
	int OrderID;
	int TimeWrk;
	AnsiString FieldKey;
	TDateTime DT_Beg_Ord;
	TDateTime TM_Beg_Ord;
	AnsiString Hint1,Hint2,Hint3,Hint4,Hint5;
	DrawData() { Clear();}
	void Clear() {
		GraphID = OrderID = TimeWrk = 0;
		DT_Beg_Ord = TDateTime();
		TM_Beg_Ord = TDateTime();
	}
	void Fill(TDataSet * DSet) {
		 if (DSet->FieldByName("FLAG_KIND")->AsInteger) {
			 GraphID  = DSet->FieldByName(FieldKey)->AsInteger;
			 OrderID  = DSet->FieldByName("Orders_ID")->AsInteger;
			 TimeWrk  = DSet->FieldByName("Wrk_Minut")->AsInteger +
							DSet->FieldByName("Wrk_Day")->AsInteger * 1440;
			 DT_Beg_Ord = TDateTime(GetDateStr(DSet->FieldByName("DT_BEG")->AsDateTime));
			 TM_Beg_Ord = DSet->FieldByName("TIME_BEG")->AsDateTime;
			 Hint1      = DSet->FieldByName("HINT_STR1")->AsString;
			 Hint2      = DSet->FieldByName("HINT_STR2")->AsString;
			 Hint3      = DSet->FieldByName("HINT_STR3")->AsString;
			 Hint4      = DSet->FieldByName("HINT_STR4")->AsString;
			 Hint5      = DSet->FieldByName("HINT_STR5")->AsString;
		 }
		 else Clear();
	}
};
static DrawData SData;
namespace XXX {
using Gridseh::TGridCoord;
class TFormTrans : public TForm
{
__published:	// IDE-managed Components
	TsPanel *sPanel1;
	TsPageControl *sPageControl1;
	TsStatusBar *sStatusBar1;
	TsTabSheet *sTabSheet1;
	TsTabSheet *sTabSheet2;
	TsTabSheet *sTabSheet3;
	TsTabSheet *sTabSheet4;
	TsTabSheet *sTabSheet5;
	TsSplitter *sSplitter1;
	TsSplitter *sSplitter2;
	TsTabSheet *sTabSheet6;
	TDBGridEh *DBGridEh61;
	TsPanel *sPanel2;
	TsSplitter *sSplitter4;
	TDBGridEh *DBGridEh62;
	TDBGridEh *DBGridEh63;
	TsSplitter *sSplitter3;
	TDBGridEh *DBGridEh31;
	TsPanel *sPanel5;
	TDBGridEh *DBGridEh11;
	TDBGridEh *DBGridEh12;
	TsSplitter *sSplitter5;
	TDBGridEh *DBGridEh13;
	TMemTableEh *MemTableEh11;
	TMemTableEh *MemTableEh12;
	TMemTableEh *MemTableEh13;
	TDataSetDriverEh *DataSetDriverEh11;
	TDataSetDriverEh *DataSetDriverEh12;
	TDataSetDriverEh *DataSetDriverEh13;
	TDataSource *DataSource11;
	TDataSource *DataSource12;
	TDataSource *DataSource13;
	TQuery *Query11;
	TQuery *Query12;
	TQuery *Query13;
	TQuery *Query14;
	TIntegerField *MemTableEh11TRANS_COMPANY_ID;
	TStringField *MemTableEh11TRANS_COMPANY_NAME;
	TIntegerField *MemTableEh11TRANS_COMPANY_FLAG;
	TDateTimeField *MemTableEh11DATECHANGE;
	TIntegerField *MemTableEh11STATUS;
	TStringField *MemTableEh11Out_Flag;
	TQuery *Query15;
	TQuery *Query16;
	TComboBox *ComboBox;
	TIntegerField *MemTableEh12TRANS_TYPE_ID;
	TStringField *MemTableEh12TRANS_TYPE_NAME;
	TDateTimeField *MemTableEh12DATECHANGE;
	TIntegerField *MemTableEh12STATUS;
	TDBDateTimeEditEh *DBDateTimeEditEh;
	TDataSource *DataSource21;
	TMemTableEh *MemTableEh21;
	TDataSetDriverEh *DataSetDriverEh21;
	TQuery *Query21;
	TDataSource *DataSource22;
	TMemTableEh *MemTableEh22;
	TDataSetDriverEh *DataSetDriverEh22;
	TQuery *Query22;
	TQuery *Query24;
	TQuery *Query25;
	TDataSource *DataSource61;
	TMemTableEh *MemTableEh61;
	TDataSetDriverEh *DataSetDriverEh61;
	TQuery *Query61;
	TDataSource *DataSource62;
	TMemTableEh *MemTableEh62;
	TDataSetDriverEh *DataSetDriverEh62;
	TQuery *Query62;
	TDataSource *DataSource63;
	TMemTableEh *MemTableEh63;
	TDataSetDriverEh *DataSetDriverEh63;
	TQuery *Query63;
	TDataSource *DataSource71;
	TMemTableEh *MemTableEh71;
	TDataSetDriverEh *DataSetDriverEh71;
	TQuery *Query71;
	TIntegerField *MemTableEh61TOWN_ID;
	TStringField *MemTableEh61TOWN_NAME;
	TDateTimeField *MemTableEh61DATECHANGE;
	TIntegerField *MemTableEh61STATUS;
	TIntegerField *MemTableEh62STREET_ID;
	TStringField *MemTableEh62STREET_NAME;
	TIntegerField *MemTableEh62STREET_TYPE;
	TIntegerField *MemTableEh62TOWN_ID;
	TDateTimeField *MemTableEh62DATECHANGE;
	TIntegerField *MemTableEh62STATUS;
	TIntegerField *MemTableEh71EMPLOYEE_ID;
	TStringField *MemTableEh71FULL_NAME;
	TStringField *MemTableEh71PSWD;
	TIntegerField *MemTableEh71EMPL_RIGHTS;
	TIntegerField *MemTableEh71EMPL_TYPE;
	TStringField *MemTableEh71PHONE_NUMBER;
	TDateTimeField *MemTableEh71DATECHANGE;
	TIntegerField *MemTableEh71STATUS;
	TQuery *Query64;
	TQuery *Query65;
	TQuery *Query66;
	TQuery *Query72;
	TDataSource *DataSource31;
	TMemTableEh *MemTableEh31;
	TDataSetDriverEh *DataSetDriverEh31;
	TQuery *Query31;
	TQuery *Query32;
	TDataSource *DataSource41;
	TMemTableEh *MemTableEh41;
	TDataSetDriverEh *DataSetDriverEh41;
	TQuery *Query41;
	TQuery *Query44;
	TStringField *MemTableEh71OUT_R01;
	TStringField *MemTableEh71OUT_R02;
	TStringField *MemTableEh71OUT_R03;
	TStringField *MemTableEh71OUT_R04;
	TStringField *MemTableEh71OUT_R05;
	TStringField *MemTableEh71OUT_R06;
	TStringField *MemTableEh71OUT_R07;
	TStringField *MemTableEh71OUT_R08;
	TStringField *MemTableEh71OUT_R09;
	TStringField *MemTableEh71OUT_R10;
	TStringField *MemTableEh71OUT_R11;
	TStringField *MemTableEh71OUT_R12;
	TDBNumberEditEh *DBNumberEditEh;
	TDBEditEh *DBEditEh;
	TIntegerField *MemTableEh63DRIVER_ID;
	TStringField *MemTableEh63DRIVER_NAME;
	TStringField *MemTableEh63DRIVER_PHONE;
	TDateTimeField *MemTableEh63DATECHANGE;
	TIntegerField *MemTableEh63STATUS;
	TsTabSheet *sTabSheet7;
	TsSpeedButton *sSpeedButton1;
	TsSpeedButton *sSpeedButton2;
	TDataSource *DataSource51;
	TMemTableEh *MemTableEh51;
	TDataSetDriverEh *DataSetDriverEh51;
	TQuery *Query51;
	TQuery *Query52;
	TIntegerField *MemTableEh51OUTLAY_ID;
	TIntegerField *MemTableEh51EXPENSE_ID;
	TDateTimeField *MemTableEh51DATEMAKE;
	TStringField *MemTableEh51OUTLAY_NAME;
	TIntegerField *MemTableEh51OUTLAY_VALUE;
	TIntegerField *MemTableEh51TRANSPORT_ID;
	TDateTimeField *MemTableEh51DATECHANGE;
	TIntegerField *MemTableEh51STATUS;
	TStringField *MemTableEh51TRANSPORT_NAME;
	TStringField *MemTableEh51REG_NUMBER;
	TStringField *MemTableEh51TRANS_TYPE_NAME;
	TStringField *MemTableEh51EXPENSE_NAME;
	TDBGridEh *DBGridEh51;
	TDBGridEh *DBGridEh71;
	TStringField *MemTableEh71OUT_R13;
	TStringField *MemTableEh71OUT_R14;
	TsSpeedButton *sSpeedButton3;
	TsSpeedButton *sSpeedButton4;
	TsSpeedButton *sSpeedButton5;
	TsPanel *sPanel6;
	TsLabel *sLabelGraphBeg;
	TsDateEdit *sDateEdit3;
	TsPanel *sPanel4;
	TsLabel *sLabel51;
	TsLabel *sLabel52;
	TsDateEdit *sDateEdit5;
	TsDateEdit *sDateEdit6;
	TDBDateTimeEditEh *DBDateTimeEditEh1;
	TDBDateTimeEditEh *DBDateTimeEditEh2;
	TTimer *Timer1;
	TIntegerField *MemTableEh63TRANS_COMPANY_ID;
	TStringField *MemTableEh63TRANS_COMPANY_NAME;
	TIntegerField *MemTableEh63TRANS_COMPANY_FLAG;
	TIntegerField *MemTableEh13TRANSPORT_ID;
	TStringField *MemTableEh13TRANSPORT_NAME;
	TIntegerField *MemTableEh13TRANS_COMPANY_ID;
	TIntegerField *MemTableEh13TRANS_TYPE_ID;
	TStringField *MemTableEh13REG_NUMBER;
	TIntegerField *MemTableEh13PASS_NUMBER;
	TStringField *MemTableEh13TRANS_COMMENT;
	TIntegerField *MemTableEh13TRANS_DRIVER_ID;
	TDateTimeField *MemTableEh13DATECHANGE;
	TIntegerField *MemTableEh13STATUS;
	TStringField *MemTableEh13TRANS_COMPANY_NAME;
	TStringField *MemTableEh13TRANS_TYPE_NAME;
	TIntegerField *MemTableEh13TRANS_COMPANY_FLAG;
	TStringField *MemTableEh13DRIVER_NAME;
	TsSpeedButton *sSpeedButton8;
	TIntegerField *MemTableEh22CONTACT_ID;
	TIntegerField *MemTableEh22CLIENT_ID;
	TStringField *MemTableEh22CONTACT_NAME;
	TStringField *MemTableEh22CONTACT_PHONE;
	TIntegerField *MemTableEh22USER_ID;
	TStringField *MemTableEh22COMP_NAME;
	TDateTimeField *MemTableEh22DATECHANGE;
	TIntegerField *MemTableEh22STATUS;
	TsCheckBox *sCheckBox41;
	TsSpeedButton *sSpeedButton41;
	TsSpeedButton *sSpeedButton6;
	TPrintDBGridEh *PrintDBGridEh1;
	TIntegerField *MemTableEh51YY;
	TIntegerField *MemTableEh51MM;
	TsCheckBox *sCheckBox51;
	TsSpeedButton *sSpeedButton7;
	TsLabel *sLabel10;
	TsLabel *sLabel7;
	TsLabel *sLabel8;
	TsComboEdit *sComboEdit3;
	TsLabel *sLabel9;
	TsEdit *sEdit1;
	TsComboEdit *sComboEdit4;
	TsLabel *sLabel11;
	TDBNumberEditEh *DBNumberEditEh1;
	TsGroupBox *sGroupBox3;
	TsLabel *sLabel12;
	TsComboEdit *sComboEdit5;
	TsLabel *sLabel13;
	TsComboEdit *sComboEdit6;
	TsLabel *sLabel14;
	TsEdit *sEdit2;
	TsGroupBox *sGroupBox4;
	TsLabel *sLabel15;
	TsComboEdit *sComboEdit7;
	TsLabel *sLabel16;
	TsComboEdit *sComboEdit8;
	TsLabel *sLabel17;
	TsEdit *sEdit3;
	TsGroupBox *sGroupBox5;
	TsLabel *sLabel18;
	TsComboEdit *sComboEdit9;
	TsLabel *sLabel19;
	TsComboEdit *sComboEdit10;
	TsEdit *sEdit4;
	TsGroupBox *sGroupBox6;
	TsLabel *sLabel20;
	TsLabel *sLabel22;
	TsLabel *sLabel24;
	TsLabel *sLabel25;
	TsLabel *sLabel26;
	TsLabel *sLabel27;
	TsLabel *sLabel28;
	TsLabel *sLabel29;
	TsLabel *sLabel30;
	TsLabel *sLabel31;
	TsLabel *sLabel32;
	TDBDateTimeEditEh *DBDateTimeEditEh3;
	TsGroupBox *sGroupBox7;
	TsLabel *sLabel33;
	TsLabel *sLabel34;
	TsLabel *sLabel35;
	TsLabel *sLabel36;
	TsLabel *sLabel37;
	TComboBox *ComboBox1;
	TsLabel *sLabel38;
	TsButton *sButton1;
	TsButton *sButton2;
	TsLabel *sLabel39;
	TDBNumberEditEh *DBNumberEditEh3;
	TDBDateTimeEditEh *DBDateTimeEditEh4;
	TsEdit *sEdit6;
	TDBNumberEditEh *DBNumberEditEh4;
	TDBNumberEditEh *DBNumberEditEh5;
	TDBNumberEditEh *DBNumberEditEh6;
	TDBNumberEditEh *DBNumberEditEh7;
	TDBNumberEditEh *DBNumberEditEh8;
	TDBNumberEditEh *DBNumberEditEh9;
	TComboBox *ComboBox3;
	TComboBox *ComboBox4;
	TDBNumberEditEh *DBNumberEditEh11;
	TDBDateTimeEditEh *DBDateTimeEditEh7;
	TDBNumberEditEh *DBNumberEditEh12;
	TDBDateTimeEditEh *DBDateTimeEditEh8;
	TDBNumberEditEh *DBNumberEditEh14;
	TsMemo *sMemo2;
	TIntegerField *MemTableEh51OUTLAY_TYPE;
	TStringField *MemTableEh51OUTLAY_TYPE_STR;
	TIntegerField *MemTableEh51DRIVER_ID;
	TStringField *MemTableEh51DRIVER_NAME;
	TQuery *Query45;
	TMemTableEh *MemTableEh43;
	TDataSource *DataSource43;
	TIntegerField *MemTableEh41SORT_ORDER;
	TIntegerField *MemTableEh41FLAG_MES;
	TIntegerField *MemTableEh41FLAG_KIND;
	TIntegerField *MemTableEh41GRAPH_ID;
	TIntegerField *MemTableEh41TRANSPORT_ID;
	TStringField *MemTableEh41TRANSPORT_NAME;
	TIntegerField *MemTableEh41TRANS_COMPANY_ID;
	TIntegerField *MemTableEh41TRANS_TYPE_ID;
	TStringField *MemTableEh41REG_NUMBER;
	TIntegerField *MemTableEh41PASS_NUMBER;
	TIntegerField *MemTableEh41TRANS_HOUR_TAX;
	TIntegerField *MemTableEh41TRANS_DIST_TAX;
	TDateTimeField *MemTableEh41TRANS_TIME_ADD;
	TDateTimeField *MemTableEh41TRANS_TIME_MIN;
	TStringField *MemTableEh41TRANS_COMMENT;
	TStringField *MemTableEh41TRANS_COMPANY_NAME;
	TStringField *MemTableEh41TRANS_TYPE_NAME;
	TIntegerField *MemTableEh41TRANS_COMPANY_FLAG;
	TIntegerField *MemTableEh41MIN_BEG;
	TIntegerField *MemTableEh41MIN_END;
	TIntegerField *MemTableEh41TRANS_DRIVER_ID;
	TIntegerField *MemTableEh41DRIVER_ID;
	TStringField *MemTableEh41DRIVER_NAME;
	TStringField *MemTableEh41TRANS_DRIVER_NAME;
	TStringField *MemTableEh41DRIVER_PHONE;
	TIntegerField *MemTableEh41ORDERS_ID;
	TStringField *MemTableEh41HINT_STR1;
	TStringField *MemTableEh41HINT_STR2;
	TStringField *MemTableEh41HINT_STR3;
	TStringField *MemTableEh41HINT_STR4;
	TStringField *MemTableEh41HINT_STR5;
	TIntegerField *MemTableEh41WRK_MINUT;
	TIntegerField *MemTableEh41WRK_DAY;
	TDateTimeField *MemTableEh41DT_BEG;
	TDateTimeField *MemTableEh41TIME_BEG;
	TIntegerField *MemTableEh41STATUS;
	TDateTimeField *MemTableEh41DATECHANGE;
	TIntegerField *MemTableEh41ORDER_STATE;
	TStringField *MemTableEh41ORDER_STATE_STR;
	TIntegerField *MemTableEh41DUMMY;
	TIntegerField *MemTableEh43SORT_ORDER;
	TIntegerField *MemTableEh43FLAG_MES;
	TIntegerField *MemTableEh43FLAG_KIND;
	TIntegerField *MemTableEh43GRAPH_ID;
	TIntegerField *MemTableEh43TRANSPORT_ID;
	TStringField *MemTableEh43TRANSPORT_NAME;
	TIntegerField *MemTableEh43TRANS_COMPANY_ID;
	TIntegerField *MemTableEh43TRANS_TYPE_ID;
	TStringField *MemTableEh43REG_NUMBER;
	TIntegerField *MemTableEh43PASS_NUMBER;
	TIntegerField *MemTableEh43TRANS_HOUR_TAX;
	TIntegerField *MemTableEh43TRANS_DIST_TAX;
	TDateTimeField *MemTableEh43TRANS_TIME_ADD;
	TDateTimeField *MemTableEh43TRANS_TIME_MIN;
	TStringField *MemTableEh43TRANS_COMMENT;
	TStringField *MemTableEh43TRANS_COMPANY_NAME;
	TStringField *MemTableEh43TRANS_TYPE_NAME;
	TIntegerField *MemTableEh43TRANS_COMPANY_FLAG;
	TIntegerField *MemTableEh43MIN_BEG;
	TIntegerField *MemTableEh43MIN_END;
	TIntegerField *MemTableEh43TRANS_DRIVER_ID;
	TIntegerField *MemTableEh43DRIVER_ID;
	TStringField *MemTableEh43DRIVER_NAME;
	TStringField *MemTableEh43TRANS_DRIVER_NAME;
	TStringField *MemTableEh43DRIVER_PHONE;
	TIntegerField *MemTableEh43ORDERS_ID;
	TStringField *MemTableEh43HINT_STR1;
	TStringField *MemTableEh43HINT_STR2;
	TStringField *MemTableEh43HINT_STR3;
	TStringField *MemTableEh43HINT_STR4;
	TStringField *MemTableEh43HINT_STR5;
	TIntegerField *MemTableEh43WRK_MINUT;
	TIntegerField *MemTableEh43WRK_DAY;
	TDateTimeField *MemTableEh43DT_BEG;
	TDateTimeField *MemTableEh43TIME_BEG;
	TIntegerField *MemTableEh43STATUS;
	TDateTimeField *MemTableEh43DATECHANGE;
	TIntegerField *MemTableEh43ORDER_STATE;
	TStringField *MemTableEh43ORDER_STATE_STR;
	TIntegerField *MemTableEh43DUMMY;
	TDataSetDriverEh *DataSetDriverEh43;
	TQuery *Query43;
	TComboBox *ComboBox5;
	TsLabel *sLabel21;
	TDBNumberEditEh *DBNumberEditEh10;
	TsLabel *sLabel23;
	TComboBox *ComboBox6;
	TsLabel *sLabel40;
	TComboBox *ComboBox7;
	TIntegerField *MemTableEh12TRANS_HOUR_TAX;
	TIntegerField *MemTableEh12TRANS_DIST_TAX;
	TDateTimeField *MemTableEh12TRANS_TIME_MIN;
	TDateTimeField *MemTableEh12TRANS_TIME_ADD;
	TsPanel *sPanel3;
	TDBGridEh *DBGridEh22;
	TsSplitter *sSplitter8;
	TDBGridEh *DBGridEh23;
	TDataSource *DataSource23;
	TMemTableEh *MemTableEh23;
	TDataSetDriverEh *DataSetDriverEh23;
	TQuery *Query23;
	TQuery *Query26;
	TDBNumberEditEh *DBNumberEditEh13;
	TsLabel *sLabel43;
	TDBGridEh *DBGridEh41;
	TDBGridEh *DBGridEh43;
	TsPanel *sPanel7;
	TsCheckBox *sCheckBox20;
	TsCheckBox *sCheckBox22;
	TIntegerField *MemTableEh21CLIENT_ID;
	TStringField *MemTableEh21CLIENT_NAME;
	TIntegerField *MemTableEh21CLIENT_TYPE;
	TStringField *MemTableEh21CLIENT_TYPE_STR;
	TIntegerField *MemTableEh21CLIENT_FLAG;
	TStringField *MemTableEh21CLIENT_FLAG_STR;
	TStringField *MemTableEh21CONTACT_NAME;
	TStringField *MemTableEh21CONTACT_PHONE;
	TIntegerField *MemTableEh21WORK_TYPE_ID;
	TStringField *MemTableEh21WORK_TYPE_NAME;
	TDateTimeField *MemTableEh21DATECHANGE;
	TIntegerField *MemTableEh21STATUS;
	TsCheckBox *sCheckBox21;
	TsSpeedButton *sSpeedButton10;
	TsSpeedButton *sSpeedButton17;
	TsLabel *sLabelGraphEnd;
	TsGroupBox *sGroupBox1;
	TsLabel *sLabel5;
	TsCheckBox *sCheckBox2;
	TsCheckBox *sCheckBox3;
	TsCheckBox *sCheckBox5;
	TsCheckBox *sCheckBox7;
	TsCheckBox *sCheckBox8;
	TsCheckBox *sCheckBox9;
	TsCheckBox *sCheckBox10;
	TsCheckBox *sCheckBox1;
	TsCheckBox *sCheckBox4;
	TsSpeedButton *sSpeedButton11;
	TsSpeedButton *sSpeedButton12;
	TsSpeedButton *sSpeedButton13;
	TsSpeedButton *sSpeedButton14;
	TsSpeedButton *sSpeedButton15;
	TsLabel *sLabel1;
	TsComboBox *sComboBox1;
	TsLabel *sLabel2;
	TsDateEdit *sDateEdit1;
	TsLabel *sLabel3;
	TsDateEdit *sDateEdit2;
	TsLabel *sLabel6;
	TsComboEdit *sComboEdit2;
	TsLabel *sLabel4;
	TsComboEdit *sComboEdit1;
	TsSpeedButton *sSpeedButton9;
	TsSpeedButton *sSpeedButton16;
	TsSpeedButton *sSpeedButton18;
	TsSpeedButton *sSpeedButton19;
	TsSpeedButton *sSpeedButton21;
	TsSpeedButton *sSpeedButton20;
	TsSpeedButton *sSpeedButton22;
	TsSpeedButton *sSpeedButton23;
	TsSpeedButton *sSpeedButton24;
	TsSpeedButton *sSpeedButton25;
	TIntegerField *MemTableEh23CLIENT_TAX_ID;
	TIntegerField *MemTableEh23CLIENT_ID;
	TIntegerField *MemTableEh23TRANS_TYPE_ID;
	TStringField *MemTableEh23TRANS_TYPE_NAME;
	TIntegerField *MemTableEh23WORK_TYPE_ID;
	TStringField *MemTableEh23WORK_TYPE_NAME;
	TIntegerField *MemTableEh23CLIENT_HOUR_TAX;
	TIntegerField *MemTableEh23CLIENT_DIST_TAX;
	TDateTimeField *MemTableEh23CLIENT_TIME_MIN;
	TDateTimeField *MemTableEh23CLIENT_TIME_ADD;
	TIntegerField *MemTableEh23CLIENT_DOG_TAX;
	TIntegerField *MemTableEh23FLAG_CALC_INCOME;
	TStringField *MemTableEh23FLAG_CALC_INCOME_STR;
	TIntegerField *MemTableEh23USER_ID;
	TStringField *MemTableEh23COMP_NAME;
	TDateTimeField *MemTableEh23DATECHANGE;
	TIntegerField *MemTableEh23STATUS;
	TIntegerField *MemTableEh31ORDERS_ID;
	TDateTimeField *MemTableEh31DT_MAKE;
	TDateTimeField *MemTableEh31DT_BEG;
	TDateTimeField *MemTableEh31TIME_BEG;
	TIntegerField *MemTableEh31BEF_MINUT;
	TDateTimeField *MemTableEh31TIME_BEF;
	TIntegerField *MemTableEh31WRK_DAY;
	TIntegerField *MemTableEh31WRK_MINUT;
	TDateTimeField *MemTableEh31TIME_WRK;
	TDateTimeField *MemTableEh31DAY_END;
	TDateTimeField *MemTableEh31DT_END;
	TIntegerField *MemTableEh31DAY_SUM;
	TDateTimeField *MemTableEh31TIME_SUM;
	TStringField *MemTableEh31TIME_SUM_STR;
	TStringField *MemTableEh31TIME_SUM_STR_F;
	TIntegerField *MemTableEh31ORDER_STATE;
	TStringField *MemTableEh31ORDER_STATE_STR;
	TIntegerField *MemTableEh31ORDER_TYPE;
	TStringField *MemTableEh31ORDER_TYPE_STR;
	TIntegerField *MemTableEh31CLIENT_ID;
	TStringField *MemTableEh31CLIENT_NAME;
	TIntegerField *MemTableEh31WORK_TYPE_ID;
	TStringField *MemTableEh31WORK_TYPE_NAME;
	TIntegerField *MemTableEh31CONTACT_ID;
	TStringField *MemTableEh31CONTACT_NAME;
	TStringField *MemTableEh31CONTACT_PHONE;
	TIntegerField *MemTableEh31TRANS_TYPE_ID;
	TStringField *MemTableEh31TRANS_TYPE_NAME;
	TIntegerField *MemTableEh31PASS_NEED;
	TIntegerField *MemTableEh31TRANSPORT_ID;
	TStringField *MemTableEh31TRANSPORT_NAME;
	TStringField *MemTableEh31REG_NUMBER;
	TIntegerField *MemTableEh31PASS_NUMBER;
	TIntegerField *MemTableEh31DRIVER_ID;
	TStringField *MemTableEh31DRIVER_NAME;
	TStringField *MemTableEh31DRIVER_PHONE;
	TIntegerField *MemTableEh31DRIVER_HAND_MONEY;
	TIntegerField *MemTableEh31BEG_TOWN_ID;
	TIntegerField *MemTableEh31END_TOWN_ID;
	TIntegerField *MemTableEh31BEG_STREET_ID;
	TIntegerField *MemTableEh31END_STREET_ID;
	TStringField *MemTableEh31BEG_ADDR_NAME;
	TStringField *MemTableEh31END_ADDR_NAME;
	TIntegerField *MemTableEh31RET_TO_START;
	TStringField *MemTableEh31RET_TO_START_STR;
	TIntegerField *MemTableEh31CLIENT_TAX_ID;
	TDateTimeField *MemTableEh31TIME_ADD;
	TDateTimeField *MemTableEh31TIME_MIN;
	TIntegerField *MemTableEh31HOUR_TAX;
	TIntegerField *MemTableEh31DIST_TAX;
	TIntegerField *MemTableEh31DOG_TAX;
	TIntegerField *MemTableEh31DIST_RES;
	TFloatField *MemTableEh31PAY_CALC;
	TFloatField *MemTableEh31PAY_RES;
	TIntegerField *MemTableEh31PAY_TYPE;
	TStringField *MemTableEh31PAY_TYPE_STR;
	TIntegerField *MemTableEh31PAY_AVC;
	TIntegerField *MemTableEh31PAY_AVC_STATE;
	TStringField *MemTableEh31PAY_AVC_STATE_STR;
	TIntegerField *MemTableEh31PAY_AVC_RECEIVER;
	TStringField *MemTableEh31PAY_AVC_RECEIVER_STR;
	TFloatField *MemTableEh31PAY_REST;
	TIntegerField *MemTableEh31PAY_REST_STATE;
	TStringField *MemTableEh31PAY_REST_STATE_STR;
	TIntegerField *MemTableEh31PAY_REST_RECEIVER;
	TStringField *MemTableEh31PAY_REST_RECEIVER_STR;
	TIntegerField *MemTableEh31ORDER_FLAG;
	TIntegerField *MemTableEh31EXC_PAY;
	TDateTimeField *MemTableEh31EXC_PAY_DATE;
	TIntegerField *MemTableEh31MNG_PAY;
	TDateTimeField *MemTableEh31MNG_PAY_DATE;
	TIntegerField *MemTableEh31DRV_PAY;
	TIntegerField *MemTableEh31MANAGER_ID;
	TStringField *MemTableEh31COMMENT;
	TDateTimeField *MemTableEh31DATECHANGE;
	TIntegerField *MemTableEh31STATUS;
	TDateTimeField *MemTableEh31TRANS_TIME_MIN;
	TDateTimeField *MemTableEh31TRANS_TIME_ADD;
	TIntegerField *MemTableEh31TRANS_HOUR_TAX;
	TIntegerField *MemTableEh31TRANS_DIST_TAX;
	TStringField *MemTableEh31BEG_STREET_NAME;
	TStringField *MemTableEh31BEG_TOWN_NAME;
	TStringField *MemTableEh31END_STREET_NAME;
	TStringField *MemTableEh31END_TOWN_NAME;
	TStringField *MemTableEh31FULL_NAME;
	TIntegerField *MemTableEh31TRANS_COMPANY_ID;
	TStringField *MemTableEh31TRANS_COMPANY_NAME;
	TIntegerField *MemTableEh31TRANS_COMPANY_FLAG;
	TIntegerField *MemTableEh31SUM_MINUT;
	TFloatField *MemTableEh31INCOME;
	TIntegerField *MemTableEh31SRC_ORDER_ID;
	TIntegerField *MemTableEh31FLAG_CALC_INCOME;
	TStringField *MemTableEh31FLAG_CALC_INCOME_STR;
	TStringField *MemTableEh31TAX_TAKE_STR;
	TStringField *MemTableEh41COMMENT;
	TStringField *MemTableEh43COMMENT;
	TsSpeedButton *sSpeedButton43;
	TStringField *MemTableEh31TRANS_COMMENT;
	TsPanel *sPanel8;
	TDBGridEh *DBGridEh21;
	TsMemo *sMemo3;
	TStringField *MemTableEh21COMMENT;
	TStringField *MemTableEh11COMMENT;
	TsSpeedButton *sSpeedButton44;
	TsGroupBox *sGroupBox2;
	TsComboEdit *sComboEdit11;
	TsEdit *sEdit5;
	TsLabel *sLabel41;
	TsLabel *sLabel42;
	TDBNumberEditEh *DBNumberEditEh2;
	TsLabel *sLabel45;
	TsPanel *sPanel9;
	TsLabel *sLabel46;
	TsLabel *sLabel47;
	TsLabel *sLabel48;
	TsLabel *sLabel49;
	TsLabel *sLabel50;
	TsLabel *sLabel53;
	TComboBox *ComboBox2;
	TsMemo *sMemo1;
	TsSpeedButton *sSpeedButton45;
	TsSpeedButton *sSpeedButton35;
	TsCheckBox *sCheckBox42;
	TsLabel *sLabel44;
	TsCheckBox *sCheckBox6;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sPageControl1Change(TObject *Sender);
	void __fastcall MemTableEhAfterClose(TDataSet *DataSet);
	void __fastcall MemTableEhAfterOpen(TDataSet *DataSet);
	void __fastcall MemTableEhAfterScroll(TDataSet *DataSet);
	void __fastcall MemTableEhBeforeScroll(TDataSet *DataSet);
	void __fastcall MemTableEhCalcFields(TDataSet *DataSet);
	void __fastcall MemTableEhFilterRecord(TDataSet *DataSet, bool &Accept);
	void __fastcall DBEditEhExit(TObject *Sender);
	void __fastcall DBEditEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEhDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumnEh *Column, TGridDrawStateEh State);
	void __fastcall DBGridEhGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont,
          TColor &Background, TGridDrawStateEh State);
	void __fastcall DBGridEhKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEhKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall DBGridEhEnter(TObject *Sender);
	void __fastcall DBGridEhExit(TObject *Sender);
	void __fastcall DBGridEhSortMarkingChanged(TObject *Sender);
	void __fastcall sCheckBoxClick(TObject *Sender);
	void __fastcall sSpeedButtonClick(TObject *Sender);
	void __fastcall sDateEditAcceptDate(TObject *Sender, TDateTime &aDate, bool &CanAccept);
	void __fastcall sComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sComboBox1CloseUp(TObject *Sender);
	void __fastcall DBDateTimeEditEhChange(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall sPageControl1Changing(TObject *Sender, bool &AllowChange);
	void __fastcall sComboEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sComboEditButtonClick(TObject *Sender);
	void __fastcall DBGridEhDblClick(TObject *Sender);
	void __fastcall sCheckBoxAddClick(TObject *Sender);
	void __fastcall DBGridEh31ApplyFilter(TObject *Sender);
	void __fastcall sMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sMemoExit(TObject *Sender);
	void __fastcall DBGridEhCellMouseClick(TCustomGridEh *Grid, TGridCoord &Cell,
			 TMouseButton Button, TShiftState Shift, int X, int Y, bool &Processed);
	void __fastcall DBGridEhRowDetailPanelHide(TCustomDBGridEh *Sender, bool &CanHide);
	void __fastcall DBGridEhRowDetailPanelShow(TCustomDBGridEh *Sender, bool &CanShow);
	void __fastcall sComboEditDetailButtonClick(TObject *Sender);
	void __fastcall DetailEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DetailEditExit(TObject *Sender);
	void __fastcall sButtonClick(TObject *Sender);
	void __fastcall DetailEditEnter(TObject *Sender);
	void __fastcall DBGridEhColumnsDataHintShow(TCustomDBGridEh *Sender, TPoint &CursorPos,
			 TGridCoord &Cell, TPoint &InCellCursorPos, TColumnEh *Column, TDBGridEhDataHintParams *&Params,
          bool &Processed);
	void __fastcall sPageControl1Exit(TObject *Sender);
	void __fastcall DBGridEh41CellClick(TColumnEh *Column);
	void __fastcall DBGridEh41ColEnter(TObject *Sender);






private:	// User declarations
public:		// User declarations
	int PageTag;
	int SelIndex;
	int SelViewID;
	int SelFilterID;

	int CurTransCompID;
	int CurTransportID;
	int CurTransTypeID;

	int CurOrderID;
	int CurClientID;
	int PrvGraphID;
	int CurGraphID;
	int CurDriverID;
	int CurGraphCol;
	int PrvGraphCol;

	int MaxFrozenCols;
	int NumDetailCtrl;
	int AllDetailCtrl;
	bool RestoreEditMulti;
//	bool FirstOpenDetail;
	AnsiString FilterName;
	AnsiString SelectResultStr;
	TObject* RDPWCtrl;
	int Minuts_All,Minuts_Rnd;

	GridData GDataTransComp;
	GridData GDataTransType;
	GridData GDataTransport;

	GridData GDataClient;
	GridData GDataContact;
	GridData GDataClientTax;

	GridData GDataOrders;
	GridData GDataGraph;
	GridData GDataDetail;

	GridData GDataEmployee;
	GridData GDataTown;
	GridData GDataStreet;
	GridData GDataDriver;

	GridData GDataOutlay;

	GridData* WrkGData;
	GridData* DefGData;

	TDateTime DT_Beg_Ord,DT_End_Ord,DT_Beg_Exp,DT_End_Exp,DT_Graph;// DT_Beg_Grp,DT_End_Grp;
	TDateTime TM_Beg_Grp,TM_End_Grp;

	AnsiString DefColWidth;

	typedef std::vector<int>  Vect;
	std::map<int,Vect>        TransWork;
	std::map<int,AnsiString>  GraphHint;
	std::map<int,DrawData>    DrawMap;
	std::vector<TWinControl*> WCtrlVect;
	std::vector<AnsiString>   FNameVect;
	std::vector<bool>         DetailEditCng;
	std::vector<int>          ShowTransVect;

	FilterCols OrderFilter;

	int SumPayCalc,SumPayRes, SumPayAvc, SumPayRest, SumPayExc,SumPayMng,SumPayDrv,SumIncCalc,SumOutlay;
	__fastcall TFormTrans(TComponent* Owner);
	bool __fastcall TFormTrans::ChooseStartPage();
	void __fastcall TFormTrans::InitGData();
	void __fastcall TFormTrans::InitCommon();
	void __fastcall TFormTrans::SetCommonExtParams(GridData& GData);
	void __fastcall TFormTrans::CreateEditList();

	void __fastcall TFormTrans::CalcMinutes();
	void __fastcall TFormTrans::SetGraphLabels();
	void __fastcall TFormTrans::CreateGraphColumns();
	void __fastcall TFormTrans::EnumtateOrderColums(TDBGridEh* Grid);

	AnsiString __fastcall TFormTrans::GetCurColWidtList();


	void __fastcall TFormTrans::SelectPage();
	void __fastcall TFormTrans::ChangePage();
	void __fastcall TFormTrans::OpenPage();
	void __fastcall TFormTrans::SetWrkGData();
	void __fastcall TFormTrans::EnablePageCtrl();

	GridData& __fastcall TFormTrans::GetGDataRef(TObject* Sender);
	bool __fastcall TFormTrans::RefreshOneRow(GridData& GData,TDataSet* DSet);

	AnsiString __fastcall TFormTrans::GetErrMsg(GridData& GData,int Error);
	AnsiString __fastcall TFormTrans::GetErrMsgBody(int Tag,int Error);
	AnsiString __fastcall TFormTrans::GetSelEditParams();


	void __fastcall TFormTrans::SwapEmplRightBit();
	bool __fastcall TFormTrans::GetSQL(TDataSet* DSet);

	bool __fastcall TFormTrans::GetTransCompanyID(TForm* Frm, int Left,int &ID,TParams*&);
	bool __fastcall TFormTrans::GetTransTypeID(TForm* Frm, int Left,int &ID,TParams*&);
	bool __fastcall TFormTrans::GetEmployeeID(TForm* Frm, int Left,int &ID,TParams*&);
	bool __fastcall TFormTrans::GetTransportID(TForm* Frm, int Left,int &ID,TParams*&);
	bool __fastcall TFormTrans::GetClientID(TForm* Frm, int Left,int &ID,TParams*&);
	bool __fastcall TFormTrans::GetContactID(TForm* Frm, int Left,int &ID,TParams*&);
	bool __fastcall TFormTrans::GetTownID(TForm* Frm, int Left,int &ID,TParams*&);
	bool __fastcall TFormTrans::GetStreetID(TForm* Frm, int Left,int &ID,TParams*&);
   bool __fastcall TFormTrans::GetDriverID(TForm* Frm, int Left,int &ID,TParams*&);
   bool __fastcall TFormTrans::GetExpenseID(TForm* Frm, int Left,int &ID,TParams*&);
   bool __fastcall TFormTrans::GetWorkTypeID(TForm* Frm, int Left,int &ID,TParams*&);

//	void __fastcall TFormTrans::SetOrdersBitMask();
	void __fastcall TFormTrans::SetEditBitMask(TDataSet *DataSet);

	void __fastcall TFormTrans::RestoreEditMultiFlag();

	TsCheckBox* __fastcall TFormTrans::GetCurrentCBox();
	void __fastcall TFormTrans::ShowCurColumnGroup(TDBGridEh* Grid);
	void __fastcall TFormTrans::HideCurColumnGroup(TDBGridEh* Grid);


	void __fastcall TFormTrans::HideCurrentColumn(TDBGridEh* Grid);
	void __fastcall TFormTrans::ShowNextColumn(TDBGridEh* Grid,int Shift);
	void __fastcall TFormTrans::ShowNeighbours(TDBGridEh* Grid);
	void __fastcall TFormTrans::ShowAllColumns(TDBGridEh* Grid, bool Show);

	void __fastcall TFormTrans::SetDefaultValue(TDBGridEh* Grid);
	void __fastcall TFormTrans::SetDefaultValue(TDBGridEh* Grid,int Idx);

	void __fastcall TFormTrans::AddCurrentRow(GridData& GData, int Add, bool Show, bool Clear = false);
	void __fastcall TFormTrans::ShowSummary(TDBGridEh* Grid);
	void __fastcall TFormTrans::ClearSums();
	void __fastcall TFormTrans::RestoreMultiFlag();

	void __fastcall TFormTrans::CheckRecordByFilter();
	bool __fastcall TFormTrans::RecordNotInSelectCondition();
	void __fastcall TFormTrans::ProcRefreshPage();
	void __fastcall TFormTrans::SaveCurrentView();
	void __fastcall TFormTrans::PrintGrid();
	void __fastcall TFormTrans::ProcResultViewWidth(AnsiString& WdtList, bool SaveCurState);
	bool __fastcall TFormTrans::SelCurrentView(bool Sel);
	void __fastcall TFormTrans::FindOrder();
	void __fastcall TFormTrans::FindOrder(int OrderID);


	void __fastcall TFormTrans::SaveViewWidth();
	void __fastcall TFormTrans::ProcHistory(bool All);

	AnsiString __fastcall TFormTrans::TranslateName(AnsiString FldName);
	AnsiString __fastcall TFormTrans::TransportCanBeChanged();

	void __fastcall TFormTrans::MoveGraphDay(int Shift);
	void __fastcall TFormTrans::ToggleShowSelected (GridData& GData);
	void __fastcall TFormTrans::ToggleShowCost(bool Show);

	void __fastcall TFormTrans::ToggleOrdersEditMode(bool Set);

	void __fastcall TFormTrans::StoreOrdersTbl();
	void __fastcall TFormTrans::ChangeTransport();
	void __fastcall TFormTrans::ChangeDriver();
	void __fastcall TFormTrans::ClearTransport();
   void __fastcall TFormTrans::ClearTransportOne(int OrdersID);

//	bool __fastcall TFormTrans::AcceptRecord(TDataSet *DataSet);
	bool __fastcall TFormTrans::FillHintStructures(TDataSet *DataSet);


	void __fastcall TFormTrans::ProcFilter();
	void __fastcall TFormTrans::AttachOuterTransport();
	void __fastcall TFormTrans::DetachOuterTransport();
	bool __fastcall TFormTrans::CheckOrderFilter();
	bool __fastcall TFormTrans::GetCurFldCheck(AnsiString& FldName,FieldFilter& FF);
	bool __fastcall TFormTrans::CheckIntValue(int IVal,FieldFilter& FF);
	bool __fastcall TFormTrans::CheckStrValue(AnsiString& SVal,FieldFilter& FF);
	bool __fastcall TFormTrans::CheckDateValue(TDateTime DT,FieldFilter& FF);
	bool __fastcall TFormTrans::CheckTimeValue(TDateTime DT,FieldFilter& FF);
	void __fastcall TFormTrans::ClearSelView();
	void __fastcall TFormTrans::ClearFilter();

	void __fastcall TFormTrans::RestoreValue(RestValue& RestData, bool CurrentCol);
	int  __fastcall TFormTrans::FindRestColumn(TDBGridColumnsEh* Columns,RestValue& RestData);
	void __fastcall TFormTrans::ShowOrders(TDateTime DT);
	void __fastcall TFormTrans::CopyOrder();
	void __fastcall TFormTrans::DublicateOrder();
	void __fastcall TFormTrans::ShowCopiedOrders(int OrderID);
	void __fastcall TFormTrans::SetAfterScroll(TDataSet *DataSet);
	void __fastcall TFormTrans::DrawZone(DrawData& DD,const TRect &Rect, int MinBeg, int MinEnd, TColor Color);

	void __fastcall TFormTrans::DrawColumnCell(const TRect &Rect,int DataCol, TColumnEh *Column, TGridDrawStateEh State);

	AnsiString __fastcall TFormTrans::GetHintStrByPoint(int Col,int Row,TColumnEh *Column,TPoint &InCellCursorPos);
	AnsiString __fastcall TFormTrans::GetHintStrByPointInDrawData(int Col,int Row,TColumnEh *Column,TPoint &InCellCursorPos);
	AnsiString __fastcall TFormTrans::GetDrawDataHint(DrawData& DD, int Col,TColumnEh *Column,TPoint &InCellCursorPos);



	void __fastcall TFormTrans::FillDetailEdit(TWinControl* Wctrl);
	void __fastcall TFormTrans::FillRowDetailPanel();
	void __fastcall TFormTrans::GoToNext(TObject *Sender, bool Forward);
	bool __fastcall TFormTrans::DetailEditChanged(TObject *Sender);
	void __fastcall TFormTrans::ClearDetailParam(AnsiString FName);
	bool __fastcall TFormTrans::GetDetailStreetID(bool Beg, int& ID);
	bool __fastcall TFormTrans::GetDetailTransportID(int &ID);
	bool __fastcall TFormTrans::GetDetailDriverID(int &ID);


	void __fastcall TFormTrans::CloseRowDetailPanel();
	void __fastcall TFormTrans::SaveDetailPanel();
	void __fastcall TFormTrans::ResetDetailPanel();
	int __fastcall TFormTrans::GetCurrentID(TObject *Sender, int *IBase = NULL);
	int __fastcall TFormTrans::GetCurrentID(AnsiString IName, int* BaseID = NULL);

	void __fastcall TFormTrans::ClearDetailComboEdit(TObject *Sender);
	void __fastcall TFormTrans::ClearDetailEditText(TObject *Sender);
	void __fastcall TFormTrans::RestoreDetailEditText(TObject *Sender);
	void __fastcall TFormTrans::ShowDetailEditPopup(TObject *Sender);
	void __fastcall TFormTrans::SetDetailEditColor(TObject *Sender,TColor Color);
	void __fastcall TFormTrans::SetDetailEditText(TObject *Sender,AnsiString Txt);
	void __fastcall TFormTrans::ShowCalcFields();
	void __fastcall TFormTrans::StoreChanges(TObject *Sender,int Idx,bool Cng);
	void __fastcall TFormTrans::CalcIncomeField();

	void __fastcall TFormTrans::RefreshGraphRow(TDataSet* DSet);
	void __fastcall TFormTrans::ClearTransportFromDetail();
	void __fastcall TFormTrans::ClearGraphDate();
	void __fastcall TFormTrans::WriteMemo();
	void __fastcall TFormTrans::EditDriverGraph();
   void __fastcall TFormTrans::ClearDriver();
   void __fastcall TFormTrans::GoToCurrentOrder();


/*
BEGIN_MESSAGE_MAP
	 MESSAGE_HANDLER(WM_MOUSEMOVE, TWMMouse,      MyMouseMove);
	 MESSAGE_HANDLER(WM_MOUSEWHEEL,TWMMouseWheel, MyMouseWheel);
	 MESSAGE_HANDLER(WM_COMMAND,   TMessage,      MyCommand);
END_MESSAGE_MAP(TForm);
	MESSAGE void MyMouseMove(TWMMouse& Msg);
	MESSAGE void MyMouseWheel(TWMMouseWheel& Msg);
	MESSAGE void MyCommand(TMessage& Msg);
*/
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTrans *FormTrans;
};

//---------------------------------------------------------------------------
#endif
