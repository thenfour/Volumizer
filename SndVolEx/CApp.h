/*
    Let's talk about different behaviors with different destination types
    selected.
*/


#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include "CAppSettings.h"
#include "SaveDlg.h"
#include "DisplayProperties.h"
#include "..\\CCLib\\RecentFiles.h"
#include "..\\CCLib\\utilities.h"
#include "MeterWindow.h"
#include "ThemeManager.h"
#include "splash.h"


static _ATL_FUNC_INFO OnLineChangeInfo = { CC_STDCALL, VT_EMPTY, 1, {VT_UNKNOWN} };
static _ATL_FUNC_INFO OnControlChangeInfo = { CC_STDCALL, VT_EMPTY, 1, {VT_UNKNOWN} };


#define VOLUMIZER_WND_PROP L"VolumizerInfoPtr"


class CApp :
    public IDispEventSimpleImpl<0, CApp, &DIID__IMixerEvents>,
    public CVolumizerRegistrationInterface
{
    friend class CSaveDlg;
    friend class CDisplayProperties;
    friend class CThemeManager;
public:

    CApp();
    ~CApp();

    void Entry(PCWSTR wszCmdLine);

    BEGIN_SINK_MAP(CApp)
         SINK_ENTRY_INFO(0, DIID__IMixerEvents, 1, OnLineChange, &OnLineChangeInfo)
         SINK_ENTRY_INFO(0, DIID__IMixerEvents, 2, OnControlChange, &OnControlChangeInfo)
    END_SINK_MAP()

    void __stdcall OnLineChange(IMixerLine* pLine);
	void __stdcall OnControlChange(IMixerControl* p);

    /*
        This is called by the theme manager when the user changes the theme.
        At this point, the app will tear down and reconstruct its controls,
        as well as the meter window.
    */
    void OnNewTheme();

private:

    // displays the splash screen, does the verification for time and stufff.
    bool SplashEntry();
        int CalculateDaysLeft();

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void OnBal(CCPot* pPot);
    void OnVol(CCPot* pPot);
    void OnMute(CCPot* pPot);
    void OnOpen();
    void OnSave();
    void OnProperties();
    void OnMonitor();
    void OnAlwaysOnTop();
    void OnToggleCenter();

    /*
        When there are no pot controls, here's a little message that
        we put up on the screen.
    */
    CCStatic m_cNoControls;

    CSaveDlg m_SaveDlg;

    CThemeManager m_Themes;

    /*
        Call this to sink the current mixer object so can
        receive events.
    */
    void SinkEvents();
    void UnsinkEvents();

    /*
        Since we'll be doing our own modifications to the UI every
        once in a while, we need a flag that tells whether or
        not to process incoming change messages from the pot controls.
    */
    BOOL m_bAcceptUIChanges;

    /*
        ConstructDisplay() will breakdown, if necessary, the existing dynamic
        controls, and reconstruct them all.  There must be a valid m_pLibrary
        to do this.  It will try to use the current settings, or it will
        use defaults if there are no current m_pDest and m_pMixer objects.

        TearDown() also affects the level meter window.
    */
    HRESULT ConstructDisplay();
    void TearDown();

    /*
        Returns TRUE if the pot was used.  Otherwise, if the pot wasn't used
        it should be skipped.
    */
    BOOL SetupPotControl(IMixerLine* pLine, CCPot* pPot, IN OUT int* px);

    /*
        This doesn't reconstruct anything - just updates the display.
    */
    void RefreshDisplay();
    void RefreshPot(CCPot* pPot);

    IMixerLibrary* m_pLibrary;
    IMixerDestination* m_pDest;
    IMixer* m_pMixer;

    HMENU m_hMenu;
    HMENU m_hHardware;
    HMENU m_hDestinations;
    CCCustomWnd m_Main;
    CCPot* m_pPots;
    int m_nPots;// Number of VALID pots.  The number allocated may be more.

    void SizeupControls();// Sizes the already-created pots, and the main window.

    /*
        Since the resources associated with teh pot control
        are static, and they are only available when there
        is an instance of the class, here we will make sure
        that they are ALWAYS available.
    */
    CCPot m_abcdefg;

    /*
        We put the type of destination we're currently displaying here.
        This is because the MIXD_SPEAKERS and MIXD_WAVEIN destinations
        just act differently.
    */
    MIX_DESTINATION m_DestType;
    BOOL m_bMuxMute;// TRUE if the mute buttons work as mux selectors.

    // Constructs the menu system for destinations
    // when a mixer is selected.
    HRESULT OnSelectMixer(UINT uId);
    HRESULT OnSelectDestination();

    CAppSettings m_Settings;
    CDisplayProperties m_DisplayProps;

    void Usage();
    static LRESULT CALLBACK UsageProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    CCCustomWnd m_UsageWnd;
    CCEditBox   m_UsageEdit;
    CCButton    m_UsageOk;

    CRecentFiles m_RecentFiles;

    CMeterWindow m_Meter;

    static INT_PTR CALLBACK RegistrationDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void DoRegistrationDialog(HWND hParent);

    bool RegKeyValid();
    bool RegKeyValid(const char* szKey);// szKey must be

    void DoAboutDialog();
};


