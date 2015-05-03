//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("FrmPassWord.cpp", FormPassWord);
USEFORM("FrmOrderCopy.cpp", FormOrderCopy);
USEFORM("FrmSelSimpleEh.cpp", FormSelSimpleEh);
USEFORMNS("FrmTrans.cpp",XXX, FormTrans);
USEFORM("DModT.cpp", DModT); /* TDataModule: File Type */
USEFORM("FrmDriverGraph.cpp", FormDriverGraph);
USEFORM("FrmGetFieldFilter.cpp", FormGetFieldFilter);
USEFORM("FrmFilter.cpp", FormFilter);
USEFORM("FrmDriverGraphDay.cpp", FormDriverGraphDay);
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
