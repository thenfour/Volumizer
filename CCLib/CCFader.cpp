

#include "stdafx.h"
#include "CCFader.h"
#include <Windowsx.h>
#include <tchar.h>


//////////////////////////////////////////////////////////////////////////////
CCFader::~CCFader()
{
    //this->Destroy();
}


//////////////////////////////////////////////////////////////////////////////
CCFader::CCFader()
{
    this->nPos = 0;
    this->nHigh = 0;
    this->nLow = 0;
}


void CCFader::Destroy()
{
    SAFE_DELETEOBJECT(this->hBackground);
    SAFE_DELETEOBJECT(this->hCenterLine);
    SAFE_DELETEOBJECT(this->hFader);
    SAFE_DELETEOBJECT(this->hSlit);
    SAFE_DELETEOBJECT(this->hTickMarks);

	if(n_hWnd) DestroyWindow(n_hWnd);

	UnregisterClass(this->sClass, this->hInstance);
    n_hWnd = 0;
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CCFader::Create(HWND hParent, HINSTANCE hInstance, RECT prect, RECT orect)
{
	WNDCLASS wc;

    this->hBackground = CreateSolidBrush(RGB(40,40,60));
    this->hCenterLine = CreateSolidBrush(RGB(255,255,255));
    this->hFader = CreateSolidBrush(RGB(96,96,128));
    this->hSlit = CreateSolidBrush(RGB(0,0,0));
    this->hTickMarks = CreateSolidBrush(RGB(255,255,255));

    this->hInstance  = hInstance;

	CopyRect(&this->orect, &orect);
	CopyRect(&this->prect, &prect);

	this->hParent = hParent;
	this->dwStyle = WS_CHILD | WS_VISIBLE;

 	this->sClass.FormatW(L"CCFader 0x%X", this->GetId());

	wc.cbClsExtra= 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
    wc.lpfnWndProc = CCFader::WndProc;
	wc.lpszClassName = this->sClass;
	wc.lpszMenuName = 0;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClass(&wc);

	this->hWnd = CreateWindowEx(0, this->sClass, _T(""), this->dwStyle,
		0, 0, 1, 1,
		this->hParent,
		(HMENU)0, hInstance, this);

    this->bIsTracking = FALSE;

	return S_OK;
}


LRESULT CALLBACK CCFader::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CCFader* pThis = (CCFader*)GetWindowLongPtr(hWnd, GWL_USERDATA);

    switch(uMsg)
    {
    case WM_LBUTTONDOWN:
        {
            if(pThis->bIsTracking == FALSE)
            {
                SetCapture(hWnd);
                pThis->bIsTracking = TRUE;
                pThis->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            }
            return 0;
        }
    case WM_MOUSEMOVE:
        {
            pThis->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        }
    case WM_LBUTTONUP:
        {
            if(pThis->bIsTracking == TRUE)
            {
                pThis->bIsTracking = FALSE;
                ReleaseCapture();
            }
            return 0;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            pThis->Draw(ps.hdc);
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_CREATE:
        {
            CREATESTRUCT * pcs = (CREATESTRUCT*)lParam;
            pThis = (CCFader*)pcs->lpCreateParams;
            SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void CCFader::OnMouseMove(int x, int y)
{
    if(this->bIsTracking == TRUE)
    {
        this->nPos = this->PixelsToPosition(y);

        NMHDR nmh;
        nmh.code = CCF_POSCHANGED;
        nmh.hwndFrom = this->hWnd;
        nmh.idFrom = this->id;
        SendMessage(GetParent(this->hWnd), WM_NOTIFY, this->id, (LPARAM)&nmh);
        this->Invalidate();
    }
}


HRESULT CCFader::SetPos(int nPos)
{
    if(nPos > this->nHigh) nPos = this->nHigh;
    if(nPos < this->nLow) nPos = this->nLow;

    this->nPos = nPos;
    this->Invalidate();
    return S_OK;
}


int CCFader::GetPos()
{
    return this->nPos;
}

HRESULT CCFader::SetBounds(int nLow, int nHigh)
{
    this->nLow = min(nLow, nHigh);
    this->nHigh = max(nLow, nHigh);

    if(this->nPos > this->nHigh) this->nPos = this->nHigh;
    if(this->nPos < this->nLow) this->nPos = this->nLow;

    return S_OK;
}


HRESULT CCFader::GetBounds(int* pnLow, int* pnHigh)
{
    if(pnLow) *pnLow = this->nLow;
    if(pnHigh) *pnHigh = this->nHigh;

    return S_OK;
}


void CCFader::Draw(HDC dc)
{
    RECT rc;

    GetClientRect(this->hWnd, &rc);

    FillRect(dc, &rc, this->hBackground);
    this->_DrawTicks(dc);
    this->_DrawSlit(dc);
    this->_DrawCursor(dc);
}


void CCFader::_DrawTicks(HDC dc)
{
}


#define CURSOR_SIZEY 8
void CCFader::_DrawCursor(HDC dc)
{
    RECT rc;
    RECT rcClient;
    GetClientRect(this->hWnd, &rcClient);
    int nPos = this->PositionToPixels(this->nPos);

    SetRect(&rc, rcClient.left, nPos - (CURSOR_SIZEY/2), rcClient.right, nPos + (CURSOR_SIZEY/2));
    FillRect(dc, &rc, this->hFader);
    SetRect(&rc, rcClient.left, nPos - 1, rcClient.right, nPos + 1);
    FillRect(dc, &rc, this->hCenterLine);
}


void CCFader::_DrawSlit(HDC dc)
{
    RECT rc;
    GetClientRect(this->hWnd, &rc);

    int nWidth = (rc.right - rc.left) / 2;

    rc.left = nWidth - 3;
    rc.right = nWidth + 3;

    FillRect(dc, &rc, this->hSlit);
}


int CCFader::PositionToPixels(int nPos)
{
    RECT rcClient;
    int nWidth;
    int nResult;
    GetClientRect(this->hWnd, &rcClient);

    if((this->nHigh - this->nLow) == 0) return 0;

    nWidth = rcClient.bottom - rcClient.top;

    nResult = rcClient.bottom - ((nWidth * nPos) / (this->nHigh - this->nLow));
    if(nResult < rcClient.top) return 0;
    if(nResult > rcClient.bottom) return rcClient.bottom;

    return nResult;
}


int CCFader::PixelsToPosition(int nPixels)
{
    RECT rcClient;
    int nWidth;
    int nResult;
    GetClientRect(this->hWnd, &rcClient);

    if((this->nHigh - this->nLow) == 0) return 0;

    nWidth = rcClient.bottom - rcClient.top;

    nResult = ((rcClient.bottom - nPixels) * (this->nHigh - this->nLow)) / nWidth;
    if(nResult > this->nHigh) return this->nHigh;
    if(nResult < this->nLow) return this->nLow;

    return nResult;
}

