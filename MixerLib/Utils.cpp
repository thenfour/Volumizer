

#include "stdafx.h"
#include "Utils.h"


WCHAR g_wszMixerTypeConv[50];


BOOL VariantIsNumber(VARIANT* p)
{
    switch(p->vt)
    {
    case VT_I2:
    case VT_I4:
    case VT_I8:
    case VT_R4:
    case VT_R8:
    case VT_UI2:
    case VT_UI4:
    case VT_UI8:
    case VT_INT:
    case VT_UINT:
        return TRUE;
    }
    return FALSE;
}


BOOL VariantIsString(VARIANT* p)
{
    switch(p->vt)
    {
    case VT_BSTR:
    case VT_LPWSTR:
    case VT_LPSTR:
        return TRUE;
    }
    return FALSE;
}


PCWSTR DestinationToString(MIX_DESTINATION x)
{
    switch(x)
    {
    case MIXD_INVALID: swprintf(g_wszMixerTypeConv, L"INVALID"); break;
    case MIXD_HEADPHONES: swprintf(g_wszMixerTypeConv, L"HEADPHONES"); break;
    case MIXD_LINE: swprintf(g_wszMixerTypeConv, L"LINE"); break;
    case MIXD_MONITOR: swprintf(g_wszMixerTypeConv, L"MONITOR"); break;
    case MIXD_SPEAKERS: swprintf(g_wszMixerTypeConv, L"SPEAKERS"); break;
    case MIXD_TELEPHONE: swprintf(g_wszMixerTypeConv, L"TELEPHONE"); break;
    case MIXD_UNDEFINED: swprintf(g_wszMixerTypeConv, L"UNDEFINED"); break;
    case MIXD_VOICEIN: swprintf(g_wszMixerTypeConv, L"VOICEIN"); break;
    case MIXD_WAVEIN: swprintf(g_wszMixerTypeConv, L"WAVEIN"); break;
    case MIXD_DIGITAL: swprintf(g_wszMixerTypeConv, L"DIGITAL"); break;
    default: swprintf(g_wszMixerTypeConv, L"UNDEFINED"); break;
    }

    return g_wszMixerTypeConv;
}


PCWSTR LineToString(MIX_LINE x)
{
    switch(x)
    {
    case MIXL_INVALID: swprintf(g_wszMixerTypeConv, L"INVALID"); break;
    case MIXL_AUXILIARY: swprintf(g_wszMixerTypeConv, L"AUXILIARY"); break;
    case MIXL_COMPACTDISC: swprintf(g_wszMixerTypeConv, L"COMPACTDISC"); break;
    case MIXL_DIGITAL: swprintf(g_wszMixerTypeConv, L"DIGITAL"); break;
    case MIXL_LINE: swprintf(g_wszMixerTypeConv, L"LINE"); break;
    case MIXL_MICROPHONE: swprintf(g_wszMixerTypeConv, L"MICROPHONE"); break;
    case MIXL_PCSPEAKER: swprintf(g_wszMixerTypeConv, L"PCSPEAKER"); break;
    case MIXL_SYNTHESIZER: swprintf(g_wszMixerTypeConv, L"SYNTHESIZER"); break;
    case MIXL_TELEPHONE: swprintf(g_wszMixerTypeConv, L"TELEPHONE"); break;
    case MIXL_UNDEFINED: swprintf(g_wszMixerTypeConv, L"UNDEFINED"); break;
    case MIXL_WAVEOUT: swprintf(g_wszMixerTypeConv, L"WAVEOUT"); break;
    case MIXL_SELF: swprintf(g_wszMixerTypeConv, L"SELF"); break;
    case MIXL_ANALOG: swprintf(g_wszMixerTypeConv, L"ANALOG"); break;
    default: swprintf(g_wszMixerTypeConv, L"UNDEFINED"); break;
    }

    return g_wszMixerTypeConv;
}


