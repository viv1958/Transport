//---------------------------------------------------------------------------
#ifndef ComProcH
#define ComProcH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//#include <DBGrids.hpp>
//#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>

#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "MemTableEh.hpp"

#include "sCheckBox.hpp"
#include "sEdit.hpp"
#include "sLabel.hpp"
#include "sSpeedButton.hpp"
#include "sStatusBar.hpp"


#include <vector>
#include <list>
#include <map>
#include <bitset>
#include <string>
#include <algorithm>
//#define UnicodeString AnsiString
//---------------------------------------------------------------------------
#ifdef UnicodeString
class ExcelOut {
   public:               static Variant ExApp;
			 static Variant ExSheet;
			 static void __fastcall ExcelInit(AnsiString File,bool Visible = true);
			 static void __fastcall toExCellCell(int Row,int Col,AnsiString Text);
   public:
			 static void __fastcall WriteDataToExcel(void* GC,TDataSet* SrcDSet);
			 static void __fastcall WriteDataToExcelEh(void* GC,TDataSet* SrcDSet);
			 static void __fastcall WriteDataToExcel(void* GC,TDataSet* SrcDSet,int NDim,int *Arr,AnsiString FName,bool ShowTitle,AnsiString FileName);
                         static void __fastcall ExcelPrint(AnsiString File);
};
#endif
//==== Печать числа а текстовом виде ========================================
  AnsiString  __fastcall GetMoneyText(double X,int Mode);
  AnsiString  __fastcall GetMoneyText(int X,int Mode);
  AnsiString  __fastcall GetMoneyText(AnsiString S,int Mode);
  AnsiString  __fastcall GetNumberText(AnsiString S);
// ===== Простейшие примитивы ==========================================
        void __fastcall SetFormPosStd(TForm* Frm,int Width,int Height,int Left =0,bool SetMaxH = true);
        void __fastcall SaveRect(const TRect &Rect);
        void __fastcall SetGlobalErrMsg(const AnsiString& S);
  AnsiString __fastcall GetGlobalErrMsg(bool Clear = true);
        void __fastcall OutGlobalErrMsg(bool Clear = true);

        bool __fastcall IsInteger(const AnsiString& S);
        bool __fastcall GetInteger(int& X,const AnsiString& S);
	bool __fastcall InputInteger(const UnicodeString& Caption,const UnicodeString& Prompt,int& X);
	bool __fastcall IsDateTime(const AnsiString& S);
        bool __fastcall GetDateTime(TDateTime& DT,const AnsiString& S);
         int __fastcall GetMinutes(TDateTime DT);
      double __fastcall RoundDbl(double X);

        int  __fastcall GetComponentTag(TObject* Sender);
        void __fastcall OutputMessage(const AnsiString& Msg,bool SavMsg = true);
  AnsiString __fastcall GetRangeStr(int WrkSrvID,const AnsiString& Fld);
  AnsiString __fastcall GetStatusStr(const AnsiString& Fld);
        bool __fastcall RowIsDeleted(TDataSet *DataSet);

AnsiString  __fastcall GetDateStr(TDateTime DT,bool Add = false);
AnsiString  __fastcall GetDateStr(TDataSet* DSet,AnsiString const& FName);
        int __fastcall GetComboIndex(int Value);
// ===== Работа со строками ===========================================
  AnsiString __fastcall GetPiece(AnsiString Src,const AnsiString& Dlm,int N);
  AnsiString __fastcall SetPiece(AnsiString Src,const AnsiString& Piece,const AnsiString& Dlm,int N);
  AnsiString __fastcall GetSegment(AnsiString Src,const AnsiString& Dlm, int NBeg, int NEnd);
  AnsiString __fastcall MakeFIO(AnsiString S);
  AnsiString __fastcall GetLatinText(const AnsiString& Text);
        bool __fastcall CheckName(const AnsiString& Name,const AnsiString& NameFilter);
		  bool __fastcall CheckNameOne(const AnsiString& Name,const AnsiString& NameFilter);
		  void __fastcall RemoveReturn(AnsiString& S);
        bool __fastcall FindDoubleReturn(TMemo* Memo);
