

#pragma once


#include "global.h"
#include <windows.h>
#include "CCControl.h"


// BST_CHECKED, BST_INDETERMINATE, BST_UNCHECKED


class CCEXPORT CCCheckBox : public CCControl
{
public:
	CCCheckBox();
	~CCCheckBox();

	HRESULT Create(PCWSTR wszCaption, HWND hParent, RECT& prect, RECT& orect, int nStates, BOOL bAuto);
	HRESULT Toggle();
    HRESULT SetCheck(UINT b);
    int GetCheck();
    HRESULT SetStates(int n, BOOL bAuto, BOOL bAuto3);// 2 or 3 state check box
    HRESULT SetActive(BOOL b);

private:
};


