

#include <windows.h>
#include "global.h"
#include "LinkedList.h"


class CCEXPORT CRecentFileNode
{
public:
    int cmp(CRecentFileNode& x)
    {
        return wcsicmp(sFile, x.sFile);
    }

    CCString sFile;
    CRecentFileNode* pNext;
    CRecentFileNode* pPrev;
};


class CCEXPORT CRecentFiles
{
public:
    CRecentFiles();
    ~CRecentFiles();

    void Save(HKEY hKey, PCWSTR wszSubKey);
    void Load(HKEY hKey, PCWSTR wszSubKey);

    /*
        Call this function when you receive a WM_MENUCOMMAND message.
        The return value is the index of the item that the user has
        selected, or -1 if the user didn't select anything from the
        recent file list.
    */
    int OnMenuCommand(WPARAM wParam, LPARAM lParam);
    void GetItem(int i, CCString* pOut);

    HMENU CreateSubMenu();
    void InsertIntoMenu(HMENU hMenu, int nStartPos);
    void UseFile(PCWSTR wszFullPath);

private:

    void _InsertMenuItem(int i, CRecentFileNode* p);
    void _RemoveMenuItems();

    int m_iMenuItems;// Number of menu items we have created.

    BOOL m_bChanged;// Has the list changed since it was loaded?
                    // Used so we don't always have to save to registry

    HMENU m_hMenu;// This is the menu that we keep up-to-date.
    int m_iMenu;// The position in the menu that we start at.

    void _Free();
    CLinkedList<CRecentFileNode> m_List;
};

