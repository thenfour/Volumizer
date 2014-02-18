

#include "stdafx.h"
#include "CCProgressBar.h"
#include <stdio.h>
#include <tchar.h>


//////////////////////////////////////////////////////////////////////////////
CCProgressBar::CCProgressBar()
{
    this->dwMax = 0;
    this->dwMin = 0;
    this->dwPos = 0;
    this->hBackground = NULL;
    this->hComplete = NULL;
    this->pProc = NULL;
    this->pUserData = NULL;
    this->OldText[0] = 0;
}


//////////////////////////////////////////////////////////////////////////////
CCProgressBar::~CCProgressBar()
{
    //destroy the window if it isn't already.
    //if(IsWindow(this->hWnd) == TRUE) DestroyWindow(this->hWnd);

    if(this->hBackground != NULL)
    {
        DeleteObject(this->hBackground);
    }

    if(this->hComplete != NULL)
    {
        DeleteObject(this->hComplete);
    }
}


/////////////////////////////////////////////////////////////////////////////
//int CCProgressBar::Create(
  //  PROGRESSBARPROC pProc, PVOID pUser, HWND hParent, HINSTANCE hInstance,
   // int x, int y, int w, int h)
int CCProgressBar::Create(PROGRESSBARPROC pProc, PVOID pUser, HWND hParent, const RECT& prect, const RECT& orect)
{
    WNDCLASS wc;

    CopyRect(&m_orect, &orect);
	CopyRect(&m_prect, &prect);

    if(pProc == NULL)
    {
        this->pProc = CCProgressBar::DefaultProc;
        this->pUserData = this;
    }
    else
    {
        this->pProc = pProc;
        this->pUserData = pUser;
    }

    //Create brushes
    this->hBackground = CreateSolidBrush(RGB(255,255,255));
    this->hComplete = CreateSolidBrush(RGB(0,20,244));

    ZeroMemory(&wc, sizeof(wc));
    wc.hbrBackground = this->hBackground;
    wc.hInstance = g_hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpfnWndProc = CCProgressBar::WndProc;
    wc.lpszClassName = PROGRESSBAR_CLASS;
    wc.style = CS_VREDRAW | CS_HREDRAW;
    RegisterClass(&wc);

    m_hWnd = CreateWindow(PROGRESSBAR_CLASS, _T("x"),
        WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hParent, 0, 0, (LPVOID)this);

    SetFont();
    Size();
    Show(TRUE);

    return 0;
}


//////////////////////////////////////////////////////////////////////////////
DWORD CCProgressBar::GetPos()
{
    return this->dwPos;
}


//////////////////////////////////////////////////////////////////////////////
DWORD CCProgressBar::SetPos(DWORD dwNew)
{
    this->InvalidateRange(dwNew, this->dwPos);
    this->dwPos = dwNew;
    return 0;
}


//////////////////////////////////////////////////////////////////////////////
DWORD CCProgressBar::SetMax(DWORD dwNew)
{
    this->dwMax = dwNew;
    if(this->dwMin > dwNew) this->dwMax = this->dwMin;
    this->Invalidate();
    return 0;
}


//////////////////////////////////////////////////////////////////////////////
DWORD CCProgressBar::SetMin(DWORD dwMin)
{
    this->dwMin = dwMin;
    if(this->dwMin > this->dwMax) this->dwMin = this->dwMax;
    Invalidate();
    return 0;
}


//////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK CCProgressBar::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CCProgressBar * pThis = (CCProgressBar*)GetWindowLong(hWnd, GWL_USERDATA);

    switch(uMsg)
    {
    case WM_DESTROY:
        {
            pThis->dwMax = 0;
            pThis->dwMin = 0;
            pThis->dwPos = 0;
            pThis->hBackground = NULL;
            pThis->hComplete = NULL;
            pThis->pProc = NULL;
            pThis->pUserData = NULL;
            pThis->OldText[0] = 0;

            return 0;
        }
    case WM_CREATE:
        {
            LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;
            pThis = (CCProgressBar*)cs->lpCreateParams;
            SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);

            return 0;
        }
    case WM_PAINT:
        pThis->OnPaint();
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//////////////////////////////////////////////////////////////////////////////
inline void CCProgressBar::CorrectBounds()
{
    if(this->dwPos < this->dwMin) this->dwPos = this->dwMin;
    if(this->dwPos > this->dwMax) this->dwPos = this->dwMax;
}

