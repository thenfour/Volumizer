// MixerDestinations.cpp : Implementation of CMixerDestinations
#include "stdafx.h"
#include "MixerLib.h"
#include "MixerDestinations.h"

/////////////////////////////////////////////////////////////////////////////
// CMixerDestinations
HRESULT CMixerDestinations::FinalConstruct()
{
    return S_OK;
}


void CMixerDestinations::FinalRelease()
{
    _ReleaseCollection();
}


STDMETHODIMP CMixerDestinations::get_Item(VARIANT i, IMixerDestination** pVal)
{
    return _get_Item_Index(i, pVal);
}


STDMETHODIMP CMixerDestinations::get__NewEnum(IUnknown** pVal)
{
    return _get__NewEnum(pVal);
}


STDMETHODIMP CMixerDestinations::get_Count(long *pVal)
{
    return _get_Count(pVal);
}


/*
    In order to find a destination of a particular type,
    we go down the list and see if anyone matches this.
*/
CComObject<CMixerDestination>* CMixerDestinations::FindMatch(MIX_DESTINATION dest)
{
    CCollectionNode<CMixerDestination>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        if(pCurrent->pThis->IsMatch(dest))
        {
            return pCurrent->pThis;
        }

        pCurrent = pCurrent->pNext;
    }

    // No matches found.
    return 0;
}




HRESULT CMixerDestinations::GetLineByID(DWORD dwID, IMixerLine** pVal)
{
    CCollectionNode<CMixerDestination>* pCurrent = m_List.m_pRoot;
    CComObject<CMixerLine>* pMatch = 0;

    *pVal = 0;

    while(pCurrent)
    {
        pMatch = pCurrent->pThis->GetLineByID(dwID);

        if(pMatch)
        {
            return pMatch->QueryInterface(IID_IMixerLine, (void**)pVal);
        }
        else if(pCurrent->pThis->GetLineID() == dwID)
        {
            // The match is a destination!
            return pCurrent->pThis->QueryInterface(IID_IMixerLine, (void**)pVal);
        }

        pCurrent = pCurrent->pNext;
    }

    // No matches found.
    return E_NOINTERFACE;
}


CComObject<CMixerControl>* CMixerDestinations::GetControlByID(DWORD id)
{
    CCollectionNode<CMixerDestination>* pCurrent = m_List.m_pRoot;
    CComObject<CMixerControl>* pMatch = 0;

    while(pCurrent)
    {
        pMatch = pCurrent->pThis->GetControlByID(id);

        if(pMatch)
        {
            return pMatch;
        }

        pCurrent = pCurrent->pNext;
    }

    // No matches found.
    return 0;
}


CComObject<CMixerDestination>* CMixerDestinations::GetDestinationByID(DWORD id)
{
    CCollectionNode<CMixerDestination>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        if(pCurrent->pThis->GetLineID() == id)
        {
            return pCurrent->pThis;
        }

        pCurrent = pCurrent->pNext;
    }

    // No matches found.
    return 0;
}


HRESULT CMixerDestinations::SaveDestinations(XMLDoc* pDoc, XMLEl* pMixer)
{
    CCollectionNode<CMixerDestination>* pCurrent = m_List.m_pRoot;
    HRESULT hr;

    while(pCurrent)
    {
        if(FAILED(hr = pCurrent->pThis->SaveDestination(pDoc, pMixer)))
        {
            return hr;
        }

        pCurrent = pCurrent->pNext;
    }

    return S_OK;
}


HRESULT CMixerDestinations::LoadDestinations(XMLEl* pLibrary)
{
    CCollectionNode<CMixerDestination>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        pCurrent->pThis->LoadDestination(pLibrary);
        pCurrent = pCurrent->pNext;
    }

    return S_OK;
}