// ===== Работа с базой данных ========================================
        bool __fastcall OpenDB(TDatabase* DB,bool Out = true);
        bool __fastcall StartTransaction(TDatabase* DB);
        bool __fastcall StartTransactionEx(TDatabase* DB);

  AnsiString __fastcall GetSProcParamValues(TStoredProc* SProc);
  AnsiString __fastcall GetDSetText(TQuery* DSet);
        bool __fastcall ExecuteProcStd(TStoredProc* SProc,TDatabase* DB);
        bool __fastcall OpenDSetStd(TDataSet* DSet);
        bool __fastcall ReOpenDSetStd(TDataSet* DSet);
        bool __fastcall ExecuteQry(const AnsiString& SQL, TDatabase* DB,bool Out = true);
        bool __fastcall ExecuteQry(TQuery* Qry,bool Out = true);
        bool __fastcall OpenTmpQuery(const AnsiString& SQL,TParams*& Result,TDatabase* DB);
        void __fastcall GetTmpQueryParamsResult(TDataSet* Qry,TParams*& Result);
        bool __fastcall OpenTmpQuery(const AnsiString& SQL,const AnsiString& FName,Variant& Result,TDatabase* DB);
        bool __fastcall OpenTmpQuery(const AnsiString& SQL,const AnsiString& FNames,std::map<AnsiString,Variant>& Result,TDatabase* DB);
        bool __fastcall GetTmpQueryMapResult(TDataSet* Qry,const AnsiString& FNames,std::map<AnsiString,Variant>& Result);

        bool __fastcall Trunc(TDataSet* DSet, TCustomEdit* Edit,const AnsiString& FieldName);   // надо переставить ?!?!
        bool __fastcall Trunc(TDataSet* DSet, const AnsiString& FieldName, AnsiString& S);
        void __fastcall Trunc(AnsiString& S,int Size);

        void __fastcall ClearSProcParam(TStoredProc* SProc);
        void __fastcall ClearQueryParam(TQuery* SProc);
        void __fastcall PrepSProcByQry(TStoredProc* SProc, TDataSet* Qry, bool Clear = true);
        void __fastcall PrepQueryByQry(TQuery*      TagQry,TDataSet* Qry, bool Clear = true);

        void __fastcall SetProcParamQry(TStoredProc* SP,TDataSet* DS, const AnsiString& Fld,int Type,bool ClearEmplty);
        void __fastcall SetProcParamVal(TStoredProc* SP,Variant Value,const AnsiString& Fld,int Type,bool ClearEmpty);
        void __fastcall SetDSetParamVal(TQuery* SP,Variant Value,const AnsiString& Fld,int Type,bool ClearEmpty);
        void __fastcall SetDSetParamQry(TQuery* SP,TDataSet* DS,const AnsiString& Fld,int Type,bool ClearEmpty);
// ===== Работа с таблицами ========================================
        void __fastcall NumerateGridFields(TDBGridEh* Grid,bool Out = false);
        void __fastcall SwitchGridOption(TDBGridEh* Grid,bool New,Dbgrideh::TDBGridOption Opt);
        void __fastcall SwitchGridOptionEh(TDBGridEh* Grid,bool New,Dbgrideh::TDBGridEhOption Opt);

        void __fastcall PutEditOnGrid(TWinControl* Grid,TWinControl* Edit,bool SetWidth = true);
        void __fastcall ProcWinCtrl(TDBGridEh* Grid,TWinControl* WinCtrl,TWinControl* Parent,
                                AnsiString FldName,int EditCol,int Action = 2,int AddWidth =0,int DPlaces =0);
        void __fastcall ShowPanel(TDBGridEh* Grid,TPanel* Panel,TWinControl** WinLst,int NumCol);
//==== GData ================================================================
using namespace std;
enum ParamFlag  {
                NO_FLAGS               = 0x0000,
                MULTIPLE_SEL           = 0x0001,     // в форме допускается множественный выбор пробелом
                STD_STATUSBAR          = 0x0002,     // в форме используется стандарный StatusBar c 4-мя полями
																	  // 1 - значения ключевого(ых) поля(ей)
					 MOVE_DOWN_AFTER_SEL    = 0x0004,     // после выбора строки смещаться на строку вниз

					 CAN_SEE_DELETED        = 0x0008,     // допускается просмотр удаленных записей
					 SHOW_COMMENT           = 0x0010,     // автоматический показ комментария в Memo1
					 FILTER_NOT_ALLOWED     = 0x0020,     // фильтрация записей не допускается
					 SAVE_SELECTION         = 0x0080,     // сохранять выделенные строки после обработки хранимой процедурой

					 SHOW_SELECTED          = 0x0100,     // показать только выделенные строки
					 HIGHLIGHT_EDIT_ROW     = 0x0200,     // подсвечивать текущую редактируемую строки другим цветом
					 EXEC_SP_ALWAYS         = 0x0400,     // всегда выполнять хранимую процедуру
					 FILTER_BY_NAME         = 0x0800,     // Фильтр по строке в EditSearch

					 INS_IF_NOT_FOUND       = 0x1000,     // Запустить процедуру встваки, если не найден в EditSearch
					 DONT_CHECK_KEY_ID      = 0x2000,     // не проверять ID в ключе на соответствие N сервера
					 INC_SEARCH             = 0x4000,     // инкрементный поиск по таблице
					 SHOW_RDP_ON_RETURN     = 0x8000,     // Первое нажатие Return раскрывает DetailPanel если есть таковая

					 USE_SAVEPOSSTD         = 0x10000,    // Использовать процедуру SavePosStd после выполнения StoredProc вместо стандартного исп-я Result
					 SEL_LINES_FROM_CUR     = 0x20000,    // при выборе всех строк запрашивать выбор начиная с текущей строки
					 ASK_EACH_LINE_CONFIRM  = 0x40000,    // множественные операции с опросом
					 SKIP_NOT_ALLOWED       = 0x80000,    // пропускать не разрешеные к обработке строки при множественном выборе (иначе остановка)

