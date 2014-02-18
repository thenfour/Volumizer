/*
    A TreeView control with 3-state checkmarks
*/


#pragma once


#include <windows.h>
#include "global.h"
#include "CCControl.h"
#include "CCTreeView.h"
#include "CCImageList.h"


// Item states
enum TVCheckState
{
    CS_UNCHECKABLE = 0,//  0000 - an uncheckable item.
    CS_xxxx = 1,       //  0001
    CS_NOCHECK = 2,    //  0010
    CS_HALFCHECK = 3,  //  0011
    CS_FULLCHECK = 4,  //  0100
};


enum TVCheckType
{
    CT_UNCHECKABLE = 0,
    CT_CHECK = 1,
    CT_UNCHECK = 2,
    CT_TOGGLE = 3
};


class CCEXPORT CCTreeView3s : public CCTreeView
{
public:
    CCTreeView3s();
    ~CCTreeView3s();

    HRESULT Create(HWND hParent, HINSTANCE hInstance, RECT& prect, RECT& orect);
    HRESULT TakeOver(HWND hWnd);

    BOOL SetCheck(HTREEITEM hItem, TVCheckType nCheck);
    HTREEITEM GetFirstCheckedItem();
    HTREEITEM GetNextCheckedItem(HTREEITEM hItem);

    void Destroy();

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

    void SetChildChecks(HTREEITEM hItem, TVCheckState s);
    void _InitWindow();// After we've created/taken over the window, this sets it up.
    BOOL AllImmediateChildrenMatch(HTREEITEM hParent, TVCheckState s);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    WNDPROC m_pOldProc;
    CCImageList m_Checks;
};

