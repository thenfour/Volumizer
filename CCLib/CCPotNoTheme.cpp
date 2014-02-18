

#include "stdafx.h"
#include "CCPotNoTheme.h"
#include "CCPot.h"


#define WEIRD_TO_NORMAL(min, max, n) ( (max)-(n)+(min) )


HWND CCPotNoTheme::m_hExample = 0;


CCPotNoTheme::CCPotNoTheme()
{
    m_pOwner = 0;
}


CCPotNoTheme::~CCPotNoTheme()
{
}


HRESULT CCPotNoTheme::Create(HWND hParent, int x, int y, class CCPot* pOwner)
{
    m_pOwner = pOwner;

    // Create the dialog to stick inside of the main window.
    m_pOwner->m_hWnd = CreateDialogParam(g_hRes, 
        MAKEINTRESOURCE(IDD_POTNOTHEME), 
        hParent, CCPotNoTheme::DlgProc, (LPARAM)this);

    SetWindowPos(m_pOwner->m_hWnd, 0, x, y, 0, 0, 
        SWP_NOSIZE | SWP_NOZORDER);

    SendDlgItemMessage(m_pOwner->m_hWnd, IDC_VOLUME, TBM_SETRANGEMIN,
        FALSE, POT_VOL_MIN);

    SendDlgItemMessage(m_pOwner->m_hWnd, IDC_VOLUME, TBM_SETRANGEMAX,
        FALSE, POT_VOL_MAX);

    SendDlgItemMessage(m_pOwner->m_hWnd, IDC_VOLUME, TBM_SETTICFREQ,
        11000, 0);

    SendDlgItemMessage(m_pOwner->m_hWnd, IDC_BALANCE, TBM_SETRANGEMIN,
        FALSE, POT_BAL_MIN);

    SendDlgItemMessage(m_pOwner->m_hWnd, IDC_BALANCE, TBM_SETRANGEMAX,
        FALSE, POT_BAL_MAX);

    SendDlgItemMessage(m_pOwner->m_hWnd, IDC_BALANCE, TBM_SETTICFREQ,
        (POT_BAL_MAX-POT_BAL_MIN)/2, 0);

    pOwner->Show(TRUE);

    return S_OK;
}


int CCPotNoTheme::GetVol()
{
    return WEIRD_TO_NORMAL(POT_VOL_MIN, POT_VOL_MAX, 
        SendDlgItemMessage(m_pOwner->m_hWnd, IDC_VOLUME, TBM_GETPOS, 0, 0));
}


BOOL CCPotNoTheme::GetMute()
{
    return m_bMute;
    UINT ui = IsDlgButtonChecked(m_pOwner->m_hWnd, IDC_MUTE);
    return (ui == BST_UNCHECKED) ? TRUE : FALSE;
}


int CCPotNoTheme::GetBal()
{
    return SendDlgItemMessage(m_pOwner->m_hWnd, IDC_BALANCE, TBM_GETPOS, 0, 0);
}


void CCPotNoTheme::SetVol(int n)
{
    SendDlgItemMessage(m_pOwner->m_hWnd, IDC_VOLUME, TBM_SETPOS, TRUE, 
        (LPARAM)WEIRD_TO_NORMAL(POT_VOL_MIN, POT_VOL_MAX, n));
}


void CCPotNoTheme::SetMute(BOOL b)
{
    CheckDlgButton(m_pOwner->m_hWnd, IDC_MUTE, 
        (b == FALSE) ? BST_CHECKED : BST_UNCHECKED);
    m_bMute = b;
}


void CCPotNoTheme::SetBal(int n)
{
    SendDlgItemMessage(m_pOwner->m_hWnd, IDC_BALANCE, TBM_SETPOS, TRUE, (LPARAM)n);
}


void CCPotNoTheme::UseMute(BOOL b)
{
    EnableWindow(GetDlgItem(m_pOwner->m_hWnd, IDC_MUTE), b);
    if(b == FALSE)
    {
        SetMute(FALSE);
    }
}


void CCPotNoTheme::UseBal(BOOL b)
{
    EnableWindow(GetDlgItem(m_pOwner->m_hWnd, IDC_BALANCE), b);
    if(b == FALSE)
    {
        SetBal((POT_BAL_MAX-POT_BAL_MIN)/2);
    }
}


void CCPotNoTheme::UseVol(BOOL b)
{
    EnableWindow(GetDlgItem(m_pOwner->m_hWnd, IDC_VOLUME), b);
    if(b == FALSE)
    {
        SetVol((POT_VOL_MAX-POT_VOL_MIN)/2);
    }
}


int CCPotNoTheme::GetGlobalWidth()
{
    RECT rc = { 0, 0, 60, 150 };
    MapDialogRect(m_hExample, &rc);
    return rc.right;
}


int CCPotNoTheme::GetGlobalHeight()
{
    RECT rc = { 0, 0, 60, 150 };
    MapDialogRect(m_hExample, &rc);
    return rc.bottom;
}


void CCPotNoTheme::Destroy()
{
    if(m_pOwner) EndDialog(m_pOwner->m_hWnd, 0);
}


void CCPotNoTheme::SendNotification(UINT uMsg)
{
    NMHDR nmh;

    nmh.code = uMsg;
    nmh.hwndFrom = m_pOwner->m_hWnd;
    nmh.idFrom = m_pOwner->GetId();

    SendMessage(::GetParent(m_pOwner->m_hWnd), WM_NOTIFY, 
        (WPARAM)m_pOwner->GetId(), (LPARAM)&nmh);

    return;
}


INT_PTR CALLBACK CCPotNoTheme::DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CCPotNoTheme* pThis = (CCPotNoTheme*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    switch(uMsg)
    {
    case WM_HSCROLL:
        {
            if(LOWORD(wParam) == TB_THUMBTRACK)
            {
                // User is moving the balance slider.
                pThis->SendNotification(PN_BAL);
            }
            return TRUE;
        }
    case WM_VSCROLL:
        {
            if(LOWORD(wParam) == TB_THUMBTRACK)
            {
                // User is moving the volume slider.
                pThis->SendNotification(PN_VOL);
            }
            return TRUE;
        }
    case WM_COMMAND:
        {
            // User is toggling the mute switch.
            if(LOWORD(wParam) == IDC_MUTE)
            {
                pThis->SendNotification(PN_MUTE);
            }
            return TRUE;
        }
    case WM_SETTEXT:
        {
            SetDlgItemText(hWnd, IDC_NAME, (PCWSTR)lParam);
            return TRUE;
        }
    case WM_INITDIALOG:
        {
            pThis = (CCPotNoTheme*)lParam;
            
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            return TRUE;
        }
    }

    return FALSE;
}


void CCPotNoTheme::Startup()
{
    m_hExample = CreateDialogParam(g_hRes, MAKEINTRESOURCE(IDD_POTNOTHEME),
        GetDesktopWindow(), CCPotNoTheme::ExampleProc, 0);
}


void CCPotNoTheme::Shutdown()
{
    EndDialog(m_hExample, 0);
    m_hExample = 0;
}


INT_PTR CALLBACK CCPotNoTheme::ExampleProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}