					 DONT_SET_EDIT_WIDTH    = 0x100000,   // не изменять ширину Control при наложении на Grid  (сбрасывается каждый раз)
					 USE_SEPARATE_TRANS     = 0x200000,   // Каждая запись выполняется в отдельной транзакции
					 UPDATE_IN_MEMORY       = 0x400000,   // обновление записей в памяти
					 PULSE_AFTER_UPDATE     = 0x800000,   // после обновления записи сделать PulseFilter

					 UPDATE_ONLY_CURRENT    = 0x1000000,
					 OK_ON_DELETED          = 0x2000000
};
enum InternalFlag {                           // ==== записывается в State =========
  EDIT_IN_PROGRESS              = 0x0001,     // на Grid наложен TCustomEdit для редактирования поля
  LOCATE_IN_PROGRESS            = 0x0002,     // поиск на Focused Grid по имени
  SCROLL_IN_PROGRESS            = 0x0004,
  SCROLL_KEY_PRESSED            = 0x0008,     // был нажат Key, перемещающий позицию по строкам в Grid
  SET_ROW_DETAIL_PANEL_VISIBLE  = 0x0010,     // открвыть Detail Panel после выполнения scroll
  DELETED_ARE_SELECTED          = 0x0020      // в выборке участвуют только удаленные строки
};    // всегда выполнять хранимую процедуру для строки

class GridData;
typedef bool       __fastcall (__closure *FunGetID)(TForm*,int ,int& ,TParams*&);  // вызывается для получения ID поля
typedef bool       __fastcall (*FunGetSrvID)(int&);
typedef bool       __fastcall (__closure *FunFrmDataSet)   (TDataSet*);
typedef bool       __fastcall (__closure *FunFrmGDataDSet) (GridData& GData,TDataSet*);
typedef bool       __fastcall (__closure *FunFrmCanEdit)   (GridData& GData,bool CheckFld);
typedef void       __fastcall (__closure *FunFrmAddCurRow) (GridData& GData,int Add,bool Show, bool Clear = false);
typedef int        __fastcall (__closure *FunFrmCanDoIt)   (GridData& GData,bool Allowed);
typedef bool       __fastcall (__closure *FunFrmGetSProc)  (GridData& GData);
typedef AnsiString __fastcall (__closure *FunGetErrMsg)    (GridData& GData,int Error);
typedef bool       __fastcall (__closure *FunFrmAfterExec) (GridData& GData,bool& Result);

//typedef bool _fastcall (*FunGetID)(TForm*,int ,int& ,TParams*&);  // вызывается для получения ID поля
//typedef bool _fastcall (*FunGetSrvID)(int&);
/*
typedef void _fastcall (*FunSetSQL) (TForm*,TDataSet*);
typedef void _fastcall (*FunCalcField) (TDataSet*);
typedef bool _fastcall (*FunCanEdit)(GridData& GData,bool CheckFld);
typedef int  _fastcall (*FunCanDoIt)(GridData& GData,bool Allowed);
typedef bool _fastcall (*FunGetSProc)(GridData& GData);
typedef AnsiString _fastcall (*FunGetErrMsg)(GridData& GData,int Error);
typedef bool _fastcall (*FunAfterExec)(GridData& GData,bool& Result);
*/



class GridKeyValue {
   private : Variant Key;
   public  : GridKeyValue() {}
	     GridKeyValue(Variant const& S) : Key(S) {}
	     bool IsNull()   const { return Key.IsNull();  }
	     bool IsEmpty()  const { return Key.IsEmpty(); }
	     bool IsArray()  const { return Key.IsArray(); }
             void Clear()          { Key.Clear();          }
             Variant Value() const { return Key; }
	     GridKeyValue& operator=(Variant const& S) {
	     	Key = S;
	        return *this;
	     }
	     GridKeyValue& operator=(GridKeyValue const& S) {
	        Key = S.Key;
		return *this;
	     }
	     operator Variant() { return Key; }
	     bool operator!=(GridKeyValue const &Src) {
                return !operator==(Src);
             }
	     bool operator==(GridKeyValue const &Src) {
		bool B1 = Src.IsNull() || Src.IsEmpty();
		bool B2 = Key.IsNull() || Key.IsEmpty();
		if (B1 || B2) {
		  return (B1 = B2);
		}
		B1 = Key.IsArray();
		B2 = Src.IsArray();
		bool bRes = false;
		if (B1 == B2) {
		   if (B1) {
		      int b1 = Key.ArrayHighBound();
		      int b2 = Src.Key.ArrayHighBound();
		      if (b1 == b2) {
		    	 bRes = true;
		    	 for (int i=0; i<=b1; i++) {
		            Variant V1 = Key.GetElement(i);
			    Variant V2 = Src.Key.GetElement(i);
			    if (V1 != V2) {
			       bRes = false;
			       break;
			    }
		         }
	              }
                   }
		   else {
		     bRes = (Key == Src.Key);
		   }
                }
		return bRes;
	     }
};
template <int N>
void __fastcall SetBitMask(bitset<N>& Mask,unsigned int MaskVal,int nPos = 0)
{
//	int Shift = nPos*sizeof(Mask);
	while (MaskVal) {
		Mask[nPos++] = MaskVal & 0x0001;
		MaskVal >>= 1;
	}
};
template <int N>
void __fastcall SetBitMask(bitset<N>& Mask,const AnsiString MaskVal,  int nPos = 0)
{
//	int Shift  = nPos*sizeof(Mask);
	int Length = MaskVal.Length();
	for (int i=0; i< Length; ) {
		AnsiString C = MaskVal.SubString(++i,1);
		if (C != ' ')
			Mask[nPos++] = (MaskVal[i] == '1');
	}
}
// ==== Status Bar and SelArray ================================================
  AnsiString __fastcall PrintSelArray(GridData& GData);
	     void __fastcall SetStatusBarStd(GridData& GData);
        void __fastcall ClearArrStd(GridData& GData);
        void __fastcall HighlightEditRow(GridData& GData,bool Highlight);
