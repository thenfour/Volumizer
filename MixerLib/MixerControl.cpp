// MixerControl.cpp : Implementation of CMixerControl
#include "stdafx.h"
#include "MixerLib.h"
#include "MixerControl.h"
#include "utils.h"
#include "MixerLine.h"
#include "Mixer.h"
#include "MixerDestination.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerControl
HRESULT CMixerControl::FinalConstruct()
{
    return S_OK;
}


void CMixerControl::FinalRelease()
{
    m_hMixer = 0;

    /*
        Release our buffers.
    */
    if(m_pRaw)
    {
        free(m_pRaw);
        m_pRaw = 0;
    }
    if(m_pVariants)
    {
        free(m_pVariants);
        m_pVariants = 0;
    }
    if(m_pStrings)
    {
        free(m_pStrings);
        m_pStrings = 0;
    }
}


void CMixerControl::Init(HMIXER hMixer, MIXERCONTROL* pmc, MIXERLINE* pml, 
                         class CMixerDestination* pDest, class CMixerLine* pLine)
{
    m_hMixer = hMixer;

    m_pDest = pDest;
    m_pLine = pLine;

    memcpy(&m_mc, pmc, sizeof(MIXERCONTROL));

    memcpy(&m_ml, pml, sizeof(MIXERLINE));

    if((m_Type = WinToMix_Control(m_mc.dwControlType)) == MIXC_INVALID)
    {
        m_Type = MIXC_UNDEFINED;
    }

    m_DataType = WinToMix_DataType(m_mc.dwControlType);

    // First set m_nRawItems to the number of channels affected.
    // THen we will multiply it by number of items.
    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM)
    {
        m_nRawItems = 1;
    }
    else
    {
        m_nRawItems = m_ml.cChannels;
    }

    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE)
    {
        m_nRawItems *= m_mc.cMultipleItems;
    }

    // Now create our buffers.
    switch(m_DataType)
    {
    case MIXDT_CUSTOM:
        {
            m_pRaw = (BYTE*)malloc(m_mc.Metrics.cbCustomData);
            break;
        }
    case MIXDT_SIGNED:
        {
            m_pRaw = (BYTE*)malloc(m_nRawItems * sizeof(MIXERCONTROLDETAILS_SIGNED));
            m_pVariants = (VARIANT*)malloc(sizeof(VARIANT) * m_nRawItems);
            break;
        }
    case MIXDT_UNSIGNED:
        {
            m_pRaw = (BYTE*)malloc(m_nRawItems * sizeof(MIXERCONTROLDETAILS_UNSIGNED));
            m_pVariants = (VARIANT*)malloc(sizeof(VARIANT) * m_nRawItems);
            break;
        }
    case MIXDT_BOOLEAN:
        {
            m_pRaw = (BYTE*)malloc(m_nRawItems * sizeof(MIXERCONTROLDETAILS_BOOLEAN));
            m_pVariants = (VARIANT*)malloc(sizeof(VARIANT) * m_nRawItems);
            break;
        }
    default:
        {
            // this should never happen...
            //DebugBreak();
            break;
        }
    }

    /*
        Create the listtext buffer if it's valid.
    */
    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE)
    {
        m_pStrings = (MIXERCONTROLDETAILS_LISTTEXT*)malloc(sizeof(MIXERCONTROLDETAILS_LISTTEXT) * m_mc.cMultipleItems);
    }

    // And finally refresh the stuff to fill in all of our values.
    Refresh();

    return;
}


STDMETHODIMP CMixerControl::get_name(BSTR *pVal)
{
    if(!pVal) return E_POINTER;

    *pVal = T2BSTR(m_mc.szName);

    return S_OK;
}


BOOL CMixerControl::IsMatch(MIX_CONTROL type)
{
    if(m_Type == type) return TRUE;
    return FALSE;
}


STDMETHODIMP CMixerControl::get_type(MIX_CONTROL *pVal)
{
    if(!pVal) return E_POINTER;

    *pVal = m_Type;

	return S_OK;
}


STDMETHODIMP CMixerControl::get_uniform(BOOL *pVal)
{
    if(!pVal) return E_POINTER;

    *pVal = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM) ? TRUE : FALSE ;

	return S_OK;
}


STDMETHODIMP CMixerControl::get_multiple(long *pVal)
{
    if(!pVal) return E_POINTER;

    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE)
    {
        *pVal = m_mc.cMultipleItems;
    }
    else
    {
        *pVal = 1;
    }

	return S_OK;
}


STDMETHODIMP CMixerControl::get_channels(long *pVal)
{
    if(!pVal) return E_POINTER;

    *pVal = m_ml.cChannels;

	return S_OK;
}


STDMETHODIMP CMixerControl::get_datatype(MIX_DATATYPE *pVal)
{
    if(!pVal) return E_POINTER;

    *pVal = m_DataType;

	return S_OK;
}


