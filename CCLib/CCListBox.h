

#pragma once


#include "CCImageList.h"
#include "CCControl.h"
#include "ccstring.h"

//////////////////////////////////////////////////////////////////////////////
class CCEXPORT LIST_COLUMN
{
public:
	void Set(PCWSTR Title, DWORD Orientation, int Size);
	WCHAR Title[MAX_PATH];
	DWORD Orientation;
	int Size;
};


class CCEXPORT LIST_COLUMNORDER
{
public:
    void Set(int nIndex, int nSize);
    int nIndex;
    int nSize;
};

//////////////////////////////////////////////////////////////////////////////
// For use with LIST_COLUMN
#define LIST_RIGHT   LVCFMT_RIGHT
#define LIST_LEFT    LVCFMT_LEFT
#define LIST_CENTER  LVCFMT_CENTER


//////////////////////////////////////////////////////////////////////////////
class CCEXPORT CCListBox : public CCControl
{
public:
	CCListBox();
	~CCListBox();

    HRESULT Create(HWND hParent, HINSTANCE hInstance, RECT prect, RECT orect);
    HRESULT SetBigImageList(CCImageList* pil);
    HRESULT SetSmallImageList(CCImageList* pil);
    HRESULT SetStateImageList(CCImageList* pil);
	HRESULT Clear();
    void SetExtendedListViewStyle(DWORD dw);
    DWORD GetExtendedListViewStyle();

    // nImage == -1 for no image.
    HRESULT AddItem(int* pId, LPARAM lParam, int nImage);
    HRESULT AddItemText(int nId, int Column, PCWSTR Label);// For adding sub-items.

    HRESULT SelectAnItem(int iItem);
    int GetSelectionMark();
    int SetSelectionMark(int i);

    int FindLParam(LPARAM pCriteria);
	int GetItemCount();

    // Column stuff
    HRESULT SizeColumns();
	HRESULT ShowHeader(int nParts, LIST_COLUMN * Strings);
    int     GetColumnCount();
    HRESULT GetColumnText(int iCol, CCString* pOut);
    int GetColumnIndexesAndSizes(LIST_COLUMNORDER* p);
    int SetColumnIndexesAndSizes(LIST_COLUMNORDER* p);// Must have column count indexes.

    // Item information stuff
    LPARAM  GetItemLParam(int iItem);
    HRESULT GetItemText(int iItem, int iColumn, CCString* pOut);
    int     GetItemState(int iItem);
    HRESULT SetItemState(int iItem, int nState);

    // Notification message stuff
    NMLISTVIEW*     IsSelectedNotify(LPARAM lParam);
    int             IsSortNotify(LPARAM lParam);
    NMITEMACTIVATE* IsActivatedNotify(LPARAM lParam);

    void SimulateColumnClick(int iColumn);

    // Sorting stuff
    void SortById(PVOID pUser, PFNLVCOMPARE pfnCompare);
    void SortByLParam(PVOID pUser, PFNLVCOMPARE pfnCompare);
    void SortTextAutomatically(int iCol);
    void SortParamAutomatically();

    int GetLastColumnClicked();

private:

    int m_nLastColumnClicked;
    int m_iCol;// Used temporarily for the comparison function.
    static int CALLBACK TextCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
    static int CALLBACK LParamCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

    CCImageList* m_pState;
    CCImageList* m_pBig;
    CCImageList* m_pSmall;
    int m_nColumns;
};


