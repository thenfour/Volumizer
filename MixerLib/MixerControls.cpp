// MixerControls.cpp : Implementation of CMixerControls
#include "stdafx.h"
#include "MixerLib.h"
#include "MixerControls.h"

/////////////////////////////////////////////////////////////////////////////
// CMixerControls
HRESULT CMixerControls::FinalConstruct()
{
    return S_OK;
}


void CMixerControls::FinalRelease()
{
    _ReleaseCollection();
}


STDMETHODIMP CMixerControls::get_Item(VARIANT i, IMixerControl** pVal)
{
    return _get_Item_Index(i, pVal);
}


STDMETHODIMP CMixerControls::get__NewEnum(IUnknown** pVal)
{
    return _get__NewEnum(pVal);
}


STDMETHODIMP CMixerControls::get_Count(long *pVal)
{
    return _get_Count(pVal);
}


/*
    In order to find a destination of a particular type,
    we go down the list and see if anyone matches this.
*/
CComObject<CMixerControl>* CMixerControls::FindMatch(MIX_CONTROL type)
{
    CCollectionNode<CMixerControl>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        if(pCurrent->pThis->IsMatch(type))
        {
            return pCurrent->pThis;
        }

        pCurrent = pCurrent->pNext;
    }

    // No matches found.
    return 0;
}


CComObject<CMixerControl>* CMixerControls::GetControlByID(DWORD id)
{
    CCollectionNode<CMixerControl>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        if(pCurrent->pThis->GetID() == id)
        {
            return pCurrent->pThis;
        }

        pCurrent = pCurrent->pNext;
    }

    // No matches found.
    return 0;
}


HRESULT CMixerControls::SaveControls(XMLDoc* pDoc, XMLEl* pLine)
{
    CCollectionNode<CMixerControl>* pCurrent = m_List.m_pRoot;
    HRESULT hr;

    while(pCurrent)
    {
        if(FAILED(hr = pCurrent->pThis->SaveControl(pDoc, pLine)))
        {
            return hr;
        }

        pCurrent = pCurrent->pNext;
    }

    return S_OK;
}


HRESULT CMixerControls::LoadControls(XMLEl* pLibrary)
{
    CCollectionNode<CMixerControl>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        pCurrent->pThis->LoadControl(pLibrary);
        pCurrent = pCurrent->pNext;
    }

    return S_OK;
}





