

// Mixers.cpp : Implementation of CMixers
#include "stdafx.h"
#include "MixerLib.h"
#include "Mixers.h"


/////////////////////////////////////////////////////////////////////////////
// CMixers
HRESULT CMixers::FinalConstruct()
{
    return S_OK;
}


void CMixers::FinalRelease()
{
    _ReleaseCollection();
}


STDMETHODIMP CMixers::get_Item(VARIANT i, IMixer** pVal)
{
    return _get_Item_Index(i, pVal);
}


STDMETHODIMP CMixers::get__NewEnum(IUnknown** pVal)
{
    return _get__NewEnum(pVal);
}


STDMETHODIMP CMixers::get_Count(long *pVal)
{
    return _get_Count(pVal);
}


/*
    Given the document and library nodes, save all the mixers underneath it.
*/
HRESULT CMixers::SaveMixers(IXMLDOMDocument* pDoc, IXMLDOMElement* pLibrary)
{
    CCollectionNode<CMixer>* pCurrent = m_List.m_pRoot;
    HRESULT hr;

    while(pCurrent)
    {
        if(FAILED(hr = pCurrent->pThis->SaveMixer(pDoc, pLibrary)))
        {
            return hr;
        }

        pCurrent = pCurrent->pNext;
    }

    return S_OK;
}


HRESULT CMixers::LoadMixers(XMLEl* pLibrary)
{
    CCollectionNode<CMixer>* pCurrent = m_List.m_pRoot;

    while(pCurrent)
    {
        pCurrent->pThis->LoadMixer(pLibrary);
        pCurrent = pCurrent->pNext;
    }

    return S_OK;
}
