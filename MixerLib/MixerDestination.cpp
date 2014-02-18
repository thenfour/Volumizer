// MixerDestination.cpp : Implementation of CMixerDestination
#include "stdafx.h"
#include "MixerLib.h"
#include "MixerDestination.h"
#include "Mixer.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerDestination
HRESULT CMixerDestination::FinalConstruct()
{
    CComObject<CMixerLines>::CreateInstance(&m_pLines);
    m_pLines->AddRef();

    CComObject<CMixerControls>::CreateInstance(&m_pControls);
    m_pControls->AddRef();

    return S_OK;
}


void CMixerDestination::FinalRelease()
{
    m_pLines->Release();
    m_pLines = 0;

    m_pControls->Release();
    m_pControls = 0;

    // This is freed by CMixer, so just set it to zero.
    m_hMixer = 0;
}


void CMixerDestination::Init(HMIXER hMixer, unsigned int uDestID, class CMixer* pOwner)
{
    m_pOwner = pOwner;
    m_hMixer = hMixer;
    m_uDestID = uDestID;
    m_bInitialized = FALSE;
}


void CMixerDestination::EnsureInitialized()
{
    if(m_bInitialized == TRUE) return;

    CCollectionNode<CMixerLine>* pNewLine = 0;
    CCollectionNode<CMixerControl>* pNewControl = 0;
    unsigned int i = 0;

    // Initialize our mixerline struct
    memset(&m_ml, 0, sizeof(m_ml));
    m_ml.cbStruct = sizeof(m_ml);
    m_ml.dwDestination = m_uDestID;

    // Grab info about ourselves
    if(MMSYSERR_NOERROR != mixerGetLineInfo((HMIXEROBJ)m_hMixer, &m_ml, MIXER_GETLINEINFOF_DESTINATION))
    {
        return;
    }

    if((m_Type = WinToMix_Destination(m_ml.dwComponentType)) == MIXD_INVALID)
    {
        m_Type = MIXD_UNDEFINED;
    }

    {
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
        if(MMSYSERR_NOERROR == mixerGetLineControls((HMIXEROBJ)m_hMixer, &mlc, MIXER_GETLINECONTROLSF_ALL))
        {
            for(i=0;i<m_ml.cControls;i++)
            {
                pNewControl = m_pControls->_NewItem();
                pNewControl->pThis->Init(m_hMixer, &pmc[i], &m_ml, this, 0);
            }

            SAFE_FREE(pmc);
        }
    }

    // Initialize all our child lines.
    for(i=0;i<m_ml.cConnections;i++)
    {
        pNewLine = m_pLines->_NewItem();
        pNewLine->pThis->Init(m_hMixer, m_uDestID, i, this);
    }

    m_bInitialized = TRUE;

    return;
}


STDMETHODIMP CMixerDestination::get_name(BSTR *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = T2BSTR(m_ml.szName);

    return S_OK;
}


STDMETHODIMP CMixerDestination::get_lines(IMixerLines **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    return m_pLines->QueryInterface(IID_IMixerLines, (void**)pVal);
}


STDMETHODIMP CMixerDestination::get_controls(IMixerControls **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    return m_pControls->QueryInterface(IID_IMixerControls, (void**)pVal);
}


STDMETHODIMP CMixerDestination::EnumLines(IEnumMixerLines **ppVal)
{
    if(!ppVal) return E_POINTER;
    EnsureInitialized();

    return CreateEnum<IEnumMixerLines,
                      &IID_IEnumMixerLines,
                      IMixerLine, 
                      &IID_IMixerLine, 
                      CMixerLine>
                      (ppVal, m_pLines->_GetList());
}


STDMETHODIMP CMixerDestination::EnumControls(IEnumMixerControls **ppVal)
{
    if(!ppVal) return E_POINTER;
    EnsureInitialized();

    return CreateEnum<IEnumMixerControls,
                      &IID_IEnumMixerControls,
                      IMixerControl, 
                      &IID_IMixerControl, 
                      CMixerControl>
                      (ppVal, m_pControls->_GetList());
}


