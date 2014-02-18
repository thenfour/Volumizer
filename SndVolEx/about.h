

#include "stdafx.h"
#include "cappsettings.h"
#include "../cclib/cccontrols.h"


class CVolumizerAbout
{
public:
    CVolumizerAbout();
    ~CVolumizerAbout();

    bool Entry(HWND hParent, CAppSettings& x);

private:
    CCCustomWnd m_MainWnd;
    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    CCButton m_cOk;
    CCEditBox m_cInfo;

    bool m_bKeepGoing;

    CSimpleImage m_Image;
    HBRUSH m_hbr;
};

//ID_HELP_REGISTER