// ==== Save & resore position in DSet =========================================
        bool __fastcall OpenDSetStd(GridData& GData);
        bool __fastcall ReOpenDSetStd(GridData& GData);
        void __fastcall FindUndelStrStd(GridData& GData);
        bool __fastcall GetKeyValueStd(GridData& GData,GridKeyValue& KeyValue,bool ForChild = true);
        bool __fastcall SavePosStd(GridData& GData);
        void __fastcall ProcRefreshStd(GridData& GData,bool ResetSQL);
        void __fastcall RefreshRowStd(GridData& GData,TDataSet* DSet);
        void __fastcall RefreshRowStd(GridData& GData,AnsiString SQL);
        void __fastcall InsertRowStd(GridData& GData,TDataSet* DSet);
        void __fastcall InsertRowStd(GridData& GData,AnsiString SQL);

        bool __fastcall RestorePosStd(GridData& GData,bool RestoreChild);
        bool __fastcall KeyFieldIsNullStd(GridData& GData);

        void __fastcall PulseFilterStd(GridData& GData);
        bool __fastcall ExecSProcStd(GridData& GData);
// ==== EditSearch handlers ====================================================
        void __fastcall SetEditSearchTxtStd(GridData& GData);
        void __fastcall EditSearchChangeStd(GridData& GData);
TModalResult __fastcall EditSearchKeyDownStd(GridData& GData,WORD &Key, TShiftState Shift);
        void __fastcall EditSearchKeyUpStd(GridData& GData,WORD &Key, TShiftState Shift);
// ==== Misc routines ==========================================================
		  bool __fastcall OpenExecQueryStd(GridData& GData);
  AnsiString __fastcall GetFieldOutTitleStd(GridData& GData);
  AnsiString __fastcall GetFieldOutTitleStd(GridData& GData,AnsiString FieldOut);
        bool __fastcall EditIsAllowedStd  (GridData& GData,bool CheckSpace   = true,bool CheckField = true);
        bool __fastcall EditIsAllowedStdEx(GridData& GData);
        bool __fastcall ProcKeyIsAllowed(GridData& GData);
        void __fastcall GetGridColParam(GridData& GData,bool Translate);
        bool __fastcall AskQuestionStd(GridData& GData,const AnsiString& S);
        int  __fastcall AskQuestionStd(GridData& GData,const AnsiString& S,TMsgDlgButtons Btn);
        bool  __fastcall AskQuestionStd(const AnsiString& S);
        int  __fastcall AskQuestionStd(const AnsiString& S,TMsgDlgButtons Btn);
        bool TranslateName(GridData& GData,AnsiString& EditFldName);
        bool __fastcall KeysAreEqual(GridData& GData,Variant& V1,Variant V2);
        void __fastcall RepaintNewKeyLine(GridData& GData);
  AnsiString __fastcall GetCurrentFieldName(GridData& GData);
        void _fastcall RefreshRecordStd(GridData& GData,bool bRes);

// ==== Form KeyDown handlers ==================================================
        void __fastcall FormKeyDownStd(GridData& GData,WORD &Key,TShiftState Shift);
        void __fastcall ProcSeeSQLStd(GridData& GData, bool GetSQL); // VK_F1
        void __fastcall ProcFilterStd(GridData& GData,bool FilterCurColumn,AnsiString Title = ""); // VK_F3
        void __fastcall ProcSeeDelStd(GridData& GData); // VK_F8
        void __fastcall ProcOutputStd(GridData& GData); // VK_F12
        void __fastcall ProcOutputStd(TDBGridEh* Grid);
		  void __fastcall ProcSelAllStd(GridData& GData,WORD* Key, bool Ask = true); // VK_ADD
		  void __fastcall ProcUnsAllStd(GridData& GData,WORD* Key);
