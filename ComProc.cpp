//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "ComProc.h"
//#include "Excel_2K_SRVR.h"
#include <locale>
#include <ctype.h>
int Debug = 0;
bool __fastcall GetDefSrvID(int&) {
	return false;    // тогда нет проверки на работу в правильном адресном пространстве
}
bool GridData::GetCurSrvID(int &CurSrvID) {
		if (FGetSrvID) return FGetSrvID(CurSrvID);
		else          return true;
}
FunGetSrvID GridData::FGetSrvID = GetDefSrvID;
GridData*   GridData::WrkGData  = NULL;
//---------------------------------------------------------------------------
#pragma package(smart_init)
//===========================================================================
//==== Печать числа а текстовом виде ========================================
//===========================================================================
AnsiString GetDTVal(Variant V) {
	try {
		TDateTime DT = V;
		return DT.FormatString("dd.mm.yy hh:nn");
	} catch (...) {

	}
	return "Cannot cast";
}
AnsiString  __fastcall GetTripleTxt(AnsiString S,int N)
{
	switch (S.Length()) {
		case 1:  S = "00" + S; break;
		case 2:  S = "0"  + S; break;
		case 3:  if (S != "000")
						break;
		default: return "";
	}
	AnsiString R,P,EA,E1,E2,E3;
	switch (N) {
		case 2: P = "тысяч";    E1 = "а "; E2 = "и "; E3 = " ";   break;
		case 3: P = "миллион";  E1 = " ";  E2 = "а "; E3 = "ов "; break;
		case 4: P = "миллиард"; E1 = " ";  E2 = "а "; E3 = "ов "; break;
		case 5: P = "триллион"; E1 = " ";  E2 = "а "; E3 = "ов "; break;
	}
	AnsiString S1 = S.SubString(1,1); int I1 = StrToInt(S1);
	AnsiString S2 = S.SubString(2,1); int I2 = StrToInt(S2);
	AnsiString S3 = S.SubString(3,1); int I3 = StrToInt(S3);
	switch (I1) {
		case 1: R = "сто ";        break;
		case 2: R = "двести ";     break;
		case 3: R = "триста ";     break;
      case 4: R = "четыреста ";  break;
      case 5: R = "пятьсот ";    break;
      case 6: R = "шестьсот ";   break;
      case 7: R = "семьсот ";    break;
      case 8: R = "восемьсот ";  break;
      case 9: R = "девятьсот ";  break;
   }
   switch (I2) {
      case 1:
              switch (I3) {
                 case 0: R = R + "десять ";   break;
                 case 1: R = R + "одиннадцать ";   break;
                 case 2: R = R + "двенадцать ";    break;
                 case 3: R = R + "тринадцать ";    break;
                 case 4: R = R + "четырнадцать ";  break;
                 case 5: R = R + "пятнадцать ";    break;
                 case 6: R = R + "шестнадцать ";   break;
                 case 7: R = R + "семнадцать ";    break;
                 case 8: R = R + "восемнадцать ";  break;
                 case 9: R = R + "девятнадцать ";  break;
              }
              I3 = 0;
              break;
      case 2: R = R + "двадцать ";     break;
      case 3: R = R + "тридцать ";     break;
      case 4: R = R + "сорок ";        break;
      case 5: R = R + "пятьдесят ";    break;
      case 6: R = R + "шестьдесят ";   break;
      case 7: R = R + "семьдесят ";    break;
      case 8: R = R + "восемьдесят ";  break;
      case 9: R = R + "девяносто ";    break;
   }
   EA = E3;
   switch (I3) {
      case 1: R = R + ((N == 2) ? AnsiString("одна "): AnsiString("один "));   EA = E1; break;
      case 2: R = R + ((N == 2) ? AnsiString("две ") : AnsiString("два "));    EA = E2; break;
      case 3: R = R + "три ";    EA = E2; break;
      case 4: R = R + "четыре "; EA = E2; break;
      case 5: R = R + "пять ";            break;
      case 6: R = R + "шесть ";           break;
      case 7: R = R + "семь ";            break;
      case 8: R = R + "восемь ";          break;
      case 9: R = R + "девять ";          break;
   }
   R = R + P + EA;
   return R;
}
//---------------------------------------------------------------------------
AnsiString  __fastcall GetNumberText(AnsiString T)
{
   AnsiString R;

   if(T.SubString(1,1) == "-") T.Delete(1,1);
   if (T == "0" || T == "") return "Ноль";
   int N = 1;
   while (true) {
     int L = T.Length();
     if (L <= 3) {
        R = GetTripleTxt(T,N)+R;
        break;
     }
     else {
        AnsiString P = T.SubString(L-2,3);
        R = GetTripleTxt(P,N)+ " "+R;
        T = T.SubString(1,L-3);
     }
     N++;
   }
   R = R.SubString(1,1).UpperCase() + R.SubString(2,R.Length());
   return R;
}
//---------------------------------------------------------------------------
AnsiString  __fastcall GetMoneyText(AnsiString S,int Mode)
{
   AnsiString R,asCurrName[]={" руб. РФ "," коп."," тенге "," тиын"};
   int L = S.Length();
   if (L > 2) {
      AnsiString T = S.SubString(1,L-2);
      S = S.SubString(L-1,2);
// ---- разбор рублей ------
      R = GetNumberText(T);
   }
   else R = "0";
   R = R.Trim() + asCurrName[Mode*2];
// ---- разбор копеек ------
   L = S.Length();
   if (L == 1) R = R + "0";
   R = R + S + asCurrName[Mode*2+1];
   return R;
}
//---------------------------------------------------------------------------
AnsiString  __fastcall GetMoneyText(int X,int Mode)
{
   AnsiString S = IntToStr(X);
   return GetMoneyText(S,Mode);
}
//---------------------------------------------------------------------------
AnsiString  __fastcall GetMoneyText(double X,int Mode)
{
   AnsiString S = FloatToStrF(X*100,ffFixed,15,0);
   return GetMoneyText(S,Mode);
}
//===========================================================================
//==== Простейшие примитивы =================================================
//===========================================================================
static TRect      RcCell;
static AnsiString ErrMsg;
static AnsiString LastMsg;
//---------------------------------------------------------------------------
void __fastcall SetFormPosStd(TForm* Frm,int Width,int Height,int Left,bool SetMaxHgt)
{
   TForm* OwnerForm = dynamic_cast<TForm*>(Frm->Owner);
   int Top;
   int ScrWdt = Screen->Width;
   int ScrHgt = Screen->Height - 50; if (ScrHgt < 800) ScrHgt = 800;
   if (Height > ScrHgt) Height = ScrHgt;
   if (Width  > ScrWdt) Width  = ScrWdt;
   if (OwnerForm) {
      if (Frm->Width > OwnerForm->Width) {
         Left = OwnerForm->Left;
         Top  = OwnerForm->Top;
      }
      else {
        Left += OwnerForm->Left;
        int Rgt = OwnerForm->Left + OwnerForm->Width;
        if (Left + Width > Rgt) Left = Rgt -Width;
        Top = OwnerForm->Top;
      }
   }
   else             Top = 0;

   if (Left + Width  > ScrWdt) Left = ScrWdt - Width;
   if (Top  + Height > ScrHgt) Top  = ScrHgt - Height;
   if (Left < 0) Left = 0;
   if (SetMaxHgt) {
      if (Top + Height < ScrHgt) Height = ScrHgt - Top;
   }
   Frm->Width  = Width;
   Frm->Left   = Left;
   Frm->Top    = Top;
   Frm->Height = Height;
}
//---------------------------------------------------------------------------
void __fastcall SaveRect(const TRect &Rect)
{
   RcCell = Rect;
}
//---------------------------------------------------------------------------
void __fastcall SetGlobalErrMsg(const AnsiString& S)
{
   ErrMsg = S;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetGlobalErrMsg(bool Clear)
{
   AnsiString S = ErrMsg;
   if (Clear) ErrMsg = "";
   return S;
}
//---------------------------------------------------------------------------
void __fastcall OutGlobalErrMsg(bool Clear)
{
	OutputMessage(GetGlobalErrMsg(Clear));
}
//---------------------------------------------------------------------------
bool __fastcall IsInteger(const AnsiString& S)
{
   int IVal;
   return GetInteger(IVal,S);
}
//---------------------------------------------------------------------------
bool __fastcall GetInteger(int& X,const AnsiString& S)
{
   try         { X = StrToInt(S); }
   catch (...) { return false;    }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall InputInteger(const UnicodeString& Caption,const UnicodeString& Prompt,int& X)
{
   UnicodeString S = IntToStr(X);
   while (true) {
	  if (!InputQuery(Caption,Prompt,S)) break;
      if (GetInteger(X,S)) return true;
   }
   return false;
}

//---------------------------------------------------------------------------
bool __fastcall IsDateTime(const AnsiString& S)
{
   TDateTime DT;
   return GetDateTime(DT,S);
}
//---------------------------------------------------------------------------
bool __fastcall GetDateTime(TDateTime& DT,const AnsiString& S)
{
   try         { DT = TDateTime(S); }
   catch (...) {
       return false;
   }
   return true;
}
//---------------------------------------------------------------------------
int __fastcall GetMinutes(TDateTime DT)
{
   unsigned short H,M,S,mS;
   DT.DecodeTime(&H,&M,&S,&mS);
   int Res = H*60+M;
   return Res;
}
//---------------------------------------------------------------------------
double __fastcall RoundDbl(double X)
{
  double Y =  floorl(X);
  return (X >0) ? (( X - Y <  0.5) ? Y : Y+1) :
                  (( X - Y <= 0.5) ? Y : Y+1);
}
//---------------------------------------------------------------------------
int __fastcall GetComponentTag(TObject* Sender)
{
   int Tag = 0;
   TComponent* Comp = dynamic_cast<TComponent*>(Sender);
   if (Comp) Tag = Comp->Tag;
   return Tag;
}
//---------------------------------------------------------------------------
void __fastcall OutputMessage(const AnsiString& Msg,bool SavMsg)
{
   ShowMessage(Msg);
   if (SavMsg) LastMsg = Msg;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetRangeStr(int WrkSrvID,const AnsiString& Fld)
{
   int REnd = WrkSrvID*100000000;
   int RBeg = REnd - 100000000;
   AnsiString S = Fld + " > " + IntToStr(RBeg) + " and " + Fld + " < " + IntToStr(REnd);
   return S;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetStatusStr(const AnsiString& Fld)
{
   AnsiString S = " (" +Fld + " is null or " + Fld + " >=0) ";
   return S;
}
//---------------------------------------------------------------------------
bool __fastcall RowIsDeleted(TDataSet *DataSet)
{
   TField* Fld = DataSet->FindField("STATUS");
   if (Fld)
      if (Fld->AsInteger < 0) return true;
   return false;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetDateStr(TDateTime DT,bool Add)
{
   AnsiString S = DT.FormatString("dd.mm.yy");
   if (Add) S = "'" + S + "'";
   return S;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetDateStr(TDataSet* DSet,AnsiString const& FName)
{
   return DSet->FieldByName(FName)->AsDateTime.FormatString("dd.mm.yy");
}
//---------------------------------------------------------------------------
int __fastcall GetComboIndex(int Value)
{
   int Ret = 0;
   if (Value) {
      Ret = 1;
      while (!(Value& 1)) {
         Value >>= 1;
         ++Ret;
      }
   }
   return Ret;
}
//===========================================================================
//==== Работа с кусками строк ===============================================
//===========================================================================
AnsiString __fastcall SetPiece(AnsiString Src,const AnsiString& Piece,const AnsiString& Dlm,int N)
{
   if (N <=0) return Src;
   AnsiString Res,Add;
   bool bFind = false;
   int Cnt    = 1;
   int DLen   = Dlm.Length();
   while (true) {
      int Pos = Src.Pos(Dlm);
      if (Pos) {
         Add = Src.SubString(1,Pos-1);
         Src = Src.SubString(Pos+DLen,Src.Length());
      }
      else {
         Add = Src;
         Src = "";
      }
      if (Cnt == N) {
         bFind = true;
         Add   = Piece;
      }
      Cnt++;
      Res = Res + Dlm +Add;
      if (bFind && !Pos) break;
   }
   Res = Res.SubString(Dlm.Length()+1,Res.Length());
   return Res;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetPiece(AnsiString Src,const AnsiString& Dlm,int N)
{
   AnsiString Res;
   int DLen = Dlm.Length();
   if (N*DLen <= 0) return Res;
   N--;
   while (N > 0) {
      int Pos = Src.Pos(Dlm);
      if (Pos) {
         Src = Src.SubString(Pos+DLen,Src.Length()); N--;
      }
      else {
         return Res;
      }
   }
   int Pos = Src.Pos(Dlm);
   if (Pos) Res = Src.SubString(1,Pos-1);
   else     Res = Src;
   return Res;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetSegment(AnsiString Src,const AnsiString& Dlm, int NBeg, int NEnd)
{
   AnsiString Res;
   int DLen = Dlm.Length();
   if (DLen <= 0 || NBeg <= 0 || NEnd <= 0 || NBeg > NEnd) return Res;
   for (int i=1; i<=NEnd; i++) {
      int Pos = Src.Pos(Dlm);
      if (Pos) {
         if (i >= NBeg) {
            Res = Res + Dlm + Src.SubString(1,Pos-1);
         }
         Src = Src.SubString(Pos+DLen,Src.Length());
      }
      else {
         if (i >= NBeg)
            Res = Res + Dlm + Src;
         Src = "";
      }
   }
   Res = Res.SubString(Dlm.Length()+1,Res.Length());
   return Res;
}
//---------------------------------------------------------------------------
AnsiString __fastcall MakeFIO(AnsiString S)
{
   int i = 0;
   AnsiString S1,Res;
   S = S.Trim();
   while (true) {
      S1 = GetPiece(S," ",++i);
      if (S1 == "") break;
      S1 =S1.SubString(1,1).UpperCase()+S1.SubString(2,S1.Length()).LowerCase();
      Res = SetPiece(Res,S1," ",i);
   }
   return Res;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetLatinText(const AnsiString& Text)
{
   AnsiString Out,S;
   AnsiString Eng = "qwertyuiop[]asdfghjkl;'zxcvbnm,.QWERTYUIOP[]ASDFGHJKL;'ZXCVBNM,.";
   AnsiString Rus = "йцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";

   int Len = Text.Length();
   for (int i=0; i<Len; i++) {
      S = Text.SubString(i+1,1);
      int Pos = Rus.Pos(S);
      if (Pos != 0)     Out = Out + Eng.SubString(Pos,1);
      else              Out = Out+ S;
   }
   return Out;
}
//---------------------------------------------------------------------------
bool __fastcall CheckName(const AnsiString& Name,const AnsiString& NameFilter)
{
	if (NameFilter.Trim() == "") return true;
	int N = 0;
	AnsiString Dlm;
	if (NameFilter.Pos("|"))       Dlm = "|";
	else if (NameFilter.Pos("\\")) Dlm = "\\";
	else                           Dlm = "|";
	while (true) {
		AnsiString Filter = GetPiece(NameFilter,Dlm,++N).Trim();
		if (Filter == "") break;
		if (CheckNameOne(Name,Filter))
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall CheckNameOne(const AnsiString& Name,const AnsiString& NameFilter)
{
	if (NameFilter == "") return true;
	bool Accept = true;
	AnsiString SS  = Name.UpperCase();
	AnsiString Wrk = NameFilter.UpperCase();
	AnsiString Term;
	bool Contain = true;
	while (true) {
	  int Pos1 = Wrk.Pos(" ");
	  if (!Pos1) Term = Wrk;
	  else       Term = Wrk.SubString(1,Pos1-1);
	  if (Wrk == "") break;
	  if (Term.SubString(1,1) == "!") {
		  Contain = false;
		  Term = Term.SubString(2,Term.Length());
	  }
	  else Contain = true;
	  int Len = Wrk.Length();
	  Wrk = Wrk.SubString(Pos1+1,Len);
	  if (!SS.Pos(Term)) Accept = false;
	  if (!Contain) Accept = !Accept;
	  if (!Pos1 || !Accept) break;
	}
	return Accept;
}
//---------------------------------------------------------------------------
void __fastcall RemoveReturn(AnsiString& S)
{
   while (true) {
      int PosBeg = S.Pos("\r\n");
      if (!PosBeg) break;
      AnsiString B = S.SubString(1,PosBeg-1);
      int L = S.Length();
      AnsiString E = S.SubString(PosBeg+2,L);
      AnsiString T = B + " " + E;
      S = T;
   }
}
//---------------------------------------------------------------------------
bool __fastcall FindDoubleReturn(TMemo* Memo)
{
   int PosBeg = Memo->Text.Pos("\r\n\r\n");
   if (PosBeg > 0) {
      AnsiString B = Memo->Text.SubString(1,PosBeg-1);
      int L = Memo->Text.Length();
      AnsiString E = Memo->Text.SubString(PosBeg+4,L);
      AnsiString T = B + E;
      Memo->Text = T;
      return true;
   }
   return false;
}
//===========================================================================
//==== Работа с базой данных ================================================
//===========================================================================
bool __fastcall OpenDB(TDatabase* DB,bool Out)
{
   try                     { DB->Connected = true; }
   catch (Exception &E)    {
     AnsiString S = "Ошибка при открытии БД "+ DB->AliasName + "\n"+E.Message;
     SetGlobalErrMsg(S);
     if (Out) ShowMessage(S);
     return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall StartTransactionEx(TDatabase* DB)
{
   bool bRes = true;
   if (!DB->InTransaction) bRes = StartTransaction(DB);
   return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall StartTransaction(TDatabase* DB)
{
   bool Res = true;
   try { DB->StartTransaction(); }
   catch(Exception &E) {
      AnsiString S = "Невозможно открыть транзакцию на сервере\n" + E.Message;
      SetGlobalErrMsg(S);
      OutputMessage(S);
      Res = false;
   }
   if (!Res) {
      if (GetGlobalErrMsg().Pos("progress") && DB->Connected) {
         try { DB->Rollback(); }
         catch (...) { return Res; }
         OutputMessage("Выполнен откат предыдущей транзакции: \n"
                       "предыдущие изменения не записаны в БД,\n"
                       "проверьте правильность ввода данных.");
      }
   }
   return Res;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetSProcParamValues(TStoredProc* SProc)
{
   AnsiString P;
   int Cnt = SProc->Params->Count;
   for (int i=0; i<Cnt ; i++) {
      TParam* Param = SProc->Params->Items[i];
      AnsiString PStr  = Param->AsString;
      if (PStr == "") PStr = "NULL";
      P = SetPiece(P,PStr," , ",i+1);
   }
   P = "("+ P +")";
   return P;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetDSetText(TQuery* DSet)
{
	AnsiString S;
	if (DSet) {
		S = DSet->SQL->Text.UpperCase();
		int Cnt = DSet->Params->Count;
		for (int i=0; i<Cnt ; i++) {
			TParam* Param = DSet->Params->Items[i];
			AnsiString PName = ":"+Param->Name.UpperCase();
			TFieldType DType = Param->DataType;
			AnsiString PStr  = Param->AsString;
			if (PStr == "") PStr = "NULL";
			int Pos = S.Pos(PName);
			if (Pos) {
				AnsiString B = S.SubString(1,Pos-1);
				AnsiString E = S.SubString(Pos+PName.Length(),1000);
				if ((DType == ftString || DType == ftDateTime) && PStr != "NULL") {
					PStr = "'" + PStr + "'";
				}
				S = B + PStr + E;
         }
      }
   }
   return S;
}
//---------------------------------------------------------------------------
bool __fastcall ExecuteProcStd(TStoredProc* SProc,TDatabase* DB)
{
   try {
      SProc->ExecProc();
   }
   catch (Exception &E) {
      if (DB->InTransaction) DB->Rollback();
      AnsiString S = "Ошибка записи в базу процедурой - "+SProc->StoredProcName+"\n" +
                     GetSProcParamValues (SProc) +E.Message;
      SetGlobalErrMsg(S);
      OutputMessage(S);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall OpenDSetStd(TDataSet* DSet)
{
   bool bRes = DSet->Active;
   if (!bRes) {
      try {
         DSet->Open();
      }
		catch (Exception &E) {
         DSet->Active = false;
         AnsiString S = "Невозможно открыть набор данных\n"+ GetDSetText(dynamic_cast<TQuery*>(DSet))+"\n"+E.Message;
         SetGlobalErrMsg(S);
			OutputMessage(S);
			UnicodeString NewVal = S;
			if (Debug)
   			InputQuery("??",_TEXT("Задайте список текстовых подстрок через пробелы"),NewVal);

      }
      bRes = DSet->Active;
   }
   return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall ReOpenDSetStd(TDataSet* DSet)
{
   if (DSet->Active) DSet->Close();
   return OpenDSetStd(DSet);
}
//---------------------------------------------------------------------------
bool __fastcall ExecuteQry(const AnsiString& SQL,TDatabase* DB,bool Out)
{
   TQuery* Qry = new TQuery(Application);
   Qry->DatabaseName = DB->DatabaseName;
   Qry->SQL->Add(SQL);
   Qry->Prepare();
   bool bRes = ExecuteQry(Qry,Out);
   return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall ExecuteQry(TQuery* Qry,bool Out)
{
   try {
      Qry->ExecSQL();
   }
   catch (Exception &E) {
      AnsiString S = "Невозможно выполнить команду SQL:\n"+ GetDSetText(Qry) +"\n"+E.Message;
      SetGlobalErrMsg(S);
      if (Out) {
        OutputMessage(S);
      }
      delete Qry;
      return false;
   }
   delete Qry;
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall OpenTmpQuery(const AnsiString& SQL,TParams*& Result,TDatabase* DB)
{
  TQuery* Qry = new TQuery(Application);
  Qry->DatabaseName = DB->DatabaseName;
  Qry->SQL->Text = SQL;
  if (OpenDSetStd(Qry)) {
     GetTmpQueryParamsResult(Qry,Result);
  }
  Qry->Active = false;
  delete Qry;
  return (Result && Result->Count > 0);
}
//---------------------------------------------------------------------------
void __fastcall GetTmpQueryParamsResult(TDataSet* Qry,TParams*& Result)
{
	if (!Result) Result = new TParams();
	AnsiString FName;
	AnsiString Text = Qry->FieldList->Text;
	TFieldList* FList = Qry->FieldList;
	for (int i=0; i<FList->Count; i++) {
		TField* Fld = FList->Fields[i];
		FName = Fld->FieldName;
		TFieldType FldType = ftUnknown;
		switch (Fld->DataType) {
			case ftString:    FldType = ftString;
									break;
			case ftSmallint:
			case ftInteger:
			case ftWord:      FldType = ftInteger;
									break;
			case ftDateTime:  FldType = ftDateTime;
									break;
		}
		if (FldType != ftUnknown) {
			Result->CreateParam(FldType,FName,ptInput);
			Result->ParamValues[FName] = Qry->FieldByName(FName)->Value;
		}
		else
		  OutputMessage("Err");
  }
}
//---------------------------------------------------------------------------
bool __fastcall OpenTmpQuery(const AnsiString& SQL,const AnsiString& FNames,std::map<AnsiString,Variant>& Result,TDatabase* DB)
{
   TQuery* Qry = new TQuery(Application);
   Qry->DatabaseName = DB->DatabaseName;
   Qry->SQL->Text = SQL;
   bool bRes = false;
   if (OpenDSetStd(Qry)) {
      bRes = GetTmpQueryMapResult(Qry,FNames,Result);
   }
   Qry->Active = false;
   delete Qry;
	return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall GetTmpQueryMapResult(TDataSet* Qry,const AnsiString& FNames,std::map<AnsiString,Variant>& Result)
{
   AnsiString S;
   int i=0;
   bool bRes = true;
   while (++i) {
      S = GetPiece(FNames,";",i);
      if (S == "") break;
      if (!Qry->FindField(S)) {
         bRes = false;
         break;
      }
      Variant V = Qry->FieldByName(S)->AsVariant;
      Result.insert(pair<AnsiString,Variant>(S,V));
   }
   return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall OpenTmpQuery(const AnsiString& SQL,const AnsiString& FName,Variant& Result,TDatabase* DB)
{
  TQuery* Qry = new TQuery(Application);
  Qry->DatabaseName = DB->DatabaseName;
  Qry->SQL->Text = SQL;
  bool bRes = false;
  if (OpenDSetStd(Qry)) {
     if (Qry->FindField(FName)) {
        bRes = true;
        Result = Qry->FieldByName(FName)->AsVariant;
     }
  }
  Qry->Active = false;
  delete Qry;
  return bRes;
}

//---------------------------------------------------------------------------
bool __fastcall Trunc(TDataSet* DSet, TCustomEdit* Edit,const AnsiString& FieldName)
{
   AnsiString S = Edit->Text;
   bool bRes = Trunc(DSet,FieldName,S);
   Edit->Text  = S;
   return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall Trunc(TDataSet* DSet, const AnsiString& FieldName, AnsiString& S)
{
   int Size = DSet->FieldByName(FieldName)->Size;
   S = S.Trim();
   while (true) {
      int Pos = S.Pos("  ");
      if (!Pos) break;
      S =S.SubString(1,Pos-1)+ S.SubString(Pos+1,S.Length());
   }
   if (S.Length() > Size) S = S.SubString(1,Size);
   return (DSet->FieldByName(FieldName)->AsString != S);
}
//---------------------------------------------------------------------------
void __fastcall Trunc(AnsiString& S,int Size)
{
   S = S.Trim();
   while (true) {
      int Pos = S.Pos("  ");
      if (!Pos) break;
      S =S.SubString(1,Pos-1)+ S.SubString(Pos+1,S.Length());
   }
   if (S.Length() > Size) S = S.SubString(1,Size);
}
//---------------------------------------------------------------------------
void __fastcall ClearSProcParam(TStoredProc* SProc)
{
   if (!SProc->Prepared) SProc->Prepare();
   int NPar = SProc->Params->Count;
   for (int i=0; i<NPar; i++) {
      SProc->Params->Items[i]->Clear();
   }

}
//---------------------------------------------------------------------------
void __fastcall ClearQueryParam(TQuery* Qry)
{
	if (!Qry->Prepared) Qry->Prepare();
	int NPar = Qry->Params->Count;
	for (int i=0; i<NPar; i++) {
		Qry->Params->Items[i]->Clear();
	}
}
//---------------------------------------------------------------------------
void __fastcall PrepSProcByQry(TStoredProc* SProc,TDataSet* Qry,bool Clear)
{
	if (!SProc->Prepared) SProc->Prepare();
	int Cnt = SProc->ParamCount;
	AnsiString FName;
	for (int i=0; i< Cnt; i++) {
		FName = SProc->Params->Items[i]->Name;
		if (Qry->FindField(FName))
			SProc->ParamByName(FName)->Value = Qry->FieldByName(FName)->Value;
		else {
			if (Clear) SProc->ParamByName(FName)->Clear();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall SetParamsType(TParams* Params,TDataSet* Qry)
{
	int Cnt = Params->Count;
	AnsiString FName;
	for (int i=0; i< Cnt; i++) {
		TParam* Param = Params->Items[i];
		Param->ParamType = ptInput;
		FName = Param->Name;
		if (Qry->FindField(FName)) {
			Param->DataType =  Qry->FieldByName(FName)->DataType;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall PrepQueryByQry(TQuery* TagQry,TDataSet* Qry,bool Clear)
{
	if (!TagQry->Prepared) TagQry->Prepare();
	int Cnt = TagQry->ParamCount;
	AnsiString FName;
	for (int i=0; i< Cnt; i++) {
		TParam* Param = TagQry->Params->Items[i];
		Param->ParamType = ptInput;
		FName = Param->Name;
		if (Qry->FindField(FName)) {
			Variant Value =  Qry->FieldByName(FName)->Value;
			Param->Value  =  Value;
			if (Value.IsNull())
				Param->DataType =  Qry->FieldByName(FName)->DataType;
		}
		else {
			if (Clear) TagQry->ParamByName(FName)->Clear();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall SetProcParamQry(TStoredProc* SP,TDataSet* DS,const AnsiString& Fld,int Type,bool ClearEmpty)
{
	int        IVal;
	AnsiString SVal;
	if (DS->FieldByName(Fld)->IsNull && ClearEmpty) Type = 0;
   switch (Type) {
      case 0: SP->ParamByName(Fld)->Clear();
              break;
      case 1: IVal = DS->FieldByName(Fld)->AsInteger;
              if (!IVal && ClearEmpty) SP->ParamByName(Fld)->Clear();
              else                     SP->ParamByName(Fld)->AsInteger = IVal;
              break;
      case 2: SVal = DS->FieldByName(Fld)->AsString;
              if (SVal == "" && ClearEmpty) SP->ParamByName(Fld)->Clear();
              else                          SP->ParamByName(Fld)->AsString = SVal;
              break;
      case 3: SP->ParamByName(Fld)->AsDateTime = DS->FieldByName(Fld)->AsDateTime;
              break;
      case 4: SP->ParamByName(Fld)->AsFloat = DS->FieldByName(Fld)->AsFloat;
              break;
   }
}
//---------------------------------------------------------------------------
void __fastcall SetProcParamVal(TStoredProc* SP,Variant Value,const AnsiString& Fld,int Type,bool ClearEmpty)
{
   if (Value.IsNull() && ClearEmpty) Type = 0;
   switch (Type) {
      case 0: SP->ParamByName(Fld)->Clear();
              break;
      case 1: SP->ParamByName(Fld)->AsInteger  = Value;
              break;
      case 2: if (ClearEmpty && Value == AnsiString("")) SP->ParamByName(Fld)->Clear();
              else                                       SP->ParamByName(Fld)->AsString   = Value;
              break;
      case 3: SP->ParamByName(Fld)->AsDateTime = Value;
              break;
      case 4: if (ClearEmpty && Value == 0) SP->ParamByName(Fld)->Clear();
              else                          SP->ParamByName(Fld)->AsFloat    = Value;
              break;
   }
}
//---------------------------------------------------------------------------
void __fastcall SetDSetParamQry(TQuery* SP,TDataSet* DS,const AnsiString& Fld,int Type,bool ClearEmpty)
{
   int        IVal;
   AnsiString SVal;
   if (DS->FieldByName(Fld)->IsNull && ClearEmpty) Type = 0;
   switch (Type) {
	  case 0: SP->ParamByName(Fld)->Clear();
			  break;
	  case 1: IVal = DS->FieldByName(Fld)->AsInteger;
			  if (!IVal && ClearEmpty) SP->ParamByName(Fld)->Clear();
			  else                     SP->ParamByName(Fld)->AsInteger = IVal;
			  break;
	  case 2: SVal = DS->FieldByName(Fld)->AsString;
			  if (SVal == "" && ClearEmpty) SP->ParamByName(Fld)->Clear();
			  else                          SP->ParamByName(Fld)->AsString = SVal;
			  break;
	  case 3: SP->ParamByName(Fld)->AsDateTime = DS->FieldByName(Fld)->AsDateTime;
			  break;
	  case 4: SP->ParamByName(Fld)->AsFloat = DS->FieldByName(Fld)->AsFloat;
			  break;
   }
}
//---------------------------------------------------------------------------
void __fastcall SetDSetParamVal(TQuery* SP,Variant Value,const AnsiString& Fld,int Type,bool ClearEmpty)
{
   if (Value.IsNull() && ClearEmpty) Type = 0;
   switch (Type) {
	  case 0: SP->ParamByName(Fld)->Clear();
			  break;
	  case 1: SP->ParamByName(Fld)->AsInteger  = Value;
			  break;
	  case 2: if (ClearEmpty && Value == AnsiString("")) SP->ParamByName(Fld)->Clear();
			  else                                       SP->ParamByName(Fld)->AsString   = Value;
			  break;
	  case 3: SP->ParamByName(Fld)->AsDateTime = Value;
			  break;
	  case 4: if (ClearEmpty && Value == 0) SP->ParamByName(Fld)->Clear();
			  else                          SP->ParamByName(Fld)->AsFloat    = Value;
			  break;
   }
}
//===========================================================================
//==== Работа с таблицами ===================================================
//===========================================================================
void __fastcall NumerateGridFields(TDBGridEh* Grid, bool Out)
{
   AnsiString S;
   int Cnt = Grid->Columns->Count;
   for (int i=0; i<Cnt; i++) {
      TField* F = Grid->Columns->Items[i]->Field;
      if (F != NULL) {
         S = Grid->Columns->Items[i]->Field->FieldName;
         Grid->Columns->Items[i]->Tag = i+1;
         F->Tag = i+1;
      }
      else {
         Grid->Columns->Items[i]->Tag = i+1;
			if (Out)
            OutputMessage("В столбце N = "+ IntToStr(i) + " нет поля из набора данных " + Grid->DataSource->DataSet->Name);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall SwitchGridOption(TDBGridEh* Grid,bool New,Dbgrideh::TDBGridOption Opt)
{
   bool Old = Grid->Options.Contains(Opt);
   if (Old != New) {
      if (New) Grid->Options = Grid->Options << Opt;
      else     Grid->Options = Grid->Options >> Opt;
//      if (Grid->OptionsEh.Contains(Dbgrideh::dghHighlightFocus))
//         Grid->OptionsEh = Grid->OptionsEh >> Dbgrideh::dghHighlightFocus;
      Grid->Repaint();
   }
}
//---------------------------------------------------------------------------
void __fastcall SwitchGridOptionEh(TDBGridEh* Grid,bool New,Dbgrideh::TDBGridEhOption Opt)
{
   bool Old = Grid->OptionsEh.Contains(Opt);
   if (Old != New) {
      if (New) Grid->OptionsEh = Grid->OptionsEh << Opt;
      else     Grid->OptionsEh = Grid->OptionsEh >> Opt;
      Grid->Repaint();
   }
}
//---------------------------------------------------------------------------
void __fastcall PutEditOnGrid(TWinControl* Grid,TWinControl* Edit,bool SetWidth)
{
   Edit->Parent = Grid->Parent;
   Edit->Left   = RcCell.Left+1 + Grid->Left;
   Edit->Top    = RcCell.Top+1  + Grid->Top;
   if (SetWidth) Edit->Width  = RcCell.Right  - RcCell.Left + 1;
   Edit->Height = RcCell.Bottom - RcCell.Top  + 1;
   Edit->Enabled = true;
   Edit->Visible = true;
   Edit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall ShowPanel(TDBGridEh* Grid,TPanel* Panel,TWinControl** WinLst,int NumCol)
{
   Panel->Parent = Grid;
   int L[100],W[100];
   if (!NumCol)
      NumCol  = Grid->Columns->Count;
   int X       = Grid->Left;
   int RowHeight   = RcCell.Bottom - RcCell.Top  + 1;
   Panel->Height   = RowHeight+1;
   for (int i=0; i<NumCol; i++) {
      W[i] = Grid->Columns->Items[i]->Width+1;
      L[i] = X;
      X = X + W[i];
      WinLst[i]->Top = 0;       WinLst[i]->Left   = L[i];
      WinLst[i]->Width = W[i];  WinLst[i]->Height = RowHeight;
   }
   Panel->Left     = Grid->Left + 13;
   Panel->Top      = RcCell.Top;
   int PanelRgt    = X + 13;
   Panel->Width    = PanelRgt - Panel->Left;

   Panel->Enabled  = true;
   Panel->Visible  = true;

}
//---------------------------------------------------------------------------
// ==== Status Bar and SelArray =============================================
//---------------------------------------------------------------------------
// ==== Внутренняя: для расстановки падежей =================================

AnsiString GetMultiSelStr(int Size)
{
   AnsiString S1,S2,S;
   if (Size) {
      S1 = "о ";
      switch(Size%10) {
         case 1: S1 = "а "; S2 = "а"; break;
         case 2:
         case 3:
         case 4: S2 = "и"; break;
      }
      S = "Выбран" + S1 + IntToStr(Size) + " строк" + S2 +".";
   }
   return S;
}
// ==== печать массива выбранных строк =======================================
AnsiString __fastcall PrintSelArray(GridData& GData)
{
   int Size = GData.SelArray.size();
   AnsiString S;
   if (Size) {
      std::vector<GridKeyValue>::iterator IterBeg = GData.SelArray.begin();
      std::vector<GridKeyValue>::iterator IterEnd = GData.SelArray.end();
      int I=0;
      for (std::vector<GridKeyValue>::iterator iter = IterBeg; iter < IterEnd; iter++) {
         I++;
         GridKeyValue pGKV = (*iter);
         Variant V = pGKV.Value();
         if (V.IsArray()) {
            S = "";
            int E = V.ArrayHighBound();
            for (int i=0; i<=E; i++) {
               S = S + V.GetElement(i) + " ";
            }
            S = IntToStr(I)+ " " + S;
         }
         else S = S + IntToStr(I)+ " " + V + " ";
         S += "\n";
      }
   }
   return S;
}
// ==== Обслуживает стандартный StatusBar c 3-мя полями =====================
// ==== значения ключей,фильтр,видеть удаленные         =====================
void __fastcall SetStatusBarStd(GridData& GData)
{
   TsStatusBar* SBar = GData.WrkSBar;
   if (!SBar || !(GData.Flags & STD_STATUSBAR)) return;
   AnsiString S,P;
   int i = 1;
   while(true) {
      P = GetPiece(GData.FieldKey,";",i);
		if (P == "") break;
		AnsiString XS = GData.WrkDSet->FieldByName(P)->AsString;
		S = SetPiece(S,GData.WrkDSet->FieldByName(P)->AsString,";",i);
      i++;
   }
   SBar->Panels->Items[0]->Text = S;
   S = "";
   if (GData.ParentGData) {
      if (GData.ParentGData->Filter != "")
         S + "Фильтр: " + GData.ParentGData->Filter;
   }
   if (GData.Filter != "") {
      if (S != "") S = S + "  -> ";
      S = S + "Фильтр: "+GData.Filter;
   }
   SBar->Panels->Items[1]->Text = S;
   S = "";
   if (GData.ParentGData) {
      S = GetMultiSelStr(GData.ParentGData->SelArray.size());
   }
   int Size = GData.SelArray.size();
   if (Size) {
      if (S != "") S = S + "  -> ";
      S = S + GetMultiSelStr(GData.SelArray.size());
   }
   SBar->Panels->Items[2]->Text = S;
   S = "";
   if (GData.SeeDeleted) S = "Удал";
   SBar->Panels->Items[3]->Text = S;
}
// ==== Сброс списка выбранных строк ========================================
void __fastcall ClearArrStd(GridData& GData)
{
   GData.SelArray.clear();
   GData.WrkGrid->Repaint();
   SetStatusBarStd(GData);
}
// ==== Вкл\выкл подсветку редактируемой строки =============================
// ---- если строка выбрана ранее, подсветка не сбрасывается ----------------
void __fastcall HighlightEditRow(GridData& GData,bool Highlight)
{
   if (GData.Flags & (MULTIPLE_SEL | HIGHLIGHT_EDIT_ROW)) {
      if (Highlight) {
			if (!RowIsSelectedStd(GData,true)) {
            GData.UnselLast = !(GData.Flags & SAVE_SELECTION);
         }
      }
      else {
         if (GData.UnselLast) {
           if (!GData.SelArray.empty()) {
              GData.SelArray.erase(GData.SelArray.begin());
              SetStatusBarStd(GData);
           }
           GData.UnselLast = false;
         }
      }
      GData.WrkGrid->Repaint();
   }
}
// ==========================================================================
// ==== Save & resore position in DSet ======================================
// ==========================================================================
// ---- Внутренние: закрыть, открыть child-наборы ---------------------------
void __fastcall CloseChildDSet(GridData& GData, bool SavePos = false)
{
	for (std::vector<GridData*>::iterator iter = GData.ChildGData.begin(); iter < GData.ChildGData.end(); iter++) {
		if (SavePos) SavePosStd(**iter);
		CloseChildDSet(**iter);
		(*iter)->WrkDSet->Active = false;
	}
}
void __fastcall SavePosChildDSet(GridData& GData)
{
	for (std::vector<GridData*>::iterator iter = GData.ChildGData.begin(); iter < GData.ChildGData.end(); iter++) {
		SavePosStd(**iter);
	}
}
void __fastcall OpenChildDSet(GridData& GData)
{
	for (std::vector<GridData*>::iterator iter = GData.ChildGData.begin(); iter < GData.ChildGData.end(); iter++) {
		GridData& GD = **iter;
		TDataSet* DSet = (*iter)->WrkDSet;
		OpenDSetStd(GD);
		if (!DSet->AfterOpen || GData.Flags & USE_SAVEPOSSTD)
			RestorePosStd(GD,false);
		OpenChildDSet(GD);
	}
}
//---------------------------------------------------------------------------
bool __fastcall OpenDSetStd(GridData& GData)
{
	bool bRes = true;
	TDataSet* SrcDSet = GData.SrcDSet;
	if (!SrcDSet) SrcDSet = GData.WrkDSet;
	if (SrcDSet && SrcDSet->Active == false) {
		bRes = OpenDSetStd(SrcDSet);
		if (bRes) {
			TMemTableEh* MemTbl= dynamic_cast<TMemTableEh*>(GData.WrkDSet);
			if (MemTbl) {
				if (MemTbl->DataDriver)
					MemTbl->Active = true;
				else {
					MemTbl->LoadFromDataSet(SrcDSet,-1,Memtableeh::lmCopy,false);
					SrcDSet->Active = false;  // только в этом случае
				}
			}
		}
	}
	return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall ReOpenDSetStd(GridData& GData)
{
	TDataSet*  DSet = GData.SrcDSet;
	if (DSet) DSet->Active = false;
	GData.WrkDSet->Active = false;
	if (GData.ParentGData) {
		SavePosStd(*GData.ParentGData);
		DSet = GData.ParentGData->SrcDSet;
		if (DSet) DSet->Active = false;
		GData.ParentGData->WrkDSet->Active = false;
		OpenDSetStd(*GData.ParentGData);
		if (!GData.ParentGData->WrkDSet->AfterOpen)
			RestorePosStd(*GData.ParentGData,false);
	}
	bool bRes =OpenDSetStd(GData);
   if (bRes) {
      if (!GData.WrkDSet->AfterOpen || (GData.Flags & USE_SAVEPOSSTD))
         RestorePosStd(GData,false);
   }
   return bRes;
}

// ==== Найти неудаленную строку ============================================
void __fastcall FindUndelStrStd(GridData& GData)
{
	TDataSet* WrkDSet = GData.WrkDSet;
	if (WrkDSet->FindField("STATUS")) {
		CloseChildDSet(GData);
		while (!WrkDSet->Bof && WrkDSet->FieldByName("STATUS")->AsInteger < 0)
			WrkDSet->Prior();
	}
}
// ==== Получить значения ключевых полей ====================================
bool __fastcall GetKeyValueStd(GridData& GData,GridKeyValue& KeyValue,bool ForChild)
{
	bool bRes = false;
	KeyValue.Clear();
	AnsiString FieldKey = GData.FieldKey;
	if (FieldKey != "" && GData.WrkDSet->Active) {
		int i = 1;
		int Bounds[] = {0,0};                              // lower and upper bounds
		TDataSet* DSet = GData.WrkDSet;
		Variant V = VarArrayCreate(Bounds,1,varVariant);   // create one-dim array of variants
		while (i++) {                                      // считаем количество ключевых полей
			AnsiString Fld = GetPiece(FieldKey,";",i);
			if (Fld == "") break;
		}
		switch (i) {
			case 1:                                                break;
			case 2:  // ключевое поле одно
						KeyValue = DSet->FieldByName(FieldKey)->Value;
						bRes = !KeyValue.IsNull();
						break;
			default: // ключевых полей несколько => создаем Variant array
						i = 0;
						while (++i) {
							AnsiString Fld = GetPiece(FieldKey,";",i);
							if (Fld == "") break;
							if (i > 1) VarArrayRedim(V,i-1);
							V.PutElement(DSet->FieldByName(Fld)->Value,i-1);
							if (!DSet->FieldByName(Fld)->IsNull) bRes = true;
						}
						KeyValue = V;
						break;
		}
	}
	// ---- если требуется, делаем то же самое для дочерних НД ---------------
	if (ForChild) {
		for (std::vector<GridData*>::iterator iter = GData.ChildGData.begin(); iter < GData.ChildGData.end(); iter++) {
			GridData* GDataChild = (*iter);
			GetKeyValueStd(*GDataChild,GDataChild->KeyValue);
		}
	}
	return bRes;
}
// ==========================================================================
// ==== Сохранить текущее положение НД ======================================
bool __fastcall SavePosStd(GridData& GData)
{
	if (!GData.WrkDSet->Active) return false;
	bool SaveChild = FilterRecordStd(GData); // текущая запись удовлетворяет фильтру ?
	return GetKeyValueStd(GData,GData.KeyValue,SaveChild); // если да => сохранить Child НД
}
// ==========================================================================
// ==== Восстановить текущее положение НД ===================================
bool __fastcall RestorePosStd(GridData& GData,bool RestoreChild)
{
	bool bRes = false;
	AnsiString FieldKey = GData.FieldKey;
	if (FieldKey != "") {
		Variant KeyValue = GData.KeyValue;
		TDataSet* DSet = GData.WrkDSet;
		if (!KeyValue.IsEmpty() && !KeyValue.IsNull() && DSet->Active) {
			if (KeyValue.IsArray()) {
				int H = KeyValue.ArrayHighBound(1)+1;
				FieldKey = GetSegment(FieldKey,";",1,H);
			}
			else FieldKey = GetPiece(FieldKey,";",1);
			bRes = DSet->Locate(FieldKey,KeyValue,TLocateOptions());
			SetEditSearchTxtStd(GData);
			GData.KeyValue.Clear();
		}
		else RestoreChild = false;
	}
	if (RestoreChild) {
		for (std::vector<GridData*>::iterator iter = GData.ChildGData.begin(); iter < GData.ChildGData.end(); iter++) {
			GridData* GDataChild = *iter;
			if (GDataChild->WrkDSet->Active) {
				if (bRes)  RestorePosStd(*GDataChild,true);
				else       GDataChild->KeyValue.Clear();
 			}
		}
   }
   SetStatusBarStd(GData);
   return bRes;
}
// ==== Обновить данные, взяв их из БД ======================================
void __fastcall ProcRefreshStd(GridData& GData,bool NewSQL)
{
   SavePosStd(GData);
   for (std::vector<GridData*>::iterator iter = GData.ChildGData.begin(); iter < GData.ChildGData.end(); iter++)
      (*iter)->WrkDSet->Active = false;
   TDataSet* DSet = GData.WrkDSet;
	if (GData.SrcDSet) DSet = GData.SrcDSet;
	if (NewSQL && GData.SetSQL)
      GData.SetSQL(DSet);
   if (ReOpenDSetStd(GData)) {
      OpenChildDSet(GData);
   }
}
// ==== Обновить строку =====================================================
void __fastcall RefreshRowStd(GridData& GData,TDataSet* DSet)
{
    TMemTableEh* MemTable = dynamic_cast<TMemTableEh*>(GData.WrkDSet);
    if (MemTable) {
		 TMemoryRecordEh* MemRec = MemTable->Rec;
       int Cnt = MemTable->FieldCount;
       for (int i = 0; i < Cnt; i++) {
          AnsiString FName = MemTable->Fields->Fields[i]->FieldName;
			 if (DSet->FindField(FName)) {
				 Variant V = DSet->FieldByName(FName)->Value;
				 MemRec->DataValues[FName][dvvValueEh]      = V;
          }
       }
    }
}
// --------------------------------------------------------------------
void __fastcall RefreshRowStd(GridData& GData,AnsiString SQL)
{
   TQuery* Qry = new TQuery(Application);
   TDataSet* DSet = GData.SrcDSet ? GData.SrcDSet : GData.WrkDSet;
   TQuery* QryD = dynamic_cast<TQuery*>(DSet);
   if (QryD)
		Qry->DatabaseName = QryD->DatabaseName;
	else
		Qry->DatabaseName = GData.WrkDBase->DatabaseName;

	if (SQL == "") GData.FunSetSQLOne(GData,Qry);
	else Qry->SQL->Text = SQL;

	if (Qry->SQL->Text != "" && OpenDSetStd(Qry)) {
		RefreshRowStd(GData,Qry);
		Qry->Active = false;
	}
	delete Qry;
}
// ==== Вставить строку в набор =============================================
void __fastcall InsertRowStd(GridData& GData,TDataSet* DSet)
{
    TMemTableEh* MemTable = dynamic_cast<TMemTableEh*>(GData.WrkDSet);
    if (MemTable) {
       TDataDriverEh* DDrv = MemTable->DataDriver;
       MemTable->DataDriver = NULL;
       MemTable->Insert();
       int Cnt = MemTable->FieldCount;
       for (int i = 0; i < Cnt; i++) {
          AnsiString FName = MemTable->Fields->Fields[i]->FieldName;
          if (DSet->FindField(FName)) {
             MemTable->FieldByName(FName)->Value = DSet->FieldByName(FName)->Value;
          }
       }
       MemTable->Post();
       MemTable->DataDriver = DDrv;
    }
}
void __fastcall InsertRowStd(GridData& GData,AnsiString SQL)
{
   TQuery* Qry = new TQuery(Application);
	Qry->DatabaseName = GData.WrkDBase->DatabaseName;//rQyD->DatabaseName;
	if (SQL == "") GData.FunSetSQLOne(GData,Qry);
	else Qry->SQL->Text = SQL;
	if (OpenDSetStd(Qry));
		InsertRowStd(GData,Qry);
	 Qry->Active = false;
   delete Qry;
}
// ==== Есть ли что-нибудь в НД ============================================
bool __fastcall KeyFieldIsNullStd(GridData& GData)
{
   int i = 0;
   while (++i) {
      AnsiString Fld = GetPiece(GData.FieldKey,";",i);
      if (Fld == "") break;
      if (GData.WrkDSet->FieldByName(Fld)->IsNull) return true;
   }
   return false;
}
// ==== Переустановить фильтр ==============================================
void __fastcall PulseFilterStd(GridData& GData)
{
	TDataSet* DSet = GData.WrkDSet;
	if (DSet->Active) {
		GData.WrkGrid->DataSource->Enabled = false;
		bool bRestore = true;
		if (FilterRecordStd(GData)) SavePosStd(GData);
		else {
			CloseChildDSet(GData);
			int N = 0;
			bRestore = false;
			while (!DSet->Bof && N < 40) {
				DSet->Prior(); N++;
				if (FilterRecordStd(GData)) {
					SavePosStd(GData);
					bRestore = true;
					break;
				}
			}
		}
		bool FilterByName = GData.EditSearch && (GData.Flags & FILTER_BY_NAME);
		if (FilterByName) GData.Flags &= ~FILTER_BY_NAME;
		GData.WrkDSet->Filtered = false;
		GData.WrkDSet->Filtered = true;
		GData.SearchTxt = "";
		if (bRestore) RestorePosStd(GData,false);
		SetStatusBarStd(GData);
		if (FilterByName) GData.Flags |= FILTER_BY_NAME;
		GData.WrkGrid->DataSource->Enabled = true;
	}
}
//---------------------------------------------------------------------------
// ==== EditSearch handlers =================================================
//---------------------------------------------------------------------------
void __fastcall SetEditSearchTxtStd(GridData& GData)
{
   TEdit* EditSearch = GData.EditSearch;
   if (EditSearch) {
      TNotifyEvent OnChange = EditSearch->OnChange;
      EditSearch->OnChange = NULL;
      if (GData.WrkDSet->Active && GData.FieldOut != "")
         EditSearch->Text = GData.WrkDSet->FieldByName(GData.FieldOut)->AsString;
      EditSearch->OnChange = OnChange;
   }
}
//---------------------------------------------------------------------------
void __fastcall EditSearchChangeStd(GridData& GData)
{
   TEdit* EditSearch = GData.EditSearch;
   if (!EditSearch && !EditSearch->Focused()) return;
   TNotifyEvent EditSearchChange = EditSearch->OnChange;
   EditSearch->OnChange = NULL;
   bool bFind = false;
   if (EditSearch->Text != "") {
      if (GData.FieldOut != "") {
         if (GData.Flags & FILTER_BY_NAME) {
            GData.WrkDSet->Filtered = false;
            GData.WrkDSet->Filtered = true;
         }
         bFind = GData.WrkDSet->Locate(GData.FieldOut,EditSearch->Text,
                        TLocateOptions()<< loPartialKey << loCaseInsensitive);
      }
   }
   else {
      GData.WrkDSet->Filtered = false;
      GData.WrkDSet->Filtered = true;
   }
   if (bFind)
       RepaintNewKeyLine(GData);
	SwitchGridOptionEh(GData.WrkGrid,bFind,Dbgrideh::dghRowHighlight);

	EditSearch->OnChange = EditSearchChange;
}
//---------------------------------------------------------------------------
TModalResult __fastcall EditSearchKeyDownStd(GridData& GData,WORD &Key, TShiftState Shift)
{
	TModalResult ModalRes = mrNone;
	TEdit* EditSearch = GData.EditSearch;
	if (!EditSearch && !EditSearch->Focused()) return ModalRes;
	int NMove = 0;
	switch (Key) {
		case VK_ESCAPE:   if (EditSearch->Text != "") EditSearch->Text = "";
								else                        ModalRes = mrCancel;
								break;
		case VK_UP:       NMove =  -1;  break;
		case VK_DOWN:     NMove =   1;  break;
		case VK_PRIOR:    NMove = -GData.WrkGrid->VisibleRowCount;  break;
		case VK_NEXT:     NMove =  GData.WrkGrid->VisibleRowCount;  break;
		case VK_RETURN:   if (GData.WrkGrid->OptionsEh.Contains(Dbgrideh::dghRowHighlight)) {
									if (!KeyFieldIsNullStd(GData) && !RowIsDeleted(GData.WrkDSet))
										 ModalRes = mrOk;
								}
								else {
									AnsiString FldOut = GData.FieldOut;
									if (FldOut != "")
										 if (TranslateName(GData,FldOut) && GData.CurFun) FldOut = "";
									if (FldOut != "" && GData.WrkDSet && (GData.WrkSProc || GData.WrkQuery) && GData.Flags & INS_IF_NOT_FOUND) {
										Trunc(GData.WrkDSet, EditSearch,FldOut);
										UnicodeString  Name = EditSearch->Text;
										if (Name != "") {
											 if (Name != GData.WrkDSet->FieldByName(FldOut)->AsString ) {
												  if (AskQuestionStd(GData,"Ввести наименование\n<" + Name + "> ?"))
													  ProcInsertStd(GData,Name);
												  break;
											 }
											 ModalRes = mrOk;
										}
                           }
                        }
                        break;
      case VK_END:      if (Shift.Contains(ssCtrl)) {
                           bool FilterByName = GData.EditSearch && (GData.Flags & FILTER_BY_NAME);
                           if (FilterByName) GData.Flags &= ~FILTER_BY_NAME;
                           GData.WrkDSet->Last();
                           SetEditSearchTxtStd(GData);
                           SwitchGridOptionEh(GData.WrkGrid,true,Dbgrideh::dghRowHighlight);
                           EditSearch->SelectAll();
                           if (FilterByName) GData.Flags |= FILTER_BY_NAME;
                        }
                        break;
      case VK_HOME:     if (Shift.Contains(ssCtrl)) {
                           bool FilterByName = GData.EditSearch && (GData.Flags & FILTER_BY_NAME);
                           if (FilterByName) GData.Flags &= ~FILTER_BY_NAME;
                           GData.WrkDSet->First();
                           SetEditSearchTxtStd(GData);
                           SwitchGridOptionEh(GData.WrkGrid,true,Dbgrideh::dghRowHighlight);
                           EditSearch->SelectAll();
                           if (FilterByName) GData.Flags |= FILTER_BY_NAME;
                        }
                        break;
   }
   if (!NMove) return ModalRes;
   SwitchGridOptionEh(GData.WrkGrid,true,Dbgrideh::dghRowHighlight);

   for (int i=0; i<NMove; i++)
      GData.WrkDSet->Next();
   for (int i=NMove; i<0; i++)
      GData.WrkDSet->Prior();
   SetEditSearchTxtStd(GData);
   EditSearch->SelectAll();
   return ModalRes;
}
//---------------------------------------------------------------------------
void __fastcall EditSearchKeyUpStd(GridData& GData,WORD &Key, TShiftState Shift)
{
   TEdit* EditSearch = GData.EditSearch;
   if (!EditSearch && !EditSearch->Focused()) return;
   switch (Key) {
      case VK_NEXT:
      case VK_PRIOR:
      case VK_DOWN:
      case VK_UP:     EditSearch->SelectAll();
   }
}
//---------------------------------------------------------------------------
// ==== Misc routines =======================================================
//---------------------------------------------------------------------------
AnsiString __fastcall GetFieldOutTitleStd(GridData& GData)
{
   AnsiString SS = GetFieldOutTitleStd(GData,GData.FieldOut);
   if (SS == "") SS = "Наименование:";
   return SS;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetFieldOutTitleStd(GridData& GData,AnsiString FieldOut)
{
   TDBGridEh* Grid     = GData.WrkGrid;
   AnsiString SS;
   FieldOut = FieldOut.UpperCase();
   if (Grid && FieldOut != "") {
      for (int i=0; i<Grid->Columns->Count; i++) {
          if (Grid->Columns->Items[i]->FieldName.UpperCase() == FieldOut) {
              SS = Grid->Columns->Items[i]->Title->Caption;
              break;
          }
      }
   }
   return SS;
}
//---------------------------------------------------------------------------
bool __fastcall EditIsAllowedStd(GridData& GData, bool CheckSpace,bool CheckField)
{
   int CurSrvID;
   TStoredProc* SP = GData.WrkSProc;
   TQuery*      Qr = GData.WrkQuery;
   if ( (!SP || SP->StoredProcName == "") &&
        (!Qr || Qr->SQL->Text      == ""))
      return false;
   if (GData.FunCanEdit && !GData.FunCanEdit(GData,CheckField))
      return false;
   if (GData.GetCurSrvID(CurSrvID) && CheckSpace && !(GData.Flags & DONT_CHECK_KEY_ID)) {
      if (!KeyFieldIsNullStd(GData)) {
         int i = 0;
         while (++i) {
            AnsiString Fld = GetPiece(GData.FieldKey,";",i).UpperCase();
            if (Fld == "") break;
            if (Fld.Pos("_ID") == Fld.Length()-2) {
               if (GData.WrkDSet->FieldByName(Fld)->DataType == ftInteger) {
                  int ID = GData.WrkDSet->FieldByName(Fld)->AsInteger;
                  int SrvID = ID/100000000 + 1;
                  if (SrvID != CurSrvID) return false;
               }
            }
         }
      }
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall EditIsAllowedStdEx(GridData& GData)
{
   bool bRes;
   WORD Key = GData.CurKeyPressed;
   switch (Key) {
        case VK_INSERT: bRes = EditIsAllowedStd(GData,true,false);
                        break;
        case VK_F9:
        case VK_RETURN:
        case VK_BACK:
        case VK_DELETE: bRes = !KeyFieldIsNullStd(GData) && (RowIsDeleted(GData.WrkDSet) == (Key == VK_F9)) &&
                                EditIsAllowedStd(GData,true,(Key == VK_RETURN || Key == VK_BACK));
                        break;
        default:        if (GData.ActionTag)
                           bRes = !KeyFieldIsNullStd(GData) && !RowIsDeleted(GData.WrkDSet) &&
                                  EditIsAllowedStd(GData,true,false);
                        else
                           bRes = !KeyFieldIsNullStd(GData) && !RowIsDeleted(GData.WrkDSet) &&
                                  EditIsAllowedStd(GData,true,true);

   }
   GData.CurEditAllowed = bRes; // для передачи наверх
   return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall ProcKeyIsAllowed(GridData& GData)
{
   bool bRes;
   WORD Key = GData.CurKeyPressed;
   int Size = GData.SelArray.size();
   switch (Key) {
        case VK_INSERT: bRes = EditIsAllowedStd(GData,true,false);
                        break;
        case VK_F9:
        case VK_RETURN:
        case VK_BACK:
        case VK_DELETE: if (Size) {
                           if (bool(GData.State & DELETED_ARE_SELECTED) != (Key == VK_F9)) bRes = false;
                           else bRes = EditIsAllowedStd(GData,true,(Key == VK_RETURN || Key == VK_BACK));
                        }
                        else {
                           bRes = !KeyFieldIsNullStd(GData) && (RowIsDeleted(GData.WrkDSet) == (Key == VK_F9)) &&
                                   EditIsAllowedStd(GData,true,(Key == VK_RETURN || Key == VK_BACK));
                        }
                        break;
        default:        bRes = false;
   }
   GData.CurEditAllowed = bRes; // для передачи наверх
   return bRes;
}
//---------------------------------------------------------------------------
void __fastcall GetGridColParam(GridData& GData,bool Translate)
{
	GData.GridCol       = GData.WrkGrid->Col;
	TColumnEh* Col      = GData.WrkGrid->Columns->Items[GData.GridCol-1];
	GData.Column        = Col;
	GData.PickCnt       = Col->PickList->Count;
	GData.EditFld       = Col->Field;
	GData.EditCol       = Col->Tag;
	GData.ColCaption    = Col->Title->Caption;
	GData.CurFun        = NULL;
	GData.FieldType     = Col->Field->DataType;
	GData.DPlaces       =
	GData.ItemIndex     = 0;
	AnsiString EditFldName   = Col->Field->FieldName;
//   if (EditFldName.Pos("Out_")  == 1) EditFldName = EditFldName.SubString(5,100);
	if (Translate) {
      TranslateName(GData,EditFldName);
/*
      if (TranslateName(GData,EditFldName)) {
         TField* Fld = GData.WrkDSet->FindField(EditFldName);
         if (Fld) {
            GData.EditFld       = Col->Field;
            GData.FieldType     = Col->Field->DataType;
         }
      }
*/
   }
   if (GData.FieldType == ftFloat) {
      TFloatField* FField = dynamic_cast<TFloatField*>(Col->Field);
      if (FField) {
         AnsiString S = FField->DisplayFormat;
         if (S == "") S = Col->DisplayFormat;
         GData.DPlaces = GetPiece(S,".",2).Length();
      }
   }
   GData.EditFldName = EditFldName;
}
//---------------------------------------------------------------------------
bool  __fastcall AskQuestionStd(GridData& GData,const AnsiString& S)
{
   return (MessageDlg(S, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes);
}
//---------------------------------------------------------------------------
int  __fastcall AskQuestionStd(GridData& GData,const AnsiString& S,TMsgDlgButtons Btn)
{
   return MessageDlg(S, mtConfirmation, Btn, 0);
}
//---------------------------------------------------------------------------
bool  __fastcall AskQuestionStd(const AnsiString& S)
{
   return (MessageDlg(S, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes);
}
//---------------------------------------------------------------------------
int  __fastcall AskQuestionStd(const AnsiString& S,TMsgDlgButtons Btn)
{
   return MessageDlg(S, mtConfirmation, Btn, 0);
}
//---------------------------------------------------------------------------
bool TranslateName(GridData& GData,AnsiString& EditFldName)
{
   bool bRet = false;
	GData.CurFun        = NULL;
	if (GData.FldTranslateMap.size()) {
      std::map<AnsiString,AnsiString>::iterator iter = GData.FldTranslateMap.find(EditFldName);
      if (iter != GData.FldTranslateMap.end()) {
         EditFldName = iter->second;
         bRet = true;
         if (GData.FunGetIDMap.size()) {
            std::map<AnsiString,FunGetID>::iterator iter = GData.FunGetIDMap.find(EditFldName);
            if (iter != GData.FunGetIDMap.end()) {
               GData.CurFun = iter->second;
               GData.FieldType = ftInteger;
            }
         }
      }
   }
   return bRet;
}
//---------------------------------------------------------------------------
bool __fastcall KeysAreEqual(GridData& GData,Variant& V1,Variant V2)
{
   bool bRes =false;
   if (!V1.IsNull() & !V1.IsEmpty() && !V2.IsNull() && !V2.IsEmpty()) {
      AnsiString FieldKey = GData.FieldKey;
      int i = 1;
      while (i++) {                                      // считаем количество ключевых полей
         AnsiString Fld = GetPiece(FieldKey,";",i);
         if (Fld == "") break;
      }
      switch (i) {
         case 1:                                                break;
         case 2:  // ключевое поле одно
                  bRes = (V1 == V2);
                  break;
         default: // ключевых полей несколько => создаем Variant array
                  i = 0; bRes = true;
                  while (++i) {
                     AnsiString Fld = GetPiece(FieldKey,";",i);
                     if (Fld == "") break;
                     Variant VX = V1.GetElement(i-1);
                     Variant VY = V2.GetElement(i-1);
                     if (VX != VY) {
                        bRes = false;
                        break;
                     }
                  }
                  break;
      }
   }
   return bRes;
}
//---------------------------------------------------------------------------
void __fastcall RepaintNewKeyLine(GridData& GData)
{
   if (GData.WrkGrid->Options.Contains(Dbgrideh::dgRowSelect)) {
      Variant V  = GData.CurKeyValue;
      GetKeyValueStd(GData,GData.CurKeyValue,false);
      if (!KeysAreEqual(GData,V,GData.CurKeyValue)) {
         GData.WrkGrid->Repaint();
      }
   }
}
//---------------------------------------------------------------------------
AnsiString  __fastcall GetCurrentFieldName(GridData& GData)
{
   int Col = GData.WrkGrid->Col-1;
   return GData.WrkGrid->Columns->Items[Col]->FieldName;
}
//---------------------------------------------------------------------------
// ==== Form KeyDown handlers ================================================
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall ProcSeeSQLStd(GridData& GData, bool GetSQL)
{
	TDataSet* DSet = GData.WrkDSet;
	if (GData.SrcDSet) DSet = GData.SrcDSet;
	else {
		TMemTableEh* MemTbl = dynamic_cast<TMemTableEh*>(DSet);
		if (MemTbl) {
			TDataSetDriverEh* Drv = dynamic_cast<TDataSetDriverEh*>(MemTbl->DataDriver);
			if (Drv) DSet = Drv->ProviderDataSet;
		}
	}
	TQuery* Qry = dynamic_cast<TQuery*>(DSet);
	if (!Qry) return;
	AnsiString  S = GetDSetText(Qry);
	TRichEdit *RE = NULL;
	if (GetSQL) {
		TRichEdit *RE = new TRichEdit(GData.WrkForm);
		RE->Parent = GData.WrkGrid->Parent;
		RE->Visible = false;
		RE->Text = S;
		RE->SelectAll();
		RE->CopyToClipboard();
	}
	ShowMessage(S);
	delete RE;
}
//---------------------------------------------------------------------------
void __fastcall FormKeyDownStd(GridData& GData,WORD &Key,TShiftState Shift)
{
	 if (!(GData.State & EDIT_IN_PROGRESS)) {
		 switch (Key) {
			 case VK_F1:        ProcSeeSQLStd(GData, Shift.Contains(ssShift) || Shift.Contains(ssAlt) || Shift.Contains(ssCtrl));
									  break;
			 case VK_F3:        ProcFilterStd(GData);    	break;
			 case VK_F8:        ProcSeeDelStd(GData);    	break;
			 case VK_F12:       ProcOutputStd(GData);			break;
			 case VK_ADD:       ProcSelAllStd(GData, &Key);	break;
			 case VK_SUBTRACT:  ProcUnsAllStd(GData, &Key); break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall ProcUnsAllStd(GridData& GData, WORD* KeyPtr )
{
	 if (!GData.WrkGrid->RowDetailPanel->Visible) {
		 ClearArrStd(GData); GData.WrkGrid->Repaint();
		 GData.WrkGrid->DataSource->Enabled = false;
		 if (GData.FunAddRow) GData.FunAddRow(GData,0,true, true);
		 GData.WrkGrid->DataSource->Enabled = true;
	 }
	 if (GData.WrkGrid->RowDetailPanel->Active && KeyPtr) *KeyPtr = NULL;
}
//---------------------------------------------------------------------------
void __fastcall ProcFilterStd(GridData& GData,AnsiString Title)
{
	// определяем поле для фильтра
	if (GData.Flags & FILTER_NOT_ALLOWED) return;
	GetGridColParam(GData,false);
	if (GData.FilterFldMask[GData.EditCol-1]) {
		GData.FieldFlt = GData.EditFldName;
		Title = "Фильтр по полю '" + GData.ColCaption +"'";
	}
	else {
		if (GData.DefFieldFlt != "") GData.FieldFlt = GData.DefFieldFlt;
		else  return;
	}
	// определяем заголовок формы
	if (GData.FieldFlt == "") return;
	if (Title == "") {
		if (GData.FieldFlt == GData.DefFieldFlt && GData.DefFilterCaption != "")
			Title = GData.DefFilterCaption;
		else {
			Title  = "Фильтр по полю '" + GetFieldOutTitleStd(GData,GData.FieldFlt) + "'";
		}
	}
	if (GetFilterStr(GData.Filter,Title)) {
		PulseFilterStd(GData);
		SetEditSearchTxtStd(GData);
		if (GData.EditSearch) GData.EditSearch->SelectAll();
	}
}
//---------------------------------------------------------------------------
void __fastcall ProcSeeDelStd(GridData& GData)
{
	TDataSet* WrkDSet = GData.WrkDSet;
   if (GData.Flags & CAN_SEE_DELETED && WrkDSet && WrkDSet->FindField("STATUS")) {
      GData.SeeDeleted = !GData.SeeDeleted;
      if (!GData.SeeDeleted && RowIsDeleted(WrkDSet)) {
         FindUndelStrStd(GData);
      }
      PulseFilterStd(GData);
   }
}
//---------------------------------------------------------------------------
#include "DBGridEhImpExp.hpp"
#include <Dialogs.hpp>

void __fastcall ProcOutputStd(GridData& GData)
{
   ProcOutputStd(GData.WrkGrid);
}
void __fastcall ProcOutputStd(TDBGridEh* Grid)
{
#ifdef __Excel_2K_SRVR_h__
//   ExcelOut::WriteDataToExcelEh(GData.WrkGrid->Columns,GData.WrkDSet);
#endif
   TOpenDialog* Dlg = new TOpenDialog(NULL);
	Dlg->Filter = "Excel-files (*.xls)|*.xls|All files (*.*)|*.*";
	Dlg->FilterIndex = 1;
	if (Dlg->Execute()) {
	  AnsiString S(Dlg->FileName.c_str());
	  if (!S.Pos(".xls")) {
		  S = S + ".xls";
		}
		SaveDBGridEhToExportFile(__classid(TDBGridEhExportAsXLS),Grid,S.c_str(),false);
		ShellExecute(NULL,L"open",Dlg->FileName.w_str(),NULL,NULL,SW_SHOWDEFAULT);
	}
	delete Dlg;

}
//---------------------------------------------------------------------------
void __fastcall ProcSelAllStd(GridData& GData,WORD* Key, bool Ask)
{
	bool StartFrom1 = true;
	if (!(GData.Flags & MULTIPLE_SEL)) return;
	TDataSet* WrkDSet = GData.WrkDSet;
	if (Ask) {
		if (GData.Flags & SEL_LINES_FROM_CUR) {
//      int X = mbNoToAll;
//      int Y = mbYesToAll;
			int Ret = AskQuestionStd(GData,"Выбрать все строки -YesToAll\nначиная с текущей - NoToAll", TMsgDlgButtons() << mbCancel << mbNoToAll << mbYesToAll);
			switch (Ret) {
				case mrCancel:        return;
				case mbNoToAll+1:     StartFrom1= false;
			}
		}
		else {
			if (!AskQuestionStd(GData,"Выбрать все строки ?")) return;
		}
	}
	ClearArrStd(GData);
	GData.WrkGrid->DataSource->Enabled = false;
	if (StartFrom1) WrkDSet->First();
	do {
		if (!RowIsDeleted(WrkDSet)) {
			GridKeyValue KeyValue;
			if (GetKeyValueStd(GData,KeyValue,false)) {
				GData.SelArray.push_back(KeyValue);
				if (GData.FunAddRow) GData.FunAddRow(GData,1,false);
			}
		}
		WrkDSet->Next();
	}
	while(!WrkDSet->Eof);
	if (GData.FunAddRow) GData.FunAddRow(GData,0,true);
	GData.WrkGrid->DataSource->Enabled = true;
	SetStatusBarStd(GData);
	if (GData.WrkGrid->RowDetailPanel->Active && Key ) *Key = NULL;
}
//---------------------------------------------------------------------------
// ==== Filter record & draw colored cells handlers ============================
//---------------------------------------------------------------------------
bool __fastcall RowIsSelectedStd(GridData& GData,bool SelectIfNot)
{
//   Variant KeyValue;
    GridKeyValue KeyValue;
    if ((GData.SelArray.size() || SelectIfNot) && GetKeyValueStd(GData,KeyValue,false)) {
       if (KeyValue.IsNull() || KeyValue.IsEmpty()) {
         OutputMessage("Variant is null");
         return false;
      }
      try {
         std::vector<GridKeyValue>::iterator IterBeg = GData.SelArray.begin();
         std::vector<GridKeyValue>::iterator IterEnd = GData.SelArray.end();
			std::vector<GridKeyValue>::iterator IterFnd = find(IterBeg,IterEnd,KeyValue);
			if (IterFnd != IterEnd)
				return true;
			else if (SelectIfNot) {
				GData.SelArray.insert(IterBeg,KeyValue);
//            GData.SelArray.push_back(KeyValue);
			}
		}
		catch (...) {
			OutputMessage("Ошибка в RowIsSelected");
//         OutputMessage(IntToStr((int)KeyValue));
		}
   }
   return false;
}
//---------------------------------------------------------------------------
bool __fastcall GetFilterStr(AnsiString& Filter,AnsiString Title)
{
   bool bRes = false;
   UnicodeString OldVal = Filter;
   UnicodeString NewVal = Filter;
   if (Title == "") Title = "Установка текстового фильтра";
	if (InputQuery(Title,_TEXT("Задайте список текстовых подстрок через пробелы"),NewVal)) {
	  bRes = (OldVal.UpperCase() != NewVal.UpperCase());
	  if (bRes) Filter = NewVal;
   }
   return bRes;
}
//---------------------------------------------------------------------------
void __fastcall GetCellParamsStd(GridData& GData,TFont *AFont, TColor &Background, TGridDrawStateEh State)
{
	if (State.Contains(Gridseh::gdFocused)) {
		Background   = clRed;
		AFont->Color = clWhite;
	}
	else {
		if (RowIsSelectedStd(GData)) {
			AFont->Color = clRed;
		}
		if (GData.WrkGrid->OptionsEh.Contains(Dbgrideh::dghRowHighlight) ){
			if (GData.WrkGrid->Options.Contains(Dbgrideh::dgRowSelect)) {
				GridKeyValue KeyValue;
				GetKeyValueStd(GData,KeyValue,false);
				Variant KeyValueF = GData.CurKeyValue;
				if (KeysAreEqual(GData,KeyValueF,KeyValue)) {
					Background   = clRed;
					AFont->Color = clWhite;
				}
			}
			if (State.Contains(Gridseh::gdSelected)) {
				Background   = clRed;
				AFont->Color = clWhite;
			}
		}
		if (RowIsDeleted(GData.WrkDSet)) {
			if (AFont->Color == clRed) AFont->Color = TColor(RGB(255, 165, 0));
			else                       AFont->Color = clGray;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall GetCellParamsStd(TDBGridEh* WrkGrid,TFont *AFont, TColor &Background, TGridDrawStateEh State)
{
	if (State.Contains(Gridseh::gdFocused)) {
		Background   = clRed;
      AFont->Color = clWhite;
   }
   else {
      if (RowIsDeleted(WrkGrid->DataSource->DataSet)) {
         if (AFont->Color == clRed) AFont->Color = TColor(RGB(0,100,0));
         else                       AFont->Color = clGray;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall DrawColumnCellStd(const TRect& Rect,TGridDrawStateEh State)
{
   if (State.Contains(Gridseh::gdFocused))
      SaveRect(Rect);
}
//---------------------------------------------------------------------------
void __fastcall DrawColumnCellStd(GridData& GData,const TRect &Rect,int DataCol,TColumnEh *Column,
      TGridDrawStateEh State)
{
   if (State.Contains(Gridseh::gdFocused))
      SaveRect(Rect);
   AnsiString FName = Column->FieldName;
   AnsiString SearchTxt = GData.SearchTxt;
   if (SearchTxt != "") {
      if (FName == GData.FieldOut || FName == GData.DefFieldFlt) {
//         Variant Key;
         GridKeyValue Key;
         GetKeyValueStd(GData,Key,false);
         if (Key == GData.SearchKey) {
            TDBGridEh* Grid = GData.WrkGrid;
            TRect R = Rect;
            int Len = SearchTxt.Length();
            AnsiString SrcTxt = GData.WrkDSet->FieldByName(FName)->AsString.SubString(1,Len);
            int W = Grid->Canvas->TextWidth(SrcTxt);
            R.right = R.left + W+3;
            Grid->Canvas->Brush->Color = clYellow;
            Grid->Canvas->FillRect(R);
            Grid->Canvas->Font->Color = clBlack;
            Grid->DefaultDrawColumnCell(R,DataCol,Column,State);
         }
      }
   }
}
//---------------------------------------------------------------------------
bool __fastcall ExternalCtrlEnterStd(GridData& GData)
{
   bool bRes = false;
   if (GData.State & SCROLL_IN_PROGRESS) {
      GData.WrkGrid->SetFocus();
      GData.State &= ~SCROLL_IN_PROGRESS;
      bRes = true;
   }
   return bRes;
}
// ==== Query event handlers ===================================================
//---------------------------------------------------------------------------
bool __fastcall FilterRecordStd(GridData& GData)
{
	bool Accept = true;
	if (GData.Filter != "" && GData.FieldFlt != "" && GData.WrkDSet->FindField(GData.FieldFlt)) {
		AnsiString SS  = GData.WrkDSet->FieldByName(GData.FieldFlt)->AsString;
		Accept = CheckName(SS,GData.Filter);
	}
	if (!GData.SeeDeleted && Accept && RowIsDeleted(GData.WrkDSet))
		Accept = false;
	if (Accept && (GData.Flags & SHOW_SELECTED))
		Accept = RowIsSelectedStd(GData);
	if (Accept && GData.FunAcceptRec)
		Accept = GData.FunAcceptRec(GData.WrkDSet);
	if (Accept && (GData.Flags & FILTER_BY_NAME)) {
		TEdit* EditSearch = GData.EditSearch;
		if (EditSearch && EditSearch->Focused() && GData.EditSearch->Text != "")
			Accept = GData.WrkDSet->FieldByName(GData.FieldOut)->AsString.UpperCase().Pos(GData.EditSearch->Text.UpperCase());
	}
//	if (!Accept && RowIsSelected(GData))
//		ProcSelectStd(GData,false);
//	}
	return Accept;
}
//---------------------------------------------------------------------------
void __fastcall AfterCloseStd(GridData& GData)
{
	if (!(GData.State & LOCATE_IN_PROGRESS) && GData.SearchTxt != "")
     GData.SearchTxt = "";
   SetStatusBarStd(GData);
}
//---------------------------------------------------------------------------
void __fastcall AfterScrollStd(GridData& GData)
{
//   int Key = GData.WrkDSet->FieldByName(GData.FieldKey)->AsInteger;
   if (!(GData.State & LOCATE_IN_PROGRESS) && GData.SearchTxt != "")
     GData.SearchTxt = "";
   SetStatusBarStd(GData);
	if (GData.State & SET_ROW_DETAIL_PANEL_VISIBLE) {
		GData.WrkGrid->RowDetailPanel->Visible = true;
      GData.State &= ~(SET_ROW_DETAIL_PANEL_VISIBLE | SCROLL_KEY_PRESSED);
   }
   RepaintNewKeyLine(GData);
}
//---------------------------------------------------------------------------
void __fastcall BeforeScrollStd(GridData& GData)
{
   if (GData.WrkGrid->RowDetailPanel->Visible)
      GData.State |= SET_ROW_DETAIL_PANEL_VISIBLE;
}
//---------------------------------------------------------------------------
void __fastcall CalcFieldsStd(GridData& GData)
{
   if (GData.CalcFields) {
      GData.CalcFields(GData.WrkDSet);
   }
}
// ===== Write routine ======================================================
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall Commit(TDatabase* DB)
{
  bool bRes = true;
  if (DB->InTransaction) {
     try { DB->Commit(); }
     catch (Exception &E) {
        AnsiString S = "Ошибка подтверждении записи в БД "+ DB->AliasName + "\nДанные будут потеряны."+E.Message;
        OutputMessage(S);
        SetGlobalErrMsg(S);
        bRes = false;
     }
  }
  return bRes;
}
bool __fastcall Rollback(TDatabase* DB)
{
  bool bRes = true;
  if (DB->InTransaction) {
     try { DB->Rollback(); }
     catch (Exception &E) {
        AnsiString S = "Ошибка подтверждении записи в БД "+ DB->AliasName + "\nДанные будут потеряны."+E.Message;
        OutputMessage(S);
        SetGlobalErrMsg(S);
        bRes = false;
     }
  }
  return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall PrepSProcStd(GridData& GData,bool Delete)
{
    TStoredProc* SProc = GData.WrkSProc;
    TDataSet* TakeDSet  = GData.SP_DSet;
    if (!TakeDSet) TakeDSet = GData.WrkDSet;
    PrepSProcByQry(SProc,TakeDSet);
    TParams* CurParams = GData.CurParams;
    bool bRet =true;
    if (CurParams) {
       SProc->Params->AssignValues(CurParams);
//       AnsiString S = GetSProcParamValues(SProc);
       if (GData.ExtParams) SProc->Params->AssignValues(GData.ExtParams);
       if (!(GData.Flags & EXEC_SP_ALWAYS) && CurParams->Count) {
          bRet = false;
          AnsiString PName;
          for (int i=0; i<CurParams->Count; i++) {
             TParam* Param = CurParams->Items[i];
				 PName = Param->Name;
				 TField* Field = TakeDSet->FindField(PName);
				 if (Field) {
					 Variant PV = Param->Value;
					 Variant FV = Field->Value;
					 if (  PV.IsEmpty() ||
						  ( PV.IsNull() && !FV.IsNull()) ||
						  (!PV.IsNull() &&  FV.IsNull()) || PV != FV) {
						 bRet = true;
						 break;
					 }
				 }
			 }
		 }
	 }
	 else
		 if (GData.ExtParams) SProc->Params->AssignValues(GData.ExtParams);

	 if (Delete) {
		 if (TakeDSet->FieldByName("Status")->AsInteger <0) bRet = false;
		 else    SetProcParamVal(SProc, -1, "Status", 1, false);
	 }
	 if (GData.ExtParams) {
		  SProc->Params->AssignValues(GData.ExtParams);
	 }
	 if (GData.FunFillSProc) bRet = GData.FunFillSProc(GData,bRet);
	 AnsiString S = GetSProcParamValues(SProc);
	 return bRet;
}
//---------------------------------------------------------------------------
bool __fastcall PrepQueryStd(GridData& GData,bool Delete)
{
	 TQuery* WrkQuery = GData.WrkQuery;
	 TDataSet* TakeDSet  = GData.SP_DSet;
	 if (!TakeDSet) TakeDSet = GData.WrkDSet;
	 WrkQuery->Active = false;
	 PrepQueryByQry(WrkQuery,TakeDSet);
//	 AnsiString S = GetDSetText(WrkQuery);
	 if (GData.ExtParams) {
/*
		int Cnt = GData.ExtParams->Count;
		for (int i=0; i < Cnt; i++) {
			TParam* Param = GData.ExtParams->Items[i];
			AnsiString PName = Param->Name;
			Variant PV       = Param->Value;
			int X = Param->ParamType;
			int Y = Param->DataType;
			int Z = 0;
		}
*/
		WrkQuery->Params->AssignValues(GData.ExtParams);
	 }
//	 S = GetDSetText(WrkQuery);
	 TParams* CurParams = GData.CurParams;
	 bool bRet =true;
	 if (CurParams) {
		 WrkQuery->Params->AssignValues(CurParams);
		 if (GData.ExtParams) WrkQuery->Params->AssignValues(GData.ExtParams);
		 if (!(GData.Flags & EXEC_SP_ALWAYS) && CurParams->Count) {
			 bRet = false;
			 AnsiString PName;
			 for (int i=0; i<CurParams->Count; i++) {
				 TParam* Param = CurParams->Items[i];
				 PName = Param->Name;
				 TField* Field = TakeDSet->FindField(PName);
				 if (Field) {
					 Variant PV = Param->Value;
					 Variant FV = Field->Value;
					 if (  PV.IsEmpty() ||
						  ( PV.IsNull() && !FV.IsNull()) ||
						  (!PV.IsNull() &&  FV.IsNull()) || PV != FV) {
						 bRet = true;
						 break;
					 }
				 }
			 }
		 }
	 }
	 AnsiString
	 S = GetDSetText(WrkQuery);
//	 ShowMessage(S);
	 if (Delete) {
		 if (TakeDSet->FindField("STATUS") && TakeDSet->FieldByName("Status")->AsInteger <0) bRet = false;
		 else {
			  if (WrkQuery->Params->FindParam("STATUS")) {
				  WrkQuery->ParamByName("STATUS")->AsInteger = -1;
				  bRet = true;
			 }
		 }
	  }
	 if (GData.ExtParams) WrkQuery->Params->AssignValues(GData.ExtParams);
	 if (GData.FunFillSProc) bRet = GData.FunFillSProc(GData,bRet);
	 S = GetDSetText(WrkQuery);
	 if (Debug) {
		 ShowMessage(S);
	 }
	 return bRet;
}
//---------------------------------------------------------------------------
bool __fastcall ExecSProcStd(GridData& GData)
{
	TStoredProc* SProc = GData.WrkSProc;
	TDatabase*   DB    = GData.WrkDBase;
	bool bResult = ExecuteProcStd(SProc,DB);
	if (bResult) {
		if (SProc->Params->FindParam("RESULT")) {
			int Result   = SProc->ParamByName("RESULT")->AsInteger;
			GData.Result = Result;
			if (Result <= 0) {
				Rollback(DB);
				OutErrMsgStd(GData,Result);
				bResult = false;
			}
			else GData.KeyValue = Result;
		 }
   }
   return bResult;
}
//---------------------------------------------------------------------------
AnsiString __fastcall MakeSeparateString(AnsiString Str)
{
	AnsiString Res,S;
	for (int i = 1; ; i++) {
		S = GetPiece(Str,"|",i);
		if (S == "") break;
		Res += "\n" + S;
	}
	return Res.SubString(2,Res.Length());
}
//---------------------------------------------------------------------------
bool __fastcall OpenExecQueryStd(GridData& GData)
{
	TQuery* Qry = GData.WrkQuery;
	TDatabase* DB = GData.WrkDBase;
	bool bRes = OpenDSetStd(Qry);
	if (!bRes) {
		if (DB->InTransaction) DB->Rollback();
		AnsiString S = "Ошибка записи в базу " + GetDSetText(Qry);
		OutputMessage(S);
	}

	else {
		if (Qry->FindField("RESULT")) {
			int Result = Qry->FieldByName("RESULT")->AsInteger;
			GData.Result = Result;
			if (Result <= 0) {
				Rollback(DB);
				if (Qry->FindField("ERRMSG") && Qry->FieldByName("ERRMSG")->AsString != "") {
					AnsiString S = GetErrMsgStd(GData, Result);
					if (S != "") S = S + "|";
					OutputMessage(MakeSeparateString(S + Qry->FieldByName("ERRMSG")->AsString));
				}
				else OutErrMsgStd(GData,Result);
				bRes = false;
			}
			else {
				GData.KeyValue = Result;
				if (Qry->FindField("ERRMSG") && Qry->FieldByName("ERRMSG")->AsString != "") {
					OutputMessage(MakeSeparateString(Qry->FieldByName("ERRMSG")->AsString));
				}
			}
		}

   }
   return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall ReorderDataStd(GridData& GData, bool Delete)
{
	bool Reorder = false;
	if (GData.Flags & UPDATE_IN_MEMORY && !(GData.Flags & PULSE_AFTER_UPDATE) && !Delete) {
		TMemTableEh* MemTbl = dynamic_cast<TMemTableEh*>(GData.WrkDSet);
		if (!MemTbl) return Reorder;
		if (GData.EditFld) {
			AnsiString S = "," + GData.EditFld->FieldName.UpperCase() + ",";
			AnsiString X = "," + MemTbl->SortOrder.UpperCase() + ",";
			Reorder = X.Pos(S);
		}
		else Reorder = GData.CurKeyPressed = VK_INSERT;
		if (Reorder) {
			GData.WrkGrid->DataSource->Enabled = false;
			AnsiString X = MemTbl->SortOrder;
			MemTbl->SortOrder = "";
			MemTbl->SortOrder = X;
			GData.WrkGrid->DataSource->Enabled = true;
		}
	}
	return Reorder;
}
//---------------------------------------------------------------------------
bool __fastcall WriteDataStd(GridData& GData,bool Delete)
{
	bool bRes = true;
	GData.DoneArray.clear();
	bRes = WriteDataObjStd(GData,Delete);
	GData.ActionTag = 0;
	if (bRes) {
		if (!GData.Flags & SAVE_SELECTION)
			ClearArrStd(GData);
	}
	else GData.DoneArray.clear();
	GData.ClearCurParams();
	return bRes;
}
//---------------------------------------------------------------------------
void _fastcall RefreshRecordStd(GridData& GData,bool bRes)
{
   if (bRes && GData.FunSetSQLOne) {
      switch (GData.CurKeyPressed) {
         case VK_INSERT: InsertRowStd(GData,"");
                         break;
         default:        RefreshRowStd(GData,"");
                         break;
      }
   }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall WriteDataObjStd(GridData& GData,bool Delete)
{
	TStoredProc* SProc = GData.WrkSProc;
	TQuery* WrkQuery   = GData.WrkQuery;
	bool bResult = true;
	int Succ = 0;
	int Skip = 0;
	int Size = GData.SelArray.size();
	bool AskConfirm = false;
	if (Size > 1 && GData.Flags & ASK_EACH_LINE_CONFIRM && !(GData.Flags & UPDATE_ONLY_CURRENT)) {
		switch (AskQuestionStd(GData,GetMultiSelStr(Size) +"\nВыполнить с опросом ?",TMsgDlgButtons() << mbYes << mbNo << mbCancel)) {
			case mrYes:     AskConfirm = true;  break;
			case mrNo:      AskConfirm = false; break;
			case mrCancel:  return bResult;
		}
	}
	TDatabase* DB = (SProc) ? Session->FindDatabase(SProc->DatabaseName) :
									  Session->FindDatabase(WrkQuery->DatabaseName);
	bool UpdateInMemory = GData.Flags & UPDATE_IN_MEMORY;
	if (DB) {
		if (GData.WrkDBase != DB) GData.WrkDBase = DB;
		if (StartTransaction(DB)) {
			try {
				if (GData.SelArray.empty() || GData.CurKeyPressed == VK_INSERT || GData.Flags & UPDATE_ONLY_CURRENT) {
					int iCase = GData.OperationIsAllowed();
					if (iCase > 0 && ( (GData.WrkSProc && PrepSProcStd(GData,Delete)) ||
											 (GData.WrkQuery && PrepQueryStd(GData,Delete)) )) {
						bResult = (GData.WrkSProc) ? ExecSProcStd(GData) : OpenExecQueryStd(GData);
						bool Selected = RowIsSelectedStd(GData);
						bool AddRow = false;
						if ( bResult && Selected && GData.FunAddRow &&
							 (GData.CurKeyPressed == VK_RETURN || GData.CurKeyPressed == VK_BACK || GData.CurKeyPressed == VK_DELETE)) {
							GData.FunAddRow(GData,-1,true);
							AddRow = true;
						}
						if (GData.FunAfterExec) GData.FunAfterExec(GData,bResult);
						if (UpdateInMemory) {

							 RefreshRecordStd(GData,bResult);
						}
						if (AddRow) {
							if (FilterRecordStd(GData) && GData.CurKeyPressed != VK_DELETE) {
								GData.FunAddRow(GData,1,true);
							}
							else {
								ProcSelectStd(GData,false);
								GData.FunAddRow(GData,0,true);
							}
						}
						if (bResult) {

							WORD Key = GData.CurKeyPressed;
							if (Key != VK_INSERT) {
								GridKeyValue KeyValue;
								GetKeyValueStd(GData,KeyValue,false);
								GData.DoneArray.push_back(KeyValue);
							}
						}
					}
				}
				else {
					std::vector<GridKeyValue>::reverse_iterator iter;
					if (GData.SelArray.size() > GData.MaxUpdateInMemory) UpdateInMemory = false;
					for (iter = GData.SelArray.rbegin(); iter < GData.SelArray.rend(); ++iter) {
						GData.KeyValue = *iter;
						if (RestorePosStd(GData,false)) {
#if DEBUG
							if (0) OutputMessage("Встали на запись");
#endif
							GData.WrkForm->Refresh();                            //???
							int iCase = GData.OperationIsAllowed();
							if (iCase < 0) break;
							if (iCase > 0 && ((GData.WrkSProc && PrepSProcStd(GData,Delete)) ||
													(GData.WrkQuery && PrepQueryStd(GData,Delete)) )) {

#if DEBUG
								if (0) OutputMessage("Приготовили");
#endif
								bool DoIt = true;
								if (AskConfirm) {
									int Res = AskQuestionStd(GData,"Выполнить для текущей строки",TMsgDlgButtons() << mbYes<< mbNo << mbCancel);
									if (Res == mrCancel) break;
									DoIt = (Res == mrYes);
								}
								if (DoIt) {
									bResult = StartTransactionEx(DB) && ((GData.WrkSProc) ? ExecSProcStd(GData) : OpenExecQueryStd(GData));
#if DEBUG
									if (0) OutputMessage("Сделали");
#endif
									if (bResult)
										 GData.DoneArray.insert(GData.DoneArray.begin(),*iter);
									if (GData.FunAfterExec) GData.FunAfterExec(GData,bResult);
									if (!bResult) break;
									if (UpdateInMemory)     RefreshRecordStd(GData,bResult);
									if (GData.Flags & USE_SEPARATE_TRANS) {
										Commit(DB);
									}
									Succ++;
								}
								else Skip++;
							}
							else Skip++;
							if (!(GData.Flags & (SHOW_SELECTED | SAVE_SELECTION)))
								GData.SelArray.pop_back();
						}
					}
				}
			}
			catch (Exception &E) {
				Rollback(DB);
				bResult = false;
				OutputMessage("Выполнен откат текущей транзакции: \n"
								  "Текущие изменения не записаны в БД.\n"
								  + E.Message);
			}
#if DEBUG
			if (0) OutputMessage("Все сделано");
#endif
			if (bResult) {
				Commit(DB);

				if (Delete && !GData.SeeDeleted) {
					GData.WrkDSet->Prior();
					FindUndelStrStd(GData);
					SavePosStd(GData);
				}
				else if (GData.Flags & USE_SAVEPOSSTD)
					SavePosStd(GData);
				if (Size > 1 && Size != Succ + Skip && !(GData.Flags & UPDATE_ONLY_CURRENT)) {
					OutputMessage("Из " + IntToStr(Size) + " операций успешно выполнено : "+IntToStr(Succ));
				}
				if (UpdateInMemory) {
					if (GData.CurKeyPressed == VK_INSERT) {
						GData.KeyValue = GData.Result;
//						RestorePosStd(GData,false);
					}
					GData.ClearCurParams();
					bool bPulse = GData.Flags & PULSE_AFTER_UPDATE || (Delete && !GData.SeeDeleted);
					if (bPulse) {
						if (GData.CurKeyPressed == VK_INSERT) {
							RestorePosStd(GData,false);
						}
						while (!FilterRecordStd(GData) && !GData.WrkDSet->Bof) {
							GData.WrkDSet->Prior();
						}
						PulseFilterStd(GData);
					}
					else {
						if (GData.CurKeyPressed == VK_INSERT || GData.CurKeyPressed == VK_RETURN) {
							if (ReorderDataStd(GData,Delete) || GData.CurKeyPressed == VK_INSERT)
								RestorePosStd(GData,false);
						}
					}
               GData.WrkGrid->Repaint();
               return bResult;
            }
         }
         else SavePosStd(GData);
         CloseChildDSet(GData);
         ReOpenDSetStd(GData);
         OpenChildDSet(GData);
      }
   }
   else OutputMessage("Невозможно найти базу данных "+SProc->DatabaseName);
   GData.ClearCurParams();
   return bResult;
}
//---------------------------------------------------------------------------
bool __fastcall WriteDataQueryStd(GridData& GData,bool Delete)
{
   TQuery* WrkQuery = GData.WrkQuery;
   bool bResult = true;
   int Succ = 0;
   int Skip = 0;
   int Size = GData.SelArray.size();
   bool AskConfirm = false;
   if (Size > 1 && GData.Flags & ASK_EACH_LINE_CONFIRM) {
      switch (AskQuestionStd(GData,GetMultiSelStr(Size) +"\nВыполнить с опросом ?",TMsgDlgButtons() << mbYes << mbNo << mbCancel)) {
         case mrYes:     AskConfirm = true;  break;
         case mrNo:      AskConfirm = false; break;
         case mrCancel:  return bResult;
      }
   }
   TDatabase* DB = Session->FindDatabase(WrkQuery->DatabaseName);
   bool UpdateInMemory = GData.Flags & UPDATE_IN_MEMORY;
   if (DB) {
      if (GData.WrkDBase != DB) GData.WrkDBase = DB;
      TDataSet* WrkDSet = GData.WrkDSet;
      if (StartTransaction(DB)) {
         try {
            if (GData.SelArray.empty() || GData.CurKeyPressed == VK_INSERT) {
               int iCase = GData.OperationIsAllowed();
               if (iCase > 0 && PrepQueryStd(GData,Delete)) {
                  bResult = OpenExecQueryStd(GData);
                  if (GData.FunAfterExec) GData.FunAfterExec(GData,bResult);
                  if (UpdateInMemory)     RefreshRecordStd(GData,bResult);
                  if (bResult) {
                     WORD Key = GData.CurKeyPressed;
                     if (Key != VK_INSERT) {
                        GridKeyValue KeyValue;
                        GetKeyValueStd(GData,KeyValue,false);
                        GData.DoneArray.push_back(KeyValue);
                     }
                  }
               }
            }
            else {
               std::vector<GridKeyValue>::reverse_iterator iter;
               if (GData.SelArray.size() > GData.MaxUpdateInMemory) UpdateInMemory = false;
               for (iter = GData.SelArray.rbegin(); iter < GData.SelArray.rend(); iter++) {
                  GData.KeyValue = *iter;
                  if (RestorePosStd(GData,false)) {
							GData.WrkForm->Refresh();                            //???
                     int iCase = GData.OperationIsAllowed();
                     if (iCase < 0) break;
							if (iCase > 0 && PrepQueryStd(GData,Delete)) {
                        bool DoIt = true;
                        if (AskConfirm) {
                           int Res = AskQuestionStd(GData,"Выполнить для текущей строки",TMsgDlgButtons() << mbYes<< mbNo << mbCancel);
                           if (Res == mrCancel) break;
                           DoIt = (Res == mrYes);
                        }
                        if (DoIt) {
                           bResult = StartTransactionEx(DB) && OpenExecQueryStd(GData);
                           if (bResult)
                               GData.DoneArray.insert(GData.DoneArray.begin(),*iter);
                           if (GData.FunAfterExec) GData.FunAfterExec(GData,bResult);
                           if (!bResult) break;
                           if (UpdateInMemory)     RefreshRecordStd(GData,bResult);
                           if (GData.Flags & USE_SEPARATE_TRANS) Commit(DB);
                           Succ++;
                        }
                        else Skip++;
                     }
                     else Skip++;
                     if (!(GData.Flags & (SHOW_SELECTED || SAVE_SELECTION)))
                        GData.SelArray.pop_back();
                  }
               }
            }
         }
         catch (Exception &E) {
            Rollback(DB);
            bResult = false;
            OutputMessage("Выполнен откат текущей транзакции: \n"
                          "Текущие изменения не записаны в БД.\n"
                          + E.Message);
         }
         if (bResult) {
            Commit(DB);
            if (Delete && !GData.SeeDeleted) {
               WrkDSet->Prior();
               FindUndelStrStd(GData);
               SavePosStd(GData);
            }
            else if (GData.Flags & USE_SAVEPOSSTD)
               SavePosStd(GData);
            if (Size > 1 && Size != Succ + Skip) {
               OutputMessage("Из " + IntToStr(Size) + " операций успешно выполнено : "+IntToStr(Succ));
            }
            if (UpdateInMemory) {
               if (GData.CurKeyPressed == VK_INSERT) {
                  GData.KeyValue = GData.Result;
                  RestorePosStd(GData,false);
               }
               GData.ClearCurParams();
               bool bPulse = GData.Flags & PULSE_AFTER_UPDATE || !FilterRecordStd(GData);
               if (bPulse) {
                  while (!FilterRecordStd(GData) && !GData.WrkDSet->Bof) {
                     GData.WrkDSet->Prior();
                  }
						PulseFilterStd(GData);
               }
               GData.WrkGrid->Repaint();
               return bResult;
            }
         }
			else SavePosStd(GData);
         CloseChildDSet(GData);
         ReOpenDSetStd(GData);
         OpenChildDSet(GData);
      }
   }
   else OutputMessage("Невозможно найти базу данных "+WrkQuery->DatabaseName);
   GData.ClearCurParams();
   return bResult;
}
//---------------------------------------------------------------------------
AnsiString __fastcall GetErrMsgStd(GridData& GData,int Result)
{
  AnsiString S;
  if (GData.GetErrMsg) S = GData.GetErrMsg(GData,Result);
  if (S == "") {
	  switch (Result) {
		  case    0: S = "Запись отсутсвует в базе или поле 'DateChange' записи пусто"; break;
		  case   -1: S = "Данные изменены другим пользователем\n"
							  "Повторите предыдущее действие";
						 break;
		  case   -2: S = "Запись удалена другим пользователем";
						 if (GData.Flags & CAN_SEE_DELETED) GData.SeeDeleted = true;
						 break;
		  default:   S = "Ошибка ("+ IntToStr(Result)+ ") ";
						 TStoredProc* WrkSProc = GData.WrkSProc;
						 if (WrkSProc) {
							 S += "хранимой процедуры "+ WrkSProc->StoredProcName +"\n";
							 S += GetSProcParamValues(WrkSProc);
						 }
						 else {
							 TQuery* WrkQuery = GData.WrkQuery;
							 if (WrkQuery) {
								 S += "запроса\n";
								 S += GetDSetText(WrkQuery);
							 }
						 }
	  }
  }
  return S;
}
//---------------------------------------------------------------------------
bool __fastcall OutErrMsgStd(GridData& GData,int Result)
{
  AnsiString S = GetErrMsgStd(GData,Result);
  OutputMessage(S);
  return false;
}
//---------------------------------------------------------------------------
// ==== Show and write comment in Memo ======================================
//---------------------------------------------------------------------------
void __fastcall ShowMemoStd(GridData& GData,TMemo* Memo,AnsiString* CommentFieldName)
{
  TDataSet* DSet = GData.WrkDSet;
  AnsiString FName = (CommentFieldName) ? *CommentFieldName : AnsiString("COMMENT");
  if (DSet->FindField(FName)) {
	  Memo->Text = DSet->FieldByName(FName)->AsString;
	  if (DSet->FindField("STATUS")) {
			Memo->Enabled =  DSet->FieldByName("STATUS")->AsInteger >= 0;
	  }
  }
}
//---------------------------------------------------------------------------
void __fastcall WriteMemoStd(GridData& GData,TMemo* Memo)
{
   GData.CurKeyPressed = VK_RETURN;
	if (ProcKeyIsAllowed(GData)) {            // Memo c VK_RETURN
		TDataSet* WrkDSet = GData.WrkDSet;
		Trunc(WrkDSet,Memo,"COMMENT");
      if (Memo->Text != WrkDSet->FieldByName("COMMENT")->AsString && GData.InitSProc()) {
         GData.AddCurParam(ftString,"COMMENT",Memo->Text);
         WriteDataStd(GData,false);           // записываем Memo
      }
   }
   ShowMemoStd(GData,Memo);
}
//---------------------------------------------------------------------------
// ==== Handle grid keys ====================================================
//---------------------------------------------------------------------------
bool __fastcall GetLocateField(GridData& GData,AnsiString &LocField,bool GoTo)
{
   LocField = GData.FieldLoc;
   if (LocField == "") LocField = GData.FieldOut;
	if (LocField == "") LocField = GData.DefFieldFlt;
   if (LocField == "") return false;
   if (GoTo) {
      TDBGridColumnsEh* Columns = GData.WrkGrid->Columns;
      if (LocField != Columns->Items[GData.WrkGrid->Col-1]->Field->FieldName) {
         for (int i=0; i<Columns->Count; i++) {
            if (Columns->Items[i]->Field->FieldName == LocField) {
               GData.WrkGrid->Col = ++i;
               break;
            }
         }
      }
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall LocateGDataStd(GridData& GData)
{
   bool bRes = false;
   AnsiString LocField;
   if (GetLocateField(GData,LocField,true)) {
      AnsiString SearchTxt = GData.SearchTxt;
      GData.State |= LOCATE_IN_PROGRESS;
      bRes = GData.WrkDSet->Locate(LocField,SearchTxt,
                        TLocateOptions()<< loPartialKey << loCaseInsensitive);
      if (!bRes) {
         GData.SearchTxt = SearchTxt.SubString(1,SearchTxt.Length()-1);
         GData.SearchKey.Clear();//Null;
      }
      else {
          GetKeyValueStd(GData,GData.SearchKey,false);
      }
      GData.State &= ~LOCATE_IN_PROGRESS;
   }
   else GData.SearchTxt = "";
   return bRes;
}
//---------------------------------------------------------------------------
void __fastcall ProcKeyDownStd(GridData& GData,WORD Key)
{
    GData.CurKeyPressed = Key;
    switch (Key) {
        case VK_INSERT: ProcInsertStd(GData);   break;
		  case VK_RETURN: ProcReturnStd(GData);   break;
        case VK_BACK:   ProcBackSpStd(GData);   break;
        case VK_DELETE: ProcDeleteStd(GData);   break;
        case VK_F9:     ProcRestoreStd(GData);  break;
		  case VK_SPACE:  ProcSelectStd(GData);   break;
		  case VK_F7:     if (GData.WrkGrid->RowDetailPanel->Active)
									GData.WrkGrid->RowDetailPanel->Visible = !GData.WrkGrid->RowDetailPanel->Visible;
								break;
		  case VK_ESCAPE: if (GData.SearchTxt != "") {
									 GData.SearchTxt = "";
									 GData.WrkGrid->Repaint();
								}
								GData.WrkGrid->RowDetailPanel->Visible = false;
								break;
		  case VK_UP:
		  case VK_PRIOR:
		  case VK_NEXT:
								GData.State |= SCROLL_KEY_PRESSED;
                        break;
		  case VK_DOWN:   if (GData.WrkGrid->RowDetailPanel->Visible && !GData.WrkDSet->Eof) {
									GData.WrkGrid->RowDetailPanel->Visible = false;
									GData.State |= SET_ROW_DETAIL_PANEL_VISIBLE;

									GData.State |= SCROLL_IN_PROGRESS;
//                           GData.WrkDSet->Next();
                        }
                        break;
   }
}
static AnsiString AlphaNum = "qwertyuiopasdfghjklzxcvbnm,йцукенгшщзхъфывапролджэячсмитьбю.ё"
                             "QWERTYUIOPASDFGHJKLZXCVBNM,ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ.Ё[];'"
                             """<>?:{}1234567890-=\|+_)(*&^%$#@!./";
//---------------------------------------------------------------------------
bool __fastcall KeyIsAlphaNum(wchar_t &Key)
{
	return AlphaNum.Pos(Key);
}
//---------------------------------------------------------------------------
void __fastcall ProcKeyPressStd(GridData& GData,wchar_t &Key)
{
   if ((GData.Flags & INC_SEARCH)) {
      if (KeyIsAlphaNum(Key) || (Key == char(" ") && GData.SearchTxt != "")) {
			GData.SearchTxt += AnsiString(Key);
			LocateGDataStd(GData);
		}
	}
}
//---------------------------------------------------------------------------
bool __fastcall ProcInsertStd(GridData& GData,UnicodeString Name)
{
	bool bRes  = false;
	GData.CurKeyPressed = VK_INSERT;
	if (ProcKeyIsAllowed(GData)) {   // Insert
		bool DoIt  = true;
		AnsiString FldOut = GData.FieldOut;
		if (FldOut != "")
			if (TranslateName(GData,FldOut) && GData.CurFun) FldOut = "";
		if (FldOut != "" && Name == "" ) {
			UnicodeString Msg = GetFieldOutTitleStd(GData);
			if (InputQuery(_TEXT("Ввод новой записи"),Msg,Name))
				Name = Name.Trim();
			if (Name == "") DoIt = false;
		}
		if (DoIt && GData.InitSProc()) {
			TParams* WrkParams = NULL;
			TParams* CurParams = GData.CurParams;
			TStoredProc* SProc = GData.WrkSProc;
			TQuery*      Query = GData.WrkQuery;
			if (SProc) {
				ClearSProcParam(SProc);             // все параметры SP в Null
				WrkParams  = SProc->Params;            // из SP => CurParams
			}
			else if (Query) {
				SetParamsType(Query->Params,GData.WrkDSet);
				ClearQueryParam(Query);    // все параметры Qry в Null
				WrkParams = Query->Params;
			}
			if (CurParams) WrkParams->AssignValues(CurParams);
			else           CurParams = new TParams();
			CurParams->Assign(WrkParams);
			GData.CurParams = CurParams;
			if (GData.SelParams) {
				for (int i=0; i<GData.SelParams->Count; i++) {
					AnsiString FName = GData.SelParams->Items[i]->Name;
					int ID = 0;
					FunGetID Fun = NULL;
					if (GData.FunGetIDMap.size()) {
						std::map<AnsiString,FunGetID>::iterator iter = GData.FunGetIDMap.find(FName);
						if (iter != GData.FunGetIDMap.end()) {
							Fun = iter->second;
							if (Fun && Fun(GData.WrkForm,0,ID,GData.ExtParams))
								GData.CurParams->ParamValues[FName] = ID;
							else {
								DoIt = false;
								break;
							}
						}
					}

				}
			}
			if (DoIt) {
				GData.Filter = "";
				if (FldOut != "" && Name != "")
					 GData.CurParams->ParamValues[FldOut] = Name;
				GData.SkipCheckEditIsAllowed();
				bRes = WriteDataStd(GData,false);    // делаем Insert
			}
		}
	}
	GData.ClearCurParams();
	return bRes;
}
//---------------------------------------------------------------------------
bool __fastcall ShowDetailPanel(GridData& GData,bool CheckFlag)
{
	bool bRes = false;
	if (!CheckFlag || (GData.Flags & SHOW_RDP_ON_RETURN)) {
		TDBGridEh* Grid = GData.WrkGrid;
		if (Grid->RowDetailPanel->Active && !Grid->RowDetailPanel->Visible) {
			AnsiString S;
			if (GetLocateField(GData,S,false)) {
				if (S == GData.EditFldName) {
					Grid->RowDetailPanel->Visible = true;
					GData.SearchTxt = "";
					Grid->Repaint();
					bRes = true;
				}
			}
		}
	}
	return bRes;
}
//---------------------------------------------------------------------------
int __fastcall GetCurColumnEditAction(GridData& GData)
{
	int Action    = 0;
	GData.CurKeyPressed = VK_RETURN;
	GridData::WrkGData = &GData;
	GetGridColParam(GData,true);                      // вынесено специально наверх
	int EditCol1 = GData.EditCol-1;
	if (ProcKeyIsAllowed(GData) ) {                  // Return на Grid'е
		if (GData.EditAllowMask[EditCol1]) {
			if (GData.Select_IDMask[EditCol1] ) {
				Action = -1;
			}
			else {
				switch (GData.EditFld->DataType) {
					case ftString:  if (GData.PickCnt) Action = 2;
										 else               Action = 1;
										 break;
					case ftInteger:
					case ftWord:
					case ftSmallint:
					case ftFloat:    Action = 4;   break;
					case ftDateTime: Action = 5;   break;
				}
			}
		}
	}
	return Action;
}
//---------------------------------------------------------------------------
int __fastcall ProcReturnStd(GridData& GData)
{
	int Action    = 0;
	GData.CurKeyPressed = VK_RETURN;
	GridData::WrkGData = &GData;
	GetGridColParam(GData,true);                    // вынесено специально наверх
	int EditCol1 = GData.EditCol-1;
	if (!ShowDetailPanel(GData,true)) {
		if (ProcKeyIsAllowed(GData) ) {              // Return на Grid'е
			if (GData.EditAllowMask[EditCol1]) {
				if (GData.Select_IDMask[EditCol1] ) {
					if (GData.CurFun) {
						ProcSel_IDStd(GData,0);
					}
					Action = -1; // все уже сделано
				}
				else {
					switch (GData.EditFld->DataType) {
						case ftString:  if (GData.PickCnt) Action = 2;
											 else               Action = 1;
											 break;
						case ftInteger:
						case ftWord:
						case ftSmallint:
						case ftFloat:    Action = 4;   break;
						case ftDateTime: Action = 5;   break;
					}
					if (Action > 0) {
						HighlightEditRow(GData,true);
						if (ProcWinCtlStd(GData,Action)) Action = 0;
					}
					else {
						if (ShowDetailPanel(GData,false)) Action = -1;
					}
				}
			}
		}
		else if (ShowDetailPanel(GData,false)) Action = -1;
	}
	else Action = -1;
	return Action;
}
//---------------------------------------------------------------------------
TWinControl* GetEditWinControl(GridData& GData,int Action)
{
	TWinControl* WinCtrl = NULL;
	TDataSet* DS = GData.WrkDSet;
	AnsiString FldName = GData.EditFldName;
	switch (Action) {
		case 1: if (GData.TextEdit) {
					  WinCtrl = GData.TextEdit;
					  GData.TextEdit->Text = DS->FieldByName(GData.EditFldName)->AsString.Trim();
					  GData.TextEdit->SelectAll();
				  }
				  break;
	  case  2: if (GData.ListEdit) {
					  TComboBox* CBox = GData.ListEdit;
					  CBox->Items->Clear();
					  CBox->Items->Assign(GData.Column->PickList);
					  CBox->ItemIndex = DS->FieldByName(FldName)->AsInteger;
					  CBox->DropDownCount = CBox->Items->Count;
					  WinCtrl = CBox;
				  }
				  break;
		case 3: break;
		case 4: if (GData.NumbEdit) {
					  GData.NumbEdit->Value = DS->FieldByName(FldName)->AsFloat;
					  GData.NumbEdit->DecimalPlaces = GData.DPlaces;
					  GData.NumbEdit->SelectAll();
					  WinCtrl = GData.NumbEdit;
				  }
				  break;
		case 5: if (GData.DateEdit) {
					  int Pos = GData.Column->DisplayFormat.Trim().Pos("hh:nn");
					  GData.DateEdit->EditButton->Enabled = !Pos;
					  GData.DateEdit->EditButton->Visible = !Pos;
					  switch (Pos) {
							case 0:  //GData.DateEdit->Kind       = dtkDateEh;
										GData.DateEdit->EditFormat = "dd.mm.yy";
										break;
							case 1:  //GData.DateEdit->Kind       = dtkTimeEh;
										GData.DateEdit->EditFormat = "hh:nn";
										break;
							default: //GData.DateEdit->Kind       = dtkDateTimeEh;
										GData.DateEdit->EditFormat = "dd.mm.yy hh:nn";
										break;
					  }
					  if (DS->FieldByName(FldName)->IsNull) {
							GData.DateEdit->Value = Date();
					  }
					  else {
						  GData.DateEdit->Value = DS->FieldByName(FldName)->Value;
					  }
					  WinCtrl = GData.DateEdit;
				  }
				  break;
	}
	return WinCtrl;
}
//---------------------------------------------------------------------------
bool __fastcall ProcWinCtlStd(GridData& GData,int Action)
{
	bool bRes = false;
	TWinControl* WinCtrl = NULL;
	AnsiString FldName = GData.EditFldName;
	TDataSet* DS = GData.WrkDSet;
	int MoveUp,MoveLft,nTmp;
	switch (Action) {
		case 1: if (GData.TextEdit) {
					  GData.TextEdit->Text = DS->FieldByName(GData.EditFldName)->AsString.Trim();
					  GData.TextEdit->SelectAll();
					  WinCtrl = GData.TextEdit;
				  }
				  break;
	  case 2:  if (GData.ListEdit) {
					  TComboBox* CBox = GData.ListEdit;
					  CBox->Items->Clear();
					  CBox->Items->Assign(GData.Column->PickList);
					  CBox->ItemIndex = DS->FieldByName(FldName)->AsInteger;
					  CBox->DropDownCount = CBox->Items->Count;
					  WinCtrl = CBox;
				  }
				  break;
		case 3: break;
		case 4: if (GData.NumbEdit) {
					  GData.NumbEdit->Value = DS->FieldByName(FldName)->AsFloat;
					  GData.NumbEdit->DecimalPlaces = GData.DPlaces;
					  GData.NumbEdit->SelectAll();
					  WinCtrl = GData.NumbEdit;
				  }
				  break;
		case 5: if (GData.DateEdit) {
		           GData.DateEdit->Value = Null;
					  int Pos = GData.Column->DisplayFormat.Trim().Pos("hh:nn");
					  GData.DateEdit->EditButton->Enabled = !Pos;
					  GData.DateEdit->EditButton->Visible = !Pos;
					  switch (Pos) {
							case 0:  //GData.DateEdit->Kind       = dtkDateEh;
										GData.DateEdit->EditFormat = "dd.mm.yy";
										break;
							case 1:  //GData.DateEdit->Kind       = dtkTimeEh;
										GData.DateEdit->EditFormat = "hh:nn";
										break;
							default: //GData.DateEdit->Kind       = dtkDateTimeEh;
										GData.DateEdit->EditFormat = "dd.mm.yy hh:nn";
										break;
					  }

					  if (DS->FieldByName(FldName)->IsNull) {
                    GData.DateEdit->Value = Date();
					  }
					  else {
						  GData.DateEdit->Value = DS->FieldByName(FldName)->Value;
					  }
					  WinCtrl = GData.DateEdit;
				  }
				  break;
	}
	if (WinCtrl) {
		PutEditOnGrid(GData.WrkGrid,WinCtrl,!(GData.Flags & DONT_SET_EDIT_WIDTH));
		GData.State |= EDIT_IN_PROGRESS;
		if (Action == 1) {
			GData.TextEdit->Font->Style = GData.TextEdit->Font->Style >> fsBold;
		}
		switch (Action) {
			case 2: if (GData.ListEdit->Width < 90) GData.ListEdit->Width = 90;
					  GData.ListEdit->DroppedDown = true;
					  break;
			case 5: if (GData.DateEdit->EditFormat == "dd.mm.yy") {
						  int ColWidth  = GData.Column->Width;
//						  int ColHeight = GData.WrkGrid->RowHeight;
						  if (GData.DateEdit->Width < 90) {
								GData.DateEdit->Width = ColWidth + 18;
								if (GData.DateEdit->Width < 69) {
									GData.DateEdit->Width = 69;
								}
						  }
						  GData.DateEdit->DropDown();
						  break;
						}
						if (GData.DateEdit->EditFormat == "dd.mm.yy hh:nn") {
							if (GData.DateEdit->Width < 110) GData.DateEdit->Width = 110;
						}
						break;

		}
	}
	return bRes;
}
//---------------------------------------------------------------------------
void __fastcall ProcSel_IDStd(GridData& GData,int Index1)
{
	AnsiString FName = GData.EditFldName;
	int ID = GData.WrkDSet->FieldByName(FName)->AsInteger;
	FunGetID Fun = GData.CurFun;
	if (Fun) {
		HighlightEditRow(GData,true);
		TDBGridColumnsEh* Columns = GData.WrkGrid->Columns;
		int Width = 0;
		for (int i=0; i<GData.GridCol-1; i++) {
			Width += Columns->Items[i]->Width;
		}
		POINT P;
		P.x = Width;
		P = GData.WrkGrid->ClientToScreen(P);
		Width = P.x;
		if (Fun(GData.WrkForm,Width,ID,GData.CurParams)) {
			int Size = GData.SelArray.size();
			if (Size > 1 && !(GData.Flags & UPDATE_ONLY_CURRENT)) {
				AnsiString S = GetMultiSelStr(Size) +"\n Выполнить запрошенное действие ?";
				if (!AskQuestionStd(GData,S)) return;
			}
			GData.AddCurParam(ftInteger, FName,ID);
			if (GData.InitSProc())
				WriteDataStd(GData,false);   // записываем рез-т выбора ID
		}
		HighlightEditRow(GData,false);
	}
	GData.ClearCurParams();
}
//---------------------------------------------------------------------------
bool __fastcall ProcDeleteStd(GridData& GData)
{
	bool bRes = false;
	GData.CurKeyPressed = VK_DELETE;
	if (ProcKeyIsAllowed(GData) ) {  // Delete
		AnsiString S;
		int Size = GData.SelArray.size();
		if (GData.AskDel != "") {
			S = GData.AskDel;
			GData.AskDel = "";
		}
		else {
			if (Size > 1 && !(GData.Flags & UPDATE_ONLY_CURRENT))
				S = GetMultiSelStr(Size) +" Удалить их ?";
			else {
				if (GData.FieldOut != "")
					S  = "Удалить "+ GData.ObjectName + " '" +GData.WrkDSet->FieldByName(GData.FieldOut)->AsString+"' ?";
				else
					S = "Удалить текущую запись ?";
			}
		}
		if (GData.InitSProc()) {
			HighlightEditRow(GData,true);
			if (AskQuestionStd(GData,S)) {
				bRes = WriteDataStd(GData,true);        // удаляем запись
				SetEditSearchTxtStd(GData);
			}
			HighlightEditRow(GData,false);
		}
	}
	GData.ClearCurParams();
	return bRes;
}
//---------------------------------------------------------------------------
void __fastcall ProcRestoreStd(GridData& GData)
{
   GData.CurKeyPressed = VK_F9;
   if (ProcKeyIsAllowed(GData)) { // F9 restore на Grid'е
      AnsiString S;
      int Size = GData.SelArray.size();
		if (Size > 1 && !(GData.Flags & UPDATE_ONLY_CURRENT))
		  S = GetMultiSelStr(Size) +" Восстановить их ?";
		else {
			if (GData.FieldOut != "")
				S  = "Восстановить " + GData.ObjectName + " '" +GData.WrkDSet->FieldByName(GData.FieldOut)->AsString+"' ?";
			else
				S = "Восстановить текущую запись ?";
		}
		if (GData.InitSProc()) {
			if (RowIsDeleted(GData.WrkDSet) && !(GData.Flags & UPDATE_ONLY_CURRENT))
				HighlightEditRow(GData,true);
			if (AskQuestionStd(GData,S)) {
				Variant V;
				V.Clear();
				GData.AddCurParam(ftInteger, "Status",V);
				WriteDataStd(GData,false);                    // восстанавливаем запись
			}
         else GData.ClearCurParams();
         HighlightEditRow(GData,false);
      }
   }
}
//---------------------------------------------------------------------------
bool __fastcall ProcBackSpStd(GridData& GData)
{
	bool bRes = true;
	GData.CurKeyPressed = VK_BACK;
	int Length = GData.SearchTxt.Length();
	if (Length--) {
		GData.SearchTxt = GData.SearchTxt.SubString(1,Length);
		if (Length) LocateGDataStd(GData);
		else        GData.WrkGrid->Repaint();
		return bRes;
	}
	GetGridColParam(GData,true);
	if (ProcKeyIsAllowed(GData))  {  // VK_BACK на Grid'е
		int NBit      = GData.EditCol-1;
		if (GData.NullAllowMask[NBit]) {    // 5.09.11 VIV
			AnsiString S;
			int Size = GData.SelArray.size();
			if (Size > 1 && !(GData.Flags & UPDATE_ONLY_CURRENT))
				S = GetMultiSelStr(Size)+"\n";
			if (GData.InitSProc()) {
				HighlightEditRow(GData,true);
				if (AskQuestionStd(GData,S + "Очистить поле '"+GData.ColCaption+"' ?")) {
					Variant V;
					V.Clear();
					GData.AddCurParam(GData.FieldType,GData.EditFldName,V);
					bRes = WriteDataStd(GData,false);                               // стираем поле
            }
            HighlightEditRow(GData,false);
         }
      }
   }
	GData.ClearCurParams();
	return bRes;
}
//---------------------------------------------------------------------------
void __fastcall ProcSelectStd(GridData& GData,bool Move)
{
	GData.CurKeyPressed = VK_SPACE;
	bool IsDeleted = RowIsDeleted(GData.WrkDSet);
	if (!GData.SelArray.size()) {
		if (IsDeleted) GData.State |=  DELETED_ARE_SELECTED;
		else           GData.State &= ~DELETED_ARE_SELECTED;
	}
	else {
		if (IsDeleted != bool (GData.State & DELETED_ARE_SELECTED)) return;
	}
	if (!(GData.Flags & MULTIPLE_SEL) || KeyFieldIsNullStd(GData) || GData.SearchTxt != "") return;
	if (RowIsSelectedStd(GData,true)) {
		GridKeyValue KeyValue;
		GetKeyValueStd(GData,KeyValue,false);
			 std::vector<GridKeyValue>::iterator Iter = find(GData.SelArray.begin(),GData.SelArray.end(),KeyValue);
		if (Iter != GData.SelArray.end()) {
			GridKeyValue Prv;
			bool UsePrv = false;
			if (Iter != GData.SelArray.begin()) {
				Prv = *(Iter-1);
				UsePrv = true;
			}
			GData.SelArray.erase(Iter);
			if (GData.FunAddRow) {
				GData.FunAddRow(GData, -1, true);
			}
			if (Move && GData.Flags & MOVE_DOWN_AFTER_SEL) {
				if (GData.SelArray.size()) {
					GData.KeyValue = (UsePrv) ? Prv : *GData.SelArray.begin();
					RestorePosStd(GData,false);
				}
			}
		}
	}
	else {
		  if (GData.FunAddRow) {
			  GData.FunAddRow(GData, 1, true);
		  }
		  if (Move && GData.Flags & MOVE_DOWN_AFTER_SEL)
			  GData.WrkDSet->Next();
	}
	GData.WrkGrid->Repaint();
	SetStatusBarStd(GData);
}
// ==== Grid event handlers ====================================================
void __fastcall DBGridEhExitStd(GridData& GData)
{
}
void __fastcall RowDetailPanelHideStd(GridData& GData)
{
   if (GData.State & SCROLL_KEY_PRESSED)
      GData.State |= SET_ROW_DETAIL_PANEL_VISIBLE;
}
void __fastcall RowDetailPanelShowStd(GridData& GData)
{
	if (!GData.State & SCROLL_KEY_PRESSED)
		GData.WrkGrid->RowDetailPanel->Visible = false;
}
//---------------------------------------------------------------------------
// ==== Edit on grid ========================================================
//---------------------------------------------------------------------------
bool __fastcall EditKeyDownStd(GridData& GData,TObject *Sender, WORD &Key,TShiftState Shift)
{
	bool         DoIt = false;
	bool         SaveULast;
	int          Size;
	bool         bRes = true;
	TCustomEdit*       TextEdit;
	TDBNumberEditEh*   NumbEdit;
	TDBDateTimeEditEh* DateEdit;
	TDataSet*          WrkDSet;
	TCustomDBEditEh*   CustEditEh;
	AnsiString         EditFldName;
	switch (Key) {
		case VK_RETURN: WrkDSet      = GData.WrkDSet;
							 EditFldName  = GData.EditFldName;
							 SaveULast    = GData.UnselLast;
							 GData.UnselLast = false;            // чтобы не убралась из выбранных на событии EditExit
							 if (GData.DateEdit && GData.DateEdit->Visible) {
								 GData.DateEdit->CloseUp(true);
							 }
							 GData.WrkGrid->SetFocus();
							 GData.WrkGrid->Repaint();
							 GData.UnselLast = SaveULast;
							 DoIt = false;
							 Size = GData.SelArray.size();
							 if (Size > 1 && !(GData.Flags & UPDATE_ONLY_CURRENT)) {
								 AnsiString S = GetMultiSelStr(Size) +"\n Выполнить запрошенное действие ?";
								 if (!AskQuestionStd(GData,S)) return true;
								 DoIt = true;
							 }
							 else DoIt = false;
							 CustEditEh = dynamic_cast<TCustomDBEditEh*>(Sender);
							 if (CustEditEh) {
								 if (GData.InitSProc()) {
									 switch (GData.EditFld->DataType) {
										  case ftString:    DoIt = Trunc(WrkDSet,CustEditEh,EditFldName);
																  break;
											default:         DoIt = DoIt || CustEditEh->Value != WrkDSet->FieldByName(EditFldName)->Value;
																  break;
									 }
									 if (DoIt)
										  GData.AddCurParam(GData.EditFld->DataType,EditFldName,CustEditEh->Value);
								 }
								 else DoIt = false;
							 }
							 else {
								 TComboBox* CBox = dynamic_cast<TComboBox*>(Sender);
								 if (CBox) {
									 int ItemIndex   = GData.ItemIndex = CBox->ItemIndex;
									 if (GData.InitSProc()) {
										 DoIt = DoIt ||  ItemIndex != WrkDSet->FieldByName(EditFldName)->AsInteger;
										 if (DoIt)
											 GData.AddCurParam(ftInteger,EditFldName,ItemIndex);
									 }
									 else DoIt = false;
								 }
								 else DoIt = false;
							 }
							 if (DoIt || GData.Flags & EXEC_SP_ALWAYS)
								 bRes = WriteDataStd(GData,false);
							 GData.ClearCurParams();
							 HighlightEditRow(GData,false);
							 break;
		case VK_ESCAPE: GData.WrkGrid->SetFocus();
							 GData.WrkGrid->Repaint();
							 HighlightEditRow(GData,false);
							 break;
		case VK_INSERT: if (!GData.DateEdit->CalendarVisible)
							    GData.DateEdit->DropDown();
							 break;
	}
	return bRes;
}
//---------------------------------------------------------------------------
void __fastcall EditExitStd(TObject* Sender)
{
	TWinControl* Edit = dynamic_cast<TWinControl*>(Sender);
	if (Edit) {
		Edit->Visible = false;
		Edit->Enabled = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall EditExitStd(GridData& GData,TObject* Sender)
{
//   GData.State ^= EDIT_IN_PROGRESS;
   GData.State &= ~EDIT_IN_PROGRESS;
   TWinControl* Edit = dynamic_cast<TWinControl*>(Sender);
   if (Edit) {
      Edit->Visible = false;
      Edit->Enabled = false;
   }
   HighlightEditRow(GData,false);
}
// ==== Working with Excel ==================================================
#ifdef __Excel_2K_SRVR_h__

Variant ExcelOut::ExApp   = Null;
Variant ExcelOut::ExSheet = Null;
void __fastcall ExcelOut::ExcelInit(AnsiString File,bool Visible)
{
// если Excel запущен - подключиться к нему
   try {
	  ExcelOut::ExApp = Variant::GetActiveObject("Excel.Application");
   }
   catch (...) {
	  // Excel не запущен - запустить его
	  try {
		 ExcelOut::ExApp = Variant::CreateObject("Excel.Application");
	  }
	  catch (...) {
		 Application->MessageBox("Невозможно открыть Microsoft Excel!"
		 "Возможно Excel не установлен на компьютере.","Ошибка",MB_OK+MB_ICONERROR);
	  }
  }
  try {
     ExcelOut::ExApp.OlePropertySet("Visible",Visible);
     if(File!="") {
        ExApp.OlePropertyGet("WorkBooks").OleProcedure("Open",File);
        ExcelOut::ExSheet = ExApp.OlePropertyGet("WorkSheets",1);
     }
     else  {
//        if (New) ExApp.OlePropertyGet("WorkBooks").OleProcedure("add");
//        Variant WB = ExApp.OlePropertyGet("WorkBooks");
//        if (WB.IsNull()) WB.OleProcedure("add");
        ExcelOut::ExApp.OlePropertyGet("WorkBooks").OleProcedure("add");
        ExcelOut::ExSheet = ExApp.OlePropertyGet("WorkSheets",1);
     }
  }
  catch(...) {
     Application->MessageBox("Ошибка открытия книги Microsoft Excel!",
                             "Ошибка",MB_OK+MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall ExcelOut::toExCellCell(int Row,int Col,AnsiString Text)
{
   try {
      Variant Cur = ExcelOut::ExSheet.OlePropertyGet("Cells",Row,Col);
      Cur.OlePropertySet("Value",Text.c_str());
   }
   catch (...) { ; }
}
//---------------------------------------------------------------------------
void __fastcall ExcelOut::WriteDataToExcel(void* GC,TDataSet* SrcDSet)
{
   ExcelInit("");
   TDBGridColumns* Columns = (TDBGridColumns*)(GC);
   if (!Columns) return;
   int NCol = Columns->Count;
   for (int i=0; i<NCol; i++) {
     toExCellCell(1,i+1,Columns->Items[i]->Title->Caption);
   }
   SrcDSet->First();
   int Row = 2;
   while (!SrcDSet->Eof) {
      for (int i=0; i<NCol; i++) {
         toExCellCell(Row,i+1,SrcDSet->FieldByName(Columns->Items[i]->FieldName)->AsString);
      }
      Row++;
      SrcDSet->Next();
   }
}
//---------------------------------------------------------------------------
void __fastcall ExcelOut::WriteDataToExcelEh(void* GC,TDataSet* SrcDSet)
{
   ExcelInit("");
   TDBGridColumnsEh* Columns = (TDBGridColumnsEh*)(GC);
   if (!Columns) return;
   int NCol = Columns->Count;
   for (int i=0; i<NCol; i++) {
     toExCellCell(1,i+1,Columns->Items[i]->Title->Caption);
   }
   SrcDSet->First();
   int Row = 2;
   while (!SrcDSet->Eof) {
      for (int i=0; i<NCol; i++) {
         toExCellCell(Row,i+1,SrcDSet->FieldByName(Columns->Items[i]->FieldName)->AsString);
      }
      Row++;
      SrcDSet->Next();
   }
}
//---------------------------------------------------------------------------
void __fastcall ExcelOut::WriteDataToExcel(void* GC,TDataSet* SrcDSet,int NDim,int *Arr,AnsiString FName,bool ShowTitle,AnsiString FileName)
{
   ExcelInit("");
   int Row = 1;
   TDBGridColumns* Columns = (TDBGridColumns*) GC;
   int NCol = Columns->Count;
   if  (ShowTitle) {
      for (int i=0; i<NCol; i++) {
         toExCellCell(1,i+1,Columns->Items[i]->Title->Caption);
      }
      Row++;
   }
   SrcDSet->First();
   bool Sav = true;
   while (!SrcDSet->Eof) {
      if (NDim) {
        Sav = false;
        int ID = SrcDSet->FieldByName(FName)->AsInteger;
        for (int i=0; i<NDim; i++) {
          if (Arr[i] == ID) {
            Sav = true;
            break;
          }
        }
      }
      if (Sav) {
         for (int i=0; i<NCol; i++) {
            toExCellCell(Row,i+1,SrcDSet->FieldByName(Columns->Items[i]->FieldName)->AsString);
        }
        Row++;
      }
      SrcDSet->Next();
   }
   if (FileName != "") {
      ExApp.OlePropertySet("DisplayAlerts",false);
      ExSheet.OleProcedure("SaveAs",FileName);
      ExApp.OleProcedure("Quit");
   }
}
//---------------------------------------------------------------------------
bool __fastcall DefaultPrinterIsZebra()
{

  TPrinter *pr=new TPrinter;
  char s1[255],s2[255],s3[255];
  unsigned int a;
  AnsiString as;

  pr->PrinterIndex=-1;
  pr->GetPrinter(s1, s2, s3, a);
  as=s1;
  delete pr;
  if(as.UpperCase().Pos("ZEBRA") || as.UpperCase().Pos("ZDESIGNER")) return true;
  return false;
}
//---------------------------------------------------------------------------
void __fastcall ExcelOut::ExcelPrint(AnsiString File)
{
   if (DefaultPrinterIsZebra()) {
		OutputMessage("Нельзя печатать на принтер типа Zebra");
      return;
   }
   Variant PageSetup;
   ExcelOut::ExcelInit(File,false);

   PageSetup = ExcelOut::ExSheet.OlePropertyGet("PageSetup");
   PageSetup.OlePropertySet("LeftMargin",0);
   PageSetup.OlePropertySet("RightMargin",0);
   PageSetup.OlePropertySet("Zoom",false);
   PageSetup.OlePropertySet("FitToPagesWide",1);
   PageSetup.OlePropertySet("FitToPagesTall",1);
   ExcelOut::ExApp.OlePropertyGet("ActiveWorkbook").OleProcedure("PrintOut");// Copies:=1, Collate:=True
   ExcelOut::ExApp.OlePropertyGet("ActiveWorkbook").OleProcedure("Close",false);
   ExcelOut::ExApp.OleProcedure("Quit");
   PageSetup.Clear();
   ExcelOut::ExSheet.Clear();
   ExcelOut::ExApp.Clear();
}
#endif


