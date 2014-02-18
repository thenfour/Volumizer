

#include "stdafx.h"
#include "about.h"


#define VOLUMIZER_ABOUT_WND_PROP L"VolumizerInfoPtr"


CVolumizerAbout::CVolumizerAbout()
{
}


CVolumizerAbout::~CVolumizerAbout()
{
}


bool CVolumizerAbout::Entry(HWND hParent, CAppSettings& Settings)
{
    /// load the splash bitmap
    m_Image.OleLoad(g_hInstance, MAKEINTRESOURCE(IDR_SPLASH), L"OL_BIN");

    RECT prect, orect;
    SetRect(&prect, 50, 50, 50, 50);
    SetRect(&orect, 0, 0, m_Image.m_bm.bmWidth, m_Image.m_bm.bmHeight);
    m_MainWnd.Create(L"OneLight Volumizer", 0,
        CVolumizerAbout::WndProc, g_hInstance, prect, orect, WS_BORDER, this, IDI_ICON1);

    {
        // Size and center the window correctly.
        AdjustWindowRectEx(&orect, m_MainWnd.GetStyle(), FALSE, m_MainWnd.GetExStyle());
        int halfw = (orect.right - orect.left)/2;
        int halfh = (orect.bottom - orect.top)/2;
        SetRect(&orect, -halfw, -halfh, halfw, halfh);
        m_MainWnd.SetPlacement(&prect, &orect);
        m_MainWnd.Size();
    }

    //------------------
    int xpad = 22;
    int ypad = 14;
    int button_w = 75;
    int button_h = 25;
    SetRect(&prect, 0, 100, 0, 100);
    SetRect(&orect, xpad, -(ypad+button_h), xpad+button_w, -ypad);
    m_cOk.Create(L"Ok", m_MainWnd, g_hInstance, prect, orect);
    m_cOk.AddStyle(BS_DEFPUSHBUTTON);

    SetRect(&prect, 0, 0, 0, 100);
    SetRect(&orect, xpad, 57, xpad+225, -(ypad+button_h+6));
    m_cInfo.CreateMultiline(m_MainWnd, g_hInstance, prect, orect);
    m_cInfo.SetReadOnly(TRUE);

    // generate text to stick in there.
    CCString s(L"OneLight Volumizer 1.0\r\n(c) 2003 OneLight Software\r\n\r\n");
    s.cat(L"Registered to: ");
    s.cat(Settings.m_szName);
    s.cat(L"\r\nOrganization: ");
    s.cat(Settings.m_szOrganization);
    m_cInfo.SetText(s);

    // get the background brush for the edit box.
    m_hbr = CreatePatternBrush(m_Image.hbm());

    //------------------
    m_MainWnd.Show(TRUE);
    SetFocus(m_cOk);

    MSG msg;
    m_bKeepGoing = true;
    while(m_bKeepGoing)
    {
        if(GetMessage(&msg, 0, 0, 0))
        {
            if(!IsDialogMessage(m_MainWnd, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    DeleteObject(m_hbr);

    m_Image.Free();

    return true;
}


LRESULT CALLBACK CVolumizerAbout::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CVolumizerAbout* pThis = (CVolumizerAbout*)GetProp(hWnd, VOLUMIZER_ABOUT_WND_PROP);

    switch(uMsg)
    {
    case WM_CREATE:
        {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            pThis = (CVolumizerAbout*)pcs->lpCreateParams;
            SetProp(hWnd, VOLUMIZER_ABOUT_WND_PROP, (HANDLE)pThis);
            return 0;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            pThis->m_Image.Blt(ps.hdc, 0, 0);
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_COMMAND:
        {
            HWND hCtrl = (HWND)lParam;

            if(hCtrl == pThis->m_cOk.GethWnd())
            {
                DestroyWindow(hWnd);
                return 0;
            }

            return 0;
        }
    case WM_CLOSE:
        {
            DestroyWindow(hWnd);
            return 0;
        }
    case WM_DESTROY:
        {
            pThis->m_bKeepGoing = false;
            return 0;
        }
    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLOREDIT:
        {
            HDC dc = (HDC)wParam;
            HWND hCtl = (HWND)lParam;
            if(hCtl == pThis->m_cInfo)
            {
                SetBkMode(dc, TRANSPARENT);
                return (LRESULT)pThis->m_hbr;
            }
            break;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

