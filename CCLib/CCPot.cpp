

#include "stdafx.h"
#include "CCPot.h"

#include <math.h>
#include <windowsx.h>


void CopyPotTheme(POT_THEME* pDest, const POT_THEME* pSrc)
{
    CopyRect(&pDest->rcMute, &pSrc->rcMute);
    pDest->ptBalCenter.x = pSrc->ptBalCenter.x;
    pDest->ptBalCenter.y = pSrc->ptBalCenter.y;
    pDest->nBalLength = pSrc->nBalLength;
    pDest->nVolumeTop = pSrc->nVolumeTop;
    pDest->nVolumeBottom = pSrc->nVolumeBottom;
    pDest->clrBack = pSrc->clrBack;
    pDest->clrBal = pSrc->clrBal;
    pDest->clrText = pSrc->clrText;
    pDest->nBalAngleRestriction = pSrc->nBalAngleRestriction;
    pDest->sThumb = pSrc->sThumb;
    pDest->sBack = pSrc->sBack;
    pDest->sOn = pSrc->sOn;
    pDest->sOff = pSrc->sOff;
    pDest->sBal = pSrc->sBal;
    pDest->nBalXPlacement = pSrc->nBalXPlacement;
    pDest->nBalYPlacement = pSrc->nBalYPlacement;
    pDest->nMuteXPlacement = pSrc->nMuteXPlacement;
    pDest->nMuteYPlacement = pSrc->nMuteYPlacement;
    pDest->sFont = pSrc->sFont;
    pDest->nFontSize = pSrc->nFontSize;
    CopyRect(&pDest->rcText, &pSrc->rcText);
}


/*
    Instantiate statics.
*/
int CCPot::m_nRefCt = 0;
CSimpleImage CCPot::m_Back;
CSimpleImage CCPot::m_Thumb;
CSimpleImage CCPot::m_On;
CSimpleImage CCPot::m_Off;
CSimpleImage CCPot::m_Bal;
POT_THEME CCPot::m_CurrentTheme;
HBRUSH CCPot::m_hBackColor = 0;
HPEN CCPot::m_hBalPen = 0;
HBITMAP CCPot::m_hBuffer = 0;
BOOL CCPot::m_bTheme = FALSE;
HFONT CCPot::m_hGlobalFont = 0;


CCPot::CCPot()
{
    m_nRefCt ++;

    if(m_nRefCt == 1)
    {
        CCPotNoTheme::Startup();
    }

    m_nVol = 0;
    m_bMute = 0;
    m_nBal = 0;

    m_pUser = 0;

    m_bUseVol = TRUE;
    m_State = POT_IDLE;
    m_bUseBal = TRUE;
    m_bUseMute = TRUE;
}


CCPot::~CCPot()
{
    if(::IsWindow(m_hWnd))
    {
        DestroyWindow(m_hWnd);
    }

    m_hWnd = 0;

    // Free all resources
    CCPot::m_nRefCt --;

    if(CCPot::m_nRefCt == 0)
    {
        CCPot::FreeTheme();
        CCPotNoTheme::Shutdown();
    }
}


COLORREF CCPot::GetGlobalBackColor()
{
    return m_CurrentTheme.clrBack;
}


int CCPot::GetGlobalWidth()
{
    if(CCPot::m_bTheme == FALSE) return CCPotNoTheme::GetGlobalWidth();

    return m_Back.m_bm.bmWidth;
}


int CCPot::GetGlobalHeight()
{
    if(CCPot::m_bTheme == FALSE) return CCPotNoTheme::GetGlobalHeight();
    return m_Back.m_bm.bmHeight;
}


