#include <windows.h>
#include "..\DuiLib\UIlib.h"
#include"mainWindow.h"
#include"UIMessageBox.h"
using namespace DuiLib;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    HANDLE hMutex = CreateMutex(NULL, FALSE, _T("NB_HEXHANDLER_EX_MUTEX"));
    if (GetLastError() == ERROR_ALREADY_EXISTS){   
        if (hMutex)
            CloseHandle(hMutex);
        hMutex = NULL;
        return 0;
    }

    CPaintManagerUI::SetInstance(hInstance);

    
    //CDuiMessageBox duiFrame;
    CDuiFrameWnd duiFrame;
    //CsubWnd duiFrame;
    duiFrame.Create(NULL, _T("HexHandlerEx"), /*UI_WNDSTYLE_DIALOG*/WS_MINIMIZEBOX, WS_EX_WINDOWEDGE);
    duiFrame.CenterWindow();
    duiFrame.ShowModal();

    return 0;
}