PCWSTR ControlToString(MIX_CONTROL x)
{
    switch(x)
    {
    case MIXC_INVALID: swprintf(g_wszMixerTypeConv, L"INVALID"); break;
    case MIXC_BASS: swprintf(g_wszMixerTypeConv, L"BASS"); break;
    case MIXC_EQUALIZER: swprintf(g_wszMixerTypeConv, L"EQUALIZER"); break;
    case MIXC_FADER: swprintf(g_wszMixerTypeConv, L"FADER"); break;
    case MIXC_TREBLE: swprintf(g_wszMixerTypeConv, L"TREBLE"); break;
    case MIXC_VOLUME: swprintf(g_wszMixerTypeConv, L"VOLUME"); break;
    case MIXC_MIXER: swprintf(g_wszMixerTypeConv, L"MIXER"); break;
    case MIXC_MULTIPLESELECT: swprintf(g_wszMixerTypeConv, L"MULTIPLESELECT"); break;
    case MIXC_MUX: swprintf(g_wszMixerTypeConv, L"MUX"); break;
    case MIXC_SINGLESELECT: swprintf(g_wszMixerTypeConv, L"SINGLESELECT"); break;
    case MIXC_BOOLEANMETER: swprintf(g_wszMixerTypeConv, L"BOOLEANMETER"); break;
    case MIXC_PEAKMETER: swprintf(g_wszMixerTypeConv, L"PEAKMETER"); break;
    case MIXC_SIGNEDMETER: swprintf(g_wszMixerTypeConv, L"SIGNEDMETER"); break;
    case MIXC_UNSIGNEDMETER: swprintf(g_wszMixerTypeConv, L"UNSIGNEDMETER"); break;
    case MIXC_DECIBELS: swprintf(g_wszMixerTypeConv, L"DECIBELS"); break;
    case MIXC_PERCENT: swprintf(g_wszMixerTypeConv, L"PERCENT"); break;
    case MIXC_SIGNED: swprintf(g_wszMixerTypeConv, L"SIGNED"); break;
    case MIXC_UNSIGNED: swprintf(g_wszMixerTypeConv, L"UNSIGNED"); break;
    case MIXC_PAN: swprintf(g_wszMixerTypeConv, L"PAN"); break;
    case MIXC_QSOUNDPAN: swprintf(g_wszMixerTypeConv, L"QSOUNDPAN"); break;
    case MIXC_SLIDER: swprintf(g_wszMixerTypeConv, L"SLIDER"); break;
    case MIXC_BOOLEAN: swprintf(g_wszMixerTypeConv, L"BOOLEAN"); break;
    case MIXC_BUTTON: swprintf(g_wszMixerTypeConv, L"BUTTON"); break;
    case MIXC_LOUDNESS: swprintf(g_wszMixerTypeConv, L"LOUDNESS"); break;
    case MIXC_MONO: swprintf(g_wszMixerTypeConv, L"MONO"); break;
    case MIXC_MUTE: swprintf(g_wszMixerTypeConv, L"MUTE"); break;
    case MIXC_ONOFF: swprintf(g_wszMixerTypeConv, L"ONOFF"); break;
    case MIXC_STEREOENH: swprintf(g_wszMixerTypeConv, L"STEREOENH"); break;
    case MIXC_BASS_BOOST: swprintf(g_wszMixerTypeConv, L"BASS_BOOST"); break;
    case MIXC_MICROTIME: swprintf(g_wszMixerTypeConv, L"MICROTIME"); break;
    case MIXC_MILLITIME: swprintf(g_wszMixerTypeConv, L"MILLITIME"); break;
    case MIXC_CUSTOM: swprintf(g_wszMixerTypeConv, L"CUSTOM"); break;
    case MIXC_UNDEFINED: swprintf(g_wszMixerTypeConv, L"UNDEFINED"); break;
    default: swprintf(g_wszMixerTypeConv, L"UNDEFINED"); break;
    }

    return g_wszMixerTypeConv;
}


MIX_DESTINATION WinToMix_Destination(DWORD dw)
{
    switch(dw)
    {
        case MIXERLINE_COMPONENTTYPE_DST_UNDEFINED: return MIXD_UNDEFINED;
        case MIXERLINE_COMPONENTTYPE_DST_DIGITAL: return MIXD_DIGITAL;
        case MIXERLINE_COMPONENTTYPE_DST_LINE: return MIXD_LINE;
        case MIXERLINE_COMPONENTTYPE_DST_MONITOR: return MIXD_MONITOR;
        case MIXERLINE_COMPONENTTYPE_DST_SPEAKERS: return MIXD_SPEAKERS;
        case MIXERLINE_COMPONENTTYPE_DST_HEADPHONES: return MIXD_HEADPHONES;
        case MIXERLINE_COMPONENTTYPE_DST_TELEPHONE: return MIXD_TELEPHONE;
        case MIXERLINE_COMPONENTTYPE_DST_WAVEIN: return MIXD_WAVEIN;
        case MIXERLINE_COMPONENTTYPE_DST_VOICEIN: return MIXD_VOICEIN;
    }
    return MIXD_INVALID;
}


MIX_LINE WinToMix_Line(DWORD dw)
{
    switch(dw)
    {
        case MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED: return MIXL_UNDEFINED;
        case MIXERLINE_COMPONENTTYPE_SRC_DIGITAL: return MIXL_DIGITAL;
        case MIXERLINE_COMPONENTTYPE_SRC_LINE: return MIXL_LINE;
        case MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE: return MIXL_MICROPHONE;
        case MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER: return MIXL_SYNTHESIZER;
        case MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC: return MIXL_COMPACTDISC;
        case MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE: return MIXL_TELEPHONE;
        case MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER: return MIXL_PCSPEAKER;
        case MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT: return MIXL_WAVEOUT;
        case MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY: return MIXL_AUXILIARY;
        case MIXERLINE_COMPONENTTYPE_SRC_ANALOG: return MIXL_ANALOG;
    }
    return MIXL_INVALID;
}


