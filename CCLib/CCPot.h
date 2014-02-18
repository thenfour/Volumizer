/*
    This is the control that will drive the entire
    line controls on the mixer.

    This sucker sends a WM_NOTIFY where the code is either
    PN_MUTE, PN_VOL, or PN_BAL to indicate which item
    changed.
*/


#pragma once


#include <windows.h>
#include "global.h"
#include "CCControl.h"
#include "SimpleImage.h"
#include "CCPotNoTheme.h"


/*
#define POT_MUTE_RECT 34, 243, 59, 255

#define POT_BAL_CENTER_X 46// X coord of the center of the balance pot
#define POT_BAL_CENTER_Y 47// Y coord of the center of the balance pot
#define POT_BAL_LENGTH   19// Length of the balance thumb line

#define POT_VOL_TOP 86// Y Coord of the top of the active area
#define POT_VOL_BOTTOM 219//

#define POT_BACK_COLOR RGB(0x28,0x3F,0x2F)
#define POT_BAL_COLOR  RGB(0xAF,0xAF,0x9A)
#define POT_TEXT_COLOR RGB(0xAF,0xAF,0x9A)

#define POT_ANGLE_RESTRICTION 45// Angle off-center where the valid values start.

#define POT_FILE_THUMB  L"thumb.bmp"
#define POT_FILE_BACK   L"back.bmp"
#define POT_FILE_ON     L"on.bmp"
#define POT_FILE_OFF    L"off.bmp"
#define POT_FILE_BAL    L"bal.bmp"
*/

#define POT_VOL_MIN 0
#define POT_VOL_MAX 65535
#define POT_BAL_MIN 0
#define POT_BAL_MAX 65535

#define POT_CLASS      L"Mixer-Line-Controls"


struct CCEXPORT POT_THEME
{
    RECT rcMute;// Rect where the mute button is actually located.
    POINT ptBalCenter;// Center of the balance pot.
    int nBalLength;
    int nVolumeTop;// Y-coord of where teh volume slider is
    int nVolumeBottom;//
    COLORREF clrBack;
    COLORREF clrBal;// Balance line color
    int nBalAngleRestriction;// Angle off-center where the valid values start.

    // where to blit the mute images and balance image.  if these are -1, the default will be used.
    int nMuteXPlacement;
    int nMuteYPlacement;
    int nBalXPlacement;
    int nBalYPlacement;

    // Filenames
    CCString sThumb;
    CCString sBack;
    CCString sOn;
    CCString sOff;
    CCString sBal;

    // text
    CCString sFont;
    RECT rcText;// if bottom or right are 0, defaults are used.
    int nFontSize;
    COLORREF clrText;// The color of the name of the control
};


// Stuff for the notification msg.
#define PN_MUTE 0
#define PN_VOL  1
#define PN_BAL  2


/*
    Used for determining what the user is currently doing.
*/
enum POT_STATE
{
    POT_IDLE = 0,
    POT_VOL = 1,
    POT_BAL = 2,
    POT_MUTE = 3

};


class CCEXPORT CCPot : public CCControl
{
    friend class CCPotNoTheme;

public:
    CCPot();
    ~CCPot();

    HRESULT Create(HWND hParent, int x, int y);
    static void SetTheme(POT_THEME* pThemeData, BOOL bEnabled);

    int GetVol();
    BOOL GetMute();
    int GetBal();

    void Destroy();

    void SetVol(int n);
    void SetMute(BOOL b);
    void SetBal(int n);
    void UseMute(BOOL b);
    void UseBal(BOOL b);
    void UseVol(BOOL b);

    void SetUserData(void* p);
    void* GetUserData();

    static COLORREF GetGlobalBackColor();
    static int GetGlobalWidth();
    static int GetGlobalHeight();

private:

    void _RegisterWindowClass();

    void* m_pUser;

    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    void OnLButtonDown(int x, int y);
    void OnLButtonUp(int x, int y);
    void OnMouseMove(int x, int y);

    static void FreeTheme();
    static POT_THEME m_CurrentTheme;
    static BOOL m_bTheme;// is the theme enabled?

    void Draw(HDC dc);

    /*
        From a value, returns the point where the line should
        be drawn from.
    */
    void Balance_ValueToPoint(int nVal, int* x, int* y);

    /*
        From a point, client coords, returns the value
        to which that point corresponds.
    */
    int Balance_PointToValue(int x, int y);

    double _AngleFromPoint(int x, int y);
    void _PointFromAngle(int* x, int* y, double fAngle);
    int ValueToY(int v);
    int YToValue(int y);// in client coords.

    /*
        In order to better manage memory, only use one set
        of these guys at a time, so make them static.  In
        order to properly maintain them, we need to keep a
        ref count for this class, then.
    */
    static int m_nRefCt;
    static CSimpleImage m_Back;
    static CSimpleImage m_Thumb;
    static CSimpleImage m_On;
    static CSimpleImage m_Off;
    static CSimpleImage m_Bal;

    static HBRUSH m_hBackColor;
    static HPEN m_hBalPen;
    static HFONT m_hGlobalFont;

    static HBITMAP m_hBuffer;

    int m_nVol;
    BOOL m_bMute;
    int m_nBal;
    BOOL m_bUseMute;
    BOOL m_bUseBal;
    BOOL m_bUseVol;

    // More UI stuff!
    POT_STATE m_State;
    int m_nOriginalValue;// Value before they changed it, so they can cancel.

    BOOL _HitMute(int x, int y);

    CCString m_sText;

    CCPotNoTheme m_NoTheme;// this handles all the stuff with the standard windows gui stuff
};


