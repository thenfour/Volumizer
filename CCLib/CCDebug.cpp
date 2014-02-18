/*
    2002-03-29 Carl Corcoran

    This stuff used to be in global.cpp, but I've now moved them
    to this file and added logging capabilities and revised some
    thing to make it easier to do an application log.
*/

#include "stdafx.h"
#include "ccdebug.h"
#include "ccstring.h"
#include "cclog.h"
#include <shlwapi.h>
#include <stdio.h>


// Global log.
CCLog __g_Log;
BOOL __g_bLogOpened = FALSE;


#ifdef NDEBUG
#else

HRESULT CCOpenDebugLog(PCWSTR wszFileName)
{
    CCString s = wszFileName;

    if(s.Path_IsRelative() == TRUE)
    {
        GetModuleFileName(NULL, s.GetBuffer(MAX_PATH), MAX_PATH);
        s.Path_StripToPath();
        s.Path_Append(wszFileName);
    }
    
    __g_bLogOpened = TRUE;

    return __g_Log.SetFile(s);
}


HRESULT CCEXPORT CCCloseDebugLog()
{
    __g_bLogOpened = FALSE;
    return S_OK;
}


void __cdecl MsgBoxf(PCWSTR String, ...)
{
    va_list argptr;

    va_start(argptr, String);
    MsgBoxfv(String, argptr);
    va_end(argptr);
}


void MsgBoxfv(PCWSTR String, va_list argptr)
{
    CCString Buf;

    Buf.FormatvW(String, argptr);

    if(__g_bLogOpened == TRUE)
    {
        __g_Log._AddEntry(Buf);
    }

    MessageBoxW(0, Buf, 0, MB_OK | MB_ICONASTERISK);
}


void odsfv(PCWSTR wszFunction, PCWSTR wszFormat, va_list argptr)
{
    CCString s;
    s.FormatvW(wszFormat, argptr);
    _odsf(wszFunction, s);
    return;
}


void _odsf(PCWSTR wszFunction, PCWSTR wszString)
{
    CCString sMsg;

    sMsg.FormatW(L"[ %-20.20s ]  ", wszFunction);
    sMsg.cat(wszString);

    if(__g_bLogOpened == TRUE)
    {
        __g_Log._AddEntry(sMsg);
    }

    OutputDebugStringW(sMsg);
    OutputDebugStringW(L"\n");
}


void __cdecl odsf(PCWSTR wszFunction, PCWSTR wszFormat, ...)
{
    va_list argptr;

    va_start(argptr, wszFormat);
    odsfv(wszFunction, wszFormat, argptr);
    va_end(argptr);
}


/*
	010319 Carl Corcoran
*/
void odsr(PCWSTR wszFunction, PCWSTR wszString, PRECT prc)
{
	WCHAR wszBuf[1024];
	swprintf(wszBuf, L"%s  (%d,%d)-(%d,%d)", wszString,
		prc->left, prc->top, prc->right, prc->bottom);

	_odsf(wszFunction, wszBuf);
}



#endif// defined NDEBUG