MIX_CONTROL WinToMix_Control(DWORD dw)
{
    switch(dw)
    {
        case MIXERCONTROL_CONTROLTYPE_CUSTOM: return MIXC_CUSTOM;
        case MIXERCONTROL_CONTROLTYPE_BOOLEANMETER: return MIXC_BOOLEANMETER;
        case MIXERCONTROL_CONTROLTYPE_SIGNEDMETER: return MIXC_SIGNEDMETER;
        case MIXERCONTROL_CONTROLTYPE_PEAKMETER: return MIXC_PEAKMETER;
        case MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER: return MIXC_UNSIGNEDMETER;
        case MIXERCONTROL_CONTROLTYPE_BOOLEAN: return MIXC_BOOLEAN;
        case MIXERCONTROL_CONTROLTYPE_ONOFF: return MIXC_ONOFF;
        case MIXERCONTROL_CONTROLTYPE_MUTE: return MIXC_MUTE;
        case MIXERCONTROL_CONTROLTYPE_MONO: return MIXC_MONO;
        case MIXERCONTROL_CONTROLTYPE_LOUDNESS: return MIXC_LOUDNESS;
        case MIXERCONTROL_CONTROLTYPE_STEREOENH: return MIXC_STEREOENH;
        case MIXERCONTROL_CONTROLTYPE_BASS_BOOST: return MIXC_BASS_BOOST;
        case MIXERCONTROL_CONTROLTYPE_BUTTON: return MIXC_BUTTON;
        case MIXERCONTROL_CONTROLTYPE_DECIBELS: return MIXC_DECIBELS;
        case MIXERCONTROL_CONTROLTYPE_SIGNED: return MIXC_SIGNED;
        case MIXERCONTROL_CONTROLTYPE_UNSIGNED: return MIXC_UNSIGNED;
        case MIXERCONTROL_CONTROLTYPE_PERCENT: return MIXC_PERCENT;
        case MIXERCONTROL_CONTROLTYPE_SLIDER: return MIXC_SLIDER;
        case MIXERCONTROL_CONTROLTYPE_PAN: return MIXC_PAN;
        case MIXERCONTROL_CONTROLTYPE_QSOUNDPAN: return MIXC_QSOUNDPAN;
        case MIXERCONTROL_CONTROLTYPE_FADER: return MIXC_FADER;
        case MIXERCONTROL_CONTROLTYPE_VOLUME: return MIXC_VOLUME;
        case MIXERCONTROL_CONTROLTYPE_BASS: return MIXC_BASS;
        case MIXERCONTROL_CONTROLTYPE_TREBLE: return MIXC_TREBLE;
        case MIXERCONTROL_CONTROLTYPE_EQUALIZER: return MIXC_EQUALIZER;
        case MIXERCONTROL_CONTROLTYPE_SINGLESELECT: return MIXC_SINGLESELECT;
        case MIXERCONTROL_CONTROLTYPE_MUX: return MIXC_MUX;
        case MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT: return MIXC_MULTIPLESELECT;
        case MIXERCONTROL_CONTROLTYPE_MIXER: return MIXC_MIXER;
        case MIXERCONTROL_CONTROLTYPE_MICROTIME: return MIXC_MICROTIME;
        case MIXERCONTROL_CONTROLTYPE_MILLITIME: return MIXC_MILLITIME;
    }
    return MIXC_INVALID;
}


DWORD MixToWin_Destination(MIX_DESTINATION dw)
{
    switch(dw)
    {
        case MIXD_UNDEFINED: return MIXERLINE_COMPONENTTYPE_DST_UNDEFINED;
        case MIXD_DIGITAL: return MIXERLINE_COMPONENTTYPE_DST_DIGITAL;
        case MIXD_LINE: return MIXERLINE_COMPONENTTYPE_DST_LINE;
        case MIXD_MONITOR: return MIXERLINE_COMPONENTTYPE_DST_MONITOR;
        case MIXD_SPEAKERS: return MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
        case MIXD_HEADPHONES: return MIXERLINE_COMPONENTTYPE_DST_HEADPHONES;
        case MIXD_TELEPHONE: return MIXERLINE_COMPONENTTYPE_DST_TELEPHONE;
        case MIXD_WAVEIN: return MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
        case MIXD_VOICEIN: return MIXERLINE_COMPONENTTYPE_DST_VOICEIN;
    }
    return (DWORD)-1;
}


DWORD MixToWin_Line(MIX_LINE dw)
{
    switch(dw)
    {
        case MIXL_UNDEFINED: return MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED;
        case MIXL_DIGITAL: return MIXERLINE_COMPONENTTYPE_SRC_DIGITAL;
        case MIXL_LINE: return MIXERLINE_COMPONENTTYPE_SRC_LINE;
        case MIXL_MICROPHONE: return MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;
        case MIXL_SYNTHESIZER: return MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER;
        case MIXL_COMPACTDISC: return MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC;
        case MIXL_TELEPHONE: return MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE;
        case MIXL_PCSPEAKER: return MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER;
        case MIXL_WAVEOUT: return MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT;
        case MIXL_AUXILIARY: return MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY;
        case MIXL_ANALOG: return MIXERLINE_COMPONENTTYPE_SRC_ANALOG;
    }
    return (DWORD)-1;
}


DWORD MixToWin_Control(MIX_CONTROL dw)
{
    switch(dw)
    {
        case MIXC_CUSTOM: return MIXERCONTROL_CONTROLTYPE_CUSTOM;
        case MIXC_BOOLEANMETER: return MIXERCONTROL_CONTROLTYPE_BOOLEANMETER;
        case MIXC_SIGNEDMETER: return MIXERCONTROL_CONTROLTYPE_SIGNEDMETER;
        case MIXC_PEAKMETER: return MIXERCONTROL_CONTROLTYPE_PEAKMETER;
        case MIXC_UNSIGNEDMETER: return MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER;
        case MIXC_BOOLEAN: return MIXERCONTROL_CONTROLTYPE_BOOLEAN;
        case MIXC_ONOFF: return MIXERCONTROL_CONTROLTYPE_ONOFF;
        case MIXC_MUTE: return MIXERCONTROL_CONTROLTYPE_MUTE;
        case MIXC_MONO: return MIXERCONTROL_CONTROLTYPE_MONO;
        case MIXC_LOUDNESS: return MIXERCONTROL_CONTROLTYPE_LOUDNESS;
        case MIXC_STEREOENH: return MIXERCONTROL_CONTROLTYPE_STEREOENH;
        case MIXC_BASS_BOOST: return MIXERCONTROL_CONTROLTYPE_BASS_BOOST;
        case MIXC_BUTTON: return MIXERCONTROL_CONTROLTYPE_BUTTON;
        case MIXC_DECIBELS: return MIXERCONTROL_CONTROLTYPE_DECIBELS;
        case MIXC_SIGNED: return MIXERCONTROL_CONTROLTYPE_SIGNED;
        case MIXC_UNSIGNED: return MIXERCONTROL_CONTROLTYPE_UNSIGNED;
        case MIXC_PERCENT: return MIXERCONTROL_CONTROLTYPE_PERCENT;
        case MIXC_SLIDER: return MIXERCONTROL_CONTROLTYPE_SLIDER;
        case MIXC_PAN: return MIXERCONTROL_CONTROLTYPE_PAN;
        case MIXC_QSOUNDPAN: return MIXERCONTROL_CONTROLTYPE_QSOUNDPAN;
        case MIXC_FADER: return MIXERCONTROL_CONTROLTYPE_FADER;
        case MIXC_VOLUME: return MIXERCONTROL_CONTROLTYPE_VOLUME;
        case MIXC_BASS: return MIXERCONTROL_CONTROLTYPE_BASS;
        case MIXC_TREBLE: return MIXERCONTROL_CONTROLTYPE_TREBLE;
        case MIXC_EQUALIZER: return MIXERCONTROL_CONTROLTYPE_EQUALIZER;
        case MIXC_SINGLESELECT: return MIXERCONTROL_CONTROLTYPE_SINGLESELECT;
        case MIXC_MUX: return MIXERCONTROL_CONTROLTYPE_MUX;
        case MIXC_MULTIPLESELECT: return MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT;
        case MIXC_MIXER: return MIXERCONTROL_CONTROLTYPE_MIXER;
        case MIXC_MICROTIME: return MIXERCONTROL_CONTROLTYPE_MICROTIME;
        case MIXC_MILLITIME: return MIXERCONTROL_CONTROLTYPE_MILLITIME;
    }
    return (DWORD)-1;
}


