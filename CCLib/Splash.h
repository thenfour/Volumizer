

#pragma once


#include "CCImageList.h"


#define SLF_FILE 0x00000001
#define SLF_RESOURCE 0x00000002


//////////////////////////////////////////////////////////////////////////////
class CCEXPORT CCSplash : public CCControl
{
public:
	CCSplash();
	~CCSplash();

    /*
        hBitmap will be automatically deleted by this control.
    */
    HRESULT Create(POINT pStatic, COLORREF color, CCString FileName);
    HRESULT Create(POINT pStatic, COLORREF color, UINT idResource, HINSTANCE hInstance);

    HRESULT SetStatusText(CCString s);
    void Destroy();

private:

    static void ThreadProc(PVOID p);
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HRESULT Draw(HDC dc);

    POINT pStatic;
    CCString sClass;
    COLORREF rgbStaticColor;

    CCImageList Images;
    int nImage;
    CCString sFileName;
    UINT idResource;
    DWORD dwLoadFrom;// SLF_RESOURCE | SLF_FILE
    CCString sStaticText;
    HINSTANCE user_hInstance;

    HANDLE hThread;
    DWORD dwThreadId;

    HANDLE hEventExit;
};


