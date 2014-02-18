

#include "stdafx.h"
#include "utilities.h"


void InitWaveFormatStruct(WAVEFORMATEX* pFormat, int nChannels, int nSamplesPerSec, int nBitsPerSample)
{
    pFormat->cbSize = 0;
    pFormat->wFormatTag = WAVE_FORMAT_PCM;
    pFormat->nChannels = nChannels;
    pFormat->nSamplesPerSec = nSamplesPerSec;
    pFormat->wBitsPerSample = nBitsPerSample;
    pFormat->nBlockAlign = nChannels * nBitsPerSample / 8;
    pFormat->nAvgBytesPerSec = pFormat->nBlockAlign * nSamplesPerSec;
}




CCUINT64 FileTimeToInt64(const FILETIME& t)
{
    CCUINT64 r = t.dwHighDateTime;
    r <<= 32;
    r |= t.dwLowDateTime;
    return r;
}


void Int64ToFileTime(CCUINT64 t, FILETIME& out)
{
    CCUINT64 high = t;
    high >>= 32;
    CCUINT64 low = t;
    low &= 0xFFFFFFFF;

    out.dwHighDateTime = (DWORD)high;
    out.dwLowDateTime = (DWORD)low;
}


int GetDaysDifference(const FILETIME& something_in_the_past)
{
    bool bNegative = false;
    SYSTEMTIME stToday;
    FILETIME ftToday;
    CCUINT64 uiToday;
    CCUINT64 uiValue;
    CCUINT64 uiDifference;

    SYSTEMTIME stPast;
    FileTimeToSystemTime(&something_in_the_past, &stPast);

    GetLocalTime(&stToday);
    SystemTimeToFileTime(&stToday, &ftToday);
    uiToday = FileTimeToInt64(ftToday);
    uiValue = FileTimeToInt64(something_in_the_past);

    uiDifference = uiToday - uiValue;
    if((uiDifference > uiToday) || (uiDifference > uiValue))
    {
        // overflow
        bNegative = true;
        uiDifference = uiValue - uiToday;
    }

    // now we have the absolute value of the difference, in 100 nanosecond units.
    uiDifference /= 10000;// now it's in milliseconds.
    uiDifference /= 1000;// seconds
    uiDifference /= 60;// minutes
    uiDifference /= 60;// hours
    uiDifference /= 24;// days

    int r = (int)uiDifference;
    if(bNegative) r = -r;

    return r;
}

