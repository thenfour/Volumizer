// MixerDestination.h : Declaration of the CMixerDestination


#ifndef __MIXERDESTINATION_H_
#define __MIXERDESTINATION_H_


#include "resource.h"       // main symbols
#include "CollectionBase.h"
#include "MixerLines.h"
#include "MixerControls.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerDestination
class ATL_NO_VTABLE CMixerDestination : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IMixerDestination,
    public IMixerLine,
    public IMixerLine2,
    public CCollectionItem
{
        friend class CMixerLine;
        friend class CMixerControl;
    public:
	    CMixerDestination()
	    {
            m_pOwner = 0;
            m_bInitialized = FALSE;
            m_hMixer = 0;
            m_pControls = 0;
            m_pLines = 0;
            m_Type = MIXD_UNDEFINED;
	    }

    HRESULT FinalConstruct();
    void FinalRelease();

    void Init(HMIXER hMixer, unsigned int uDestID, class CMixer* pOwner);
    class CMixer* m_pOwner;

    //DECLARE_REGISTRY_RESOURCEID(IDR_MIXERDESTINATION)
    DECLARE_NOT_AGGREGATABLE(CMixerDestination)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CMixerDestination)
	    COM_INTERFACE_ENTRY(IMixerDestination)
	    COM_INTERFACE_ENTRY(IMixerLine)
	    COM_INTERFACE_ENTRY(IMixerLine2)
    END_COM_MAP()

    // IMixerDestination
    public:
	    STDMETHOD(GetControl)(/*[in]*/ MIX_CONTROL control, /*[out, retval]*/ IMixerControl** pVal);
	    STDMETHOD(GetLineControl)(/*[in]*/ MIX_LINE line, /*[in]*/ MIX_CONTROL control, /*[out, retval]*/ IMixerControl** pVal);
	    STDMETHOD(GetLine)(/*[in]*/ MIX_LINE line, /*[out, retval]*/ IMixerLine** pVal);
	    STDMETHOD(get_line_count)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(EnumLines)(/*[out, retval]*/ IEnumMixerLines** ppVal);
	    STDMETHOD(get_lines)(/*[out, retval]*/ IMixerLines **pVal);
	    STDMETHOD(get_type_destination)(/*[out, retval]*/ MIX_DESTINATION *pVal);
	    STDMETHOD(get_owner)(/*[out, retval]*/ IMixer* *pVal);

    // IMixerLine
    public:
	    STDMETHOD(get_control_count)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal);
        STDMETHOD(get_controls)(/*[out, retval]*/ IMixerControls **pVal);
	    STDMETHOD(EnumControls)(/*[out, retval]*/ IEnumMixerControls **ppVal);
	    STDMETHOD(Save)(/*[in]*/ VARIANT v);
	    STDMETHOD(Load)(/*[in]*/ VARIANT v);
	    STDMETHOD(get_type)(/*[out, retval]*/ MIX_LINE *pVal);
	    STDMETHOD(get_short_name)(/*[out, retval]*/ BSTR *pVal);
	    STDMETHOD(get_lineid)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(get_channels)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(get_owner)(/*[out, retval]*/ IMixerDestination* *pVal);
	    STDMETHOD(RefreshLine)();
	    STDMETHOD(GetControlByID)(/*[in]*/ unsigned long ulId, /*[out]*/ IMixerControl** pVal);

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
	    STDMETHOD(GetLineControlByID)(/*[in]*/ unsigned long ulId, /*[out]*/ IMixerControl** pVal);
	    STDMETHOD(GetLineByID)(/*[in]*/ unsigned long ulId, /*[out]*/ IMixerLine** pVal);
	    STDMETHOD(Refresh)();

    public:
	    STDMETHOD(get_fade)(/*[out, retval]*/ unsigned long *pVal);
	    STDMETHOD(put_fade)(/*[in]*/ unsigned long newVal);
	    STDMETHOD(LoadDestination)(/*[in]*/ VARIANT v);
	    STDMETHOD(SaveDestination)(/*[in]*/ VARIANT v);
        CComObject<CMixerControl>* GetLineControl(MIX_LINE line, MIX_CONTROL control);
        CComObject<CMixerLine>* GetLine(MIX_LINE line);
        CComObject<CMixerControl>* GetControl(MIX_CONTROL control);

        BOOL IsMatch(MIX_DESTINATION);
        CComObject<CMixerLine>* GetLineByID(DWORD dwLineID);
        DWORD GetLineID();

        CComObject<CMixerControl>* GetControlByID(DWORD id);
        HRESULT SaveDestination(XMLDoc* pDoc, XMLEl* pParent);
        HRESULT SaveLine(XMLDoc* pDoc, XMLEl* pParent);

        HRESULT GetNode(XMLDoc* pDoc, XMLEl* pLibrary, XMLEl** p, BOOL bCreate);
        HRESULT LoadDestination(XMLEl* pParent);
        HRESULT LoadLine(XMLEl* pParent);

    private:

        MIX_DESTINATION m_Type;

        void EnsureInitialized();
        BOOL m_bInitialized;
        UINT m_uDestID;

        HMIXER m_hMixer;
        MIXERLINE m_ml;

        CComObject<CMixerLines>* m_pLines;
        CComObject<CMixerControls>* m_pControls;
};

#endif //__MIXERDESTINATION_H_


