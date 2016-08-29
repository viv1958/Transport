//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DModT.h"
#include "ComProc.h"
#include "StructDef.h"

#include "FrmFilter.h"
#include "FrmGetFieldFilter.h"
#include "FrmSelSimpleEh.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sPanel"
#pragma link "sStatusBar"
#pragma link "sSpeedButton"
#pragma link "sComboEdit"
#pragma link "sCustomComboEdit"
#pragma link "sMaskEdit"
#pragma resource "*.dfm"
bool SelFilter(FilterCols& OrderFilter,TDBGridEh* OrderGrid,int& SelFilterID,AnsiString& FilterName)
{

	TFormFilter* Frm = new TFormFilter(Application, OrderFilter, OrderGrid, SelFilterID, FilterName);
	if(Frm->SelCurrentFilter(false)) {
		OrderFilter = Frm->OrderFilter;
		SelFilterID = Frm->SelFilterID;
		if (SelFilterID) {
			FilterName  = Frm->sComboEdit1->Text;
		}
		else {
			FilterName  = "";
			if (!Frm->FilterIsEmpty()) {
				FilterName  = "Пользовательский";
			}
		}
		return true;
	}
	return false;
}
bool GetFilter(FilterCols& OrderFilter,TDBGridEh* OrderGrid,int& SelFilterID,AnsiString& FilterName)
{
	TFormFilter* Frm = new TFormFilter(Application, OrderFilter, OrderGrid, SelFilterID, FilterName);
	if (Frm->ShowModal() == mrOk) {
		OrderFilter = Frm->OrderFilter;
		SelFilterID = Frm->SelFilterID;
		if (SelFilterID) {
			FilterName  = Frm->sComboEdit1->Text;
		}
		else {
			FilterName  = "";
			if (!Frm->FilterIsEmpty()) {
				FilterName  = "Пользовательский";
			}
		}
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
__fastcall TFormFilter::TFormFilter(TComponent* Owner,FilterCols& OrderFilter,TDBGridEh* OrderGrid,int SelFilterID,AnsiString FilterName)
	: TForm(Owner)
{
	this->OrderFilter = OrderFilter;
	this->OrderGrid   = OrderGrid;
	this->SelFilterID = SelFilterID;
	if (SelFilterID) {
		this->sComboEdit1->Text = FilterName;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::FormCreate(TObject *Sender)
{
	 SetFormPosStd(this,1024,750,0,true);
	 FillFirstColumn();
	 FillCells();
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::AddEmptyElement()
{
	 FilterRows Empty;
	 OrderFilter.push_back(Empty);
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::FillFirstColumn()
{
	TDBGridColumnsEh* Columns = OrderGrid->Columns;
	if (!OrderFilter.size()) {
		AddEmptyElement();
	}
	int RowCount = Columns->Count;
	int ColCount = OrderFilter.size();
	StringGrid1->RowCount = RowCount+1;
	StringGrid1->ColCount = ColCount+1;
	for (int i = 0; i <= ColCount; i++) {
		StringGrid1->ColWidths[i] = 250;
		StringGrid1->Cells[i][0] = "Фильтр "+IntToStr(i);
	}
	StringGrid1->Cells[0][0] = "Наименования фильтруемых колонок";
	for (int i = 0; i < RowCount; i++) {
		AnsiString S  = Columns->Items[i]->Title->Caption;
		AnsiString S1 = GetPiece(S,"|",1);
		AnsiString S2 = GetPiece(S,"|",2);
		int N = StrToIntDef(S2,0);
		if (N) S2 = "";
		else   S2 = " -> " + S2;
		StringGrid1->Cells[0][i+1] = S1 + S2;
		FilteredFields.push_back(FieldInRow(i,Columns->Items[i]->FieldName,
										 Columns->Items[i]->Field->DataType,
										 Columns->Items[i]->DisplayFormat));
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::FillCells()
{
	int Col = 0;
	int Row;
	for (FilterCols::iterator iter1 = OrderFilter.begin(); iter1 != OrderFilter.end(); ++iter1) {
		Col++; Row = -1;
		for (FilterRows::iterator iter2 = (*iter1).begin(); iter2!=(*iter1).end(); ++iter2) {
			AnsiString FldName = iter2->first;
			std::vector<FieldInRow>::iterator iterFF;
			for (iterFF = FilteredFields.begin(); iterFF != FilteredFields.end(); ++iterFF) {
				if (iterFF->FldName == FldName) {
					Row = iterFF->Row;
					break;
				}
			}
			if (Row >=0) {
				StringGrid1->Cells[Col][Row+1] = GetFilterSetString(iter2->second,&*iterFF);
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::sSpeedButtonClick(TObject *Sender)
{
	StringGrid1->SetFocus();
	switch (GetComponentTag(Sender)) {
		case 1: DeleteCurColumn();
				  break;
		case 2: CreateNewColumn();
				  break;
		case 3: ClearCurColumn();
				  break;
		case 4: DeleteAllColumns();
				  break;
		case 5: SaveCurrentFilter();
				  break;
		case 6: ModalResult = mrOk;
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::DeleteCurColumn()
{
	int NCol = StringGrid1->ColCount - 1;
	ClearCurColumn();
	if (NCol == 1) {
		return;
	}
	int Col = StringGrid1->Col;
	if (Col == NCol) {
		StringGrid1->ColCount = NCol;
		OrderFilter.pop_back();
		return;
	}

	OrderFilter.erase(OrderFilter.begin() + Col-1);
	for (int i = Col; i < NCol; i++) {
		StringGrid1->Cols[i] = StringGrid1->Cols[i+1];
	}
	StringGrid1->ColCount = NCol;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::AddColIfNeed()
{
	int Col = StringGrid1->Col;
	int ColCnt = StringGrid1->ColCount - 1;
	int RowCnt = StringGrid1->RowCount;
	if (Col == ColCnt) {
		bool Add = false;
		for (int i = 1; i < RowCnt; i++) {
			if (StringGrid1->Cells[Col][1] != "") {
				Add = true;
				break;
			}
		}
		if (Add) {
			CreateNewColumn();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::ClearSGCol(int Col)
{
	int Cnt = StringGrid1->RowCount;
	for (int i = 1; i < Cnt; i++) {
		StringGrid1->Cells[Col][1] = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::CreateNewColumn()
{
	AddEmptyElement();
	int N = StringGrid1->ColCount;
	StringGrid1->ColCount = N+1;
	StringGrid1->Cells[N][0] = "Фильтр "+IntToStr(N);
	ClearSGCol(N);
	StringGrid1->ColWidths[N] = 250;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::ClearCurColumn()
{
	int Cnt = StringGrid1->RowCount;
	int Col = StringGrid1->Col;
	if (!Col ) return;
	if (OrderFilter[Col-1].size())
		ClearSelFilter();
	AnsiString S;
	for (int i = 1; i < Cnt; i++) {
		StringGrid1->Cells[Col][i] = S;
	}
	OrderFilter[Col-1].clear();
}
//---------------------------------------------------------------------------
bool __fastcall TFormFilter::FilterIsEmpty()
{
	for (FilterCols::iterator iterCol = OrderFilter.begin(); iterCol != OrderFilter.end(); ++iterCol) {
		FilterRows::iterator iterRow = iterCol->begin();
		for (FilterRows::iterator iterRow = iterCol->begin(); iterRow!=iterCol->end(); ++iterRow) {
			if (iterRow->second.size()) {
				return false;
			}
		}
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::DeleteAllColumns()
{
	StringGrid1->ColCount = 2;
	if (SelFilterID && !FilterIsEmpty()) {
		ClearSelFilter();
	}
	OrderFilter.clear();
	AddEmptyElement();
	StringGrid1->Col = 1;
	ClearCurColumn();
	ClearSelFilter();
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::SaveCurrentFilter()
{
	SelCurrentFilter(true);
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::StringGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key) {
		case VK_RETURN: EditCell();   	break;
		case VK_BACK:   ClearCell();  	break;
		case VK_RIGHT:  AddColIfNeed(); 	break;
		case VK_ESCAPE: ModalResult = mrCancel; break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::StringGrid1DblClick(TObject *Sender)
{
	EditCell();
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormFilter::GetFilterSetString(std::vector<FieldFilter>& FieldFilterSet,FieldInRow* FR)
{
	AnsiString Res,S;
	if (FieldFilterSet.size()) {
		for (std::vector<FieldFilter>::iterator iter = FieldFilterSet.begin(); iter != FieldFilterSet.end(); ++iter) {
			if (iter->NullCheck) {
				Res += " или 'ПУСТО'";
			}
			S = GetVariantString(iter->EqvValue,FR);
			if (S != "") {
				Res += " или = '" + S + "'";
			}
			S = GetVariantString(iter->MinValue,FR);
			if (S != "") {
				AnsiString S1 = GetVariantString(iter->MaxValue,FR);
				if (S1 != "") {
					Res += " или ( >= '"+ S + "' и <= '" + S1 +"')";
				}
				else Res += " или >= '" + S + "'";
			}
			else {
				S = GetVariantString(iter->MaxValue,FR);
				if (S != "") {
					Res += " или <= '" + S + "'";
				}
			}
		}
		if (Res != "") Res = Res.SubString(5,Res.Length());
	}
	return Res;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::EditCell()
{
	int Col = StringGrid1->Col;
	int Row = StringGrid1->Row;
	AnsiString DD = StringGrid1->Cells[Col][Row];
	FieldInRow* FR = &FilteredFields[Row-1];
	AnsiString FldName = FR->FldName;
	AnsiString RowName = StringGrid1->Cells[0][Row];
	FilterRows::iterator iter = OrderFilter[Col-1].find(FldName);
	vector<FieldFilter> FieldFilterSet;
	bool Insert = (iter == OrderFilter[Col-1].end());
	if (!Insert)
		FieldFilterSet = iter->second;
	if (GetFieldFilter(FieldFilterSet,FR,RowName)) {
		if (FieldFilterSet.size()) {
			if (Insert) {
				OrderFilter[Col-1].insert(pair<AnsiString,vector<FieldFilter> >(FldName,FieldFilterSet));
			}
			else {
				iter->second = FieldFilterSet;
			}
		}
		else {
			if (!Insert)
				OrderFilter[Col-1].erase(iter);
		}
		AnsiString SOld = StringGrid1->Cells[Col][Row];
		AnsiString SNew = GetFilterSetString(FieldFilterSet,FR);
		if (SOld != SNew) {
			StringGrid1->Cells[Col][Row] = SNew;
			ClearSelFilter();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::ClearCell()
{
	int Row = StringGrid1->Row;
	int Col = StringGrid1->Col;
	AnsiString FldName = FilteredFields[Row-1].FldName;
	FilterRows::iterator iter = OrderFilter[Col-1].find(FldName);
	if (iter != OrderFilter[Col-1].end()) {
		iter->second.clear();
		if (StringGrid1->Cells[Col][Row] != "") {
			StringGrid1->Cells[Col][Row] = "";
			ClearSelFilter();
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::sComboEdit1ButtonClick(TObject *Sender)
{
	 switch(GetComponentTag(Sender)) {
		 case 1:	SelCurrentFilter(false);	break;
	 }
}
//---------------------------------------------------------------------------
bool __fastcall TFormFilter::SelCurrentFilter(bool SaveCurState)
{
	 bool bRes = false;
	 AnsiString S,Params,ResWdt;
	 Params = IntToStr(DModT->CurEmpID) + ",'" + DModT->ComputerName + "'";
	 if (SimpleSelFilterID(this, Left + sComboEdit1->Left + sComboEdit1->Width + 5, SelFilterID, &S,Params)) {
		 int SavID = SelFilterID;
		 ProcResultFilterSel(SaveCurState);
		 SelFilterID      = SavID;
		 sComboEdit1->Text = S;
		 sSpeedButton5->Enabled = false;

		 bRes = true;
	 }
	 return bRes;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::ProcResultFilterSel(bool SaveCurState)
{
	if (SaveCurState) {
		SaveFilterCont();
	}
	else {
		RestoreFilterCont();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::SaveFilterCont()
{
	if (!SelFilterID) return;
	AnsiString SQL = "update Filter_cont set status = -1, dateChange = 'now' where Filters_id = "+ IntToStr(SelFilterID);
	if (!ExecuteQry(SQL,DModT->Database1,true)) return;

	AnsiString BegStr;
	int Col = 0;
	for (FilterCols::iterator iterCol = OrderFilter.begin(); iterCol != OrderFilter.end(); ++iterCol) {
		Col++;
//		int Row = 0;
		FilterRows::iterator iterRow = iterCol->begin();
		for (FilterRows::iterator iterRow = iterCol->begin(); iterRow!=iterCol->end(); ++iterRow) {
			AnsiString FldName = iterRow->first;
			BegStr = "select * from Edit_Filter_Cont(" + IntToStr(SelFilterID) + "," + IntToStr(Col) + ",'" + FldName + "',";
			for (vector<FieldFilter>::iterator iterCond = iterRow->second.begin(); iterCond != iterRow->second.end(); ++iterCond) {
				int NullCheck      = iterCond->NullCheck;
				Variant MinValue   = iterCond->MinValue;
				Variant MaxValue   = iterCond->MaxValue;
				Variant EqvValue   = iterCond->EqvValue;
				TFieldType FldType = iterCond->FldType;
				AnsiString Format  = iterCond->Format;
				SQL  = BegStr + IntToStr(FldType) + ",'" + Format  + "',"  + IntToStr(NullCheck) + ",'";
				SQL += GetVariantString(EqvValue, FldType, Format) + "','" + GetVariantString(MinValue, FldType, Format) + "','" +
						 GetVariantString(MaxValue, FldType, Format) + "'," + IntToStr(DModT->CurEmpID) + ",'" +
						 DModT->ComputerName +"')";
				Variant Result;
				if (!OpenTmpQuery(SQL,"RESULT",Result,DModT->Database1)) {
					OutputMessage("Ошибка записи фильтра");
					return;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::RestoreFilterCont()
{
	if (!SelFilterID) return;
	AnsiString SQL = "select * from filter_cont where Filters_ID = "+ IntToStr(SelFilterID) + " and " + GetStatusStr("Status") +
						  "order by Filter_Cont_Id";
	Query1->SQL->Text = SQL;
	DeleteAllColumns();
	OrderFilter.clear();
	int Prv_Col = 0;
	if (ReOpenDSetStd(Query1)) {
		while (!Query1->Eof) {
			int Filter_Col = Query1->FieldByName("FILTER_COL")->AsInteger;
			if (Filter_Col != Prv_Col) {
			  AddEmptyElement();
			  Prv_Col = Filter_Col;
			}
			AnsiString Field_Name = Query1->FieldByName("FIELD_NAME")->AsString;
			FilterRows::iterator iter = OrderFilter[Filter_Col-1].find(Field_Name);

			bool Insert = (iter == OrderFilter[Filter_Col-1].end());
			if (Insert) {
				vector<FieldFilter> FieldFilterSet;
				std::pair<FilterRows::iterator,bool> ret;
				ret =	OrderFilter[Filter_Col-1].insert(pair<AnsiString,vector<FieldFilter> >(Field_Name,FieldFilterSet));
				if (ret.second != true) {
					OutputMessage("Ошибка восстановления фильтра");
					return;
				}
				iter = ret.first;
			}
			FieldFilter FF;
			FF.NullCheck = Query1->FieldByName("NULL_CHECK")->AsInteger;
			FF.FldType   = (TFieldType)Query1->FieldByName("FIELD_TYPE")->AsInteger;
			FF.Format    = Query1->FieldByName("FORMAT_STR")->AsString;
			bool DateFmt    = FF.Format.Pos("dd.");
         TDateTime Today = Date();
			AnsiString MinVal = Query1->FieldByName("MIN_VAL")->AsString;
			AnsiString MaxVal = Query1->FieldByName("MAX_VAL")->AsString;
			AnsiString EqvVal = Query1->FieldByName("EQV_VAL")->AsString;
			switch (FF.FldType) {
				case ftInteger:   if (MinVal != "") FF.MinValue = StrToInt(MinVal);
										if (MaxVal != "") FF.MaxValue = StrToInt(MaxVal);
										if (EqvVal != "") FF.EqvValue = StrToInt(EqvVal);
										break;
				case ftString:    if (MinVal != "") FF.MinValue = MinVal;
										if (MaxVal != "") FF.MaxValue = MaxVal;
										if (EqvVal != "") FF.EqvValue = EqvVal;
										break;
				case ftDateTime:  if (MinVal != "") {
											if (DateFmt) FF.MinValue = TDateTime(Today + StrToInt(MinVal));
											else         FF.MinValue = TDateTime(MinVal);
										}
										if (MaxVal != "") {
											if (DateFmt) FF.MaxValue = TDateTime(Today + StrToInt(MaxVal));
											else         FF.MaxValue = TDateTime(MaxVal);
										}
										if (EqvVal != "") {
											if (DateFmt) FF.EqvValue = TDateTime(Today + StrToInt(EqvVal));
											else         FF.EqvValue = TDateTime(EqvVal);
										}
										break;
			}
			iter->second.push_back(FF);
			Query1->Next();
		}
		FillCells();
	}

}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::ClearSelFilter()
{
	if (SelFilterID) {
		SelFilterID = 0; sComboEdit1->Text = "Не выбран";
		sSpeedButton5->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormFilter::sComboEdit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch(Key) {
		case VK_BACK:   ClearSelFilter(); 			break;
		case VK_ESCAPE: ModalResult = mrCancel;   break;
	}
}
//---------------------------------------------------------------------------

