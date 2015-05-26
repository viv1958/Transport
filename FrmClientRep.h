//---------------------------------------------------------------------------

#ifndef FrmClientRepH
#define FrmClientRepH
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
//---------------------------------------------------------------------------
class TFormClientRep : public TForm
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
	TsLabel *sLabel1;
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


private:	// User declarations
public:		// User declarations
   int PageTag;
	int ClientID;
	int CurMM, CurYY,SelMM;
	int MaxMM, MaxYY,SelYY;

	TDateTime DT_Beg;
	TDateTime DT_End;
	GridData *WrkGData;
	GridData GDataOrders;
	int SumPayCalc, SumPayRes, SumPayAvc, SumPayRest;
   AnsiString ClientName;
	__fastcall TFormClientRep::TFormClientRep(TComponent* Owner,int ClientID, AnsiString ClientName);

	void __fastcall TFormClientRep::SetClient(int ClientID, AnsiString ClientName);
	void __fastcall TFormClientRep::SetDates(int MM,int YY);
	void __fastcall TFormClientRep::InitCommon();

	void __fastcall TFormClientRep::SetButtonCaption(int Mon);
	void __fastcall TFormClientRep::InitGData();
	bool __fastcall TFormClientRep::SetSQL(TDataSet* DSet);
	void __fastcall TFormClientRep::CloseAll();
	void __fastcall TFormClientRep::ProcRefreshPage();
	void __fastcall TFormClientRep::ProcHistory(bool All);
	void __fastcall TFormClientRep::ShowMonth(int Shift);
	void __fastcall TFormClientRep::SelectClient();
	void __fastcall TFormClientRep::SetPage();

	AnsiString __fastcall TFormClientRep::TranslateName(AnsiString FldName);
   GridData&  __fastcall TFormClientRep::GetGDataRef(TObject* Sender);

	void __fastcall TFormClientRep::ShowLowFooter(TDBGridEh* Grid,TDataSet *DataSet, int Item);
	void __fastcall TFormClientRep::ShowLowFooter(TDataSet *DataSet);
	void __fastcall TFormClientRep::ShowHighFooter(TDataSet *DataSet);

	void __fastcall TFormClientRep::PrintReport();
	void __fastcall TFormClientRep::ClearSums();
	void __fastcall TFormClientRep::AddCurrentRow(GridData& GData,int Mul, bool Show, bool Clear);


};
void ShowClientReport(int ClientID, AnsiString ClientName);

//---------------------------------------------------------------------------
extern PACKAGE TFormClientRep *FormClientRep;
//---------------------------------------------------------------------------
#endif
