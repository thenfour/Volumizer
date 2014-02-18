

#pragma once


#include <windows.h>
#include "global.h"
#include "CCControl.h"


class CCEXPORT CCStatic : public CCControl
{
public:
    HRESULT Create(PCWSTR wsz, HWND hParent, HINSTANCE hInstance, 
        RECT& prect, RECT& orect);
};

