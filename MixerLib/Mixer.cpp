// Mixer.cpp : Implementation of CMixer
#include "stdafx.h"
#include "MixerLib.h"
#include "Mixer.h"
#include "MixerLibrary.h"


extern HINSTANCE g_hInstance;


/////////////////////////////////////////////////////////////////////////////
// CMixer


HRESULT CMixer::FinalConstruct()
{
    CComObject<CMixerDestinations>::CreateInstance(&m_pDestinations);
    m_pDestinations->AddRef();

    return S_OK;
}


void CMixer::FinalRelease()
{
    mixerClose(m_hMixer);
    m_hMixer = 0;

    DestroyWindow(m_hNotification);
    m_hNotification = 0;

    m_pDestinations->Release();
    m_pDestinations = 0;
}


void CMixer::Init(UINT uMixID, class CMixerLibrary* pOwner)
{
    m_pOwner = pOwner;
    m_uID = uMixID;
    m_bInitialized = FALSE;

    // Create our notification window.
    WNDCLASSEX wcx = {0};
    wcx.cbSize = sizeof(wcx);
    wcx.hInstance = g_hInstance;
    wcx.lpfnWndProc = CMixer::WndProc;
    wcx.lpszClassName = MIXER_WNDCLASS;
    RegisterClassEx(&wcx);

    m_hNotification = CreateWindowEx(0, MIXER_WNDCLASS,
        L"MixerLib Notification Window", WS_POPUP,
        0, 0, 0, 0, (HWND)0, (HMENU)0, g_hInstance, this);

    return;
}


LRESULT CALLBACK CMixer::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CMixer* pThis = (CMixer*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch(uMsg)
    {
    case MM_MIXM_CONTROL_CHANGE:
        {
            DWORD dwControlID = (DWORD)lParam;
            CComObject<CMixerControl>* pMatch = 0;
            IMixerControl* pControl = 0;

            pMatch = pThis->m_pDestinations->GetControlByID(dwControlID);

            if(pMatch)
            {
                pMatch->QueryInterface(IID_IMixerControl, (void**)&pControl);

                if(pControl)
                {
                    pThis->Fire_OnControlChange(pControl);
                    pControl->Release();
                }
            }

            return 0;
        }
    case MM_MIXM_LINE_CHANGE:
        {
            DWORD dwLineID = (DWORD)lParam;
            IMixerLine* pLine = 0;

            if(SUCCEEDED(pThis->m_pDestinations->GetLineByID(dwLineID, &pLine)))
            {
                pThis->Fire_OnLineChange(pLine);
                pLine->Release();
            }

            return 0;
        }
    case WM_CLOSE:
        {
            DestroyWindow(hWnd);
            pThis->m_hNotification = 0;
            return 0;
        }
    case WM_CREATE:
        {
            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
            pThis = (CMixer*)pcs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


STDMETHODIMP CMixer::get_name(BSTR *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = T2BSTR(m_mc.szPname);

	return S_OK;
}


STDMETHODIMP CMixer::get_destinations(IMixerDestinations **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = 0;
    return m_pDestinations->QueryInterface(IID_IMixerDestinations, (void**)pVal);
}


STDMETHODIMP CMixer::EnumDestinations(IEnumMixerDestinations **ppVal)
{
    if(!ppVal) return E_POINTER;
    EnsureInitialized();
    *ppVal = 0;

    return CreateEnum<IEnumMixerDestinations,
                      &IID_IEnumMixerDestinations,
                      IMixerDestination, 
                      &IID_IMixerDestination, 
                      CMixerDestination>
                      (ppVal, m_pDestinations->_GetList());
}


STDMETHODIMP CMixer::get_destination_count(long *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = m_pDestinations->_GetList()->Count();

	return S_OK;
}



void CMixer::EnsureInitialized()
{
    if(m_bInitialized == TRUE) return;

    unsigned long i = 0;
    CCollectionNode<CMixerDestination>* pNew = 0;

    if(MMSYSERR_NOERROR != mixerOpen(&m_hMixer, m_uID, (DWORD)m_hNotification, 0, CALLBACK_WINDOW))
    {
        return;
    }

    // Successfully opened the mixer object.  We need to get 
    // mixer information first.
    memset(&m_mc, 0, sizeof(m_mc));

    if(MMSYSERR_NOERROR != mixerGetDevCaps(m_uID, &m_mc, sizeof(m_mc)))
    {
        mixerClose(m_hMixer);
        m_hMixer = 0;
        return;
    }

    // Now let's hax up all our child destinations.
    for(i=0;i<m_mc.cDestinations;i++)
    {
        pNew = m_pDestinations->_NewItem();
        pNew->pThis->Init(m_hMixer, i, this);
    }

    m_bInitialized = TRUE;

    return;
}


STDMETHODIMP CMixer::GetDestination(MIX_DESTINATION dest, IMixerDestination **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = 0;

    CComObject<CMixerDestination>* pMatch = GetDestination(dest);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixerDestination, (void**)pVal);
    }

	return MIX_E_NOTFOUND;
}


STDMETHODIMP CMixer::GetLine(MIX_DESTINATION dest, MIX_LINE line, IMixerLine **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = 0;

    CComObject<CMixerLine>* pMatch = GetLine(dest, line);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixerLine, (void**)pVal);
    }

    if(line == MIXL_SELF)
    {
        CComObject<CMixerDestination>* pDest = GetDestination(dest);

        if(pDest)
        {
            return pDest->QueryInterface(IID_IMixerLine, (void**)pVal);
        }
    }

	return MIX_E_NOTFOUND;
}