MIX_DATATYPE WinToMix_DataType(DWORD dw)
{
    switch(dw)
    {
        // Custom
        case MIXERCONTROL_CONTROLTYPE_CUSTOM:
            return MIXDT_CUSTOM;

        // Fader
        case MIXERCONTROL_CONTROLTYPE_BASS:
        case MIXERCONTROL_CONTROLTYPE_EQUALIZER:
        case MIXERCONTROL_CONTROLTYPE_FADER:
        case MIXERCONTROL_CONTROLTYPE_TREBLE:
        case MIXERCONTROL_CONTROLTYPE_VOLUME:
            return MIXDT_UNSIGNED;

        // List
        case MIXERCONTROL_CONTROLTYPE_MIXER:
        case MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT:
        case MIXERCONTROL_CONTROLTYPE_MUX:
        case MIXERCONTROL_CONTROLTYPE_SINGLESELECT:
            return MIXDT_BOOLEAN;

        // Meter
        case MIXERCONTROL_CONTROLTYPE_BOOLEANMETER:
            return MIXDT_BOOLEAN;
        case MIXERCONTROL_CONTROLTYPE_PEAKMETER:
        case MIXERCONTROL_CONTROLTYPE_SIGNEDMETER:
            return MIXDT_SIGNED;
        case MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER:
            return MIXDT_UNSIGNED;

        // Numbers
        case MIXERCONTROL_CONTROLTYPE_DECIBELS:
        case MIXERCONTROL_CONTROLTYPE_PERCENT:
        case MIXERCONTROL_CONTROLTYPE_SIGNED:
            return MIXDT_SIGNED;
        case MIXERCONTROL_CONTROLTYPE_UNSIGNED:
            return MIXDT_UNSIGNED;

        // Sliders
        case MIXERCONTROL_CONTROLTYPE_PAN:
        case MIXERCONTROL_CONTROLTYPE_QSOUNDPAN:
        case MIXERCONTROL_CONTROLTYPE_SLIDER:
            return MIXDT_SIGNED;

        // Switches
        case MIXERCONTROL_CONTROLTYPE_BOOLEAN:
        case MIXERCONTROL_CONTROLTYPE_BUTTON:
        case MIXERCONTROL_CONTROLTYPE_LOUDNESS:
        case MIXERCONTROL_CONTROLTYPE_MONO:
        case MIXERCONTROL_CONTROLTYPE_MUTE:
        case MIXERCONTROL_CONTROLTYPE_ONOFF:
        case MIXERCONTROL_CONTROLTYPE_STEREOENH:
            return MIXDT_BOOLEAN;

        // Time
        case MIXERCONTROL_CONTROLTYPE_MICROTIME:
        case MIXERCONTROL_CONTROLTYPE_MILLITIME:
            return MIXDT_UNSIGNED;

        default:
            return MIXDT_UNDEFINED;
    }

    // No man's land!
    return MIXDT_INVALID;
}


HRESULT MapMMRToHRESULT(MMRESULT dw)
{
    switch(dw)
    {
        case MMSYSERR_NOERROR: return S_OK;
        case MMSYSERR_ERROR: return MIX_E_MIXERERROR;
        case MMSYSERR_BADDEVICEID: return MIX_E_NOTFOUND;
        case MMSYSERR_NOTENABLED: return MIX_E_NOTENABLED;
        case MMSYSERR_ALLOCATED: return MIX_E_ALLOCATED ;
        case MMSYSERR_INVALHANDLE: return E_HANDLE;
        case MMSYSERR_NODRIVER: return MIX_E_NODRIVER;
        case MMSYSERR_NOMEM: return E_OUTOFMEMORY;
        case MMSYSERR_NOTSUPPORTED: return E_NOTIMPL;
        case MMSYSERR_BADERRNUM: return MIX_E_MIXERERROR;
        case MMSYSERR_INVALFLAG: return E_INVALIDARG;
        case MMSYSERR_INVALPARAM: return E_INVALIDARG;
        case MMSYSERR_HANDLEBUSY: return MIX_E_BUSY;
        case MMSYSERR_INVALIDALIAS: return MIX_E_INVALIDALIAS;
        case MMSYSERR_BADDB: return MIX_E_BADDB;
        case MMSYSERR_KEYNOTFOUND: return MIX_E_KEYNOTFOUND;
        case MMSYSERR_READERROR: return MIX_E_READERROR;
        case MMSYSERR_WRITEERROR: return MIX_E_WRITEERROR;
        case MMSYSERR_DELETEERROR: return MIX_E_DELETEERROR;
        case MMSYSERR_VALNOTFOUND: return MIX_E_NOTFOUND;
        case MMSYSERR_NODRIVERCB: return MIX_E_NODRIVERCB;
        case MMSYSERR_MOREDATA: return MIX_E_MIXERERROR;
    }

    return MIX_E_MIXERERROR;
}