// ==== Filter record & draw colored cells handlers ============================
        bool __fastcall RowIsSelectedStd(GridData& GData,bool SelectIfNot = false);
        bool __fastcall GetFilterStr(AnsiString& Filter,AnsiString Title);
// ==== GridEh event handlers ==================================================
        void __fastcall GetCellParamsStd(GridData& GData,TFont *AFont, TColor &Background, TGridDrawStateEh State);
        void __fastcall GetCellParamsStd(TDBGridEh* Grid,TFont *AFont, TColor &Background, TGridDrawStateEh State);
	void __fastcall DrawColumnCellStd(const TRect& Rect,TGridDrawStateEh State);
        void __fastcall DrawColumnCellStd(GridData& GData,const TRect &Rect,int DataCol,TColumnEh *Column,
                        TGridDrawStateEh State);
        bool __fastcall ExternalCtrlEnterStd(GridData& GData);
// ==== Query event handlers ===================================================
        bool __fastcall FilterRecordStd(GridData& GData);
        void __fastcall AfterCloseStd(GridData& GData);
        void __fastcall AfterScrollStd(GridData& GData);
        void __fastcall BeforeScrollStd(GridData& GData);
        void __fastcall CalcFieldsStd(GridData& GData);
// ===== Write routine =========================================================
        bool __fastcall Commit(TDatabase* DB);
        bool __fastcall Rollback(TDatabase* DB);
        bool __fastcall PrepSProcStd(GridData& GData,bool Delete);
        bool __fastcall PrepQueryStd(GridData& GData,bool Delete);
        bool __fastcall ReorderDataStd(GridData& GData, bool Delete);
		  bool __fastcall WriteDataStd(GridData& GData,bool Delete);
//        bool __fastcall WriteDataSProcStd(GridData& GData,bool Delete);
		  bool __fastcall WriteDataQueryStd(GridData& GData,bool Delete);
		  bool __fastcall WriteDataObjStd(GridData& GData,bool Delete);
		  bool __fastcall OutErrMsgStd(GridData& GData,int Result);
		  AnsiString __fastcall GetErrMsgStd(GridData& GData,int Result);
// ==== Show and write comment in Memo =========================================
        void __fastcall ShowMemoStd(GridData& GData,TMemo* Memo,AnsiString* CommentFieldName = NULL);
        void __fastcall WriteMemoStd(GridData& GData,TMemo* Memo);
// ==== Handle grid keys =======================================================
        bool __fastcall LocateGDataStd(GridData& GData);
        void __fastcall ProcKeyDownStd(GridData& GData,WORD Key);
		  void __fastcall ProcKeyPressStd(GridData& GData,wchar_t &Key);
		  bool __fastcall ProcInsertStd(GridData& GData,UnicodeString Name = "");
		  int  __fastcall GetCurColumnEditAction(GridData& GData);
		  int  __fastcall ProcReturnStd(GridData& GData);

		  TWinControl* GetEditWinControl(GridData& GData,int Action);


		  bool __fastcall ProcWinCtlStd(GridData& GData,int Action);
        void __fastcall ProcSel_IDStd(GridData& GData,int Index);
        bool __fastcall ProcDeleteStd(GridData& GData);
        void __fastcall ProcRestoreStd(GridData& GData);
        bool __fastcall ProcBackSpStd(GridData& GData);
        void __fastcall ProcSelectStd(GridData& GData,bool Move = true);
// ==== Grid event handlers ====================================================
		  void __fastcall RowDetailPanelHideStd(GridData& GData);
		  void __fastcall RowDetailPanelShowStd(GridData& GData);
// ==== Edit on grid ===========================================================
        bool __fastcall EditKeyDownStd(GridData& GData,TObject *Sender, WORD &Key,TShiftState Shift);
        void __fastcall EditExitStd(TObject* Sender);
        void __fastcall EditExitStd(GridData& GData,TObject* Sender);

class MemTableSQL {
           TMemTableEh* MemTbl;
           AnsiString SQL;
   public: MemTableSQL(TMemTableEh* M) : MemTbl(M) {};
           operator TMemTableEh*()   { return MemTbl; }
           TMemTableEh* operator->() { return MemTbl; }
           void SetSQL(AnsiString S) { SQL = S;       }
           void SetSQL(TQuery* Qry)  { SQL = GetDSetText(Qry); }
           bool operator == (MemTableSQL& MTS) {
              return MTS.SQL == SQL;
           }
           bool operator != (MemTableSQL& MTS) {
              return MTS.SQL != SQL;
           }
};

