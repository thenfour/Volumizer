

#pragma once


#include "stdafx.h"


class CSaveDlg
{
public:
    CSaveDlg();
    ~CSaveDlg();

    void ShowAdvanced();
    void HideAdvanced();
    void SetupTree();
    static UINT_PTR CALLBACK SaveHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void OnSave(class CApp* pOwner, BOOL bSave);

public:
    // This is initialized by the owning application.
    BOOL m_bAdvanced;

private:

    void OnCommitSave(const WCHAR* wszFile);
    void OnCommitLoad(const WCHAR* wszFile);

    void InsertMixers(IMixerLibrary* p, HTREEITEM hParent);
    void InsertDestinations(IMixer* p, HTREEITEM hParent);
    void InsertLines(IMixerDestination* p, HTREEITEM hParent);
    void InsertControls(IMixerLine* p, HTREEITEM hParent);

private:
    BOOL m_bSave;

    class CApp* m_pOwner;
    HWND m_hDlg;
    HWND m_hAdvanced;

    CCTreeView3s m_Tree;
    CCImageList m_Icons;
};

