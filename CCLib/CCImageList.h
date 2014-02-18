/*
	CREATED: Nov. 3, 2001 Carl Corcoran
*/


#pragma once


#include <windows.h>
#include "global.h"
#include <commctrl.h>
#include "CCControl.h"


class CCEXPORT CCImageList
{
public:
	CCImageList();
	~CCImageList();

    operator HIMAGELIST();

    // For dwColor, refer to image list stuff like:
    // ILC_COLOR24, ILC_COLOR16, etc...
    HRESULT CreateEmpty(int nSizeX, int nSizeY, DWORD dwColor);

	void Destroy();

    // cMask can be CLR_NONE or CLR_DEFAULT or a color.
    HRESULT CreateFromResource(HINSTANCE hInstance, PWSTR wszResource, int cx, COLORREF cMask);
    // cMask can be CLR_NONE or CLR_DEFAULT or a color.
    HRESULT CreateFromFile(PCWSTR wszFileName, int cx, COLORREF cMask);

    HRESULT Clear();
    HRESULT GetImageInfo(int i, IMAGEINFO* pii);

    HIMAGELIST GethImageList();

    HRESULT Draw(int i, HDC dc, int x, int y);

    HRESULT AddBitmapFromHandle(int* pn, HBITMAP hbm);
    HRESULT AddBitmapFromFile(int* pn, PCWSTR wszFileName);

    // cMask can be CLR_NONE or CLR_DEFAULT or a color.
    HRESULT AddBitmapFromFileMasked(int* pn, PCWSTR wszFileName, COLORREF cMask);
    HRESULT AddBitmapFromResource(int* pn, HINSTANCE hInstance, UINT uResource);

    // cMask can be CLR_NONE or CLR_DEFAULT or a color.
    HRESULT AddBitmapFromResourceMasked(int* pn, HINSTANCE hInstance, UINT uResource, COLORREF cMask);

    HRESULT AddIconFromFile(int* pn, PCWSTR wszFileName);
    HRESULT AddIconFromResource(int* pn, HINSTANCE hInstance, UINT uResource);

    HRESULT RemoveImage(int n);
    int GetCount();

private:

    HIMAGELIST m_hImageList;

};


