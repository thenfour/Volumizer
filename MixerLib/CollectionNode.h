

#pragma once


/*
    Collection item classes must inherit from this class, so that they are
    forced to have a GetStringKey() function.
*/
class CCollectionItem
{
public:
    virtual HRESULT GetStringKey(BSTR* pstr)
    {
        *pstr = SysAllocString(L"");
        return S_OK;
    }
};


/*
    This templated class is used by CCollectionBase.
    This class will store an IUnknown and IBlahClass of 1 node
    in the collection.

    The Child class must inherit CCollectionItem
*/
template<typename TChildClass>
class CCollectionNode
{
public:
    IUnknown* pUnk;
    CComObject<TChildClass>* pThis;

    CCollectionNode<TChildClass>* pNext;
    CCollectionNode<TChildClass>* pPrev;

    int cmp(CCollectionNode<TChildClass>& c)
    {
        BSTR wsz1;
        BSTR wsz2;
        int i;

        pThis->GetStringKey(&wsz1);
        c.pThis->GetStringKey(&wsz2);

        i = wcsicmp(wsz1, wsz2);

        SysFreeString(wsz1);
        SysFreeString(wsz2);

        return i;
    }

    HRESULT CopyToVariant(VARIANT* pOut)
    {
        if(pUnk)
        {
            VariantInit(pOut);
            pOut->vt = VT_UNKNOWN;
            return this->pUnk->QueryInterface(IID_IUnknown, (void**)&pOut->punkVal);
        }

        return E_POINTER;
    }

    HRESULT QI(REFIID iid, void** pp)
    {
        return this->pThis->QueryInterface(iid, pp);
    }
};

