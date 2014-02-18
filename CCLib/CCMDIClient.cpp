

#include "stdafx.h"
#include "CCMDIClient.h"
#include "CCMDIChild.h"
#include <tchar.h>
#include <stdio.h>

CCMDIClient::CCMDIClient()
{
    this->Class[0] = 0;
}


CCMDIClient::~CCMDIClient()
{
}


HRESULT CCMDIClient::Create(HWND hParent, HINSTANCE hInstance, RECT prect, RECT orect,
                         WNDPROC ChildProc)
{
    CLIENTCREATESTRUCT ccs;

    CopyRect(&this->prect, &prect);
    CopyRect(&this->orect, &orect);

    /*
        Register the class for the child windows.
    */
 	_stprintf(this->Class, _T("MDI Child 0x%X"), this->GetId());

    WNDCLASS wc = {0};
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
    wc.lpfnWndProc = ChildProc;
    wc.cbWndExtra = 0;
	wc.lpszClassName = this->Class;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&wc);

    this->hParent = hParent;
    this->hInstance = hInstance;

    ccs.hWindowMenu = 0;
    ccs.idFirstChild = 0;

    this->hWnd = CreateWindowEx(0, _T("MDICLIENT"), NULL, 
        WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL, 
        0, 0, 0, 0, hParent, (HMENU)0, hInstance, &ccs); 

    if(this->hWnd == 0) return E_FAIL;

    this->Size();

    return S_OK;
}



HRESULT CCMDIClient::CreateChild(CCMDIChild** pOut, const TCHAR* tszTitle, long lParam, RECT prect, RECT orect)
{
    CCMDIChild* pNew = new CCMDIChild;
    HRESULT hr;

    *pOut = pNew;

    hr = pNew->Create(this, tszTitle, lParam, prect, orect);

    if(FAILED(hr))
    {
        *pOut = NULL;
        return E_FAIL;
    }


    return S_OK;
}

