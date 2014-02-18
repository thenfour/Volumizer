

#include "stdafx.h"
#include "CCToolTip.h"


CCToolTip::CCToolTip()
{
    this->hOwner = NULL;
    this->hWnd = NULL;
}


CCToolTip::~CCToolTip()
{
}


HRESULT CCToolTip::Create(HINSTANCE hInstance, HWND hParent)
{
    this->hWnd = CreateWindowEx(
        NULL, TOOLTIPS_CLASS, NULL,
        WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        hParent, NULL, hInstance,
        NULL);

    SetWindowPos(this->hWnd, HWND_TOPMOST,0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    this->hOwner = hParent;

    return S_OK;
}


HRESULT CCToolTip::AddTool(HWND hWnd, CCString Text, LPARAM lParam)
{
    TOOLINFO ti;
    ti.cbSize = sizeof(ti);
    ti.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
    ti.hwnd = this->hOwner;
    ti.uId = (UINT_PTR)hWnd;
    ti.lpszText = (PTSTR)Text;
    ti.lParam = lParam;

    if(SendMessage(this->hWnd, TTM_ADDTOOL, 0, (LPARAM)&ti) == FALSE)
    {
        return E_FAIL;
    }

    return S_OK;
}





