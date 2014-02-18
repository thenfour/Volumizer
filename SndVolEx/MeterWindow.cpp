

#include "stdafx.h"
#include "MeterWindow.h"


CMeterWindow::CMeterWindow()
{
    m_Meter.SetDefaultSize(300,150);
}


CMeterWindow::~CMeterWindow()
{
    Hide();
}

/*
void CMeterWindow::Entry(HWND hParent, IMixer* pMixer, METER_THEME* pTheme, BOOL bTheme)
{
    BSTR strName = 0;
    int nMeterH = 0;
    int nMeterW = 0;
    DWORD dwMixerID = 0;
    RECT orect, prect;

    // Destroy our stuff!
    m_Main.Destroy();
    m_Meter.Destroy();

    m_Meter.SetTheme(pTheme, bTheme);

    nMeterH = m_Meter.GetHeight();
    nMeterW = m_Meter.GetWidth();

    // Create the main window.  The size is the size of the progress bar + the combo box.
    SetRect(&prect, 50, 50, 50, 50);
    SetRect(&orect, -10, -10, 10, 10);// this is only temporary.

    m_Main.Create(L"Level Meter", hParent, CMeterWindow::WndProc, g_hInstance, 
        prect, orect, WS_SYSMENU | WS_MINIMIZEBOX, this, IDI_ICON1);

    // Create the meter window.
    SetRect(&prect, 0, 0, 0, 0);
    SetRect(&orect, 0, 0, nMeterW, nMeterH);
    m_Meter.Create(g_hInstance, m_Main, 0, 0, orect, prect);

    // Create the combo box.
    SetRect(&prect, 0, 0, 0, 0);
    SetRect(&orect, 0, nMeterH, nMeterW, 400);
    m_Select.Create(m_Main, prect, orect);

    // Fill in information in the select combo box
    {
        IMixerLibrary* pLibrary = 0;
        IEnumMixers* pEnum = 0;
        IMixer* pMix = 0;// the enumerated mixer.
        BSTR strMixer = 0;
        ULONG ul = 0;
        int i = 0;// index of inserted item.
        IUnknown* pUnk1 = 0;
        IUnknown* pUnk2 = 0;

        pMixer->get_owner(&pLibrary);
        pLibrary->EnumMixers(&pEnum);
        pLibrary->Release();

        while(1)
        {
            pEnum->Next(1, &pMix, &ul);
            if(ul == 0) break;
            pMix->get_name(&strMixer);
            m_Select.AddString(strMixer, 0);
            SysFreeString(strMixer);

            // See if this is the one we're supposed to be selecting
            pMixer->QueryInterface(IID_IUnknown, (void**)&pUnk1);
            pMix->QueryInterface(IID_IUnknown, (void**)&pUnk2);

            if(pUnk1 == pUnk2)
            {
                // Select this one.
                SendMessage(m_Select, CB_SETCURSEL, i, 0);
            }

            pUnk1->Release();
            pUnk2->Release();
            pMix->Release();
        }

        pEnum->Release();
    }

    // Make the main window the right size.
    SetRect(&orect, 0, 0, nMeterW, nMeterH + GetWindowHeight(m_Select));
    SetWindowClientArea(m_Main, orect.right, orect.bottom);

    m_Main.Show(TRUE);
    pMixer->get_mixerid(&dwMixerID);
    pMixer->get_name(&strName);

    if(FAILED(m_Meter.StartCapture(dwMixerID, strName)))
    {
        MsgBoxf(L"Failed to start audio capture for the level meter.  The audio device may already be in use, or does not support this operation.");
        m_Meter.Destroy();
        m_Main.Destroy();
        SetActiveWindow(hParent);
    }

    SysFreeString(strName);

    return;
}
*/


