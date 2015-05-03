//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DModT.h"
#include "ComProc.h"
#include "StructDef.h"

#include "FrmGetFieldFilter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sPanel"
#pragma link "sSpeedButton"
#pragma link "DBCtrlsEh"
#pragma link "sCheckBox"
#pragma resource "*.dfm"
bool GetFieldFilter(std::vector<FieldFilter>& FieldFilterSet,const FieldInRow* FldDsc, AnsiString FName)
{
	TFormGetFieldFilter* Frm = new TFormGetFieldFilter(Application, FieldFilterSet, FldDsc, FName);
	if (Frm->ShowModal() == mrOk) {
		FieldFilterSet = Frm->FieldFilterSet;
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
__fastcall TFormGetFieldFilter::TFormGetFieldFilter(TComponent* Owner,std::vector<FieldFilter> FieldFilterSet,const FieldInRow* FldDsc, AnsiString FName)
	: TForm(Owner)
{
	 this->FieldFilterSet = FieldFilterSet;
	 this->Caption        = this->Caption + " > " + FName + " <";
	 this->FldRowPtr      = FldDsc;
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::FormCreate(TObject *Sender)
{
	 CreateColumns();
	 CreateRows();
	 AnsiString S = FldRowPtr->Format;
	 DBDateTimeEditEh1->EditFormat = S;
	 HourMin = FldRowPtr->Format == "hh:nn";
	 if (HourMin)
		 DBDateTimeEditEh1->EditButton->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::AddEmptyElement()
{
	FieldFilter FF;
	FieldFilterSet.push_back(FF);
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::CreateRows()
{
	 int Size = FieldFilterSet.size();
	 if (!Size) {
		 AddEmptyElement();
		 Size++;
	 }
	 int RowCount = Size+1;
	 StringGrid1->RowCount = RowCount;
	 for (int i = 1; i < RowCount; i++) {
		 StringGrid1->Cells[0][i] = "Вариант "+IntToStr(i) ;
		 ShowRow(i);
	 }

}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::ShowRow(int i)
{
	FieldFilter FF = FieldFilterSet[i-1];
	if (FF.NullCheck == 1) {
		StringGrid1->Cells[1][i] = "Да";
	}
	StringGrid1->Cells[2][i] = GetVariantString(FF.MinValue,FldRowPtr);
	StringGrid1->Cells[3][i] = GetVariantString(FF.EqvValue,FldRowPtr);
	StringGrid1->Cells[4][i] = GetVariantString(FF.MaxValue,FldRowPtr);
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::CreateColumns()
{
	int Cnt = StringGrid1->ColCount;
	StringGrid1->ColWidths[0] = 80;
	for (int i=1; i < Cnt; i++) {
		StringGrid1->ColWidths[i] = 120;
	}
	StringGrid1->Cells[1][0] = "Пустое поле";
	switch (FldRowPtr->FldType) {
		case ftString:    StringGrid1->Cells[2][0] = "Начинается с";
								StringGrid1->Cells[3][0] = "Включает";
								StringGrid1->Cells[4][0] = "Оканчивается на";
								break;
		case ftInteger:	StringGrid1->Cells[2][0] = "Больше или равно";
								StringGrid1->Cells[3][0] = "Точно равно";
								StringGrid1->Cells[4][0] = "Меньше или равно";
								break;
		case ftDateTime:  StringGrid1->Cells[2][0] = "Начиная с (вкл.)";
								StringGrid1->Cells[3][0] = "Точно равно";
								StringGrid1->Cells[4][0] = "Вплоть до (вкл.)";
								break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::StringGrid1DrawCell(TObject *Sender, int ACol,
			 int ARow, TRect &Rect, TGridDrawState State)
{
	if (State.Contains(Grids::gdFocused))
		SaveRect(Rect);
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::StringGrid1KeyDown(TObject *Sender, WORD &Key,
			 TShiftState Shift)
{
	switch (Key) {
		 case VK_RETURN: EditCell();  	break;
		 case VK_BACK:   ClearCell(); 	break;
		 case VK_DOWN:   AddRowIfNeed(); break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::EditCell()
{
	EditCol = StringGrid1->Col;
	EditRow = StringGrid1->Row;
	FieldFilter CurFF = FieldFilterSet[EditRow-1];
	if (EditCol == 1) {
		int X = CurFF.NullCheck;
		FieldFilterSet[EditRow-1].NullCheck = 1-X;
		StringGrid1->Cells[EditCol][EditRow]    = X ? AnsiString(""):AnsiString("Да");
		return;
	}
	else {
		TWinControl* Edit = NULL;
		switch (FldRowPtr->FldType) {
			case ftInteger:  Edit = DBNumberEditEh1;   break;
			case ftDateTime: Edit = DBDateTimeEditEh1; break;
			default:         Edit = DBEditEh1;         break;
		}
		if (Edit) {
			PutEditOnGrid(StringGrid1,Edit,true);
			Variant V = (EditCol == 2) ? CurFF.MinValue :
							(EditCol == 3) ? CurFF.EqvValue :
												  CurFF.MaxValue;
			switch(GetComponentTag(Edit)) {
				case 1: DBEditEh1->Text = V;
						  DBEditEh1->SelectAll();
						  break;
				case 2: DBNumberEditEh1->Value  = V;
						  DBNumberEditEh1->SelectAll();
						  break;
				case 3: if (V.IsNull() || V.IsEmpty()) {
							  V = Date();
						  }
						  DBDateTimeEditEh1->Text = GetVariantString(V,FldRowPtr);
						  if (!HourMin) DBDateTimeEditEh1->DropDown();
						  break;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::ClearCell()
{
	int Col = StringGrid1->Col;
	int Row = StringGrid1->Row;
	StringGrid1->Cells[Col][Row] = "";
	switch (Col) {
		case 1: FieldFilterSet[Row-1].NullCheck = 0; break;
		case 2: FieldFilterSet[Row-1].MinValue  = Variant();
		case 3: FieldFilterSet[Row-1].EqvValue  = Variant();
		case 4: FieldFilterSet[Row-1].MaxValue  = Variant();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::sSpeedButtonClick(TObject *Sender)
{
	StringGrid1->SetFocus();
	switch (GetComponentTag(Sender)) {
		case 1: DeleteCurRow();
				  break;
		case 2: CreateNewRow();
				  break;
		case 3: ClearCurRow();
				  break;
		case 4: DeleteAllRows();
				  break;
		case 5: SelectFilter();
				  break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::SelectFilter()
{
	std::vector<FieldFilter> NewSet;
	int Cnt =  FieldFilterSet.size();
	for (int i = 0; i < Cnt; i++) {
		FieldFilter FF = FieldFilterSet[i];
		if (FF.NullCheck == 1 || !FF.MinValue.IsNull() || !FF.MinValue.IsEmpty() ||
										 !FF.EqvValue.IsNull() || !FF.EqvValue.IsEmpty() ||
										 !FF.MaxValue.IsNull() || !FF.MaxValue.IsEmpty() ) {
			FF.FldType = FldRowPtr->FldType;
			FF.Format  = FldRowPtr->Format;

			NewSet.push_back(FF);
		}
	}
	FieldFilterSet = NewSet;
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::DeleteCurRow()
{
	int RowCnt = StringGrid1->RowCount - 1;
	ClearCurRow();
	if (RowCnt == 1) {
		return;
	}
	int Row = StringGrid1->Row;

	if (Row == RowCnt) {
		StringGrid1->RowCount = RowCnt;
		FieldFilterSet.pop_back();
		return;
	}
	FieldFilterSet.erase(FieldFilterSet.begin() + Row - 1);
	for (int i = Row; i < RowCnt; i++) {
		StringGrid1->Rows[i] = StringGrid1->Rows[i+1];
		StringGrid1->Cells[0][i] = "Вариант "+IntToStr(i);
	}
	StringGrid1->RowCount = RowCnt;
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::AddRowIfNeed()
{
	int Row = StringGrid1->Row;
	int RowCnt = StringGrid1->RowCount - 1;
	int ColCnt = StringGrid1->ColCount;
	if (Row == RowCnt) {
		bool Add = false;
		for (int i = 1; i < ColCnt; i++) {
			if (StringGrid1->Cells[i][Row] != "") {
				Add = true;
				break;
			}
		}
		if (Add) {
			CreateNewRow();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::ClearSGRow(int Row)
{
	int Cnt = StringGrid1->ColCount;
	for (int i = 1; i < Cnt; i++) {
		StringGrid1->Cells[i][Row] = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::CreateNewRow()
{
	AddEmptyElement();
	int N = StringGrid1->RowCount;
	StringGrid1->RowCount = N+1;
	StringGrid1->Cells[0][N] = "Вариант "+IntToStr(N);
	ClearSGRow(N);
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::ClearCurRow()
{
	int Row = StringGrid1->Row;
	FieldFilter FF;
	FieldFilterSet[Row - 1] = FF;
	ClearSGRow(Row);
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::DeleteAllRows()
{
	FieldFilterSet.clear();
	AddEmptyElement();
	StringGrid1->RowCount = 2;
	ClearSGRow(1);
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::DBEditEh1KeyDown(TObject *Sender, WORD &Key,
			 TShiftState Shift)
{
	switch (Key) {
		case VK_RETURN: SaveEditValue(Sender);
		case VK_ESCAPE: StringGrid1->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::SaveEditValue(TObject *Sender)
{
	Variant V;
	switch(GetComponentTag(Sender)) {
		case 1: V = DBEditEh1->Text.Trim();	  break;
		case 2: V = DBNumberEditEh1->Value;   break;
		case 3: if (!HourMin) {
					  DBDateTimeEditEh1->CloseUp(true);
					  V = DBDateTimeEditEh1->Value;
				  }
				  else {
					 AnsiString S = DBDateTimeEditEh1->Text;
					 int H = StrToIntDef(GetPiece(S,":",1).Trim(),0);
					 int M = StrToIntDef(GetPiece(S,":",2).Trim(),0);
					 H %= 24;
					 M %= 60;
					 S = IntToStr(H) + ":";
					 if (H < 9 ) S = "0"+S;
					 if (M < 9)  S = S + "0";
					 S += IntToStr(M);
					 S = GetDateStr(Date()) + " " + S;
					 TDateTime DT = TDateTime(S);
					 V = DT;
				  }
				  break;
	}
	if      (EditCol == 2) FieldFilterSet[EditRow-1].MinValue = V;
	else if (EditCol == 3) FieldFilterSet[EditRow-1].EqvValue = V;
	else                   FieldFilterSet[EditRow-1].MaxValue = V;
	AnsiString S = GetVariantString(V,FldRowPtr);
	StringGrid1->Cells[EditCol][EditRow] = S;
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::DBEditEh1Exit(TObject *Sender)
{
	 EditExitStd(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::StringGrid1DblClick(TObject *Sender)
{
	EditCell();
}
//---------------------------------------------------------------------------
void __fastcall TFormGetFieldFilter::DBDateTimeEditEh1CloseUp(TObject *Sender, bool Accept)
{
	if (Accept) {
		SaveEditValue(Sender);
		StringGrid1->SetFocus();
	}
}
//---------------------------------------------------------------------------

