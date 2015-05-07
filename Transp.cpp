//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------



USEFORM("FrmPassWord.cpp", FormPassWord);
USEFORM("FrmOrderCopy.cpp", FormOrderCopy);
USEFORM("FrmGetFieldFilter.cpp", FormGetFieldFilter);
USEFORMNS("FrmTrans.cpp",XXX, FormTrans);
USEFORM("FrmSelSimpleEh.cpp", FormSelSimpleEh);
USEFORM("FrmFilter.cpp", FormFilter);
USEFORM("DModT.cpp", DModT); /* TDataModule: File Type */
USEFORM("DModRep.cpp", DModReport); /* TDataModule: File Type */
USEFORM("FrmDriverGraphDay.cpp", FormDriverGraphDay);
USEFORM("FrmDriverGraph.cpp", FormDriverGraph);
USEFORM("FrmDateRange.cpp", FormDateRange);
USEFORM("FrmDriverRep.cpp", FormDriverRep);
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
