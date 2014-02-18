

#pragma once


#include <windows.h>
#include "global.h"
#include "CCString.h"
#include "CCDebug.h"


/*
    This function will stick the error text in the buffer.

    Return value is the size of the buffer needed.  szBuf
    can be NULL if needed.
*/
void CCEXPORT TraceErrorSys(CCString* pBuf, HRESULT hr);

void CCEXPORT odssys(CCString Function, CCString Header, HRESULT hr);

