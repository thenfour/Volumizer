

#include "stdafx.h"
#include "LevelMeter.h"
#include "Utilities.h"
#include <stdio.h>
#include <shlwapi.h>


/*
#define METER_START 5
#define METER_COUNT 10
#define METER_STEP 29
*/


#define LEVEL_METER_CLASS    L"LevelMeterClass"
#define BUFFER_SECONDS 3
#define TIMER_DELAY 50
#define MAX_SAMPLE 32768


int CLevelMeter::m_nDefaultHeight = 0;
int CLevelMeter::m_nDefaultWidth = 0;


CLevelMeter::CLevelMeter()
{
    m_nLeft = 0;
    m_nRight = 0;
    m_bMatch = FALSE;
    m_pDSC = 0;
    m_bTheme = FALSE;
    m_pDSCB = 0;
}


CLevelMeter::~CLevelMeter()
{
    StopCapture();
    FreeTheme();
}


void CLevelMeter::_CreateProgressBars()
{
    if(::IsWindow(m_hWnd))
    {
        RECT orect, prect;
        SetRect(&orect, 0, 0, 0, 0);
        SetRect(&prect, 0, 0, 0, 0);
        SetPlacement(&m_prect_notheme, &m_orect_notheme);
        m_ProgressBarL.Create(CCProgressBar::DefaultProcNoText, 0, m_hWnd, prect, orect);
        m_ProgressBarR.Create(CCProgressBar::DefaultProcNoText, 0, m_hWnd, prect, orect);
        m_ProgressBarL.SetMin(0);
        m_ProgressBarL.SetMax(32768);
        m_ProgressBarR.SetMin(0);
        m_ProgressBarR.SetMax(32768);
    }
}


HRESULT CLevelMeter::SetTheme(METER_THEME* p, BOOL bEnabled)
{
    FreeTheme();
    BOOL bWasEnabled = m_bTheme;
    m_bTheme = bEnabled;

    if((bWasEnabled == FALSE) && (bEnabled == TRUE))
    {
        // Destroy the progress bar.
        m_ProgressBarR.Destroy();
        m_ProgressBarL.Destroy();
    }
    else if(bEnabled == FALSE)
    {
        // Create the progress bar and leave.
        _CreateProgressBars();
        return S_OK;
    }

    m_Theme.nLEDCount = p->nLEDCount;
    m_Theme.nStepX = p->nStepX;
    m_Theme.nStartX = p->nStartX;

    m_off.Load(p->sOff);
    m_on.Load(p->sOn);

    HDC dcScreen = GetDC(0);
    m_hBuffer = CreateCompatibleBitmap(dcScreen, GetWidth(), GetHeight());
    ReleaseDC(0, dcScreen);

    m_dc = CreateCompatibleDC(NULL);
    SelectObject(m_dc, m_hBuffer);

    return S_OK;
}


void CLevelMeter::FreeTheme()
{
    m_on.Free();
    m_off.Free();

    if(m_hBuffer)
    {
        DeleteObject(m_hBuffer);
        m_hBuffer = 0;
    }

    if(m_dc)
    {
        DeleteDC(m_dc);
        m_dc = 0;
    }
}


void CLevelMeter::Create(HINSTANCE hInstance, HWND hParent, int x, int y, const RECT& orect, const RECT& prect)
{
    CopyRect(&m_orect_notheme, &orect);
    CopyRect(&m_prect_notheme, &prect);

    SetRect(&m_prect, 0, 0, 0, 0);
    SetRect(&m_orect, x, y, x+GetWidth(), y+GetHeight());

    WNDCLASSEX wcx = {0};
    wcx.cbSize = sizeof(wcx);
    wcx.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wcx.hCursor = LoadCursor(0, IDC_ARROW);
    wcx.hInstance = hInstance;
    wcx.lpfnWndProc = CLevelMeter::WndProc;
    wcx.lpszClassName = LEVEL_METER_CLASS;
    wcx.style = CS_VREDRAW | CS_HREDRAW;
    RegisterClassEx(&wcx);

    m_hWnd = CreateWindowEx(0, LEVEL_METER_CLASS, L"",
        WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hParent, (HMENU)m_id,
        hInstance, this);

    if(m_bTheme == FALSE)
    {
        _CreateProgressBars();
    }

    SetFont();
    Size();

    return;
}


int CLevelMeter::GetHeight()
{
    if(m_bTheme == FALSE) return m_nDefaultHeight;
    return m_off.m_bm.bmHeight;
}


int CLevelMeter::GetWidth()
{
    if(m_bTheme == FALSE) return m_nDefaultWidth;
    return m_off.m_bm.bmWidth;
}


