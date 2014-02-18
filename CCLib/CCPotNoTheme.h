

#pragma once


#include <windows.h>
#include "global.h"


class CCEXPORT CCPotNoTheme
{
public:
    CCPotNoTheme();
    ~CCPotNoTheme();

    HRESULT Create(HWND hParent, int x, int y, class CCPot*);
    void Destroy();

    int GetVol();
    BOOL GetMute();
    int GetBal();

    void SetVol(int n);
    void SetMute(BOOL b);
    void SetBal(int n);
    void UseMute(BOOL b);
    void UseBal(BOOL b);
    void UseVol(BOOL b);

    static int GetGlobalWidth();
    static int GetGlobalHeight();

    static void Startup();
    static void Shutdown();

private:

    /*
        In order for GetGlobalWidth and GetGlobalHeight to work
        without a window, we need to create one of the dialogs as
        a hidden, standalone window.  That's the "example" window.
    */
    static HWND m_hExample;
    static INT_PTR CALLBACK ExampleProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void SendNotification(UINT uMsg);

    BOOL m_bMute;

    class CCPot* m_pOwner;

    static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


