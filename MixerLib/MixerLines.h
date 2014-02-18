// MixerLines.h : Declaration of the CMixerLines


#ifndef __MIXERLINES_H_
#define __MIXERLINES_H_


#include "resource.h"       // main symbols
#include "CollectionNode.h"
#include "MixerLine.h"


/////////////////////////////////////////////////////////////////////////////
// CMixerLines
class ATL_NO_VTABLE CMixerLines : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IMixerLines, &IID_IMixerLines, &LIBID_MIXERLIBLib>,
    public CCollectionBase<CMixerLine, IMixerLine, &IID_IMixerLine>
{
    public:
	    CMixerLines()
	    {
	    }

    HRESULT FinalConstruct();
    void FinalRelease();

    //DECLARE_REGISTRY_RESOURCEID(IDR_MIXERLINES)
    DECLARE_NOT_AGGREGATABLE(CMixerLines)

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CMixerLines)
	    COM_INTERFACE_ENTRY(IMixerLines)
	    COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()

    /*
        Searches the list for a destination that matches the
        criteria.
    */
    CComObject<CMixerLine>* FindMatch(MIX_LINE line);
    CComObject<CMixerLine>* GetLineByID(DWORD dwID);
    CComObject<CMixerControl>* GetControlByID(DWORD id);

    HRESULT SaveLines(XMLDoc* pDoc, XMLEl* pDest);
    HRESULT LoadLines(XMLEl* pLibrary);

    // IMixerLines
    public:
		STDMETHOD(get_Item)(VARIANT i, IMixerLine** pVal);
		STDMETHOD(get__NewEnum)(IUnknown** pVal);
		STDMETHOD(get_Count)(long *pVal);
};

#endif //__MIXERLINES_H_
