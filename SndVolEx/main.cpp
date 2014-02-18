

#include "stdafx.h"
#include "CApp.h"


HINSTANCE g_hInstance;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR wszCmdLine, int)
{
    g_hInstance = hInstance;

    InitResModule();

    INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX), ICC_TREEVIEW_CLASSES };
    InitCommonControlsEx(&icc);

    CApp* p = new CApp;

    p->Entry(wszCmdLine);

    delete p;

    UninitResModule();

    return 0;
}