STDMETHODIMP CMixerControl::get_custom_size(long *pVal)
{
    if(!pVal) return E_POINTER;

    if(m_mc.dwControlType == MIXERCONTROL_CONTROLTYPE_CUSTOM)
    {
        *pVal = m_mc.Metrics.cbCustomData;
    }
    else
    {
        *pVal = 0;
    }

	return S_OK;
}


STDMETHODIMP CMixerControl::get_min(VARIANT *pVal)
{
    if(!pVal) return E_POINTER;

    VariantInit(pVal);

    switch(m_DataType)
    {
    case MIXDT_SIGNED:
        pVal->vt = VT_INT;
        pVal->intVal = m_mc.Bounds.lMinimum;
        break;
    case MIXDT_UNSIGNED:
        pVal->vt = VT_UINT;
        pVal->uintVal = m_mc.Bounds.dwMinimum;
        break;
    default:
        memset(pVal, 0, sizeof(VARIANT));
        VariantClear(pVal);
        break;
    }

	return S_OK;
}


STDMETHODIMP CMixerControl::get_max(VARIANT *pVal)
{
    if(!pVal) return E_POINTER;

    VariantInit(pVal);

    switch(m_DataType)
    {
    case MIXDT_SIGNED:
        pVal->vt = VT_INT;
        pVal->intVal = m_mc.Bounds.lMaximum;
        break;
    case MIXDT_UNSIGNED:
        pVal->vt = VT_UINT;
        pVal->uintVal = m_mc.Bounds.dwMaximum;
        break;
    default:
        memset(pVal, 0, sizeof(VARIANT));
        VariantClear(pVal);
        break;
    }

	return S_OK;
}


STDMETHODIMP CMixerControl::get_steps(long *pVal)
{
    if(!pVal) return E_POINTER;

    switch(m_DataType)
    {
    case MIXDT_UNSIGNED:
    case MIXDT_SIGNED:
        *pVal = m_mc.Metrics.cSteps;
        break;
    default:
        *pVal = 0;
        break;
    }

	return S_OK;
}


/*
    The raw buffer is used for EVERY control.

    For custom controls
*/
void CMixerControl::_RefreshRaw()
{
    MIXERCONTROLDETAILS mcd = {0};

    if(m_DataType == MIXDT_CUSTOM)
    {
        m_pRaw = (BYTE*)malloc(m_mc.Metrics.cbCustomData);

        if(m_pRaw == 0)
        {
            // Memory error.
            //DebugBreak();
        }

        mcd.cbStruct       = sizeof(mcd);
        mcd.dwControlID    = m_mc.dwControlID;
        mcd.cChannels      = 0;// This is 0 for custom controls
        mcd.cMultipleItems = 0;// Same thing here.
        mcd.cbDetails      = m_mc.Metrics.cbCustomData;
        mcd.paDetails      = m_pRaw;

        if(MMSYSERR_NOERROR != mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mcd, MIXER_GETCONTROLDETAILSF_VALUE))
        {
            // Error!
            //MessageBox(0, L"hi", 0, MB_OK);
            //DebugBreak();
        }

        return;
    }
    else if(m_DataType == MIXDT_UNSIGNED)
    {
        mcd.cbStruct       = sizeof(mcd);
        mcd.dwControlID    = m_mc.dwControlID;
        mcd.cChannels = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM) ? 1 : m_ml.cChannels;
        mcd.cMultipleItems = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) ? m_mc.cMultipleItems : 0;
        mcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
        mcd.paDetails = m_pRaw;

        if(MMSYSERR_NOERROR != mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mcd, MIXER_GETCONTROLDETAILSF_VALUE))
        {
            // Error!
            //DebugBreak();
        }
    }
    else if(m_DataType == MIXDT_SIGNED)
    {
        mcd.cbStruct       = sizeof(mcd);
        mcd.dwControlID    = m_mc.dwControlID;
        mcd.cChannels = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM) ? 1 : m_ml.cChannels;
        mcd.cMultipleItems = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) ? m_mc.cMultipleItems : 0;
        mcd.cbDetails = sizeof(MIXERCONTROLDETAILS_SIGNED);
        mcd.paDetails = m_pRaw;

        if(MMSYSERR_NOERROR != mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mcd, MIXER_GETCONTROLDETAILSF_VALUE))
        {
            // Error!
            //DebugBreak();
        }
    }
    else if(m_DataType == MIXDT_BOOLEAN)
    {
        mcd.cbStruct       = sizeof(mcd);
        mcd.dwControlID    = m_mc.dwControlID;
        mcd.cChannels = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM) ? 1 : m_ml.cChannels;
        mcd.cMultipleItems = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) ? m_mc.cMultipleItems : 0;
        mcd.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
        mcd.paDetails = m_pRaw;

        if(MMSYSERR_NOERROR != mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mcd, MIXER_GETCONTROLDETAILSF_VALUE))
        {
            // Error!
            //DebugBreak();
        }
    }

    return;
}