STDMETHODIMP CMixer::GetControl(MIX_DESTINATION dest, MIX_LINE line, MIX_CONTROL control, IMixerControl **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();
    *pVal = 0;

    CComObject<CMixerControl>* pMatch = GetControl(dest, line, control);

    if(pMatch)
    {
        return pMatch->QueryInterface(IID_IMixerControl, (void**)pVal);
    }

	return MIX_E_NOTFOUND;
}


CComObject<CMixerDestination>* CMixer::GetDestination(MIX_DESTINATION dest)
{
    EnsureInitialized();
    return m_pDestinations->FindMatch(dest);
}


/*
    Note that this doesn't support MIXL_SELF.
*/
CComObject<CMixerLine>* CMixer::GetLine(MIX_DESTINATION dest, MIX_LINE line)
{
    EnsureInitialized();
    CComObject<CMixerDestination>* pDestination = GetDestination(dest);
    if(pDestination)
    {
        return pDestination->GetLine(line);
    }
    return 0;
}


/*
    Note that this *DOES* support MIXL_SELF.
*/
CComObject<CMixerControl>* CMixer::GetControl(MIX_DESTINATION dest, MIX_LINE line, MIX_CONTROL control)
{
    EnsureInitialized();
    CComObject<CMixerDestination>* pDestination = GetDestination(dest);
    if(pDestination)
    {
        return pDestination->GetLineControl(line, control);
    }
    return 0;
}


STDMETHODIMP CMixer::get_manufacturer(short *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = m_mc.wMid;

	return S_OK;
}


STDMETHODIMP CMixer::get_product(short *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = m_mc.wPid;

	return S_OK;
}


STDMETHODIMP CMixer::get_version_major(short *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = (m_mc.vDriverVersion & 0xFF00) >> 8;

	return S_OK;
}


STDMETHODIMP CMixer::get_version_minor(short *pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    *pVal = m_mc.vDriverVersion & 0x00FF;

	return S_OK;
}


STDMETHODIMP CMixer::get_owner(IMixerLibrary **pVal)
{
    if(!pVal) return E_POINTER;
    *pVal = 0;
    return m_pOwner->_InternalQueryInterface(IID_IMixerLibrary, (void**)pVal);
}


STDMETHODIMP CMixer::Refresh()
{
    EnsureInitialized();
    CCollectionNode<CMixerDestination>* p = m_pDestinations->_GetList()->m_pRoot;

    while(p)
    {
        p->pThis->Refresh();
        p = p->pNext;
    }

	return S_OK;
}


STDMETHODIMP CMixer::get_mixerid(DWORD *pVal)
{
    if(!pVal) return E_POINTER;
    *pVal = m_uID;
	return S_OK;
}


STDMETHODIMP CMixer::GetDestinationByID(unsigned long ulId, IMixerDestination **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    CComObject<CMixerDestination>* pMatch = m_pDestinations->GetDestinationByID(ulId);
    if(!pMatch) return MIX_E_NOTFOUND;

    return pMatch->QueryInterface(IID_IMixerDestination, (void**)pVal);
}


STDMETHODIMP CMixer::GetLineByID(unsigned long ulId, IMixerLine **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    return m_pDestinations->GetLineByID(ulId, pVal);
}


STDMETHODIMP CMixer::GetControlByID(unsigned long ulId, IMixerControl **pVal)
{
    if(!pVal) return E_POINTER;
    EnsureInitialized();

    CComObject<CMixerControl>* pMatch = m_pDestinations->GetControlByID(ulId);
    if(!pMatch) return MIX_E_NOTFOUND;

    return pMatch->QueryInterface(IID_IMixerControl, (void**)pVal);
}


HRESULT CMixer::GetNode(XMLDoc* pDoc, XMLEl* pLibrary, XMLEl** p, BOOL bCreate)
{
    return XMLFindMixer(pDoc, pLibrary, m_uID, CCString(m_mc.szPname), p, bCreate);
}


HRESULT CMixer::SaveMixer(IXMLDOMDocument* pDoc, IXMLDOMElement* pLibrary)
{
    XMLEl* pMixer = 0;
    HRESULT hr;

    EnsureInitialized();

    if(FAILED(hr = GetNode(pDoc, pLibrary, &pMixer, TRUE)))
    {
        // This means we could find the mixer AND when we tried to create it,
        // it failed.
        return hr;
    }

    hr = m_pDestinations->SaveDestinations(pDoc, pMixer);

    SAFE_RELEASE(pMixer);

    return hr;
}


STDMETHODIMP CMixer::Save(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    HRESULT hr;

    EnsureInitialized();

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    if(FAILED(hr = SaveMixer(pDoc, pLibrary)))
    {
        XMLClose(&pDoc);
        return hr;
    }

    hr = XMLCommit(pDoc, v);
    XMLClose(&pDoc);

    return hr;
}


HRESULT CMixer::LoadMixer(XMLEl* pLibrary)
{
    HRESULT hr;

    EnsureInitialized();

    // Load up the destinations.
    hr = m_pDestinations->LoadDestinations(pLibrary);

    return hr;
}


STDMETHODIMP CMixer::Load(VARIANT v)
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
    hr = LoadMixer(pLibrary);

    SAFE_RELEASE(pLibrary);
    XMLClose(&pDoc);

	return hr;
}


