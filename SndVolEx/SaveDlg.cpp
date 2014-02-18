

#include "stdafx.h"
#include "SaveDlg.h"
#include "CApp.h"


struct SaveNodeData
{
    IUnknown*      pUnk;
    SmallIcon_Type Image;
};


template<typename TInterface>
LPARAM CreateSaveDlgParam(SmallIcon_Type nImage, TInterface* p)
{
    SaveNodeData* pData = new SaveNodeData;
    pData->Image = nImage;
    p->QueryInterface(IID_IUnknown, (void**)&pData->pUnk);
    return (LPARAM)pData;
}


CSaveDlg::CSaveDlg()
{
    m_pOwner = 0;
    m_hDlg = 0;
    m_hAdvanced = 0;
}


CSaveDlg::~CSaveDlg()
{
}


void CSaveDlg::ShowAdvanced()
{
    m_Tree.Show(TRUE);

    ShowWindow(GetDlgItem(m_hDlg, IDC_INSTRUCTIONS), SW_SHOW);
    SetWindowText(m_hAdvanced, L"Advanced <<");
    m_bAdvanced = TRUE;

    RECT rcTree;
    RECT rcParent;
    HWND hParent = GetParent(m_hDlg);

    // Basically all we need to do is make the parent's BOTTOM edge
    // a few pixels away from the m_hAdvanced bottom edge.
    GetWindowRect(m_Tree, &rcTree);
    GetWindowRect(hParent, &rcParent);

    SetWindowHeight(hParent, rcTree.bottom - rcParent.top + 12);

    // Make our own dialog the size of the parent's client now to pretty things up.
    GetClientRect(hParent, &rcParent);
    SetWindowPos(m_hDlg, 0, 0, 0, 
        rcParent.right - rcParent.left, 
        rcParent.bottom - rcParent.top, SWP_NOMOVE | SWP_NOZORDER);
}


void CSaveDlg::HideAdvanced()
{
    // Modify the controls on screen to reflect changes.
    SetWindowText(m_hAdvanced, L"Advanced >>");
    m_bAdvanced = FALSE;
    ShowWindow(m_Tree, SW_HIDE);
    ShowWindow(GetDlgItem(m_hDlg, IDC_INSTRUCTIONS), SW_HIDE);

    RECT rcAdvanced;
    RECT rcParent;
    HWND hParent = GetParent(m_hDlg);

    // Basically all we need to do is make the parent's BOTTOM edge
    // a few pixels away from the m_hAdvanced bottom edge.
    GetWindowRect(m_hAdvanced, &rcAdvanced);
    GetWindowRect(hParent, &rcParent);

    SetWindowHeight(hParent, rcAdvanced.bottom - rcParent.top + 12);

    // Make our own dialog the size of the parent's client now to pretty things up.
    GetClientRect(hParent, &rcParent);
    SetWindowPos(m_hDlg, 0, 0, 0, 
        rcParent.right - rcParent.left, 
        rcParent.bottom - rcParent.top, SWP_NOMOVE | SWP_NOZORDER);
}


