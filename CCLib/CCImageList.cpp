

#include "stdafx.h"
#include "CCImageList.h"


CCImageList::CCImageList()
{
    m_hImageList = NULL;
}


CCImageList::~CCImageList()
{
}


CCImageList::operator HIMAGELIST()
{
    return m_hImageList;
}


void CCImageList::Destroy()
{
	Clear();

	if(m_hImageList)
	{
	    ImageList_Destroy(m_hImageList);
	}

	m_hImageList = NULL;
}


HRESULT CCImageList::CreateEmpty(int nSizeX, int nSizeY, DWORD dwColor)
{
	Destroy();
    m_hImageList = ImageList_Create(nSizeX, nSizeY, dwColor, 0, 10);

    if(m_hImageList == NULL) return E_FAIL;

    return S_OK;
}


HRESULT CCImageList::CreateFromResource(
    HINSTANCE hInstance, PWSTR wszResource, int cx, COLORREF cMask)
{
	Destroy();
    m_hImageList = ImageList_LoadImage(hInstance, wszResource,
        cx, 10, cMask, IMAGE_BITMAP, 0);

    if(m_hImageList == NULL) return E_FAIL;

    return S_OK;
}


HRESULT CCImageList::CreateFromFile(PCWSTR wszFile, int cx, COLORREF cMask)
{
	Destroy();
    m_hImageList = ImageList_LoadImage(NULL, wszFile,
        cx, 10, cMask, IMAGE_BITMAP, LR_LOADFROMFILE);

    if(m_hImageList == NULL) return E_FAIL;

    return S_OK;
}


HIMAGELIST CCImageList::GethImageList()
{
    return m_hImageList;
}


HRESULT CCImageList::AddBitmapFromFile(int* pn, PCWSTR wszFile)
{
    HBITMAP hBitmap;
    int i;

    hBitmap = (HBITMAP)LoadImage(NULL, wszFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if(hBitmap == NULL) return E_FAIL;

    i = ImageList_Add(m_hImageList, hBitmap, NULL);
    DeleteObject(hBitmap);

    if(pn) *pn = i;

    if(i == -1) return E_FAIL;

    return S_OK;
}


HRESULT CCImageList::AddBitmapFromFileMasked(int* pn, PCWSTR wszFile, COLORREF cMask)
{
    HBITMAP hBitmap;
    int i;

    hBitmap = (HBITMAP)LoadImage(NULL, wszFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if(hBitmap == NULL) return E_FAIL;

    i = ImageList_AddMasked(m_hImageList, hBitmap, cMask);
    DeleteObject(hBitmap);

    if(pn) *pn = i;

    if(i == -1) return E_FAIL;

    return S_OK;
}


HRESULT CCImageList::AddBitmapFromResource(int* pn, HINSTANCE hInstance, UINT uResource)
{
    HBITMAP hBitmap;
    int i;

    hBitmap = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(uResource),
        IMAGE_BITMAP, 0, 0, 0);

    if(hBitmap == NULL) return E_FAIL;

    i = ImageList_Add(m_hImageList, hBitmap, NULL);
    DeleteObject(hBitmap);

    if(pn) *pn = i;

    if(i == -1) return E_FAIL;

    return S_OK;
}


HRESULT CCImageList::AddBitmapFromResourceMasked(
    int* pn, HINSTANCE hInstance, UINT uResource, COLORREF cMask)
{
    HBITMAP hBitmap;
    int i;

    hBitmap = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(uResource),
        IMAGE_BITMAP, 0, 0, 0);

    if(hBitmap == NULL) return E_FAIL;

    i = ImageList_AddMasked(m_hImageList, hBitmap, cMask);
    DeleteObject(hBitmap);

    if(pn) *pn = i;

    if(i == -1) return E_FAIL;

    return S_OK;
}


HRESULT CCImageList::AddIconFromFile(int* pn, PCWSTR wszFile)
{
    HICON hIcon;
    int i;

    hIcon = (HICON)LoadImage(NULL, wszFile,
        IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

    if(hIcon == NULL) return E_FAIL;

    i = ImageList_AddIcon(m_hImageList, hIcon);
    DestroyIcon(hIcon);

    if(pn) *pn = i;

    if(i == -1) return E_FAIL;

    return S_OK;
}


HRESULT CCImageList::AddIconFromResource(int* pn, HINSTANCE hInstance, UINT uResource)
{
    HICON hIcon;
    int i;

    hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(uResource),
        IMAGE_ICON, 0, 0, 0);

    if(hIcon == NULL) return E_FAIL;

    i = ImageList_AddIcon(m_hImageList, hIcon);
    DestroyIcon(hIcon);

    if(pn) *pn = i;

    if(i == -1) return E_FAIL;

    return S_OK;
}


HRESULT CCImageList::RemoveImage(int n)
{
    return ImageList_Remove(m_hImageList, n) == 0 ? E_FAIL : S_OK;
}


int CCImageList::GetCount()
{
    return ImageList_GetImageCount(m_hImageList);
}


HRESULT CCImageList::GetImageInfo(int i, IMAGEINFO* pii)
{
    ImageList_GetImageInfo(m_hImageList, i, pii);
    return E_FAIL;
}


HRESULT CCImageList::Draw(int i, HDC dc, int x, int y)
{
    int n;

    n = ImageList_Draw(m_hImageList, i, dc, x, y, ILD_NORMAL);

    return n == 0 ? E_FAIL : S_OK;
}


HRESULT CCImageList::AddBitmapFromHandle(int* pn, HBITMAP hbm)
{
    int n = ImageList_Add(m_hImageList, hbm, NULL);
    DeleteObject(hbm);
    if(pn) *pn = n;
    return n == -1 ? E_FAIL : S_OK;
}


HRESULT CCImageList::Clear()
{
    return ImageList_RemoveAll(m_hImageList);
}