//////////////////////////////////////////////////////////////////////////////
void CCProgressBar::OnPaint()
{
    PAINTSTRUCT ps;
    BeginPaint(m_hWnd, &ps);

    SetBkMode(ps.hdc, TRANSPARENT);

    SelectObject(ps.hdc, this->m_hFont);

    RECT rcClientRect;
    GetClientRect(m_hWnd, &rcClientRect);
    InflateRect(&rcClientRect, -2,-2);//this will make the DrawFrame() function look nicer

    DWORD Range = this->dwMax - this->dwMin;

    //Get the pixel offset of the completed area.
    float Ratio = (float)this->dwPos / (float)Range;
    int nOffset = (int)(Ratio * rcClientRect.right);

    //Get the RECT for completed area
    RECT rcComplete;
    SetRect(&rcComplete, 0, 0, nOffset, rcClientRect.bottom);

    //Get the RECT for the rest
    RECT rcTheRest;
    SetRect(&rcTheRest, nOffset, 0, rcClientRect.right, rcClientRect.bottom);

    //Get the percent, text, and size of the text...
    TCHAR * wszPercent = this->OldText;
    this->pProc(this->pUserData, this, wszPercent);

    SIZE TextSize;
    GetTextExtentPoint32(ps.hdc, wszPercent, wcslen(wszPercent), &TextSize);

    //Figure out where to draw the text
    RECT rcTextBounds;
    rcTextBounds.top = 0;
    rcTextBounds.bottom = rcClientRect.bottom;
    rcTextBounds.left = (rcClientRect.right / 2) - (TextSize.cx / 2);
    rcTextBounds.right = (rcClientRect.right / 2) + (TextSize.cx / 2);

    RECT rcTextComplete;
    RECT rcTextTheRest;

    CopyRect(&rcTextComplete, &rcTextBounds);
    CopyRect(&rcTextTheRest, &rcTextBounds);
    rcTextComplete.right = rcComplete.right;
    rcTextTheRest.left = rcTheRest.left;

    FillRect(ps.hdc, &rcComplete, this->hComplete);
    FillRect(ps.hdc, &rcTheRest, this->hBackground);

    if(wszPercent[0])
    {
        //Draw the completed text.
        SetTextColor(ps.hdc, RGB(255,255,255));
        HRGN hTextComplete = CreateRectRgn(
            rcTextComplete.left,
            rcTextComplete.top,
            rcTextComplete.right,
            rcTextComplete.bottom);
        SelectClipRgn(ps.hdc, hTextComplete);
        DrawText(ps.hdc, wszPercent, wcslen(wszPercent), &rcTextBounds, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        DeleteObject(hTextComplete);

        //Draw the completed text.
        SetTextColor(ps.hdc, RGB(0,0,255));
        HRGN hTextTheRest = CreateRectRgn(
            rcTextTheRest.left,
            rcTextTheRest.top,
            rcTextTheRest.right,
            rcTextTheRest.bottom);
        SelectClipRgn(ps.hdc, hTextTheRest);
        DrawText(ps.hdc, wszPercent, wcslen(wszPercent), &rcTextBounds, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        DeleteObject(hTextTheRest);
    }

    //And draw a frame around it.
    GetClientRect(m_hWnd, &rcClientRect);//refresh this because we changed it above
    HRGN hEntireRect = CreateRectRgn(
        rcClientRect.left,
        rcClientRect.top,
        rcClientRect.right,
        rcClientRect.bottom);
    SelectClipRgn(ps.hdc, hEntireRect);

    DrawEdge(ps.hdc, &rcClientRect, EDGE_SUNKEN, BF_RECT);
    DeleteObject(hEntireRect);

    EndPaint(m_hWnd, &ps);
}


//////////////////////////////////////////////////////////////////////////////
void CALLBACK CCProgressBar::DefaultProc(LPVOID pUser, CCProgressBar* pBar, PWSTR Text)
{
    DWORD Range = (pBar->GetMax() - pBar->GetMin());
    swprintf(Text, L"%3d%%", (DWORD)(100 * ((float)pBar->GetPos() / (float)Range)));
}


void CALLBACK CCProgressBar::DefaultProcNoText(PVOID pUser, CCProgressBar* pBar, PWSTR Text)
{
    Text[0] = 0;
}


//////////////////////////////////////////////////////////////////////////////
DWORD CCProgressBar::GetMax()
{
    return this->dwMax;
}


//////////////////////////////////////////////////////////////////////////////
DWORD CCProgressBar::GetMin()
{
    return this->dwMin;
}


void CCProgressBar::InvalidateRange(DWORD dwMin, DWORD dwMax)
{
    RECT rc;
    DWORD dwWindowWidth;

    GetClientRect(m_hWnd, &rc);
    dwWindowWidth = rc.right;
    rc.left = _ValueToPos(dwMin, dwWindowWidth);
    rc.right = _ValueToPos(dwMax, dwWindowWidth);
    if(rc.left > rc.right)
    {
        // swap! (the 'slow' way)
        int temp = rc.left;
        rc.left = rc.right;
        rc.right = temp;
    }
    rc.left -= 5;
    rc.right += 5;
    InvalidateRect(m_hWnd, &rc, FALSE);
}


int CCProgressBar::ValueToPos(DWORD dwValue)
{
    RECT rc;
    DWORD dwWindowWidth;

    GetClientRect(m_hWnd, &rc);
    dwWindowWidth = rc.right;
    return _ValueToPos(dwValue, dwWindowWidth);
}


int CCProgressBar::_ValueToPos(DWORD dwValue, DWORD dwWindowWidth)
{
    // v/total = r/width
    // r = (v*width)/total
    return MulDiv((int)dwValue, (int)dwWindowWidth, (int)(this->dwMax-this->dwMin));
}

