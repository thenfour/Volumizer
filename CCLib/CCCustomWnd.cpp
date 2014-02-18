

#include "stdafx.h"
#include "CCCustomWnd.h"
#include <stdio.h>


CCCustomWnd::~CCCustomWnd()
{
}


CCCustomWnd::CCCustomWnd()
{
	m_wszClass[0] = 0;
}


void CCCustomWnd::Destroy()
{
	DestroyWindow(m_hWnd);

	UnregisterClass(m_wszClass, m_hInstance);
	m_wszClass[0] = 0;
	m_hWnd = 0;
}


HRESULT CCCustomWnd::Create(PCWSTR wszName, HWND hParent, WNDPROC WndProc, 
                            HINSTANCE hInstance, RECT prect, RECT orect, 
                            DWORD dwStyle, PVOID lparam, int iIcon)
{
	WNDCLASSEX wc;

    m_hInstance  = hInstance;

	CopyRect(&m_orect, &orect);
	CopyRect(&m_prect, &prect);

    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(wc);
 	swprintf(m_wszClass, L"CCCustomWnd 0x%X", this->GetId());
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if(iIcon) wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(iIcon));
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WndProc == 0) ? DefWindowProc : WndProc;
	wc.lpszClassName = m_wszClass;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if(0 == RegisterClassEx(&wc))
    {
        //CCString s;
        //s.FormatW(L"Failed to register custom window class.  GetLastError = %d", GetLastError());
        //MessageBox(0, s, 0, MB_OK | MB_ICONEXCLAMATION);

        //return E_FAIL;
    }

	m_hWnd = CreateWindow(m_wszClass, wszName, dwStyle,
		0, 0, 1, 1, hParent, (HMENU)0, hInstance, lparam);

    SetFont();
    Size();

    return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CCCustomWnd::SetIcon(HICON hIcon)
{
	SetClassLong(m_hWnd, GCL_HICON, (LONG)hIcon);
	return S_OK;
}


