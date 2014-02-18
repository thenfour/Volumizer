/*
    A TreeView control with 3-state checkmarks
*/


#pragma once


#include <windows.h>
#include "global.h"
#include "CCControl.h"
#include "CCTreeView3s.h"// For the enums.
#include "CCImageList.h"


class CCEXPORT CCTreeView2s : public CCTreeView
{
public:
    CCTreeView2s();
    ~CCTreeView2s();

    HRESULT Create(HWND hParent, HINSTANCE hInstance, RECT& prect, RECT& orect);
    HRESULT TakeOver(HWND hWnd);

    BOOL SetCheck(HTREEITEM hItem, TVCheckType nCheck);
    HTREEITEM GetFirstCheckedItem();
    HTREEITEM GetNextCheckedItem(HTREEITEM hItem);

    void Destroy();

    BOOL IsItemChecked(HTREEITEM hItem);

    HTREEITEM InsertItemChecked(PCWSTR wszItem,
                         HTREEITEM hParent = TVI_ROOT,
                         HTREEITEM hInsertAfter = TVI_LAST,
                         LPARAM lParam = 0);

    HTREEITEM InsertItemWithImageChecked(PCWSTR wszItem, 
                         int nImage, int nSelectedImage,
                         HTREEITEM hParent = TVI_ROOT,
                         HTREEITEM hInsertAfter = TVI_LAST,
                         LPARAM lParam = 0);

private:

    void _InitWindow();// After we've created/taken over the window, this sets it up.

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    WNDPROC m_pOldProc;
    CCImageList m_Checks;
};

