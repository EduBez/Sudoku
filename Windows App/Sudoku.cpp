#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

USEFORM("View.cpp", View);

//
//  Main Entry Point
//
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
        Application->Initialize();
        Application->MainFormOnTaskBar = true;

        Application->CreateForm(__classid(TView), &View);
        Application->Run();
    }
    catch (Exception& e)
    {
        Application->ShowException(&e);
    }
    catch (...)
    {
        try
        {
            throw Exception("");
        }
        catch (Exception& e)
        {
            Application->ShowException(&e);
        }
    }
    return 0;
}

