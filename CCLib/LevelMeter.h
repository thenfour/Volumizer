/*
    Level meter that monitors recording source for a given device.
    Works only for 2 channels.

    Although I hate to do it, I put the DirectSound capture stuff right
    in next to all the GUI stuff.  Splitting it all up just didn't seem
    right for this type of scenario.

    Basically we will set up a multimedia timer in another thread.  The
    timer will go off every time we are to update the display... this
    means that the timer interval will be approx. the latency time.

    Every time the timer fires, we calculate the volume of the buffer
    that we haven't yet used.  We update our display, and advance our
    "already used" buffer-pointer.
*/


#pragma once


#include <windows.h>
#include "global.h"
#include "CCControl.h"
#include "SimpleImage.h"
#include <dsound.h>
#include "CCProgressBar.h"


struct CCEXPORT METER_THEME
{
    CCString sOn;
    CCString sOff;
    int nStartX;
    int nLEDCount;
    int nStepX;
};


class CCEXPORT CLevelMeter : public CCControl
{
public:
    CLevelMeter();
    ~CLevelMeter();

    void Create(HINSTANCE hInstance, HWND hParent, int x, int y, const RECT& orect, const RECT& prect);
    HRESULT SetTheme(METER_THEME* p, BOOL bEnabled);

    int GetHeight();
    int GetWidth();

    /*
        Though it may be deceiving, these two functions completely 
        initialize / uninitialize our DirectSound stuff.
    */
    HRESULT StartCapture(int nDevice, PCWSTR wszName);
    void StopCapture();

    void SetDefaultSize(int x, int y);

	HRESULT Size();

private:

    static int m_nDefaultHeight;
    static int m_nDefaultWidth;

    void _CreateProgressBars();
    CCProgressBar m_ProgressBarL;// For use when there is no theme.
    CCProgressBar m_ProgressBarR;// For use when there is no theme.

    METER_THEME m_Theme;
    BOOL m_bTheme;

    void FreeTheme();

    // Window stuff
    void Draw(HDC dc);
    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    // y = yellow, g = green, r = red.
    // 0 = off, 1 = on.
    CSimpleImage m_on;
    CSimpleImage m_off;

    // Our double-buffer... buffer.
    HBITMAP m_hBuffer;
    HDC m_dc;// For keepin around for the long haul too.

    // The timer proc - this gets called every time we are supposed to
    // update the display.
    static void CALLBACK TimeProc(UINT uID, UINT, DWORD dwUser, DWORD, DWORD);

    static BOOL CALLBACK DSEnumCallback(LPGUID lpGuid, PCWSTR, PCWSTR, PVOID pUser);
    GUID m_Device;// The callback will fill in this GUID for the initialize() function to use.
    //int m_iDevice;// index of the device to be gotten.  We decrement this and when it hits 0, we use the device.
    CCString m_strDevice;// name of the device - we use this to compare when enumerating.
    int m_iClosest;// the number of characters that are similar in the closest match so far.
    BOOL m_bMatch;// Was there a match for the device?

    MMRESULT m_nTimer;// The multimedia timer-id.
    DWORD m_dwLastPosition;// Last position in the buffer, so we know how much audio data to examine.
    DWORD m_dwBufferSize;
    IDirectSoundCapture* m_pDSC;
    IDirectSoundCaptureBuffer* m_pDSCB;
    WAVEFORMATEX m_Format;

    int m_nLeft;
    int m_nRight;

    // For use when there is no theme.  Otherwise the placement rects are
    // calculated on the fly.
    RECT m_orect_notheme;
    RECT m_prect_notheme;
};