class GridData {
   private: int          m_ActionTag;
            TDBGridEh*   m_WrkGrid;
            TQuery*      m_WrkQr;
            TStoredProc* m_SProc;
            bool SkipEditIsAllowed;
            GridData& operator=(const GridData& SrcGData);
            GridData(const GridData&);
   public:  GridKeyValue CurKeyValue;
				static FunGetSrvID    FGetSrvID;
				static GridData*      WrkGData;
				bool SelDeleted;
	int        Flags;
	int        State;
	int        PickCnt;             //  кол-во Items в выпадающем списке
	int        ItemIndex;
	int        GridCol;             //  номер редактируемой колонки в GridEh
	int        EditCol;             //  Tag редактируемой колонки в GridEh
	FunGetID   CurFun;              //  функция для выбора ID
	int        DPlaces;             //  число знаков после запятой для редактируемого поля
											  //     берется из DisplayFormat поля или колонки
	unsigned int MaxUpdateInMemory; // мксимально возможное кол-во RefreshRecord
	TColumnEh* Column;              //  редактируемая колонка
	AnsiString EditFldName;         //  имя редактируемого поля
	TField*    EditFld;             //  редактируемое поле
	TFieldType FieldType;           //  тип редактируемого поля
	AnsiString ColCaption;          //  заголовок столбца редактируемого поля
	int        Result;              //  результат выполнения SP (параметр "RESULT", если он есть)

	bitset<128> EditAllowMask;      //  Маска редактируемых полей (1 - редактируемое, 0 -нет)
	bitset<128> Select_IDMask;      //  Маска полей, где выбирается ID из другого справочника (1 - выбирается, 0- нет)
	bitset<128> NullAllowMask;      //  Маска полей, где допускается Null (1- допускается, 0- нет)
	bitset<128> FilterFldMask;      //  Маска полей, по которым допускается фильтр (1- допускается, 0- нет)

	FunFrmGDataDSet FunSetSQLOne;   //  Функция записи текста SQL в Query обновления строки (м.б. NULL)
	FunFrmDataSet   SetSQL;         //  Функция записи текста SQL в WrkDSet (вызывается в ProcRefreshStd) (м.б. NULL)
	FunFrmCanEdit   FunCanEdit;     //  Функция разрешения редактирования записи перед вводом значения (вызывается в EditIsAllowedStd) (м.б. NULL)
	FunFrmAddCurRow FunAddRow;	     //  Фунция, выполняющая действия по добавлению строки
	FunGetErrMsg    GetErrMsg;      //  Функция получения сообщения об ошибке
	FunFrmDataSet   FunAcceptRec;   //  Фильтр записи пользователя
	FunFrmDataSet   CalcFields;     //  Функция расчета полей
	FunFrmGetSProc  FunGetSProc;    //  Получить SProc и параметры в зависимости от редактируемого поля
	FunFrmCanEdit   FunFillSProc;   //  Заполнить параметры SProc
	FunFrmCanDoIt   FunCanDoIt;     //  Проверка возможности выполнения процедуры после ввода значения перед записью в базу
	FunFrmAfterExec FunAfterExec;   //  выполнияется после записи в базу

	GridKeyValue KeyValue;          //  Значения ключа

	AnsiString AskDel;              // Вопрос на удаление извне
	AnsiString ObjectName;          // удалить восстановить ... сотрудника,роль и т.п.
	AnsiString FieldOut;            //  Поле наименования (Для поиска в EditSearch и для ввода при Insert)
	AnsiString FieldKey;            //  Список ключевых полей, через ";"
	AnsiString FieldFlt;            //  Фильтруемое поле
	AnsiString DefFieldFlt;         //  Фильтруемое поле по умолчанию
	AnsiString FieldLoc;            //  Поле для инкрементального поиска
	AnsiString DefFilterCaption;    //  Заголовок фильтруемого поля по умолчанию (выводится в запросе на фильтр)
	AnsiString DefSortOrder;			  //  Список полей по умолчанию для сортировки
	bool       SeeDeleted;          //  Разрешает в фильтре видеть удаленные строки
	bool       UnselLast;           //  Сбросить последнюю выбранную строку
	bool       CurEditAllowed;      //  результат работы ProcKeyIsAllowed
	WORD         CurKeyPressed;
	AnsiString   SearchTxt;
	GridKeyValue SearchKey;
	AnsiString   Filter;              //  текстовый фильтр

	TDataSet*    SP_DSet;           // источник данных для StoredProc (иначе WrkDSet)
	TDataSet*    SrcDSet;           // источник данных для Для MemTable
	TDataSet*    WrkDSet;           // Рабочий набор
	__property TStoredProc* WrkSProc   = { read = m_SProc,     write = SetWrkSProc  };          // Pабочая SP (м.б. NULL)
	__property TQuery*      WrkQuery   = { read = m_WrkQr,     write = SetWrkQuery  };          // Query для записи в БД
   __property TDBGridEh*   WrkGrid    = { read = m_WrkGrid,   write = SetWrkGrid   };
   __property int          ActionTag  = { read = m_ActionTag, write = SetActionTag };

   TForm*       WrkForm;           // Форма, на которой находится WrkGrid (м.б. NULL)
   TDatabase*   WrkDBase;          // База, где выполняется WrkSProc (м.б. NULL)
                                   //   необязательно та из которой берется набор
   TsStatusBar*  WrkSBar;          // Рабочий sStatusBar (м.б. NULL)
   TEdit*       EditSearch;        // Edit для поиска (м.б. NULL)

