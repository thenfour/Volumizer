// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__45A70DC0_81C6_4D0C_8DFF_006B98C92C5D__INCLUDED_)
#define AFX_STDAFX_H__45A70DC0_81C6_4D0C_8DFF_006B98C92C5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>

// TODO: reference additional headers your program requires here
#include <windows.h>
#include "Global.h"
#include "CCString.h"
#include "CCControl.h"
#include "../ccres/resource.h"


extern HMODULE g_hRes;



#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "dsound.lib")


extern HINSTANCE g_hInstance;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__45A70DC0_81C6_4D0C_8DFF_006B98C92C5D__INCLUDED_)
