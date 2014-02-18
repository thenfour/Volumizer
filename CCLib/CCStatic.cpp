

#include "stdafx.h"
#include "CCStatic.h"


HRESULT CCStatic::Create(PCWSTR wsz, HWND hParent, HINSTANCE hInstance, 
    RECT& prect, RECT& orect)
{
	CopyRect(&m_orect, &orect);
	CopyRect(&m_prect, &prect);

    m_hWnd = CreateWindowEx(
		0, L"STATIC", wsz, WS_CHILD, 0, 0, 1, 1,
		hParent, (HMENU)this->GetId(), hInstance, 0);

    SetFont();
    Show(TRUE);
	Size();

	return S_OK;
}