/*
    Well what we need to do here is make sure we have our raw data,
    then do the real work.

    The real work is in converting that raw data into an array of VARIANTS.
*/
void CMixerControl::_RefreshVariants()
{
    int i = 0;

    // We can't very well get the variant data if we don't have the
    // raw data first!
    _RefreshRaw();

    switch(m_DataType)
    {
    case MIXDT_SIGNED:
        {
            MIXERCONTROLDETAILS_SIGNED* p = (MIXERCONTROLDETAILS_SIGNED*)m_pRaw;

            for(i=0;i<m_nRawItems;i++)
            {
                VariantInit(&m_pVariants[i]);
                m_pVariants[i].vt = VT_INT;
                m_pVariants[i].intVal = p[i].lValue;
            }

            break;
        }
    case MIXDT_UNSIGNED:
        {
            MIXERCONTROLDETAILS_UNSIGNED* p = (MIXERCONTROLDETAILS_UNSIGNED*)m_pRaw;

            for(i=0;i<m_nRawItems;i++)
            {
                VariantInit(&m_pVariants[i]);
                m_pVariants[i].vt = VT_UINT;
                m_pVariants[i].uintVal = p[i].dwValue;
            }

            break;
        }
    case MIXDT_BOOLEAN:
        {
            MIXERCONTROLDETAILS_BOOLEAN* p = (MIXERCONTROLDETAILS_BOOLEAN*)m_pRaw;

            for(i=0;i<m_nRawItems;i++)
            {
                VariantInit(&m_pVariants[i]);
                m_pVariants[i].vt = VT_BOOL;
                m_pVariants[i].boolVal = (p[i].fValue == TRUE) ? VARIANT_TRUE : VARIANT_FALSE;
            }

            break;
        }
    case MIXDT_CUSTOM:
    default:
        {
            // this should never happen...
            //DebugBreak();
            break;
        }
    }

    return;
}


void CMixerControl::_RefreshStrings()
{
    if(!(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE)) return;

    // We are guaranteed here that the control is a multiple-item control,
    // and therefore we're "ok to go" as ellie would say from Contact.

    MIXERCONTROLDETAILS mcd = {0};

    mcd.cbStruct = sizeof(mcd);
    mcd.cbDetails = sizeof(MIXERCONTROLDETAILS_LISTTEXT);
    mcd.dwControlID = m_mc.dwControlID;
    mcd.cChannels = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM) ? 1 : m_ml.cChannels;
    mcd.cMultipleItems = m_mc.cMultipleItems;
    mcd.paDetails = m_pStrings;

    if(MMSYSERR_NOERROR != mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mcd, MIXER_GETCONTROLDETAILSF_LISTTEXT))
    {
        //DebugBreak();
        return;
    }

    return;
}


/*
    This is where we refresh all our own data.  This includes
    all the buffers associated with this control.
*/
STDMETHODIMP CMixerControl::Refresh()
{
    _RefreshVariants();// Since this calls _RefreshRaw() we leave that one out.
    _RefreshStrings();
	return S_OK;
}


/*
    pcb may be 0
*/
STDMETHODIMP CMixerControl::GetCustomBuffer(BYTE **pVal, long *pcb)
{
    if(!pVal) return E_POINTER;
    if(m_Type != MIXC_CUSTOM) return MIX_E_WRONGTYPE;

    *pVal = m_pRaw;
    if(pcb) *pcb = m_mc.Metrics.cbCustomData;

	return S_OK;
}


STDMETHODIMP CMixerControl::CommitCustomBuffer()
{
    if(m_Type != MIXC_CUSTOM) return MIX_E_WRONGTYPE;

    MMRESULT mmr = 0;
    MIXERCONTROLDETAILS mcd = {0};

    mcd.cbStruct = sizeof(mcd);
    mcd.cbDetails = m_mc.Metrics.cbCustomData;
    mcd.dwControlID = m_mc.dwControlID;
    mcd.cChannels = 0;
    mcd.cMultipleItems = 0;
    mcd.paDetails = m_pRaw;

    mmr = mixerSetControlDetails((HMIXEROBJ)m_hMixer, &mcd, MIXER_GETCONTROLDETAILSF_VALUE);

    Refresh();

    return MapMMRToHRESULT(mmr);
}


STDMETHODIMP CMixerControl::GetValuesBuffer(VARIANT ** pVal, long *pc)
{
    if(!pVal) return E_POINTER;
    if(m_Type == MIXC_CUSTOM) return MIX_E_WRONGTYPE;

    *pVal = m_pVariants;
    if(pc) *pc = m_nRawItems;

	return S_OK;
}


