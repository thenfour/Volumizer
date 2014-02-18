/*
    This template implements the nuts and bolts of an IEnumVARIANT interface
    for use in a COM collection object for compatibility with VB.

    Fortunately, the enumerator doesn't need to be much - just enumerates
    items in the object.

    The object that this class uses to enumerate must derive from the CEnum
    pure virtual class.
*/


#pragma once


#include <windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include "CollectionNode.h"


template<typename TNodeType, typename TEnumInterface, const GUID* TEnumIID,
         typename TItemInterface, const GUID* TItemIID>
class ATL_NO_VTABLE CCollectionEnum :
	public CComObjectRootEx<CComSingleThreadModel>,
    TEnumInterface
{
    public:
	    CCollectionEnum()
	    {
            m_pCurrent = 0;
            m_pEnumerator = 0;
	    }

        ~CCollectionEnum()
        {
        }

	    void SetEnumerator(CContainer<TNodeType>* pEnumerator)
	    {
            m_pEnumerator = pEnumerator;
            m_pCurrent = 0;
            m_pEnumerator->Reset();
	    }

        DECLARE_NOT_AGGREGATABLE(CCollectionEnum)
        DECLARE_GET_CONTROLLING_UNKNOWN()
    
        BEGIN_COM_MAP(CCollectionEnum)
	        COM_INTERFACE_ENTRY(TEnumInterface)
        END_COM_MAP()

        // IEnumVARIANT
        HRESULT STDMETHODCALLTYPE Next(unsigned long celt, 
            TItemInterface** rgvar, unsigned long* pceltFetched)
        {
            unsigned long i = 0;// iterator
            HRESULT hr = S_OK;

            for(i=0;i<celt;i++)
            {
                if(pceltFetched) *pceltFetched = i+1;

                m_pCurrent = m_pEnumerator->Next(m_pCurrent);
                if(m_pCurrent == 0)
                {
                    // We have reached the end of the list.
                    *pceltFetched = 0;
                    return S_FALSE;
                }

                if(FAILED(hr = m_pCurrent->QI(*TItemIID, (void**)&rgvar[i])))
                {
                    return hr;
                }
            }

            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE Skip(unsigned long celt)
        {
            HRESULT hr = S_OK;

            m_pCurrent = m_pEnumerator->Skip(m_pCurrent, celt);

            if(m_pCurrent == 0) hr = S_FALSE;

            return hr;
        }

        HRESULT STDMETHODCALLTYPE Reset()
        {
            m_pCurrent = m_pEnumerator->Reset();
            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE Clone(TEnumInterface** ppenum)
        {
            CComObject<CCollectionEnum<TNodeType, TEnumInterface, TEnumIID, TItemInterface, TItemIID> >* pNew;

            CComObject<CCollectionEnum<TNodeType, TEnumInterface, TEnumIID, TItemInterface, TItemIID> >::CreateInstance(&pNew);
            pNew->AddRef();

            pNew->SetEnumerator(m_pEnumerator);
            pNew->m_pCurrent = m_pCurrent;

            pNew->QueryInterface(*TEnumIID, (void**)ppenum);

            pNew->Release();

            return S_OK;
        }

        // The object that holds all our data.
        CContainer<TNodeType>* m_pEnumerator;

        // Our "current" thingy
        TNodeType* m_pCurrent;
};


template<typename TEnumInterface, const GUID* TEnumIID,
         typename TItemInterface, const GUID* TItemIID, typename TItemClass>
HRESULT CreateEnum(TEnumInterface** ppVal, CContainer<CCollectionNode<TItemClass> >* pContainer)
{
    HRESULT hr = S_OK;

    CComObject<CCollectionEnum<CCollectionNode<TItemClass>, TEnumInterface, TEnumIID, TItemInterface, TItemIID> >* pNew = 0;

    hr = CComObject<CCollectionEnum<CCollectionNode<TItemClass>, TEnumInterface, TEnumIID, TItemInterface, TItemIID> >::CreateInstance(&pNew);

    if(FAILED(hr))
    {
        return hr;
    }

    pNew->AddRef();
    pNew->SetEnumerator(pContainer);

    hr = pNew->QueryInterface(*TEnumIID, (void**)ppVal);

    pNew->Release();
    pNew = 0;

    return hr;
}



template<typename TNodeType>
class ATL_NO_VTABLE CCollectionEnumVARIANT :
	public CComObjectRootEx<CComSingleThreadModel>,
    IEnumVARIANT
{
    public:
	    CCollectionEnumVARIANT()
	    {
            m_pCurrent = 0;
            m_pEnumerator = 0;
	    }

        ~CCollectionEnumVARIANT()
        {
        }

	    void SetEnumerator(CContainer<TNodeType>* pEnumerator)
	    {
            m_pEnumerator = pEnumerator;
            m_pCurrent = 0;
            m_pEnumerator->Reset();
	    }

        DECLARE_NOT_AGGREGATABLE(CCollectionEnumVARIANT)
        DECLARE_GET_CONTROLLING_UNKNOWN()
    
        BEGIN_COM_MAP(CCollectionEnumVARIANT)
	        COM_INTERFACE_ENTRY(IEnumVARIANT)
        END_COM_MAP()

        // IEnumVARIANT
        HRESULT STDMETHODCALLTYPE Next(unsigned long celt, 
            VARIANT* rgvar, unsigned long* pceltFetched)
        {
            unsigned long i = 0;// iterator

            for(i=0;i<celt;i++)
            {
                if(pceltFetched) *pceltFetched = i+1;

                m_pCurrent = m_pEnumerator->Next(m_pCurrent);
                if(m_pCurrent == 0)
                {
                    // We have reached the end of the list.
                    *pceltFetched = 0;
                    return S_FALSE;
                }

                VariantInit(&rgvar[i]);
                rgvar[i].vt = VT_UNKNOWN;

                // Initialize the variant with the IUnknown pointer
                // from the item.
                m_pCurrent->CopyToVariant(&rgvar[i]);
            }

            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE Skip(unsigned long celt)
        {
            HRESULT hr = S_OK;

            m_pCurrent = m_pEnumerator->Skip(m_pCurrent, celt);

            if(m_pCurrent == 0) hr = S_FALSE;

            return hr;
        }

        HRESULT STDMETHODCALLTYPE Reset()
        {
            m_pCurrent = m_pEnumerator->Reset();
            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE Clone(IEnumVARIANT** ppenum)
        {
            CComObject<CCollectionEnumVARIANT<TNodeType> >* pNew;

            CComObject<CCollectionEnumVARIANT<TNodeType> >::CreateInstance(&pNew);
            pNew->AddRef();

            pNew->SetEnumerator(m_pEnumerator);
            pNew->m_pCurrent = m_pCurrent;

            pNew->QueryInterface(IID_IEnumVARIANT, (void**)ppenum);

            pNew->Release();

            return S_OK;
        }

        // The object that holds all our data.
        CContainer<TNodeType>* m_pEnumerator;

        // Our "current" thingy
        TNodeType* m_pCurrent;
};






