

#include "stdafx.h"
#include "CCTreeView3s.h"


#define CCTREEVIEW3S_PROP L"CCTV3S"


CCTreeView3s::CCTreeView3s()
{
    m_pOldProc = 0;
}


CCTreeView3s::~CCTreeView3s()
{
}


HRESULT CCTreeView3s::Create(HWND hParent, HINSTANCE hInstance, 
                             RECT& prect, RECT& orect)
{
    m_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, WC_TREEVIEW, L"CCTreeView3s", 
        WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT,
        0, 0, 0, 0, hParent, (HMENU)m_id, hInstance, 0);

    if(!m_hWnd) return E_FAIL;

    _InitWindow();

    return S_OK;
}


void CCTreeView3s::Destroy()
{
    this->CCTreeView::Destroy();

    // Destroy our check image list.
    m_Checks.Destroy();
}


HRESULT CCTreeView3s::TakeOver(HWND hWnd)
{
    CCControl::TakeOver(hWnd);

    // Set the prop and subclass the window.
    _InitWindow();

    return S_OK;
}


void CCTreeView3s::_InitWindow()
{
    HWND hParent;

    hParent = GetParent();

    SetProp(hParent, CCTREEVIEW3S_PROP, (HANDLE)this);

    // Subclass the window.
    m_pOldProc = (WNDPROC)GetWindowLongPtr(hParent, GWLP_WNDPROC);
    SetWindowLongPtr(hParent, GWLP_WNDPROC, (LONG_PTR)CCTreeView3s::WndProc);

    // Set up the check marks.
    m_Checks.CreateFromResource(g_hRes, MAKEINTRESOURCE(IDB_CHECKS), 13, CLR_NONE);
    TreeView_SetImageList(m_hWnd, m_Checks, TVSIL_STATE);

    return;
}


LRESULT CALLBACK CCTreeView3s::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CCTreeView3s* pThis = (CCTreeView3s*)GetProp(hWnd, CCTREEVIEW3S_PROP);

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


HTREEITEM CCTreeView3s::GetFirstCheckedItem()
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

        if(iImage == CS_NOCHECK)
        {
            // We can just skip this node altogether because not
            // even any children are checked.

            // So get the next sibling.
            HTREEITEM hti = TreeView_GetNextItem(m_hWnd, hItem, TVGN_NEXT);

            if( hti == NULL )
            {
                // No more siblings... let's traverse up the tree to find the next
                // node.
                hItem = GetNextItem(hItem);
            }
            else
            {
                // We found a sibling; use it.
                hItem = hti;
            }
        }
        else
        {
            hItem = GetNextItem(hItem);
        }
    }

    // No matches.
    return 0;
}



BOOL CCTreeView3s::SetCheck(HTREEITEM hItem, TVCheckType nCheck)
{
    UINT nState = 0;

    if(hItem == NULL) return FALSE;

    nState = GetStateImage(hItem);

    // For toggling, let's figure out what we'll actually be doing.
    if(nCheck == CT_TOGGLE)
    {
        switch(nState)
        {
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
            break;
        }
    case CT_CHECK:
        {
            // 1) Check this and all its children.
            SetChildChecks(hItem, CS_FULLCHECK);

            // 2) Also tell all parents that they're atleast half checked.
            HTREEITEM hParent = TreeView_GetParent(m_hWnd, hItem);

            while(hParent)
            {
                if(GetStateImage(hParent) == CS_NOCHECK)
                {
                    SetStateImage(hParent, CS_HALFCHECK);
                }

                // If all immediate children are checked,
                // set it to FULLCHECK
                if(AllImmediateChildrenMatch(hParent, CS_FULLCHECK))
                {
                    SetStateImage(hParent, CS_FULLCHECK);
                }

                hParent = TreeView_GetParent(m_hWnd, hParent);
            }

            break;
        }
    case CT_UNCHECK:
        {
            // 1) Uncheck this item and all children.
            SetChildChecks(hItem, CS_NOCHECK);

            // 2) Tell all parents that they're no more than half-checked.
            HTREEITEM hParent = TreeView_GetParent(m_hWnd, hItem);

            while(hParent)
            {
                if(GetStateImage(hParent) == CS_FULLCHECK)
                {
                    SetStateImage(hParent, CS_HALFCHECK);
                }

                // If all immediate children are unchecked,
                // set it to NOCHECK
                if(AllImmediateChildrenMatch(hParent, CS_NOCHECK))
                {
                    SetStateImage(hParent, CS_NOCHECK);
                }

                hParent = TreeView_GetParent(m_hWnd, hParent);
            }

            break;
        }
    }

    return TRUE;
}


void CCTreeView3s::SetChildChecks(HTREEITEM hItem, TVCheckState s)
{
    // Set this item.
    SetStateImage(hItem, s);

    // Set all children.
    HTREEITEM hChild = TreeView_GetChild(m_hWnd, hItem);

    while(hChild)
    {
        SetChildChecks(hChild, s);

        hChild = GetNextSibling(hChild);
    }
}


BOOL CCTreeView3s::AllImmediateChildrenMatch(HTREEITEM hParent, TVCheckState s)
{
    HTREEITEM hChild = TreeView_GetChild(m_hWnd, hParent);

    while(hChild)
    {
        if((int)GetStateImage(hChild) != (int)s) return FALSE;

        hChild = TreeView_GetNextSibling(m_hWnd, hChild);
    }

    return TRUE;
}


/*
    Find the next item that's fully checked.  Because
    a checked item implies all children are checked,
    we don't search down from checked nodes.  Therefore
    if hItem is checked, we grab its next sibling (or whatever
    is next) and traverse that way.
*/
HTREEITEM CCTreeView3s::GetNextCheckedItem(HTREEITEM hItem)
{
    hItem = GetNextItemNoChildren(hItem);

    while(hItem != NULL)
    {
        int iImage = GetStateImage(hItem);

        if(iImage == CS_FULLCHECK) return hItem;

        if(iImage == CS_NOCHECK)
        {
            // Get next sibling.
            HTREEITEM hti = GetNextSibling(hItem);

            if(hti == NULL)
            {
                hItem = GetNextItem(hItem);
            }
            else 
            {
                hItem = hti;
            }
        }
        else
        {
            hItem = GetNextItem(hItem);
        }
    }

    return NULL;
}


HTREEITEM CCTreeView3s::InsertItemChecked(PCWSTR wszItem,
                     HTREEITEM hParent,
                     HTREEITEM hInsertAfter,
                     LPARAM lParam)
{
    return InsertItemWithState(wszItem, CS_FULLCHECK, hParent, hInsertAfter, lParam);
}


HTREEITEM CCTreeView3s::InsertItemWithImageChecked(PCWSTR wszItem, int nImage, int nSelectedImage,
                     HTREEITEM hParent,
                     HTREEITEM hInsertAfter,
                     LPARAM lParam)
{
    return InsertItemWithState(wszItem, CS_FULLCHECK, nImage, nSelectedImage,
        hParent, hInsertAfter, lParam);
}

