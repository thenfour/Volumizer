

#pragma once



class CCEXPORT CCMDIChild : public CCControl
{
    friend class CCMDIClient;

public:
    CCMDIChild();
    ~CCMDIChild();

    static long GetParam();

private:

    /*
        This is so we don't have more than one of these guys being
        created at the same time.
    */
    static long m_lRefCt;// How many instances are created.
    static BOOL m_bInitialized;
    static CRITICAL_SECTION m_csCreate;
    static long lParam;

    HRESULT Create(class CCMDIClient* pParent, const TCHAR* tszTitle, long lParam, RECT prect, RECT orect);
};