/*
    We can load from an IStream or a filename (BSTR).
*/
HRESULT ValidateLoad(VARIANT v)
{
    HRESULT hr;

    if(v.vt == VT_BSTR) return S_OK;
    if(v.vt == VT_UNKNOWN)
    {
        IStream* ps = 0;

        if(!v.punkVal) return E_POINTER;

        if(FAILED(hr = v.punkVal->QueryInterface(IID_IStream, (void**)&ps)))
        {
            return hr;
        }

        ps->Release();
        ps = 0;
        return S_OK;
    }

    return E_INVALIDARG;
}


/*
    We can save to an IStream or a filename (BSTR).
*/
HRESULT ValidateSave(VARIANT v)
{
    HRESULT hr;

    if(v.vt == VT_BSTR) return S_OK;
    if(v.vt == VT_UNKNOWN)
    {
        IStream* ps = 0;

        if(!v.punkVal) return E_POINTER;

        if(FAILED(hr = v.punkVal->QueryInterface(IID_IStream, (void**)&ps)))
        {
            return hr;
        }

        ps->Release();
        ps = 0;
        return S_OK;
    }

    return E_INVALIDARG;
}


/*
    This function appends a child to the end of the specified parent.
    This function is special, though, because it will form the XML well.

    Without this function, the XML gets ugly:
    <LoveLine><Episode adsfasdfasdfad=""/></LoveLine>

    With this function, it's pretty:
    <LoveLine>
        <Episode asdfasdfadsf="">
        </Episode>
    </LoveLine>
*/
HRESULT XMLAppendChild(IXMLDOMDocument* pDoc, IXMLDOMNode* pNewParent, IXMLDOMNode* pNewChild)
{
    HRESULT hr;
    DWORD i;
    CCString ErrBuf;
    CCString sText;

    IXMLDOMNode* pNewOne = NULL;

    if(pNewParent == NULL || pNewChild == NULL)
    {
        return E_INVALIDARG;
    }

    DWORD dwParents = 1;// How many parents the NEW node has (parents the PARENT has + 1).
    dwParents = XMLGetParents(pNewParent) + 1;

    // append the first new line and tabs.
    sText = L"\r\n";

    for(i=1;i<dwParents;i++)
    {
        sText.cat(L"\t");
    }

    //if(FAILED(hr = XMLAppendText(pDoc, pNewParent, sText)))
    {
        //return E_FAxIL;
    }

    if(FAILED(hr = XMLAppendText(pDoc, pNewChild, sText)))
    {
        //return E_FAxIL;
    }

    // Now add it to the XML.
    if(FAILED(hr = pNewParent->appendChild(pNewChild, &pNewOne)))
    {
        return MIX_E_XMLERR;
    }

    sText = L"\r\n";

    for(i=1;i<dwParents - 1;i++)
    {
        sText.cat(L"\t");
    }

    if(FAILED(hr = XMLAppendText(pDoc, pNewParent, sText)))
    {
        //return E_FAxIL;
    }

    SAFE_RELEASE(pNewOne);

    return S_OK;
}


/*
    Returns the number of parents this node has.
*/
DWORD XMLGetParents(IXMLDOMNode* pNode)
{
    DWORD dwParents = 0;
    IXMLDOMNode* pParent = NULL;
    IXMLDOMNode* pOldParent = NULL;

    if(pNode == NULL)
    {
        return 0;
    }

    // Because we will release this when we're doing parents, we need to addref.
    pNode->AddRef();

    // Determine how many parents the node has.  For each parent, indent it one tab character.
    pOldParent = pNode;
    while(1)
    {
        pOldParent->get_parentNode(&pParent);
        SAFE_RELEASE(pOldParent);

        if(pParent == NULL) break;
        dwParents ++;
        pOldParent = pParent;
    }

    SAFE_RELEASE(pParent);

    return dwParents;
}


/*
    Appends text to the end of an element.
*/
HRESULT XMLAppendText(IXMLDOMDocument* pDoc, IXMLDOMNode* pNode, CCString& Text)
{
    IXMLDOMText* pText = NULL;
    IXMLDOMNode* pTextNode = NULL;
    IXMLDOMNode* pNewOne = NULL;
    HRESULT hr;

    if(pDoc == NULL || pNode == NULL)
    {
        return E_INVALIDARG;
    }

    if(FAILED(hr = pDoc->createTextNode(Text.bstr(), &pText)))
    {
        return MIX_E_XMLERR;
    }

    if(FAILED(hr = pText->QueryInterface(IID_IXMLDOMNode, (PVOID*)&pTextNode)))
    {
        SAFE_RELEASE(pText);
        return MIX_E_XMLERR;
    }

    // Now add it to the XML.
    if(FAILED(hr = pNode->appendChild(pTextNode, &pNewOne)))
    {
        SAFE_RELEASE(pTextNode);
        SAFE_RELEASE(pText);
        return MIX_E_XMLERR;
    }

    SAFE_RELEASE(pText);
    SAFE_RELEASE(pTextNode);
    SAFE_RELEASE(pNewOne);

    return S_OK;
}


/*
    Gets an interface to an element that matches the specified XPath criteria
*/
HRESULT XMLMatchElement(XMLEl** ppVal, XMLEl* pParent, PCWSTR wszFormat, ...)
{
    XMLNode* pNode = 0;
    HRESULT hr;
    va_list args;

    if(FAILED(pParent->QueryInterface(IID_IXMLDOMNode, (void**)&pNode)))
    {
        return MIX_E_XMLERR;
    }

    va_start(args, wszFormat);
    hr = XMLMatchElement(ppVal, pNode, wszFormat, args);
    va_end(args);

    SAFE_RELEASE(pNode);

    return hr;
}


