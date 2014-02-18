// MixerLine.cpp : Implementation of CMixerLine


#include "stdafx.h"
#include "MixerLib.h"
#include "MixerLine.h"
#include "MixerDestination.h"
#include "Mixer.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerLine
HRESULT CMixerLine::FinalConstruct()
{
    CComObject<CMixerControls>::CreateInstance(&m_pControls);
    m_pControls->AddRef();
    return S_OK;
}


void CMixerLine::FinalRelease()
{
    m_hMixer = 0;

    m_pControls->Release();
    m_pControls = 0;
    return;
}


void CMixerLine::Init(HMIXER hMixer, DWORD dwDestIndex, DWORD dwLineIndex, CMixerDestination* pOwner)
{
    m_hMixer = hMixer;
    m_pOwner = pOwner;
    m_dwDestID = dwDestIndex;
    m_dwLineID = dwLineIndex;
    m_bInitialized = FALSE;
}


HRESULT CMixerLine::EnsureInitialized()
{
    if(m_bInitialized == TRUE) return S_OK;

    CCollectionNode<CMixerControl>* pNewControl = 0;
    UINT i = 0;

    // Initialize ourself.
    memset(&m_ml, 0, sizeof(m_ml));
    m_ml.cbStruct = sizeof(m_ml);
    m_ml.dwSource = m_dwLineID;
    m_ml.dwDestination = m_dwDestID;

    if(MMSYSERR_NOERROR != mixerGetLineInfo((HMIXEROBJ)m_hMixer, &m_ml, MIXER_GETLINEINFOF_SOURCE))
    {
        return MIX_E_MIXERERROR;
    }

    if((m_Type = WinToMix_Line(m_ml.dwComponentType)) == MIXL_INVALID)
    {
        m_Type = MIXL_UNDEFINED;
    }

    // Initialize all our child controls.
    // Since you can't get single control info without the DWORD ID,
    // We get all the information right here and just pass it to the
    // child control objects - so they don't have to do any work
    // really.
    MIXERLINECONTROLS mlc = {0};
    MIXERCONTROL* pmc = 0;

    // Initialize our MIXERCONTROL stuff
    size_t nBytes = sizeof(MIXERCONTROL) * m_ml.cControls;
    pmc = (MIXERCONTROL*)malloc(nBytes);
    memset(pmc, 0, nBytes);

    // Initialize the MIXERLINECONTROLS stuff.
    mlc.cbStruct = sizeof(mlc);
    mlc.pamxctrl = pmc;
    mlc.cbmxctrl = sizeof(MIXERCONTROL);
    mlc.dwLineID = m_ml.dwLineID;
    mlc.cControls = m_ml.cControls;

    // Initialize our own stuff
    if(MMSYSERR_NOERROR != mixerGetLineControls((HMIXEROBJ)m_hMixer, &mlc, MIXER_GETLINECONTROLSF_ALL))
    {
        return MIX_E_MIXERERROR;
    }

    for(i=0;i<m_ml.cControls;i++)
    {
        pNewControl = m_pControls->_NewItem();
        pNewControl->pThis->Init(m_hMixer, &pmc[i], &m_ml, m_pOwner, this);
    }

    free(pmc);
    pmc = 0;

    m_bInitialized = TRUE;

    return S_OK;
}


STDMETHODIMP CMixerLine::get_name(BSTR *pVal)
{
    HRESULT hr = 0;

    if(!pVal) return E_POINTER;

    if(FAILED(hr = EnsureInitialized()))
    {
        *pVal = 0;
        return hr;
    }

    *pVal = T2BSTR(m_ml.szName);

    return S_OK;
}


STDMETHODIMP CMixerLine::get_controls(IMixerControls **pVal)
{
    HRESULT hr = 0;
    if(!pVal) return E_POINTER;
    *pVal = 0;

    if(FAILED(hr = EnsureInitialized()))
    {
        *pVal = 0;
        return hr;
    }

    return m_pControls->QueryInterface(IID_IMixerControls, (void**)pVal);
}


STDMETHODIMP CMixerLine::EnumControls(IEnumMixerControls **ppVal)
{
    HRESULT hr = 0;
    if(!ppVal) return E_POINTER;
    *ppVal = 0;

    if(FAILED(hr = EnsureInitialized()))
    {
        return hr;
    }

    return CreateEnum<IEnumMixerControls,
                      &IID_IEnumMixerControls,
                      IMixerControl, 
                      &IID_IMixerControl, 
                      CMixerControl>
                      (ppVal, m_pControls->_GetList());
}


