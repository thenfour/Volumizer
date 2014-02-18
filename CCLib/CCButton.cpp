

#include "stdafx.h"
#include "CCButton.h"


CCButton::CCButton()
{
    m_hBitmap = NULL;
}


CCButton::~CCButton()
{
    _FreeBitmap();
}


HRESULT CCButton::Click()
{
	return SendMessage(m_hWnd, BM_CLICK, 0, 0);
}


HRESULT CCButton::Create(PCWSTR wszText, HWND hParent, HINSTANCE hInstance, 
						 RECT& prect, RECT& orect)
{
	CopyRect(&m_orect, &orect);
	CopyRect(&m_prect, &prect);

	m_hWnd = CreateWindowEx(0, L"BUTTON", wszText, WS_CHILD, 0, 0, 1, 1,
		hParent, (HMENU)this->GetId(), hInstance, 0);

    SetFont();
    Size();
    Show(TRUE);

    return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CCButton::CreateGroup(PCWSTR wszText, HWND hParent, 
							  HINSTANCE hInstance, 
							  RECT& prect, RECT& orect)
{
	CopyRect(&m_orect, &orect);
	CopyRect(&m_prect, &prect);
 
	m_hWnd = CreateWindowEx(0, L"BUTTON", wszText, WS_CHILD | BS_GROUPBOX, 
        0, 0, 1, 1, hParent, (HMENU)this->GetId(), hInstance, 0);

	return S_OK;
}


HRESULT CCButton::SetActive(BOOL b)
{
    if(b == FALSE)
    {
        AddStyle(WS_DISABLED);
    }
    else
    {
        RemoveStyle(WS_DISABLED);
    }

    Invalidate();

    return S_OK;
}


HRESULT CCButton::SetBitmap(HINSTANCE hInst, UINT uResid)
{
    _FreeBitmap();

    // Set our state so that we don't have borders and stuff.
    AddStyle(BS_BITMAP | BS_FLAT);
    RemoveStyle(WS_BORDER | BS_TEXT);

    m_hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(uResid));

    if(m_hBitmap)
    {
        SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBitmap);
    }

    return S_OK;
}


void CCButton::_FreeBitmap()
{
    if(m_hBitmap)
    {
        DeleteObject(m_hBitmap);
        m_hBitmap = 0;
    }
}

