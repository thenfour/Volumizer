// MixerDestinations.h : Declaration of the CMixerDestinations


#ifndef __MIXERDESTINATIONS_H_
#define __MIXERDESTINATIONS_H_


#include "resource.h"       // main symbols
#include "CollectionNode.h"
#include "MixerDestination.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerDestinations
class ATL_NO_VTABLE CMixerDestinations : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IMixerDestinations, &IID_IMixerDestinations, &LIBID_MIXERLIBLib>,
    public CCollectionBase<CMixerDestination, IMixerDestination, &IID_IMixerDestination>
{
    public:
	    CMixerDestinations()
	    {
	    }

        HRESULT FinalConstruct();
        void FinalRelease();

        //DECLARE_REGISTRY_RESOURCEID(IDR_MIXERDESTINATIONS)
        DECLARE_NOT_AGGREGATABLE(CMixerDestinations)

        DECLARE_PROTECT_FINAL_CONSTRUCT()

        BEGIN_COM_MAP(CMixerDestinations)
	        COM_INTERFACE_ENTRY(IMixerDestinations)
	        COM_INTERFACE_ENTRY(IDispatch)
        END_COM_MAP()

        /*
            Searches the list for a destination that matches the
            criteria.
        */
        CComObject<CMixerDestination>* FindMatch(MIX_DESTINATION dest);
        HRESULT GetLineByID(DWORD dwID, IMixerLine** pVal);
        CComObject<CMixerControl>* GetControlByID(DWORD id);
        CComObject<CMixerDestination>* GetDestinationByID(DWORD id);

        HRESULT SaveDestinations(XMLDoc* pDoc, XMLEl* pMixer);
        HRESULT LoadDestinations(XMLEl* pLibrary);


    // IMixerDestinations
    public:
		STDMETHOD(get_Item)(VARIANT i, IMixerDestination** pVal);
		STDMETHOD(get__NewEnum)(IUnknown** pVal);
		STDMETHOD(get_Count)(long *pVal);
};

#endif //__MIXERDESTINATIONS_H_
