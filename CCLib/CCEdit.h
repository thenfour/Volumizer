

#pragma once


#include <windows.h>
#include "global.h"
#include "CCControl.h"


//////////////////////////////////////////////////////////////////////////////
class CCEXPORT CCEditBox : public CCControl
{
public:
	CCEditBox();
	~CCEditBox();

	HRESULT Create(HWND hParent, HINSTANCE, RECT& prect, RECT& orect);
	HRESULT CreateMultiline(HWND hParent, HINSTANCE, RECT& prect, RECT& orect);

    HRESULT Append(PCWSTR);

    HRESULT SetReadOnly(BOOL);

private:

};


