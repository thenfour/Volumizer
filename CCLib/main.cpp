

#include "stdafx.h"


HINSTANCE g_hInstance;


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, PVOID)
{
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
        {
            g_hInstance = hInstance;
            break;
        }
    }
    return TRUE;
}


