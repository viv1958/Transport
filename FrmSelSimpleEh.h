//---------------------------------------------------------------------------

#ifndef FrmSelSimpleEhH
#define FrmSelSimpleEhH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Mask.hpp>
#include "DBCtrlsEh.hpp"
#include "MemTableEh.hpp"
#include "DataDriverEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "MemTableDataEh.hpp"
#include "sComboEdit.hpp"
#include "sCustomComboEdit.hpp"
#include "sMaskEdit.hpp"
#include "sPanel.hpp"
#include "sCheckBox.hpp"
#include "sEdit.hpp"
#include "sLabel.hpp"
#include "sSpeedButton.hpp"
#include "sStatusBar.hpp"
#include "DBAxisGridsEh.hpp"
#include "DBGridEhToolCtrls.hpp"
#include "ToolCtrlsEh.hpp"
class SelParamData : public GridData{
   public:  //enum EntryType {SIMPL = 0};
				enum ParamData {NO_FLAGS = 0,   NO_PANEL = 0x0001,INC_SEARCH = 0x0002, SEL_BTN_VISIBLE = 0x0004, EDIT_FORM = 0x0080};
            int Top;
            int Left;
            int MaxWidth;
            int MaxHeight;
//            ParamData SPFlags;
            int SPFlags;
            //EntryType SpecEntry;


            AnsiString Caption;
            AnsiString SQL;
            AnsiString TitleList;
            AnsiString FieldList;
            AnsiString WidthList;
            AnsiString SProcName;
				AnsiString FormatList;
				AnsiString EditQuerySQL;

            TDataSet*  OuterDSet;

				typedef void  __fastcall (*FunAfterCreate) (GridData& GData);
				FunAfterCreate AfterCreate;

