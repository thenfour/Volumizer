// MixerLine.h : Declaration of the CMixerLine


#ifndef __MIXERLINE_H_
#define __MIXERLINE_H_


#include "resource.h"       // main symbols
#include "CollectionBase.h"
#include "MixerControls.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerLine
class ATL_NO_VTABLE CMixerLine : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IMixerLine,
    public IMixerLine2,
    public CCollectionItem
{
        friend class CMixerControl;
    public:
	    CMixerLine()
	    {
            m_pOwner = 0;
            m_bInitialized = FALSE;
            m_pControls = 0;
            m_hMixer = 0;
            m_dwDestID = 0;
            m_dwLineID = 0;
            m_Type = MIXL_UNDEFINED;
	    }

    HRESULT FinalConstruct();
    void FinalRelease();

    void Init(HMIXER hMixer, DWORD dwDestIndex, DWORD dwLineIndex, class CMixerDestination* pOwner);
    class CMixerDestination* m_pOwner;

    //DECLARE_REGISTRY_RESOURCEID(IDR_MIXERLINE)
    DECLARE_NOT_AGGREGATABLE(CMixerLine)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CMixerLine)
	    COM_INTERFACE_ENTRY(IMixerLine)
	    COM_INTERFACE_ENTRY(IMixerLine2)
    END_COM_MAP()

    // IMixerLine
    public:
	    STDMETHOD(Save)(/*[in]*/ VARIANT v);
	    STDMETHOD(Load)(/*[in]*/ VARIANT v);
	    STDMETHOD(GetControl)(/*[in]*/ MIX_CONTROL control, /*[out, retval]*/ IMixerControl** pVal);
	    STDMETHOD(get_control_count)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(EnumControls)(/*[out, retval]*/ IEnumMixerControls **ppVal);
	    STDMETHOD(get_controls)(/*[out, retval]*/ IMixerControls **pVal);
	    STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal);
	    STDMETHOD(get_type)(/*[out, retval]*/ MIX_LINE *pVal);
	    STDMETHOD(get_short_name)(/*[out, retval]*/ BSTR *pVal);
	    STDMETHOD(get_lineid)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(get_channels)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(get_owner)(/*[out, retval]*/ IMixerDestination* *pVal);
	    STDMETHOD(RefreshLine)();

    // IMixerLine2
    public:
	    STDMETHOD(get_mute)(/*[out, retval]*/ BOOL *pVal);
	    STDMETHOD(put_mute)(/*[in]*/ BOOL newVal);
	    STDMETHOD(get_balance)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(put_balance)(/*[in]*/ unsigned long newVal);
	    STDMETHOD(get_volume)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(put_volume)(/*[in]*/ unsigned long newVal);
	    STDMETHOD(get_mux_type)(/*[out, retval]*/ MIX_LINE *pVal);
	    STDMETHOD(put_mux_type)(/*[in]*/ MIX_LINE newVal);
	    STDMETHOD(get_mux_source)(/*[out, retval]*/ IMixerLine* *pVal);
	    STDMETHOD(put_mux_source)(/*[in]*/ IMixerLine* newVal);

    public:
	    STDMETHOD(get_fade)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(put_fade)(/*[in]*/ unsigned long newVal);
	    STDMETHOD(GetControlByID)(/*[in]*/ unsigned long ulId, /*[out]*/ IMixerControl** pVal);
        CComObject<CMixerControl>* GetControl(MIX_CONTROL control);
        CComObject<CMixerControl>* GetControlByID(DWORD id);
        BOOL IsMatch(MIX_LINE line);
        DWORD GetLineID();
        HRESULT SaveLine(XMLDoc* pDoc, XMLEl* pParent);
        HRESULT GetNode(XMLDoc* pDoc, XMLEl* pLibrary, XMLEl** p, BOOL bCreate);
        HRESULT LoadLine(XMLEl* pLibrary);

    private:

        MIX_LINE m_Type;

        HRESULT EnsureInitialized();

        BOOL m_bInitialized;
        DWORD m_dwDestID;// this and m_dwLineID are just copies of what
        DWORD m_dwLineID;// is passed into Init();

        MIXERLINE m_ml;
        HMIXER m_hMixer;

        CComObject<CMixerControls>* m_pControls;
};

#endif //__MIXERLINE_H_
