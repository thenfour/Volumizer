

#include "stdafx.h"
#include "CCControl.h"


/*
    Some interesting helper-functions
*/
int GetWindowHeight(HWND hWnd)
{
    RECT rc;
    GetWindowRect(hWnd, &rc);
    return rc.bottom - rc.top;
}


int GetWindowWidth(HWND hWnd)
{
    RECT rc;
    GetWindowRect(hWnd, &rc);
    return rc.right - rc.left;
}


int SetWindowHeight(HWND hWnd, int n)
{
    if(!SetWindowPos(hWnd, 0, 0, 0, GetWindowWidth(hWnd), n, SWP_NOMOVE | SWP_NOZORDER))
    {
        return 0;
    }

    return 0;
}


int SetWindowWidth(HWND hWnd, int n)
{
    if(!SetWindowPos(hWnd, 0, 0, 0, n, GetWindowHeight(hWnd), SWP_NOMOVE | SWP_NOZORDER))
    {
        return 0;
    }

    return 0;
}


int ScreenToClient(HWND hWnd, LPRECT prc)
{
    POINT p[2] = {prc->left, prc->top, prc->right, prc->bottom};
    ScreenToClient(hWnd, &p[0]);
    ScreenToClient(hWnd, &p[1]);

    SetRect(prc, p[0].x, p[0].y, p[1].x, p[1].y);

    return 0;
}


/*
    The window's top and left edges stay in place.

    First adjust window rect using API
    Then check the client size - adjust again if necessary, loop.
*/
HRESULT SetWindowClientArea(HWND hWnd, int DesiredX, int DesiredY)
{
    {
        RECT rc;
        DWORD dwStyle = 0;
        DWORD dwExStyle = 0;
        BOOL bMenu = 0;

        if(IsWindow(hWnd) == FALSE) return E_FAIL;

        // Fill in bMenu
        bMenu = TRUE;
        if(GetMenu(hWnd) == NULL) bMenu = FALSE;

        // Fill in styles
        dwStyle = GetWindowLong(hWnd, GWL_STYLE);
        dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);

        // Fill in rc
        GetWindowRect(hWnd, &rc);
        rc.bottom = rc.top + DesiredY;
        rc.right = rc.left + DesiredX;

        // Now get the window rect.
        AdjustWindowRectEx(&rc, dwStyle, bMenu, dwExStyle);

        // Actually adjust the window.
        MoveWindow(hWnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);
    }

    // Check to make sure.
    {
        RECT rcClient;
        RECT rcWindow;
        int x = 0;// Difference, X
        int y = 0;// Difference, Y
        int c = 0;// Count how many times we've looped - we'll only do it a maximum
                  // of three times.

        GetClientRect(hWnd, &rcClient);
        y = DesiredY - (rcClient.bottom - rcClient.top);
        x = DesiredX - (rcClient.right - rcClient.left);

        while(((x+y)!=0) && (c<3))
        {
            // There is a difference in the ACTUAL client area and the DESIRED
            // client area.  Add or subtract to the window size to get it right.
            GetWindowRect(hWnd, &rcWindow);

            MoveWindow(hWnd, rcWindow.left, rcWindow.top,
                rcWindow.right + x, rcWindow.bottom + y, TRUE);

            // Calculate the difference.
            GetClientRect(hWnd, &rcClient);
            y = DesiredY - (rcClient.bottom - rcClient.top);
            x = DesiredX - (rcClient.right - rcClient.left);

            c++;
        }
    
        if((x+y)!=0) return E_FAIL;
    }

    return S_OK;
}


HRESULT CenterWindow(HWND hWnd, HWND hParent)
{
    RECT rcParentClient;
    RECT rcWnd;
    int nHeight = 0;// These are actually divided by 2
    int nWidth = 0;
    int nCenterX = 0;// Center coords of the parent window
    int nCenterY = 0;

    if(hParent == NULL) hParent = GetDesktopWindow();

    GetWindowRect(hWnd, &rcWnd);
    GetClientRect(hParent, &rcParentClient);

    // Calculate it
    nHeight = (rcWnd.bottom - rcWnd.top)/2;
    nWidth = (rcWnd.right - rcWnd.left)/2;

    nCenterX = (rcParentClient.right - rcParentClient.left) / 2;
    nCenterY = (rcParentClient.bottom - rcParentClient.top) / 2;

    MoveWindow(hWnd,
        nCenterX - nWidth,
        nCenterY - nHeight,
        nWidth*2,
        nHeight*2,
        TRUE);

    return S_OK;
}


// Instantiate statics.
UINT CCControl::NextId = 500;


