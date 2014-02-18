

#include "stdafx.h"
#include "DisplayProperties.h"
#include "CApp.h"


struct DispPropNode
{
    DWORD dwID;
};


CDisplayProperties::CDisplayProperties()
{
    SetRect(&m_rc, 100, 100, 400, 500);
    m_pOwner = 0;
}


CDisplayProperties::~CDisplayProperties()
{
    // Free the list.
    _Free();
}


/*
    Save this data to the registry.  We tear down - and reconstruct
    the list every time.
*/
void CDisplayProperties::Save()
{
    HKEY hKey = 0;
    CDisplayPropNode* p = m_List.m_pRoot;
    CCString sValueName;
    DWORD dw = 0;// Just a placeholder

    // First delete the key.
    RegDeleteKey(HKEY_CURRENT_USER, L"Software\\OneLightVolumizer\\Settings\\DisabledLines");

    if(ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER,
        L"Software\\OneLightVolumizer\\Settings\\DisabledLines", 0, 0, 0, 
        KEY_SET_VALUE, 0, &hKey, 0))
    {
        odsf(L"DisplayProps, Saving", L"Unable to create a registry key.");
        return;
    }

    // Save window placement.
    RegSetValueEx(hKey, NULL, 0, REG_BINARY, (BYTE*)&this->m_rc, sizeof(this->m_rc));

    while(p)
    {
        sValueName.FormatW(L"%08x", p->m_dwLineID);
        RegSetValueEx(hKey, sValueName, 0, REG_DWORD, (BYTE*)&dw, sizeof(dw));

        p = p->pNext;
    }

    RegCloseKey(hKey);
}


void CDisplayProperties::Load()
{
    HKEY hKey = 0;
    CCString sValueName;
    CDisplayPropNode* p = 0;
    DWORD dw;
    int i = 0;
    int r = 0;// return value from RegEnumValue

    if(ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER,
        L"Software\\OneLightVolumizer\\Settings\\DisabledLines", 0,
        KEY_QUERY_VALUE, &hKey))
    {
        odsf(L"DisplayProps::Load()", L"Unable to open a registry key.");
        return;
    }

    // Grab window placement.
    dw = sizeof(this->m_rc);
    RegQueryValueEx(hKey, NULL, 0, 0, (BYTE*)&this->m_rc, &dw);
    dw = 0;

    // Enum values.
    while(1)
    {
        dw = 100;
        r = RegEnumValue(hKey, i, sValueName.GetBuffer(100), &dw, 0, 0, 0, 0);
        if(r != ERROR_SUCCESS) break;

        if(sValueName.len())
        {
            p = new CDisplayPropNode;
            p->m_dwLineID = sValueName.toul(16);
            m_List.Insert(p);
        }

        i++;
    }

    RegCloseKey(hKey);
}


/*
    Determine whether the line is enabled or disabled.
*/
BOOL CDisplayProperties::IsLineEnabled(DWORD id)
{
    CDisplayPropNode Criteria;
    CDisplayPropNode* pMatch = 0;

    Criteria.m_dwLineID = id;
    pMatch = m_List.Find(&Criteria);

    if(pMatch) return FALSE;

    return TRUE;
}


void CDisplayProperties::_Free()
{
    CDisplayPropNode* p = m_List.m_pRoot;
    CDisplayPropNode* pNext = 0;

    while(p)
    {
        pNext = p->pNext;
        delete p;
        p = pNext;
    }
}


void CDisplayProperties::EnableLine(DWORD id, BOOL b)
{
    CDisplayPropNode Criteria;
    CDisplayPropNode* pMatch = 0;

    Criteria.m_dwLineID = id;
    pMatch = m_List.Find(&Criteria);

    if(b == TRUE)
    {
        // Remove it from the list if it's already in there.
        if(pMatch)
        {
            m_List.Remove(pMatch);
        }
    }
    else
    {
        // Add it to the list, if necessary.
        if(!pMatch)
        {
            CDisplayPropNode* pNew = new CDisplayPropNode;
            pNew->m_dwLineID = id;
            m_List.Insert(pNew);
        }
    }

    return;
}