UINT_PTR CALLBACK CSaveDlg::SaveHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CSaveDlg* pThis = (CSaveDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(uMsg)
    {
    case WM_DESTROY:
        {
            // Free tree associated data.
            return TRUE;
        }
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
            case IDC_ADVANCED:
                {
                    if(pThis->m_bAdvanced == TRUE)
                    {
                        pThis->HideAdvanced();
                    }
                    else
                    {
                        pThis->ShowAdvanced();
                    }

                    SendMessage(hWnd, WM_SIZE, 0, 0);

                    return TRUE;
                }
            }
            break;
        }
    case WM_INITDIALOG:
        {
            OPENFILENAME* pofn = (OPENFILENAME*)lParam;
            pThis = (CSaveDlg*)pofn->lCustData;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

            pThis->m_hDlg = hWnd;
            pThis->m_hAdvanced = GetDlgItem(hWnd, IDC_ADVANCED);
            pThis->m_Tree.TakeOver(GetDlgItem(hWnd, IDC_TREE1));

            return TRUE;
        }
    case WM_NOTIFY:
        {
            NMHDR* pnmh = (NMHDR*)lParam;

            switch(pnmh->code)
            {
            case TVN_DELETEITEM:
                {
                    NMTREEVIEW* pnmtv = (NMTREEVIEW*)lParam;
                    SaveNodeData* pData = (SaveNodeData*)pnmtv->itemOld.lParam;

                    if(pData)
                    {
                        SAFE_RELEASE(pData->pUnk);
                        delete pData;
                    }

                    return TRUE;
                }
            case CDN_INITDONE:
                {
                    // Now initialize the view so that the display is not advanced.
                    pThis->SetupTree();
                    
                    if(pThis->m_bSave == TRUE)
                    {
                        SetDlgItemText(hWnd, IDC_INSTRUCTIONS, L"Select the items that will be saved.");
                    }
                    else
                    {
                        SetDlgItemText(hWnd, IDC_INSTRUCTIONS, L"Select the items that can be affected.");
                    }

                    if(pThis->m_bAdvanced == TRUE)
                    {
                        pThis->ShowAdvanced();
                    }
                    else
                    {
                        pThis->HideAdvanced();
                    }

                    return TRUE;
                }
            case CDN_FILEOK:
                {
                    // The user has chosen a file and needs to save it.
                    // Let's go ahead now and do our work.
                    WCHAR wsz[MAX_PATH];
                    SendMessage(pnmh->hwndFrom, CDM_GETFILEPATH, (WPARAM)MAX_PATH, (LPARAM)wsz);

                    // If there is no extension on this thing, stick on our
                    // default extension.
                    if(wcschr(wsz, L'.') == 0)
                    {
                        wcscat(wsz, L".xml");
                    }

                    if(pThis->m_bSave == TRUE)
                    {
                        pThis->OnCommitSave(wsz);
                    }
                    else
                    {
                        pThis->OnCommitLoad(wsz);
                    }

                    return TRUE;
                }
            }

            break;
        }
    }

    return FALSE;
}


void CSaveDlg::OnSave(class CApp* pOwner, BOOL bSave)
{
    CCString sFile;
    OPENFILENAME ofn = {0};

    m_pOwner = pOwner;
    m_bSave = bSave;

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hInstance = g_hInstance;
    ofn.lpTemplateName = MAKEINTRESOURCE(IDD_COMDLG32);
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_ENABLEHOOK | OFN_ENABLETEMPLATE | OFN_EXPLORER | OFN_DONTADDTORECENT | OFN_HIDEREADONLY;
    ofn.hwndOwner = pOwner->m_Main;
    ofn.lpstrDefExt = L"xml";
    ofn.lpfnHook = CSaveDlg::SaveHook;
    ofn.FlagsEx = OFN_EX_NOPLACESBAR;
    ofn.lCustData = (LONG)this;
    ofn.lpstrFilter = L"XML Data (*.xml)\0*.xml\0All Files (*.*)\0*.*\0\0";
    ofn.lpstrFile = sFile.GetBuffer(MAX_PATH);
    ofn.nMaxFile = MAX_PATH;

    if(bSave == TRUE)
    {
        GetSaveFileName(&ofn);
    }
    else
    {
        GetOpenFileName(&ofn);
    }

    // By this time, our data has already been processed by the
    // dialogproc....

    // Free our resources.

    m_pOwner = 0;
    m_hDlg = 0;
    m_hAdvanced = 0;
}


void CSaveDlg::SetupTree()
{
    TVINSERTSTRUCT tvi = {0};
    HTREEITEM hLibrary = 0;

    m_Icons.CreateFromResource(g_hInstance, MAKEINTRESOURCE(IDB_SMALLICONS), 16, RGB(255,255,255));
    m_Tree.SetNormalImageList(m_Icons, TRUE);

    // Add the library node.
    hLibrary = m_Tree.InsertItemWithImageChecked(L"Mixer Library",
        Image_Library, Image_Library, TVI_ROOT, TVI_LAST,
        CreateSaveDlgParam<IMixerLibrary>(Image_Library, m_pOwner->m_pLibrary));

    InsertMixers(m_pOwner->m_pLibrary, hLibrary);

    m_Tree.SetCheck(hLibrary, CT_CHECK);

    // Expand the node
    m_Tree.Expand(hLibrary);

    return;
}