CCControl::CCControl()
{
	m_hWnd = 0;
	m_hFont = 0;
	ZeroMemory(&m_prect, sizeof(RECT));
	ZeroMemory(&m_orect, sizeof(RECT));

	m_id = CCControl::NextId;
	CCControl::NextId++;
}


CCControl::~CCControl()
{
    _FreeFont();
    Destroy();
}


CCControl::operator HWND()
{
    return m_hWnd;
}


CCControl::operator UINT()
{
    return m_id;
}


HRESULT CCControl::SetRedraw(BOOL b)
{
    SendMessage(m_hWnd, WM_SETREDRAW, b, 0);
    return S_OK;
}


HRESULT CCControl::Sizing(WPARAM wParam, LPARAM lParam, POINT* pMin)
{
	RECT* pRect = (RECT*)lParam;
	int w = pRect->right - pRect->left;
	int h = pRect->bottom - pRect->top;

	if(w < pMin->x)
    {
		switch(wParam)
        {
		case WMSZ_BOTTOMLEFT:
		case WMSZ_LEFT:
		case WMSZ_TOPLEFT:
			//adjust the left side.
			pRect->left = pRect->right - pMin->x;
			break;

		case WMSZ_BOTTOMRIGHT:
		case WMSZ_RIGHT:
		case WMSZ_TOPRIGHT:
			//adjust the left side.
			pRect->right = pRect->left + pMin->x;
			break;
		}
	}

	if(h < pMin->y)
    {
		switch(wParam)
        {
		case WMSZ_TOPRIGHT:
		case WMSZ_TOP:
		case WMSZ_TOPLEFT:
			//adjust the left side.
			pRect->top = pRect->bottom - pMin->y;
			break;

		case WMSZ_BOTTOMLEFT:
		case WMSZ_BOTTOM:
		case WMSZ_BOTTOMRIGHT:
			//adjust the left side.
			pRect->bottom = pRect->top + pMin->y;
			break;
		}
	}

	return TRUE;
}


UINT CCControl::GetId()
{
	return m_id;
}


HWND CCControl::GethWnd()
{
	return m_hWnd;
}


HWND CCControl::GetParent()
{
    return ::GetParent(m_hWnd);
}


void CCControl::_FreeFont()
{
	if(m_hFont)
    {
		DeleteObject(m_hFont);
		m_hFont = 0;
	}

    return;
}


HRESULT CCControl::SetFont()
{
    HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, FALSE);

    _FreeFont();

    return S_OK;
}


HRESULT CCControl::SetFont(HFONT hFont, BOOL bAutoFree)
{
    SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
    
    _FreeFont();

    if(bAutoFree == TRUE)
    {
        m_hFont = hFont;
    }

    return S_OK;
}


