

#include <windows.h>
#include "global.h"
#include <msxml.h>


class CCEXPORT CXMLConfig
{
public:
    CXMLConfig();
    ~CXMLConfig();

    HRESULT Open(PCWSTR wszFile, PCWSTR wszRootElementName);
    HRESULT Close();
    HRESULT GetSetting(PCWSTR XPathElement, PCWSTR Attribute, CCString* psValue);
    HRESULT SetSetting(PCWSTR XPathElement, PCWSTR Attribute, CCString& sValue);
    IXMLDOMElement* GetRoot();

private:

    HRESULT GetElement(PCWSTR XPath, IXMLDOMElement** pElement);

    IXMLDOMDocument* m_pDoc;
    IXMLDOMElement* m_pRoot;
};

