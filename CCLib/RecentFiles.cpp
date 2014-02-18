

#include "stdafx.h"
#include "RecentFiles.h"


#define RF_MAXLIST 5


CRecentFiles::CRecentFiles()
{
    m_iMenuItems = 0;
    m_bChanged = FALSE;
    m_hMenu = 0;
    m_iMenu = 0;
}


CRecentFiles::~CRecentFiles()
{
    _Free();
}


void CRecentFiles::_Free()
{
    CRecentFileNode* p = m_List.m_pRoot;
    CRecentFileNode* pNext = 0;

    while(p)
    {
        pNext = p->pNext;
        delete p;
        p = pNext;
    }

    m_bChanged = FALSE;
    m_hMenu = 0;
    m_iMenu = 0;

    return;
}


void CRecentFiles::Save(HKEY hKey, PCWSTR wszSubKey)
{
    HKEY hKey2 = 0;
    DWORD dw = 0xC0FFFEEE;// just a dummy so we can stick data in the thing.
    CRecentFileNode* p = m_List.m_pRoot;

    if(m_bChanged == FALSE) return;

    RegDeleteKey(hKey, wszSubKey);

    if(ERROR_SUCCESS != RegCreateKeyEx(hKey, wszSubKey, 0, 0, 0, KEY_SET_VALUE, 0, &hKey2, 0))
    {
        return;
    }

    while(p)
    {
        RegSetValueEx(hKey2, p->sFile, 0, REG_DWORD, (BYTE*)&dw, sizeof(dw));
        p = p->pNext;
    }

    RegCloseKey(hKey2);

    return;
}


void CRecentFiles::Load(HKEY hKey, PCWSTR wszSubKey)
{
    m_bChanged = FALSE;
    CRecentFileNode* p = 0;
    HKEY hKey2 = 0;
    CCString sValueName;
    DWORD dw;
    int i = 0;
    int r = 0;// return value from RegEnumValue

    _Free();

    if(ERROR_SUCCESS != RegOpenKeyEx(hKey, wszSubKey, 0, KEY_QUERY_VALUE, &hKey2))
    {
        return;
    }

    // Enum values.
    while(1)
    {
        dw = MAX_PATH;
        r = RegEnumValue(hKey2, i, sValueName.GetBuffer(MAX_PATH), &dw, 0, 0, 0, 0);
        if(r != ERROR_SUCCESS) break;

        if(sValueName.len())
        {
            p = new CRecentFileNode;
            p->sFile = sValueName;
            m_List.InsertAfter(p, 0);

            if(m_List.Count() >= RF_MAXLIST) break;
        }

        i++;
    }

    RegCloseKey(hKey2);
}


HMENU CRecentFiles::CreateSubMenu()
{
    return 0;
}


void CRecentFiles::InsertIntoMenu(HMENU hMenu, int nStartPos)
{
    CRecentFileNode* p = m_List.m_pRoot;
    int i = nStartPos;

    _RemoveMenuItems();

    m_hMenu = hMenu;
    m_iMenu = nStartPos;

    while(p)
    {
        _InsertMenuItem(i, p);
        i++;
        p = p->pNext;
    }

    return;
}


void CRecentFiles::_InsertMenuItem(int i, CRecentFileNode* p)
{
    // First clean up after ourselves.
    MENUITEMINFO mii = {0};
    mii.cbSize = sizeof(mii);
    mii.fMask = MIIM_STRING;
    mii.dwTypeData = p->sFile;

    // Insert it.
    InsertMenuItem(m_hMenu, i, TRUE, &mii);
    m_iMenuItems ++;
}


/*
    File
    -----------
    0 Open
    1 Close
    2 ..\blah\c.txt   <-- our ID is 2., length 1.
    3 Exit
*/
int CRecentFiles::OnMenuCommand(WPARAM wParam, LPARAM lParam)
{
    if((HMENU)lParam != m_hMenu) return -1;

    // It's in the same menu.  Now determine what position
    // the selected item is.
    if((int)wParam < m_iMenu) return -1;
    if((int)wParam >= (m_iMenu + m_iMenuItems)) return -1;

    // We know it's one of our own items, so let's return the index
    // of it.  Our internal list is always the same order as the menu.

    return wParam - m_iMenu;
}


void CRecentFiles::GetItem(int i, CCString* pOut)
{
    CRecentFileNode* pMatch = 0;

    pMatch = m_List.Item(i);

    if(pMatch)
    {
        *pOut = pMatch->sFile;
    }
    else
    {
        *pOut = L"";
    }

    return;
}


void CRecentFiles::_RemoveMenuItems()
{
    int i = 0;

    if(!m_hMenu) return;

    for(;m_iMenuItems>0;m_iMenuItems--)
    {
        RemoveMenu(m_hMenu, m_iMenu, MF_BYPOSITION);
    }

    return;
}


void CRecentFiles::UseFile(PCWSTR wszFullPath)
{
    CRecentFileNode* pMatch = 0;
    CRecentFileNode Criteria;

    m_bChanged = TRUE;

    // See if we already have this file in the list.
    Criteria.sFile = wszFullPath;
    pMatch = m_List.Find(&Criteria);

    if(pMatch)
    {
        // Move it to the front of the list.
        m_List.Remove(pMatch);
        m_List.InsertBefore(pMatch, 0);

        // If we exceeded our maximum size, then trim off the last file.
        if(m_List.Count() >= RF_MAXLIST) m_List.Remove(m_List.m_pTail);

        InsertIntoMenu(m_hMenu, m_iMenu);
    }
    else
    {
        // Create a new node for this file.
        CRecentFileNode* pNew = new CRecentFileNode;
        pNew->sFile = wszFullPath;
        m_List.InsertBefore(pNew, 0);

        // If we exceeded our maximum size, then trim off the last file.
        if(m_List.Count() >= RF_MAXLIST) m_List.Remove(m_List.m_pTail);

        InsertIntoMenu(m_hMenu, m_iMenu);
    }

    return;
}













