

#include "stdafx.h"
#include "splash.h"


#define VOLUMIZER_SPLASH_WND_PROP L"VolumizerInfoPtr"


CVolumizerSplash::CVolumizerSplash()
{
}


CVolumizerSplash::~CVolumizerSplash()
{
}


bool CVolumizerSplash::Show(int nDaysLeft, CVolumizerRegistrationInterface* pReg)
{
    /// load the splash bitmap
    m_Image.OleLoad(g_hInstance, MAKEINTRESOURCE(IDR_SPLASH), L"OL_BIN");

    m_pReg = pReg;

    RECT prect, orect;
    SetRect(&prect, 50, 50, 50, 50);
    SetRect(&orect, 0, 0, m_Image.m_bm.bmWidth, m_Image.m_bm.bmHeight);
    m_MainWnd.Create(L"OneLight Volumizer Evaluation Version", 0,
        CVolumizerSplash::WndProc, g_hInstance, prect, orect, WS_BORDER, this, IDI_ICON1);

    {
        // Size and center the window correctly.
        AdjustWindowRectEx(&orect, m_MainWnd.GetStyle(), FALSE, m_MainWnd.GetExStyle());
        int halfw = (orect.right - orect.left)/2;
        int halfh = (orect.bottom - orect.top)/2;
        SetRect(&orect, -halfw, -halfh, halfw, halfh);
        m_MainWnd.SetPlacement(&prect, &orect);
        m_MainWnd.Size();
    }

    int y = 64;
    int x = 22;
    int w = 75;
    int h = 25;
    int spacer = 6;
    int freq = h+spacer;

    SetRect(&prect, 0, 0, 0, 0);
    SetRect(&orect, x, y, x+w, y+h);
    m_cClose.Create(L"&Close", m_MainWnd, g_hInstance, prect, orect);
    y += freq;

    SetRect(&prect, 0, 0, 0, 0);
    SetRect(&orect, x, y, x+w, y+h);
    m_cEULA.Create(L"&License", m_MainWnd, g_hInstance, prect, orect);
    y += freq;

    SetRect(&prect, 0, 0, 0, 0);
    SetRect(&orect, x, y, x+w, y+h);
    m_cOrder.Create(L"&Register", m_MainWnd, g_hInstance, prect, orect);
    y += freq;

    SetRect(&prect, 0, 0, 0, 0);
    SetRect(&orect, x, y, x+w, y+h);
    m_cOk.Create(L"&Ok", m_MainWnd, g_hInstance, prect, orect);
    m_cOk.AddStyle(BS_DEFPUSHBUTTON);
    y += freq;

    GetClientRect(m_MainWnd, &m_rcTimeLeft);
    m_rcTimeLeft.top  = 0;
    m_rcTimeLeft.left = x;
    m_rcTimeLeft.bottom -= spacer;
    m_sTimeLeft.FormatW(L"You have %d days left in your evaluation", nDaysLeft);

    m_bKeepGoing = true;
    m_bClose = false;

    m_cOk.Enable(FALSE);
    m_MainWnd.Show(TRUE);
    SetFocus(m_cOk);

    if(nDaysLeft > 0) SetTimer(m_MainWnd, 0, (EVAL_PERIOD - nDaysLeft)*266, 0);

    MSG msg;
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

    if(nDaysLeft > 0) KillTimer(m_MainWnd, 0);

    m_Image.Free();

    return !m_bClose;
}


LRESULT CALLBACK CVolumizerSplash::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CVolumizerSplash* pThis = (CVolumizerSplash*)GetProp(hWnd, VOLUMIZER_SPLASH_WND_PROP);

    switch(uMsg)
    {
    case WM_TIMER:
        {
            if(pThis)
            {
                SetFocus(pThis->m_cOk);
                pThis->m_cOk.Enable(TRUE);
            }
            return 0;
        }
    case WM_CREATE:
        {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            pThis = (CVolumizerSplash*)pcs->lpCreateParams;
            SetProp(hWnd, VOLUMIZER_SPLASH_WND_PROP, (HANDLE)pThis);
            return 0;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            pThis->m_Image.Blt(ps.hdc, 0, 0);
            SetBkMode(ps.hdc, TRANSPARENT);
            SelectObject(ps.hdc, GetStockObject(DEFAULT_GUI_FONT));
            SetTextColor(ps.hdc, RGB(0,0,0));
            DrawText(ps.hdc, pThis->m_sTimeLeft, pThis->m_sTimeLeft.len(), &pThis->m_rcTimeLeft, DT_SINGLELINE | DT_NOPREFIX | DT_BOTTOM | DT_NOCLIP);
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_COMMAND:
        {
            HWND hCtrl = (HWND)lParam;
            if(hCtrl == pThis->m_cEULA.GethWnd())
            {
                // show the eula.
                CCString path;
                GetModuleFileName(NULL, path.GetBuffer(MAX_PATH), MAX_PATH);
                path.Path_StripToPath();
                path.Path_Append(L"eula.txt");
                CCString cd;
                cd.Path_GetCurrentDirectory();
                ShellExecute(0, NULL, path, NULL, cd, SW_SHOW);
                return 0;
            }
            else if(hCtrl == pThis->m_cOk.GethWnd())
            {
                DestroyWindow(hWnd);
                return 0;
            }
            else if(hCtrl == pThis->m_cClose.GethWnd())
            {
                pThis->m_bClose = true;
                DestroyWindow(hWnd);
                return 0;
            }
            else if(hCtrl == pThis->m_cOrder.GethWnd())
            {
                // show registration dialog.
                pThis->m_pReg->DoRegistrationDialog(hWnd);

                if(pThis->m_pReg->RegKeyValid())
                {
                    SetFocus(pThis->m_cOk);
                    pThis->m_cOk.Enable(TRUE);
                }

                // show the order form.
                //CCString path;
                //GetModuleFileName(NULL, path.GetBuffer(MAX_PATH), MAX_PATH);
                //path.Path_StripToPath();
                //path.Path_Append(L"order.rtf");
                //CCString cd;
                //cd.Path_GetCurrentDirectory();
                //ShellExecute(0, NULL, path, NULL, cd, SW_SHOW);
                return 0;
            }
            return 0;
        }
    case WM_CLOSE:
        {
            return 0;
        }
    case WM_DESTROY:
        pThis->m_bKeepGoing = false;
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


