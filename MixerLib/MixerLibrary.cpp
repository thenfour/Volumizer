// MixerLibrary.cpp : Implementation of CMixerLibrary
#include "stdafx.h"
#include "MixerLib.h"
#include "MixerLibrary.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerLibrary
HRESULT CMixerLibrary::FinalConstruct()
{
    CComObject<CMixers>::CreateInstance(&m_pMixers);
    m_pMixers->AddRef();

    return S_OK;
}


void CMixerLibrary::FinalRelease()
{
    m_pMixers->Release();
    m_pMixers = 0;
}


STDMETHODIMP CMixerLibrary::get_mixers(IMixers **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = 0;

    return m_pMixers->QueryInterface(IID_IMixers, (void**)pVal);
}


STDMETHODIMP CMixerLibrary::EnumMixers(IEnumMixers **ppVal)
{
    if(!ppVal) return E_POINTER;
    EnsureInitialized();
    *ppVal = 0;

    return CreateEnum<IEnumMixers,
                      &IID_IEnumMixers,
                      IMixer, 
                      &IID_IMixer, 
                      CMixer>
                      (ppVal, m_pMixers->_GetList());
}


STDMETHODIMP CMixerLibrary::get_mixer_count(long *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = m_pMixers->_GetList()->Count();
	return S_OK;
}


void CMixerLibrary::EnsureInitialized()
{
    if(m_bInitialized == TRUE) return;

    CCollectionNode<CMixer>* pNew = 0;
    int nDevs = 0;
    int i = 0;

    nDevs = mixerGetNumDevs();

    for(i=0;i<nDevs;i++)
    {
        pNew = m_pMixers->_NewItem();
        pNew->pThis->Init(i, this);
    }

    m_bInitialized = TRUE;

    return;
}


STDMETHODIMP CMixerLibrary::GetMixer(long id, IMixer **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = 0;

    CComObject<CMixer>* pMatch = GetMixer(id);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixer, (void**)pVal);
    }

	return MIX_E_NOTFOUND;
}


STDMETHODIMP CMixerLibrary::GetDestination(long idMixer, MIX_DESTINATION Dest, IMixerDestination **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = 0;

    CComObject<CMixerDestination>* pMatch = GetDestination(idMixer, Dest);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixerDestination, (void**)pVal);
    }

	return MIX_E_NOTFOUND;
}


STDMETHODIMP CMixerLibrary::GetLine(long idMixer, MIX_DESTINATION dest, MIX_LINE line, IMixerLine **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = 0;

    CComObject<CMixerLine>* pMatch = GetLine(idMixer, dest, line);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixerLine, (void**)pVal);
    }

    // There was no match, let's see if they're asking for the MIXL_SELF
    // thingy
    if(line == MIXL_SELF)
    {
        CComObject<CMixerDestination>* pMatch = GetDestination(idMixer, dest);

        if(pMatch)
        {
            return pMatch->QueryInterface(IID_IMixerLine, (void**)pVal);
        }
    }

	return MIX_E_NOTFOUND;
}


STDMETHODIMP CMixerLibrary::GetControl(long idMixer, MIX_DESTINATION dest, MIX_LINE line, MIX_CONTROL control, IMixerControl **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = 0;

    CComObject<CMixerControl>* pMatch = GetControl(idMixer, dest, line, control);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixerControl, (void**)pVal);
    }

	return MIX_E_NOTFOUND;
}


CComObject<CMixer>* CMixerLibrary::GetMixer(long id)
{
    EnsureInitialized();
    CCollectionNode<CMixer>* pFound = m_pMixers->_GetList()->Item(id);
    if(!pFound) return 0;
    return pFound->pThis;
}


CComObject<CMixerDestination>* CMixerLibrary::GetDestination(long id, MIX_DESTINATION dest)
{
    EnsureInitialized();
    CComObject<CMixer>* pMixer = GetMixer(id);
    if(pMixer)
    {
        return pMixer->GetDestination(dest);
    }
    return 0;
}


CComObject<CMixerLine>* CMixerLibrary::GetLine(long id, MIX_DESTINATION dest, MIX_LINE line)
{
    EnsureInitialized();
    CComObject<CMixer>* pMixer = GetMixer(id);
    if(pMixer)
    {
        return pMixer->GetLine(dest, line);
    }
    return 0;
}


CComObject<CMixerControl>* CMixerLibrary::GetControl(long id, MIX_DESTINATION dest, MIX_LINE line, MIX_CONTROL control)
{
    EnsureInitialized();
    CComObject<CMixer>* pMixer = GetMixer(id);
    if(pMixer)
    {
        return pMixer->GetControl(dest, line, control);
    }
    return 0;
}


STDMETHODIMP CMixerLibrary::Refresh()
{
    CCollectionNode<CMixer>* p = m_pMixers->_GetList()->m_pRoot;

    while(p)
    {
        p->pThis->Refresh();
        p = p->pNext;
    }

	return S_OK;
}


/*
    This function will save the entire library to an XML file.
    The file specified may exist, but it's not required.  If
    it exists, then it's just modified to reflect the changes.

    The value of v may be a IUnknown that supports:
    VT_IUNKNOWN   IStream
    VT_BSTR
*/
STDMETHODIMP CMixerLibrary::Save(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    HRESULT hr;

    EnsureInitialized();

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    if(FAILED(hr = m_pMixers->SaveMixers(pDoc, pLibrary)))
    {
        return hr;
    }

    hr = XMLCommit(pDoc, v);
    XMLClose(&pDoc);

    return hr;
}


STDMETHODIMP CMixerLibrary::Load(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    HRESULT hr;

    EnsureInitialized();

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    // SAve all the mixer objects.
    hr = m_pMixers->LoadMixers(pLibrary);

    SAFE_RELEASE(pLibrary);

    XMLClose(&pDoc);

	return hr;
}


