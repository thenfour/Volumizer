

#pragma once

#include <windows.h>
#include "global.h"

typedef unsigned __int64 CCUINT64;

void InitWaveFormatStruct(WAVEFORMATEX* pFormat, int nChannels, int nSamplesPerSec, int nBitsPerSample);

int GetDaysDifference(const FILETIME& something_in_the_past);

CCUINT64 FileTimeToInt64(const FILETIME& t);
void Int64ToFileTime(CCUINT64 t, FILETIME& out);
