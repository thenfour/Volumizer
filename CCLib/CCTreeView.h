

#pragma once


#include <windows.h>
#include <commctrl.h>
#include "global.h"
#include "CCControl.h"


class CCEXPORT CCTreeView : public CCControl
{
public:
    CCTreeView();
    ~CCTreeView();

    HRESULT Create(HWND hParent, RECT& prect, RECT& orect);

    void SetNormalImageList(HIMAGELIST himg, BOOL bAutoFree);
    void SetStateImageList(HIMAGELIST himg, BOOL bAutoFree);

    // These are basically just stolen from MFC
    HTREEITEM InsertItem(TVINSERTSTRUCT* lpInsertStruct);

    HTREEITEM InsertItem(UINT nMask, PCWSTR wszItem, int nImage,
                         int nSelectedImage, UINT nState, UINT nStateMask, 
                         LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter);

    virtual HTREEITEM InsertItem(PCWSTR wszItem,
                         HTREEITEM hParent = TVI_ROOT,
                         HTREEITEM hInsertAfter = TVI_LAST,
                         LPARAM lParam = 0);

    virtual HTREEITEM InsertItemWithImage(PCWSTR wszItem, int nImage, int nSelectedImage,
                         HTREEITEM hParent = TVI_ROOT,
                         HTREEITEM hInsertAfter = TVI_LAST,
                         LPARAM lParam = 0);

    HTREEITEM InsertItemWithState(PCWSTR wszItem, int nStateImage,
                                  int nImage, int nSelectedImage,
                                  HTREEITEM hParent = TVI_ROOT,
                                  HTREEITEM hInsertAfter = TVI_LAST,
                                  LPARAM lParam = 0);

    HTREEITEM InsertItemWithState(PCWSTR wszItem, int nStateImage,
                                  HTREEITEM hParent = TVI_ROOT,
                                  HTREEITEM hInsertAfter = TVI_LAST,
                                  LPARAM lParam = 0);

    void Expand(HTREEITEM hti, UINT flag = TVE_EXPAND);
    LPARAM GetLParam(HTREEITEM hti);
    HTREEITEM GetNextSibling(HTREEITEM hti);
    int GetStateImage(HTREEITEM hti);
    void SetStateImage(HTREEITEM hti, int nImage);
    HTREEITEM GetRoot();
    HTREEITEM GetNextItem(HTREEITEM hti);
    HTREEITEM GetNextItemNoChildren(HTREEITEM hItem);

private:

    void _FreeImageLists();
    void _FreeNormal();
    void _FreeState();

    HIMAGELIST m_hNormal;
    HIMAGELIST m_hState;
};