HRESULT CCControl::SetFont(PCWSTR wszFontName, int nPoints)
{

    if(wszFontName)
    {
        HFONT hFont = 0;
        HDC hDC = GetDC(m_hWnd);

        int nHeight = -MulDiv(nPoints, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	    hFont = CreateFont(
		    nHeight,0,0,0,0,0,0,0,DEFAULT_CHARSET,0,0,0,0,wszFontName);

        ReleaseDC(m_hWnd, hDC);

	    SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
        _FreeFont();
        m_hFont = hFont;
    }
    else
    {
        //hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	    SendMessage(m_hWnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
        _FreeFont();
    }

	return S_OK;
}


HRESULT CCControl::Size()
{
	RECT rcNew;
	RECT rcClient;
	int cx = 0;
    int cy = 0;

    if(m_hWnd)
    {
        if(!GetClientRect(::GetParent(m_hWnd), &rcClient))
        {
            GetClientRect(GetDesktopWindow(), &rcClient);
        }

		ControlRectToRect(&rcNew, &m_prect, &m_orect, &rcClient);

		cy = rcNew.bottom - rcNew.top;
		cx = rcNew.right - rcNew.left;

		if(!SetWindowPos(m_hWnd, 0, rcNew.left, rcNew.top, cx, cy, SWP_NOZORDER))
        {
			return E_FAIL;
		}
	}

	return S_OK;
}


/*
    Converts a control's placement to actual positioning.
    Uses the parent's client rect, a percentag-rect, and an offset-rect to
    calculate the new client coords for the control.
*/
HRESULT CCControl::ControlRectToRect(RECT* prcNew, RECT* pprect, 
									 RECT* porect, RECT* pParentClient)
{
    int nParentW = pParentClient->right - pParentClient->left;
    int nParentH = pParentClient->bottom - pParentClient->top;

    /*
        Scale it.

        prtop     (n)
        ----- = -------
         100    parenth

        prtop * parenth / 100 = n
    */
	prcNew->top = pprect->top * nParentH / 100;
	prcNew->left = pprect->left * nParentW / 100;
	prcNew->bottom = pprect->bottom * nParentH / 100;
	prcNew->right = pprect->right * nParentW / 100;
	prcNew->top += porect->top + pParentClient->top;
	prcNew->left += porect->left + pParentClient->left;
	prcNew->bottom += porect->bottom +pParentClient->top;
	prcNew->right += porect->right + pParentClient->left;

	return S_OK;
}


HRESULT CCControl::GetPlacement(RECT* pprect, RECT* porect)
{
	if(pprect)
    {
		CopyRect(pprect, &m_prect);
	}

	if(porect)
    {
		CopyRect(porect, &m_orect);
	}

	return S_OK;
}


void CCControl::Destroy()
{
    if(::IsWindow(m_hWnd))
    {
        DestroyWindow(m_hWnd);
    	m_hWnd = 0;
    }
}


DWORD CCControl::GetStyle()
{
    return GetWindowLong(m_hWnd, GWL_STYLE);
}


DWORD CCControl::GetExStyle()
{
    return GetWindowLong(m_hWnd, GWL_EXSTYLE);
}


void CCControl::SetStyle(DWORD dw)
{
    SetWindowLong(m_hWnd, GWL_STYLE, dw);
}


void CCControl::SetExStyle(DWORD dw)
{
    SetWindowLong(m_hWnd, GWL_EXSTYLE, dw);
}


void CCControl::Invalidate()
{
    InvalidateRect(m_hWnd, NULL, FALSE);
}


void CCControl::RemoveStyle(DWORD s)
{
    DWORD dw = GetStyle();
    dw &= ~s;
    SetStyle(dw);
}


void CCControl::RemoveExStyle(DWORD s)
{
    DWORD dw = GetExStyle();
    dw &= ~s;
    SetExStyle(dw);
}


void CCControl::AddExStyle(DWORD s)
{
    SetExStyle(GetExStyle() | s);
}


void CCControl::AddStyle(DWORD s)
{
    SetStyle(GetStyle() | s);
}


#if(WINVER >= 0x0500) && (_WIN32_WINNT >= 0x0500)

void CCControl::SetColorKey(COLORREF rgb)
{
    AddExStyle(WS_EX_LAYERED);
    SetLayeredWindowAttributes(m_hWnd, rgb, NULL, LWA_COLORKEY);
}


void CCControl::SetTransparency(BYTE b)
{
    AddExStyle(WS_EX_LAYERED);
    SetLayeredWindowAttributes(m_hWnd, NULL, b, LWA_ALPHA);
}

#endif


void CCControl::Invalidate(const RECT* rc)
{
    InvalidateRect(m_hWnd, rc, FALSE);
}


void CCControl::SetText(PCWSTR wsz)
{
    SetWindowText(m_hWnd, wsz);
}


void CCControl::Show(BOOL b)
{
    ShowWindow(m_hWnd, b == TRUE ? SW_SHOW : SW_HIDE);
}


/*
    This function will attach this window to the specified window.
    In this way we can use these classes for windows that weren't
    created using the classes.  For instance, dialog box items.
*/
HRESULT CCControl::TakeOver(HWND hWnd)
{
    if(::IsWindow(hWnd) == FALSE) return E_FAIL;

    m_hWnd = hWnd;

    SetRect(&m_prect, 0, 0, 0, 0);
    GetWindowRect(hWnd, &m_orect);

    if(::GetParent(hWnd))
    {
        ScreenToClient(::GetParent(hWnd), &m_orect);
    }

    m_hInstance = 0;
    m_id = GetDlgCtrlID(hWnd);

    return S_OK;
}


int CCControl::GetText(PWSTR wsz, DWORD cchMax)
{
    return GetWindowText(m_hWnd, wsz, cchMax);
}


int CCControl::GetTextLength()
{
    return GetWindowTextLength(m_hWnd);
}


HRESULT CCControl::SetPlacement(RECT* pprect, RECT* porect)
{
    if(pprect)
    {
        CopyRect(&m_prect, pprect);
    }
    if(porect)
    {
        CopyRect(&m_orect, porect);
    }

    Size();

    return S_OK;
}


void CCControl::Enable(BOOL b)
{
    EnableWindow(m_hWnd, b);
}


BOOL CCControl::IsWindow()
{
    return ::IsWindow(m_hWnd);
}


