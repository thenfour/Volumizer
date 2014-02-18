

#pragma once


#include <windows.h>
#include "global.h"
#include <commctrl.h>


// API!
int CCEXPORT GetWindowHeight(HWND hWnd);
int CCEXPORT GetWindowWidth(HWND hWnd);
int CCEXPORT SetWindowHeight(HWND hWnd, int n);
int CCEXPORT SetWindowWidth(HWND hWnd, int n);
int CCEXPORT ScreenToClient(HWND hWnd, RECT* prc);
HRESULT CCEXPORT SetWindowClientArea(HWND hWnd, int x, int y);// Sets the client area size.  If it could not be done, returns an error.
HRESULT CCEXPORT CenterWindow(HWND hWnd, HWND hParent);// hParent may be NULL to center to the desktop.


//////////////////////////////////////////////////////////////////////////////
class CCEXPORT CCControl
{
public:
	CCControl();
	~CCControl();

    operator HWND();
    operator UINT();// For the ID.

    virtual void Destroy();
    virtual BOOL IsWindow();

    virtual HRESULT TakeOver(HWND hWnd);

    /*
        Resizes the control based on the placement rects.
    */
	virtual HRESULT Size();
	virtual HRESULT GetPlacement(RECT* pprect, RECT* porect);
	virtual HRESULT SetPlacement(RECT* pprect, RECT* porect);

    /*
        Sizing() ensures that the window doesn't go out of bounds.

        case WM_SIZING:
	    	POINT p;
	    	p.x = 360;
	    	p.y = 344;
	    	return pThis->cWindow.Sizing(wParam, lParam, &p);
    */
    virtual HRESULT Sizing(WPARAM wParam, LPARAM lParam, LPPOINT pMin);

	virtual UINT GetId();
	virtual HWND GethWnd();
	virtual HWND GetParent();

	//virtual WNDPROC Subclass(PVOID pUser, WNDPROC NewProc);

    virtual HRESULT SetRedraw(BOOL);
	virtual HRESULT SetFont(PCTSTR, int);
    virtual HRESULT SetFont(HFONT hFont, BOOL bAutoFree);
    virtual HRESULT SetFont();// Sets it to the default gui font.

    virtual void SetText(PCWSTR wsz);
    virtual int GetText(PWSTR wsz, DWORD cchMax);// Returns the length returned.
    virtual int GetTextLength();

    virtual void Show(BOOL b);

    virtual void Invalidate();
    virtual void Invalidate(const RECT* rc);

    virtual void RemoveStyle(DWORD s);
    virtual void AddStyle(DWORD s);
    virtual void RemoveExStyle(DWORD s);
    virtual void AddExStyle(DWORD s);
    virtual DWORD GetStyle();
    virtual DWORD GetExStyle();
    virtual void SetStyle(DWORD dw);
    virtual void SetExStyle(DWORD dw);

    virtual void Enable(BOOL b);

#if(WINVER >= 0x0500) && (_WIN32_WINNT >= 0x0500)

    virtual void SetColorKey(COLORREF rgb);
    virtual void SetTransparency(BYTE b);

#endif

protected:

	static UINT NextId;

    // Control ID.
	UINT m_id;

	HFONT m_hFont;

	HINSTANCE m_hInstance;

	RECT m_orect;
	RECT m_prect;

	HWND m_hWnd;

	HRESULT ControlRectToRect(RECT*, RECT*, RECT*, RECT*);
    void _FreeFont();
};


