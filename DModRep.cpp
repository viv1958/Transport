//---------------------------------------------------------------------------


#pragma hdrstop

#include "DModRep.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
TDModReport *DModReport;
//---------------------------------------------------------------------------
__fastcall TDModReport::TDModReport(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