/*
    Gets an interface to an element that matches the specified XPath criteria
*/
HRESULT XMLMatchElement(XMLEl** ppVal, XMLNode* pParent, PCWSTR wszFormat, ...)
{
    HRESULT hr;
    va_list args;

    va_start(args, wszFormat);
    hr = XMLMatchElement(ppVal, pParent, wszFormat, args);
    va_end(args);

    return hr;
}


/*
    Gets an interface to an element that matches the specified XPath criteria
*/
HRESULT XMLMatchElement(XMLEl** ppVal, XMLNode* pParent, PCWSTR wszFormat, va_list Args)
{
    CCString sQuery;
    XMLNode* pNode = 0;
    HRESULT hr;

    *ppVal = 0;

    sQuery.FormatvW(wszFormat, Args);

    if(FAILED(hr = pParent->selectSingleNode(sQuery.bstr(), &pNode)))
    {
        return MIX_E_XMLERR;
    }

    if(hr == S_FALSE)
    {
        // I know this isn't really an error, but the idea behind this function
        // is that we return an error code if it's not found.
        return MIX_E_XMLERR;
    }

    hr = pNode->QueryInterface(IID_IXMLDOMElement, (void**)ppVal);

    SAFE_RELEASE(pNode);

    return hr;
}


/*
    This does the same thing as the other function but takes an XMLNode as the parent.
*/
HRESULT XMLEnsureElementExists(XMLDoc* pDoc, XMLNode* pParent, CCString& Query, CCString& sName, XMLEl** pVal)
{
    XMLNode* pMatch = 0;
    HRESULT hr;

    // Validate args and initialize stuff
    if(!pDoc) return E_POINTER;
    if(!pParent) return E_POINTER;
    if(!pVal) return E_POINTER;

    *pVal = 0;

    // Try to select it.
    if(FAILED(hr = pParent->selectSingleNode(Query.bstr(), &pMatch)))
    {
        return hr;
    }

    if(!pMatch)
    {
        // It's not there - let's try to construct the library node ourselves.
        if(FAILED(hr = XMLNewChildElement(pDoc, pParent, sName, pVal)))
        {
            return hr;
        }

        return S_OK;
    }

    // We now have pMatch for sure.
    hr = pMatch->QueryInterface(IID_IXMLDOMElement, (void**)pVal);

    SAFE_RELEASE(pMatch);

    return hr;
}


/*
    This function will try very hard to stick a pointer to
    an element that matches the query string in pVal.
    
    It does this by testing to see whether it exists, 
    and if it does it just returns it.

    Otherwise, it creates the element named sName underneath
    the parent.
*/
HRESULT XMLEnsureElementExists(IXMLDOMDocument* pDoc, XMLEl* pParent,
                               CCString& Query, CCString& sName, XMLEl** pVal)
{
    XMLNode* pNode = 0;
    HRESULT hr;

    if(FAILED(pParent->QueryInterface(IID_IXMLDOMNode, (void**)&pNode)))
    {
        return MIX_E_XMLERR;
    }

    hr = XMLEnsureElementExists(pDoc, pNode, Query, sName, pVal);

    SAFE_RELEASE(pNode);

    return hr;
}


HRESULT XMLNewChildElement(XMLDoc* pDoc, XMLNode* pParent, CCString& sName, XMLEl** pVal)
{
    HRESULT hr;

    // It's not there - let's try to construct the library node ourselves.
    if(FAILED(hr = pDoc->createElement(sName.bstr(), pVal)))
    {
        return hr;
    }

    // Now insert the sucker in the document.
    if(FAILED(XMLAppendChild(pDoc, pParent, *pVal)))
    {
        SAFE_RELEASE(*pVal);
        return MIX_E_XMLERR;
    }

    return S_OK;
}


/*
    This function creates a new element underneath the given element unconditionally.
*/
HRESULT XMLNewChildElement(XMLDoc* pDoc, XMLEl* pParent, CCString& sName, XMLEl** pVal)
{
    XMLNode* pNode = 0;
    HRESULT hr;

    if(FAILED(pParent->QueryInterface(IID_IXMLDOMNode, (void**)&pNode)))
    {
        return MIX_E_XMLERR;
    }

    hr = XMLNewChildElement(pDoc, pNode, sName, pVal);

    SAFE_RELEASE(pNode);

    return hr;
}


HRESULT XMLGetAttribute(IXMLDOMElement* pNode, CCString& Name, CCString* pValue)
{
    VARIANT v;
    HRESULT hr;

    if(FAILED(hr = pNode->getAttribute(Name.bstr(), &v)))
    {
        return MIX_E_XMLERR;
    }

    // Doesn't exist
    if(hr == S_FALSE) return MIX_E_XMLERR;

    // Invalid datatype
    if(v.vt == VT_NULL) return MIX_E_XMLERR;

    *pValue = v.bstrVal;
    SysFreeString(v.bstrVal);

    return S_OK;
}


