

#pragma once


#include "..\\CCLib\\LinkedList.h"
#include "Utils.h"// For VariantIsNumber() etc.
#include "CollEnum.h"// For CCollEnum<>
#include "CollectionNode.h"


/*
    Collection classes inherit from this class.  The requirements are that
    the child class must inherit from CCollectionItem (of course).

    The collection class must also be sure to call _ReleaseCollection()
    to free this class up - typically in FinalRelease()
*/
template<typename TChildClass, typename TChildInterface, const GUID* TChildIID>
class CCollectionBase
{
    public:
        void _ReleaseCollection()
        {
            _FreeList();
        }

		STDMETHOD(_get_Item_Index)(VARIANT i, TChildInterface** pVal)
        {
            CCollectionNode<TChildClass>* pCurrent = 0;// The object that we're gonna return

            if(!pVal) return E_POINTER;
            if(i.vt & VT_BYREF) return E_INVALIDARG;
            if(VariantIsNumber(&i) == FALSE) return E_INVALIDARG;

            // work on index basis.
            pCurrent = m_List.Item(i.lVal - 1);

            if(pCurrent)
            {
                return pCurrent->pUnk->QueryInterface(*TChildIID, (void**)pVal);
            }

            // Wasn't found.
            return E_INVALIDARG;
        }

		STDMETHOD(_get_Item_String)(VARIANT i, IMixer** pVal)
        {
            CCollectionNode<TChildClass>* pCurrent = 0;// The object that we're gonna return
            VARIANT vList;// Variant that we construct from list items.

            if(!pVal) return E_POINTER;
            if(i.vt & VT_BYREF) return E_INVALIDARG;
            if(VariantIsString(&i) == FALSE) return E_INVALIDARG;

            VariantInit(&vList);
            vList.vt = VT_BSTR;

            // We know it's a string, so let's loop and try to find the item.
            pCurrent = m_List.m_pRoot;

            while(pCurrent)
            {
                // Get the name.
                pCurrent->pThis->GetStringKey(&vList.bstrVal);

                // Compare them.
                if(VarCmp(&i, &vList, 0) == VARCMP_EQ)
                {
                    SysFreeString(vList.bstrVal);
                    return pCurrent->pThis->QueryInterface(*TChildIID, (void**)pVal);
                }

                SysFreeString(vList.bstrVal);

                pCurrent = pCurrent->pNext;
            }

            // Not found.
            return E_INVALIDARG;
        }

		STDMETHOD(_get__NewEnum)(IUnknown** pVal)
        {
            if(!pVal) return E_POINTER;

            CComObject<CCollectionEnumVARIANT<CCollectionNode<TChildClass> > >* pNew;

            CComObject<CCollectionEnumVARIANT<CCollectionNode<TChildClass> > >::CreateInstance(&pNew);
            pNew->AddRef();

            pNew->SetEnumerator(&m_List);
            pNew->QueryInterface(IID_IUnknown, (void**)pVal);

            pNew->Release();
	        return S_OK;
        }

		STDMETHOD(_get_Count)(long *pVal)
        {
            if(!pVal) return E_POINTER;
            *pVal = m_List.Count();
            return S_OK;
        }

        void _FreeList()
        {
            CCollectionNode<TChildClass>* pCurrent;

            while(m_List.m_pRoot)
            {
                pCurrent = m_List.m_pRoot;
                m_List.Remove(m_List.m_pRoot);
                pCurrent->pThis->Release();
                pCurrent->pUnk->Release();
                delete pCurrent;
            }
        }

        CCollectionNode<TChildClass>* _NewItem()
        {
            CCollectionNode<TChildClass>* pNew = new CCollectionNode<TChildClass>;

            CComObject<TChildClass>::CreateInstance(&pNew->pThis);
            pNew->pThis->AddRef();

            pNew->pThis->QueryInterface(IID_IUnknown, (void**)&pNew->pUnk);

            m_List.Insert(pNew);

            return pNew;
        }

        CLinkedList< CCollectionNode<TChildClass> >* _GetList()
        {
            return &m_List;
        }


    protected:
        CLinkedList< CCollectionNode<TChildClass> > m_List;
};