STDMETHODIMP CMixerLine::get_control_count(long *pVal)
{
    HRESULT hr = 0;

    if(!pVal) return E_POINTER;

    if(FAILED(hr = EnsureInitialized()))
    {
        *pVal = 0;
        return hr;
    }

    *pVal = m_pControls->_GetList()->Count();

	return S_OK;
}



STDMETHODIMP CMixerLine::GetControl(MIX_CONTROL control, IMixerControl **pVal)
{
    HRESULT hr = 0;
    if(!pVal) return E_POINTER;

    *pVal = 0;

    if(FAILED(hr = EnsureInitialized()))
    {
        *pVal = 0;
        return hr;
    }

    CComObject<CMixerControl>* pMatch = GetControl(control);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixerControl, (void**)pVal);
    }

	return MIX_E_NOTFOUND;
}


CComObject<CMixerControl>* CMixerLine::GetControlByID(DWORD id)
{
    return m_pControls->GetControlByID(id);
}


BOOL CMixerLine::IsMatch(MIX_LINE line)
{
    HRESULT hr = 0;

    if(FAILED(hr = EnsureInitialized())) return hr;

    if(m_Type == line) return TRUE;
    return FALSE;
}


CComObject<CMixerControl>* CMixerLine::GetControl(MIX_CONTROL control)
{
    HRESULT hr = 0;

    if(FAILED(hr = EnsureInitialized())) return 0;

    return m_pControls->FindMatch(control);
}


STDMETHODIMP CMixerLine::get_type(MIX_LINE *pVal)
{
    HRESULT hr = 0;

    if(!pVal) return E_POINTER;
    if(FAILED(hr = EnsureInitialized())) return hr;

    *pVal = m_Type;

	return S_OK;
}


DWORD CMixerLine::GetLineID()
{
    HRESULT hr = 0;

    if(FAILED(hr = EnsureInitialized())) return hr;

    return m_ml.dwLineID;
}


STDMETHODIMP CMixerLine::get_owner(IMixerDestination **pVal)
{
    HRESULT hr = 0;

    if(!pVal) return E_POINTER;

    *pVal = 0;

    if(FAILED(hr = EnsureInitialized()))
    {
        return hr;
    }

    return m_pOwner->_InternalQueryInterface(IID_IMixerDestination, (void**)pVal);
}


STDMETHODIMP CMixerLine::get_channels(long *pVal)
{
    HRESULT hr = 0;
    if(!pVal) return E_POINTER;
    if(FAILED(hr = EnsureInitialized())) return hr;

    *pVal = m_ml.cChannels;

	return S_OK;
}

STDMETHODIMP CMixerLine::get_lineid(unsigned long *pVal)
{
    HRESULT hr = 0;
    if(!pVal) return E_POINTER;
    if(FAILED(hr = EnsureInitialized())) return hr;

    *pVal = m_ml.dwLineID;

	return S_OK;
}

STDMETHODIMP CMixerLine::get_short_name(BSTR *pVal)
{
    HRESULT hr = 0;
    if(!pVal) return E_POINTER;
    if(FAILED(hr = EnsureInitialized())) return hr;

    *pVal = T2BSTR(m_ml.szShortName);

	return S_OK;
}


STDMETHODIMP CMixerLine::get_mute(BOOL *pVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUTE);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_mute(pVal);
}


STDMETHODIMP CMixerLine::put_mute(BOOL newVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUTE);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_mute(newVal);
}


STDMETHODIMP CMixerLine::get_balance(unsigned long *pVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_VOLUME);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_balance(pVal);
}


STDMETHODIMP CMixerLine::put_balance(unsigned long newVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_VOLUME);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_balance(newVal);
}


STDMETHODIMP CMixerLine::get_volume(unsigned long *pVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_VOLUME);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_volume(pVal);
}


STDMETHODIMP CMixerLine::put_volume(unsigned long newVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_VOLUME);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_volume(newVal);
}


STDMETHODIMP CMixerLine::get_mux_type(MIX_LINE *pVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUX);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_mux_type(pVal);
}


