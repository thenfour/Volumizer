/*
	CREATED: Nov. 3, 2001 Carl Corcoran
*/


#pragma once


#include <commctrl.h>


class CCEXPORT CCToolTip
{
public:

    CCToolTip();
    ~CCToolTip();

    HRESULT Create(HINSTANCE hInstance, HWND hParent);
    HRESULT AddTool(HWND hWnd, CCString Text, LPARAM lParam);

private:

    HWND hOwner;
    HWND hWnd;

};