				void InitData() {
					Flags = NO_FLAGS;
					SPFlags = NO_FLAGS;
					Top = 0; Left = 0;
					MaxWidth  = 1024;
//               SpecEntry = SIMPL;
					MaxHeight = Screen->Height - 30;
					OuterDSet = NULL;
					AfterCreate = NULL;
				};
				SelParamData() {
					 InitData();
				};
				SelParamData(TForm* Frm) {
				  InitData();
				  if (Frm)  {
					  Left = Frm->Left;
					  Top = Frm->Top;
					  MaxHeight = Frm->Height;
					  MaxWidth  = Frm->Width;
				  }
				}
};
//---------------------------------------------------------------------------
class TFormSelSimpleEh : public TForm
{
__published:	// IDE-managed Components
        TDBGridEh *DBGridEh1;
        TMemo *Memo1;
        TSplitter *Splitter1;
        TDataSource *DataSource1;
        TDBEditEh *DBEditEh1;
        TDBDateTimeEditEh *DBDateTimeEditEh1;
        TDBNumberEditEh *DBNumberEditEh1;
        TQuery *Query1;
        TMemTableEh *MemTableEh1;
        TDataSetDriverEh *DataSetDriverEh1;
	TsPanel *sPanel1;
	TsStatusBar *sStatusBar1;
	TsEdit *EditSearch;
	TsLabel *sLabel2;
	TsCheckBox *sCheckBox1;
	TsSpeedButton *SBtn1;
	TQuery *Query2;
	TComboBox *ComboBox1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DBGridEh1DblClick(TObject *Sender);
        void __fastcall DBGridEh1DrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumnEh *Column,
          TGridDrawStateEh State);
        void __fastcall DBGridEh1GetCellParams(TObject *Sender,
          TColumnEh *Column, TFont *AFont, TColor &Background,
          TGridDrawStateEh State);
        void __fastcall DBGridEh1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall RxQuery1AfterScroll(TDataSet *DataSet);
        void __fastcall EditSearchChange(TObject *Sender);
        void __fastcall EditSearchClick(TObject *Sender);
        void __fastcall EditSearchEnter(TObject *Sender);
        void __fastcall EditSearchExit(TObject *Sender);
        void __fastcall EditSearchKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EditSearchKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall EditExit(TObject *Sender);
        void __fastcall EditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CheckBox1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Memo1Exit(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RxQuery1AfterClose(TDataSet *DataSet);
        void __fastcall RxQuery1FilterRecord(TDataSet *DataSet,
          bool &Accept);
        void __fastcall SBtnClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall MemTableEh1CalcFields(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
//        bool FilterByName;
        SelParamData* SPData;
		  TDataSet*     WrkQuery;
//        AnsiString ArtSelStr,ArtFilterStr;
        __fastcall TFormSelSimpleEh(TComponent* Owner,SelParamData* SPData);
	void __fastcall TFormSelSimpleEh::ProcReturn();
	void __fastcall TFormSelSimpleEh::ProcHistory(bool All);
	AnsiString __fastcall TFormSelSimpleEh::TranslateName(AnsiString FldName);

	bool __fastcall TFormSelSimpleEh::GetTransCompanyID(TForm* Frm, int Left,int &ID,TParams*&);
   bool __fastcall TFormSelSimpleEh::GetTransTypeID(TForm* Frm, int Left,int &ID,TParams*&);



};

struct RestValue {
	AnsiString FieldName;
	int Old_ID_Value;
	int New_ID_Value;
	AnsiString New_Str_Value;
	AnsiString Old_Str_Value;
	Variant    NewValue;
	RestValue() : Old_ID_Value(0), New_ID_Value(0) {}
};

class ShowModalForm {
	private: TFormSelSimpleEh* Frm;
	public:  ShowModalForm(TForm* Form, SelParamData* SPData) {
					Frm = new TFormSelSimpleEh(Form,SPData);
				}
				bool Execute() {
					return (Frm->ShowModal() == mrOk);
				}
				~ShowModalForm() {
					delete Frm;
				}
				TField* __fastcall FBN(AnsiString S) {
					return Frm->MemTableEh1->FieldByName(S);
            }
};
bool __fastcall ExecSelEhSimple(TForm* Form,SelParamData& SPData,const AnsiString& GetFldList,int* ResID = NULL,AnsiString* Name = NULL);

bool __fastcall SimpleSelEhTransCompanyID(TForm* Form,int Left, int& TransCompID,int TransTypeID,AnsiString *Res);
bool __fastcall SimpleSelEhTransTypeID   (TForm* Form,int Left, int& TransTypeID,AnsiString* Name);
bool __fastcall SimpleSelEhEmployeeID    (TForm* Form,int Left, int& EmployeeID);
bool __fastcall SimpleSelEhClientID      (TForm* Form,int Left, int& ClientID);
bool __fastcall SimpleSelEhContactID     (TForm* Form,int Left, int& Contact, int ClientID,AnsiString &Params,AnsiString* Name);
bool __fastcall SimpleSelEhTransportID   (TForm* Form,int Left, int& TransportID, int& TransTypeID, int& TransCompID, AnsiString &Params,AnsiString* Name);
//bool __fastcall SimpleSelEhTransportID   (TForm* Form,int Left, int& TransportID);

bool __fastcall SimpleSelEhTownID(TForm* Form,int Left,int &ID,AnsiString Params,AnsiString *Res);
bool __fastcall SimpleSelEhStreetID(TForm* Form,int Left,int &ID,int TownID,AnsiString Params,AnsiString *Res);
bool __fastcall SimpleSelEhDriverID(TForm* Form,int Left,int &ID,int TC_ID,AnsiString Params,AnsiString *Res);

bool __fastcall SimpleSelEhExpenseID(TForm* Form,int Left,int &ID,AnsiString Params);
bool __fastcall SimpleSelSpecViewID(TForm* Form, int Left, int &ID, AnsiString* ViewName,AnsiString* ResWdt, AnsiString Params);
bool __fastcall SimpleSelFilterID(TForm* Form, int Left, int &ID, AnsiString* FilterName,AnsiString Params);
bool __fastcall SimpleSelHistoryID(TForm* Form, int Left,AnsiString Title,AnsiString TableName,int ID,const AnsiString& FieldNames,const AnsiString &FieldTitles,RestValue& RestoreData);
bool __fastcall SimpleSelHistoryID(TForm* Form, int Left,AnsiString Title,AnsiString TableName,int ID, TStringList* FieldNames,TStringList* FieldTitles,RestValue& RestoreData);
bool __fastcall SimpleSelEhWorkTypeID(TForm* Form,int Left,int &ID,int ClientID,AnsiString Params,AnsiString *Res);

//---------------------------------------------------------------------------
extern PACKAGE TFormSelSimpleEh *FormSelSimpleEh;
//---------------------------------------------------------------------------
#endif