BOOL CDisplayProperties::DoDialog(CApp* pOwner)
{
    RECT prect, orect;

    m_pOwner = pOwner;

    // 12 pixel border all around, Buttons are 75x23.
#define BUTTONX 75
#define BUTTONY 23
#define CONTROLSPACE 6
#define BORDER 12

    SetRect(&prect, 0, 0, 0, 0);
    m_Main.Create(L"Select Audio Lines to Display", 
        pOwner->m_Main, CDisplayProperties::WndProc, g_hInstance, prect, m_rc, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, this, IDI_ICON1);

    m_Icons.CreateFromResource(g_hInstance, MAKEINTRESOURCE(IDB_SMALLICONS), 16, RGB(255,255,255));

    SetRect(&prect, 0, 0, 100, 100);
    SetRect(&orect, BORDER, BORDER, -BORDER, - (BORDER+BUTTONY+CONTROLSPACE) );
    m_Tree.Create(m_Main, g_hInstance, prect, orect);
    m_Tree.SetNormalImageList(m_Icons, TRUE);

    SetRect(&prect, 100, 100, 100, 100);
    SetRect(&orect, -(BORDER+BUTTONX+BUTTONX+CONTROLSPACE), -(BORDER+BUTTONY), -(BORDER+CONTROLSPACE+BUTTONX), -BORDER);
    m_Ok.Create(L"OK", m_Main, g_hInstance, prect, orect);

    SetRect(&prect, 100, 100, 100, 100);
    SetRect(&orect, -(BORDER+BUTTONX), -(BORDER+BUTTONY), -(BORDER), -BORDER);
    m_Cancel.Create(L"Cancel", m_Main, g_hInstance, prect, orect);

    _SetupTree();

    m_Main.Show(TRUE);
    m_Main.Size();

    EnableWindow(m_pOwner->m_Main, FALSE);

    m_bReturnVal = FALSE;

    MSG msg;
    while(GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    m_Icons.Destroy();

    return m_bReturnVal;
}


LRESULT CALLBACK CDisplayProperties::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CDisplayProperties* pThis = (CDisplayProperties*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(uMsg)
    {
    case WM_WINDOWPOSCHANGED:
        {
            GetWindowRect(hWnd, &pThis->m_rc);
            pThis->m_Tree.Size();
            pThis->m_Ok.Size();
            pThis->m_Cancel.Size();
            return 0;
        }
    case WM_COMMAND:
        {
            if(lParam == (LPARAM)pThis->m_Cancel.GethWnd())
            {
                SendMessage(hWnd, WM_CLOSE, 0, 0);
                return 0;
            }
            else if(lParam == (LPARAM)pThis->m_Ok.GethWnd())
            {
                pThis->_OnOk();
                SendMessage(hWnd, WM_CLOSE, 0, 0);
                return 0;
            }

            break;
        }
    case WM_SIZE:
        {
            return 0;
        }
    case WM_DESTROY:
        {
            EnableWindow(pThis->m_pOwner->m_Main, TRUE);
            PostQuitMessage(0);
            return 0;
        }
    case WM_CLOSE:
        {
            DestroyWindow(hWnd);
            return 0;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_CREATE:
        {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            pThis = (CDisplayProperties*)pcs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void CDisplayProperties::_SetupTree()
{
    HTREEITEM hMixer = 0;
    IEnumMixers* pEnum = 0;
    IMixer* pMixer = 0;
    DWORD dwFetched = 0;
    BSTR str = 0;

    m_pOwner->m_pLibrary->EnumMixers(&pEnum);

    if(pEnum)
    {
        while(1)
        {
            pEnum->Next(1, &pMixer, &dwFetched);
            if(dwFetched != 1) break;

            pMixer->get_name(&str);

            // We have a valid mixer object, let's stick it in the tree.
            // We leave the LPARAM at 0 so that we will know later on
            // when traversing the tree to not worry about this item.
            // We can only allow audio LINES to be checked/unchecked.
            hMixer = m_Tree.InsertItemWithImageChecked(str, Image_Mixer, Image_Mixer);
            m_Tree.SetCheck(hMixer, CT_UNCHECKABLE);

            SysFreeString(str);

            // Now stick all the destinations underneath it.
            _SetupDestinations(hMixer, pMixer);

            m_Tree.Expand(hMixer);

            SAFE_RELEASE(pMixer);
        }

        SAFE_RELEASE(pEnum);
    }

    return;
}


void CDisplayProperties::_SetupDestinations(HTREEITEM hParent, IMixer* p)
{
    HTREEITEM hDest = 0;
    HTREEITEM hLine = 0;
    IEnumMixerDestinations* pEnum = 0;
    IMixerDestination* pDest = 0;
    IMixerLine* pLine = 0;
    DWORD dwFetched = 0;
    BSTR str = 0;

    p->EnumDestinations(&pEnum);

    if(pEnum)
    {
        while(1)
        {
            pEnum->Next(1, &pDest, &dwFetched);
            if(dwFetched != 1) break;

            pDest->QueryInterface(IID_IMixerLine, (void**)&pLine);
            pLine->get_name(&str);

            // Once again, leave lParam to 0 to indicate not to use this
            // line.
            hDest = m_Tree.InsertItemWithImageChecked(str, 
                Image_Destination, Image_Destination, hParent);

            m_Tree.SetCheck(hDest, CT_UNCHECKABLE);

            // Stick ourself underneath... ourself
            DispPropNode* pNew = new DispPropNode;
            pLine->get_lineid(&pNew->dwID);

            hLine = m_Tree.InsertItemWithImageChecked(str,
                Image_Line, Image_Line, hDest, TVI_LAST, (LPARAM)pNew);

            if(IsLineEnabled(pNew->dwID) == TRUE)
            {
                m_Tree.SetCheck(hLine, CT_CHECK);
            }
            else
            {
                m_Tree.SetCheck(hLine, CT_UNCHECK);
            }

            SysFreeString(str);

            // Now stick all the lines underneath it.
            _SetupLines(hDest, pDest);

            m_Tree.Expand(hDest);

            SAFE_RELEASE(pLine);
            SAFE_RELEASE(pDest);
        }

        SAFE_RELEASE(pEnum);
    }

    return;
}


void CDisplayProperties::_SetupLines(HTREEITEM hParent, IMixerDestination* p)
{
    HTREEITEM hLine = 0;
    IEnumMixerLines* pEnum = 0;
    IMixerLine* pLine = 0;
    DWORD dwFetched = 0;
    BSTR str = 0;

    p->EnumLines(&pEnum);

    if(pEnum)
    {
        while(1)
        {
            pEnum->Next(1, &pLine, &dwFetched);
            if(dwFetched != 1) break;

            pLine->get_name(&str);

            DispPropNode* pNew = new DispPropNode;
            pLine->get_lineid(&pNew->dwID);

            hLine = m_Tree.InsertItemWithImageChecked(str, Image_Line, Image_Line,
                hParent, TVI_LAST, (LPARAM)pNew);

            if(IsLineEnabled(pNew->dwID) == TRUE)
            {
                m_Tree.SetCheck(hLine, CT_CHECK);
            }
            else
            {
                m_Tree.SetCheck(hLine, CT_UNCHECK);
            }

            SysFreeString(str);

            SAFE_RELEASE(pLine);
        }

        SAFE_RELEASE(pEnum);
    }

    return;
}


void CDisplayProperties::_OnOk()
{
    // Traverse the entire list, item by item and enable/disable the lines based on
    // their IDs.
    HTREEITEM hItem = m_Tree.GetRoot();
    DispPropNode* p;// The lParam Data associated with the item.

    m_bReturnVal = TRUE;

    while(hItem)
    {
        p = (DispPropNode*)m_Tree.GetLParam(hItem);

        if(p)
        {
            EnableLine(p->dwID, m_Tree.IsItemChecked(hItem));
            delete p;
            p = 0;
        }

        hItem = m_Tree.GetNextItem(hItem);
    }

    return;
}