STDMETHODIMP CMixerDestination::get_line_count(long *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = m_pLines->_GetList()->Count();

    return S_OK;
}


STDMETHODIMP CMixerDestination::get_control_count(long *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = m_pControls->_GetList()->Count();

    return S_OK;
}


STDMETHODIMP CMixerDestination::GetLine(MIX_LINE line, IMixerLine **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    if(line == MIXL_SELF)
    {
        return this->_InternalQueryInterface(IID_IMixerLine, (void**)pVal);
    }

    CComObject<CMixerLine>* pMatch = GetLine(line);

    if(pMatch)
    {
        return pMatch->_InternalQueryInterface(IID_IMixerLine, (void**)pVal);
    }

	return MIX_E_NOTFOUND;
}


STDMETHODIMP CMixerDestination::GetLineControl(MIX_LINE line, MIX_CONTROL control, IMixerControl **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    CComObject<CMixerControl>* pMatch = GetLineControl(line, control);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixerControl, (void**)pVal);
    }

	return MIX_E_NOTFOUND;
}


STDMETHODIMP CMixerDestination::GetControl(MIX_CONTROL control, IMixerControl **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    CComObject<CMixerControl>* pMatch = GetControl(control);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixerControl, (void**)pVal);
    }

	return MIX_E_NOTFOUND;
}


BOOL CMixerDestination::IsMatch(MIX_DESTINATION dest)
{
    EnsureInitialized();
    if(dest == m_Type) return TRUE;
    return FALSE;
}


CComObject<CMixerControl>* CMixerDestination::GetLineControl(MIX_LINE line, MIX_CONTROL control)
{
    EnsureInitialized();
    CComObject<CMixerLine>* pLine = m_pLines->FindMatch(line);
    if(pLine)
    {
        return pLine->GetControl(control);
    }

    if(line == MIXL_SELF)
    {
        return GetControl(control);
    }

    return 0;
}


/*
    Note that this doesn't support MIXL_SELF because it can't
    deal with outer objects.
*/
CComObject<CMixerLine>* CMixerDestination::GetLine(MIX_LINE line)
{
    EnsureInitialized();
    return m_pLines->FindMatch(line);
}


CComObject<CMixerControl>* CMixerDestination::GetControl(MIX_CONTROL control)
{
    EnsureInitialized();
    return m_pControls->FindMatch(control);
}


STDMETHODIMP CMixerDestination::get_type_destination(MIX_DESTINATION *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = m_Type;

	return S_OK;
}


STDMETHODIMP CMixerDestination::get_type(MIX_LINE *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = MIXL_SELF;

	return S_OK;
}


CComObject<CMixerLine>* CMixerDestination::GetLineByID(DWORD dwLineID)
{
    return m_pLines->GetLineByID(dwLineID);
}


STDMETHODIMP CMixerDestination::get_owner(IMixerDestination **pVal)
{
    if(!pVal) return E_POINTER;
    return _InternalQueryInterface(IID_IMixerDestination, (void**)pVal);
}


STDMETHODIMP CMixerDestination::get_owner(IMixer **pVal)
{
    if(!pVal) return E_POINTER;
    return m_pOwner->_InternalQueryInterface(IID_IMixer, (void**)pVal);
}


STDMETHODIMP CMixerDestination::get_channels(long *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = m_ml.cChannels;
	return S_OK;
}


STDMETHODIMP CMixerDestination::get_lineid(unsigned long *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = m_ml.dwLineID;
	return S_OK;
}


STDMETHODIMP CMixerDestination::get_short_name(BSTR *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = T2BSTR(m_ml.szShortName);
	return S_OK;
}


STDMETHODIMP CMixerDestination::get_mute(BOOL *pVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUTE);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_mute(pVal);
}


STDMETHODIMP CMixerDestination::put_mute(BOOL newVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUTE);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_mute(newVal);
}


STDMETHODIMP CMixerDestination::get_balance(unsigned long *pVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_VOLUME);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_balance(pVal);
}


