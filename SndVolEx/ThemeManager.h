/*
    There is always 1 file called themes.xml in the same dir as the EXE.
    This contains several <theme> elements that contain information
    about the different themes available on the system.

    Each theme data file is any .xml file that contains all the settings
    needed for display.

    In the registry we will save the name of the THEME XML.

    HKCU\\Software\\OneLightVolumizer\\Theme
    (default value)
*/


#pragma once


#include <windows.h>
#include "..\\CCLib\\XMLConfig.h"


class CThemeManager
{
public:
    CThemeManager();
    ~CThemeManager();

    /*
        Loads the theme completely, from registry.
    */
    HRESULT LoadTheme();
    HRESULT Commit();// Saves our current theme to registry
    HRESULT GetMeterTheme(METER_THEME* pDest);
    BOOL GetThemesEnabled();

    HRESULT ThemesDialog(class CApp* pOwner);
    HRESULT LoadTheme(PCWSTR wszFile);

private:

    HRESULT GetThemesFileName(CCString* ps);

    class CApp* m_pOwner;

    // Grabs the name of the theme that's loaded in registry.
    // If there isn't anything in the registry, or it's not valid,
    // we will get the default theme file if possible.
    HRESULT GetDataFromRegistry();

    // Called by GetDataFromRegistry to nab the default theme file.
    HRESULT GetDefaultThemeFile();

    CCString m_sThemeFile;

    METER_THEME m_Meter;
    POT_THEME m_Pot;
    BOOL m_bThemesEnabled;

    HWND m_hParent;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    CCCustomWnd m_Main;
    CCListBox m_List;
    CCButton m_Button;
    CCCheckBox m_ThemesEnabled;
    CCStatic m_Static;
    void SetupList();
};

