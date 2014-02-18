

#pragma once


#include "stdafx.h"
#include "../cclib/cccontrols.h"


class CVolumizerRegistrationInterface
{
public:
    virtual void DoRegistrationDialog(HWND hParent) = 0;
    virtual bool RegKeyValid() = 0;
};


// # of days for evaluation period
#define EVAL_PERIOD 30


class CVolumizerSplash
{
public:
    CVolumizerSplash();
    ~CVolumizerSplash();

    bool Show(int nDaysLeft, CVolumizerRegistrationInterface* pReg);

private:
    CCCustomWnd m_MainWnd;
    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    CCButton m_cOk;
    CCButton m_cEULA;
    CCButton m_cOrder;
    CCButton m_cClose;

    CCString m_sTimeLeft;
    RECT m_rcTimeLeft;
    //CCStatic m_cTimeLeft;

    CSimpleImage m_Image;

    bool m_bClose;
    bool m_bKeepGoing;

    CVolumizerRegistrationInterface* m_pReg;
};

//ID_HELP_REGISTER