   TDBEditEh*         TextEdit;    //  TCustomEdit
   TDBNumberEditEh*   NumbEdit;
	TDBDateTimeEditEh* DateEdit;
	TDateTimePicker*   TimeEdit;
   TComboBox*         ListEdit;

   TParams*     ExtParams;         // Дополнительные параметры, которые всегда записываются в SP (м.б. NULL)
   TParams*     SelParams;         // Параметры, которые используются при Insert
   TParams*     CurParams;         // Текущие параметры, которые записываются в SP
                                   // после выполнения SP сбрасываются

   std::vector<GridKeyValue>       SelArray;        // Массив выбранных строк
   std::vector<GridKeyValue>       DoneArray;       // Массив выполненных
   std::map<AnsiString,AnsiString> FldTranslateMap; // трансляция видимых в редакируемые поля (Ex.: "OutName","ID_Name")
   std::map<AnsiString,FunGetID>   FunGetIDMap;     // список функций для выбора Id из других таблиц ((Ex.: "ID_Name",GetExNameID)
   GridData*  ParentGData;                          // master GData (м.б. NULL)
   std::vector<GridData*> ChildGData;               // Child  GData (м.б. NULL)

   GridData() :
					Flags(NO_FLAGS),State(0),GridCol(0),EditCol (0),EditFld(NULL),CurFun(NULL),SkipEditIsAllowed(false),ActionTag(0),
/*					KeyValue(Null),*/
					SeeDeleted(false),UnselLast(false),SrcDSet(NULL),SP_DSet(NULL),
               WrkDSet(NULL),WrkSProc(NULL),WrkGrid(NULL),WrkQuery(NULL),
               WrkForm(NULL),WrkDBase(NULL),WrkSBar(NULL),EditSearch(NULL),
               ExtParams(NULL),SelParams(NULL),CurParams(NULL),ParentGData(NULL),
					TextEdit(NULL),NumbEdit(NULL),DateEdit(NULL),TimeEdit(NULL),ListEdit(NULL),
					SetSQL(NULL),FunCanEdit(NULL),FunAddRow(NULL),CalcFields(NULL),GetErrMsg(NULL),FunCanDoIt(NULL),FunGetSProc(NULL),FunAfterExec(NULL),
					FunAcceptRec(NULL),FunSetSQLOne(NULL), FunFillSProc(NULL),
               MaxUpdateInMemory(5)
    {
       ActionTag = 0;
       WrkDSet  = NULL;
       WrkSProc = NULL;
		 WrkQuery = NULL;
       WrkGrid  = NULL;
       return;
    }