HRESULT CLevelMeter::StartCapture(int nDevice, PCWSTR wszName)
{
    DSCCAPS dsc;
    DSCBUFFERDESC1 dscbDesc;
    HRESULT hr;

    StopCapture();

    // Set up our wave format.
    InitWaveFormatStruct(&m_Format, 2, 22050, 16);

    // Get the right device's GUID.
    //m_iDevice = nDevice;
    m_strDevice = wszName;
    m_bMatch = FALSE;
    m_iClosest = 9999;
    memset(&m_Device, 0, sizeof(GUID));
    DirectSoundCaptureEnumerate(CLevelMeter::DSEnumCallback, this);

    if(m_bMatch == FALSE) return E_FAIL;

    // Create DirectSoundCapture object.
    if(FAILED(hr = DirectSoundCaptureCreate(&m_Device, &m_pDSC, NULL)))
    {
        return hr;
    }

    /*
        Here is where we should check the capabilities of the sound card against
        the format that was passed in.
    */
    dsc.dwSize = sizeof(DSCCAPS);
    if(FAILED(hr = m_pDSC->GetCaps(&dsc)))
    {
        SAFE_RELEASE(m_pDSC);
        return hr;
    }

    /*
        Create the capture buffer.
    */
    dscbDesc.dwSize = sizeof(dscbDesc);
    dscbDesc.dwFlags = DSCBCAPS_WAVEMAPPED;
    dscbDesc.dwBufferBytes = (m_Format.nAvgBytesPerSec * BUFFER_SECONDS);
    dscbDesc.dwReserved = 0;
    dscbDesc.lpwfxFormat = &m_Format;
    m_dwBufferSize = dscbDesc.dwBufferBytes;

    if(FAILED(hr = m_pDSC->CreateCaptureBuffer((DSCBUFFERDESC*)&dscbDesc, &m_pDSCB, NULL)))
    {
        SAFE_RELEASE(m_pDSC);
        return hr;
    }

    // Now start up our timer!
    m_nTimer = timeSetEvent(TIMER_DELAY, TIMER_DELAY/2, CLevelMeter::TimeProc, (DWORD_PTR)this, TIME_PERIODIC);

    // Start capture
    m_pDSCB->Start(DSCBSTART_LOOPING);

    return S_OK;
}


void CLevelMeter::StopCapture()
{
    if(m_nTimer)
    {
        // Stop our timer
        timeKillEvent(m_nTimer);
        m_nTimer = 0;
    }

    if(m_pDSCB)
    {
        m_pDSCB->Stop();
    }

    SAFE_RELEASE(m_pDSCB);
    SAFE_RELEASE(m_pDSC);

    m_dwLastPosition = 0;

    return;
}


void CALLBACK CLevelMeter::TimeProc(UINT uID, UINT, DWORD dwUser, DWORD, DWORD)
{
    BYTE* pBuf1 = 0;
    BYTE* pBuf2 = 0;
    DWORD dwBuf1 = 0;
    DWORD dwBuf2 = 0;
    DWORD dwLockBytes = 0;
    DWORD dwReadCursor = 0;

    CLevelMeter* pThis = (CLevelMeter*)dwUser;

    // Make sure we're OK TO GO, ELLIE
    if(!pThis) return;
    if(!pThis->m_pDSCB) return;

    if(FAILED(pThis->m_pDSCB->GetCurrentPosition(0, &dwReadCursor)))
    {
        return;
    }

    // Determine how many bytes we need to lock.  We may not need to read anything.
    if(dwReadCursor >= pThis->m_dwLastPosition)
    {
        dwLockBytes = dwReadCursor - pThis->m_dwLastPosition;
    }
    else
    {
        dwLockBytes = dwReadCursor + (pThis->m_dwBufferSize - pThis->m_dwLastPosition);
    }

    if(dwLockBytes == 0)
    {
        return;
    }

    // Check our sound buffer to see what's up yo
    if(FAILED(pThis->m_pDSCB->Lock(pThis->m_dwLastPosition, dwLockBytes, 
        (void**)&pBuf1, &dwBuf1, (void**)&pBuf2, &dwBuf2, 0)))
    {
        return;
    }

    // Now we scan through the thing and come up with a value that represents
    // the volume.  The buffer is a bunch of signed WORDs.
    signed short* p = 0;
    signed short wl, wr;// the left/right values.
    int i = 0;
    int nTotal = 0;

    pThis->m_nLeft = 0;
    pThis->m_nRight = 0;

    p = (signed short*)pBuf1;
    nTotal = dwBuf1 / 2;// divide by number of bytes in a WORD.

    for(i=0;i<nTotal;i+=2)
    {
        wl = abs(p[i]);
        wr = abs(p[i+1]);
        pThis->m_nLeft = max(pThis->m_nLeft, wl);
        pThis->m_nRight = max(pThis->m_nRight, wr);
    }

    p = (signed short*)pBuf2;
    nTotal = dwBuf2 / 2;// divide by number of bytes in a WORD.

    for(i=0;i<nTotal;i+=2)
    {
        wl = abs(p[i]);
        wr = abs(p[i+1]);
        pThis->m_nLeft = max(pThis->m_nLeft, wl);
        pThis->m_nRight = max(pThis->m_nRight, wr);
    }

    pThis->m_pDSCB->Unlock(pBuf1, dwBuf1, pBuf2, dwBuf2);

    pThis->m_dwLastPosition = (pThis->m_dwLastPosition + dwLockBytes) % pThis->m_dwBufferSize;

    // Draw our new info to the window.
    if(pThis->m_bTheme == FALSE)
    {
        if(pThis->m_nLeft > 32768)
        {
            int a = 0;
        }
        pThis->m_ProgressBarL.SetPos(pThis->m_nLeft);
        pThis->m_ProgressBarR.SetPos(pThis->m_nRight);
    }
    else
    {
        InvalidateRect(pThis->m_hWnd, NULL, FALSE);
    }

    return;
}