/*
    Completely rips out old theme stuff and places new stuff
    in there.
*/
void CCPot::SetTheme(POT_THEME* pThemeData, BOOL bEnabled)
{
    m_bTheme = bEnabled;

    if(bEnabled == FALSE) return;

    CopyPotTheme(&m_CurrentTheme, pThemeData);

    // Load our images.
    m_Back.Load(pThemeData->sBack);
    m_On.Load(pThemeData->sOn);
    m_Off.Load(pThemeData->sOff);
    m_Thumb.Load(pThemeData->sThumb);
    m_Bal.Load(pThemeData->sBal);

    m_hBackColor = CreateSolidBrush(pThemeData->clrBack);
    m_hBalPen = CreatePen(PS_SOLID, 3, pThemeData->clrBal);

    // Create our back buffer.
    HDC dcScreen = GetDC(0);
    m_hBuffer = CreateCompatibleBitmap(dcScreen, CCPot::GetGlobalWidth(), CCPot::GetGlobalHeight());
    ReleaseDC(0, dcScreen);

    // Create the font
    m_hGlobalFont = 0;// this will default to the default gui font.
    if(pThemeData->sFont.len() > 0)
    {
        HDC hDC = GetDC(0);
        int nHeight = -MulDiv(pThemeData->nFontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	    m_hGlobalFont = CreateFont(
		    nHeight,0,0,0,0,0,0,0,DEFAULT_CHARSET,0,0,0,0,pThemeData->sFont);
        ReleaseDC(0, hDC);
    }
}


void CCPot::FreeTheme()
{
    m_Thumb.Free();
    m_Back.Free();
    m_On.Free();
    m_Off.Free();
    m_Bal.Free();

    DeleteObject(m_hBuffer);

    if(m_hBackColor) { DeleteObject(m_hBackColor); m_hBackColor = 0; }
    if(m_hBalPen) { DeleteObject(m_hBalPen); m_hBalPen = 0; }
    if(m_hGlobalFont) { DeleteObject(m_hGlobalFont); m_hGlobalFont = 0; }
}


void CCPot::_RegisterWindowClass()
{
    WNDCLASSEX wcx = {0};
    wcx.cbSize = sizeof(wcx);
    wcx.hbrBackground = CCPot::m_hBackColor;
    wcx.hCursor = LoadCursor(0, IDC_ARROW);
    wcx.hInstance = g_hInstance;
    wcx.lpfnWndProc = CCPot::WndProc;
    wcx.lpszClassName = POT_CLASS;
    wcx.style = CS_VREDRAW | CS_HREDRAW;
    RegisterClassEx(&wcx);
}


HRESULT CCPot::Create(HWND hParent, int x, int y)
{
    if(m_bTheme == FALSE) return m_NoTheme.Create(hParent, x, y, this);

    _RegisterWindowClass();

    SetRect(&m_prect, 0, 0, 0, 0);
    SetRect(&m_orect, x, y, x+m_Back.m_bm.bmWidth, y+m_Back.m_bm.bmHeight);

    m_hWnd = CreateWindowEx(0, POT_CLASS, L"(unknown)",
        WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hParent, (HMENU)m_id,
        0, this);

    m_sText = L"(unknown)";

    return S_OK;
}


void CCPot::UseMute(BOOL b)
{
    if(b == m_bUseMute) return;
    if(m_bTheme == FALSE) return m_NoTheme.UseMute(b);

    m_bUseMute = b;
    Invalidate();
}


void CCPot::UseBal(BOOL b)
{
    if(b == m_bUseBal) return;
    if(m_bTheme == FALSE) return m_NoTheme.UseBal(b);

    m_bUseBal = b;
    Invalidate();
}


void CCPot::UseVol(BOOL b)
{
    if(b == m_bUseVol) return;
    if(m_bTheme == FALSE) return m_NoTheme.UseVol(b);

    m_bUseVol = b;
    Invalidate();
}


int CCPot::GetVol()
{
    if(m_bTheme == FALSE) return m_NoTheme.GetVol();
    return m_nVol;
}


BOOL CCPot::GetMute()
{
    if(m_bTheme == FALSE) return m_NoTheme.GetMute();
    return m_bMute;
}


int CCPot::GetBal()
{
    if(m_bTheme == FALSE) return m_NoTheme.GetBal();
    return m_nBal;
}


void CCPot::SetVol(int n)
{
    if(m_bTheme == FALSE)
    {
        m_NoTheme.SetVol(n);
        return;
    }

    m_nVol = n;

    NMHDR nmh;
    nmh.code = PN_VOL;
    nmh.hwndFrom = m_hWnd;
    nmh.idFrom = m_id;
    SendMessage(::GetParent(m_hWnd), WM_NOTIFY, (WPARAM)m_id, (LPARAM)&nmh);

    Invalidate();
}


void CCPot::SetMute(BOOL b)
{
    if(m_bTheme == FALSE)
    {
        m_NoTheme.SetMute(b);
        return;
    }

    m_bMute = b;

    NMHDR nmh;
    nmh.code = PN_MUTE;
    nmh.hwndFrom = m_hWnd;
    nmh.idFrom = m_id;
    SendMessage(::GetParent(m_hWnd), WM_NOTIFY, (WPARAM)m_id, (LPARAM)&nmh);

    RECT rc = 
    {
        0,
        m_Back.m_bm.bmHeight-m_On.m_bm.bmHeight,
        m_Back.m_bm.bmWidth,
        m_Back.m_bm.bmHeight
    };

    Invalidate(&rc);
}


void CCPot::SetBal(int n)
{
    if(m_bTheme == FALSE)
    {
        m_NoTheme.SetBal(n);
        return;
    }

    m_nBal = n;

    NMHDR nmh;
    nmh.code = PN_BAL;
    nmh.hwndFrom = m_hWnd;
    nmh.idFrom = m_id;
    SendMessage(::GetParent(m_hWnd), WM_NOTIFY, (WPARAM)m_id, (LPARAM)&nmh);

    RECT rc = 
    {
        0,
        0,
        m_Back.m_bm.bmWidth,
        m_Bal.m_bm.bmHeight
    };

    Invalidate(&rc);
}


void CCPot::SetUserData(void* p)
{
    m_pUser = p;
}


void* CCPot::GetUserData()
{
    return m_pUser;
}


void CCPot::Draw(HDC dcWnd)
{
    HDC dc = CreateCompatibleDC(NULL);
    SelectObject(dc, m_hBuffer);

    // Draw the background.
    m_Back.Blt(dc, 0, 0);

    if(m_bUseMute == TRUE)
    {
        int x = m_CurrentTheme.nMuteXPlacement;
        int y = m_CurrentTheme.nMuteYPlacement;
        if(x == -1) x = 0;
        if(y == -1) y = m_Back.m_bm.bmHeight - m_Off.m_bm.bmHeight;
        if(m_bMute == TRUE)
        {
            m_Off.Blt(dc, x, y);
        }
        else
        {
            m_On.Blt(dc, x, y);
        }
    }

    // Draw the thumb.
    int x, y;

    if(m_bUseVol)
    {
        x = m_CurrentTheme.ptBalCenter.x - (m_Thumb.m_bm.bmWidth / 2);// Compensate for thumb width.
        y = ValueToY(m_nVol);

        // Now compensate for the thumb height.
        y -= m_Thumb.m_bm.bmHeight / 2;
        m_Thumb.Blt(dc, x, y);
    }

    /*
        Now draw the cool little rotating dealie.
    */
    if(m_bUseBal == TRUE)
    {
        int xBal = m_CurrentTheme.nBalXPlacement;
        int yBal = m_CurrentTheme.nBalYPlacement;
        if(xBal == -1) xBal = 0;
        if(yBal == -1) yBal = 0;
        m_Bal.Blt(dc, xBal, yBal);

        Balance_ValueToPoint(m_nBal, &x, &y);

        SelectObject(dc, m_hBalPen);
        MoveToEx(dc, m_CurrentTheme.ptBalCenter.x, m_CurrentTheme.ptBalCenter.y, 0);
        LineTo(dc, x, y);
    }

    // Draw the text.
    SelectObject(dc, (HFONT)GetStockObject(DEFAULT_GUI_FONT));
    SetTextColor(dc, m_CurrentTheme.clrText);
    SetBkMode(dc, TRANSPARENT);
    
    // initialize with defaults.
    RECT rc = {0, 0, m_Back.m_bm.bmWidth, m_CurrentTheme.nVolumeTop};
    if((m_CurrentTheme.rcText.bottom != 0)&&(m_CurrentTheme.rcText.right != 0))
    {
        CopyRect(&rc, &m_CurrentTheme.rcText);
    }

    if(m_hGlobalFont)
    {
        SelectObject(dc, m_hGlobalFont);
    }
    else
    {
        SelectObject(dc, GetStockObject(DEFAULT_GUI_FONT));
    }

    DrawText(dc, m_sText, m_sText.len(), &rc, DT_NOCLIP | DT_CENTER);

    // Blit that bitmap to the actual screen.
    BitBlt(dcWnd, 0, 0, CCPot::GetGlobalWidth(), CCPot::GetGlobalHeight(),
        dc, 0, 0, SRCCOPY);

    DeleteDC(dc);

    return;
}


void CCPot::Balance_ValueToPoint(int nVal, int* px, int* py)
{
    int nAngleRange = 0;
    int nAngleStart = 0;
    double fAngle = 0;

    // Validate / Adjust arguments.
    if(nVal < POT_BAL_MIN) nVal = POT_BAL_MIN;
    if(nVal > POT_BAL_MAX) nVal = POT_BAL_MAX;

    // Try to calculate the angle at which this value will sit.

    // Figure out the range of angles that valid values
    // correspond to.
    nAngleRange = 360 - (m_CurrentTheme.nBalAngleRestriction*2);

    // Figure out what angle POT_BAL_MIN corresponds to.
    nAngleStart = 270-m_CurrentTheme.nBalAngleRestriction;

    /*  Now scale nVal from (nAngleStart) through (nAngleStart-nAngleRange);

            (nVal-POT_BAL_MIN)        (nAngleStart-nAngle)
        -------------------------  =  --------------------
        (POT_BAL_MAX-POT_BAL_MIN)         (nAngleRange)
    */
    fAngle = nVal-POT_BAL_MIN;
    fAngle *= nAngleRange;
    fAngle /= (double)(POT_BAL_MAX-POT_BAL_MIN);
    fAngle -= nAngleStart;
    fAngle = -fAngle;

    // Now that we know the angle that we're dealing with,
    // we can get the point easily with a function call.
    _PointFromAngle(px, py, fAngle);

    return;
}


int CCPot::Balance_PointToValue(int x, int y)
{
    int nAngleRange = 0;
    int nAngleStart = 0;
    double fAngle = 0;
    double fVal = 0;// We make it a double to preserve some precision during calculations.

    // Figure out the range of angles that valid values correspond to.
    nAngleRange = 360 - (m_CurrentTheme.nBalAngleRestriction*2);

    // Figure out what angle POT_BAL_MIN corresponds to.
    nAngleStart = 270-m_CurrentTheme.nBalAngleRestriction;
    
    // Figure out what angle this thing's at.
    fAngle = _AngleFromPoint(x, y);

    // Adjust fAngle so that it's from 0 to nAngleRange.
    if(fAngle >=270) fAngle = -(360-fAngle);
    fAngle = (double)nAngleStart - fAngle;

    // Interpret out-of-bounds values
    if(fAngle < 0) return POT_BAL_MIN;
    if(fAngle >= nAngleRange) return POT_BAL_MAX;

    /*  Now scale fAngle from (0) through (nAngleRange);

            (fVal-POT_BAL_MIN)          fAngle
        -------------------------  =  -----------
        (POT_BAL_MAX-POT_BAL_MIN)     nAngleRange
    */
    fVal = fAngle*(POT_BAL_MAX-POT_BAL_MIN);
    fVal /= (double)nAngleRange;
    fVal += POT_BAL_MIN;

    return (int)fVal;
}


/*
    Returns client coordinates based on an angle.

    The returned point is the outer point of the "hash mark"
    or "thumb" on the balance pot.
*/
void CCPot::_PointFromAngle(int* px, int* py, double fAngle)
{
    double x, y;

    // Convert fAngle from degrees to radians.
    fAngle *= 3.1415926535;
    fAngle /= 180.00000000;

    // Get x
    x = cos(fAngle);
    x *= m_CurrentTheme.nBalLength;

    // Get y
    y = sin(fAngle);
    y *= m_CurrentTheme.nBalLength;

    *px = m_CurrentTheme.ptBalCenter.x + (int)x;
    *py = m_CurrentTheme.ptBalCenter.y - (int)y;

    return;
}


/*
    Takes client coords and turns it into an angle,
    in DEGREES, not radians.
*/
double CCPot::_AngleFromPoint(int x, int y)
{
    double a;

    // Adjust x and y to fit into the good old
    // geometric coord system, and to be relative
    // to the center of the pot.
    y = m_CurrentTheme.ptBalCenter.y - y;
    x = x - m_CurrentTheme.ptBalCenter.x;

    // Get the actual angle.  Since trig is screwed up
    // we will have to adjust the angles based on
    // the sign of x and y. (positive vs. negative).
    a = atan2(abs(y), abs(x));
    a *= 180;
    a /= 3.141592654;

    // Now adjust for the REAL angle (since trig is screwy).
    if(y<0) a = -a;
    if(x<0) a = 180-a;

    while(a < 0) a += 360;

    return a;
}


int CCPot::ValueToY(int v)
{
    int y = 0;
    /*
        -- some quick chicken scratches:

        ((POT_VOL_MAX-m_nVol)-POT_VOL_MIN)           (y-POT_VOL_TOP)
        ----------------------------------  =  ----------------------------
            (POT_VOL_MAX-POT_VOL_MIN)          (POT_VOL_BOTTOM-POT_VOL_TOP)
    */

    y = (POT_VOL_MAX-v) - POT_VOL_MIN;
    y *= m_CurrentTheme.nVolumeBottom - m_CurrentTheme.nVolumeTop;
    y /= (POT_VOL_MAX - POT_VOL_MIN);
    y += m_CurrentTheme.nVolumeTop;

    return y;
}


int CCPot::YToValue(int y)
{
    int n = 0;

    // First check bounds.
    if(y <= m_CurrentTheme.nVolumeTop) return POT_VOL_MAX;
    if(y >= m_CurrentTheme.nVolumeBottom) return POT_VOL_MIN;

    int nPixelRange = (m_CurrentTheme.nVolumeBottom-m_CurrentTheme.nVolumeTop);
    int nValueRange = (POT_VOL_MAX-POT_VOL_MIN);
    y -= m_CurrentTheme.nVolumeTop;

    /*
        y               (POT_VOL_MAX-n)
        -----------  =  ---------------
        nPixelRange     nValueRange
    */
    n = nValueRange * y;
    n /= nPixelRange;
    n -= POT_VOL_MAX;
    n = -n;

    return n;
}


void CCPot::OnLButtonDown(int x, int y)
{
    if(m_State == POT_IDLE)
    {
        // Do a little hit testing.
        if((y <= m_Bal.m_bm.bmHeight) && (m_bUseBal == TRUE))
        {
            // We're doin the balance pot!
            m_State = POT_BAL;
            m_nOriginalValue = m_nBal;
            SetCapture(m_hWnd);
            OnMouseMove(x, y);
        }
        else if(_HitMute(x, y) && (m_bUseMute == TRUE))
        {
            // User is clicking on the MUTE button.
            m_State = POT_MUTE;
            m_nOriginalValue = m_bMute;
            SetCapture(m_hWnd);
            OnMouseMove(x, y);
        }
        else if((y >= (m_CurrentTheme.nVolumeTop-m_Thumb.m_bm.bmHeight)) && (y <= (m_CurrentTheme.nVolumeBottom+m_Thumb.m_bm.bmHeight)))
        {
            if(m_bUseVol == TRUE)
            {
                // Volume fader.
                m_State = POT_VOL;
                m_nOriginalValue = m_nVol;
                SetCapture(m_hWnd);
                OnMouseMove(x, y);
            }
        }
    }
}


void CCPot::OnLButtonUp(int x, int y)
{
    switch(m_State)
    {
    case POT_MUTE:
    case POT_BAL:
    case POT_VOL:
        ReleaseCapture();
        m_State = POT_IDLE;
        break;
    case POT_IDLE:
    default:
        break;
    }
}


BOOL CCPot::_HitMute(int x, int y)
{
    POINT pt = {x, y};
    return PtInRect(&m_CurrentTheme.rcMute, pt);
}


void CCPot::OnMouseMove(int x, int y)
{
    switch(m_State)
    {
    case POT_MUTE:
        if(_HitMute(x, y) == TRUE)
        {
            SetMute(m_nOriginalValue == TRUE ? FALSE : TRUE);
            break;
        }
        else
        {
            SetMute(m_nOriginalValue == FALSE ? FALSE : TRUE);
            break;
        }
        break;
    case POT_BAL:
        // Adjust the volume fader.
        SetBal(Balance_PointToValue(x, y));
        break;
    case POT_VOL:
        // Adjust the volume fader.
        SetVol(YToValue(y));
        break;
    case POT_IDLE:
    default:
        break;
    }
}


LRESULT CALLBACK CCPot::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CCPot* pThis = (CCPot*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(uMsg)
    {
    case WM_SETTEXT:
        {
            pThis->m_sText = (PCWSTR)lParam;
            pThis->Invalidate();
            return 0;
        }
    case WM_LBUTTONDOWN:
        {
            pThis->OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        }
    case WM_LBUTTONUP:
        {
            pThis->OnLButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;
        }
    case WM_MOUSEMOVE:
        {
            pThis->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
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
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            pThis = (CCPot*)pcs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void CCPot::Destroy()
{
    if(m_bTheme == FALSE) 
    {
        m_NoTheme.Destroy();
        return;
    }

    CCControl::Destroy();
    return;
}
