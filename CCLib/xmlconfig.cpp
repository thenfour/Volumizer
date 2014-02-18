

#include "stdafx.h"
#include "xmlconfig.h"


CXMLConfig::CXMLConfig()
{
    m_pRoot = 0;
    m_pDoc = 0;
}


CXMLConfig::~CXMLConfig()
{
    Close();
}


HRESULT CXMLConfig::Close()
{
    SAFE_RELEASE(m_pRoot);
    SAFE_RELEASE(m_pDoc);

    return S_OK;
}


HRESULT CXMLConfig::Open(PCWSTR wszFile, PCWSTR wszRootElementName)
{
    HRESULT hr;
    VARIANT_BOOL bSuccess;
    CCString sFile;
    IXMLDOMNode* pRoot = 0;
    IXMLDOMNode* pNode = 0;// just a temp var
    CCString XPath;

    // Create an XML document.
    if(FAILED(hr = CoCreateInstance(CLSID_DOMDocument, NULL,
        CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, (void**)&m_pDoc)))
    {
        return hr;
    }

    sFile = wszFile;

    m_pDoc->load(sFile.variant(), &bSuccess);

    if(bSuccess == VARIANT_FALSE)
    {
        // problem
        return E_FAIL;
    }

    // Find the mixerlibrary node (the root node).
    // If it's not there, then we have to stick one in there.
    if(FAILED(hr = m_pDoc->QueryInterface(IID_IXMLDOMNode, (void**)&pRoot)))
    {
        SAFE_RELEASE(m_pDoc);
        return hr;
    }

    // Get the "root" node.
    XPath.FormatW(L"/%s", wszRootElementName);
    if(S_OK != (hr = pRoot->selectSingleNode(XPath.bstr(), &pNode)))
    {
        SAFE_RELEASE(pRoot);
        SAFE_RELEASE(m_pDoc);
        return E_FAIL;
    }

    if(FAILED(hr = pNode->QueryInterface(IID_IXMLDOMElement, (void**)&m_pRoot)))
    {
        SAFE_RELEASE(pRoot);
        SAFE_RELEASE(pNode);
        SAFE_RELEASE(m_pDoc);
        return hr;
    }

    SAFE_RELEASE(pNode);
    SAFE_RELEASE(pRoot);

	return S_OK;
}


HRESULT CXMLConfig::GetSetting(PCWSTR XPathElement, PCWSTR Attribute, CCString* psValue)
{
    IXMLDOMElement* pElement = 0;
    HRESULT hr;
    VARIANT v;

    // Get the element to which this query corresponds.
    if(FAILED(hr = GetElement(XPathElement, &pElement)))
    {
        return hr;
    }

    if(FAILED(hr = pElement->getAttribute(CCString(Attribute).bstr(), &v)))
    {
        return hr;
    }

    SAFE_RELEASE(pElement);

    if(v.vt != VT_BSTR)
    {
        return E_FAIL;
    }

    *psValue = v.bstrVal;

    SysFreeString(v.bstrVal);

    return S_OK;
}


HRESULT CXMLConfig::SetSetting(PCWSTR XPathElement, PCWSTR Attribute, CCString& sValue)
{
    IXMLDOMElement* pElement = 0;
    HRESULT hr;

    // Get the element to which this query corresponds.
    if(FAILED(hr = GetElement(XPathElement, &pElement)))
    {
        return hr;
    }

    if(FAILED(hr = pElement->setAttribute(CCString(Attribute).bstr(), sValue.variant())))
    {
        return hr;
    }

    SAFE_RELEASE(pElement);

    return S_OK;
}


HRESULT CXMLConfig::GetElement(PCWSTR XPath, IXMLDOMElement** pElement)
{
    HRESULT hr;
    IXMLDOMNode* pNode = 0;

    if(S_OK != (hr = m_pRoot->selectSingleNode(CCString(XPath).bstr(), &pNode)))
    {
        return E_FAIL;
    }

    // Get the element reference
    if(FAILED(hr = pNode->QueryInterface(IID_IXMLDOMElement, (void**)pElement)))
    {
        SAFE_RELEASE(pNode);
        return hr;
    }

    if(!pElement)
    {
        SAFE_RELEASE(pNode);
        return E_NOINTERFACE;
    }

    return S_OK;
}


IXMLDOMElement* CXMLConfig::GetRoot()
{
    return m_pRoot;
}