/*
    This function needs to first convert our VARIANT array
    to the binary raw data.

    Then it commits it just like normal.
*/
STDMETHODIMP CMixerControl::CommitValuesBuffer()
{
    if(m_Type == MIXC_CUSTOM) return MIX_E_WRONGTYPE;

    int i = 0;
    MMRESULT mmr = 0;
    MIXERCONTROLDETAILS mcd = {0};

    switch(m_DataType)
    {
    case MIXDT_SIGNED:
        {
            MIXERCONTROLDETAILS_SIGNED* p = (MIXERCONTROLDETAILS_SIGNED*)m_pRaw;

            for(i=0;i<m_nRawItems;i++)
            {
                p[i].lValue = m_pVariants[i].intVal;
            }
            break;
        }
    case MIXDT_UNSIGNED:
        {
            MIXERCONTROLDETAILS_UNSIGNED* p = (MIXERCONTROLDETAILS_UNSIGNED*)m_pRaw;

            for(i=0;i<m_nRawItems;i++)
            {
                p[i].dwValue = m_pVariants[i].uintVal;
            }
            break;
        }
    case MIXDT_BOOLEAN:
        {
            MIXERCONTROLDETAILS_BOOLEAN* p = (MIXERCONTROLDETAILS_BOOLEAN*)m_pRaw;

            for(i=0;i<m_nRawItems;i++)
            {
                p[i].fValue = (m_pVariants[i].boolVal == VARIANT_TRUE) ? TRUE : FALSE;
            }
            break;
        }
    default:
        {
            // Error.
            return MIX_E_WRONGTYPE;
        }
    }

    return _CommitRawBuffer();
}


STDMETHODIMP CMixerControl::GetText(long id, BSTR *pVal)
{
    if(!pVal) return E_POINTER;
    if(!(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE)) return MIX_E_WRONGTYPE;
    if((id < 0) || (id >= (long)m_mc.cMultipleItems)) return E_INVALIDARG;

    *pVal = T2BSTR(m_pStrings[id].szName);

	return S_OK;
}


/*
    As far as I can tell, all multiple-item controls are required
    to supply list-text.
*/
STDMETHODIMP CMixerControl::get_supports_text(BOOL *pVal)
{
    if(!pVal) return E_POINTER;
    *pVal = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM) ? TRUE : FALSE;
	return S_OK;
}


/*
    Give the corresponding line for a mux (or mixer) item.
*/
STDMETHODIMP CMixerControl::GetMuxLine(long id, IMixerLine **pVal)
{
    // Validate stuff.
    if((m_Type != MIXC_MUX) && (m_Type != MIXC_MIXER)) return MIX_E_WRONGTYPE;
    if(!pVal) return E_POINTER;
    if((id < 0) || (id >= (long)m_mc.cMultipleItems)) return E_INVALIDARG;

    *pVal = 0;

    // Get the line ID
    CComObject<CMixerLine>* pLine = 0;

    pLine = m_pDest->GetLineByID(m_pStrings[id].dwParam1);

    if(!pLine) return MIX_E_NOTFOUND;

    return pLine->QueryInterface(IID_IMixerLine, (void**)pVal);
}


STDMETHODIMP CMixerControl::SetValuesUniformly(VARIANT v)
{
    long i;

    // Validate that the variant is the right type.
    switch(m_DataType)
    {
    case MIXDT_SIGNED:
        if(v.vt != VT_INT) return E_INVALIDARG;
        break;
    case MIXDT_UNSIGNED:
        if(v.vt != VT_UINT) return E_INVALIDARG;
        break;
    case MIXDT_BOOLEAN:
        if(v.vt != VT_BOOL) return E_INVALIDARG;
        break;
    default:
        return E_INVALIDARG;
        break;
    }

    for(i=0;i<m_nRawItems;i++)
    {
        VariantCopy(&m_pVariants[i], &v);
    }

	return S_OK;
}


STDMETHODIMP CMixerControl::get_owner(IMixerLine **pVal)
{
    if(!pVal) return E_POINTER;

    *pVal = 0;

    if(m_pLine)
    {
        return m_pLine->_InternalQueryInterface(IID_IMixerLine, (void**)pVal);
    }
    else
    {
        return m_pDest->_InternalQueryInterface(IID_IMixerLine, (void**)pVal);
    }

    // No man's land again!
	return MIX_E_FAIL;
}


STDMETHODIMP CMixerControl::get_controlid(unsigned long *pVal)
{
    if(!pVal) return E_POINTER;
    *pVal = m_mc.dwControlID;
	return S_OK;
}


STDMETHODIMP CMixerControl::get_short_name(BSTR *pVal)
{
    if(!pVal) return E_POINTER;
    *pVal = T2BSTR(m_mc.szShortName);
	return S_OK;
}


/*
    Gets the volume.  The volume is the value of the LOUDEST
    channel.
*/
STDMETHODIMP CMixerControl::get_volume(unsigned long *pVal)
{
    if(!pVal) return E_POINTER;
    if(m_DataType != MIXDT_UNSIGNED) return MIX_E_WRONGTYPE;
    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) return MIX_E_WRONGTYPE;

    int i = 0;
    unsigned long ret = 0;
    MIXERCONTROLDETAILS_UNSIGNED* p = (MIXERCONTROLDETAILS_UNSIGNED*)m_pRaw;

    for(i=0;i<m_nRawItems;i++)
    {
        if(p[i].dwValue > ret) ret = p[i].dwValue;
    }

    *pVal = ret;

	return S_OK;
}


