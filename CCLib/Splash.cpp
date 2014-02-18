

#include "stdafx.h"
#include "Splash.h"
#include <process.h>
#include <tchar.h>


CCSplash::CCSplash()
{
    this->sClass.FromNewGuid();
    this->dwThreadId = 0;
    this->hEventExit = 0;
    this->hThread = 0;
}


CCSplash::~CCSplash()
{
    this->Destroy();
}


HRESULT CCSplash::Destroy()
{
    if(this->hThread == 0) return S_OK;

    /*
        Tell the thread to quit.
    */
    SetEvent(this->hEventExit);

    WaitForSingleObject(this->hThread, INFINITE);

//    CloseHandle(this->hThread);
    this->hThread = NULL;
    this->dwThreadId = 0;
    this->hWnd = 0;

    CloseHandle(this->hEventExit);
    this->hEventExit = NULL;

	this->Images.Destroy();

    return S_OK;
}

HRESULT CCSplash::Create(POINT pStatic, COLORREF color, UINT idResource, HINSTANCE hInstance)
{
    if(this->hThread) return E_FAIL;

    this->dwLoadFrom = SLF_RESOURCE;

    this->rgbStaticColor = color;
    this->user_hInstance = hInstance;

    this->pStatic = pStatic;
    this->idResource = idResource;

    this->hEventExit = CreateEvent(NULL, FALSE, FALSE, NULL);

	this->hThread = (HANDLE)_beginthread(CCSplash::ThreadProc, 0, this);
    //this->hThread = CreateThread(NULL, 0, CCSplash::ThreadProc, this, 0, &this->dwThreadId);

	return S_OK;
}

HRESULT CCSplash::Create(POINT pStatic, COLORREF color, CCString FileName)
{
    if(this->hThread) return E_FAIL;

    this->dwLoadFrom = SLF_FILE;

    this->rgbStaticColor = color;

    this->pStatic = pStatic;
    this->sFileName = FileName;

    this->hEventExit = CreateEvent(NULL, FALSE, FALSE, NULL);

	this->hThread = (HANDLE)_beginthread(CCSplash::ThreadProc, 0, this);
    //this->hThread = CreateThread(NULL, 0, CCSplash::ThreadProc, this, 0, &this->dwThreadId);

	return S_OK;
}


HRESULT CCSplash::Draw(HDC dc)
{
    this->Images.Draw(this->nImage, dc, 0, 0);
    RECT rc;

    SelectObject(dc, (HFONT)GetStockObject(DEFAULT_GUI_FONT));
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, this->rgbStaticColor);

    GetClientRect(this->hWnd, &rc);
    rc.left = this->pStatic.x;
    rc.top = this->pStatic.y;

    DrawText(dc, this->sStaticText, this->sStaticText.len(), &rc, DT_SINGLELINE | DT_END_ELLIPSIS);

    return S_OK;
}


HRESULT CCSplash::SetStatusText(CCString s)
{
    this->sStaticText = s;
    this->Invalidate();
    return S_OK;
}


LRESULT CALLBACK CCSplash::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CCSplash* pThis = (CCSplash*) GetWindowLong(hWnd, GWL_USERDATA);

    switch(uMsg)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            pThis->Draw(ps.hdc);
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_SIZE:
        {
            pThis->Size();
            return 0;
        }
    case WM_CREATE:
        {
            CREATESTRUCT * pcs = (CREATESTRUCT*)lParam;
            pThis = (CCSplash*)pcs->lpCreateParams;

            SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void CCSplash::ThreadProc(PVOID p)
{
    CCSplash* pThis = (CCSplash*)p;
	WNDCLASS wc;

    pThis->Images.CreateEmpty(400, 240, ILC_COLOR24);

    if(pThis->dwLoadFrom == SLF_FILE)
    {
        if(FAILED(pThis->Images.AddBitmapFromFile(&pThis->nImage, pThis->sFileName)))
        {
           return;
        }
    }
    else
    {
        if(FAILED(pThis->Images.AddBitmapFromResource(&pThis->nImage, pThis->user_hInstance, pThis->idResource)))
        {
            return;
        }
    }

    IMAGEINFO ii;
    int nHeight;
    int nWidth;
    pThis->Images.GetImageInfo(pThis->nImage, &ii);
    nHeight = ii.rcImage.bottom - ii.rcImage.top;
    nWidth = ii.rcImage.right - ii.rcImage.left;

    SetRect(&pThis->orect, -(nWidth/2), -(nHeight/2), nWidth - (nWidth/2), nHeight - (nHeight/2));
    SetRect(&pThis->prect, 50, 50, 50, 50);

    pThis->hInstance  = GetModuleHandle(NULL);

	pThis->hParent = 0;
	pThis->dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_OVERLAPPED | WS_CLIPCHILDREN;

	wc.cbClsExtra= 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hInstance = pThis->hInstance;
    wc.lpfnWndProc = CCSplash::WndProc;
    wc.lpszClassName = pThis->sClass;
	wc.lpszMenuName = 0;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClass(&wc);

    pThis->hWnd = CreateWindowEx(
        0,//WS_EX_TOPMOST, 
        pThis->sClass, _T(""), pThis->dwStyle,
		0, 0, 1, 1,
		(HWND)pThis->hParent,
		(HMENU)0, pThis->hInstance, pThis);

    pThis->hParent = GetDesktopWindow();

	SendMessage(
		pThis->hWnd, WM_SETFONT,(WPARAM) GetStockObject(DEFAULT_GUI_FONT), 0);
    pThis->SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	pThis->CCControl::Size();
    pThis->AddStyle(WS_VISIBLE);

    // Message loop.
    MSG msg;

    while(1)
    {
        if(WaitForSingleObject(pThis->hEventExit, 0) == WAIT_OBJECT_0)
        {
            break;
        }

        Sleep(0);
        if(PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
        {
            GetMessage(&msg, 0, 0, 0);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Destroy our window.
	DestroyWindow(pThis->hWnd);
    UnregisterClass(pThis->sClass, pThis->hInstance);
    pThis->hWnd = NULL;

    return;
}



