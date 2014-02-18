

#include "stdafx.h"

void InitResModule()
{
    g_hRes = LoadLibrary(L"ccres.dll");
    if(g_hRes == 0)
    {
        MessageBox(0, L"Unable to load the resource pack.  Please reinstall the application.", L"One Light Volumizer", MB_OK);
    }
}

void UninitResModule()
{
    if(g_hRes) FreeLibrary(g_hRes);
    g_hRes = 0;
}

