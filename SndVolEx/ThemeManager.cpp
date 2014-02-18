

#include "stdafx.h"
#include "ThemeManager.h"
#include "CApp.h"


CThemeManager::CThemeManager()
{
    m_pOwner = 0;
    m_bThemesEnabled = TRUE;
}


CThemeManager::~CThemeManager()
{
}


void FixThemePath(PCWSTR wszRoot, CCString& File)
{
    if(File.Path_IsRelative() == TRUE)
    {
        CCString sTemp = wszRoot;
        sTemp.Path_Append(File);

        File = sTemp;
    }
}


HRESULT CThemeManager::LoadTheme()
{
    HRESULT hr;

    if(FAILED(hr = GetDataFromRegistry()))
    {
        odsf(L"ThemeManager::LoadTheme()", L"Failed to restore and/or load default theme data.  themes.xml may be corrupt.");
        return hr;
    }

    return LoadTheme(m_sThemeFile);
}


HRESULT CThemeManager::LoadTheme(PCWSTR wszFile)
{
    HRESULT hr;
    CXMLConfig Theme;
    CCString sValue;
    CCString sRootPath;

    // Fix the wszFile so that it's ABSOLUTE, not relative.
    GetModuleFileName(NULL, sRootPath.GetBuffer(MAX_PATH), MAX_PATH);
    sRootPath.Path_StripToPath();
    sRootPath.Path_Append(wszFile);

    if(FAILED(hr = Theme.Open(sRootPath, L"Theme")))
    {
        odsf(L"ThemeManager::LoadTheme()", L"Could not open the specific theme file, '%s'.  It may be missing or invalid.", (PCWSTR)sRootPath);
        return hr;
    }

    // In order to get the correct path for all the relative paths in the XML file,
    // grab the directory that the XML file is in.
    CCString sThemePath = sRootPath;
    sThemePath.Path_StripToPath();

    // Grab all the relevant settings.
    if(FAILED(Theme.GetSetting(L"ChannelStrip/MuteButton/Setting[@name=\"OnImage\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/MuteButton/OnImage is invalid.");
    }
    m_Pot.sOn = sValue;
    FixThemePath(sThemePath, m_Pot.sOn);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/MuteButton/Setting[@name=\"OffImage\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/MuteButton/OffImage is invalid");
    }
    m_Pot.sOff = sValue;
    FixThemePath(sThemePath, m_Pot.sOff);

    m_Pot.nMuteXPlacement = -1;
    if(FAILED(Theme.GetSetting(L"ChannelStrip/MuteButton/Setting[@name=\"PlacementX\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/MuteButton/PlacementX is invalid");
    }
    else
    {
        m_Pot.nMuteXPlacement = sValue.tol(10);
    }

    m_Pot.nMuteYPlacement = -1;
    if(FAILED(Theme.GetSetting(L"ChannelStrip/MuteButton/Setting[@name=\"PlacementY\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/MuteButton/PlacementY is invalid");
    }
    else
    {
        m_Pot.nMuteYPlacement = sValue.tol(10);
    }

    if(FAILED(Theme.GetSetting(L"ChannelStrip/MuteButton/Setting[@name=\"Left\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/MuteButton/Left is invalid");
    }
    m_Pot.rcMute.left = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/MuteButton/Setting[@name=\"Top\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/MuteButton/Top is invalid");
    }
    m_Pot.rcMute.top = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/MuteButton/Setting[@name=\"Right\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/MuteButton/Right is invalid");
    }
    m_Pot.rcMute.right = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/MuteButton/Setting[@name=\"Bottom\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/MuteButton/Bottom is invalid");
    }
    m_Pot.rcMute.bottom = sValue.tol(10);

    // Volume
    if(FAILED(Theme.GetSetting(L"ChannelStrip/VolumeFader/Setting[@name=\"Top\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/VolumeFader/Top is invalid");
    }
    m_Pot.nVolumeTop = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/VolumeFader/Setting[@name=\"Bottom\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/VolumeFader/Bottom is invalid");
    }
    m_Pot.nVolumeBottom = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/VolumeFader/Setting[@name=\"ThumbImage\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/VolumeFader/ThumbImage is invalid");
    }
    m_Pot.sThumb = sValue;
    FixThemePath(sThemePath, m_Pot.sThumb);

    // Balance
    m_Pot.nBalXPlacement = -1;
    if(FAILED(Theme.GetSetting(L"ChannelStrip/BalancePot/Setting[@name=\"PlacementX\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BalancePot/PlacementX is invalid");
    }
    else
    {
        m_Pot.nBalXPlacement = sValue.tol(10);
    }

    m_Pot.nBalYPlacement = -1;
    if(FAILED(Theme.GetSetting(L"ChannelStrip/BalancePot/Setting[@name=\"PlacementY\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BalancePot/PlacementY is invalid");
    }
    else
    {
        m_Pot.nBalYPlacement = sValue.tol(10);
    }

    if(FAILED(Theme.GetSetting(L"ChannelStrip/BalancePot/Setting[@name=\"CenterX\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BalancePot/CenterX is invalid");
    }
    m_Pot.ptBalCenter.x = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/BalancePot/Setting[@name=\"CenterY\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BalancePot/CenterY is invalid");
    }
    m_Pot.ptBalCenter.y = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/BalancePot/Setting[@name=\"LineLength\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BalancePot/LineLength is invalid");
    }
    m_Pot.nBalLength = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/BalancePot/Setting[@name=\"LineColor\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BalancePot/LineColor is invalid");
    }
    m_Pot.clrBal = sValue.ToColorref();

    if(FAILED(Theme.GetSetting(L"ChannelStrip/BalancePot/Setting[@name=\"AngleRestriction\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BalancePot/AngleRestriction is invalid");
    }
    m_Pot.nBalAngleRestriction = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"ChannelStrip/BalancePot/Setting[@name=\"Image\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BalancePot/Image is invalid");
    }
    m_Pot.sBal = sValue;
    FixThemePath(sThemePath, m_Pot.sBal);

    // TEXT
    if(FAILED(Theme.GetSetting(L"ChannelStrip/Setting[@name=\"TextColor\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/TextColor is invalid");
    }
    m_Pot.clrText = sValue.ToColorref();

    m_Pot.nFontSize = 14;
    if(FAILED(Theme.GetSetting(L"ChannelStrip/Setting[@name=\"TextSize\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/TextSize is invalid");
    }
    else
    {
        m_Pot.nFontSize = sValue.tol(10);
    }

    m_Pot.sFont = L"";
    if(FAILED(Theme.GetSetting(L"ChannelStrip/Setting[@name=\"Font\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/Font is invalid");
    }
    else
    {
        m_Pot.sFont = sValue;
    }

    SetRect(&m_Pot.rcText, 0, 0, 0, 0);
    if(FAILED(Theme.GetSetting(L"ChannelStrip/Setting[@name=\"TextLeft\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/Left is invalid");
    }
    else
    {
        m_Pot.rcText.left = sValue.tol(10);
    }

    if(FAILED(Theme.GetSetting(L"ChannelStrip/Setting[@name=\"TextTop\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/Top is invalid");
    }
    else
    {
        m_Pot.rcText.top = sValue.tol(10);
    }

    if(FAILED(Theme.GetSetting(L"ChannelStrip/Setting[@name=\"TextRight\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/Right is invalid");
    }
    else
    {
        m_Pot.rcText.right = sValue.tol(10);
    }

    if(FAILED(Theme.GetSetting(L"ChannelStrip/Setting[@name=\"TextBottom\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/Bottom is invalid");
    }
    else
    {
        m_Pot.rcText.bottom = sValue.tol(10);
    }

    // Global pot stuff

    if(FAILED(Theme.GetSetting(L"ChannelStrip/Setting[@name=\"BackColor\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BackColor is invalid");
    }
    m_Pot.clrBack = sValue.ToColorref();

    if(FAILED(Theme.GetSetting(L"ChannelStrip/Setting[@name=\"BackImage\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: ChannelStrip/BackImage is invalid");
    }
    m_Pot.sBack = sValue;
    FixThemePath(sThemePath, m_Pot.sBack);

    // Level meter stuff
    if(FAILED(Theme.GetSetting(L"LevelMeter/Setting[@name=\"ImageOn\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: LevelMeter/ImageOn is invalid");
    }
    m_Meter.sOn = sValue;
    FixThemePath(sThemePath, m_Meter.sOn);

    if(FAILED(Theme.GetSetting(L"LevelMeter/Setting[@name=\"ImageOff\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: LevelMeter/ImageOff is invalid");
    }
    m_Meter.sOff = sValue;
    FixThemePath(sThemePath, m_Meter.sOff);

    if(FAILED(Theme.GetSetting(L"LevelMeter/Setting[@name=\"XOffset\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: LevelMeter/XOffset is invalid");
    }
    m_Meter.nStartX = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"LevelMeter/Setting[@name=\"LEDWidth\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: LevelMeter/LEDWidth is invalid");
    }
    m_Meter.nStepX = sValue.tol(10);

    if(FAILED(Theme.GetSetting(L"LevelMeter/Setting[@name=\"LEDCount\"]", L"value", &sValue)))
    {
        MsgBoxf(L"Theme Error: LevelMeter/LEDCount is invalid");
    }
    m_Meter.nLEDCount = sValue.tol(10);

//    if(m_pOwner) m_pOwner->TearDown();
    CCPot::SetTheme(&m_Pot, m_bThemesEnabled);
//    if(m_pOwner) m_pOwner->ConstructDisplay();
    if(m_pOwner) m_pOwner->OnNewTheme();

    return S_OK;
}


HRESULT CThemeManager::Commit()
{
    HKEY hKey = 0;
    DWORD dwSize = 0;

    if(ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER,
        L"Software\\OneLightVolumizer\\Theme", 0, 0, 0, 
        KEY_SET_VALUE, 0, &hKey, 0))
    {
        // Failed to create/open the key - load defaults.
        odsf(L"ThemeManager::Commit()", L"Error creating a registry key.  gle=%d", GetLastError());
        return E_FAIL;
    }

    PCWSTR wsz = m_sThemeFile;
    dwSize = sizeof(WCHAR) * (m_sThemeFile.len() + 1);

    RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE*)wsz, dwSize);

    DWORD dw = m_bThemesEnabled;
    RegSetValueEx(hKey, L"Enabled", 0, REG_DWORD, (BYTE*)&dw, sizeof(DWORD));

    RegCloseKey(hKey);

    return S_OK;
}


HRESULT CThemeManager::GetDataFromRegistry()
{
    HKEY hKey = 0;
    DWORD dwSize = 0;
    WCHAR* wszFile = 0;

    if(ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER,
        L"Software\\OneLightVolumizer\\Theme", 0,
        KEY_QUERY_VALUE, &hKey))
    {
        // Failed to get the key - load defaults.
        odsf(L"ThemeManager::Commit()", L"Error opening a registry key.... Attempting to load default theme");
        return GetDefaultThemeFile();
    }

    // Allocate the right amount of data and grab it.
    if(ERROR_SUCCESS != RegQueryValueExW(hKey, NULL, 0, 0, NULL, &dwSize))
    {
        RegCloseKey(hKey);
        odsf(L"ThemeManager::Commit()", L"Error examining a registry value.... Attempting to load default theme");
        return GetDefaultThemeFile();
    }

    if(dwSize <= sizeof(WCHAR))
    {
        RegCloseKey(hKey);
        odsf(L"ThemeManager::Commit()", L"Found invalid data in the registry.  Loading the default theme.");
        return GetDefaultThemeFile();
    }

    wszFile = (WCHAR*)malloc(dwSize);
    if(!wszFile)
    {
        RegCloseKey(hKey);
        odsf(L"ThemeManager::Commit()", L"Out of memory!  Loading the default theme.");
        return GetDefaultThemeFile();
    }

    if(ERROR_SUCCESS != RegQueryValueExW(hKey, NULL, 0, 0, (BYTE*)wszFile, &dwSize))
    {
        free(wszFile);
        RegCloseKey(hKey);
        odsf(L"ThemeManager::Commit()", L"Error examining a registry value.... Attempting to load default theme");
        return GetDefaultThemeFile();
    }

    dwSize = sizeof(DWORD);
    DWORD dw = 0;
    if(ERROR_SUCCESS != RegQueryValueExW(hKey, L"Enabled", 0, 0, (BYTE*)&dw, &dwSize))
    {
        free(wszFile);
        RegCloseKey(hKey);
        odsf(L"ThemeManager::Commit()", L"Error examining a registry value.... Attempting to load default theme");
        return GetDefaultThemeFile();
    }

    m_bThemesEnabled = (BOOL)dw;

    RegCloseKey(hKey);

    m_sThemeFile = wszFile;

    free(wszFile);

    return S_OK;
}


HRESULT CThemeManager::GetThemesFileName(CCString* ps)
{
    // Get the name of the themes.xml file.
    GetModuleFileName(NULL, ps->GetBuffer(MAX_PATH), MAX_PATH);

    ps->Path_StripToPath();// Remove the EXE off of the path.
    ps->Path_Append(L"Themes.xml");

    return S_OK;
}


HRESULT CThemeManager::GetDefaultThemeFile()
{
    HRESULT hr;
    CCString sThemesFile;
    CXMLConfig Themes;

    GetThemesFileName(&sThemesFile);

    // Open it
    if(FAILED(hr = Themes.Open(sThemesFile, L"Themes")))
    {
        odsf(L"ThemeManager::GetDefaultThemeFile()", L"Error opening '%s'.", (PCWSTR)sThemesFile);
        return hr;
    }

    if(FAILED(hr = Themes.GetSetting(L"Theme", L"link", &m_sThemeFile)))
    {
        odsf(L"ThemeManager::GetDefaultThemeFile()", L"Found no themes listed in the themes file.");
        return hr;
    }

    // Make it relative to our exe path.
    CCString sPath;

    GetModuleFileName(NULL, sPath.GetBuffer(MAX_PATH), MAX_PATH);

    sPath.Path_StripToPath();
    sPath.Path_Append(m_sThemeFile);

    m_sThemeFile = sPath;

    return S_OK;
}


HRESULT CThemeManager::GetMeterTheme(METER_THEME* pDest)
{
    pDest->nLEDCount = m_Meter.nLEDCount;
    pDest->nStartX = m_Meter.nStartX;
    pDest->nStepX = m_Meter.nStepX;
    pDest->sOff = m_Meter.sOff;
    pDest->sOn = m_Meter.sOn;

    return S_OK;
}


HRESULT CThemeManager::ThemesDialog(CApp* pOwner)
{
    RECT orect, prect;

    m_pOwner = pOwner;
    m_hParent = pOwner->m_Main.GethWnd();

    SetRect(&prect, 50,50,50,50);
    SetRect(&orect, -150, -150, 150, 150);
    m_Main.Create(L"Themes", m_hParent, CThemeManager::WndProc, g_hInstance,
        prect, orect, WS_OVERLAPPEDWINDOW, this, IDI_ICON1);

    SetRect(&prect, 0, 0, 100, 0);
    SetRect(&orect, 12, 12, -12, 35);
    m_Static.Create(L"Please choose the theme to load.", m_Main, g_hInstance, prect, orect);

    SetRect(&prect, 0, 0, 100, 0);
    SetRect(&orect, 12, 41, -12, 59);
    m_ThemesEnabled.Create(L"Themes enabled", m_Main, prect, orect, 2, TRUE);

    SetRect(&prect, 100, 100, 100, 100);
    SetRect(&orect, -87, -35, -12, -12);
    m_Button.Create(L"OK", m_Main, g_hInstance, prect, orect);

    SetRect(&prect, 0, 0, 100, 100);
    SetRect(&orect, 12, 59, -12, -41);
    m_List.Create(m_Main, g_hInstance, prect, orect);

    LIST_COLUMN col[2];
    col[0].Set(L"Name", LIST_LEFT, 300);
    col[1].Set(L"Path", LIST_LEFT, 100);
    m_List.ShowHeader(2, col);

    SetupList();

    m_Main.Show(TRUE);

    EnableWindow(m_hParent, FALSE);

    MSG msg;
    while(GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return S_OK;
}


void CThemeManager::SetupList()
{
    // Set up the list.
    CXMLConfig ThemeFile;
    CCString sThemesFile;
    CCString XPath;
    IXMLDOMElement* pRoot = 0;
    IXMLDOMNodeList* pList = 0;
    IXMLDOMNode* pCurrent = 0;
    VARIANT v;
    IXMLDOMElement* pCurrEl = 0;
    int iListItem = 0;
    int iSelect = -1;// The one we should select.

    m_ThemesEnabled.SetCheck(m_bThemesEnabled);
    m_List.Enable(m_bThemesEnabled);

    GetThemesFileName(&sThemesFile);
    if(FAILED(ThemeFile.Open(sThemesFile, L"Themes")))
    {
        // error.
        odsf(L"ThemeManager, Setting up UI", L"Unable to open '%s'.  The file may be not found or invalid.", (PCWSTR)sThemesFile);
        return;
    }

    pRoot = ThemeFile.GetRoot();

    if(!pRoot) return;

    XPath = L"Theme";
    if(FAILED(pRoot->selectNodes(XPath.bstr(), &pList)))
    {
        ThemeFile.Close();
        return;
    }

    pList->nextNode(&pCurrent);

    while(pCurrent)
    {
        pCurrent->QueryInterface(IID_IXMLDOMElement, (void**)&pCurrEl);
        SAFE_RELEASE(pCurrent);
        
        // Get the name.
        XPath.FormatW(L"name");
        pCurrEl->getAttribute(XPath.bstr(), &v);

        m_List.AddItem(&iListItem, 0, 0);

        if(v.vt == VT_BSTR)
        {
            m_List.AddItemText(iListItem, 0, v.bstrVal);
            SysFreeString(v.bstrVal);
        }

        // Get the link.
        XPath.FormatW(L"link");
        pCurrEl->getAttribute(XPath.bstr(), &v);

        if(v.vt == VT_BSTR)
        {
            m_List.AddItemText(iListItem, 1, v.bstrVal);
            if(this->m_sThemeFile.cmpi(v.bstrVal) == 0)
            {
                iSelect = iListItem;
            }
            SysFreeString(v.bstrVal);
        }

        SAFE_RELEASE(pCurrEl);

        pList->nextNode(&pCurrent);
    }

    // Select the one we're currently using.
    m_List.SelectAnItem(iSelect);
    m_List.SetSelectionMark(iSelect);

    ThemeFile.Close();

    return;
}


LRESULT CALLBACK CThemeManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CThemeManager* pThis = (CThemeManager*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(uMsg)
    {
    case WM_WINDOWPOSCHANGED:
        {
            pThis->m_List.Size();
            return 0;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    case WM_COMMAND:
        {
            if(LOWORD(wParam) == pThis->m_Button.GetId())
            {
                SendMessage(hWnd, WM_CLOSE, 0, 0);
                return 0;
            }
            else if(LOWORD(wParam) == pThis->m_ThemesEnabled.GetId())
            {
                int nCheck = pThis->m_ThemesEnabled.GetCheck();
                BOOL bChecked = (nCheck == BST_CHECKED) ? TRUE : FALSE;

                pThis->m_List.Enable(bChecked);
                pThis->m_bThemesEnabled = bChecked;

                // Try to load the theme up.  If it works, save it.
                pThis->LoadTheme(pThis->m_sThemeFile);

                return 0;
            }

            break;
        }
    case WM_CLOSE:
        {
            EnableWindow(pThis->m_hParent, TRUE);
            pThis->m_pOwner->m_Main.Show(TRUE);
            SetFocus(pThis->m_pOwner->m_Main);
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
            pThis = (CThemeManager*)pcs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            return 0;
        }
    case WM_NOTIFY:
        {
            NMHDR* pnmh = (NMHDR*)lParam;

            if((pnmh->hwndFrom == pThis->m_List) && (pnmh->code == NM_CLICK))
            {
                NMITEMACTIVATE* pnmlv = (NMITEMACTIVATE*)lParam;
                CCString s;

                pThis->m_List.GetItemText(pnmlv->iItem, 1, &s);

                // Try to load the theme up.  If it works, save it.
                if(SUCCEEDED(pThis->LoadTheme(s)))
                {
                    pThis->m_sThemeFile = s;
                }

                SetFocus(pThis->m_List);

                return 0;
            }

            break;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


BOOL CThemeManager::GetThemesEnabled()
{
    return m_bThemesEnabled;
}

