// Mixers.h : Declaration of the CMixers


#ifndef __MIXERS_H_
#define __MIXERS_H_


#include "resource.h"       // main symbols
#include "CollectionNode.h"
#include "Mixer.h"


/////////////////////////////////////////////////////////////////////////////
// CMixers
class ATL_NO_VTABLE CMixers : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IMixers, &IID_IMixers, &LIBID_MIXERLIBLib>,
    public CCollectionBase<CMixer, IMixer, &IID_IMixer>
{
    public:
	    CMixers()
	    {
	    }

    HRESULT FinalConstruct();
    void FinalRelease();

    //DECLARE_REGISTRY_RESOURCEID(IDR_MIXERS)
    DECLARE_NOT_AGGREGATABLE(CMixers)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CMixers)
	    COM_INTERFACE_ENTRY(IMixers)
	    COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()

    // IMixers
    public:
		STDMETHOD(get_Item)(VARIANT i, IMixer** pVal);
		STDMETHOD(get__NewEnum)(IUnknown** pVal);
		STDMETHOD(get_Count)(long *pVal);
    
    public:
        HRESULT SaveMixers(IXMLDOMDocument* pDoc, IXMLDOMElement* pLibrary);
        HRESULT LoadMixers(XMLEl* pLibrary);

    private:
};

#endif //__MIXERS_H_
