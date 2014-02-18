

#include "stdafx.h"
#include "WaveCapture.h"
#include "traceerrorsys.h"
#include <process.h>



WaveCapture::WaveCapture()
{
    this->pdsb = NULL;
    this->pdsc = NULL;

    this->nPassesLeft = 0;

    this->hEvents[0] = NULL;
    this->hEvents[1] = NULL;
    this->hEvents[2] = NULL;
    this->hEvents[3] = NULL;

    this->hThread = NULL;
    this->pBuffer = NULL;
    this->nBufferSize = 0;

    this->pProc = 0;
    this->nInterval = 0;
    this->pUser = 0;
    this->dwLastPosition = 0;
}


WaveCapture::~WaveCapture()
{
    CCString ErrText;
    this->Uninitialize();
}


/*
    nInterval is in SECONDS.  The buffer we create is 3 times the interval,
    so we make three notifications that will be placed at every interval.

    pProc will be called at approximately the interval specified.
*/
HRESULT WaveCapture::Initialize(int nDevice, WAVEFORMATEX* pFormat, WAVECAPTUREPROC pProc, PVOID pUser, int nInterval)
{
    DSCCAPS dsc;
    DSCBUFFERDESC1 dscbDesc;
    HRESULT hr;
    DSBPOSITIONNOTIFY NotifyPositions[3];
    IDirectSoundNotify* pdsn;

    this->Uninitialize();

    this->pProc = pProc;
    this->pUser = pUser;
    this->nInterval = nInterval;

    // Validation.
    if(pFormat->wFormatTag != WAVE_FORMAT_PCM)
    {
        return E_FAIL;
    }

    // Copy the wave format for our own purposes.
    memcpy(&this->Format, pFormat, sizeof(WAVEFORMATEX));

    m_iDevice = nDevice;
    memset(&m_Device, 0, sizeof(GUID));
    DirectSoundCaptureEnumerate(WaveCapture::DSEnumCallback, this);

    // Create DirectSoundCapture object.
    if(FAILED(hr = DirectSoundCaptureCreate(&m_Device, &this->pdsc, NULL)))
    {
        return E_FAIL;
    }

    /*
        Here is where we should check the capabilities of the sound card against
        the format that was passed in.
    */
    dsc.dwSize = sizeof(DSCCAPS);
    if(FAILED(hr = this->pdsc->GetCaps(&dsc)))
    {
        SAFE_RELEASE(this->pdsc);
        return E_FAIL;
    }

    /*
        Create the capture buffer.
    */
    dscbDesc.dwSize = sizeof(dscbDesc);
    dscbDesc.dwFlags = DSCBCAPS_WAVEMAPPED;
    dscbDesc.dwBufferBytes = (pFormat->nAvgBytesPerSec * nInterval) * 3;
    dscbDesc.dwReserved = 0;
    dscbDesc.lpwfxFormat = &this->Format;

    if(FAILED(hr = this->pdsc->CreateCaptureBuffer((DSCBUFFERDESC*)&dscbDesc, &this->pdsb, NULL)))
    {
        SAFE_RELEASE(this->pdsc);
        return E_FAIL;
    }

    /*
        Create the notifications
    */
    this->hEvents[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
    this->hEvents[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
    this->hEvents[2] = CreateEvent(NULL, FALSE, FALSE, NULL);
    this->hEvents[3] = CreateEvent(NULL, FALSE, FALSE, NULL);

    NotifyPositions[0].dwOffset = 0;
    NotifyPositions[0].hEventNotify = this->hEvents[0];

    NotifyPositions[1].dwOffset = (this->Format.nAvgBytesPerSec * nInterval);
    NotifyPositions[1].hEventNotify = this->hEvents[1];

    NotifyPositions[2].dwOffset = (this->Format.nAvgBytesPerSec * nInterval) * 2;
    NotifyPositions[2].hEventNotify = this->hEvents[2];

    if(FAILED(hr = this->pdsb->QueryInterface(IID_IDirectSoundNotify, (PVOID*)&pdsn)))
    {
        SAFE_RELEASE(this->pdsb);
        SAFE_RELEASE(this->pdsc);
        return E_FAIL;
    }

    if(FAILED(hr = pdsn->SetNotificationPositions(3, NotifyPositions)))
    {
        SAFE_RELEASE(pdsn);
        SAFE_RELEASE(this->pdsb);
        SAFE_RELEASE(this->pdsc);
        return E_FAIL;
    }

    SAFE_RELEASE(pdsn);

    /*
        Create our own buffer so when we pass data to pProc, the data is ALWAYS
        contiguous.
    */
    this->nBufferSize = (pFormat->nAvgBytesPerSec * nInterval) * 3;
    this->pBuffer = (PBYTE)malloc(this->nBufferSize);

    /*
        Initialize our own information.
    */
    this->dwLastPosition = 0;
    this->nPassesLeft = 1;

    /*
        Now create our recording thread so life can continue.
    */
    UINT dwThreadId;
	this->hThread = (HANDLE)_beginthreadex(
        0, 0, WaveCapture::RecordingThread, this, 0, &dwThreadId);

    return S_OK;
}


HRESULT WaveCapture::Uninitialize()
{
    if(this->pdsc == NULL) return S_OK;

    this->Stop();

    /*
        Signal to our thread that we should quit and wait for it.
    */
    if(this->hThread)
    {
        SetEvent(this->hEvents[3]);
        WaitForSingleObject(this->hThread, INFINITE);
    }

    this->hThread = NULL;

    // Release everything
    if(this->pdsb)
    {
        this->pdsb->Release();
        this->pdsb = NULL;
    }

    if(this->pdsc)
    {
        this->pdsc->Release();
        this->pdsc = NULL;
    }

    if(this->pBuffer)
    {
        free(this->pBuffer);
        this->pBuffer = 0;
    }

    // Close the handles
    if(this->hEvents[0])
    {
        CloseHandle(this->hEvents[0]);
    }
    if(this->hEvents[1])
    {
        CloseHandle(this->hEvents[1]);
    }
    if(this->hEvents[2])
    {
        CloseHandle(this->hEvents[2]);
    }
    if(this->hEvents[3])
    {
        CloseHandle(this->hEvents[3]);
    }

    return S_OK;
}


HRESULT WaveCapture::Start()
{
    HRESULT hr;

    if(this->pdsb == NULL) return E_FAIL;

    if(FAILED(hr = this->pdsb->Start(DSCBSTART_LOOPING)))
    {
        return E_FAIL;
    }

    return S_OK;
}


HRESULT WaveCapture::Stop()
{
    HRESULT hr;

    // We'll return a Success if its an invalid object.
    if(this->pdsb == NULL) return S_OK;

    if(FAILED(hr = this->pdsb->Stop()))
    {
        return E_FAIL;
    }

    /*
        Now we're most likely not exactly on a notification point in the buffer,
        so we'll "flush" the buffers.
    */
    this->Flush();

    return S_OK;
}


/*
    This is the recording thread.  It's created when we initialize everything.
    It's responsibility is to monitor the events and make sure that they are handled.

    This means either calling pProc with valid data for the first 3 events, or
    exiting when hEvents[3] is signaled.
*/
UINT _stdcall WaveCapture::RecordingThread(PVOID pThisx)
{
    CoInitialize(0);

    WaveCapture* pThis = (WaveCapture*)pThisx;
    DWORD dw;

    while(1)
    {
        dw = WaitForMultipleObjects(4, pThis->hEvents, FALSE, INFINITE) - WAIT_OBJECT_0;

        switch(dw)
        {
        case 0:
        case 1:
        case 2:
            /*
                We have entered a new notification place in the buffer.
                We need to initialize our own buffer with contiguous data and call the
                user proc.
            */
            if(pThis->nPassesLeft == 0)
            {
                pThis->Flush();
            }
            else
            {
                pThis->nPassesLeft --;
            }
            break;
        case 3:
            // We need to exit!
            CoUninitialize();
            return 0;
        }
    }

    // No man's land:
    return 0;
}


/*
    Writes any NEW FRESH data to pProc.  It's possible that pProc won't be called
    in this function (for instance, if capturing is STOPPED and Flush() was called
    more than once in a row.)
*/
HRESULT WaveCapture::Flush()
{
    DWORD dwLockBytes;
    DWORD dwBufferPos;
    HRESULT hr;
    PBYTE pAudio1, pAudio2;
    DWORD dwAudio1, dwAudio2;
    
    if(this->pdsb == NULL)
    {
        return E_FAIL;
    }

    if(FAILED(hr = this->pdsb->GetCurrentPosition(NULL, &dwBufferPos)))
    {
        return E_FAIL;
    }

    // First determine how many bytes we need to lock.  We may not need to read anything.
    if(dwBufferPos >= this->dwLastPosition)
    {
        dwLockBytes = dwBufferPos - this->dwLastPosition;
    }
    else
    {
        dwLockBytes = dwBufferPos + (this->nBufferSize - this->dwLastPosition);
    }

    if(dwLockBytes == 0)
    {
        return S_OK;
    }

    // Now lock the buffer
    if(FAILED(hr = this->pdsb->Lock(this->dwLastPosition, dwLockBytes,
        (PVOID*)&pAudio1, &dwAudio1, (PVOID*)&pAudio2, &dwAudio2, 0)))
    {
        return E_FAIL;
    }

    // Let's copy data into our own buffer.
    memcpy(this->pBuffer, pAudio1, dwAudio1);
    memcpy(this->pBuffer + dwAudio1, pAudio2, dwAudio2);

    this->pdsb->Unlock(pAudio1, dwAudio1, pAudio2, dwAudio2);

    // Call the user function
    this->pProc(this->pBuffer, dwLockBytes, this->pUser);

    // And update our own cursor.
    this->dwLastPosition = (this->dwLastPosition + dwLockBytes) % this->nBufferSize;

    return S_OK;
}


BOOL CALLBACK WaveCapture::DSEnumCallback(LPGUID lpGuid, PCWSTR, PCWSTR, PVOID pUser)
{
    WaveCapture* pThis = (WaveCapture*)pUser;
    if(pThis->m_iDevice == 0)
    {
        memcpy(&pThis->m_Device, lpGuid, sizeof(GUID));
        return FALSE;
    }
    pThis->m_iDevice --;
    return TRUE;
}



