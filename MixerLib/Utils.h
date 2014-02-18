

#pragma once


#include "MixerLib.h"


BOOL VariantIsNumber(VARIANT* p);
BOOL VariantIsString(VARIANT* p);


// On error, returns MIX?_INVALID
MIX_DESTINATION WinToMix_Destination(DWORD dw);
MIX_LINE        WinToMix_Line(DWORD dw);
MIX_CONTROL     WinToMix_Control(DWORD dw);
MIX_DATATYPE    WinToMix_DataType(DWORD dw);// Takes a MIXERCONTROL::dwControlType


// Return value is -1 if one was not found.
DWORD MixToWin_Destination(MIX_DESTINATION dw);
DWORD MixToWin_Line(MIX_LINE dw);
DWORD MixToWin_Control(MIX_CONTROL dw);

/*
    Uses a statically allocated buffer; no need to free the string.
*/
PCWSTR DestinationToString(MIX_DESTINATION x);
PCWSTR LineToString(MIX_LINE x);
PCWSTR ControlToString(MIX_CONTROL x);

HRESULT MapMMRToHRESULT(MMRESULT mmr);


/*
    XML Utilities
*/
typedef IXMLDOMDocument XMLDoc;
typedef IXMLDOMElement  XMLEl;
typedef IXMLDOMNode     XMLNode;

HRESULT ValidateLoad(VARIANT v);// Returns E_INVALIDARG if v is not valid for loading a mixerlibrary XML
HRESULT ValidateSave(VARIANT v);// Same thing.

HRESULT XMLAppendChild(XMLDoc* pDoc, XMLNode* pNewParent, XMLNode* pNewChild);
DWORD XMLGetParents(IXMLDOMNode* pNode);
HRESULT XMLAppendText(XMLDoc* pDoc, XMLNode* pNode, CCString& Text);
HRESULT XMLGetAttribute(IXMLDOMElement* pNode, CCString& Name, CCString* pValue);

HRESULT XMLNewChildElement(XMLDoc* pDoc, XMLEl* pParent, CCString& sName, XMLEl** pVal);
HRESULT XMLNewChildElement(XMLDoc* pDoc, XMLNode* pParent, CCString& sName, XMLEl** pVal);

HRESULT XMLEnsureElementExists(XMLDoc* pDoc, XMLEl* pParent, CCString& Query, CCString& sName, XMLEl** pVal);
HRESULT XMLEnsureElementExists(XMLDoc* pDoc, XMLNode* pParent, CCString& Query, CCString& sName, XMLEl** pVal);

HRESULT XMLMatchElement(XMLEl** ppVal, XMLEl* pParent, PCWSTR wszFormat, ...);
HRESULT XMLMatchElement(XMLEl** ppVal, XMLNode* pParent, PCWSTR wszFormat, ...);
HRESULT XMLMatchElement(XMLEl** ppVal, XMLNode* pParent, PCWSTR wszFormat, va_list Args);

/*
    Mixer-specific XML stuff
*/
HRESULT XMLOpen           (VARIANT vFile, XMLDoc** pDoc, XMLEl** pLibrary);
HRESULT XMLFindMixer      (XMLDoc* pDoc, XMLEl* pLibrary, 
                           DWORD idMixer, CCString& sNameMixer, 
                           XMLEl** pMixer, BOOL bCreate);

HRESULT XMLFindDestination(XMLDoc* pDoc, XMLEl* pParent, 
                           DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                           XMLEl** pDest, BOOL bCreate);
HRESULT XMLFindDestination(XMLDoc* pDoc, XMLEl* pLibrary, 
                           DWORD idMixer, CCString& sNameMixer, 
                           DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                           XMLEl** pDest, BOOL bCreate);

HRESULT XMLFindLine       (XMLDoc* pDoc, XMLEl* pParent, 
                           DWORD idLine, CCString& sNameLine, MIX_LINE TypeLine, 
                           XMLEl** pLine, BOOL bCreate);
HRESULT XMLFindLine       (XMLDoc* pDoc, XMLEl* pLibrary, 
                           DWORD idMixer, CCString& sNameMixer, 
                           DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                           DWORD idLine, CCString& sNameLine, MIX_LINE TypeLine, 
                           XMLEl** pLine, BOOL bCreate);

HRESULT XMLFindControl    (XMLDoc* pDoc, XMLEl* pParent, 
                           DWORD idCtrl, CCString& sNameCtrl, MIX_CONTROL TypeCtrl,
                           XMLEl** p, BOOL bCreate);
HRESULT XMLFindControl    (XMLDoc* pDoc, XMLEl* pLibrary, 
                           DWORD idMixer, CCString& sNameMixer, 
                           DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                           DWORD idLine, CCString& sNameLine, MIX_LINE TypeLine, 
                           DWORD idCtrl, CCString& sNameCtrl, MIX_CONTROL TypeCtrl,
                           XMLEl** p, BOOL bCreate);

HRESULT XMLFindControl    (XMLDoc* pDoc, XMLEl* pLibrary, 
                           DWORD idMixer, CCString& sNameMixer, 
                           DWORD idDest, CCString& sNameDest, MIX_DESTINATION TypeDest, 
                           DWORD idCtrl, CCString& sNameCtrl, MIX_CONTROL TypeCtrl,
                           XMLEl** p, BOOL bCreate);

HRESULT XMLCommit(XMLDoc* pDoc, VARIANT vFile);
HRESULT XMLClose(XMLDoc** pDoc);

