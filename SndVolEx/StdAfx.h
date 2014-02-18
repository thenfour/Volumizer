// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>


// TODO: reference additional headers your program requires here
extern HINSTANCE g_hInstance;
#include "..\\CCLib\\CCLib.h"
#include "..\\MixerLib\\MixerLib.h"
#include <tchar.h>
#include "Resource.h"
#include <commctrl.h>


enum SmallIcon_Type
{
    Image_Library = 0,
    Image_Mixer = 1,
    Image_Destination = 2,
    Image_Line = 3,
    Image_Control = 4
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