LRESULT CALLBACK CLevelMeter::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CLevelMeter* pThis = (CLevelMeter*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(uMsg)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            pThis->Draw(ps.hdc);
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_CREATE:
        {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            pThis = (CLevelMeter*)pcs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void CLevelMeter::Draw(HDC dc)
{
    int nLeds = 0;
    int nSizeOfOneChannel = GetHeight()/2;

    if(m_bTheme == FALSE)
    {
        return;
    }

    // Draw the background.
    m_off.Blt(m_dc, 0, 0);

    /*
        Top half of the ON image is the LEFT channel.
        Let's figure out how many LEDs are involved in this.
        We have to scale it from 0 to METER_COUNT
               n             (X)
           ----------  = -----------
           MAX_SAMPLE    METER_COUNT
    */

    nLeds = MulDiv(m_nLeft, m_Theme.nLEDCount, MAX_SAMPLE);
    m_on.Blt(m_dc, 0, 0, 0, 0, m_Theme.nStartX+(nLeds*m_Theme.nStepX), nSizeOfOneChannel);

    nLeds = MulDiv(m_nRight, m_Theme.nLEDCount, MAX_SAMPLE);
    m_on.Blt(m_dc, 0, nSizeOfOneChannel, 0, nSizeOfOneChannel,
        m_Theme.nStartX+(nLeds*m_Theme.nStepX), nSizeOfOneChannel);

    BitBlt(dc, 0, 0, GetWidth(), GetHeight(), m_dc, 0, 0, SRCCOPY);

    return;
}


/*
    Counts the number of similar characters starting at the beginning of the
    strings, case-insensitive.  For instance:
    ccwcsicnt("an", "ANNIE");
    would return 2;
*/
int ccwcsicnt(PCWSTR wsz1, PCWSTR wsz2)
{
    int i = 0;
    WCHAR w1 = wsz1[0];
    WCHAR w2 = wsz2[0];

    while(w1 && w2)
    {
        if(ChrCmpIW(w1, w2))
        {
            // They're different.
            break;
        }

        // Advance to the next thingamabobber
        i++;
        w1 = wsz1[i];
        w2 = wsz2[i];
    }

    return i;
}


BOOL CALLBACK CLevelMeter::DSEnumCallback(LPGUID lpGuid, 
                                          PCWSTR wszDesc, PCWSTR wszModule, PVOID pUser)
{
    CLevelMeter* pThis = (CLevelMeter*)pUser;
    int nMatch = ccwcsicnt(wszDesc, pThis->m_strDevice);

    if((nMatch == wcslen(wszDesc)) || (nMatch == pThis->m_strDevice.len()))
    {
        pThis->m_iClosest = nMatch;
        pThis->m_bMatch = TRUE;

        if(lpGuid)
        {
            memcpy(&pThis->m_Device, lpGuid, sizeof(GUID));
        }
        else
        {
            memset(&pThis->m_Device, 0, sizeof(GUID));
        }
    }

    return TRUE;
}


HRESULT CLevelMeter::Size()
{
    if(m_bTheme == TRUE)
    {
        return CCControl::Size();
    }

    // Size up this control
    CCControl::Size();

    // Now we'll size our child progress bar controls to fit.
    RECT rc;
    GetClientRect(m_hWnd, &rc);
    int nHeight = (rc.bottom - rc.top) / 2;

    MoveWindow(m_ProgressBarL, rc.left, rc.top, rc.right, nHeight, TRUE);
    MoveWindow(m_ProgressBarR, rc.left, rc.top+nHeight, rc.right, nHeight*2, TRUE);

    return S_OK;
}


void CLevelMeter::SetDefaultSize(int x, int y)
{
    m_nDefaultHeight = y;
    m_nDefaultWidth = x;
}