void CSaveDlg::InsertMixers(IMixerLibrary* p, HTREEITEM hParent)
{
    IEnumMixers* pEnumMixers = 0;
    IMixer* pMixer = 0;
    BSTR str = 0;
    DWORD dwFetched;
    TVINSERTSTRUCT tvi = {0};
    HTREEITEM hItem = 0;

    p->EnumMixers(&pEnumMixers);

    if(pEnumMixers)
    {
        while(1)
        {
            pEnumMixers->Next(1, &pMixer, &dwFetched);

            if(dwFetched != 1)
            {
                break;
            }

            // We have a valid mixer.  Insert the item first.
            pMixer->get_name(&str);

            hItem = m_Tree.InsertItemWithImageChecked(str,
                Image_Mixer, Image_Mixer, hParent, TVI_LAST,
                CreateSaveDlgParam<IMixer>(Image_Mixer, pMixer));

            SysFreeString(str);

            // Now stick all the destinations underneath it.
            InsertDestinations(pMixer, hItem);

            m_Tree.Expand(hItem);

            SAFE_RELEASE(pMixer);
        }

        SAFE_RELEASE(pEnumMixers);
    }

    return;
}


void CSaveDlg::InsertDestinations(IMixer* p, HTREEITEM hParent)
{
    IEnumMixerDestinations* pEnumDest = 0;
    IMixerDestination* pDest = 0;
    DWORD dwFetched = 0;
    TVINSERTSTRUCT tvi = {0};
    HTREEITEM hItem = 0;
    BSTR str = 0;
    IMixerLine* pLine = 0;

    p->EnumDestinations(&pEnumDest);

    if(pEnumDest)
    {
        while(1)
        {
            pEnumDest->Next(1, &pDest, &dwFetched);

            if(dwFetched != 1)
            {
                break;
            }

            // Boom.  Valid destination.
            pDest->QueryInterface(IID_IMixerLine, (void**)&pLine);

            if(pLine)
            {
                pLine->get_name(&str);

                hItem = m_Tree.InsertItemWithImageChecked(str,
                    Image_Destination, Image_Destination, hParent, TVI_LAST,
                    CreateSaveDlgParam<IMixerDestination>(Image_Destination, pDest));

                SysFreeString(str);

                // Now stick all the Controls underneath it.
                InsertControls(pLine, hItem);
                SAFE_RELEASE(pLine);

                // Now stick all the Lines underneath it.
                InsertLines(pDest, hItem);

                TreeView_Expand(m_Tree, hItem, TVE_EXPAND);
            }

            SAFE_RELEASE(pDest);
        }

        SAFE_RELEASE(pEnumDest);
    }

    return;
}


void CSaveDlg::InsertLines(IMixerDestination* p, HTREEITEM hParent)
{
    IEnumMixerLines* pEnum = 0;
    IMixerLine* pItem = 0;
    BSTR str = 0;
    DWORD dwFetched;
    TVINSERTSTRUCT tvi = {0};
    HTREEITEM hItem = 0;

    p->EnumLines(&pEnum);

    if(pEnum)
    {
        while(1)
        {
            pEnum->Next(1, &pItem, &dwFetched);

            if(dwFetched != 1)
            {
                break;
            }

            // We have a valid mixer.  Insert the item first.
            pItem->get_name(&str);

            hItem = m_Tree.InsertItemWithImageChecked(str,
                Image_Line, Image_Line, hParent, TVI_LAST,
                CreateSaveDlgParam<IMixerLine>(Image_Line, pItem));

            SysFreeString(str);

            // Do the controls...
            InsertControls(pItem, hItem);

            SAFE_RELEASE(pItem);
        }

        SAFE_RELEASE(pEnum);
    }

    return;
}


