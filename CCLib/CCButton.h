

#pragma once


#include "global.h"
#include <windows.h>
#include "CCControl.h"


//////////////////////////////////////////////////////////////////////////////
class CCEXPORT CCButton : public CCControl
{
public:
	CCButton();
	~CCButton();

	HRESULT Create(PCWSTR, HWND, HINSTANCE, RECT& prect, RECT& orect);
	HRESULT CreateGroup(PCWSTR, HWND, HINSTANCE, RECT& prect, RECT& orect);
	HRESULT Click();
    HRESULT SetBitmap(HINSTANCE hInstance, UINT uResid);
    HRESULT SetActive(BOOL b);

private:

    void _FreeBitmap();

    HBITMAP m_hBitmap;
};


