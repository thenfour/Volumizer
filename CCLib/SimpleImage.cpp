

#include "stdafx.h"
#include "simpleimage.h"
#include <ocidl.h>// For IPicture
#include <olectl.h>


CSimpleImage::CSimpleImage()
{
    m_hbm = 0;
    m_dc = 0;
}


CSimpleImage::~CSimpleImage()
{
    Free();
}


HRESULT CSimpleImage::Load(HINSTANCE hInstance, PCWSTR szResource)
{
    Free();

    m_hbm = (HBITMAP)LoadImage(hInstance, szResource, IMAGE_BITMAP, 0, 0, 0);

    if(!m_hbm)
    {
        return E_FAIL;
    }

    HDC dcScreen = GetDC(0);
    m_dc = CreateCompatibleDC(dcScreen);
    ReleaseDC(0, dcScreen);

    SelectObject(m_dc, m_hbm);

    if(0 == GetObject(m_hbm, sizeof(m_bm), &m_bm))
    {
        return E_FAIL;
    }

    return S_OK;
}


HRESULT CSimpleImage::Load(PCWSTR wszFile)
{
    HRESULT hr = E_FAIL;
    Free();

    m_hbm = (HBITMAP)LoadImage(0, wszFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if(!m_hbm)
    {
        // try oleload
        if(FAILED(OleLoad(wszFile)))
        {
            odsf(L"CPotImage::Load", L"Failed to load %s", wszFile);
        }
        else
        {
            hr = S_OK;
        }
    }
    else
    {
        HDC dcScreen = GetDC(0);
        m_dc = CreateCompatibleDC(dcScreen);
        ReleaseDC(0, dcScreen);

        SelectObject(m_dc, m_hbm);

        if(0 != GetObject(m_hbm, sizeof(m_bm), &m_bm))
        {
            hr = S_OK;
        }
    }

    return hr;
}


HRESULT CSimpleImage::Blt(HDC dc, int x, int y)
{
    if(0 == BitBlt(dc, x, y, m_bm.bmWidth+x, m_bm.bmHeight+y, m_dc, 0, 0, SRCCOPY))
    {
        return E_FAIL;
    }

    return S_OK;
}


HRESULT CSimpleImage::Free()
{
    if(m_dc) { DeleteDC(m_dc); m_dc = 0; }
    if(m_hbm) { DeleteObject(m_hbm); m_hbm = 0; }
    return S_OK;
}


HRESULT CSimpleImage::Blt(HDC dc, int xDest, int yDest, int xSrc, int ySrc, int cx, int cy)
{
    if(!BitBlt(dc, xDest, yDest, cx, cy, m_dc, xSrc, ySrc, SRCCOPY))
    {
        return E_FAIL;
    }

    return S_OK;
}


HRESULT CSimpleImage::OleLoad(PCWSTR wszFile)
{
    HRESULT hr = E_FAIL;
    HANDLE hFile = 0;

    hFile = CreateFile(wszFile, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    
    if((hFile == INVALID_HANDLE_VALUE) || (hFile == 0))
    {
        // error!
    }
    else
    {
        DWORD dwSize = GetFileSize(hFile, 0);

        // now copy the resource to a HGLOBAL location.
        HGLOBAL hCopy = GlobalAlloc(GMEM_MOVEABLE, dwSize);
        if(hCopy)
        {
            DWORD br = 0;
            void* pBits = GlobalLock(hCopy);
            if(pBits)
            {
                ReadFile(hFile, pBits, dwSize, &br, 0);
                GlobalUnlock(hCopy);

                if(br == dwSize)
                {
                    hr = OleLoad(hCopy);
                }
            }

            GlobalFree(hCopy);
        }

        CloseHandle(hFile);
    }

    return hr;
}


HRESULT CSimpleImage::OleLoad(HGLOBAL hMem)
{
    HRESULT hr = E_FAIL;
    IStream* pStream = 0;

    // get an IStream to reference the resource
    if(SUCCEEDED(CreateStreamOnHGlobal(hMem, FALSE, &pStream)))
    {
        hr = OleLoad(pStream);
        pStream->Release();
    }

    return hr;
}


HRESULT CSimpleImage::OleLoad(IStream* pStream)
{
    HRESULT hr = E_FAIL;
    IPicture* pPicture = 0;
    // load the damn picture
    if(SUCCEEDED(OleLoadPicture(pStream, 0, TRUE, IID_IPicture, (VOID**)&pPicture)))
    {
        OLE_HANDLE hBitmap = 0;
        pPicture->get_Handle(&hBitmap);
        m_hbm = (HBITMAP)CopyImage((HANDLE)hBitmap, IMAGE_BITMAP, 0, 0, 0);

        HDC dcScreen = GetDC(0);
        m_dc = CreateCompatibleDC(dcScreen);
        ReleaseDC(0, dcScreen);

        SelectObject(m_dc, m_hbm);

        GetObject(m_hbm, sizeof(m_bm), &m_bm);

        pPicture->Release();

        hr = S_OK;
    }

    return hr;
}


HRESULT CSimpleImage::OleLoad(HINSTANCE hInstance, PCWSTR szResource, PCWSTR szType)
{
    HRSRC hResSplash = 0;
    HRESULT hr = E_FAIL;

    hResSplash = FindResource(g_hInstance, szResource, szType);
    if(hResSplash)
    {
        DWORD dwResSize = SizeofResource(g_hInstance, hResSplash);
        if(dwResSize)
        {
            HGLOBAL hLoaded = LoadResource(g_hInstance, hResSplash);
            if(hLoaded)
            {
                void* pRes = LockResource(hLoaded);
                // now copy the resource to a HGLOBAL location.
                HGLOBAL hCopy = GlobalAlloc(GMEM_MOVEABLE, dwResSize);
                if(hCopy)
                {
                    void* pCopy = GlobalLock(hCopy);
                    if(pCopy)
                    {
                        memcpy(pCopy, pRes, dwResSize);
                        GlobalUnlock(hCopy);
                    }

                    hr = OleLoad(hCopy);
                    GlobalFree(hCopy);
                }
            }
        }
    }

    return hr;
}