void CSaveDlg::InsertControls(IMixerLine* p, HTREEITEM hParent)
{
    IEnumMixerControls* pEnum = 0;
    IMixerControl* pControl = 0;
    BSTR str = 0;
    DWORD dwFetched;
    TVINSERTSTRUCT tvi = {0};
    HTREEITEM hItem = 0;

    p->EnumControls(&pEnum);

    if(pEnum)
    {
        while(1)
        {
            pEnum->Next(1, &pControl, &dwFetched);

            if(dwFetched != 1)
            {
                break;
            }

            // We have a valid mixer.  Insert the item first.
            pControl->get_name(&str);

            hItem = m_Tree.InsertItemWithImageChecked(str,
                Image_Control, Image_Control, hParent, TVI_LAST,
                CreateSaveDlgParam<IMixerControl>(Image_Control, pControl));

            SysFreeString(str);

            SAFE_RELEASE(pControl);
        }

        SAFE_RELEASE(pEnum);
    }

    return;
}


void CSaveDlg::OnCommitLoad(const WCHAR* wszFile)
{
    HTREEITEM hItem = 0;
    CCString sFile = wszFile;
    TVITEMEX tvi = {0};
    SaveNodeData* pData = 0;

    m_pOwner->m_RecentFiles.UseFile(wszFile);

    // For each completely selected node, save it to file.
    hItem = m_Tree.GetFirstCheckedItem();

    while(hItem)
    {
        pData = (SaveNodeData*)m_Tree.GetLParam(hItem);

        if(pData)
        {
            // Boom.  Let's save this guy.
            switch(pData->Image)
            {
            case Image_Library:
                {
                    IMixerLibrary* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixerLibrary, (void**)&p);

                    if(p)
                    {
                        p->Load(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            case Image_Mixer:
                {
                    IMixer* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixer, (void**)&p);

                    if(p)
                    {
                        p->Load(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            case Image_Destination:
                {
                    IMixerDestination* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixerDestination, (void**)&p);

                    if(p)
                    {
                        p->LoadDestination(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            case Image_Line:
                {
                    IMixerLine* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixerLine, (void**)&p);

                    if(p)
                    {
                        p->Load(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            case Image_Control:
                {
                    IMixerControl* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixerControl, (void**)&p);

                    if(p)
                    {
                        p->Load(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            }
        }

        // Save hItem to disk.
        hItem = m_Tree.GetNextCheckedItem(hItem);
    }

    return;
}


/*
    This is where the actual save-work is done.
*/
void CSaveDlg::OnCommitSave(const WCHAR* wszFile)
{
    HTREEITEM hItem = 0;
    CCString sFile = wszFile;
    TVITEMEX tvi = {0};
    SaveNodeData* pData = 0;

    m_pOwner->m_RecentFiles.UseFile(wszFile);

    // For each completely selected node, save it to file.
    hItem = m_Tree.GetFirstCheckedItem();

    while(hItem)
    {
        tvi.mask = TVIF_HANDLE | TVIF_PARAM;
        tvi.hItem = hItem;
        TreeView_GetItem(m_Tree, &tvi);

        pData = (SaveNodeData*)tvi.lParam;

        if(pData)
        {
            // Boom.  Let's save this guy.
            switch(pData->Image)
            {
            case Image_Library:
                {
                    IMixerLibrary* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixerLibrary, (void**)&p);

                    if(p)
                    {
                        p->Save(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            case Image_Mixer:
                {
                    IMixer* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixer, (void**)&p);

                    if(p)
                    {
                        p->Save(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            case Image_Destination:
                {
                    IMixerDestination* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixerDestination, (void**)&p);

                    if(p)
                    {
                        p->SaveDestination(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            case Image_Line:
                {
                    IMixerLine* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixerLine, (void**)&p);

                    if(p)
                    {
                        p->Save(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            case Image_Control:
                {
                    IMixerControl* p = 0;
                    pData->pUnk->QueryInterface(IID_IMixerControl, (void**)&p);

                    if(p)
                    {
                        p->Save(sFile);
                        SAFE_RELEASE(p);
                    }

                    break;
                }
            }
        }

        // Save hItem to disk.
        hItem = m_Tree.GetNextCheckedItem(hItem);
    }

    return;
}


