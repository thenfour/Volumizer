// MixerLines.cpp : Implementation of CMixerLines
#include "stdafx.h"
#include "MixerLib.h"
#include "MixerLines.h"

/////////////////////////////////////////////////////////////////////////////
// CMixerLines
HRESULT CMixerLines::FinalConstruct()
{
    return S_OK;
}


void CMixerLines::FinalRelease()
{
    _ReleaseCollection();
}


STDMETHODIMP CMixerLines::get_Item(VARIANT i, IMixerLine** pVal)
{
    return _get_Item_Index(i, pVal);
}


STDMETHODIMP CMixerLines::get__NewEnum(IUnknown** pVal)
{
    return _get__NewEnum(pVal);
}


STDMETHODIMP CMixerLines::get_Count(long *pVal)
{
    return _get_Count(pVal);
}


/*
    In order to find a destination of a particular type,
    we go down the list and see if anyone matches this.
*/
CComObject<CMixerLine>* CMixerLines::FindMatch(MIX_LINE line)
{
    CCollectionNode<CMixerLine>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        if(pCurrent->pThis->IsMatch(line))
        {
            return pCurrent->pThis;
        }

        pCurrent = pCurrent->pNext;
    }

    // No matches found.
    return 0;
}


CComObject<CMixerLine>* CMixerLines::GetLineByID(DWORD dwID)
{
    CCollectionNode<CMixerLine>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        if(pCurrent->pThis->GetLineID() == dwID)
        {
            return pCurrent->pThis;
        }

        pCurrent = pCurrent->pNext;
    }

    // No matches found.
    return 0;
}


CComObject<CMixerControl>* CMixerLines::GetControlByID(DWORD id)
{
    CCollectionNode<CMixerLine>* pCurrent = m_List.m_pRoot;
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


HRESULT CMixerLines::SaveLines(XMLDoc* pDoc, XMLEl* pDest)
{
    CCollectionNode<CMixerLine>* pCurrent = m_List.m_pRoot;
    HRESULT hr;

    while(pCurrent)
    {
        if(FAILED(hr = pCurrent->pThis->SaveLine(pDoc, pDest)))
        {
            return hr;
        }
        if(FAILED(hr = pCurrent->pThis->SaveLine(pDoc, pDest)))
        {
            return hr;
        }

        pCurrent = pCurrent->pNext;
    }

    return S_OK;
}


HRESULT CMixerLines::LoadLines(XMLEl* pLibrary)
{
    CCollectionNode<CMixerLine>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        pCurrent->pThis->LoadLine(pLibrary);
        pCurrent = pCurrent->pNext;
    }

    return S_OK;
}
