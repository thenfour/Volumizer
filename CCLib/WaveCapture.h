

#pragma once


#define INITGUID
#include <Windows.h>
#include <dsound.h>
#include "global.h"
#include "CCString.h"


/*
    This is the callback function that will be called each time the capturer
    needs to give data.
*/
typedef HRESULT (CALLBACK* WAVECAPTUREPROC)(PBYTE pData, DWORD dwDataLen, PVOID pUser);


class CCEXPORT WaveCapture
{
public:
    WaveCapture();
    ~WaveCapture();

    HRESULT Initialize(int iDevice, WAVEFORMATEX* pFormat, WAVECAPTUREPROC pProc, PVOID pUser, int nInterval);
    HRESULT Uninitialize();
    HRESULT Start();
    HRESULT Stop();

    HRESULT Flush();// If there is more data, this will call the user proc.

private:

    static UINT _stdcall RecordingThread(PVOID pThis);

    static BOOL CALLBACK DSEnumCallback(LPGUID lpGuid, PCWSTR, PCWSTR, PVOID pUser);
    GUID m_Device;// The callback will fill in this GUID for the initialize() function to use.
    int m_iDevice;// index of the device to be gotten.  We decrement this and when it hits 0, we use the device.

    IDirectSoundCapture* pdsc;
    IDirectSoundCaptureBuffer* pdsb;

    /*
        hEvent[0] - Capture is at beginning of buffer
        hEvent[1] - Capture is at first interval
        hEvent[2] - Capture is at last interval
        hEvent[3] - Uninitialize and exit
    */
    HANDLE hEvents[4];
    HANDLE hThread;
    WAVEFORMATEX Format;

    /*
        When we pass audio from the DS buffer to the user-defined function,
        we have to pass in a complete buffer, so we'll allocate it to the maximum size.
    */
    int nPassesLeft;// How many times have we hit a notification - this gets reset by Initialize().
    DWORD dwLastPosition;// Offset, in bytes, of the DS Buffer where we last grabbed data.
    PBYTE pBuffer;
    int nBufferSize;

    WAVECAPTUREPROC pProc;
    PVOID           pUser;

    int nInterval;// In Seconds.
};

