/*
    This class takes care of the "display properties" for the application.
    Basically it just maintains a registry key with a list of values,
    each corresponding to a lineID that the user has chosen to hide.
*/

#pragma once


#include <windows.h>
#include "..\\CCLib\\LinkedList.h"


class CDisplayPropNode
{
public:
    DWORD m_dwLineID;

    // Required:
    int cmp(CDisplayPropNode& x)
    {
        return m_dwLineID - x.m_dwLineID;
    }

    CDisplayPropNode* pNext;
    CDisplayPropNode* pPrev;
};


class CDisplayProperties
{
public:
    CDisplayProperties();
    ~CDisplayProperties();

    void Save();
    void Load();
    BOOL IsLineEnabled(DWORD id);// Returns TRUE if the user is supposed to "see" the line.
    void EnableLine(DWORD id, BOOL b);// Registers a line as either enabled or not.

    BOOL DoDialog(class CApp* pOwner);// Returns TRUE if the user hit OK.

public:

    void _SetupTree();
    void _SetupDestinations(HTREEITEM hParent, IMixer* p);
    void _SetupLines(HTREEITEM hParent, IMixerDestination* p);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void _OnOk();

    class CApp* m_pOwner;

    void _Free();

    CLinkedList<CDisplayPropNode> m_List;

    // controls
    CCCustomWnd  m_Main;
    CCButton     m_Ok;
    CCButton     m_Cancel;
    CCStatic     m_Instructions;
    CCTreeView2s m_Tree;
    CCImageList  m_Icons;

    BOOL m_bReturnVal;

    RECT m_rc;// Last known window-rect, for saving settings.
};