/*
    This function simply loads up an XML document and returns the library node.
    Since open and save BOTH open the XML document if it exists already, this
    function does the same thing for loading or saving.
*/
HRESULT XMLOpen(VARIANT vFile, XMLDoc** pDoc, XMLEl** pLibrary)
{
    HRESULT hr;
    VARIANT_BOOL bSuccess;

    *pDoc = 0;
    *pLibrary = 0;

    if(FAILED(hr = ValidateSave(vFile)))
    {
        return hr;
    }

    XMLNode* pDocNode = 0;

    // Create an XML document.
    if(FAILED(hr = CoCreateInstance(CLSID_DOMDocument, NULL,
        CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, (void**)pDoc)))
    {
        return MIX_E_NOXML;
    }

    // So that we can better serve you, load up the XML if
    // it already exists.  If not, that's OK.  We'll construct it up.
    (*pDoc)->load(vFile, &bSuccess);// We don't care much about success.

    // Find the mixerlibrary node (the root node).
    // If it's not there, then we have to stick one in there.
    if(FAILED(hr = (*pDoc)->QueryInterface(IID_IXMLDOMNode, (void**)&pDocNode)))
    {
        SAFE_RELEASE(*pDoc);
        return hr;
    }

    // Grab our MixerLibrary element.
    if(FAILED(hr = XMLEnsureElementExists(*pDoc, pDocNode,
        CCString(L"MixerLibrary"), CCString(L"MixerLibrary"),
        pLibrary)))
    {
        SAFE_RELEASE(pDocNode);
        SAFE_RELEASE(*pDoc);
        return hr;
    }

    SAFE_RELEASE(pDocNode);

	return S_OK;
}


/*
    Given an XML document adn parent (should be a MixerLibrary element),
    this function attempts to find a mixer node that matches the specified
    criteria, and if it can't find a suitable match, it optionally creates one.
*/
HRESULT XMLFindMixer(XMLDoc* pDoc, XMLEl* pLibrary, DWORD id, CCString& sName, XMLEl** pMixer, BOOL bCreate)
{
    HRESULT hr;

    // Find based on name
    if(FAILED(XMLMatchElement(pMixer, pLibrary, L"Mixer[@Name=\"%s\"]", (PCWSTR)sName)))
    {
        // Find the Destination element whose name attribute matches.
        if(FAILED(XMLMatchElement(pMixer, pLibrary, L"Mixer[@id=\"0x%08x\"]", id)))
        {
            // Not found!  Let's create it.
            if(bCreate == TRUE)
            {
                if(FAILED(hr = XMLNewChildElement(pDoc, pLibrary, CCString(L"Mixer"), pMixer)))
                {
                    return hr;
                }

                // It was created successfully; let's fix it all up.
                CCString Value;
                CCString Name;

                Name = L"Name";
                (*pMixer)->setAttribute(Name.bstr(), sName.variant());

                Name = L"id";
                Value.FormatW(L"0x%08x", id);
                (*pMixer)->setAttribute(Name.bstr(), Value.variant());

                return S_OK;
            }

            return MIX_E_XMLERR;
        }
    }

    return S_OK;
}


HRESULT XMLFindDestination(XMLDoc* pDoc, XMLEl* pLibrary, 
                           DWORD idMixer, CCString& sNameMixer, 
                           DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                           XMLEl** pDest, BOOL bCreate)
{
    HRESULT hr;
    XMLEl* pParent = 0;

    // Find the parent node.
    if(FAILED(XMLFindMixer(pDoc, pLibrary, idMixer, sNameMixer, &pParent, bCreate)))
    {
        return MIX_E_XMLERR;
    }

    hr = XMLFindDestination(pDoc, pParent, idDest, sNameDest, TypeDest, pDest, bCreate);

    SAFE_RELEASE(pParent);

    return hr;
}


HRESULT XMLFindDestination(XMLDoc* pDoc, XMLEl* pParent, 
                           DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                           XMLEl** pDest, BOOL bCreate)
{
    HRESULT hr;

    // Find the Destination element whose name attribute matches.
    if(FAILED(XMLMatchElement(pDest, pParent, L"Destination[@id=\"0x%08x\"]", idDest)))
    {
        // Find the destination element whose ID attribute matches
        if(FAILED(XMLMatchElement(pDest, pParent, L"Destination[@Name=\"%s\"]", (PCWSTR)sNameDest)))
        {
            // Find the destination element whose TYPE attribute matches
            //if(FAILED(XMLMatchElement(pDest, pParent, L"Destination[@Type=\"%s\"]", DestinationToString(TypeDest))))
            {
                // Not found!  Let's create it.
                if(bCreate == TRUE)
                {
                    if(FAILED(hr = XMLNewChildElement(pDoc, pParent, CCString(L"Destination"), pDest)))
                    {
                        return hr;
                    }

                    // It was created successfully; let's fix it all up.
                    CCString Value;
                    CCString Name;

                    Name = L"Name";
                    (*pDest)->setAttribute(Name.bstr(), sNameDest.variant());

                    Name = L"id";
                    Value.FormatW(L"0x%08x", idDest);
                    (*pDest)->setAttribute(Name.bstr(), Value.variant());

                    Name = L"Type";
                    Value = DestinationToString(TypeDest);
                    (*pDest)->setAttribute(Name.bstr(), Value.variant());

                    return S_OK;
                }

                return MIX_E_XMLERR;
            }
        }
    }

    return S_OK;
}


HRESULT XMLFindLine(XMLDoc* pDoc, XMLEl* pLibrary, 
                    DWORD idMixer, CCString& sNameMixer, 
                    DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                    DWORD idLine, CCString& sNameLine, MIX_LINE TypeLine, 
                    XMLEl** pLine, BOOL bCreate)
{
    HRESULT hr;
    XMLEl* pParent = 0;

    // Find the parent node.
    if(FAILED(XMLFindDestination(pDoc, pLibrary,
        idMixer, sNameMixer,
        idDest, sNameDest, TypeDest,
        &pParent, bCreate)))
    {
        return MIX_E_XMLERR;
    }

    hr = XMLFindLine(pDoc, pParent, idLine, sNameLine, TypeLine, pLine, bCreate);

    SAFE_RELEASE(pParent);

    return hr;
}


