//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "DModT.h"
#include "ComProc.h"

#include "FrmSelSimpleEh.h"
//#include "FrmSelGoodSetEh.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
//#pragma link "CurrEdit"
//#pragma link "ToolEdit"
#pragma link "DBCtrlsEh"
#pragma link "MemTableEh"
#pragma link "DataDriverEh"
#pragma link "DBGridEhGrouping"
#pragma link "MemTableDataEh"
#pragma link "sComboEdit"
#pragma link "sCustomComboEdit"
#pragma link "sMaskEdit"
#pragma link "sPanel"
#pragma link "sCheckBox"
#pragma link "sEdit"
#pragma link "sLabel"
#pragma link "sSpeedButton"
#pragma link "sStatusBar"
#pragma link "DBAxisGridsEh"
#pragma link "DBGridEhToolCtrls"
#pragma link "ToolCtrlsEh"
#pragma resource "*.dfm"
TRect SelFormRect;
//---------------------------------------------------------------------------
void __fastcall PrepSelEhSimple(SelParamData& SPData,int KeyID,int Lft,
	const AnsiString& Caption,   const AnsiString& SQL,
	const AnsiString& FieldKey,  const AnsiString& FieldOut,
	const AnsiString& TitleList, const AnsiString& FieldList,AnsiString WidthList)
{
	SPData.Left       = Lft;
	SPData.SQL        = SQL;
	SPData.Caption    = Caption;
	SPData.TitleList  = TitleList;
	SPData.FieldList  = FieldList;
	SPData.WidthList  = WidthList;
	SPData.FieldKey   = FieldKey;
	SPData.FieldOut   = FieldOut;
	SPData.FieldFlt   = FieldOut;
	SPData.SPFlags   |= SelParamData::INC_SEARCH;
	if (KeyID) SPData.KeyValue = KeyID;
	SPData.Flags     |= STD_STATUSBAR | FILTER_BY_NAME;
}
//---------------------------------------------------------------------------
void ExecSelEhSimple(TForm* Form,SelParamData& SPData)
{
	TFormSelSimpleEh* Frm = new TFormSelSimpleEh(Form,&SPData);
	Frm->ShowModal();
	delete Frm;
}
//---------------------------------------------------------------------------
bool __fastcall ExecSelEhSimple(TForm* Form,SelParamData& SPData,const AnsiString& GetFldList,int* ResID,AnsiString* Name)
{
	bool bRes = false;
	TFormSelSimpleEh* Frm = new TFormSelSimpleEh(Form,&SPData);
	if (Frm->ShowModal() == mrOk) {
	  if (ResID) *ResID = Frm->WrkQuery->FieldByName(GetPiece(GetFldList,"/",1))->AsInteger;
	  if (Name) {
		  int i = 2;
		  AnsiString Res;
		  while(true) {
			  AnsiString FName = GetPiece(GetFldList,"/",i);
			  if (FName == "") break;
			  if (Res != "") Res += "/";
			  Res += Frm->WrkQuery->FieldByName(FName)->AsString;
			  ++i;
		  }
		  *Name = Res;
	  }
	  bRes = true;
	}
	delete Frm;
	return bRes;
}
//---------------------------------------------------------------------------
bool ExecSelEhSimple(TForm* Form,SelParamData& SPData,const AnsiString& GetFldList,AnsiString& ResFldList)
{
	bool bRes = false;
	TFormSelSimpleEh* Frm = new TFormSelSimpleEh(Form,&SPData);
	if (Frm->ShowModal() == mrOk) {
	  AnsiString FName;
	  int i = 0;
	  while (++i) {
		 FName = GetPiece(GetFldList,"/",i);
		 if (FName == "") break;
		 ResFldList = SetPiece(ResFldList,Frm->WrkQuery->FieldByName(FName)->AsString,"/",i);
	  }
	  bRes = true;
	}
	delete Frm;
	return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhTransCompanyID(TForm* Form,int Left, int& TransCompID,int TransTypeID,AnsiString *Res)
{
	SelParamData SPData(Form);
	SPData.FieldOut = SPData.DefFieldFlt = "Trans_Company_Name";
	SPData.Flags |= FILTER_BY_NAME;
	if (!TransCompID) TransCompID = DModT->DefCompID;
	PrepSelEhSimple(SPData,TransCompID,Left,
	"Выбор транспортной компании","Select * from Sel_Trans_Company(" + IntToStr(TransTypeID) +
	") where " + GetStatusStr("Status") + " order by Trans_Company_Name",
	"Trans_Company_ID",  "Trans_Company_Name",
	"Наименование компании","Trans_Company_Name","300");
	return ExecSelEhSimple(Form,SPData,"Trans_Company_ID/Trans_Company_Name",&TransCompID,Res);
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhTransTypeID(TForm* Form,int Left, int& TransTypeID,AnsiString *Res)
{
	SelParamData SPData(Form);
	SPData.FieldOut = SPData.DefFieldFlt = "Trans_Type_Name";
	SPData.Flags |= FILTER_BY_NAME;
	PrepSelEhSimple(SPData,TransTypeID,Left,
	"Выбор типа ТС","Select * from Trans_Type where " + GetStatusStr("Status") +
	" order by Trans_Type_Name",
	"Trans_Type_ID",  "Trans_Type_Name",
	"Наименование типа","Trans_Type_Name","300");
	return ExecSelEhSimple(Form,SPData,"Trans_Type_ID/Trans_Type_Name",&TransTypeID,Res);
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhEmployeeID(TForm* Form,int Left, int& EmployeeID)
{
	SelParamData SPData(Form);
	SPData.FieldOut = SPData.DefFieldFlt = "Full_Name";
	SPData.Flags |= FILTER_BY_NAME;
	PrepSelEhSimple(SPData,EmployeeID,Left,
	"Выбор менеджера","Select * from Employee where " + GetStatusStr("Status") +
	" order by Full_Name",
	"Employee_ID",  "Full_Name",
	"ФИО","Full_Name","300");
	return ExecSelEhSimple(Form,SPData,"Employee_ID",&EmployeeID);
}
//---------------------------------------------------------------------------
void  __fastcall AfterCreateSpecViewTrans(GridData& GData)
{
	TFormSelSimpleEh* Form = dynamic_cast<TFormSelSimpleEh*>(GData.WrkForm);
	if (Form) {
		GData.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANS_COMPANY_ID"),  Form->GetTransCompanyID));
		GData.FunGetIDMap.insert(pair<AnsiString,FunGetID>(AnsiString("TRANS_TYPE_ID"),     Form->GetTransTypeID));
	}
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhTransportID(TForm* Form,int Left, int& TransportID,  int& TransTypeID,int& TransCompID, AnsiString &Params,AnsiString* ResFldList)
{
	SelParamData SPData(Form);
	SPData.FieldOut = SPData.DefFieldFlt = "REG_NUMBER";
	SPData.Flags |= FILTER_BY_NAME;
	SPData.FormatList = "";

	AnsiString        EditQuerySQL  = "Select * from EDIT_TRANSPORT (:TRANSPORT_ID,:TRANSPORT_NAME,";
	if (TransCompID > 0) 	{
		 EditQuerySQL += IntToStr(TransCompID)+",";
		 SPData.AddExtParam(ftInteger, "TRANS_COMPANY_ID",  TransCompID);
		 SPData.EditAllowMask =  0x0017;
		 SPData.NullAllowMask =  0x001F;
		 SPData.Select_IDMask =  0x0002;
	}
	else {
		 EditQuerySQL +=  ":TRANS_COMPANY_ID,";
		 SPData.AddSelParam(ftInteger,"TRANS_COMPANY_ID",Null);
		 SPData.EditAllowMask =  0x001F;
		 SPData.NullAllowMask =  0x001F;
		 SPData.Select_IDMask =  0x000A;
	}
	SPData.FieldOut      = "TRANSPORT_NAME";
	SPData.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANS_COMPANY_NAME","TRANS_COMPANY_ID"));
	SPData.FldTranslateMap.insert(pair<AnsiString,AnsiString>("TRANS_TYPE_NAME",   "TRANS_TYPE_ID"));

	SPData.AfterCreate = AfterCreateSpecViewTrans;

	SPData.EditQuerySQL = EditQuerySQL +  ":TRANS_TYPE_ID,:REG_NUMBER,:PASS_NUMBER,"
													  ":TRANS_DRIVER_ID,:TRANS_COMMENT," + Params + ",:DATECHANGE,:STATUS)";

	AnsiString SQL = "Select * from Sel_Transport(NULL) where " + GetStatusStr("Status");
	if (TransCompID > 0) {
		SQL += " and Trans_Company_ID = " + IntToStr(TransCompID);
	}
	if (TransCompID < 0) {
		SQL += " and Trans_Company_Flag = 1";
	}
	if (TransTypeID) {
		SQL += " and Trans_Type_ID = " + IntToStr(TransTypeID);
	}
	SQL += " Order by Trans_Company_Flag,Trans_Company_Name,Transport_Name";
	PrepSelEhSimple(SPData,TransportID,Left,
	"Выбор ТС",SQL,
	"Transport_ID","REG_NUMBER"  ,
	"Регис.N/Тип ТС/Наименование ТС/Перевозчик/Мест",
	"Reg_Number/Trans_Type_Name/Transport_Name/Trans_Company_Name/Pass_Number",
	"90/124/186/184/46");
	AnsiString FldList = "Transport_ID/Transport_ID/Trans_Type_ID/TransPort_Name/Reg_Number/Pass_Number/TRANS_COMMENT";
	if (ExecSelEhSimple(Form,SPData,FldList,&TransportID,ResFldList)) {
//		TransportID     = StrToInt(GetPiece(ResFldList,"/",1));
		TransCompID     = StrToIntDef(GetPiece(*ResFldList,"/",1),0);
		TransTypeID     = StrToIntDef(GetPiece(*ResFldList,"/",2),0);
		*ResFldList     = GetSegment(*ResFldList,"/",3,8);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhContactID(TForm* Form,int Left, int& ContactID,int ClientID, AnsiString &Params,AnsiString *Res)
{
	SelParamData SPData(Form);
	SPData.FieldOut = SPData.DefFieldFlt = "Contact_Name";
	SPData.Flags |= FILTER_BY_NAME;
	AnsiString SQL = "Select * from Contact where " + GetStatusStr("Status");
	if (ClientID ) {
		SPData.EditAllowMask = 3;
		SPData.NullAllowMask = 2;
		SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;
		SPData.EditQuerySQL = "Select * from Edit_Contact(" + IntToStr(ClientID) +
									 " ,:CONTACT_ID,:CONTACT_NAME,:CONTACT_PHONE," + Params + ",:DATECHANGE,:STATUS)";
		SQL +=  " and Client_ID = " + IntToStr(ClientID);
	}
	PrepSelEhSimple(SPData,ContactID,Left,
	"Выбор контактных данных",SQL,
	"Contact_ID",  "Contact_Name",
	"Контактное лицо/Телефон","Contact_Name/Contact_Phone","300/300");
	return ExecSelEhSimple(Form,SPData,"Contact_ID/Contact_Name/Contact_Phone",&ContactID,Res);
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhClientID(TForm* Form,int Left, int& ClientID)
{
	SelParamData SPData(Form);
	SPData.FieldOut = SPData.DefFieldFlt = "Client_Name";
	SPData.Flags |= FILTER_BY_NAME;
	PrepSelEhSimple(SPData,ClientID,Left,
	"Выбор клиента","Select * from Client where " + GetStatusStr("Status") +
	" order by Client_Name",
	"Client_ID",  "Client_Name",
	"ФИО","Client_Name","300");
	return ExecSelEhSimple(Form,SPData,"Client_ID",&ClientID);
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhTownID(TForm* Form,int Left,int &ID,AnsiString Params,AnsiString *Res)
{
	SelParamData SPData(Form);
	SPData.EditQuerySQL = "Select * from Edit_Town(:TOWN_ID,:TOWN_NAME," + Params + ",:DATECHANGE,:STATUS)";
	SPData.EditAllowMask = 1;
	SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;
	if (!ID) ID = DModT->DefTownID;
	PrepSelEhSimple(SPData,ID,Left,
	"Выбор населенного пункта","Select * from Town where " + GetStatusStr("Status") +
	" order by Town_Name",
	"Town_ID",  "Town_Name",
	"Наименование","Town_Name","300");
	return ExecSelEhSimple(Form,SPData,"Town_ID/Town_Name",&ID,Res);
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhWorkTypeID(TForm* Form,int Left,int &ID,int ClientID,AnsiString Params,AnsiString *Res)
{
	SelParamData SPData(Form);
	SPData.EditQuerySQL = "Select * from Edit_Work_Type(:WORK_TYPE_ID,:WORK_TYPE_NAME," + Params + ",:DATECHANGE,:STATUS)";
	SPData.EditAllowMask = 1;
	SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;

	PrepSelEhSimple(SPData,ID,Left,
	"Выбор типа работы","Select * from Work_Type where Client_ID = " +IntToStr(ClientID) + " and " +GetStatusStr("Status") +
	" order by Work_Type_Name",
	"Work_Type_ID",  "Work_Type_Name",
	"Наименование","Work_Type_Name","300");
	return ExecSelEhSimple(Form,SPData,"Work_Type_ID/Work_Type_Name",&ID,Res);
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhStreetID(TForm* Form,int Left,int &ID,int TownID, AnsiString Params,AnsiString *Res)
{
	SelParamData SPData(Form);
	SPData.EditQuerySQL = "Select * from Edit_Street(:Street_ID,:Street_NAME,NULL," + Params + ",:DATECHANGE,:STATUS)";
	SPData.EditAllowMask = 1;
	SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;
	PrepSelEhSimple(SPData,ID,Left,
	"Выбор улицы пункта","Select * from Street where Town_ID = " + IntToStr(TownID) + " and " + GetStatusStr("Status") +
	" order by Street_Name",
	"Street_ID",  "Street_Name",
	"Наименование","Street_Name","300");
	return ExecSelEhSimple(Form,SPData,"Street_ID/Street_Name",&ID,Res);
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhDriverID(TForm* Form,int Left,int &ID, int TransCompID, AnsiString Params, AnsiString* Res)
{
	SelParamData SPData(Form);
	AnsiString SQL;
	if (TransCompID > 0) {
		SPData.EditQuerySQL = "Select * from Edit_Driver(:Driver_ID,:Driver_Name,:Driver_Phone," +
										IntToStr(TransCompID) + "," +Params + ",:DATECHANGE,:STATUS)";
		SQL = "Select * from Driver where Trans_Company_ID = " + IntToStr(TransCompID) + " and  " +
				GetStatusStr("Status") + " order by Driver_Name";
	}
	else {
		SQL = "Select D.* from Driver D inner join Trans_Company C on  D.Trans_Company_ID = C.Trans_Company_ID "
				"and C.Trans_Company_Flag = 0  and  " + GetStatusStr("D.Status") + " order by Driver_Name";
	}
	SPData.EditAllowMask = 3;
	SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;
	PrepSelEhSimple(SPData,ID,Left,
	"Выбор водителя",SQL,
	"Driver_ID",  "Driver_Name",
	"ФИО волителя/Телефон","Driver_Name/Driver_Phone","300/300");
	return ExecSelEhSimple(Form,SPData,"Driver_ID/Driver_Name/Driver_Phone",&ID,Res);

}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelEhExpenseID(TForm* Form,int Left,int &ID,AnsiString Params)
{
	SelParamData SPData(Form);
	SPData.EditQuerySQL = "Select * from Edit_Expense(:Expense_ID,:Expense_NAME," + Params + ",:DATECHANGE,:STATUS)";
	SPData.EditAllowMask = 1;
	SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;

	PrepSelEhSimple(SPData,ID,Left,
	"Выбор статьи расхода","Select * from Expense where " + GetStatusStr("Status") +
	" order by Expense_Name",
	"Expense_ID",  "Expense_Name",
	"Наименование","Expense_Name","300");
	return ExecSelEhSimple(Form,SPData,"Expense_ID",&ID);
}
//---------------------------------------------------------------------------
void  __fastcall AfterCreateSpecView(GridData& GData)
{
	 GData.WrkGrid->Columns->Items[1]->PickList->Add("Нет");
	 GData.WrkGrid->Columns->Items[1]->PickList->Add("Да");
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelSpecViewID(TForm* Form, int Left, int &ID, AnsiString* ViewName,AnsiString* ResWdt,AnsiString Params)
{
	SelParamData SPData(Form);
	SPData.EditQuerySQL = "Select * from Edit_Spec_View(:SPEC_VIEW_ID,:SPEC_VIEW_NAME,:FLAG_COMMON,:COL_WDT," + Params + ",:DATECHANGE,:STATUS)";
	SPData.EditAllowMask = 3;
	SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;

	SPData.FldTranslateMap.insert(pair<AnsiString,AnsiString>("FULL_NAME",       "EMPLOYEE_ID"));
	SPData.FldTranslateMap.insert(pair<AnsiString,AnsiString>("FLAG_COMMON_STR", "FLAG_COMMON"));

	SPData.AfterCreate = AfterCreateSpecView;
	PrepSelEhSimple(SPData,ID,Left,
	"Выбор вида просмотра таблицы","Select * from Sel_Spec_View(" + IntToStr(DModT->CurEmpID) + ") where " + GetStatusStr("Status") +
	" order by Spec_View_Name,Flag_Common",
	"Spec_View_ID",  "Spec_View_Name",
	"Наименование вида/Общий/Ширина/Владелец/Список","Spec_View_Name/Flag_Common_Str/Screen_Width/Full_Name/Col_Wdt","300/60/60/150/400");
	AnsiString ResStr;
	if (ExecSelEhSimple(Form,SPData,"Spec_View_ID/Spec_View_Name/Col_Wdt",ResStr)) {
		ID 	  	= StrToInt(GetPiece(ResStr,"/",1));
	  *ViewName = GetPiece(ResStr,"/",2);
	  *ResWdt   = GetPiece(ResStr,"/",3);
	  return true;
	}
	return false;

}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelFilterID(TForm* Form, int Left, int &ID, AnsiString* FilterName,AnsiString Params)
{
	SelParamData SPData(Form);
	SPData.EditQuerySQL = "Select * from Edit_Filter(:FILTERS_ID,:FILTER_NAME,:FLAG_COMMON," + Params + ",:DATECHANGE,:STATUS)";
	SPData.EditAllowMask = 3;
	SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;

	SPData.AfterCreate = AfterCreateSpecView;
	SPData.FldTranslateMap.insert(pair<AnsiString,AnsiString>("FLAG_COMMON_STR", "FLAG_COMMON"));

	PrepSelEhSimple(SPData,ID,Left,
	"Выбор фильтра для просмотра таблицы","Select * from Sel_Filter(" + IntToStr(DModT->CurEmpID) + ") where " + GetStatusStr("Status") +
	" order by Filter_Name,Flag_Common desc",
	"Filters_ID",  "Filter_Name",
	"Наименование фильтра/Общий/Ширина ","Filter_Name/Flag_Common_Str","300/60");
	AnsiString ResStr;
	if (ExecSelEhSimple(Form,SPData,"Filters_ID/Filter_Name",ResStr)) {
		ID 	  	= StrToInt(GetPiece(ResStr,"/",1));
	  *FilterName = GetPiece(ResStr,"/",2);
	  return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void __fastcall FillRestoreData(ShowModalForm* SMF,RestValue* RestData)
{
	RestData->FieldName     = SMF->FBN("Field_Name")->AsString;
	RestData->Old_ID_Value  = SMF->FBN("Old_ID_Value")->AsInteger;
	RestData->New_ID_Value  = SMF->FBN("New_ID_Value")->AsInteger;
	RestData->Old_Str_Value = SMF->FBN("Old_Str_Value")->AsString;
	RestData->New_Str_Value = SMF->FBN("New_Str_Value")->AsString;
	RestData->NewValue      = SMF->FBN("New_ID_Value")->IsNull ? SMF->FBN("New_Str_Value")->AsVariant:
                                                                SMF->FBN("New_Id_Value")->AsVariant;
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelHistoryID(TForm* Form, int Left,AnsiString Title,AnsiString TableName,int ID,const AnsiString& FieldNames,const AnsiString &FieldTitles,RestValue& RestData)
{
	SelParamData SPData(Form);
	SPData.SPFlags |= SelParamData::NO_PANEL;
	SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;
	AnsiString SQL = "Select * from Sel_HISTORY_ONE('" + TableName + "'," +  IntToStr(ID) + ",'" + FieldNames + "','" + FieldTitles +
						  "') order by History_ID";
	ID = 0;
	PrepSelEhSimple(SPData,ID,Left, Title, SQL,
						 "HISTORY_ID",  "",
		"Изменение|N/Изменение|Группа/Изменяемое поле|Заголовок/Изменяемое поле|В базе/Действие/Предыдущее Значение|Число/Предыдущее Значение|Строка/Новое Значение|Число/Новое Значение|Строка/Изменено|Когда/Изменено|Кем/Изменено|С компьютера",
		"HISTORY_ID/TRANSACTION_ID/FIELD_TITLE/FIELD_NAME/MSG/OLD_ID_VALUE/OLD_STR_VALUE/NEW_ID_VALUE/NEW_STR_VALUE/DATECHANGE/FIO/COMP_NAME",
		"45/45/145/140/157/50/125/50/125/150/140/100");
	ShowModalForm SMF(Form,&SPData);
	if (SMF.Execute()) {
		FillRestoreData(&SMF,&RestData);
		return true;
	}
/*
	if (ExecSelEhSimple(Form,SPData,"",ResStr)) {
		RestData.FieldName = Form->FieldByName("Field_Name")->AsString;
		RestData.FieldName = Form->FieldByName("Old_ID_Value")->AsString;
	}
*/
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall SimpleSelHistoryID(TForm* Form, int Left,AnsiString Title,AnsiString TableName,int ID,TStringList* FieldNames,TStringList* TitleNames,RestValue& RestData)
{
	SelParamData SPData(Form);
	SPData.SPFlags |= SelParamData::NO_PANEL;
	SPData.Flags     = STD_STATUSBAR | INS_IF_NOT_FOUND | FILTER_BY_NAME | CAN_SEE_DELETED;
	AnsiString SQL = "Select * from Sel_HISTORY('" + TableName + "'," +  IntToStr(ID);
	AnsiString SS1,SS2;
	for (int i = 0; i < 7; i++) {
		if (i < FieldNames->Count) {
			SS1 = FieldNames->Strings[i];
			SS2 = TitleNames->Strings[i];
			SQL += ",'" + SS1 + "','" + SS2 + "'";
		}
		else
			 SQL += ",null,null";
	}
	SQL +=") order by History_ID";
	ID = 0;
	PrepSelEhSimple(SPData,ID,Left, Title, SQL,
						 "HISTORY_ID",  "",
		"Изменение|N/Изменение|Группа/Изменяемое поле|Заголовок/Изменяемое поле|В базе/Действие/Предыдущее Значение|Число/Предыдущее Значение|Строка/Новое Значение|Число/Новое Значение|Строка/Изменено|Когда/Изменено|Кем/Изменено|С компьютера",
		"HISTORY_ID/TRANSACTION_ID/FIELD_TITLE/FIELD_NAME/MSG/OLD_ID_VALUE/OLD_STR_VALUE/NEW_ID_VALUE/NEW_STR_VALUE/DATECHANGE/FIO/COMP_NAME",
		"45/45/145/140/157/50/125/50/125/150/140/100");

	ShowModalForm SMF(Form,&SPData);
	if (SMF.Execute()) {
		FillRestoreData(&SMF,&RestData);
		return true;
	}
/*
	AnsiString ResStr;
	if (ExecSelEhSimple(Form,SPData,"",ResStr)) {
	  return true;
	}
*/
	return false;
}
//---------------------------------------------------------------------------
__fastcall TFormSelSimpleEh::TFormSelSimpleEh(TComponent* Owner,SelParamData* SPData)
		  : TForm(Owner)
{
	this->SPData = SPData;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::FormClose(TObject *Sender,
	  TCloseAction &Action)
{
	if (Memo1->Visible)  WriteMemoStd(*SPData,Memo1);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::FormCreate(TObject *Sender)
{
	AnsiString S;

	Top      = SPData->Top;
   Left     = SPData->Left;
   Caption  = SPData->Caption;
	if (SPData->OuterDSet) {
	  WrkQuery = MemTableEh1;
	  MemTableEh1->OnCalcFields = SPData->OuterDSet->OnCalcFields;
   }
   else {
	  WrkQuery = MemTableEh1;
	  SPData->SrcDSet = Query1;
	  Query1->SQL->Add(SPData->SQL);
   }
   if (SPData->EditQuerySQL != "") {
	  SPData->WrkQuery = Query2;
	  Query2->SQL->Text = SPData->EditQuerySQL;
   }
   else Memo1->ReadOnly = true;
	if (!SPData->WrkQuery || SPData->SPFlags & SelParamData::EDIT_FORM) {
	  sCheckBox1->Visible = false;
	  sCheckBox1->Enabled = false;
	}
   if (!SPData->WrkQuery)
	  SwitchGridOption(DBGridEh1,true,Dbgrideh::dgRowSelect);
	SPData->TextEdit   = DBEditEh1;
	SPData->NumbEdit   = DBNumberEditEh1;
	SPData->DateEdit   = DBDateTimeEditEh1;
	SPData->ListEdit   = ComboBox1;
   if (SPData->Flags & STD_STATUSBAR)
	  SPData->WrkSBar    = sStatusBar1;
   if (!(SPData->SPFlags & SelParamData::NO_PANEL))
	  SPData->EditSearch = EditSearch;

   if (SPData->SPFlags & SelParamData::NO_PANEL) {
	  sPanel1->Enabled = false;
	  sPanel1->Visible = false;
	  sPanel1->Align   = alNone;
   }
   Memo1->Text = "";
   int SumW    = 0;
   DBGridEh1->UseMultiTitle = SPData->TitleList.Pos("|") > 0;
   SBtn1->Visible = SPData->SPFlags & SelParamData::SEL_BTN_VISIBLE;
   SBtn1->Enabled = SPData->SPFlags & SelParamData::SEL_BTN_VISIBLE;
   // ---- определяем положение формы ----------------------------
   int i = 0;
	while(true) {
		i++;
		S = GetPiece(SPData->WidthList,"/",i);
		if (S == "") break;
		DBGridEh1->Columns->Add();
		int CurW = StrToInt(S);
		SumW += CurW;
		TColumnEh* Column = DBGridEh1->Columns->Items[i-1];
		Column->Width           = CurW;
		Column->FieldName       = GetPiece(SPData->FieldList, "/",i);
		Column->Title->Caption  = GetPiece(SPData->TitleList, "/",i);
		Column->Title->ToolTips = true;
		Column->DisplayFormat   = GetPiece(SPData->FormatList,"/",i);
		Column->ToolTips 			= true;
		Column->WordWrap = true;
	}
	SumW +=60;
	if (SumW > Screen->Width) {
	  SumW = Screen->Width;
	  Left =0;
	}
	SPData->WrkGrid    = DBGridEh1;
	int MaxHeight = SPData->MaxHeight;
	if (MaxHeight < 200) MaxHeight = 750;
	SetFormPosStd(this,SumW,MaxHeight,SPData->Left,!(SPData->MaxHeight));
	if (SPData->SPFlags & SelParamData::INC_SEARCH) {
	  DBGridEh1->OptionsEh = DBGridEh1->OptionsEh << dghIncSearch << dghPreferIncSearch;
	}

	if (!SPData->OuterDSet && OpenDSetStd(*SPData)) {
	  SwitchGridOptionEh(DBGridEh1,true,Dbgrideh::dghRowHighlight);
	  NumerateGridFields(DBGridEh1);  // Должно быть после Open
	  SPData->SrcDSet->Active = false;
	}
	else {
	  if (SPData->OuterDSet) {
		 MemTableEh1->LoadFromDataSet(SPData->OuterDSet,-1,Memtableeh::lmCopy,false);
	  }
	  SwitchGridOptionEh(DBGridEh1,true,Dbgrideh::dghRowHighlight);
	  NumerateGridFields(DBGridEh1);  // Должно быть после Open
	  RestorePosStd(*SPData,false);
	}
	SetStatusBarStd(*SPData);
	if (!WrkQuery->FindField("COMMENT")) {
	  Memo1->Align = alNone;
	  Memo1->Enabled = false;
	  Memo1->Visible = false;
	  Splitter1->Enabled = false;
	  Splitter1->Visible = false;
	}
	if (SPData->AfterCreate) SPData->AfterCreate(*SPData);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::FormDestroy(TObject *Sender)
{
	if (Query1 == WrkQuery) WrkQuery->Filtered = false;
	SPData->SelArray.clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::FormKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
	FormKeyDownStd(*SPData,Key,Shift);
	switch (Key) {
		case VK_F3:  if (Memo1->Visible) ShowMemoStd(*SPData,Memo1);
						 break;
		case VK_F4:  if (sCheckBox1->Visible)
							sCheckBox1->Checked = ! sCheckBox1->Checked;
						 break;
		case VK_F11: ProcHistory(Shift.Contains(ssCtrl));
	}
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormSelSimpleEh::TranslateName(AnsiString FldName)
{
	if (SPData->FldTranslateMap.size()) {
		std::map<AnsiString,AnsiString>::iterator iter = SPData->FldTranslateMap.find(FldName);
		if (iter != SPData->FldTranslateMap.end()) {
			 FldName = iter->second;
		}
	}
	return FldName;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::ProcHistory(bool All)
{
	AnsiString Title  = "Просмотр истории изменения";
	AnsiString FldKey = SPData->FieldKey;
	AnsiString TableName = GetPiece(FldKey,"_ID",1).UpperCase();
	int ID = MemTableEh1->FieldByName(FldKey)->AsInteger;
	AnsiString FieldNames;
	AnsiString FieldTitles;
	TDBGridEh* Grid = SPData->WrkGrid;
	if (All) {
		TDBGridColumnsEh* Columns = Grid->Columns;
		int Cnt = Columns->Count;

		AnsiString S;
		for (int i = 0; i < Cnt; i++) {
			 TColumnEh* Column = Columns->Items[i];
			 if (Column->Visible) {
				 AnsiString X = ","+TranslateName(Column->FieldName);
				 if (!FieldNames.Pos(X)) {
					 FieldNames  += X ;
					 FieldTitles += "," + Column->Title->Caption;
				 }
			 }
		}
		Title = Title + " всех видимых полей";
		if (!FieldNames.Pos(FldKey+",")) {
			FieldNames  = FldKey     + FieldNames  + ",STATUS";
			FieldTitles = "N записи" + FieldTitles + ",Состояние";
		}
		else {
			FieldNames  = FieldNames.SubString(2,1000)  + ",STATUS";
			FieldTitles = FieldTitles.SubString(2,1000) + ",Состояние";
		}
	}
	else {
		TColumnEh* Column = Grid->Columns->Items[Grid->Col - 1];
		FieldNames  = TranslateName(Column->FieldName);
		FieldTitles = Column->Title->Caption;
		Title = Title + " поля > "+ FieldTitles + " <";
	}
	FieldNames = FieldNames.UpperCase();
	RestValue RestData;
	if (SimpleSelHistoryID(this, 0,Title,TableName,ID,FieldNames,FieldTitles, RestData)) {


	}

}
// ========= Grid events ===================================================
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::DBGridEh1DblClick(TObject *Sender)
{
	if      (sCheckBox1->Checked || SPData->SPFlags & SelParamData::EDIT_FORM) ProcReturn();
	else if (!KeyFieldIsNullStd(*SPData) && !RowIsDeleted(WrkQuery)) {
	  if (SBtn1->Visible) ProcSelectStd(*SPData);
	  else                ModalResult = mrOk;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::DBGridEh1DrawColumnCell(TObject *Sender,
	  const TRect &Rect, int DataCol, TColumnEh *Column,
	  TGridDrawStateEh State)
{
   DrawColumnCellStd(Rect,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::DBGridEh1GetCellParams(TObject *Sender,
	  TColumnEh *Column, TFont *AFont, TColor &Background,
	  TGridDrawStateEh State)
{
   GetCellParamsStd(*SPData,AFont,Background,State);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::DBGridEh1KeyDown(TObject *Sender,
	  WORD &Key, TShiftState Shift)
{
   switch(Key) {
	  case VK_RETURN: if (Shift.Contains(ssCtrl)  || Shift.Contains(ssAlt) ||
								 Shift.Contains(ssShift) || sCheckBox1->Checked    ||
								 SPData->SPFlags & SelParamData::EDIT_FORM) ProcReturn();
							else if (!KeyFieldIsNullStd(*SPData) && !RowIsDeleted(WrkQuery))
								 ModalResult = mrOk;
							break;
	  default:        ProcKeyDownStd(*SPData,Key);
					  break;
	  case VK_ESCAPE: ModalResult = mrCancel;    break;
   }
}
// ========= Query events ===================================================
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::RxQuery1AfterClose(TDataSet *DataSet)
{
   Memo1->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::RxQuery1AfterScroll(TDataSet *DataSet)
{
	if (!EditSearch->Focused()) SetEditSearchTxtStd(*SPData);
   if (Memo1->Visible)         ShowMemoStd(*SPData,Memo1);
   AfterScrollStd(*SPData);
//   SetStatusBarStd(*SPData);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::MemTableEh1CalcFields(TDataSet *DataSet)
{
   CalcFieldsStd(*SPData);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::RxQuery1FilterRecord(TDataSet *DataSet,
	  bool &Accept)
{
	Accept = FilterRecordStd(*SPData);
}
//---------------------------------------------------------------------------
// ========= EditSearch handlers ============================================
void __fastcall TFormSelSimpleEh::EditSearchChange(TObject *Sender)
{
   EditSearchChangeStd(*SPData);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::EditSearchClick(TObject *Sender)
{
	EditSearch->SelectAll();
   SwitchGridOptionEh(DBGridEh1,true,Dbgrideh::dghRowHighlight);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::EditSearchEnter(TObject *Sender)
{
   EditSearch->SelectAll();
   SwitchGridOptionEh(DBGridEh1,true,Dbgrideh::dghRowHighlight);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::EditSearchExit(TObject *Sender)
{
   SetEditSearchTxtStd(*SPData);
	if (SPData->WrkSProc || SPData->WrkQuery)
	  SwitchGridOptionEh(DBGridEh1,false,Dbgrideh::dghRowHighlight);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::EditSearchKeyDown(TObject *Sender,
	  WORD &Key, TShiftState Shift)
{
   TModalResult MR = EditSearchKeyDownStd(*SPData,Key,Shift);
	if (!(SPData->SPFlags & SelParamData::EDIT_FORM))
	  ModalResult = MR;
   else {
	  if (MR == mrOk) DBGridEh1->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::EditSearchKeyUp(TObject *Sender,
	  WORD &Key, TShiftState Shift)
{
   EditSearchKeyUpStd(*SPData,Key,Shift);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::ProcReturn()
{
   ProcReturnStd(*SPData);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::EditExit(TObject *Sender)
{
   EditExitStd(*SPData,Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::EditKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
   EditKeyDownStd(*SPData,Sender,Key,Shift);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::CheckBox1KeyDown(TObject *Sender,
	  WORD &Key, TShiftState Shift)
{
   if (Key == VK_ESCAPE) ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::Memo1Exit(TObject *Sender)
{
   WriteMemoStd(*SPData,Memo1);
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::SBtnClick(TObject *Sender)
{
   switch (GetComponentTag(Sender)) {
	  case 1: ModalResult = mrOk; break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormSelSimpleEh::FormActivate(TObject *Sender)
{
   RestorePosStd(*SPData,false);
	RepaintNewKeyLine(*SPData);
	if (SPData->EditSearch) {
//		DBGridEh1->SetFocus();
		SPData->EditSearch->SetFocus();
//		SPData->EditSearch->SelectAll();
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormSelSimpleEh::GetTransCompanyID(TForm* Frm, int Left,int &ID,TParams*&)
{
	int TransTypeID = 0;
	return SimpleSelEhTransCompanyID(Frm,0,ID,TransTypeID,NULL);
}
//---------------------------------------------------------------------------
bool __fastcall TFormSelSimpleEh::GetTransTypeID(TForm* Frm, int Left,int &ID,TParams*&)
{
	return SimpleSelEhTransTypeID(Frm,0,ID, NULL);
}
//---------------------------------------------------------------------------

