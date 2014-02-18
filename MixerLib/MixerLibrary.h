// MixerLibrary.h : Declaration of the CMixerLibrary

#ifndef __MIXERLIBRARY_H_
#define __MIXERLIBRARY_H_

#include "resource.h"       // main symbols
#include "Mixers.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerLibrary
class ATL_NO_VTABLE CMixerLibrary : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMixerLibrary, &CLSID_MixerLibrary>,
	public IMixerLibrary
{
    public:
	    CMixerLibrary()
	    {
            m_bInitialized = FALSE;
            m_pMixers = 0;
	    }

    HRESULT FinalConstruct();
    void FinalRelease();

    DECLARE_REGISTRY_RESOURCEID(IDR_MIXERLIBRARY)
    DECLARE_NOT_AGGREGATABLE(CMixerLibrary)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CMixerLibrary)
	    COM_INTERFACE_ENTRY(IMixerLibrary)
    END_COM_MAP()

    // IMixerLibrary
    public:
	    STDMETHOD(GetControl)(/*[in]*/ long idMixer, /*[in]*/ MIX_DESTINATION dest, /*[in]*/ MIX_LINE line, /*[in]*/ MIX_CONTROL control, /*[out, retval]*/ IMixerControl** pVal);
	    STDMETHOD(GetLine)(/*[in]*/ long idMixer, /*[in]*/ MIX_DESTINATION dest, /*[in]*/ MIX_LINE line, /*[out, retval]*/ IMixerLine** pVal);
	    STDMETHOD(GetDestination)(/*[in]*/ long idMixer, /*[in]*/ MIX_DESTINATION Dest, /*[out, retval]*/ IMixerDestination** pVal);
	    STDMETHOD(GetMixer)(/*[in]*/ long id, /*[out, retval]*/ IMixer** pVal);
	    STDMETHOD(get_mixer_count)(/*[out, retval]*/ long *pVal);
	    STDMETHOD(EnumMixers)(/*[out, retval]*/ IEnumMixers **ppVal);
	    STDMETHOD(Load)(/*[in]*/ VARIANT v);
	    STDMETHOD(Save)(/*[in]*/ VARIANT v);
	    STDMETHOD(get_mixers)(/*[out, retval]*/ IMixers **pVal);
	    STDMETHOD(Refresh)();

    public:
        CComObject<CMixer>* GetMixer(long id);
        CComObject<CMixerDestination>* GetDestination(long id, MIX_DESTINATION dest);
        CComObject<CMixerLine>* GetLine(long id, MIX_DESTINATION dest, MIX_LINE line);
        CComObject<CMixerControl>* GetControl(long id, MIX_DESTINATION dest, MIX_LINE line, MIX_CONTROL control);

    private:

        void EnsureInitialized();
        BOOL m_bInitialized;

        CComObject<CMixers>* m_pMixers;
};

#endif //__MIXERLIBRARY_H_

