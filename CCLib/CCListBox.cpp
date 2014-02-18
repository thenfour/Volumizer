

#include "stdafx.h"
#include "CCListBox.h"
#include <stdio.h>
#include <tchar.h>



void LIST_COLUMN::Set(PCTSTR tszTitle, DWORD Orientation, int Size)
{
	_tcscpy(this->Title, tszTitle);
	this->Orientation = Orientation;
	this->Size = Size;
}

void LIST_COLUMNORDER::Set(int nIndex, int nSize)
{
    this->nIndex = nIndex;
    this->nSize = nSize;
}


//////////////////////////////////////////////////////////////////////////////
int CCListBox::GetSelectionMark()
{
    return ListView_GetSelectionMark(m_hWnd);
}


//////////////////////////////////////////////////////////////////////////////
LPARAM CCListBox::GetItemLParam(int iItem)
{
    LVITEMW lvi = {0};
    lvi.mask = LVIF_PARAM;
    lvi.iItem = iItem;
    lvi.iSubItem = 0;
    lvi.lParam = -1;
    ListView_GetItem(m_hWnd, &lvi);

    return lvi.lParam;
}


//////////////////////////////////////////////////////////////////////////////
int CCListBox::FindLParam(LPARAM pCriteria)
{
    int ir;

    LVFINDINFOW lvfi;
    lvfi.flags = LVFI_PARAM;
    lvfi.lParam = pCriteria;

    ir = ListView_FindItem(m_hWnd, -1, &lvfi);

    return ir;
}

//////////////////////////////////////////////////////////////////////////////
HRESULT CCListBox::SelectAnItem(int iItem)
{
    LVITEMW lvi = {0};
    lvi.iItem = iItem;
    lvi.iSubItem = 0;
    lvi.mask = LVIF_STATE;
    lvi.state = LVIS_SELECTED;
    lvi.stateMask = LVIS_SELECTED;

    if(ListView_SetItem(m_hWnd, &lvi) == FALSE)
    {
        return E_FAIL;
    }

    ListView_SetSelectionMark(m_hWnd, iItem);

    return S_OK;
}


HRESULT CCListBox::SetSmallImageList(CCImageList* pil)
{
    SendMessage(m_hWnd, LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)pil->GethImageList());
    m_pSmall = pil;

    return S_OK;
}


HRESULT CCListBox::SetBigImageList(CCImageList* pil)
{
    SendMessage(m_hWnd, LVM_SETIMAGELIST, LVSIL_NORMAL, (LPARAM)pil->GethImageList());
    m_pSmall = pil;

    return S_OK;
}


