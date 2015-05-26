//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------



USEFORM("FrmOrderCopy.cpp", FormOrderCopy);
USEFORM("FrmGetFieldFilter.cpp", FormGetFieldFilter);
USEFORM("FrmFilter.cpp", FormFilter);
USEFORM("FrmPassWord.cpp", FormPassWord);
USEFORMNS("FrmTrans.cpp",XXX, FormTrans);
USEFORM("FrmSelSimpleEh.cpp", FormSelSimpleEh);
USEFORM("FrmDriverRep.cpp", FormDriverRep);
USEFORM("DModT.cpp", DModT); /* TDataModule: File Type */
USEFORM("DModRep.cpp", DModReport); /* TDataModule: File Type */
USEFORM("FrmSelRep.cpp", FormSelRep);
USEFORM("FrmDriverGraphDay.cpp", FormDriverGraphDay);
USEFORM("FrmDriverGraph.cpp", FormDriverGraph);
USEFORM("FrmDateRange.cpp", FormDateRange);
//---------------------------------------------------------------------------
extern int AppTerminate;
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TDModT), &DModT);
		if (!AppTerminate) {
			Application->CreateForm(__classid(TFormTrans), &FormTrans);
		   Application->Run();
		}
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
