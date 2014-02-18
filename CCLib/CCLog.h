

#pragma once


#include <windows.h>
#include "global.h"
#include "CCString.h"


/*
    This takes a simple filename like "the.log" and puts it on the
    path that the executable was run from, so it's in the right
    directory.
*/
void CCEXPORT GetLogFileName(CCString* pFullName, const TCHAR* tszFileName);


class CCEXPORT CCLog
{
public:
    CCLog();
    ~CCLog();

    void SetWindow(HWND hEdit);

    /*
        The file will automatically be closed when the app is shut down.
        Only 1 log may be open at a time with this class. (per class).
    */
    HRESULT SetFile(PCWSTR FileName);

    void AddEntry(HRESULT hr, PCWSTR tszFormat, ...);
    void AddEntry(PCWSTR tszFormat, ...);
    void _AddEntry(PCWSTR tsz);

    void Refresh();

private:

    HRESULT EnsureFileOpened();
    HANDLE hFile;
    BOOL bFileError;// TRUE when we couldn't open the file.

    HWND hEdit;
    CCString HiddenText;// This will be appended to Log when Refresh() is called.
    CCString Log;

    CCString sFileName;
};


