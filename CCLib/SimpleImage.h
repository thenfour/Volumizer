

#pragma once


#include <windows.h>
#include "global.h"
#include "CCDebug.h"


/*
    Class used to help automate GDI stuff for CMeterImage.
*/
class CCEXPORT CSimpleImage
{
public:
    CSimpleImage();
    ~CSimpleImage();

    HRESULT Load(PCWSTR wszFile);
    HRESULT Load(HINSTANCE hInstance, PCWSTR szResource);
    HRESULT OleLoad(HINSTANCE hInstance, PCWSTR szResource, PCWSTR szType);
    HRESULT OleLoad(PCWSTR wszFile);
    HRESULT OleLoad(HGLOBAL hMem);
    HRESULT OleLoad(IStream* pStream);

    HRESULT Blt(HDC dc, int x, int y);
    HRESULT Blt(HDC dc, int xDest, int yDest, int xSrc, int ySrc, int cx, int cy);
    HRESULT Free();

    HBITMAP hbm(){ return m_hbm; }

    BITMAP m_bm;

private:

    HDC m_dc;
    HBITMAP m_hbm;
};