STDMETHODIMP CMixerLine::put_mux_type(MIX_LINE newVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUX);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_mux_type(newVal);
}


STDMETHODIMP CMixerLine::get_mux_source(IMixerLine* *pVal)
{
    if(!pVal) return E_POINTER;
    *pVal = 0;
    CComObject<CMixerControl>* p = GetControl(MIXC_MUX);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_mux_source(pVal);
}


STDMETHODIMP CMixerLine::put_mux_source(IMixerLine* newVal)
{
    if(!newVal) return E_POINTER;
    CComObject<CMixerControl>* p = GetControl(MIXC_MUX);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_mux_source(newVal);
}


STDMETHODIMP CMixerLine::RefreshLine()
{
    CCollectionNode<CMixerControl>* pc = m_pControls->_GetList()->m_pRoot;

    while(pc)
    {
        pc->pThis->Refresh();
        pc = pc->pNext;
    }

	return S_OK;
}

STDMETHODIMP CMixerLine::GetControlByID(unsigned long ulId, IMixerControl **pVal)
{
    HRESULT hr = 0;
    if(!pVal) return E_POINTER;
    if(FAILED(hr = EnsureInitialized())) return hr;

    CComObject<CMixerControl>* pMatch = m_pControls->GetControlByID(ulId);

    if(!pMatch) return MIX_E_NOTFOUND;

    return pMatch->QueryInterface(IID_IMixerControl, (void**)pVal);
}


HRESULT CMixerLine::SaveLine(XMLDoc* pDoc, XMLEl* pParent)
{
    HRESULT hr = 0;
    XMLEl* pThis = 0;
    if(FAILED(hr = EnsureInitialized())) return hr;

    if(FAILED(hr = XMLFindLine(pDoc, pParent,
        m_ml.dwLineID, CCString(m_ml.szName), m_Type, &pThis, TRUE)))
    {
        return hr;
    }

    hr = m_pControls->SaveControls(pDoc, pThis);

    SAFE_RELEASE(pThis);

    return hr;
}


HRESULT CMixerLine::GetNode(XMLDoc* pDoc, XMLEl* pLibrary, XMLEl** p, BOOL bCreate)
{
    return XMLFindLine(pDoc, pLibrary,
        m_pOwner->m_pOwner->m_uID, CCString(m_pOwner->m_pOwner->m_mc.szPname),
        m_pOwner->m_ml.dwLineID, CCString(m_pOwner->m_ml.szName), m_pOwner->m_Type,
        m_ml.dwLineID, CCString(m_ml.szName), m_Type, p, bCreate);
}


STDMETHODIMP CMixerLine::Save(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    XMLEl* pParent = 0;
    HRESULT hr;

    if(FAILED(hr = EnsureInitialized())) return hr;

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    // Get the destination node.
    if(FAILED(hr = m_pOwner->GetNode(pDoc, pLibrary, &pParent, TRUE)))
    {
        SAFE_RELEASE(pLibrary);
        XMLClose(&pDoc);
        return hr;
    }

    if(FAILED(hr = SaveLine(pDoc, pParent)))
    {
        SAFE_RELEASE(pLibrary);
        SAFE_RELEASE(pParent);
        XMLClose(&pDoc);
        return hr;
    }

    SAFE_RELEASE(pLibrary);
    SAFE_RELEASE(pParent);

    hr = XMLCommit(pDoc, v);
    XMLClose(&pDoc);

    return hr;
}


HRESULT CMixerLine::LoadLine(XMLEl* pLibrary)
{
    HRESULT hr = 0;

    if(FAILED(hr = EnsureInitialized())) return hr;

    // Load up the destinations.
    if(FAILED(m_pControls->LoadControls(pLibrary)))
    {
        hr = MIX_E_XMLERR;
    }

    return hr;
}


STDMETHODIMP CMixerLine::Load(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    HRESULT hr = 0;

    if(FAILED(hr = EnsureInitialized())) return hr;

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    // Load ourself up.
    hr = LoadLine(pLibrary);

    SAFE_RELEASE(pLibrary);
    XMLClose(&pDoc);

	return hr;
}


STDMETHODIMP CMixerLine::get_fade(unsigned long *pVal)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}


STDMETHODIMP CMixerLine::put_fade(unsigned long newVal)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}


