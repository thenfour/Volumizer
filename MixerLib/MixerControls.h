// MixerControls.h : Declaration of the CMixerControls


#ifndef __MIXERCONTROLS_H_
#define __MIXERCONTROLS_H_


#include "resource.h"       // main symbols
#include "CollectionBase.h"
#include "MixerControl.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerControls
class ATL_NO_VTABLE CMixerControls : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IMixerControls, &IID_IMixerControls, &LIBID_MIXERLIBLib>,
    public CCollectionBase<CMixerControl, IMixerControl, &IID_IMixerControl>
{
    public:
	    CMixerControls()
	    {
	    }

    HRESULT FinalConstruct();
    void FinalRelease();

    //DECLARE_REGISTRY_RESOURCEID(IDR_MIXERCONTROLS)
    DECLARE_NOT_AGGREGATABLE(CMixerControls)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CMixerControls)
	    COM_INTERFACE_ENTRY(IMixerControls)
	    COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()

    /*
        Searches the list for a destination that matches the
        criteria.
    */
    CComObject<CMixerControl>* FindMatch(MIX_CONTROL type);
    CComObject<CMixerControl>* GetControlByID(DWORD id);
    HRESULT SaveControls(XMLDoc* pDoc, XMLEl* pLine);
    HRESULT LoadControls(XMLEl* pLibrary);

    // IMixerControls
    public:
		STDMETHOD(get_Item)(VARIANT i, IMixerControl** pVal);
		STDMETHOD(get__NewEnum)(IUnknown** pVal);
		STDMETHOD(get_Count)(long *pVal);
};

#endif //__MIXERCONTROLS_H_
