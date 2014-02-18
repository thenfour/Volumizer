

#include "stdafx.h"


// Item states
enum TVCheckState
{
    XCHECK = 0,
    XXCHECK = 1,
    NOCHECK = 2,
    HALFCHECK = 3,
    FULLCHECK = 4
};


enum TVCheckType
{
    CHECK = 0,
    UNCHECK = 1,
    TOGGLE = 2
};


BOOL TVSetCheck(HWND hTree, HTREEITEM hItem, TVCheckType nCheck);
BOOL TVIsItemChecked(HWND hTree, HTREEITEM hItem);
HTREEITEM TVGetFirstCheckedItem(HWND hTree);
HTREEITEM TVGetNextCheckedItem(HWND hTree,  HTREEITEM hItem );
HTREEITEM TVGetPrevCheckedItem(HWND hTree,  HTREEITEM hItem );
UINT TVGetItemState(HWND hTree, HTREEITEM hItem, UINT mask);
BOOL TVOnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam);
void TVSetChildChecks(HWND hTree, HTREEITEM hItem, TVCheckState s);
HTREEITEM TVGetNextItemNoChildren(HWND hTree, HTREEITEM hItem);


