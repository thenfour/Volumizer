

#include "stdafx.h"
#include "CApp.h"
#include "about.h"
#include "resource.h"


#define RECENTFILEMENUPOSITION 7

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()


CApp::CApp()
{
    m_hHardware = 0;
    m_hDestinations = 0;
    m_bMuxMute = FALSE;
    m_DestType = MIXD_UNDEFINED;
    m_nPots = 0;
    m_pLibrary = 0;
    m_hMenu = 0;
    m_pMixer = 0;
    m_pDest = 0;
    m_pPots = 0;
    m_bAcceptUIChanges = FALSE;
}


CApp::~CApp()
{
}


void CApp::Entry(PCWSTR wszCmdLine)
{
    RECT prect, orect;
    HRESULT hr;

    CCOpenDebugLog(L"Volumizer.log");

    // Parse the command line and nab information from it.
    PWSTR* argv = 0;
    int argc = 0;
    int i = 0;
    // Command options.
    int cmdm = -1;
    int cmds = -1;
    BOOL cmdx = FALSE;
    CCString cmdo;

    CoInitialize(0);

    m_Settings.GetSettings();

    /*
        Display splash screen.
        - get date info (days since installation)
    */
    if(SplashEntry())
    {
        if(wcslen(wszCmdLine))
        {
            argv = CommandLineToArgvW(wszCmdLine, &argc);

            // Volumizer.exe [-m MixerID] [-s SetID] [-o File] [-x]
            for(i=0;i<argc;i++)
            {
                switch(argv[i][1])
                {
                case L'm':
                case L'M':
                    i++;
                    if(i<argc)
                    {
                        cmdm = wcstol(argv[i], 0, 10);
                    }
                    break;
                case L'o':
                case L'O':
                    i++;
                    if(i<argc)
                    {
                        cmdo = argv[i];
                    }
                    break;
                case L's':
                case L'S':
                    i++;
                    if(i<argc)
                    {
                        cmds = wcstol(argv[i], 0, 10);
                    }
                    break;
                case L'x':
                case L'X':
                    cmdx = TRUE;
                    break;
                default:
                    // Usage
                    Usage();
                    return;
                    break;
                }
            }

            GlobalFree(argv);
        }

        if(FAILED(hr = CoCreateInstance(CLSID_MixerLibrary, 0, CLSCTX_INPROC_SERVER, IID_IMixerLibrary, (void**)&m_pLibrary)))
        {
            odsf(L"CApp::Entry()", L"Couldn't create an instance of the mixer objects.  Please make sure this software is installed correctly.");
            CoUninitialize();
            return;
        }

        // Load up if necessary.
        if(cmdo.len())
        {
            if(FAILED(m_pLibrary->Load(cmdo.variant())))
            {
                MsgBoxf(L"Failed to load '%s'.  No error was specified.", (PCWSTR)cmdo);
            }
        }

        // If we are to exit immediately, let's just get it over with and exit.
        if(cmdx == TRUE)
        {
            SAFE_RELEASE(m_pLibrary);
            CoUninitialize();
            return;
        }

        // Get our theme data.
        m_Themes.LoadTheme();

        SetRect(&prect, 0, 0, 0, 0);
        SetRect(&orect, 0, 0, 0, 0);
        m_Main.Create(L"", 0, CApp::WndProc, g_hInstance, prect, orect,
            WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU, this, IDI_ICON1);

        m_Main.AddExStyle(WS_EX_ACCEPTFILES);

        SetWindowPlacement(m_Main, &m_Settings.m_wp);

        m_hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_MENU));
        SetMenu(m_Main, m_hMenu);

        /*
            The "Hardware" menu never changes during the course of the
            application, so set that up right now.
        */
        m_hHardware = GetSubMenu(m_hMenu, 1);
        m_hDestinations = GetSubMenu(m_hMenu, 2);

        // In order to receive WM_MENUCOMMAND messages
        // we have to tell the submenus to divvy em out.
        MENUINFO mi = {0};
        mi.cbSize = sizeof(mi);
        mi.fMask = MIM_STYLE;
        mi.dwStyle = MNS_NOTIFYBYPOS | MNS_CHECKORBMP;
        SetMenuInfo(m_hHardware, &mi);
        SetMenuInfo(m_hDestinations, &mi);
        SetMenuInfo(m_hMenu, &mi);

        IEnumMixers* pEnum = 0;
        IMixer* pm = 0;
        MENUITEMINFO mii = {0};
        BSTR str = 0;
        DWORD dwFetched = 0;

        m_pLibrary->EnumMixers(&pEnum);

        if(pEnum)
        {
            while(1)
            {
                // Grab the next mixer.
                pEnum->Next(1, &pm, &dwFetched);
                if(dwFetched != 1) break;

                // Set up the menu item info struct.
                mii.cbSize = sizeof(mii);
                pm->get_mixerid(&mii.dwItemData);
                mii.fMask = MIIM_CHECKMARKS | MIIM_DATA | MIIM_STRING | MIIM_STATE | MIIM_FTYPE;
                mii.fType = MFT_STRING| MFT_RADIOCHECK;
                mii.fState = MFS_ENABLED;// | MFS_DEFAULT;
                mii.hbmpChecked = 0;
                mii.hbmpUnchecked = 0;

                pm->get_name(&str);
                mii.dwTypeData = str;
                SysFreeString(str);

                // Insert it.
                InsertMenuItem(m_hHardware, GetMenuItemCount(m_hHardware), TRUE, &mii);

                SAFE_RELEASE(pm);
            }

            SAFE_RELEASE(pEnum);
        }

        m_DisplayProps.Load();

        m_SaveDlg.m_bAdvanced = m_Settings.m_bAdvancedView;

        HMENU hOptions = GetSubMenu(m_hMenu, 0);

        if(m_Settings.m_bAlwaysOnTop == TRUE)
        {
            CheckMenuItem(hOptions, IDM_ALWAYSONTOP,
                MF_BYCOMMAND | MF_CHECKED);

            SetWindowPos(m_Main, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }
        else
        {
            CheckMenuItem(hOptions, IDM_ALWAYSONTOP,
                MF_BYCOMMAND | MF_UNCHECKED);

            SetWindowPos(m_Main, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }

        if(m_Settings.m_bCenter == TRUE)
        {
            CheckMenuItem(hOptions, ID_OPTIONS_CENTER,
                MF_BYCOMMAND | MF_CHECKED);
        }
        else
        {
            CheckMenuItem(hOptions, ID_OPTIONS_CENTER,
                MF_BYCOMMAND | MF_UNCHECKED);
        }

        if(cmdm != -1)
        {
            m_Settings.m_dwMixerID = cmdm;
        }

        /*
            Setup our recent files list.
        */
        m_RecentFiles.Load(HKEY_CURRENT_USER, L"Software\\OneLightVolumizer\\Settings\\RecentFiles");
        m_RecentFiles.InsertIntoMenu(GetSubMenu(m_hMenu, 0), RECENTFILEMENUPOSITION);

        /*
            Grab our saved mixer and destinations.
        */
        OnSelectMixer(m_Settings.m_dwMixerID);

        if(m_pMixer)
        {
            SAFE_RELEASE(m_pDest);

            // Try to select the destination now.
            if(cmds != -1)
            {
                // Load the specified destination.
                IEnumMixerDestinations* pEnum = 0;
                int i = 0;
                long l = 0;
                DWORD dwFetched = 0;

                m_pMixer->EnumDestinations(&pEnum);

                if(pEnum)
                {
                    while(1)
                    {
                        pEnum->Next(1, &m_pDest, &dwFetched);

                        // We'll just leave it at that even though we didn't 
                        // make it all the way necessarily to the
                        // Specified destination.
                        if(dwFetched != 1) break;

                        // Did we reach our goal?
                        if(i == cmds) break;
                        i++;
                    }

                    SAFE_RELEASE(pEnum);
                }
            }
            else
            {
                m_pMixer->GetDestinationByID(m_Settings.m_dwDestID, &m_pDest);

                if(!m_pDest)
                {
                    // Welp that didn't work.. try it by type.
                    m_pMixer->GetDestination(m_Settings.m_Type, &m_pDest);
                }
            }
        }

        OnSelectDestination();
        ConstructDisplay();

        // Load up our keyboard accelerators
        HACCEL hAccel = LoadAccelerators(g_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

        //m_Main.Show(TRUE);

        MSG msg;
        while(GetMessage(&msg, 0, 0, 0))
        {
            if(!TranslateAccelerator(m_Main, hAccel, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        m_Settings.m_bAdvancedView = m_SaveDlg.m_bAdvanced;
        m_Settings.SaveSettings();
        m_DisplayProps.Save();
        m_Themes.Commit();

        m_RecentFiles.Save(HKEY_CURRENT_USER, L"Software\\OneLightVolumizer\\Settings\\RecentFiles");

        UnsinkEvents();
        TearDown();

        SAFE_RELEASE(m_pDest);
        SAFE_RELEASE(m_pMixer);
        SAFE_RELEASE(m_pLibrary);
    }// splash entry.

    CoUninitialize();

    return;
}


LRESULT CALLBACK CApp::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CApp* pThis = (CApp*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

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
    case WM_DROPFILES:
        {
            HDROP hDrop = (HDROP)wParam;
            UINT nFiles = 0;
            UINT i = 0;
            CCString sFile;
            UINT nSize = 0;

            // We support dropping multiple files on the window.
            nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, 0, 0);

            for(i=0;i<nFiles;i++)
            {
                // Get the size of the filename string.
                nSize = DragQueryFile(hDrop, i, 0, 0) + 1;
                DragQueryFile(hDrop, i, sFile.GetBuffer(nSize), nSize);

                if(FAILED(pThis->m_pLibrary->Load(sFile.variant())))
                {
                    MsgBoxf(L"Failed to open '%s'.  Check to make sure the file is a valid OneLight Volumizer file.", (PCWSTR)sFile);
                }
                pThis->m_RecentFiles.UseFile(sFile);
            }

            return 0;
        }
    case WM_NOTIFY:
        {
            NMHDR* pnmh = (NMHDR*)lParam;
            int i = 0;

            if(pThis->m_bAcceptUIChanges == TRUE)
            {
                for(i=0;i<pThis->m_nPots;i++)
                {
                    if(pnmh->hwndFrom == pThis->m_pPots[i].GethWnd())
                    {
                        // We found teh right control.
                        switch(pnmh->code)
                        {
                        case PN_BAL:
                            pThis->OnBal(&pThis->m_pPots[i]);
                            return 0;
                        case PN_VOL:
                            pThis->OnVol(&pThis->m_pPots[i]);
                            return 0;
                        case PN_MUTE:
                            pThis->OnMute(&pThis->m_pPots[i]);
                            return 0;
                        }
                    }
                }
            }
            break;
        }
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
            case IDM_THEME:
                {
                    pThis->m_Themes.ThemesDialog(pThis);
                    return 0;
                }
            case IDM_MONITOR:
                {
                    pThis->OnMonitor();
                    return 0;
                }
            case IDM_ALWAYSONTOP:
                {
                    pThis->OnAlwaysOnTop();
                    return 0;
                }
            case ID_OPTIONS_CENTER:
                {
                    pThis->OnToggleCenter();
                    return 0;
                }
            case IDM_SAVE:
                {
                    pThis->OnSave();
                    return 0;
                }
            case IDM_OPEN:
                {
                    pThis->OnOpen();
                    return 0;
                }
            case IDM_PROPERTIES:
                {
                    pThis->OnProperties();
                    return 0;
                }
            case IDM_EXIT:
                {
                    SendMessage(hWnd, WM_CLOSE,0,0);
                    return 0;
                }
            case ID_HELP_REGISTER:
                {
                    pThis->DoRegistrationDialog(pThis->m_Main);
                    return 0;
                }
            case ID_HELP_ABOUT:
                {
                    pThis->DoAboutDialog();
                    return 0;
                }
            }
            break;
        }
    case WM_MENUCOMMAND:
        {
            MENUITEMINFO mii = {0};
            mii.cbSize = sizeof(mii);
            mii.fMask = MIIM_ID | MIIM_DATA;
            mii.wID = 0;
            GetMenuItemInfo((HMENU)lParam, wParam, TRUE, &mii);

            // Check to see if this is a recent file list thingy.
            int i = pThis->m_RecentFiles.OnMenuCommand(wParam, lParam);

            if(i != -1)
            {
                // Load up this recent file.
                CCString sFile;
                pThis->m_RecentFiles.GetItem(i, &sFile);

                // Open this file.
                if(FAILED(pThis->m_pLibrary->Load(sFile.variant())))
                {
                    MsgBoxf(L"Failed to open '%s'.  Check to make sure the file is a valid OneLight Volumizer file.", (PCWSTR)sFile);
                }

                pThis->m_RecentFiles.UseFile(sFile);
                return 0;
            }

            if((HMENU)lParam == pThis->m_hDestinations)
            {
                // They're selecting a new destination.
                IMixerDestination* pDest = 0;
                pThis->m_pMixer->GetDestinationByID(mii.dwItemData, &pDest);

                if(pDest)
                {
                    SAFE_RELEASE(pThis->m_pDest);

                    pThis->m_pDest = pDest;
                    pThis->OnSelectDestination();
                    pThis->ConstructDisplay();
                }

                return 0;
            }

            if((HMENU)lParam == pThis->m_hHardware)
            {
                if(mii.wID == IDM_HARDWAREPROPS)
                {
                    // Audio device properties.
                    return 0;
                }
                if(mii.wID == IDM_MONITOR)
                {
                    // Source Monitor
                    pThis->OnMonitor();
                    return 0;
                }

                // They're selecting a new sound mixer.
                pThis->OnSelectMixer(mii.dwItemData);
                pThis->ConstructDisplay();
                return 0;
            }

            // It's not one of the dynamic menus, so 
            // Let's treat it like a normal command.
            SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(mii.wID, 0), 0);
            break;
        }
    case WM_WINDOWPOSCHANGED:
        {
            pThis->m_Settings.m_wp.length = sizeof(pThis->m_Settings.m_wp);
            GetWindowPlacement(hWnd, &pThis->m_Settings.m_wp);
            return 0;
        }
    case WM_DESTROY:
        {
            pThis->m_Settings.m_wp.length = sizeof(pThis->m_Settings.m_wp);
            GetWindowPlacement(hWnd, &pThis->m_Settings.m_wp);
            PostQuitMessage(0);
            return 0;
        }
    case WM_CREATE:
        {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            pThis = (CApp*)pcs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void CApp::OnBal(CCPot* pPot)
{
    IMixerLine2* pl = (IMixerLine2*)pPot->GetUserData();
    if(!pl) return;

    unsigned long ul = pPot->GetBal();

    if(FAILED(pl->put_balance(ul)))
    {
        MsgBoxf(L"Failed to set balance.  The channel strip may not support modifying the balance at this time.");
    }

    return;
}


void CApp::OnVol(CCPot* pPot)
{
    IMixerLine2* pl = (IMixerLine2*)pPot->GetUserData();
    if(!pl) return;

    unsigned long ul = pPot->GetVol();

    if(FAILED(pl->put_volume(ul)))
    {
        MsgBoxf(L"Failed to set volume.  The channel strip may not support modifying the volume at this time.");
    }

    return;
}


void CApp::OnMute(CCPot* pPot)
{
    IMixerLine2* pl = (IMixerLine2*)pPot->GetUserData();
    if(!pl) return;

    /*
        This will behave as the mux selector if we're
        currently doing record stuff.
    */
    if(m_bMuxMute == TRUE)
    {
        IMixerLine* pLine = 0;

        pl->QueryInterface(IID_IMixerLine, (void**)&pLine);

        /*
            You can't turn off a record source - 
            you have to just select another one.
        */
        if(pPot->GetMute() == FALSE)
        {
            pPot->SetMute(TRUE);
            return;
        }

        IMixerLine2* ml2 = 0;
        if(SUCCEEDED(m_pDest->QueryInterface(IID_IMixerLine2, (void**)&ml2)))
        {
            ml2->put_mux_source(pLine);
            SAFE_RELEASE(ml2);
        }
    }
    else
    {
        pl->put_mute(pPot->GetMute());
    }

    return;
}


void CApp::TearDown()
{
    if(m_pPots)
    {
        IMixerLine* p = 0;

        for(int i=0;i<m_nPots;i++)
        {
            p = (IMixerLine*)m_pPots[i].GetUserData();
            m_pPots[i].Destroy();
            SAFE_RELEASE(p);
        }

        delete [] m_pPots;
        m_pPots = 0;
        m_nPots = 0;
    }

    m_cNoControls.Destroy();

    m_Meter.Hide();
}


HRESULT CApp::ConstructDisplay()
{
    m_bAcceptUIChanges = FALSE;
    m_Main.SetRedraw(FALSE);
    m_bMuxMute = FALSE;

    // Tear down the controls first.
    TearDown();

    // Determine if we have valid mixer and destination objects.
    if(!m_pMixer || !m_pDest)
    {
        // Free whatever we got.
        UnsinkEvents();
        SAFE_RELEASE(m_pMixer);
        SAFE_RELEASE(m_pDest);

        if(FAILED(OnSelectMixer(0)))
        {
            MsgBoxf(L"Unable to select the default mixer.  There may be no sound devices on the system.");
            m_Main.SetRedraw(TRUE);
            m_Main.Invalidate();
            return E_FAIL;
        }
    }

    /*
        Now we are guaranteed to have a valid mixer
        and destination object.  We stick 1 pot up there
        for the MIXL_SELF line, and then proceed with
        every other line there is.
    */
    int x = 0;// Current X coordinate.
    long i = 0;
    unsigned long lFetched = 0;
    long nPots = 0;
    IMixerLine* pLine = 0;
    IEnumMixerLines* pEnum = 0;

    // Allocate our pots.
    m_pDest->get_line_count(&nPots);
    m_pPots = new CCPot[nPots+1];
    m_nPots = 0;

    if(!m_pPots)
    {
        odsf(L"ConstructDisplay()", L"Out of memory.");
        m_Main.SetRedraw(TRUE);
        m_Main.Invalidate();
        return E_FAIL;// Out of memory.
    }

    // Grab the destination type so we can adjust our behaviors accordingly.
    m_pDest->get_type_destination(&m_DestType);

    // See if the destination has a mux control in it
    // And set our internal flags accordingly.
    IMixerControl* pMux = 0;
    m_pDest->GetLineControl(MIXL_SELF, MIXC_MUX, &pMux);

    if(pMux)
    {
        m_bMuxMute = TRUE;
        SAFE_RELEASE(pMux);
    }
    else
    {
        m_bMuxMute = FALSE;
    }

    // Grab our enumerator for the lines.
    if(FAILED(m_pDest->EnumLines(&pEnum)))
    {
        odsf(L"ConstructDisplay()", L"Could not enumerate mixer lines.");
        m_Main.SetRedraw(TRUE);
        m_Main.Invalidate();
        return E_FAIL;
    }

    /*
        Do the pot for the destination line.
        dod upi tru wjat O [revopis;u saod
    */
    if(FAILED(m_pDest->QueryInterface(IID_IMixerLine, (void**)&pLine)))
    {
        odsf(L"ConstructDisplay()", L"Error with the mixer objects.  Make sure the application is installed properly");
        m_Main.SetRedraw(TRUE);
        m_Main.Invalidate();
        return E_FAIL;
    }

    SetupPotControl(pLine, m_pPots, &x);

    {
        // Set the title bar text.
        BSTR strLine = 0;
        BSTR strMixer = 0;
        CCString sTitle;

        pLine->get_name(&strLine);
        m_pMixer->get_name(&strMixer);

        sTitle.FormatW(L"%s - %s - OneLight Volumizer", strLine, strMixer);
        m_Main.SetText(sTitle);

        SysFreeString(strLine);
        SysFreeString(strMixer);
    }

    SAFE_RELEASE(pLine);

    // ENUMERATE!
    while(1)
    {
        pEnum->Next(1, &pLine, &lFetched);
        if(lFetched != 1) break;

        // Set up this pot.
        SetupPotControl(pLine, &m_pPots[m_nPots], &x);

        SAFE_RELEASE(pLine);
    }

    SAFE_RELEASE(pEnum);
    m_Main.SetRedraw(TRUE);

    {
        /*
            This is a perfect place to update our settings!
        */

        m_Settings.m_bAlwaysOnTop = (GetWindowLong(m_Main, GWL_EXSTYLE) & WS_EX_TOPMOST) ? TRUE : FALSE;

        IMixerLine* pLine = 0;
        m_pDest->QueryInterface(IID_IMixerLine, (void**)&pLine);

        if(pLine)
        {
            pLine->get_lineid(&m_Settings.m_dwDestID);
            SAFE_RELEASE(pLine);
        }

        m_pDest->get_type_destination(&m_Settings.m_Type);

        m_pMixer->get_mixerid(&m_Settings.m_dwMixerID);
    }

    /*
        If there are no valid controls, then let's display a friendly
        message to the user explaining why.
    */
    if(m_nPots == 0)
    {
        RECT prect, orect;
        SetRect(&prect, 0, 0, 0, 0);
        SetRect(&orect, 0, 0, 300, 150);
        m_cNoControls.Create(L"There are no recognized audio controls for this set",
            m_Main, g_hInstance, prect, orect);
        // Make it all centered and stuff
        m_cNoControls.AddStyle(SS_CENTER);
        m_cNoControls.Invalidate();
    }

    SizeupControls();

    m_bAcceptUIChanges = TRUE;
    SetWindowPos(m_Main, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    if(m_Settings.m_bCenter)
    {
        CenterWindow(m_Main, GetDesktopWindow());
    }

    m_Main.Invalidate();
    return S_OK;
}


BOOL CApp::SetupPotControl(IMixerLine* pLine, CCPot* pPot, IN OUT int* px)
{
    IMixerLine2* pml2 = 0;
    BOOL bUseful = FALSE;

    BSTR strName = 0;
    DWORD dwBal = (DWORD)-1;
    DWORD dwVol = (DWORD)-1;
    BOOL bMute = (BOOL)-1;
    DWORD dwId = 0;

    // Get the text.
    pLine->get_name(&strName);

    // Determine if the user has specified that this control should
    // not be displayed.
    pLine->get_lineid(&dwId);
    if(m_DisplayProps.IsLineEnabled(dwId) == FALSE)
    {
        // line is not enabled in the display, so return.
        SysFreeString(strName);
        return FALSE;
    }

    pLine->QueryInterface(IID_IMixerLine2, (void**)&pml2);
    if(!pml2)
    {
        odsf(L"ConstructDisplay()", L"Error with the mixer objects.  Make sure the application is installed properly.");
        return FALSE;// Bad news, folks.
    }

    if(SUCCEEDED(pml2->get_volume(&dwVol)))
    {
        bUseful = TRUE;
    }

    if(SUCCEEDED(pml2->get_balance(&dwBal)))
    {
        bUseful = TRUE;
    }

    if(m_bMuxMute == FALSE)
    {
        if(SUCCEEDED(pml2->get_mute(&bMute)))
        {
            bUseful = TRUE;
        }
    }

    SAFE_RELEASE(pml2);

    if(bUseful == TRUE)
    {
        pPot->Create(m_Main, *px, 0);

        // We know we'll be using this control,
        // so adjust internals.
        *px += CCPot::GetGlobalWidth();
        m_nPots ++;

        pPot->SetText(strName);

        // Volume
        if(dwVol != (DWORD)-1)
        {
            pPot->UseVol(TRUE);
            pPot->SetVol(dwVol);
        }
        else
        {
            pPot->UseVol(FALSE);
        }

        // Balance
        if(dwBal != (DWORD)-1)
        {
            pPot->UseBal(TRUE);
            pPot->SetBal(dwBal);
        }
        else
        {
            pPot->UseBal(FALSE);
        }

        // Mute
        if(m_bMuxMute == FALSE)
        {
            if(bMute != (BOOL)-1)
            {
                pPot->UseMute(TRUE);
                pPot->SetMute(bMute);
            }
            else
            {
                pPot->UseMute(FALSE);
            }
        }
        else
        {
            /*
                If the destination line has a mux, we'll be using
                the mute switch as the "select" thingy.
            */
            IMixerDestination* pDest = 0;
            IMixerLine2* pDestLine = 0;
            IMixerLine* pMuxSource = 0;
            pLine->get_owner(&pDest);

            pDest->QueryInterface(IID_IMixerLine2, (void**)&pDestLine);

            if(pDestLine)
            {
                pDestLine->get_mux_source(&pMuxSource);
                if(pMuxSource)
                {
                    pPot->UseMute(TRUE);
                    pPot->SetMute(TRUE);

                    // Compare the IDs.  If the mux source and this
                    // line are equal then set our mute to FALSE.
                    DWORD dwLine = 0;
                    DWORD dwMux = 0;

                    pLine->get_lineid(&dwLine);
                    pMuxSource->get_lineid(&dwMux);

                    if(dwLine == dwMux)
                    {
                        pPot->SetMute(FALSE);
                    }

                    SAFE_RELEASE(pMuxSource);
                }
                else
                {
                    // No mux control, nevermind!
                }

                SAFE_RELEASE(pDestLine);
            }

            SAFE_RELEASE(pDest);
        }

        // Store the mixer line pointer with the window.
        IMixerLine2* pPersistent = 0;
        pLine->QueryInterface(IID_IMixerLine2, (void**)&pPersistent);
        pPot->SetUserData(pPersistent);
        pPersistent = 0;
    }

    SysFreeString(strName);

    return bUseful;
}


void CApp::RefreshDisplay()
{
    // Iterate through our valid pot controls
    // and update their controls.
    int i = 0;
    CCPot* pPot = 0;

    for(i=0;i<m_nPots;i++)
    {
        pPot = &m_pPots[i];
        RefreshPot(&m_pPots[i]);
    }

    return;
}


void CApp::RefreshPot(CCPot* pPot)
{
    IMixerLine2* pml = 0;;
    IMixerLine* pmlx = 0;
    DWORD dw = 0;

    m_bAcceptUIChanges = FALSE;

    // Get the interfaces we need.
    pml = (IMixerLine2*)pPot->GetUserData();

    pml->QueryInterface(IID_IMixerLine, (void**)&pmlx);

    if(pmlx)
    {
        pmlx->RefreshLine();
        SAFE_RELEASE(pmlx);
    }

    // Do the volume.
    if(SUCCEEDED(pml->get_volume(&dw)))
    {
        pPot->UseVol(TRUE);
        pPot->SetVol(dw);
    }

    if(SUCCEEDED(pml->get_balance(&dw)))
    {
        pPot->UseBal(TRUE);
        pPot->SetBal(dw);
    }

    // Mute depends on whether we're doing mute,
    // or mr. mux select0r.
    if(m_bMuxMute == TRUE)
    {
        // Get the MixerLine2 interface for our destination
        // so we can compare IDs.
        DWORD dwMuxSource = 0;
        DWORD dwLine = 0;
        IMixerLine2* pDestLine = 0;
        IMixerLine* pMuxSource = 0;
        IMixerLine* pLine = 0;

        m_pDest->QueryInterface(IID_IMixerLine2, (void**)&pDestLine);

        if(pDestLine)
        {
            pml->QueryInterface(IID_IMixerLine, (void**)&pLine);

            if(pLine)
            {
                pDestLine->get_mux_source(&pMuxSource);

                if(pMuxSource)
                {
                    pMuxSource->get_lineid(&dwMuxSource);
                    pLine->get_lineid(&dwLine);

                    if(dwMuxSource == dwLine)
                    {
                        pPot->SetMute(FALSE);
                    }
                    else
                    {
                        pPot->SetMute(TRUE);
                    }

                    SAFE_RELEASE(pMuxSource);
                }

                SAFE_RELEASE(pLine);
            }

            SAFE_RELEASE(pDestLine);
        }
    }
    else
    {
        BOOL b;

        if(SUCCEEDED(pml->get_mute(&b)))
        {
            pPot->UseMute(TRUE);
            pPot->SetMute(b);
        }
    }

    m_bAcceptUIChanges = TRUE;
}


void __stdcall CApp::OnLineChange(IMixerLine* pLine)
{
    // Figure out which pot this corresponds to.
    IUnknown* punk = 0;
    IUnknown* ppot = 0;
    IMixerLine2* pml2 = 0;
    int i = 0;

    // First of all though, figure out if this line is a destination line.
    // if it is, then we're gonna refresh everything.
    IMixerDestination* pDest = 0;
    pLine->QueryInterface(IID_IMixerDestination, (void**)&pDest);

    if(pDest)
    {
        // blam.
        pDest->Refresh();
        RefreshDisplay();
        SAFE_RELEASE(pDest);
        return;
    }

    pLine->QueryInterface(IID_IUnknown, (void**)&punk);

    if(punk)
    {
        for(i=0;i<m_nPots;i++)
        {
            pml2 = (IMixerLine2*)m_pPots[i].GetUserData();

            pml2->QueryInterface(IID_IUnknown, (void**)&ppot);

            if(ppot && (ppot == punk))
            {
                RefreshPot(&m_pPots[i]);
            }

            SAFE_RELEASE(ppot);
        }

        SAFE_RELEASE(punk);
    }
}


void __stdcall CApp::OnControlChange(IMixerControl* p)
{
    IMixerLine* pml = 0;

    p->get_owner(&pml);

    if(pml)
    {
        OnLineChange(pml);
        SAFE_RELEASE(pml);
    }
}


void CApp::SinkEvents()
{
    if(m_pMixer)
    {
        IUnknown* pUnk = 0;
        m_pMixer->QueryInterface(IID_IUnknown, (void**)&pUnk);
        this->DispEventAdvise(pUnk);
        SAFE_RELEASE(pUnk);
    }
}


void CApp::UnsinkEvents()
{
    if(m_pMixer)
    {
        IUnknown* pUnk = 0;
        m_pMixer->QueryInterface(IID_IUnknown, (void**)&pUnk);
        this->DispEventUnadvise(pUnk);
        SAFE_RELEASE(pUnk);
    }
}


/*
    m_pDest must be VALID.  This function basically 
    just updates the menu system to reflect what was
    selected, so the name of teh function may be deceiving.
*/
HRESULT CApp::OnSelectDestination()
{
    IMixerLine* pLine = 0;
    MENUITEMINFO mii = {0};
    DWORD dwLineID = 0;
    int i = 0;
    int nItems = GetMenuItemCount(m_hDestinations);

    if(!m_pDest) return E_FAIL;

    // Get our line ID.
    m_pDest->QueryInterface(IID_IMixerLine, (void**)&pLine);

    if(!pLine) return E_FAIL;// BAD!

    pLine->get_lineid(&dwLineID);

    SAFE_RELEASE(pLine);

    mii.cbSize = sizeof(mii);
    mii.fMask = MIIM_DATA;

    // Now search em up and select the right one.
    for(i=0;i<nItems;i++)
    {
        if(GetMenuItemInfo(m_hDestinations, i, TRUE, &mii))
        {
            if(mii.dwItemData == dwLineID)
            {
                CheckMenuItem(m_hDestinations, i, MF_CHECKED | MF_BYPOSITION);
            }
            else
            {
                CheckMenuItem(m_hDestinations, i, MF_UNCHECKED | MF_BYPOSITION);
            }
        }
    }

    return S_OK;
}


/*
    This is called right before ConstructDisplay().
    It sets up our mixer and destination objects,
    and then adjusts the menus.

    This function also calls OnSelectDestination()
    because it selects a default destination.
*/
HRESULT CApp::OnSelectMixer(UINT uId)
{
    UnsinkEvents();
    SAFE_RELEASE(m_pDest);
    SAFE_RELEASE(m_pMixer);

    if(FAILED(m_pLibrary->GetMixer(uId, &m_pMixer)))
    {
        // There may be no sound devices on the system.
        odsf(L"OnSelectMixer()", L"Could not gain access to the specified mixer device.  There may be no valid sound devices on the system.");
        return E_FAIL;
    }

    SinkEvents();

    // Now get the default destination.
    if(FAILED(m_pMixer->GetDestination(MIXD_SPEAKERS, &m_pDest)))
    {
        // Failed?  There's no output destination?
        // Well, let's try the recording one then.
        if(FAILED(m_pMixer->GetDestination(MIXD_WAVEIN, &m_pDest)))
        {
            // Major problems!
            odsf(L"OnSelectMixer()", L"No supported mixer destinations were found.");
            return E_FAIL;
        }
    }

    /*
        Set up the menus.
    */

    // Let's try to put a check mark next to the hardware
    // menu item to which this mixer corresponds.
    MENUITEMINFO mii = {0};
    mii.cbSize = sizeof(mii);
    mii.fMask = MIIM_DATA;
    int i = 0;
    int nItems = GetMenuItemCount(m_hHardware);

    for(i=2;i<nItems;i++)
    {
        if(GetMenuItemInfo(m_hHardware, i, TRUE, &mii))
        {
            if(mii.dwItemData == uId)
            {
                // Check it!
                CheckMenuItem(m_hHardware, i, MF_CHECKED | MF_BYPOSITION);
            }
            else
            {
                CheckMenuItem(m_hHardware, i, MF_UNCHECKED | MF_BYPOSITION);
            }
        }
    }

    // Delete all the existing items.
    while(GetMenuItemCount(m_hDestinations))
    {
        RemoveMenu(m_hDestinations, 0, MF_BYPOSITION);
    }

    IEnumMixerDestinations* pEnum = 0;
    IMixerDestination* pDest = 0;
    IMixerLine* pLine = 0;// This is only so we can get the line id
    DWORD dwFetched = 0;
    BSTR str = 0;

    m_pMixer->EnumDestinations(&pEnum);

    if(pEnum)
    {
        while(1)
        {
            pEnum->Next(1, &pDest, &dwFetched);
            if(dwFetched != 1) break;

            // Add a menu item for this
            MENUITEMINFO mii = {0};

            mii.cbSize = sizeof(mii);
            mii.fMask = MIIM_CHECKMARKS | MIIM_DATA | MIIM_STRING | MIIM_STATE | MIIM_FTYPE;
            mii.fType = MFT_STRING| MFT_RADIOCHECK;
            mii.fState = MFS_ENABLED;// | MFS_DEFAULT;
            mii.hbmpChecked = 0;
            mii.hbmpUnchecked = 0;

            pDest->QueryInterface(IID_IMixerLine, (void**)&pLine);
            if(pLine)
            {
                pLine->get_lineid(&mii.dwItemData);

                pLine->get_name(&str);
                mii.dwTypeData = str;
                SysFreeString(str);

                SAFE_RELEASE(pLine);
            }

            // Insert it.
            InsertMenuItem(m_hDestinations, GetMenuItemCount(m_hDestinations), TRUE, &mii);

            SAFE_RELEASE(pDest);
        }

        SAFE_RELEASE(pEnum);
    }

    OnSelectDestination();

    DrawMenuBar(m_Main);

    return S_OK;
}


void CApp::OnOpen()
{
    m_SaveDlg.OnSave(this, FALSE);
}


void CApp::OnSave()
{
    m_SaveDlg.OnSave(this, TRUE);
}


void CApp::Usage()
{
    RECT prect, orect;

    SetRect(&prect, 50, 50, 50, 50);
    SetRect(&orect, -300, -200, 300, 200);
    m_UsageWnd.Create(L"OneLight Volumizer Usage", 0, CApp::UsageProc, g_hInstance, prect, orect,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, this, IDI_ICON1);

    SetRect(&prect, 0, 0, 100, 100);
    SetRect(&orect, 12, 12, -12, -41);
    m_UsageEdit.CreateMultiline(m_UsageWnd, g_hInstance, prect, orect);
    m_UsageEdit.SetFont(L"Courier", 10);
    m_UsageEdit.SetReadOnly(TRUE);

    SetRect(&prect, 100, 100, 100, 100);
    SetRect(&orect, -87, -35, -12, -12);
    m_UsageOk.Create(L"OK", m_UsageWnd, g_hInstance, prect, orect);

    // Fill up all that text.
    HRSRC hRsrc = 0;

    hRsrc = FindResource(g_hInstance, MAKEINTRESOURCE(IDR_USAGE), L"Text");

    if(hRsrc)
    {
        char* szRes = 0;
        DWORD dwSize = 0;

        HGLOBAL hGlobal = LoadResource(g_hInstance, hRsrc);
        dwSize = SizeofResource(g_hInstance, hRsrc);
        szRes = (char*)LockResource(hGlobal);

        SetWindowTextA(m_UsageEdit, szRes);
    }

    m_UsageWnd.Size();
    m_UsageWnd.Show(TRUE);

    MSG msg;
    while(GetMessage(&msg, 0, 0, 0))
    {
        if(!IsDialogMessage(m_UsageWnd, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}


LRESULT CALLBACK CApp::UsageProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CApp* pThis = (CApp*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(uMsg)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_SIZE:
        {
            pThis->m_UsageEdit.Size();
            pThis->m_UsageOk.Size();
            return 0;
        }
    case WM_CLOSE:
        {
            DestroyWindow(hWnd);
            return 0;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    case WM_COMMAND:
        {
            if(LOWORD(wParam) == pThis->m_UsageOk.GetId())
            {
                DestroyWindow(hWnd);
                return 0;
            }
            break;
        }
    case WM_CREATE:
        {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            pThis = (CApp*)pcs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void CApp::OnProperties()
{
    if(m_DisplayProps.DoDialog(this))
    {
        // Update our display to reflect the changes.
        OnNewTheme();
        //ConstructDisplay();
    }

    // now activate our window
    m_Main.Show(TRUE);
    SetForegroundWindow(m_Main);
    SetActiveWindow(m_Main);
    SetFocus(m_Main);
}


void CApp::OnMonitor()
{
    METER_THEME Theme;

    m_Themes.GetMeterTheme(&Theme);

    m_Meter.SetTheme(&Theme, m_Themes.GetThemesEnabled());
    m_Meter.Show(m_Main);
    m_Meter.SetMixer(m_pMixer);
}

void CApp::OnToggleCenter()
{
    HMENU hOptions = GetSubMenu(m_hMenu, 0);

    switch(m_Settings.m_bCenter)
    {
    case FALSE:
        {
            // make it centered.
            m_Settings.m_bCenter = TRUE;
            CenterWindow(m_Main, GetDesktopWindow());
            CheckMenuItem(hOptions, ID_OPTIONS_CENTER, MF_BYCOMMAND | MF_CHECKED);
            break;
        }
    case TRUE:
        {
            // make it un-centered.
            m_Settings.m_bCenter = FALSE;
            CheckMenuItem(hOptions, ID_OPTIONS_CENTER, MF_BYCOMMAND | MF_UNCHECKED);
            break;
        }
    }
    return;
}

void CApp::OnAlwaysOnTop()
{
    switch(m_Settings.m_bAlwaysOnTop)
    {
    case FALSE:
        {
            SetWindowPos(m_Main, HWND_TOPMOST,
                0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            
            m_Settings.m_bAlwaysOnTop = TRUE;

            HMENU hOptions = GetSubMenu(m_hMenu, 0);
            CheckMenuItem(hOptions, IDM_ALWAYSONTOP, MF_BYCOMMAND | MF_CHECKED);
            break;
        }
    case TRUE:
        {
            SetWindowPos(m_Main, HWND_NOTOPMOST,
                0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            
            m_Settings.m_bAlwaysOnTop = FALSE;

            HMENU hOptions = GetSubMenu(m_hMenu, 0);
            CheckMenuItem(hOptions, IDM_ALWAYSONTOP, MF_BYCOMMAND | MF_UNCHECKED);
            break;
        }
    }
}


void CApp::SizeupControls()
{
    RECT prect, orect;

    if(m_nPots == 0)
    {
        RECT rc;
        GetWindowRect(m_cNoControls, &rc);
        SetWindowPos(m_Main, (HWND)0, 0, 0, rc.right - rc.left,
            rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
        return;
    }

    int x = m_nPots * CCPot::GetGlobalWidth();
    int i;

    RECT rc = {0, 0, x, CCPot::GetGlobalHeight()};
    AdjustWindowRect(&rc, GetWindowLong(m_Main, GWL_STYLE), TRUE);
    OffsetRect(&rc, -rc.left, -rc.top);
    SetWindowPos(m_Main, (HWND)0, 0, 0, rc.right, rc.bottom, SWP_NOMOVE | SWP_NOZORDER);

    x = 0;
    for(i=0;i<m_nPots;i++)
    {
        SetRect(&prect, 0, 0, 0, 0);
        SetRect(&orect, x, 0, x+CCPot::GetGlobalWidth(), CCPot::GetGlobalHeight());
        m_pPots[i].SetPlacement(&prect, &orect);
        m_pPots[i].Size();
        x += CCPot::GetGlobalWidth();
    }

    {
        // 2003-05-04 Carl Corcoran
        // if the window is too short (maybe the menus have wrapped) then let's increase to the
        // correct height.
        RECT rcClient;
        RECT rcWindow;
        GetClientRect(m_Main, &rcClient);
        if(rcClient.bottom != CCPot::GetGlobalHeight())
        {
            int nAmountToAdjust = CCPot::GetGlobalHeight() - rcClient.bottom;
            GetWindowRect(m_Main, &rcWindow);
            rcWindow.bottom += nAmountToAdjust;
            SetWindowPos(m_Main, (HWND)0, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom-rcWindow.top, SWP_NOMOVE | SWP_NOZORDER);
        }
    }
}


void CApp::OnNewTheme()
{
    METER_THEME Theme;
    BOOL bDisplayMeter = m_Meter.IsDisplayed();

    TearDown();
    ConstructDisplay();

    m_Themes.GetMeterTheme(&Theme);
    m_Meter.SetTheme(&Theme, m_Themes.GetThemesEnabled());
    if(bDisplayMeter == TRUE)
    {
        m_Meter.Show(m_Main);
        m_Meter.SetMixer(m_pMixer);
    }

    return;
}


bool CApp::RegKeyValid(const char* szKey)
{
    bool r = false;

    // check if the serial is good.
    // 584-224-879-443
    // this is what the user has to type to generate the szCorrectKey

    unsigned char szCorrectKey[] = { 0x55, 0xB2, 0x80, 0xF3,
                                     0x3A, 0x00, 0x68, 0xAB,
                                     0x88, 0xED, 0x3D, 0x03,
                                     0x6C, 0xB6, 0x9F, 0xD6
    };
    unsigned char szCompare[20] = {0};
    memcpy(szCompare, szKey, MAX_KEY_LEN);

    if(memcmp(szCompare, szCorrectKey, sizeof(szCorrectKey)) == 0)
    {
        r = true;
    }

    return r;
}


bool CApp::RegKeyValid()
{
    bool r = RegKeyValid(m_Settings.m_szRegKey);
    if(!r)
    {
        MsgBoxf(L"Reg key is invalid...");
        m_Settings.LoadDefaultContactInfo();
    }
    return r;
}


bool CApp::SplashEntry()
{
    bool r = false;

    if(RegKeyValid())
    {
        r = true;// OK to go.
    }
    else
    {
        CVolumizerSplash ss;
        r = ss.Show(CalculateDaysLeft(), this);
    }

    return r;
}


// We make these checks:
// - existance of valid registry info
// - file creation date vs. install date
// - today vs. install date.
int CApp::CalculateDaysLeft()
{
    bool bPass = false;
    int nDaysLeft = 0;

    CCUINT64 uiFile;
    CCUINT64 uiInstall;
    CCUINT64 uiToday;

    FILETIME ftInstall;
    FILETIME ftToday;
    SYSTEMTIME stToday;

    SystemTimeToFileTime(&m_Settings.m_InstallDate, &ftInstall);
    uiInstall = FileTimeToInt64(ftInstall);

    GetLocalTime(&stToday);
    SystemTimeToFileTime(&stToday, &ftToday);
    uiToday = FileTimeToInt64(ftToday);

    // #1
    if(!m_Settings.ExistsInRegistry())
    {
        MsgBoxf(L"Doesn't exist in registry...");
    }
    else
    {
        bPass = true;
        // #2
        // check to see if the exe file created time is incorrect.
        // it must be on the SAME day as the install date, and BEFORE today.
        //WCHAR wszExeName[MAX_PATH] = {0};
        //GetModuleFileName(g_hInstance, wszExeName, MAX_PATH);

        //HANDLE hExe = CreateFile(wszExeName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        //    OPEN_EXISTING, 0, 0);
        //if((hExe != INVALID_HANDLE_VALUE) || (hExe != 0))
        //{
        //    // success... I don't see that this would EVER fail.
        //    FILETIME ftCreated;
        //    if(0 != GetFileTime(hExe, NULL, NULL, &ftCreated))
        //    {
        //        // success...
        //        SYSTEMTIME stFile;
        //        FILETIME ftFile;
        //        FileTimeToLocalFileTime(&ftCreated, &ftFile);

        //        uiFile = FileTimeToInt64(ftFile);
        //        FileTimeToSystemTime(&ftFile, &stFile);

        //        if(uiFile < uiInstall)
        //        {
        //            // pass!
        //            if(uiFile < uiToday)
        //            {
        //                // pass!
        //                bPass = true;
        //            }
        //            else
        //            {
        //                MsgBoxf(L"File later than today...");
        //            }
        //        }
        //        else
        //        {
        //            MsgBoxf(L"File later than installation date...");
        //        }
        //    }

        //    CloseHandle(hExe);
        //}
    }

    if(!bPass) return 0;
    // #3: check days left.
    nDaysLeft = EVAL_PERIOD - GetDaysDifference(ftInstall);
    if(nDaysLeft <= 0)
    {
        MsgBoxf(L"Eval period expired...");
        nDaysLeft = 0;
    }

    return nDaysLeft;
}


INT_PTR CALLBACK CApp::RegistrationDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CApp* pThis = (CApp*)GetProp(hWnd, VOLUMIZER_WND_PROP);

    switch(uMsg)
    {
    case WM_INITDIALOG:
        {
            pThis = (CApp*)lParam;
            SetProp(hWnd, VOLUMIZER_WND_PROP, (HANDLE)pThis);

            // fill in existing registration info
            // name, organization, key
            SetDlgItemText(hWnd, IDC_NAME, pThis->m_Settings.m_szName);
            SetDlgItemText(hWnd, IDC_ORGANIZATION, pThis->m_Settings.m_szOrganization);

            if(pThis->RegKeyValid())
            {
                // valid reg key
                CCString s;
                s.FromBinary(pThis->m_Settings.m_szRegKey, MAX_KEY_LEN);
                SetDlgItemText(hWnd, IDC_KEY, s);

                SendDlgItemMessage(hWnd, IDC_ORGANIZATION, EM_SETREADONLY, TRUE, 0);
                SendDlgItemMessage(hWnd, IDC_NAME, EM_SETREADONLY, TRUE, 0);
                SendDlgItemMessage(hWnd, IDC_KEY, EM_SETREADONLY, TRUE, 0);
                EnableWindow(GetDlgItem(hWnd, IDC_ORDER), FALSE);
                EnableWindow(GetDlgItem(hWnd, IDOK), FALSE);
            }
            else
            {
                SendDlgItemMessage(hWnd, IDC_KEY, EM_SETLIMITTEXT, 16, 0);
            }

            return TRUE;
        }
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
            case IDC_EULA:
                {
                    // show the order form.
                    CCString path;
                    GetModuleFileName(NULL, path.GetBuffer(MAX_PATH), MAX_PATH);
                    path.Path_StripToPath();
                    path.Path_Append(L"eula.txt");
                    CCString cd;
                    cd.Path_GetCurrentDirectory();
                    ShellExecute(0, NULL, path, NULL, cd, SW_SHOW);
                    return TRUE;
                }
            case IDC_ORDER:
                {
                    // show the order form.
                    CCString path;
                    GetModuleFileName(NULL, path.GetBuffer(MAX_PATH), MAX_PATH);
                    path.Path_StripToPath();
                    path.Path_Append(L"order.rtf");
                    CCString cd;
                    cd.Path_GetCurrentDirectory();
                    ShellExecute(0, NULL, path, NULL, cd, SW_SHOW);
                    return TRUE;
                }
            case IDOK:
                {
                    // verify the information.
                    CCString s;
                    s.FromWindow(GetDlgItem(hWnd, IDC_KEY));
                    pThis->m_Settings.SetKey(s);
                    s.FromWindow(GetDlgItem(hWnd, IDC_NAME));
                    pThis->m_Settings.SetName(s);
                    s.FromWindow(GetDlgItem(hWnd, IDC_ORGANIZATION));
                    pThis->m_Settings.SetOrganization(s);

                    pThis->RegKeyValid();

                    EndDialog(hWnd, 0);
                    return TRUE;
                }
            case IDCANCEL:
                // make no changes
                EndDialog(hWnd, 0);
                return TRUE;
            }

            break;
        }
    case WM_CLOSE:
        {
            // make no changes
            EndDialog(hWnd, 0);
            return TRUE;
        }
    }
    return FALSE;
}


void CApp::DoRegistrationDialog(HWND hParent)
{
    DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_REGISTRATION),
        hParent, CApp::RegistrationDlgProc, (LPARAM)this);

    return;
}


void CApp::DoAboutDialog()
{
    CVolumizerAbout x;
    x.Entry(m_Main, this->m_Settings);
    return;
}