/*
    The problem with this is that if the volume is too low
    then the balance can get off-whack.  Oh well...
*/
STDMETHODIMP CMixerControl::put_volume(unsigned long newVal)
{
    if(m_DataType != MIXDT_UNSIGNED) return MIX_E_WRONGTYPE;
    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) return MIX_E_WRONGTYPE;

    int i = 0;
    unsigned long largest = 0;
    MIXERCONTROLDETAILS_UNSIGNED* p = (MIXERCONTROLDETAILS_UNSIGNED*)m_pRaw;

    /*
        What we need to do is determine how to scale every
        channel's volume correctly.  So, we need to figure out
        the loudest channel and scale every other channel
        based off of that.  We *could* use ANY channel for
        the basis, but the larger the value, the more accurate
        the scaling.
    */
    for(i=0;i<m_nRawItems;i++)
    {
        if(p[i].dwValue > largest) largest = p[i].dwValue;
    }

    /*
        Now it goes something like this ratio:

         x     X
        --- = ---
         l     v

        Where:
        x is the current channel's original value
        X is the current channel's NEW value (solving for this)
        l is the loudest channel's original value
        v is the loudest channel's NEW value (the value passed into this function)

        And it is translated into programmer's language like this:
        (v*x)/l = X;
    */
    for(i=0;i<m_nRawItems;i++)
    {
        if(largest == 0)
        {
            p[i].dwValue = newVal;
        }
        else
        {
            p[i].dwValue = (unsigned long)
                (((double)newVal*(double)p[i].dwValue) / (double)largest);
        }
    }

    return _CommitRawBuffer();
}


/*
    Only works if there is 2 channels.

    Returns 0 if the balance is all the way to the left.
    Returns 65535 if all the way to the right.
    32767 if it's in the center
*/
STDMETHODIMP CMixerControl::get_balance(unsigned long *pVal)
{
    if(!pVal) return E_POINTER;
    if(m_DataType != MIXDT_UNSIGNED) return MIX_E_WRONGTYPE;
    if(m_ml.cChannels != 2) return MIX_E_WRONGTYPE;
    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) return MIX_E_WRONGTYPE;

    unsigned long dwLeft;
    unsigned long dwRight;

    MIXERCONTROLDETAILS_UNSIGNED* p = (MIXERCONTROLDETAILS_UNSIGNED*)m_pRaw;

    dwLeft = p[0].dwValue;
    dwRight = p[1].dwValue;

    if(dwLeft == dwRight)
    {
        *pVal = 32767;
        return S_OK;
    }

    if(dwLeft > dwRight)
    {
        // The value will be between 0 - 32767.
        *pVal = (32768*dwRight)/dwLeft;
    }
    else
    {
        // The value will be between 32768 - 65535.
        *pVal = 65536-((32768*dwLeft)/dwRight);
    }

    if(*pVal > 65535) *pVal = 65535;// Just to be safe.

	return S_OK;
}


STDMETHODIMP CMixerControl::put_balance(unsigned long newVal)
{
    if(m_DataType != MIXDT_UNSIGNED) return MIX_E_WRONGTYPE;
    if(m_ml.cChannels != 2) return MIX_E_WRONGTYPE;
    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) return MIX_E_WRONGTYPE;

    unsigned long dwVol;

    MIXERCONTROLDETAILS_UNSIGNED* p = (MIXERCONTROLDETAILS_UNSIGNED*)m_pRaw;

    dwVol = max(p[0].dwValue, p[1].dwValue);

    // Center it, then attenuate one channel.
    p[0].dwValue = dwVol;
    p[1].dwValue = dwVol;

    if(newVal > 32767)
    {
        // Attenuate the left channel
        unsigned long dwAtt = newVal-32768;// This will be from 0-32767, how much to "quieten" the channel.
        dwAtt = 32767-dwAtt;
        p[0].dwValue = (p[0].dwValue*dwAtt)/32768;
    }
    else
    {
        // Attenuate the right channel
        unsigned long dwAtt = newVal-32768;// This will be from 0-32767, how much to "quieten" the channel.
        p[1].dwValue = (p[1].dwValue*newVal)/32768;
    }

	return _CommitRawBuffer();
}


STDMETHODIMP CMixerControl::get_mute(BOOL *pVal)
{
    if(!pVal) return E_POINTER;
    if(m_DataType != MIXDT_BOOLEAN) return MIX_E_WRONGTYPE;
    if(!(m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM)) return MIX_E_WRONGTYPE;
    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) return MIX_E_WRONGTYPE;

    MIXERCONTROLDETAILS_BOOLEAN* p = (MIXERCONTROLDETAILS_BOOLEAN*)m_pRaw;

    *pVal = p[0].fValue;

	return S_OK;
}


