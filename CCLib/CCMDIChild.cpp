

#include "stdafx.h"
#include "CCMDIChild.h"
#include <tchar.h>
#include "CCMDIClient.h"


/*
    Instantiate those statics.
*/
CRITICAL_SECTION CCMDIChild::m_csCreate;
long CCMDIChild::lParam = 0;
BOOL CCMDIChild::m_bInitialized = FALSE;
long CCMDIChild::m_lRefCt = 0;


CCMDIChild::CCMDIChild()
{
    /*
        Make sure the crit sec is initialized.
    */
    CCMDIChild::m_lRefCt ++;

    if(CCMDIChild::m_bInitialized == FALSE)
    {
        InitializeCriticalSection(&CCMDIChild::m_csCreate);
        CCMDIChild::m_bInitialized = TRUE;
    }
}


CCMDIChild::~CCMDIChild()
{
    CCMDIChild::m_lRefCt --;

    if(CCMDIChild::m_lRefCt == 0)
    {
        DeleteCriticalSection(&CCMDIChild::m_csCreate);
        CCMDIChild::m_bInitialized = FALSE;
    }
}


long CCMDIChild::GetParam()
{
    return CCMDIChild::lParam;
}


HRESULT CCMDIChild::Create(CCMDIClient* pParent, const TCHAR* tszTitle, long lParam, RECT prect, RECT orect)
{
    this->hParent = pParent->GethWnd();
    this->hInstance = pParent->hInstance;
    this->prect = prect;
    this->orect = orect;

    MDICREATESTRUCT mcs;

    mcs.szTitle = tszTitle;
    mcs.szClass = pParent->Class;
    mcs.hOwner  = this->hInstance;
    mcs.x = mcs.cx = CW_USEDEFAULT;
    mcs.y = mcs.cy = CW_USEDEFAULT;
    mcs.style = MDIS_ALLCHILDSTYLES;

    EnterCriticalSection(&CCMDIChild::m_csCreate);

    CCMDIChild::lParam = lParam;
    this->hWnd = (HWND)SendMessage(this->hParent, WM_MDICREATE, 0, (LONG)&mcs);

    LeaveCriticalSection(&CCMDIChild::m_csCreate);
    
    if(!this->hWnd)
    {
        return E_FAIL;
    }

    return S_OK;
}


