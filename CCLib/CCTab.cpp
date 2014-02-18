/*
    CREATED: Feb. 21, 2001 carlco
*/


#include "stdafx.h"
#include "CCTab.h"
#include <stdio.h>
#include <tchar.h>


/*
    Feb. 21, 2001 carlco
*/
CCTab::CCTab()
{
    for(int i = 0;i<MAX_TAB_ATTACHMENTS;i++)
    {
        this->Attachments[i] = NULL;
    }
}


/*
    Feb. 21, 2001 carlco
*/
CCTab::~CCTab()
{
}


/*
    Feb. 21, 2001 carlco
*/
HRESULT CCTab::Create(HWND hParent, RECT prect, RECT orect, int nTabs, TAB_ITEM* pTabs)
{
    this->hParent = hParent;
    CopyRect(&this->prect, &prect);
    CopyRect(&this->orect, &orect);

    this->hInstance = (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE);

    this->hWnd = CreateWindowExW(
        0,
        WC_TABCONTROLW, L"", 
        WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
        0, 0, 1, 1, 
        hParent, (HMENU)this->id, this->hInstance, NULL); 

    TCITEM tie;
    int i;

    tie.mask = TCIF_TEXT | TCIF_IMAGE | TCIF_PARAM; 
    tie.iImage = -1; 
    tie.lParam = 0;

    for (i = 0; i < nTabs; i++)
    {
        tie.pszText = (PTSTR)pTabs[i].wszTitle;
        tie.lParam = (LPARAM)pTabs[i].dwUser;

        if (TabCtrl_InsertItem(this->hWnd, i, &tie) == -1)
        {
            DestroyWindow(this->hWnd); 
			this->hWnd = 0;
            return E_FAIL; 
        } 
    }

    SendMessage(this->hWnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

    return S_OK;
}


/*
    Feb. 21, 2001 carlco
*/
HRESULT CCTab::AddTabs(TAB_ITEM* pTabs, int nTabs)
{
    TCITEMW tie;
    int i;
    int n = TabCtrl_GetItemCount(this->hWnd);

    tie.mask = TCIF_TEXT | TCIF_IMAGE | TCIF_PARAM; 
    tie.iImage = -1; 
    tie.lParam = 0;

    for (i = 0; i < nTabs; i++)
    {
        tie.pszText = (PWSTR)pTabs[i].wszTitle;
        tie.lParam = (LPARAM)pTabs[i].dwUser;

        TabCtrl_InsertItem(this->hWnd, i + n, &tie);
    }

    return S_OK;
}


/*
    Feb. 21, 2001 carlco
*/
HRESULT CCTab::Attach(CCControl* p)
{
    if(p == NULL) return E_FAIL;

    //add it to the list.
    int i = 0;
    while(1)
    {
        if(this->Attachments[i] == NULL) break;
        i++;
        if(i == MAX_TAB_ATTACHMENTS) return E_FAIL;//no more attachments allowed.
    }

    //i is now the index of the next attachment
    this->Attachments[i] = p;

    return S_OK;
}




/*
    Feb. 21, 2001 carlco
    This function overrides TLControl::Size().  It sizes all attached windows
    and then calls TLControl::Size();
*/
LRESULT CCTab::Size(){

    if(this->hWnd == NULL) return 0;

    this->CCControl::Size();

    RECT rcItem;
    SendMessage(this->hWnd, TCM_GETITEMRECT, 0, (LPARAM)&rcItem);

    int i = 0;
    RECT rcTab;
    RECT rcTabOriginal;
    CCControl * p = NULL;
    GetClientRect(this->hWnd, &rcTab);
    GetClientRect(this->hWnd, &rcTabOriginal);
    //TabCtrl_AdjustRect(this->hWnd, FALSE, &rcTab);
    rcTab.top += rcItem.bottom;
    InflateRect(&rcTab, -4, -4);

    while(1)
    {

        p = this->Attachments[i];
        if(p == NULL) break;

        //size the attachment//////////////////////////

        RECT rcNew;
        RECT orect;
        RECT prect;
        p->GetPlacement(&prect, &orect);
        this->ControlRectToRect(
            &rcNew, &prect, &orect, &rcTab);

        MoveWindow(p->GethWnd(),
            rcNew.left,
            rcNew.top,
            rcNew.right - rcNew.left, 
            rcNew.bottom - rcNew.top, 
            TRUE);
        ///////////////////////////////////////////////
        i++;
        if(i == MAX_TAB_ATTACHMENTS) return E_FAIL;//no more attachments allowed.
    }

    return 0;

}


void CCTab::RemoveLParam(DWORD dw)
{
    // Find the item first.
    TCITEMW tcItem;
    int i = 0;

    while(1)
    {
        tcItem.mask = TCIF_PARAM;

        if(TabCtrl_GetItem(this->hWnd, i, &tcItem) == FALSE)
        {
            // Error - not found.
            return;
        }

        if((DWORD)tcItem.lParam == dw) break;
        i++;
    }

    // We found it.
    SendMessage(this->hWnd, TCM_DELETEITEM, i, 0);
}


void CCTab::SelectLParam(DWORD dw)
{
    // Find the item first.
    TCITEMW tcItem;
    int i = 0;

    while(1)
    {
        tcItem.mask = TCIF_PARAM;

        if(TabCtrl_GetItem(this->hWnd, i, &tcItem) == FALSE)
        {
            // Error - not found.
            return;
        }

        if((DWORD)tcItem.lParam == dw) break;
        i++;
    }

    // We found it.
    SendMessage(this->hWnd, TCM_SETCURSEL, i, 0);
}


DWORD CCTab::GetLParam(int i)
{
    TCITEMW tcItem;

    tcItem.mask = TCIF_PARAM;

    TabCtrl_GetItem(this->hWnd, i, &tcItem);

    return tcItem.lParam;
}


void CCTab::Select(int i)
{
    SendMessage(this->hWnd, TCM_SETCURSEL, i, 0);
}


