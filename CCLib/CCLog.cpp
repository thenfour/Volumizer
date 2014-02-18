

#include "stdafx.h"
#include "CCLog.h"
#include "TraceErrorSys.h"
#include <tchar.h>
#include <shlwapi.h>

#ifdef NDEBUG


void CCEXPORT GetLogFileName(CCString* pFullName, PCWSTR wszFileName)
{
    WCHAR wszModuleName[MAX_PATH];

    // Get the module name
    GetModuleFileName(GetModuleHandle(NULL), wszModuleName, MAX_PATH);

    // Strip the filename off it.
    PathRemoveFileSpec(wszModuleName);

    PathAppend(wszModuleName, wszFileName);

    *pFullName = wszModuleName;

    return;
}


CCLog::CCLog(){}
CCLog::~CCLog(){}
HRESULT CCLog::EnsureFileOpened(){ return S_OK; }
void CCLog::_AddEntry(PCWSTR s){}
void CCLog::Refresh(){}
void CCLog::SetWindow(HWND hEdit){}
HRESULT CCLog::SetFile(PCWSTR FileName){ return S_OK; }
void CCLog::AddEntry(HRESULT hr, PCWSTR FormatString, ...){}
void CCLog::AddEntry(const TCHAR* FormatString, ...){}

#else


void CCEXPORT GetLogFileName(CCString* pFullName, PCWSTR wszFileName)
{
    WCHAR wszModuleName[MAX_PATH];

    // Get the module name
    GetModuleFileName(GetModuleHandle(NULL), wszModuleName, MAX_PATH);

    // Strip the filename off it.
    PathRemoveFileSpec(wszModuleName);

    PathAppend(wszModuleName, wszFileName);

    *pFullName = wszModuleName;

    return;
}


CCLog::CCLog()
{
    this->hEdit = 0;
    this->HiddenText = L"";
    this->Log = L"";
    this->hFile = NULL;
    this->bFileError = FALSE;
    this->sFileName = L"";
}


CCLog::~CCLog()
{
    if(this->hFile)
    {
        CloseHandle(this->hFile);
    }
}


HRESULT CCLog::EnsureFileOpened()
{
    // Here we make sure that our file is opened and if not,
    // We'll open it and add a header entry.

    if(this->hFile != 0) return S_FALSE;
    if(this->bFileError == TRUE) return S_FALSE;

    this->hFile = CreateFile(this->sFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_ALWAYS, NULL, NULL);

    if(this->hFile == INVALID_HANDLE_VALUE || this->hFile == 0)
    {
        // Error.
        this->bFileError = TRUE;
        this->hFile = NULL;
        this->AddEntry(L"Error opening the log file \"%s\"", (PCWSTR)this->sFileName);

        return E_FAIL;
    }

    SetFilePointer(this->hFile, 0, 0, FILE_END);

    CCString sHeader;
    DWORD br;

    sHeader = 
        L"\r\n--------------------------------------------------------\r\n"
        L"        Log file opened successfully.\r\n"
        L"--------------------------------------------------------\r\n";
    WriteFile(this->hFile, (PCWSTR)sHeader, sHeader.len() * sizeof(WCHAR),
        &br, NULL);

    return S_OK;
}


void CCLog::_AddEntry(PCWSTR s)
{
    //
    //   [ Oct 31 22:19.13 ] asdfasdfasdfasdfasdfasdfasdf
    //
    CCString NewEntry;
    CCString Date;
    CCString Time;
    TCHAR tszDate[200];
    TCHAR tszTime[200];

    // Make sure that our log is open.
    this->EnsureFileOpened();

    SYSTEMTIME st;
    GetLocalTime(&st);
    GetDateFormat(LOCALE_USER_DEFAULT, NULL, &st, 
        _T("MMM dd"), tszDate, 200);
    Date = tszDate;

    GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, &st,
        _T("hh':'mm'.'ss"), tszTime, 200);
    Time = tszTime;

    NewEntry.FormatW(L"[%s %s] %s\r\n", (PCWSTR)Date, (PCWSTR)Time, (PCWSTR)s);
    this->HiddenText.cat(NewEntry);

    // Write it to teh file
    if(this->hFile != NULL)
    {
        DWORD br;
        WriteFile(this->hFile, (PCWSTR)NewEntry, NewEntry.len() * sizeof(WCHAR),
            &br, NULL);
    }
}


/*
    Puts the hidden text in the log and updates the edit box.
*/
void CCLog::Refresh()
{
    if(this->HiddenText.len() == 0) return;

    int nLen = GetWindowTextLength(this->hEdit);

    // Set the limit text to allow the text to be in there
    SendMessage(this->hEdit, EM_LIMITTEXT, nLen + this->HiddenText.len() + 10, 0); 
    // Then put the cursor at the end
    SendMessage(this->hEdit, EM_SETSEL, nLen, nLen);
    // And paste the new data in there.
    SendMessage(this->hEdit, EM_REPLACESEL, FALSE, (LPARAM)(PCWSTR)this->HiddenText);

    // And finally update our own text buffer.
    this->Log.cat(this->HiddenText);
    this->HiddenText = L"";
}


void CCLog::SetWindow(HWND hEdit)
{
    this->hEdit = hEdit;
    SetWindowText(hEdit, this->Log);
}


HRESULT CCLog::SetFile(PCWSTR FileName)
{
    this->sFileName = FileName;
    this->bFileError = FALSE;
    return this->EnsureFileOpened();
}


void CCLog::AddEntry(HRESULT hr, PCWSTR FormatString, ...)
{
    CCString NewEntry;
    CCString Err;
    va_list args;

    TraceErrorSys(&Err, hr);

    va_start(args, FormatString);
    NewEntry.FormatvW(FormatString, args);
    va_end(args);

    NewEntry.cat(Err);

    this->AddEntry(NewEntry);
}


void CCLog::AddEntry(const TCHAR* FormatString, ...)
{
    CCString NewEntry;
    va_list args;

    va_start(args, FormatString);
    NewEntry.FormatvW(FormatString, args);
    va_end(args);

    this->_AddEntry(NewEntry);
}



#endif