STDMETHODIMP CMixerControl::put_mute(BOOL newVal)
{
    if(m_DataType != MIXDT_BOOLEAN) return MIX_E_WRONGTYPE;
    if(!(m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM)) return MIX_E_WRONGTYPE;
    if(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) return MIX_E_WRONGTYPE;

    MIXERCONTROLDETAILS_BOOLEAN* p = (MIXERCONTROLDETAILS_BOOLEAN*)m_pRaw;

    p[0].fValue = newVal;

	return _CommitRawBuffer();
}


CComObject<CMixerLine>* CMixerControl::_GetMuxSource()
{
    long lSelected = 0;
    CComObject<CMixerLine>* pLine = 0;

    // Get the index of the item.
    lSelected = _GetMuxIndex();
    if(lSelected == -1) return 0;

    // Now we can determine the line ID of it.
    if(!m_pStrings) return 0;

    // Get the line that we are interested in.
    return m_pDest->GetLineByID(m_pStrings[lSelected].dwParam1);
}


long CMixerControl::_GetMuxIndex()
{
    if(!(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE)) return -1;
    if(m_DataType != MIXDT_BOOLEAN) return -1;

    MIXERCONTROLDETAILS_BOOLEAN* p = (MIXERCONTROLDETAILS_BOOLEAN*)m_pRaw;
    long i = 0;
    long lSelected = -1;// index of the selected mux source.

    // Determine which mux id is selected.
    for(i=0;i<m_nRawItems;i++)
    {
        if(p[i].fValue == TRUE)
        {
            lSelected = i;
            break;
        }
    }

    return lSelected;
}


STDMETHODIMP CMixerControl::get_mux_source(IMixerLine **pVal)
{
    if(!pVal) return E_POINTER;

    *pVal = 0;

    CComObject<CMixerLine>* pLine = 0;

    pLine = _GetMuxSource();

    if(!pLine) return MIX_E_NOTFOUND;

    return pLine->QueryInterface(IID_IMixerLine, (void**)pVal);
}


STDMETHODIMP CMixerControl::put_mux_source(IMixerLine *newVal)
{
    if(!newVal) return E_POINTER;
    if(!(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE)) return MIX_E_WRONGTYPE;
    if(m_DataType != MIXDT_BOOLEAN) return MIX_E_WRONGTYPE;

    MIXERCONTROLDETAILS_BOOLEAN* p = (MIXERCONTROLDETAILS_BOOLEAN*)m_pRaw;
    unsigned long dwLineID = 0;
    long i = 0;
    HRESULT hr = 0;
    long lMuxItem = -1;

    if(FAILED(hr = newVal->get_lineid(&dwLineID)))
    {
        return hr;
    }

    if(!m_pStrings) return MIX_E_NOSUPPORT;

    // Determine which mux item that line refers to
    for(i=0;i<m_nRawItems;i++)
    {
        if(dwLineID == m_pStrings[i].dwParam1)
        {
            lMuxItem = i;
            p[i].fValue = TRUE;
        }
        else
        {
            p[i].fValue = FALSE;
        }
    }

    if(lMuxItem == -1) return MIX_E_NOTFOUND;

    return _CommitRawBuffer();
}


STDMETHODIMP CMixerControl::get_mux_type(MIX_LINE *pVal)
{
    if(!pVal) return E_POINTER;

    CComObject<CMixerLine>* pLine = 0;

    pLine = _GetMuxSource();

    if(!pLine) return MIX_E_NOTFOUND;

    return pLine->get_type(pVal);
}


STDMETHODIMP CMixerControl::put_mux_type(MIX_LINE newVal)
{
    CComObject<CMixerLine>* pLine = 0;
    IMixerLine* pILine = 0;
    HRESULT hr = 0;

    pLine = m_pDest->GetLine(newVal);
    if(!pLine) return MIX_E_NOTFOUND;

    if(FAILED(hr = pLine->QueryInterface(IID_IMixerLine, (void**)&pILine)))
    {
        return hr;
    }

    hr = put_mux_source(pILine);

    pILine->Release();
    pILine = 0;

	return hr;
}


/*
    This doesn't work for custom controls.
*/
HRESULT CMixerControl::_CommitRawBuffer()
{
    MIXERCONTROLDETAILS mcd = {0};
    MMRESULT mmr;

    mcd.cbStruct = sizeof(mcd);

    switch(m_DataType)
    {
    case MIXDT_SIGNED:
        mcd.cbDetails = sizeof(MIXERCONTROLDETAILS_SIGNED);
        break;
    case MIXDT_BOOLEAN:
        mcd.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
        break;
    case MIXDT_UNSIGNED:
        mcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
        break;
    }

    mcd.dwControlID = m_mc.dwControlID;
    mcd.cChannels = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM) ? 1 : m_ml.cChannels;
    mcd.cMultipleItems = (m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE) ? m_mc.cMultipleItems : 0;
    mcd.paDetails = m_pRaw;

    mmr = mixerSetControlDetails((HMIXEROBJ)m_hMixer, &mcd, MIXER_GETCONTROLDETAILSF_VALUE);

    Refresh();

    return MapMMRToHRESULT(mmr);
}


