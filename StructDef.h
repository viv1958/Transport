struct FieldFilter {
	int NullCheck;    // 0 - ==;  1 >
	Variant MinValue;
	Variant MaxValue;
	Variant EqvValue;
	FieldFilter(): NullCheck(0)/*, MinValue(Null),MaxValue(Null),EqvValue(Null)*/ {
		MinValue.Clear();
		MaxValue.Clear();
		EqvValue.Clear();
	}
	TFieldType FldType;
	AnsiString Format;
};

typedef std::map<AnsiString,vector<FieldFilter> > FilterRows;
typedef std::vector<FilterRows> FilterCols;

struct FieldInRow {
	int Row;
	AnsiString FldName;
	TFieldType FldType;
	AnsiString Format;
	FieldInRow(int N,AnsiString S, TFieldType Type, AnsiString Fmt) : Row(N), FldName(S), FldType(Type), Format(Fmt) {}
};

AnsiString __fastcall GetVariantString(Variant& V, const FieldInRow* FR)
{
	AnsiString Res;
	if (!V.IsNull() && !V.IsEmpty() ) {
		try {
			Res = V;
			if (FR->FldType == ftDateTime) {
				TDateTime DT = V;
				Res = DT.FormatString(FR->Format);
			}
		}
		catch(...) {

		}
	}
	return Res;
}

AnsiString __fastcall GetVariantString(Variant& V, TFieldType FldType,AnsiString Format)
{
	AnsiString Res;
	if (!V.IsNull() && !V.IsEmpty() ) {
		try {
			Res = V;
			if (FldType == ftDateTime) {
				if (Format.Pos("dd.")) {
					TDateTime DT = V;
					Res = IntToStr(DT - Date());
				}
				else {
					TDateTime DT = V;
					Res = DT.FormatString(Format);
				}
			}
		}
		catch(...) {

		}
	}
	return Res;
}

