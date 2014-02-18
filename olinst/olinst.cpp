// olinst.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "olinst.h"
#include <shlwapi.h>
#include "../sndvolex/cappsettings.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	}
    return TRUE;
}


void* olalloc(size_t nSize)
{
    return HeapAlloc(GetProcessHeap(), 0, nSize);
}

long install(char *sz)
{
    CAppSettings dat;
    FILETIME ft;

    // MAKE SURE THE DATE LAST MODIFIED IS ACCEPTABLE (IE the date before the install date)

    // get a FILETIME struct with the desired date.
    if(dat.ExistsInRegistry())
    {
        dat.GetSettings();
        SystemTimeToFileTime(&dat.m_InstallDate, &ft);
    }
    else
    {
        SYSTEMTIME st;
        GetLocalTime(&st);
        SystemTimeToFileTime(&st, &ft);
    }

    // go back 5 seconds just for some padding
    if(ft.dwLowDateTime >= 50000000)
    {
        ft.dwLowDateTime -= 50000000;// 10000 is a millisecond, 10,000,000 is a second
    }
    else
    {
        ft.dwLowDateTime = 0;
    }

    // sz is the path to volumizer.exe
    HANDLE hFile = CreateFile(sz, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    SetFileTime(hFile, 0, 0, &ft);
    CloseHandle(hFile);

    if(!dat.ExistsInRegistry())
    {
        dat.InitInstallation();
        dat.SaveSettings();
    }

    return 0;
}

void ninstall(HWND hwndParent, int string_size, char *variables, stack_t **stacktop)
{
    EXDLL_INIT()
    MessageBox(0, "attach debugger HERE", 0, MB_OK);
    char szFile[MAX_PATH];
    lstrcpy(szFile, getuservariable(21));
    lstrcat(szFile, "\\volumizer.exe");    
    install(szFile);
}