DWORD CMixerControl::GetID()
{
    return m_mc.dwControlID;
}


HRESULT CMixerControl::SaveControl(XMLDoc* pDoc, XMLEl* pParent)
{
    XMLEl* pThis = 0;
    HRESULT hr;
    CCString sValues;
    CCString sTemp;
    BOOL bFirst;

    if(FAILED(hr = XMLFindControl(pDoc, pParent, 
        m_mc.dwControlID, CCString(m_mc.szName), m_Type, &pThis, TRUE)))
    {
        return hr;
    }

    // Save the values of this control.
    // We just go in order, separating values with a comma.

    bFirst = TRUE;// This will determine if we need to add a comma or not.
    int i = 0;

    switch(m_DataType)
    {
    case MIXDT_CUSTOM:
        {
            sValues.FromBinary(m_pRaw, m_mc.Metrics.cbCustomData);
            pThis->setAttribute(CCString(L"Values"), sValues.variant());
            break;
        }
    case MIXDT_SIGNED:
        {
            MIXERCONTROLDETAILS_SIGNED* p = (MIXERCONTROLDETAILS_SIGNED*)m_pRaw;

            sValues.froml(p[0].lValue, 10);

            for(i=1;i<m_nRawItems;i++)
            {
                sValues.cat(L", ");
                sTemp.froml(p[i].lValue, 10);
                sValues.cat(sTemp);
            }

            pThis->setAttribute(CCString(L"Values"), sValues.variant());

            break;
        }
    case MIXDT_UNSIGNED:
        {
            MIXERCONTROLDETAILS_UNSIGNED* p = (MIXERCONTROLDETAILS_UNSIGNED*)m_pRaw;

            sValues.fromul(p[0].dwValue, 10);

            for(i=1;i<m_nRawItems;i++)
            {
                sValues.cat(L", ");
                sTemp.fromul(p[i].dwValue, 10);
                sValues.cat(sTemp);
            }

            pThis->setAttribute(CCString(L"Values"), sValues.variant());

            break;
        }
    case MIXDT_BOOLEAN:
        {
            MIXERCONTROLDETAILS_BOOLEAN* p = (MIXERCONTROLDETAILS_BOOLEAN*)m_pRaw;

            sValues = (p[0].fValue == TRUE) ? L"TRUE" : L"FALSE";

            for(i=1;i<m_nRawItems;i++)
            {
                sTemp.FormatW(L", %s", (p[i].fValue == TRUE) ? L"TRUE" : L"FALSE");
                sValues.cat(sTemp);
            }

            pThis->setAttribute(CCString(L"Values"), sValues.variant());

            break;
        }
    default:
        {
            //
        }
    }

    SAFE_RELEASE(pThis);

    return hr;
}


HRESULT CMixerControl::GetNode(XMLDoc* pDoc, XMLEl* pLibrary, XMLEl** p, BOOL bCreate)
{
    if(m_pLine)
    {
        return XMLFindControl(pDoc, pLibrary,
            m_pLine->m_pOwner->m_pOwner->m_uID, CCString(m_pLine->m_pOwner->m_pOwner->m_mc.szPname),
            m_pLine->m_pOwner->m_ml.dwLineID, CCString(m_pLine->m_pOwner->m_ml.szName), m_pLine->m_pOwner->m_Type,
            m_pLine->m_ml.dwLineID, CCString(m_pLine->m_ml.szName), m_pLine->m_Type,
            m_mc.dwControlID, CCString(m_mc.szName), m_Type,
            p, bCreate);
    }
    else if(m_pDest)
    {
        return XMLFindControl(pDoc, pLibrary,
            m_pDest->m_pOwner->m_uID, CCString(m_pDest->m_pOwner->m_mc.szPname),
            m_pDest->m_ml.dwLineID, CCString(m_pDest->m_ml.szName), m_pDest->m_Type,
            m_mc.dwControlID, CCString(m_mc.szName), m_Type,
            p, bCreate);
    }

    return E_FAIL;// Internal error! (bug in the program)
}


STDMETHODIMP CMixerControl::Save(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    XMLEl* pParent = 0;
    HRESULT hr;

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    // Get the parent node.  This is going to depend on whether it's a dest
    // or a line.
    if(m_pLine)
    {
        if(FAILED(hr = m_pLine->GetNode(pDoc, pLibrary, &pParent, TRUE)))
        {
            SAFE_RELEASE(pLibrary);
            XMLClose(&pDoc);
            return hr;
        }
    }
    else
    {
        if(FAILED(hr = m_pDest->GetNode(pDoc, pLibrary, &pParent, TRUE)))
        {
            SAFE_RELEASE(pLibrary);
            XMLClose(&pDoc);
            return hr;
        }
    }

    if(FAILED(hr = SaveControl(pDoc, pParent)))
    {
        SAFE_RELEASE(pParent);
        XMLClose(&pDoc);
        return hr;
    }

    SAFE_RELEASE(pParent);
    SAFE_RELEASE(pLibrary);

    hr = XMLCommit(pDoc, v);
    XMLClose(&pDoc);

    return hr;
}


