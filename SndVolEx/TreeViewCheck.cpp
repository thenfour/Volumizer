

#include "stdafx.h"
#include "TreeViewCheck.h"


void SETCHECK(HWND hTree, HTREEITEM hItem, TVCheckState x)
{
    TreeView_SetItemState(hTree,  hItem, INDEXTOSTATEIMAGEMASK((int)x), TVIS_STATEIMAGEMASK);
    return;
}


int GETCHECK(HWND hTree, HTREEITEM hItem)
{
    return ((TreeView_GetItemState(hTree,  hItem, TVIS_STATEIMAGEMASK)) >> 12);
}


void TVSetChildChecks(HWND hTree, HTREEITEM hItem, TVCheckState s)
{
    // Set this item.
    SETCHECK(hTree, hItem, s);

    // Set all children.
    HTREEITEM hChild = TreeView_GetChild(hTree, hItem);

    while(hChild)
    {
        TVSetChildChecks(hTree, hChild, s);

        hChild = TreeView_GetNextSibling(hTree, hChild);
    }
}


BOOL TVAllImmediateChildrenMatch(HWND hTree, HTREEITEM hParent, TVCheckState s)
{
    HTREEITEM hChild = TreeView_GetChild(hTree, hParent);

    while(hChild)
    {
        if(GETCHECK(hTree, hChild) != s) return FALSE;
        hChild = TreeView_GetNextSibling(hTree, hChild);
    }

    return TRUE;
}


BOOL TVSetCheck(HWND hTree, HTREEITEM hItem, TVCheckType nCheck)
{
    UINT nState = 0;

    if(hItem == NULL) return FALSE;

    nState = GETCHECK(hTree, hItem);

    // For toggling, let's figure out what we'll actually be doing.
    if(nCheck == TOGGLE)
    {
        switch(nState)
        {
        case NOCHECK:
            nCheck = CHECK;
            break;
        case HALFCHECK:
            nCheck = UNCHECK;
            break;
        case FULLCHECK:
            nCheck = UNCHECK;
            break;
        }
    }

    // Check our own node.
    switch(nCheck)
    {
    case CHECK:
        {
            // 1) Check this and all its children.
            TVSetChildChecks(hTree, hItem, FULLCHECK);

            // 2) Also tell all parents that they're atleast half checked.
            HTREEITEM hParent = TreeView_GetParent(hTree, hItem);

            while(hParent)
            {
                if(GETCHECK(hTree, hParent) == NOCHECK)
                {
                    SETCHECK(hTree, hParent, HALFCHECK);
                }

                // If all immediate children are checked,
                // set it to FULLCHECK
                if(TVAllImmediateChildrenMatch(hTree, hParent, FULLCHECK))
                {
                    SETCHECK(hTree, hParent, FULLCHECK);
                }

                hParent = TreeView_GetParent(hTree, hParent);
            }

            break;
        }
    case UNCHECK:
        {
            // 1) Uncheck this item and all children.
            TVSetChildChecks(hTree, hItem, NOCHECK);

            // 2) Tell all parents that they're no more than half-checked.
            HTREEITEM hParent = TreeView_GetParent(hTree, hItem);

            while(hParent)
            {
                if(GETCHECK(hTree, hParent) == FULLCHECK)
                {
                    SETCHECK(hTree, hParent, HALFCHECK);
                }

                // If all immediate children are unchecked,
                // set it to NOCHECK
                if(TVAllImmediateChildrenMatch(hTree, hParent, NOCHECK))
                {
                    SETCHECK(hTree, hParent, NOCHECK);
                }

                hParent = TreeView_GetParent(hTree, hParent);
            }

            break;
        }
    }

    return TRUE;
}


/*
    A little treeview helper function.  Finds the next node
    logically in the treeview.  In other words, if the entire
    treeview was completely "opened" so you could see ALL the
    nodes, this returns the one right below the given node.
*/
HTREEITEM TVGetNextItem(HWND hTree, HTREEITEM hItem)
{
    HTREEITEM hti = NULL;

    hti = TreeView_GetChild(hTree, hItem);

    if(hti == NULL)
    {
        while((hti = TreeView_GetNextSibling(hTree, hItem)) == NULL)
        {
            hItem = TreeView_GetParent(hTree, hItem);
            
            if(hItem == NULL)
            {
                return NULL;
            }
        }
    }

    return hti;
}


/*
    A little treeview helper function.  Finds the next node
    in the treeview, SKIPPING ALL CHILDREN.  So we start
    with the next sibiling.
*/
HTREEITEM TVGetNextItemNoChildren(HWND hTree, HTREEITEM hItem)
{
    HTREEITEM hti = NULL;

    while((hti = TreeView_GetNextSibling(hTree, hItem)) == NULL)
    {
        hItem = TreeView_GetParent(hTree, hItem);

        if(hItem == NULL)
        {
            return NULL;
        }
    }

    return hti;
}


HTREEITEM TVGetFirstCheckedItem(HWND hTree)
{
    HTREEITEM hItem = TreeView_GetRoot(hTree);
    int iImage = 0;

    while(hItem != NULL)
    {
        // Get the item's image.
        iImage = GETCHECK(hTree, hItem);

        // If it's checked, we're all good; just return.
        if(iImage == FULLCHECK)
        {
            return hItem;
        }

        if(iImage == NOCHECK)
        {
            // We can just skip this node altogether because not
            // even any children are checked.

            // So get the next sibling.
            HTREEITEM hti = TreeView_GetNextItem(hTree, hItem, TVGN_NEXT);

            if( hti == NULL )
            {
                // No more siblings... let's traverse up the tree to find the next
                // node.
                hItem = TVGetNextItem(hTree, hItem);
            }
            else
            {
                // We found a sibling; use it.
                hItem = hti;
            }
        }
        else
        {
            hItem = TVGetNextItem(hTree, hItem);
        }
    }

    // No matches.
    return 0;
}


/*
    Find the next item that's fully checked.  Because
    a checked item implies all children are checked,
    we don't search down from checked nodes.  Therefore
    if hItem is checked, we grab its next sibling (or whatever
    is next) and traverse that way.
*/
HTREEITEM TVGetNextCheckedItem(HWND hTree,  HTREEITEM hItem )
{
    hItem = TVGetNextItemNoChildren(hTree, hItem);

    while(hItem != NULL)
    {
        int iImage = GETCHECK(hTree, hItem);

        if(iImage == FULLCHECK) return hItem;

        if(iImage == NOCHECK)
        {
            HTREEITEM hti = TreeView_GetNextItem(hTree, hItem, TVGN_NEXT);

            if(hti == NULL)
                hItem = TVGetNextItem(hTree, hItem );
            else 
                hItem = hti;
        }
        else
            hItem = TVGetNextItem(hTree, hItem);
    }

    return NULL;
}


BOOL TVOnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(uMsg != WM_NOTIFY) return FALSE;

    NMHDR* pnmh = (NMHDR*)lParam;

    switch(pnmh->code)
    {
    case TVN_KEYDOWN:
        {
            NMTVKEYDOWN* pnmtv = (NMTVKEYDOWN*)lParam;

	        if( pnmtv->wVKey == VK_SPACE )
	        {
		        HTREEITEM hItem = TreeView_GetSelection(pnmtv->hdr.hwndFrom);
		        TVSetCheck(pnmtv->hdr.hwndFrom, hItem, TOGGLE);
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
		        TVSetCheck(hTree, hItem, TOGGLE);
		        return TRUE;
	        }

            break;
        }
    }

    return FALSE;
}


