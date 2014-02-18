

#include "stdafx.h"
#include "CCTreeView2s.h"


#define CCTREEVIEW2S_PROP L"CCTV2S"


CCTreeView2s::CCTreeView2s()
{
    m_pOldProc = 0;
}


CCTreeView2s::~CCTreeView2s()
{
}


HRESULT CCTreeView2s::Create(HWND hParent, HINSTANCE hInstance, 
                             RECT& prect, RECT& orect)
{
    CopyRect(&m_prect, &prect);
    CopyRect(&m_orect, &orect);

    m_hInstance = hInstance;

    m_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, WC_TREEVIEW, L"CCTreeView2s", 
        WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT,
        0, 0, 0, 0, hParent, (HMENU)m_id, hInstance, 0);

    if(!m_hWnd) return E_FAIL;

    _InitWindow();

    Show(TRUE);

    return S_OK;
}


void CCTreeView2s::Destroy()
{
    this->CCTreeView::Destroy();

    // Destroy our check image list.
    m_Checks.Destroy();
}


HRESULT CCTreeView2s::TakeOver(HWND hWnd)
{
    CCControl::TakeOver(hWnd);

    // Set the prop and subclass the window.
    _InitWindow();

    return S_OK;
}


void CCTreeView2s::_InitWindow()
{
    HWND hParent;

    hParent = GetParent();

    SetProp(hParent, CCTREEVIEW2S_PROP, (HANDLE)this);

    // Subclass the window.
    m_pOldProc = (WNDPROC)GetWindowLongPtr(hParent, GWLP_WNDPROC);
    SetWindowLongPtr(hParent, GWLP_WNDPROC, (LONG_PTR)CCTreeView2s::WndProc);

    // Set up the check marks.
    m_Checks.CreateFromResource(g_hRes, MAKEINTRESOURCE(IDB_CHECKS), 13, CLR_NONE);
    TreeView_SetImageList(m_hWnd, m_Checks, TVSIL_STATE);

    return;
}


LRESULT CALLBACK CCTreeView2s::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CCTreeView2s* pThis = (CCTreeView2s*)GetProp(hWnd, CCTREEVIEW2S_PROP);

    switch(uMsg)
    {
    case WM_NOTIFY:
        {
            NMHDR* pnmh = (NMHDR*)lParam;

            switch(pnmh->code)
            {
            case TVN_KEYDOWN:
                {
                    NMTVKEYDOWN* pnmtv = (NMTVKEYDOWN*)lParam;

	                if(pnmtv->wVKey == VK_SPACE)
	                {
		                HTREEITEM hItem = TreeView_GetSelection(pnmtv->hdr.hwndFrom);
		                pThis->SetCheck(hItem, CT_TOGGLE);
		                return TRUE;
	                }

                    break;
                }
            case NM_CLICK:
                {
	                UINT uFlags = 0;
                    HWND hTree = pnmh->hwndFrom;
                    TVHITTESTINFO hti;

                    GetCursorPos(&hti.pt);
                    ScreenToClient(pnmh->hwndFrom, &hti.pt);

                    TreeView_HitTest(hTree, &hti);
	                HTREEITEM hItem = hti.hItem;

	                if(hti.flags & TVHT_ONITEMSTATEICON)
	                {
		                pThis->SetCheck(hItem, CT_TOGGLE);
		                return TRUE;
	                }

                    break;
                }
            }

            break;
        }
    default:
        {
            break;
        }
    }

    return pThis->m_pOldProc(hWnd, uMsg, wParam, lParam);
}


HTREEITEM CCTreeView2s::GetFirstCheckedItem()
{
    HTREEITEM hItem = TreeView_GetRoot(m_hWnd);
    int iImage = 0;

    while(hItem != NULL)
    {
        // Get the item's image.
        iImage = GetStateImage(hItem);

        // If it's checked, we're all good; just return.
        if(iImage == CS_FULLCHECK)
        {
            return hItem;
        }

        hItem = GetNextItem(hItem);
    }

    // No matches.
    return 0;
}


HTREEITEM CCTreeView2s::GetNextCheckedItem(HTREEITEM hItem)
{
    hItem = GetNextItem(hItem);

    while(hItem != NULL)
    {
        int iImage = GetStateImage(hItem);
        if(iImage == CS_FULLCHECK) return hItem;
        hItem = GetNextItem(hItem);
    }

    return 0;
}


BOOL CCTreeView2s::SetCheck(HTREEITEM hItem, TVCheckType nCheck)
{
    UINT nState = 0;

    if(hItem == NULL) return FALSE;

    nState = GetStateImage(hItem);

    // For toggling, let's figure out what we'll actually be doing.
    if(nCheck == CT_TOGGLE)
    {
        switch(nState)
        {
        case CS_UNCHECKABLE:
            return FALSE;
        case CS_NOCHECK:
            nCheck = CT_CHECK;
            break;
        case CS_HALFCHECK:
            nCheck = CT_UNCHECK;
            break;
        case CS_FULLCHECK:
            nCheck = CT_UNCHECK;
            break;
        }
    }

    // Check our own node.
    switch(nCheck)
    {
    case CT_UNCHECKABLE:
        {
            SetStateImage(hItem, CS_UNCHECKABLE);
            break;
        }
    case CT_CHECK:
        {
            SetStateImage(hItem, CS_FULLCHECK);
            break;
        }
    case CT_UNCHECK:
        {
            SetStateImage(hItem, CS_NOCHECK);
            break;
        }
    }

    return TRUE;
}


HTREEITEM CCTreeView2s::InsertItemChecked(PCWSTR wszItem,
                     HTREEITEM hParent,
                     HTREEITEM hInsertAfter,
                     LPARAM lParam)
{
    return InsertItemWithState(wszItem, CS_FULLCHECK, hParent, hInsertAfter, lParam);
}


HTREEITEM CCTreeView2s::InsertItemWithImageChecked(PCWSTR wszItem, int nImage, int nSelectedImage,
                     HTREEITEM hParent,
                     HTREEITEM hInsertAfter,
                     LPARAM lParam)
{
    return InsertItemWithState(wszItem, CS_FULLCHECK, nImage, nSelectedImage,
        hParent, hInsertAfter, lParam);
}


BOOL CCTreeView2s::IsItemChecked(HTREEITEM hItem)
{
    switch(GetStateImage(hItem))
    {
    case CS_FULLCHECK:
        return TRUE;
    case CS_NOCHECK:
    case CS_UNCHECKABLE:
        return FALSE;
    }

    return FALSE;
}
