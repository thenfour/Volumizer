

#include "stdafx.h"
#include "ComboBox.h"


HRESULT CComboBox::Create(HWND hParent, RECT& prect, RECT& orect)
{
	CopyRect(&m_orect, &orect);
	CopyRect(&m_prect, &prect);

    m_hWnd = CreateWindowEx(
		0, L"COMBOBOX", L"", WS_CHILD | CBS_DROPDOWNLIST, 0, 0, 1, 1,
		hParent, (HMENU)this->GetId(), 0, 0);

    SetFont();
    Show(TRUE);
	Size();

	return S_OK;
}


HRESULT CComboBox::AddString(PCWSTR wsz, int* pi, void* pUser)
{
    int i = 0;

    i = SendMessage(m_hWnd, CB_ADDSTRING, 0, (LPARAM)wsz);
    SendMessage(m_hWnd, CB_SETITEMDATA, (WPARAM)i, (LPARAM)pUser);

    if(i == CB_ERR) return E_FAIL;
    if(pi) *pi = i;

    return S_OK;
}


int CComboBox::FindString(PCWSTR wsz)
{
    int i = SendMessage(m_hWnd, CB_FINDSTRINGEXACT, 0, (LPARAM)wsz);
    if(i == CB_ERR) return -1;
    return i;
}


int CComboBox::Count()
{
    int c = SendMessage(m_hWnd, CB_GETCOUNT, 0, 0);
    if(c == CB_ERR) return -1;
    return c;
}


int CComboBox::FindUserData(void* pUser)
{
    int i = 0;
    int c = Count();

    for(i=0;i<c;i++)
    {
        if(GetUserData(i) == pUser) return i;
    }

    return -1;
}


HRESULT CComboBox::SelectUserData(void* pUser)
{
    int i = FindUserData(pUser);
    if(i == -1) return E_FAIL;
    return SelectIndex(i);
}


HRESULT CComboBox::SelectString(PCWSTR wsz)
{
    if(CB_ERR == SendMessage(m_hWnd, CB_SELECTSTRING, (WPARAM)0, (LPARAM)wsz)) return E_FAIL;
    return S_OK;
}


HRESULT CComboBox::SelectIndex(int i)
{
    if(CB_ERR == SendMessage(m_hWnd, CB_SETCURSEL, (WPARAM)i, (LPARAM)0)) return E_FAIL;
    return S_OK;
}


HRESULT CComboBox::GetItemData(int i, OUT PWSTR wsz, IN OUT int* pccSize, 
                               OUT void** ppUser)
{
    int nLen = GetStringLen(i)+2;
    if(nLen == -1) return E_FAIL;

    if(ppUser)
    {
        *ppUser = GetUserData(i);
    }

    if(wsz && pccSize)
    {
        WCHAR* wszTemp = 0;
        wszTemp = (WCHAR*)malloc(sizeof(WCHAR)*(nLen));
        SendMessage(m_hWnd, CB_GETLBTEXT, (WPARAM)i, (LPARAM)wszTemp);
        wcsncpy(wsz, wszTemp, *pccSize);
        free(wszTemp);
    }

    if(pccSize)
    {
        *pccSize = nLen;
    }

    return E_FAIL;
}


void* CComboBox::GetUserData(int i)
{
    return (void*)SendMessage(m_hWnd, CB_GETITEMDATA, (WPARAM)i, 0);
}


int CComboBox::GetStringLen(int i)
{
    return (int)SendMessage(m_hWnd, CB_GETLBTEXTLEN, (WPARAM)i, 0);
}


int CComboBox::GetSelectedIndex()
{
    return (int)SendMessage(m_hWnd, CB_GETCURSEL, 0, 0);
}


