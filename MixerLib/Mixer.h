// Mixer.h : Declaration of the CMixer


#ifndef __MIXER_H_
#define __MIXER_H_


#include "resource.h"       // main symbols
#include "CollectionBase.h"
#include "MixerDestinations.h"
#include "MixerLibCP.h"


#define MIXER_WNDCLASS   L"MixerLib_MixerNotification"


/////////////////////////////////////////////////////////////////////////////
// CMixer
class ATL_NO_VTABLE CMixer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IConnectionPointContainerImpl<CMixer>,
	public IMixer,
    public CCollectionItem,
    public CProxy_IMixerEvents< CMixer >
{
        friend class CMixerLine;
        friend class CMixerControl;
        friend class CMixerDestination;
    public:
	    CMixer()
	    {
            m_hNotification = 0;
            m_pOwner = 0;
            m_bInitialized = FALSE;
            m_pDestinations = 0;
            m_hMixer = 0;
	    }

    HRESULT FinalConstruct();
    void FinalRelease();

    /*
        Initializes this class and all child classes
        based on the mixer ID.
    */
    void Init(UINT uMixID, class CMixerLibrary* pOwner);
    class CMixerLibrary* m_pOwner;

    //DECLARE_REGISTRY_RESOURCEID(IDR_MIXER)
    DECLARE_NOT_AGGREGATABLE(CMixer)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CMixer)
	    COM_INTERFACE_ENTRY(IMixer)
    	COM_INTERFACE_ENTRY(IConnectionPointContainer)
    	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
    END_COM_MAP()

    BEGIN_CONNECTION_POINT_MAP(CMixer)
    CONNECTION_POINT_ENTRY(DIID__IMixerEvents)
    END_CONNECTION_POINT_MAP()

    // IMixer
    public:
	    STDMETHOD(get_destinations)(/*[out, retval]*/ IMixerDestinations **pVal);
	    STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal);
	    STDMETHOD(Save)(/*[in]*/ VARIANT v);
	    STDMETHOD(Load)(/*[in]*/ VARIANT v);
	    STDMETHOD(GetControl)(/*[in]*/ MIX_DESTINATION dest, /*[in]*/ MIX_LINE line, /*[in]*/ MIX_CONTROL control, /*[out, retval]*/ IMixerControl** pVal);
	    STDMETHOD(GetLine)(/*[in]*/ MIX_DESTINATION dest, /*[in]*/ MIX_LINE line, /*[out, retval]*/ IMixerLine** pVal);
	    STDMETHOD(GetDestination)(/*[in]*/ MIX_DESTINATION dest, /*[out, retval]*/ IMixerDestination** pVal);
	    STDMETHOD(get_destination_count)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(EnumDestinations)(/*[out, retval]*/ IEnumMixerDestinations **ppVal);
	    STDMETHOD(Refresh)();
	    STDMETHOD(get_owner)(/*[out, retval]*/ IMixerLibrary* *pVal);
	    STDMETHOD(get_version_minor)(/*[out, retval]*/ short *pVal);
	    STDMETHOD(get_version_major)(/*[out, retval]*/ short *pVal);
	    STDMETHOD(get_product)(/*[out, retval]*/ short *pVal);
	    STDMETHOD(get_manufacturer)(/*[out, retval]*/ short *pVal);

    public:
	    STDMETHOD(GetControlByID)(/*[in]*/ unsigned long ulId, /*[out]*/ IMixerControl** pVal);
	    STDMETHOD(GetLineByID)(/*[in]*/ unsigned long ulId, /*[out]*/ IMixerLine** pVal);
	    STDMETHOD(GetDestinationByID)(/*[in]*/ unsigned long ulId, /*[out]*/ IMixerDestination** pVal);
	    STDMETHOD(get_mixerid)(/*[out, retval]*/ DWORD *pVal);
        HMIXER GetMixer();
        CComObject<CMixerDestination>* GetDestination(MIX_DESTINATION dest);
        CComObject<CMixerLine>* GetLine(MIX_DESTINATION dest, MIX_LINE line);
        CComObject<CMixerControl>* GetControl(MIX_DESTINATION dest, MIX_LINE line, MIX_CONTROL control);

        HRESULT GetNode(XMLDoc* pDoc, XMLEl* pLibrary, XMLEl** p, BOOL bCreate);
        HRESULT SaveMixer(IXMLDOMDocument* pDoc, IXMLDOMElement* pLibrary);
        HRESULT LoadMixer(XMLEl* pLibrary);

    private:

        /*
            We set up a notification-only window to receive
            mixer change notifications.
        */
        HWND m_hNotification;
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        UINT m_uID;// Used to initialize.
        void EnsureInitialized();
        BOOL m_bInitialized;

        HMIXER m_hMixer;
        MIXERCAPS m_mc;

        CComObject<CMixerDestinations>* m_pDestinations;
};


#endif //__MIXER_H_

