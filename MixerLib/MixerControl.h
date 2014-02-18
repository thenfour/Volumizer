/*
    Mixer Controls are *ALWAYS* initialized by the parent, so there
    is no need for the old m_bInitialzied stuff.  That's due to the
    flaky design of the mixer APIs, not my own choice.
*/

// MixerControl.h : Declaration of the CMixerControl


#ifndef __MIXERCONTROL_H_
#define __MIXERCONTROL_H_


#include "resource.h"       // main symbols
#include "CollectionNode.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerControl
class ATL_NO_VTABLE CMixerControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IMixerControl,
    public IMixerControl2,
    public CCollectionItem
{
friend void GrabMixerValues(CMixerControl* pThis);
    public:
	    CMixerControl()
	    {
            m_pDest = 0;
            m_pLine = 0;
            m_nRawItems = 0;
            m_pRaw = 0;
            m_pVariants = 0;
            m_pStrings = 0;

            m_Type = MIXC_UNDEFINED;
            m_DataType = MIXDT_UNDEFINED;
            m_hMixer = 0;
	    }

    HRESULT FinalConstruct();
    void FinalRelease();

    void Init(HMIXER hMixer, MIXERCONTROL* pmc, MIXERLINE* pml, class CMixerDestination* pDest, class CMixerLine* pLine);
    class CMixerDestination* m_pDest;
    class CMixerLine* m_pLine;

    //DECLARE_REGISTRY_RESOURCEID(IDR_MIXERCONTROL)
    DECLARE_NOT_AGGREGATABLE(CMixerControl)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CMixerControl)
	    COM_INTERFACE_ENTRY(IMixerControl)
	    COM_INTERFACE_ENTRY(IMixerControl2)
    END_COM_MAP()

    // IMixerControl
    public:
	    STDMETHOD(Save)(/*[in]*/ VARIANT v);
	    STDMETHOD(Load)(/*[in]*/ VARIANT v);
	    STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal);
	    STDMETHOD(get_supports_text)(/*[out, retval]*/ BOOL *pVal);
	    STDMETHOD(GetText)(/*[in]*/ long id, /*[out]*/ BSTR* pVal);
	    STDMETHOD(CommitValuesBuffer)();
	    STDMETHOD(GetValuesBuffer)(/*[out]*/ VARIANT**, /*[out]*/ long* pc);
	    STDMETHOD(CommitCustomBuffer)();
	    STDMETHOD(GetCustomBuffer)(/*[out]*/ BYTE**pVal, /*[out]*/ long* pcb);
	    STDMETHOD(Refresh)();
	    STDMETHOD(get_steps)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(get_max)(/*[out, retval]*/ VARIANT *pVal);
	    STDMETHOD(get_min)(/*[out, retval]*/ VARIANT *pVal);
	    STDMETHOD(get_custom_size)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(get_datatype)(/*[out, retval]*/ MIX_DATATYPE *pVal);
	    STDMETHOD(get_channels)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(get_multiple)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(get_uniform)(/*[out, retval]*/ BOOL *pVal);
	    STDMETHOD(get_type)(/*[out, retval]*/ MIX_CONTROL *pVal);
	    STDMETHOD(GetMuxLine)(/*[in]*/ long id, /*[out, retval]*/ IMixerLine **pVal);
	    STDMETHOD(SetValuesUniformly)(/*[in]*/ VARIANT v);

    // IMixerControl2
    public:
	    STDMETHOD(get_mux_type)(/*[out, retval]*/ MIX_LINE *pVal);
	    STDMETHOD(put_mux_type)(/*[in]*/ MIX_LINE newVal);
	    STDMETHOD(get_mux_source)(/*[out, retval]*/ IMixerLine* *pVal);
	    STDMETHOD(put_mux_source)(/*[in]*/ IMixerLine* newVal);
	    STDMETHOD(get_mute)(/*[out, retval]*/ BOOL *pVal);
	    STDMETHOD(put_mute)(/*[in]*/ BOOL newVal);
	    STDMETHOD(get_balance)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(put_balance)(/*[in]*/ unsigned long newVal);
	    STDMETHOD(get_volume)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(put_volume)(/*[in]*/ unsigned long newVal);
	    STDMETHOD(get_short_name)(/*[out, retval]*/ BSTR *pVal);
	    STDMETHOD(get_controlid)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(get_owner)(/*[out, retval]*/ IMixerLine* *pVal);

    public:
	    STDMETHOD(get_fade)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(put_fade)(/*[in]*/ unsigned long newVal);
        BOOL IsMatch(MIX_CONTROL type);
        DWORD GetID();
        HRESULT SaveControl(XMLDoc* pDoc, XMLEl* pParent);
        HRESULT GetNode(XMLDoc* pDoc, XMLEl* pLibrary, XMLEl** p, BOOL bCreate);
        HRESULT LoadControl(XMLEl* pLibrary);

    private:

        /*
            Gets a pointer to the line associated with the
            currently selected mux item.
        */
        CComObject<CMixerLine>* _GetMuxSource();

        /*
            gets the index of the selected mux item.
            Returns -1 for no match.
        */
        long _GetMuxIndex();

        MIX_CONTROL m_Type;
        MIX_DATATYPE m_DataType;

        HMIXER m_hMixer;
        MIXERCONTROL m_mc;

        // We store the mixer line just in case we need to get
        // the information for later use.
        MIXERLINE m_ml;

        /*
            Buffers!  All these guys are just simple structures and
            shall be allocated with malloc().

            The buffers are the same memory throughout the lifetime
            of the control.
        */
        void _RefreshRaw();
        void _RefreshVariants();
        void _RefreshStrings();

        /*
            Since EVERY control has data associated with it, this is always used.

            This may be an array of:
            BYTE
            MIXERCONTROLDETAILS_BOOLEAN
            MIXERCONTROLDETAILS_SIGNED
            MIXERCONTROLDETAILS_UNSIGNED
        */
        BYTE* m_pRaw;// This is the buffer WE use for values, also for custom data.
        int m_nRawItems;// number of raw items in the array.  Since it's always supp
                        // osed to be the same, we don't set it to 0 when the array
                        // is freed.

        /*
            m_pVariants is not used for controls that don't use real values.
            It holds an array of VARIANTs that are exposed to the client
            application for MIXDT_SIGNED, MIXDT_UNSIGNED, and MIXDT_BOOLEAN.

            Custom controls do not use this, and it will always be 0 for them.
        */
        VARIANT* m_pVariants;

        /*
            We treat listtext stuff separately of any data associated with
            the control.  So if the control supports listtext, we will
            nab it and stick it in here.

            This array is only valid for multiple-item controls
            and its size is always the number of items.
        */
        MIXERCONTROLDETAILS_LISTTEXT* m_pStrings;// Used for the string data.

        /*
            Just does a good old fashioned 
            mixerSetControlDetails() on our raw buffer.
        */
        HRESULT _CommitRawBuffer();
};


#endif //__MIXERCONTROL_H_