HRESULT XMLFindLine(XMLDoc* pDoc, XMLEl* pParent, 
                    DWORD idLine, CCString& sNameLine, MIX_LINE TypeLine, 
                    XMLEl** pLine, BOOL bCreate)
{
    HRESULT hr;

    // Find the Destination element whose name attribute matches.
    if(FAILED(XMLMatchElement(pLine, pParent, L"Line[@id=\"0x%08x\"]", idLine)))
    {
        // Find the destination element whose ID attribute matches
        if(FAILED(XMLMatchElement(pLine, pParent, L"Line[@Name=\"%s\"]", (PCWSTR)sNameLine)))
        {
            // Find the destination element whose TYPE attribute matches
            //if(FAILED(XMLMatchElement(pLine, pParent, L"Line[@Type=\"%s\"]", LineToString(TypeLine))))
            {
                // Not found!  Let's create it.
                if(bCreate == TRUE)
                {
                    if(FAILED(hr = XMLNewChildElement(pDoc, pParent, CCString(L"Line"), pLine)))
                    {
                        return hr;
                    }

                    // It was created successfully; let's fix it all up.
                    CCString Value;
                    CCString Name;

                    Name = L"Name";
                    (*pLine)->setAttribute(Name.bstr(), sNameLine.variant());

                    Name = L"id";
                    Value.FormatW(L"0x%08x", idLine);
                    (*pLine)->setAttribute(Name.bstr(), Value.variant());

                    Name = L"Type";
                    Value = LineToString(TypeLine);
                    (*pLine)->setAttribute(Name.bstr(), Value.variant());

                    return S_OK;
                }

                return MIX_E_XMLERR;
            }
        }
    }

    return S_OK;
}


/*
    This one only applies to controls who are beneath a line.
*/
HRESULT XMLFindControl(XMLDoc* pDoc, XMLEl* pLibrary, 
                       DWORD idMixer, CCString& sNameMixer, 
                       DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                       DWORD idLine, CCString& sNameLine, MIX_LINE TypeLine, 
                       DWORD idCtrl, CCString& sNameCtrl, MIX_CONTROL TypeCtrl,
                       XMLEl** p, BOOL bCreate)
{
    HRESULT hr;
    XMLEl* pParent = 0;

    // Find the parent node.
    if(FAILED(XMLFindLine(pDoc, pLibrary,
        idMixer, sNameMixer,
        idDest, sNameDest, TypeDest,
        idLine, sNameLine, TypeLine,
        &pParent, bCreate)))
    {
        return MIX_E_XMLERR;
    }

    hr = XMLFindControl(pDoc, pParent, idCtrl, sNameCtrl, TypeCtrl, p, bCreate);

    SAFE_RELEASE(pParent);

    return hr;
}


/*
    This one only applies to controls who are beneath a line.
*/
HRESULT XMLFindControl(XMLDoc* pDoc, XMLEl* pLibrary, 
                       DWORD idMixer, CCString& sNameMixer, 
                       DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                       DWORD idCtrl, CCString& sNameCtrl, MIX_CONTROL TypeCtrl,
                       XMLEl** p, BOOL bCreate)
{
    HRESULT hr;
    XMLEl* pParent = 0;

    // Find the parent node.
    if(FAILED(XMLFindDestination(pDoc, pLibrary,
        idMixer, sNameMixer,
        idDest, sNameDest, TypeDest,
        &pParent, bCreate)))
    {
        return MIX_E_XMLERR;
    }

    hr = XMLFindControl(pDoc, pParent, idCtrl, sNameCtrl, TypeCtrl, p, bCreate);

    SAFE_RELEASE(pParent);

    return hr;
}


HRESULT XMLFindControl(XMLDoc* pDoc, XMLEl* pParent, 
                       DWORD idCtrl, CCString& sNameCtrl, MIX_CONTROL TypeCtrl,
                       XMLEl** p, BOOL bCreate)
{
    HRESULT hr;

    // Find the Destination element whose name attribute matches.
    if(FAILED(XMLMatchElement(p, pParent, L"Control[@id=\"0x%08x\"]", idCtrl)))
    {
        // Find the destination element whose ID attribute matches
        if(FAILED(XMLMatchElement(p, pParent, L"Control[@Name=\"%s\"]", (PCWSTR)sNameCtrl)))
        {
            // Find the destination element whose TYPE attribute matches
            //if(FAILED(XMLMatchElement(p, pParent, L"Control[@Type=\"%s\"]", ControlToString(TypeCtrl))))
            {
                // Not found!  Let's create it.
                if(bCreate == TRUE)
                {
                    if(FAILED(hr = XMLNewChildElement(pDoc, pParent, CCString(L"Control"), p)))
                    {
                        return hr;
                    }

                    // It was created successfully; let's fix it all up.
                    CCString Value;
                    CCString Name;

                    Name = L"Name";
                    (*p)->setAttribute(Name.bstr(), sNameCtrl.variant());

                    Name = L"id";
                    Value.FormatW(L"0x%08x", idCtrl);
                    (*p)->setAttribute(Name.bstr(), Value.variant());

                    Name = L"Type";
                    Value = ControlToString(TypeCtrl);
                    (*p)->setAttribute(Name.bstr(), Value.variant());

                    return S_OK;
                }

                return MIX_E_XMLERR;
            }
        }
    }

    return S_OK;
}


/*
    Saves the changes to the document; doesn't free up anything.
*/
HRESULT XMLCommit(XMLDoc* pDoc, VARIANT vFile)
{
    HRESULT hr;

    // Save!
    if(FAILED(hr = pDoc->save(vFile)))
    {
        return hr;
    }

    return S_OK;
}


/*
    All this does is free up the document.  No changes are commited this way.
*/
HRESULT XMLClose(XMLDoc** pDoc)
{
    DSAFE_RELEASE(L"XMLClose()", *pDoc);
    return S_OK;
}

