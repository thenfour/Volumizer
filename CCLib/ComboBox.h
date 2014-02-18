

#pragma once


#include <windows.h>
#include "global.h"
#include "CCControl.h"


class CCEXPORT CComboBox : public CCControl
{
public:
    HRESULT Create(HWND hParent, RECT& prect, RECT& orect);
    HRESULT AddString(PCWSTR wsz, int* pi, void* pUser);// pi and pUser are optional
    int Count();

    int FindString(PCWSTR wsz);
    int FindUserData(void* pUser);
    HRESULT SelectUserData(void* pUser);
    HRESULT SelectString(PCWSTR wsz);
    HRESULT SelectIndex(int i);
    
    // wsz and pcbSize go together, and are optional.  pcbSize will receive the
    // size of the required string if pcbSize is valid.
    // ppUser is optional, and receives the user data associated with the item.
    HRESULT GetItemData(int i,
        OUT PWSTR wsz, IN OUT int* pccSize,
        OUT void** ppUser);
    void* GetUserData(int i);
    int GetStringLen(int i);
    int GetSelectedIndex();
};

