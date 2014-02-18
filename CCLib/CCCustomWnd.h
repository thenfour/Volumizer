

#pragma once


#include <windows.h>
#include "global.h"
#include "CCControl.h"


//////////////////////////////////////////////////////////////////////////////
class CCEXPORT CCCustomWnd : public CCControl
{
public:
	CCCustomWnd();
	~CCCustomWnd();

    HRESULT Create(PCWSTR wszName, HWND hParent, WNDPROC WndProc, HINSTANCE hInstance,
        RECT prect, RECT orect, DWORD dwStyle, PVOID lparam, int iIcon);

	HRESULT SetIcon(HICON hIcon);
	void Destroy();

private:

	WCHAR m_wszClass[MAX_PATH];
};


