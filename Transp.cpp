//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORMNS("FrmTrans.cpp",XXX, FormTrans);
USEFORM("FrmPassWord.cpp", FormPassWord);
USEFORM("FrmOrderCopy.cpp", FormOrderCopy);
USEFORM("FrmGetFieldFilter.cpp", FormGetFieldFilter);
USEFORM("FrmSelSimpleEh.cpp", FormSelSimpleEh);
USEFORM("FrmDateRange.cpp", FormDateRange);
USEFORM("DModT.cpp", DModT); /* TDataModule: File Type */
USEFORM("FrmFilter.cpp", FormFilter);
USEFORM("FrmDriverGraphDay.cpp", FormDriverGraphDay);
USEFORM("FrmDriverGraph.cpp", FormDriverGraph);
USEFORM("DModRep.cpp", DModReport); /* TDataModule: File Type */
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
			Application->CreateForm(__classid(TDModReport), &DModReport);
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
