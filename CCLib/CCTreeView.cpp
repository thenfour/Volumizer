

#include "stdafx.h"
#include "CCTreeView.h"


CCTreeView::CCTreeView()
{
    m_hNormal = 0;
    m_hState = 0;
}


CCTreeView::~CCTreeView()
{
    _FreeImageLists();
}


HRESULT CCTreeView::Create(HWND hParent, RECT& prect, RECT& orect)
{
    return E_NOTIMPL;
}


/*
    A little treeview helper function.  Finds the next node
    logically in the treeview.  In other words, if the entire
    treeview was completely "opened" so you could see ALL the
    nodes, this returns the one right below the given node.
*/
HTREEITEM CCTreeView::GetNextItem(HTREEITEM hItem)
{
    HTREEITEM hti = NULL;

    hti = TreeView_GetChild(m_hWnd, hItem);

    if(hti == NULL)
    {
        while((hti = TreeView_GetNextSibling(m_hWnd, hItem)) == NULL)
        {
            hItem = TreeView_GetParent(m_hWnd, hItem);
            
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
HTREEITEM CCTreeView::GetNextItemNoChildren(HTREEITEM hItem)
{
    HTREEITEM hti = NULL;

    while((hti = TreeView_GetNextSibling(m_hWnd, hItem)) == NULL)
    {
        hItem = TreeView_GetParent(m_hWnd, hItem);

        if(hItem == NULL)
        {
            return NULL;
        }
    }

    return hti;
}


void CCTreeView::SetNormalImageList(HIMAGELIST himg, BOOL bAutoFree)
{
    _FreeNormal();
    TreeView_SetImageList(m_hWnd, himg, TVSIL_NORMAL);

    if(bAutoFree)
    {
        m_hNormal = himg;
    }
}


void CCTreeView::SetStateImageList(HIMAGELIST himg, BOOL bAutoFree)
{
    _FreeState();
    TreeView_SetImageList(m_hWnd, himg, TVSIL_STATE);

    if(bAutoFree)
    {
        m_hState = himg;
    }
}


void CCTreeView::_FreeImageLists()
{
    _FreeNormal();
    _FreeState();
}


void CCTreeView::_FreeNormal()
{
    if(m_hNormal)
    {
        ImageList_Destroy(m_hNormal);
        m_hNormal = 0;
    }
}


void CCTreeView::_FreeState()
{
    if(m_hState)
    {
        ImageList_Destroy(m_hState);
        m_hState = 0;
    }
}


HTREEITEM CCTreeView::InsertItem(TVINSERTSTRUCT* pInsertStruct)
{
    return TreeView_InsertItem(m_hWnd, &pInsertStruct);
}


HTREEITEM CCTreeView::InsertItem(UINT nMask, PCWSTR wszItem, int nImage,
                     int nSelectedImage, UINT nState, UINT nStateMask, 
                     LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	TVINSERTSTRUCT tvis;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hInsertAfter;
	tvis.item.mask = nMask;
	tvis.item.pszText = (PWSTR)wszItem;
	tvis.item.iImage = nImage;
	tvis.item.iSelectedImage = nSelectedImage;
	tvis.item.state = nState;
	tvis.item.stateMask = nStateMask;
	tvis.item.lParam = lParam;
	return (HTREEITEM)::SendMessage(m_hWnd, TVM_INSERTITEM, 0, (LPARAM)&tvis);
}


HTREEITEM CCTreeView::InsertItem(PCWSTR wszItem, 
                                 HTREEITEM hParent,
                                 HTREEITEM hInsertAfter,
                                 LPARAM lParam)
{
    return InsertItem(TVIF_TEXT | TVIF_PARAM, wszItem, 0, 0, 0, 0,
        lParam, hParent, hInsertAfter);
}


HTREEITEM CCTreeView::InsertItemWithImage(PCWSTR wszItem, 
                                 int nImage, 
                                 int nSelectedImage,
                                 HTREEITEM hParent,
                                 HTREEITEM hInsertAfter,
                                 LPARAM lParam)
{
    return InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
        wszItem, nImage, nSelectedImage, 0, 0,
        lParam, hParent, hInsertAfter);
}


HTREEITEM CCTreeView::InsertItemWithState(PCWSTR wszItem, 
                                          int nStateImage,
                                          int nImage, 
                                          int nSelectedImage,
                                          HTREEITEM hParent,
                                          HTREEITEM hInsertAfter,
                                          LPARAM lParam)
{
    return InsertItem(
        TVIF_TEXT | TVIF_STATE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
        wszItem, nImage, nSelectedImage,
        INDEXTOSTATEIMAGEMASK(nStateImage), TVIS_STATEIMAGEMASK,
        lParam, hParent, hInsertAfter);
}


HTREEITEM CCTreeView::InsertItemWithState(PCWSTR wszItem, int nStateImage,
                              HTREEITEM hParent,
                              HTREEITEM hInsertAfter,
                              LPARAM lParam)
{
    return InsertItem(
        TVIF_TEXT | TVIF_STATE | TVIF_PARAM, wszItem, 0, 0,
        INDEXTOSTATEIMAGEMASK(nStateImage), TVIS_STATEIMAGEMASK,
        lParam, hParent, hInsertAfter);
}


void CCTreeView::Expand(HTREEITEM hti, UINT uFlag)
{
    TreeView_Expand(m_hWnd, hti, uFlag);
}


LPARAM CCTreeView::GetLParam(HTREEITEM hti)
{
    TVITEMEX tvi = {0};

    tvi.mask = TVIF_HANDLE | TVIF_PARAM;
    tvi.hItem = hti;

    TreeView_GetItem(m_hWnd, &tvi);

    return tvi.lParam;
}


HTREEITEM CCTreeView::GetNextSibling(HTREEITEM hti)
{
    return TreeView_GetNextItem(m_hWnd, hti, TVGN_NEXT);
}


int CCTreeView::GetStateImage(HTREEITEM hti)
{
    int r = 0;

    r = TreeView_GetItemState(m_hWnd,  hti, TVIS_STATEIMAGEMASK);
    r >>= 12;
    r &= 15;

    return r;
}


void CCTreeView::SetStateImage(HTREEITEM hti, int nImage)
{
    TreeView_SetItemState(m_hWnd, hti, 
        INDEXTOSTATEIMAGEMASK(nImage), TVIS_STATEIMAGEMASK);
}

HTREEITEM CCTreeView::GetRoot()
{
    return TreeView_GetRoot(m_hWnd);
}