HRESULT CCListBox::SetStateImageList(CCImageList* pil)
{
    SendMessage(m_hWnd, LVM_SETIMAGELIST, LVSIL_STATE, (LPARAM)pil->GethImageList());
    m_pSmall = pil;

    return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
int CCListBox::GetItemCount()
{
	return SendMessage(m_hWnd, LVM_GETITEMCOUNT, 0, 0);
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CCListBox::GetItemText(int iItem, int iColumn, CCString* pOut)
{
    int nLen;
    TCHAR tsz[1024];

    LV_ITEM lvi;
    lvi.iSubItem = iColumn;
    lvi.cchTextMax = 1024;
    lvi.pszText = tsz;

    nLen = SendMessage(m_hWnd, LVM_GETITEMTEXT, iItem, (LPARAM)&lvi);

    *pOut = tsz;

    return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
int CCListBox::GetColumnCount()
{
    int r = 0;
    LVCOLUMNW col;
    col.mask = LVCF_WIDTH;

    while(ListView_GetColumn(m_hWnd, r, &col) != FALSE)
    {
        r++;
    }

    return r;
}




//////////////////////////////////////////////////////////////////////////////
HRESULT CCListBox::GetColumnText(int iCol, CCString* pOut)
{
    LVCOLUMN col;
    TCHAR tsz[MAX_PATH];
    col.mask = LVCF_TEXT;
    col.pszText = tsz;
    col.cchTextMax = MAX_PATH;

    if(ListView_GetColumn(m_hWnd, iCol, &col) == FALSE)
    {
        return E_FAIL;
    }

    *pOut = tsz;

    return S_OK;
}



//////////////////////////////////////////////////////////////////////////////
HRESULT CCListBox::SizeColumns()
{
    int nCol = 0;

    while(
        ListView_SetColumnWidth(m_hWnd,
        nCol++,
        LVSCW_AUTOSIZE_USEHEADER)
        == TRUE
        );

    return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
CCListBox::CCListBox()
{
    m_nLastColumnClicked = -1;
    m_pSmall = NULL;
    m_pBig = NULL;
    m_pState = NULL;
	m_nColumns = 0;
}



//////////////////////////////////////////////////////////////////////////////
CCListBox::~CCListBox()
{
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CCListBox::Create(HWND hParent, HINSTANCE hInstance, RECT prect, RECT orect)
{
	CopyRect(&m_orect, &orect);
	CopyRect(&m_prect, &prect);
    DWORD dwStyle = 0;

    m_hInstance = hInstance;

	dwStyle = WS_CHILD | LVS_SHOWSELALWAYS | WS_TABSTOP | 
		LVS_REPORT;

	m_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, 
        WC_LISTVIEW, _T("ListView"), dwStyle,
		0, 0, 10, 10, 
		hParent, (HMENU)GetId(), hInstance, 0);

	ListView_SetExtendedListViewStyle(m_hWnd, LVS_EX_FULLROWSELECT);

	//this->Size();
    m_nLastColumnClicked = -1;

    Size();
    Show(TRUE);

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CCListBox::AddItem(int* pId, LPARAM lParam, int nImage)
{
	LVITEM lvitem;
	int i;

    ZeroMemory(&lvitem, sizeof(lvitem));
	lvitem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
    lvitem.iItem = MAXLONG;//if there are more than this, who cares if it's out of order.
    lvitem.iSubItem = 0; 
    lvitem.state = 0; 
    lvitem.stateMask = 0; 
    lvitem.pszText = 0;
    lvitem.cchTextMax = 0;
    lvitem.iImage = nImage;
    lvitem.lParam = lParam;

	i = ListView_InsertItem(this->GethWnd(), &lvitem);

	if(pId) *pId = i;

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CCListBox::AddItemText(int nId, int nColumn, PCWSTR Label)
{
	ListView_SetItemText(this->GethWnd(), nId, nColumn, (PWSTR)Label);
	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CCListBox::Clear()
{
    //this->nLastColumnClicked = -1;
	ListView_DeleteAllItems(this->GethWnd());
	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CCListBox::ShowHeader(int nParts, LIST_COLUMN * Strings)
{
	LVCOLUMN col;
	col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	m_nColumns = nParts;

	int i;
	for (i = 0 ; i <nParts; i++)
    {
		col.pszText = Strings[i].Title;
		col.cx=Strings[i].Size;
		col.fmt = Strings[i].Orientation;
		col.iSubItem = i;

		ListView_InsertColumn(m_hWnd, i, &col);
	}

    // Delete all columns to the right of these, just to make sure we're done.
	while(ListView_DeleteColumn(m_hWnd, i) == TRUE)
    {
	}

	return 0;
}


int CCListBox::GetItemState(int iItem)
{
    int nState;

    nState = SendMessage(m_hWnd, LVM_GETITEMSTATE, iItem, LVIS_STATEIMAGEMASK);

    return (nState >> 12);
}


HRESULT CCListBox::SetItemState(int iItem, int nState)
{
    LVITEM lvi;
    lvi.stateMask = LVIS_STATEIMAGEMASK;
    lvi.state = (nState & 15) << 12;

    SendMessage(m_hWnd, LVM_SETITEMSTATE, iItem, (LPARAM)&lvi);

    return S_OK;
}


void CCListBox::SetExtendedListViewStyle(DWORD dw)
{
    SendMessage(m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dw);
}


DWORD CCListBox::GetExtendedListViewStyle()
{
    return SendMessage(m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
}


NMLISTVIEW* CCListBox::IsSelectedNotify(LPARAM lParam)
{
    NMHDR* pnmh = (NMHDR*)lParam;
    NMLISTVIEW* plv = NULL;

    if(pnmh->code == LVN_ITEMCHANGED)
    {
        if(pnmh->idFrom == GetId())
        {
            // Now determine if the change was a state change.
            plv = (NMLISTVIEW*)lParam;

            if(plv->uChanged & LVIF_STATE)
            {
                // The state changed.
                if(plv->uNewState & LVIS_SELECTED)
                {
                    return plv;
                }
            }
        }
    }

    return NULL;
}


NMITEMACTIVATE* CCListBox::IsActivatedNotify(LPARAM lParam)
{
    NMHDR* pnmh = (NMHDR*)lParam;
    NMITEMACTIVATE* plv = NULL;

    if(pnmh->code == LVN_ITEMACTIVATE)
    {
        if(pnmh->idFrom == GetId())
        {
            // Now determine if the change was a state change.
            return (NMITEMACTIVATE*)lParam;
        }
    }

    return NULL;
}


int CCListBox::IsSortNotify(LPARAM lParam)
{
    NMHDR* pnmh = (NMHDR*)lParam;
    NMLISTVIEW* plv = NULL;

    if(pnmh->code == LVN_COLUMNCLICK)
    {
        if(pnmh->idFrom == GetId())
        {
            plv = (NMLISTVIEW*)lParam;
            m_nLastColumnClicked = plv->iSubItem;
            return plv->iSubItem;
        }
    }

    return -1;
}


void CCListBox::SortById(PVOID pUser, PFNLVCOMPARE pfnCompare)
{
    ListView_SortItemsEx(m_hWnd, pfnCompare, pUser);
}


void CCListBox::SortByLParam(PVOID pUser, PFNLVCOMPARE pfnCompare)
{
    ListView_SortItems(m_hWnd, pfnCompare, pUser);
}


void CCListBox::SortParamAutomatically()
{
    ListView_SortItemsEx(m_hWnd, CCListBox::LParamCompareFunc, this);
}


void CCListBox::SortTextAutomatically(int iCol)
{
    m_iCol = iCol;
    ListView_SortItemsEx(m_hWnd, CCListBox::TextCompareFunc, this);
}

int CALLBACK CCListBox::TextCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CCListBox* pThis = (CCListBox*)lParamSort;
    CCString Text1, Text2;

    pThis->GetItemText(lParam1, pThis->m_iCol, &Text1);
    pThis->GetItemText(lParam2, pThis->m_iCol, &Text2);

    return Text1.cmp(Text2);
}


int CCListBox::SetSelectionMark(int i)
{
    return ListView_SetSelectionMark(m_hWnd, i);
}


void CCListBox::SimulateColumnClick(int iColumn)
{
    if(iColumn == -1) return;

    NMLISTVIEW nmlv;
    nmlv.hdr.code = LVN_COLUMNCLICK;
    nmlv.hdr.hwndFrom = m_hWnd;
    nmlv.hdr.idFrom = GetId();

    nmlv.iItem = -1;
    nmlv.iSubItem = iColumn;
    nmlv.lParam = 0;
    nmlv.ptAction.x = 0;
    nmlv.ptAction.y = 0;
    nmlv.uChanged = 0;
    nmlv.uNewState = 0;
    nmlv.uOldState = 0;

    SendMessage(GetParent(), WM_NOTIFY, GetId(), (LPARAM)&nmlv);
}


int CCListBox::GetLastColumnClicked()
{
    return m_nLastColumnClicked;
}


int CCListBox::GetColumnIndexesAndSizes(LIST_COLUMNORDER* p)
{
    int nColumns = this->GetColumnCount();
    int i;
    int* pOrder = NULL;

    // Get column orders.
    pOrder = new int[nColumns];
    if(pOrder == 0) return -1;

    ListView_GetColumnOrderArray(m_hWnd, nColumns, pOrder);

    // Now get the column sizes and stick ALL the info in the outgoing struct
    for(i=0;i<nColumns;i++)
    {
        if(p) p[i].Set(pOrder[i], ListView_GetColumnWidth(m_hWnd, i));
    }

    delete [] pOrder;

    return nColumns;
}


int CCListBox::SetColumnIndexesAndSizes(LIST_COLUMNORDER* p)
{
    int nColumns = this->GetColumnCount();
    int i;
    int* pOrder = NULL;

    if(p == 0) return -1;

    // Set up the order array - this will be filled in during the sizing loop
    // and later put into action.
    pOrder = new int[nColumns];
    if(pOrder == 0) return -1;

    for(i=0;i<nColumns;i++)
    {
        ListView_SetColumnWidth(m_hWnd, i, p[i].nSize);
        pOrder[i] = p[i].nIndex;
    }

    ListView_SetColumnOrderArray(m_hWnd, nColumns, pOrder);

    delete [] pOrder;

    return nColumns;
}


int CALLBACK CCListBox::LParamCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    return lParam1 - lParam2;
}