   ~GridData() { delete ExtParams,SelParams,CurParams; SelArray.clear(); }
   bool InitSProc()   {
      bool bRes = true;
      if (FunGetSProc) bRes = FunGetSProc(*this);
      return bRes;
   }
   void SetActionTag(int Tag) {
      CurKeyPressed = 0;
      m_ActionTag     = Tag;
   }
   void SetWrkQuery(TQuery*   Qry) {
      m_SProc = NULL;
      m_WrkQr = Qry;
   }
   void SetWrkSProc(TStoredProc*   Proc) {
      m_SProc = Proc;
      m_WrkQr = NULL;
   }
   void SetWrkGrid(TDBGridEh*   WrkGrid) {
		m_WrkGrid = WrkGrid;
		if (m_WrkGrid) {
			NumerateGridFields(m_WrkGrid);
			WrkDSet   = WrkGrid->DataSource->DataSet;
			if (TMemTableEh* MT = dynamic_cast<TMemTableEh*>(WrkDSet)) {
            DefSortOrder = MT->SortOrder;
			}
			TComponent* Owner = WrkGrid->Owner;
			while (true) {
				if (!Owner) break;
				TForm* Frm = dynamic_cast<TForm*>(Owner);
				if (Frm) {
					WrkForm = Frm;
				  break;
				}
				else Owner = Owner->Owner;
			}
		}
	}
	/*
	GridData& operator=(const GridData& SrcGData) {
		if (&SrcGData != this) {
         Flags = SrcGData.Flags;
         State = SrcGData.State;
         SkipEditIsAllowed = false;
         ActionTag     = 0;

         EditAllowMask = SrcGData.EditAllowMask;
         Select_IDMask = SrcGData.Select_IDMask;
         NullAllowMask = SrcGData.NullAllowMask;
         FilterFldMask = SrcGData.FilterFldMask;

         FieldOut      = SrcGData.FieldOut;
         FieldKey      = SrcGData.FieldKey;
         FieldFlt      = SrcGData.FieldFlt;
         SeeDeleted    = SrcGData.SeeDeleted;
         UnselLast     = SrcGData.UnselLast;
         KeyValue      = SrcGData.KeyValue;

         Filter        = SrcGData.Filter;

         SP_DSet       = SrcGData.SP_DSet;
         SrcDSet       = SrcGData.SrcDSet;
         WrkDSet       = SrcGData.WrkDSet;
         WrkSProc      = SrcGData.WrkSProc;
         WrkQuery      = SrcGData.WrkQuery;
         WrkGrid       = SrcGData.WrkGrid;
         WrkForm       = SrcGData.WrkForm;
         WrkSBar       = SrcGData.WrkSBar;
         WrkDBase      = SrcGData.WrkDBase;

         EditSearch    = SrcGData.EditSearch;
         TextEdit      = SrcGData.TextEdit;
         NumbEdit      = SrcGData.NumbEdit;
         DateEdit      = SrcGData.DateEdit;
         ListEdit      = SrcGData.ListEdit;

         SelArray      = SrcGData.SelArray;

         FunSetSQL     = SrcGData.FunSetSQL;
         FunCanEdit    = SrcGData.FunCanEdit;
         FunGetErrMsg  = SrcGData.FunGetErrMsg;
         CalcFields    = SrcGData.CalcFields;
         FunGetSProc   = SrcGData.FunGetSProc;
         FunCanDoIt    = SrcGData.FunCanDoIt;
         FunAfterExec  = SrcGData.FunAfterExec;
         FunSetSQLOne  = SrcGData.FunSetSQLOne;
         FunAcceptRec  = SrcGData.FunAcceptRec;

         ParentGData   = SrcGData.ParentGData;
         ChildGData    = SrcGData.ChildGData;

         delete ExtParams; ExtParams = NULL;
         if (SrcGData.ExtParams) {
            ExtParams = new TParams();
            ExtParams->Assign(SrcGData.ExtParams);
         }
         delete SelParams; SelParams = NULL;
         if (SrcGData.SelParams) {
            SelParams = new TParams();
            SelParams->Assign(SrcGData.SelParams);
         }
         delete CurParams; CurParams = NULL;
         if (SrcGData.CurParams) {
            CurParams = new TParams();
            CurParams->Assign(SrcGData.CurParams);
         }
      }
      return *this;
   }
   */
   void ClearCurParams() {
      delete CurParams; CurParams = NULL;
   }
   void AddSelParam(TFieldType FType,AnsiString FName,Variant Value) {
      if (!SelParams) SelParams   = new TParams();
      SelParams->CreateParam(FType, FName, ptInput);
      SelParams->ParamValues[FName] = GetParamValue(FType,FName,Value);
   }
   void AddCurParam(TFieldType FType,AnsiString FName,Variant Value) {
      if (!CurParams) CurParams   = new TParams();
      if (!CurParams->FindParam(FName))
         CurParams->CreateParam(FType, FName, ptInput);
      CurParams->ParamValues[FName] = GetParamValue(FType,FName,Value);
   }
   void AddCurParam(TFieldType FType,AnsiString FName,TDataSet* DataSet) {
      if (!CurParams) CurParams   = new TParams();
      if (!CurParams->FindParam(FName))
         CurParams->CreateParam(FType, FName, ptInput);
      CurParams->ParamValues[FName] = DataSet->FieldByName(FName)->Value;

   }
   void AddExtParam(TFieldType FType,AnsiString FName,Variant Value) {
      if (!ExtParams) ExtParams   = new TParams();
      ExtParams->CreateParam(FType, FName, ptInput);
      ExtParams->ParamValues[FName] = GetParamValue(FType,FName,Value);
   }
   Variant GetParamValue(TFieldType FType,AnsiString& FName,Variant Value) {
//		Variant V = Null;
      Variant V;
		V.Clear();
      if (!Value.IsNull()) {
         switch (FType) {
	    case ftString:   {
                                AnsiString S = Value;
                                if (WrkDSet->FindField(FName))
                                   Trunc(WrkDSet,FName,S);
                                else Trunc(S,255);
                                if (S != "") V = S;
                             }
//                             if (Value != Variant(""))          V = Value;
	        	     break;
            case ftInteger:
            case ftWord:
            case ftSmallint:
            case ftFloat:    if (Value)                V = Value;
			     break;
            case ftDateTime: if (Value != Variant(TDateTime())) V = Value;
                             break;
         }
      }
      return V;
   }
   bool GetCurSrvID(int &CurSrvID);
   void ClearExtParams() {
      if (ExtParams) ExtParams->Clear();
   }
   void SkipCheckEditIsAllowed()
   {
      SkipEditIsAllowed = true;
   }
   int OperationIsAllowed()
   {
      int iRet = 0;
      bool Allow =  SkipEditIsAllowed || EditIsAllowedStdEx(*this);
      SkipEditIsAllowed = false;
      if (FunCanDoIt) {
         iRet = FunCanDoIt(*this,Allow);
      }
      else {
         if (Allow) iRet = 1;
         else {
            if (Flags & SKIP_NOT_ALLOWED) iRet = 0;
            else                          iRet = -1;
         }
      }
      return iRet;
   }
};
#endif











