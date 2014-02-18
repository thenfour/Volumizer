

#include <windows.h>
#include "..\\cclib\\cccontrols.h"


class CMeterWindow
{
public:
    CMeterWindow();
    ~CMeterWindow();

    HRESULT Hide();
    HRESULT Show(HWND hParent);// Make sure you SetTheme() before you Show().
    HRESULT SetTheme(METER_THEME* pTheme, BOOL bTheme);// Changes the theme.
    HRESULT SetMixer(IMixer* pMixer);// Changes the current device

    BOOL IsDisplayed();

    //void Entry(HWND hParent, IMixer* pMixer, METER_THEME* pTheme, BOOL bTheme);

private:

    // Takes the existing controls and resizes them to the correct layout for
    // this window.
    void _SizeupControls();

    CLevelMeter m_Meter;
    CCCustomWnd m_Main;
    CComboBox m_Select;// For selecting the different sound cards.

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

