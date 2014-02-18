

#include "stdafx.h"
#include "CCCheckBox.h"


CCCheckBox::CCCheckBox()
{
}


CCCheckBox::~CCCheckBox()
{
}


HRESULT CCCheckBox::Create(PCWSTR wszCaption, HWND hParent, RECT& prect, RECT& orect, int nStates, BOOL bAuto)
{
	CopyRect(&m_orect, &orect);
	CopyRect(&m_prect, &prect);

    DWORD dwStyle = BS_CHECKBOX | WS_CHILD;

    if((nStates == 2) && (bAuto == TRUE))
    {
        dwStyle |= BS_AUTOCHECKBOX;
    }
    else if((nStates == 2) && (bAuto == FALSE))
    {
        //dwStyle |= BS_AUTOCHECKBOX;
    }
    else if((nStates == 3) && (bAuto == TRUE))
    {
        dwStyle |= BS_3STATE | BS_AUTOCHECKBOX;
    }
    else if((nStates == 3) && (bAuto == FALSE))
    {
        dwStyle |= BS_3STATE;
    }
    else
    {
        return E_FAIL;
    }

    m_hWnd = CreateWindowEx(0, L"BUTTON", wszCaption, dwStyle, 
        0, 0, 0, 0, hParent, (HMENU)GetId(), 0, 0);

    if(!m_hWnd) return E_FAIL;

    SetFont();
    Size();
    Show(TRUE);

    return S_OK;
}


HRESULT CCCheckBox::Toggle()
{
    return S_OK;
}


HRESULT CCCheckBox::SetCheck(UINT n)
{
    SendMessage(m_hWnd, BM_SETCHECK, n, 0);
    return S_OK;
}


HRESULT CCCheckBox::SetStates(int n, BOOL bAuto, BOOL bAuto3)
{
    DWORD dwAddStyle = (bAuto == TRUE ? BS_AUTOCHECKBOX : 0) | (bAuto3 == TRUE ? BS_AUTO3STATE : 0);
    AddStyle(dwAddStyle);

    switch(n)
    {
    case 2:
        RemoveStyle(BS_3STATE);
        return S_OK;
    case 3:
        AddStyle(BS_3STATE);
        return S_OK;
    }

    return E_FAIL;
}


HRESULT CCCheckBox::SetActive(BOOL b)
{
    EnableWindow(m_hWnd, b);
    return S_OK;
}


int CCCheckBox::GetCheck()
{
    return (int)SendMessage(m_hWnd, BM_GETCHECK, 0, 0);
}