STDMETHODIMP CMixerDestination::put_balance(unsigned long newVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_VOLUME);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_balance(newVal);
}


STDMETHODIMP CMixerDestination::get_volume(unsigned long *pVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_VOLUME);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_volume(pVal);
}


STDMETHODIMP CMixerDestination::put_volume(unsigned long newVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_VOLUME);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_volume(newVal);
}


STDMETHODIMP CMixerDestination::get_mux_type(MIX_LINE *pVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUX);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_mux_type(pVal);
}


STDMETHODIMP CMixerDestination::put_mux_type(MIX_LINE newVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUX);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_mux_type(newVal);
}


STDMETHODIMP CMixerDestination::get_mux_source(IMixerLine* *pVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUX);
    if(!p) return MIX_E_NOTFOUND;
    return p->get_mux_source(pVal);
}


STDMETHODIMP CMixerDestination::put_mux_source(IMixerLine* newVal)
{
    CComObject<CMixerControl>* p = GetControl(MIXC_MUX);
    if(!p) return MIX_E_NOTFOUND;
    return p->put_mux_source(newVal);
}


STDMETHODIMP CMixerDestination::Refresh()
{
    CCollectionNode<CMixerLine>* p = m_pLines->_GetList()->m_pRoot;

    while(p)
    {
        p->pThis->RefreshLine();
        p = p->pNext;
    }

    RefreshLine();

	return S_OK;
}

STDMETHODIMP CMixerDestination::RefreshLine()
{
    CCollectionNode<CMixerControl>* p = m_pControls->_GetList()->m_pRoot;

    while(p)
    {
        p->pThis->Refresh();
        p = p->pNext;
    }

	return S_OK;
}


DWORD CMixerDestination::GetLineID()
{
    EnsureInitialized();
    return m_ml.dwLineID;
}


CComObject<CMixerControl>* CMixerDestination::GetControlByID(DWORD id)
{
    CComObject<CMixerControl>* p = 0;

    p = m_pControls->GetControlByID(id);

    if(p) return p;

    // No control?  Let's check our lines.
    p = m_pLines->GetControlByID(id);

    if(p) return p;

    return 0;
}



STDMETHODIMP CMixerDestination::GetLineByID(unsigned long ulId, IMixerLine **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    if(ulId == m_ml.dwLineID)
    {
        return _InternalQueryInterface(IID_IMixerLine, (void**)pVal);
    }

    CComObject<CMixerLine>* pMatch = m_pLines->GetLineByID(ulId);

    if(!pMatch) return MIX_E_NOTFOUND;

    return pMatch->QueryInterface(IID_IMixerLine, (void**)pVal);
}

STDMETHODIMP CMixerDestination::GetLineControlByID(unsigned long ulId, IMixerControl **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    CComObject<CMixerControl>* pMatch = m_pLines->GetControlByID(ulId);

    if(!pMatch) return GetControlByID(ulId, pVal);

    return pMatch->QueryInterface(IID_IMixerControl, (void**)pVal);
}

STDMETHODIMP CMixerDestination::GetControlByID(unsigned long ulId, IMixerControl **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    CComObject<CMixerControl>* pMatch = m_pControls->GetControlByID(ulId);

    if(!pMatch) return MIX_E_NOTFOUND;

    return pMatch->QueryInterface(IID_IMixerControl, (void**)pVal);
}


HRESULT CMixerDestination::SaveDestination(XMLDoc* pDoc, XMLEl* pParent)
{
    EnsureInitialized();
    XMLEl* pThis = 0;
    HRESULT hr;

    if(FAILED(hr = XMLFindDestination(pDoc, pParent, m_ml.dwLineID, CCString(m_ml.szName), m_Type, &pThis, TRUE)))
    {
        return hr;
    }

    if(FAILED(hr = m_pControls->SaveControls(pDoc, pThis)))
    {
        SAFE_RELEASE(pThis);
        return hr;
    }

    hr = m_pLines->SaveLines(pDoc, pThis);

    SAFE_RELEASE(pThis);

    return hr;
}


