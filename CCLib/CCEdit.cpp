

#include "stdafx.h"
#include "CCEdit.h"
#include <tchar.h>

/*
    Allocate 64k at a time
*/
#define LOCAL_EDIT_BUFFER 64000


CCEditBox::CCEditBox()
{
}


CCEditBox::~CCEditBox()
{
}


HRESULT CCEditBox::CreateMultiline(HWND hParent, HINSTANCE hInstance, 
                                   RECT& prect, RECT& orect)
{
    CopyRect(&m_prect, &prect);
    CopyRect(&m_orect, &orect);
    m_hInstance = hInstance;

    m_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
        ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_HSCROLL | 
        WS_VSCROLL | WS_CHILD | WS_VISIBLE | ES_MULTILINE,
        0, 0, 1, 1, hParent, (HMENU)m_id, hInstance, NULL);

    SetFont();
    Size();
    Show(TRUE);

    return S_OK;
}


HRESULT CCEditBox::Create(HWND hParent, HINSTANCE hInstance, RECT& prect, RECT& orect)
{
    CopyRect(&m_prect, &prect);
    CopyRect(&m_orect, &orect);
    m_hInstance = hInstance;

    m_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", 
        WS_CHILDWINDOW | ES_READONLY | WS_VISIBLE, 
        0, 0, 1, 1, hParent, (HMENU)m_id,
        hInstance, NULL);

    SetFont();
    Size();
    Show(TRUE);

    return S_OK;

}


HRESULT CCEditBox::Append(PCWSTR wszText)
{
    int nStart = GetWindowTextLength(m_hWnd);
    SendMessage(m_hWnd, EM_SETSEL, nStart, nStart);
    SendMessage(m_hWnd, EM_REPLACESEL, NULL, (LPARAM)wszText);

    return S_OK;
}


HRESULT CCEditBox::SetReadOnly(BOOL b)
{
    SendMessage(m_hWnd, EM_SETREADONLY, b, 0);
    return S_OK;
}


