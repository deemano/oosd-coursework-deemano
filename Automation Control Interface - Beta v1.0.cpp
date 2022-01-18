//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
//---------------------------------------------------------------------------
USEFORM("..\..\..\aci_v1.0\MainStartWindow.cpp", startWin);
USEFORM("..\..\..\aci_v1.0\Login.cpp", LoginWin);
USEFORM("..\..\..\aci_v1.0\LandingWindow.cpp", LandingWin);
USEFORM("..\Register.cpp", RegisterWin);
USEFORM("..\TempDashboard.cpp", DashboardTemp);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TstartWin), &startWin);
		Application->CreateForm(__classid(TLandingWin), &LandingWin);
		Application->CreateForm(__classid(TLoginWin), &LoginWin);
		Application->CreateForm(__classid(TRegisterWin), &RegisterWin);
		Application->CreateForm(__classid(TDashboardTemp), &DashboardTemp);
		Application->Run();
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