LRESULT CALLBACK CMeterWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CMeterWindow* pThis = (CMeterWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(uMsg)
    {
    case WM_KEYDOWN:
        {
            if(wParam == VK_ESCAPE)
            {
                SendMessage(hWnd, WM_CLOSE, 0, 0);
                return 0;
            }
            break;
        }
    case WM_WINDOWPOSCHANGED:
        {
            return 0;
        }
    case WM_COMMAND:
        {
            if(LOWORD(wParam) == pThis->m_Select.GetId())
            {
                if(HIWORD(wParam) == CBN_SELCHANGE)
                {
                    // The user changed the selection.
                    int nSel = 0;
                    int nLen = 0;
                    WCHAR* wszName = 0;
                    void* pUser = 0;

                    nSel = pThis->m_Select.GetSelectedIndex();
                    nLen = pThis->m_Select.GetStringLen(nSel)+1;

                    wszName = (WCHAR*)malloc(nLen*sizeof(WCHAR));
                    wszName[0] = 0;

                    pThis->m_Select.GetItemData(nSel, wszName, &nLen, &pUser);

                    pThis->m_Meter.StopCapture();
                    pThis->m_Meter.StartCapture((int)pUser, wszName);

                    free(wszName);
                    wszName = 0;
                    return 0;
                }
            }
            break;
        }
    case WM_DESTROY:
        {
            pThis->m_Meter.StopCapture();

            HWND hParent = GetParent(hWnd);
            ShowWindow(hParent, SW_SHOW);
            SetForegroundWindow(hParent);
            SetActiveWindow(hParent);
            SetFocus(hParent);

            return 0;
        }
    case WM_CLOSE:
        {
            DestroyWindow(hWnd);
            return 0;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_CREATE:
        {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            pThis = (CMeterWindow*)pcs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


/*
    Completely gets rid of this window - destroys it, stops capture.
*/
HRESULT CMeterWindow::Hide()
{
    m_Meter.StopCapture();
    m_Main.Destroy();
    m_Meter.Destroy();
    m_Select.Destroy();
    return S_OK;
}


/*
    Shows the windows and sets up everything, but capture will not run.
*/
HRESULT CMeterWindow::Show(HWND hParent)
{
    // If the windows are not created yet, create them.
    if(m_Main.IsWindow() == FALSE)
    {
        RECT prect;
        RECT orect;

        SetRect(&prect, 0, 0, 0, 0);
        SetRect(&orect, 0, 0, 10, 10);

        m_Main.Create(L"Level Meter", hParent, CMeterWindow::WndProc, g_hInstance, 
            prect, orect, WS_SYSMENU | WS_MINIMIZEBOX, this, IDI_ICON1);

        // Create the meter window.
        m_Meter.Create(g_hInstance, m_Main, 0, 0, orect, prect);

        // Create the combo box.
        m_Select.Create(m_Main, prect, orect);
    }

    // Fill in information in the select combo box
    {
        HRESULT hr = 0;
        IMixerLibrary* pLibrary = 0;
        IEnumMixers* pEnum = 0;
        IMixer* pMix = 0;// the enumerated mixer.
        BSTR strMixer = 0;
        ULONG ul = 0;
        int i = 0;// index of inserted item.
        DWORD dwMixerID = 0;

        if(FAILED(hr = CoCreateInstance(CLSID_MixerLibrary, 0, CLSCTX_INPROC_SERVER, IID_IMixerLibrary, (void**)&pLibrary)))
        {
            return E_FAIL;
        }

        pLibrary->EnumMixers(&pEnum);

        while(1)
        {
            pEnum->Next(1, &pMix, &ul);
            if(ul == 0) break;
            pMix->get_name(&strMixer);
            pMix->get_mixerid(&dwMixerID);

            m_Select.AddString(strMixer, 0, (void*)dwMixerID);

            SysFreeString(strMixer);
            pMix->Release();
        }

        pEnum->Release();
        pLibrary->Release();
    }

    _SizeupControls();

    return S_OK;
}


/*
    Tells the object what theme to use for the meter.  If it's displayed right now,
    then it will take effect immediately.  If not, then these settings will be used
    when it IS shown.
*/
HRESULT CMeterWindow::SetTheme(METER_THEME* pTheme, BOOL bTheme)
{
    HRESULT hr = 0;

    if(SUCCEEDED(hr = m_Meter.SetTheme(pTheme, bTheme)))
    {
        _SizeupControls();
    }
    return S_OK;
}


HRESULT CMeterWindow::SetMixer(IMixer* pMixer)
{
    DWORD dwMixerID = 0;
    BSTR strName = 0;

    pMixer->get_mixerid(&dwMixerID);
    pMixer->get_name(&strName);

    if(FAILED(m_Meter.StartCapture(dwMixerID, strName)))
    {
        MsgBoxf(L"Failed to start audio capture for the level meter.  The audio device may already be in use, or does not support this operation.");
    }
    else
    {
        // Select the rigt combobox item.
        m_Select.SelectUserData((void*)dwMixerID);
    }

    SysFreeString(strName);

    return S_OK;
}


void CMeterWindow::_SizeupControls()
{
    RECT orect;
    RECT prect;
    int nMeterH = 0;
    int nMeterW = 0;

    nMeterH = m_Meter.GetHeight();
    nMeterW = m_Meter.GetWidth();

    // Create the meter window.
    SetRect(&prect, 0, 0, 0, 0);
    SetRect(&orect, 0, 0, nMeterW, nMeterH);
    m_Meter.SetPlacement(&prect, &orect);

    // Create the combo box.
    SetRect(&prect, 0, 0, 0, 0);
    SetRect(&orect, 0, nMeterH, nMeterW, 400);
    m_Select.SetPlacement(&prect, &orect);

    // Make the main window the right size.
    SetRect(&orect, 0, 0, nMeterW, nMeterH + GetWindowHeight(m_Select));
    SetWindowClientArea(m_Main, orect.right, orect.bottom);

    CenterWindow(m_Main, 0);
    m_Main.Show(TRUE);

    return;
}


BOOL CMeterWindow::IsDisplayed()
{
    return m_Main.IsWindow();
}