HRESULT CMixerDestination::SaveLine(XMLDoc* pDoc, XMLEl* pParent)
{
    EnsureInitialized();
    XMLEl* pThis = 0;
    HRESULT hr;

    if(FAILED(hr = XMLFindDestination(pDoc, pParent, m_ml.dwLineID, CCString(m_ml.szName), m_Type, &pThis, TRUE)))
    {
        return hr;
    }

    hr = m_pControls->SaveControls(pDoc, pThis);

    SAFE_RELEASE(pThis);

    return hr;
}


STDMETHODIMP CMixerDestination::Save(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    XMLEl* pMixer = 0;
    HRESULT hr;

    EnsureInitialized();

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    // Get the mixer node.
    if(FAILED(hr = m_pOwner->GetNode(pDoc, pLibrary, &pMixer, TRUE)))
    {
        XMLClose(&pDoc);
        return hr;
    }

    if(FAILED(hr = SaveLine(pDoc, pMixer)))
    {
        SAFE_RELEASE(pMixer);
        XMLClose(&pDoc);
        return hr;
    }

    SAFE_RELEASE(pMixer);

    hr = XMLCommit(pDoc, v);
    XMLClose(&pDoc);

    return hr;
}


STDMETHODIMP CMixerDestination::SaveDestination(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    XMLEl* pMixer = 0;
    HRESULT hr;

    EnsureInitialized();

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    // Get the mixer node.
    if(FAILED(hr = m_pOwner->GetNode(pDoc, pLibrary, &pMixer, TRUE)))
    {
        SAFE_RELEASE(pLibrary);
        XMLClose(&pDoc);
        return hr;
    }

    if(FAILED(hr = SaveDestination(pDoc, pMixer)))
    {
        SAFE_RELEASE(pLibrary);
        SAFE_RELEASE(pMixer);
        XMLClose(&pDoc);
        return hr;
    }

    SAFE_RELEASE(pMixer);
    SAFE_RELEASE(pLibrary);

    hr = XMLCommit(pDoc, v);
    XMLClose(&pDoc);

    return hr;
}


HRESULT CMixerDestination::GetNode(XMLDoc* pDoc, XMLEl* pLibrary, XMLEl** p, BOOL bCreate)
{
    return XMLFindDestination(pDoc, pLibrary, 
        m_pOwner->m_uID, CCString(m_pOwner->m_mc.szPname),
        m_ml.dwLineID, CCString(m_ml.szName), m_Type, p, bCreate);
}


/*
    Attempt to load up all the controls / lines below the given LIBRARY node.
*/
HRESULT CMixerDestination::LoadDestination(XMLEl* pLibrary)
{
    HRESULT hr = S_OK;

    EnsureInitialized();

    // Load up the destinations.
    if(FAILED(m_pControls->LoadControls(pLibrary)))
    {
        hr = MIX_E_XMLERR;
    }

    if(FAILED(m_pLines->LoadLines(pLibrary)))
    {
        hr = MIX_E_XMLERR;
    }

    return hr;
}


HRESULT CMixerDestination::LoadLine(XMLEl* pLibrary)
{
    HRESULT hr;

    EnsureInitialized();

    // Load up the destinations.
    if(FAILED(m_pControls->LoadControls(pLibrary)))
    {
        hr = MIX_E_XMLERR;
    }

    return hr;
}


STDMETHODIMP CMixerDestination::Load(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    HRESULT hr;

    EnsureInitialized();

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


STDMETHODIMP CMixerDestination::LoadDestination(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    HRESULT hr;

    EnsureInitialized();

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    // Load ourself up.
    hr = LoadDestination(pLibrary);

    SAFE_RELEASE(pLibrary);
    XMLClose(&pDoc);

	return hr;
}


STDMETHODIMP CMixerDestination::get_fade(unsigned long *pVal)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}


STDMETHODIMP CMixerDestination::put_fade(unsigned long newVal)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}