STDMETHODIMP CMixerControl::Load(VARIANT v)
{
    XMLDoc* pDoc = 0;
    XMLEl* pLibrary = 0;
    HRESULT hr;

    if(FAILED(hr = XMLOpen(v, &pDoc, &pLibrary)))
    {
        return hr;
    }

    // Load ourself up.
    hr = LoadControl(pLibrary);

    SAFE_RELEASE(pLibrary);
    XMLClose(&pDoc);

	return hr;
}


PCWSTR SkipPastSpaces(PCWSTR wsz)
{
    while(1)
    {
        if(wsz[0] == 0)
        {
            return 0;
        }

        if(wsz[0] != L' ')
        {
            return wsz;
        }

        wsz++;
    }

    // No man's land!
    return 0;
}


/*
    This function takes a string and finds the next token.  Returns the pointer
    to the next token in the string, or 0 if we're all done.
    
    The tokens are delimited with a comma and optional spaces.
*/
PCWSTR NextToken(WCHAR* wszToken, PCWSTR wszString)
{
    PCWSTR wszCurrent = wszString;
    WCHAR wc;
    WCHAR* wszCurrentToken = wszToken;

    // Basically we just go until we hit:
    // 1) NULL
    // 2) Comma
    while(1)
    {
        wc = wszCurrent[0];
        if(wc == 0)
        {
            // We found the end of the string.
            wszCurrentToken[0] = 0;
            return 0;
        }

        if(wc == L',')
        {
            // We found a comma!  Let's skip past any spaces now and return.
            wszCurrentToken[0] = 0;
            wszCurrent++;// Skip past the comma.
            return SkipPastSpaces(wszCurrent);
        }

        wszCurrentToken[0] = wc;
        wszCurrentToken++;
        wszCurrent++;
    }

    // No man's land.
    return 0;
}


HRESULT CMixerControl::LoadControl(XMLEl* pLibrary)
{
    XMLEl* pThis = 0;
    CCString sValues;
    PCWSTR wszCurrent = 0;// Current place in the sValues string.
    WCHAR* wszToken = 0;// The token.  To avoid a buffer-overrun we make this string the same size as sValues.
    int i = 0;// Current index we're workin on.

    MIXERCONTROLDETAILS_BOOLEAN* pBoolean = (MIXERCONTROLDETAILS_BOOLEAN*)m_pRaw;
    MIXERCONTROLDETAILS_UNSIGNED* pUnsigned = (MIXERCONTROLDETAILS_UNSIGNED*)m_pRaw;
    MIXERCONTROLDETAILS_SIGNED* pSigned = (MIXERCONTROLDETAILS_SIGNED*)m_pRaw;

    if(FAILED(GetNode(0, pLibrary, &pThis, FALSE)))
    {
        return MIX_E_XMLERR;
    }

    // Here, we concern ourself with the value attribute.
    if(FAILED(XMLGetAttribute(pThis, CCString(L"Values"), &sValues)))
    {
        SAFE_RELEASE(pThis);
        return MIX_E_XMLERR;
    }

    // Let's go case-insensitive.
    sValues.upr();

    // If we're doing raw binary data, we can skip all the parsing.
    if(m_DataType == MIXDT_CUSTOM)
    {
        sValues.ToBinary(m_pRaw, m_mc.Metrics.cbCustomData);
        SAFE_RELEASE(pThis);
        return S_OK;
    }

    // Set up our looping stuff.
    wszCurrent = sValues;
    wszToken = (WCHAR*)malloc((wcslen(wszCurrent)+1)*sizeof(WCHAR));

    while(1)
    {
        wszCurrent = NextToken(wszToken, wszCurrent);

        if(m_DataType == MIXDT_BOOLEAN)
        {
            // Now wszToken is the current token.
            if(wcsicmp(wszToken, L"TRUE") == 0)
            {
                pBoolean[i].fValue = TRUE;
            }
            else if(wcsicmp(wszToken, L"FALSE") == 0)
            {
                pBoolean[i].fValue = FALSE;
            }
        }
        else if(m_DataType == MIXDT_SIGNED)
        {
            pSigned[i].lValue = wcstol(wszToken, 0, 10);
        }
        else if(m_DataType == MIXDT_UNSIGNED)
        {
            pUnsigned[i].dwValue = wcstoul(wszToken, 0, 10);
        }

        i++;

        if(i >= m_nRawItems) break;
        if(wszCurrent == 0) break;
    }

    free(wszToken);
    wszToken = 0;

    SAFE_RELEASE(pThis);

    // Now commit the buffer.
    _CommitRawBuffer();

    return S_OK;
}


STDMETHODIMP CMixerControl::get_fade(unsigned long *pVal)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CMixerControl::put_fade(unsigned long newVal)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}
