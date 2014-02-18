

#pragma once


class CCMDIChild;


class CCEXPORT CCMDIClient : public CCControl
{
    friend class CCMDIChild;
public:
    CCMDIClient();
    ~CCMDIClient();

    HRESULT Create(HWND hParent, HINSTANCE hInstance, RECT prect, RECT orect, WNDPROC ChildProc);
    HRESULT CreateChild(CCMDIChild** pOut, const TCHAR* tszTitle, long lParam, RECT prect, RECT orect);
    
private:

	TCHAR Class[MAX_PATH];

};


