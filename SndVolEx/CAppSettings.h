/*
    I made this stuff inline so it could be simply #included into any project
    and used.
*/

#pragma once


#include "../mixerlib/mixerlib.h"
#include <shlwapi.h>


#define XOR_TRANSLATOR_BYTE 0xD6
#define MAX_ORG_LEN 50
#define MAX_NAME_LEN 50
#define MAX_KEY_LEN 16


inline void TranslateData(BYTE* p, size_t nSizeBytes)
{
    while(nSizeBytes)
    {
        *p ^= XOR_TRANSLATOR_BYTE * nSizeBytes;
        p++;
        nSizeBytes--;
    }
}


struct CAppSettingsData
{
    BOOL m_bAdvancedView;
    BOOL m_bCenter;

    WINDOWPLACEMENT m_wp;
    BOOL m_bAlwaysOnTop;

    // The currently selected destination
    DWORD m_dwDestID;

    // the date when this software was installed.
    SYSTEMTIME m_InstallDate;
    char m_szRegKey[MAX_KEY_LEN];

    MIX_DESTINATION m_Type;

    // Currently selected Mixer Device
    DWORD m_dwMixerID;

    WCHAR m_szName[MAX_NAME_LEN];
    WCHAR m_szOrganization[MAX_ORG_LEN];
};

inline void LoadDefaultAppSettingContactInfo(CAppSettingsData* pDat)
{
    lstrcpyW(pDat->m_szName, L"Unregistered User");
    pDat->m_szOrganization[0] = 0;
}

inline void LoadDefaultAppSettings(CAppSettingsData* pDat)
{
    pDat->m_bAlwaysOnTop = FALSE;
    pDat->m_bCenter = TRUE;

    pDat->m_wp.flags = 0;
    pDat->m_wp.ptMaxPosition.x = 0;
    pDat->m_wp.ptMaxPosition.y = 0;
    pDat->m_wp.ptMinPosition.x = 0;
    pDat->m_wp.ptMinPosition.y = 0;
    pDat->m_wp.rcNormalPosition.top = 0;
    pDat->m_wp.rcNormalPosition.left=0;
    pDat->m_wp.rcNormalPosition.bottom = 0;
    pDat->m_wp.rcNormalPosition.right = 0;
    pDat->m_wp.length = sizeof(pDat->m_wp);
    pDat->m_wp.showCmd = SW_SHOWNORMAL;

    pDat->m_dwDestID = 0;
    pDat->m_Type = MIXD_SPEAKERS;

    pDat->m_dwMixerID = 0;

    pDat->m_bAdvancedView = FALSE;

    pDat->m_InstallDate.wDay = 1;
    pDat->m_InstallDate.wDayOfWeek = 1;
    pDat->m_InstallDate.wHour = 1;
    pDat->m_InstallDate.wMilliseconds = 1;
    pDat->m_InstallDate.wMinute = 1;
    pDat->m_InstallDate.wMonth = 1;
    pDat->m_InstallDate.wSecond = 1;
    pDat->m_InstallDate.wYear = 1990;

    pDat->m_szRegKey[0] = 0;
}


class CAppSettings
{
public:
    CAppSettings() :
        m_bAdvancedView(m_dat.m_bAdvancedView),
        m_bCenter(m_dat.m_bCenter),
        m_wp(m_dat.m_wp),
        m_bAlwaysOnTop(m_dat.m_bAlwaysOnTop),
        m_dwDestID(m_dat.m_dwDestID),
        m_InstallDate(m_dat.m_InstallDate),
        m_Type(m_dat.m_Type),
        m_szRegKey(m_dat.m_szRegKey),
        m_dwMixerID(m_dat.m_dwMixerID),
        m_szName(m_dat.m_szName),
        m_szOrganization(m_dat.m_szOrganization),
        m_bEncrypted(false)
    {LoadDefaults();}

    ~CAppSettings(){}

    bool ExistsInRegistry()
    {
        bool r = false;
        HKEY hKey = 0;
        if(ERROR_SUCCESS == RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\OneLightVolumizer\\Settings",
            0, READ_CONTROL | KEY_QUERY_VALUE, &hKey))
        {
            DWORD dwSentinel = 0;
            DWORD dwSize = sizeof(dwSentinel);
            LONG lr = 0;

            lr = RegQueryValueExW(hKey, NULL, 0, 0, (BYTE*)&dwSentinel, &dwSize);
            if((lr == ERROR_SUCCESS) || (lr == ERROR_MORE_DATA))
            {
                r = true;
            }

            RegCloseKey(hKey);
        }
        return r;
    }

    void GetSettings()
    {
        HKEY hKey = 0;

        LoadDefaults();

        if(ERROR_SUCCESS == RegOpenKeyExW(HKEY_CURRENT_USER,
            L"Software\\OneLightVolumizer\\Settings", 0,
            KEY_QUERY_VALUE, &hKey))
        {
            DWORD dwSize = sizeof(m_dat);
            Encrypt();
            RegQueryValueExW(hKey, NULL, 0, 0, (BYTE*)&m_dat, &dwSize);
            RegCloseKey(hKey);
            // decrypt it.
            Decrypt();
        }

        return;
    }

    void SaveSettings()
    {
        HKEY hKey = 0;

        if(ERROR_SUCCESS == RegCreateKeyExW(HKEY_CURRENT_USER,
            L"Software\\OneLightVolumizer\\Settings", 0, 0, 0, 
            KEY_SET_VALUE, 0, &hKey, 0))
        {
            Encrypt();
            RegSetValueExW(hKey,NULL, 0, REG_BINARY, (BYTE*)&m_dat, sizeof(m_dat));
            RegCloseKey(hKey);
            Decrypt();
        }

        return;
    }

    void LoadDefaultContactInfo()
    {
        Decrypt();
        LoadDefaultAppSettingContactInfo(&m_dat);
    }

    void LoadDefaults()
    {
        Decrypt();
        LoadDefaultAppSettings(&this->m_dat);
    }

    // call this to fill in the default settings for a new installaiton
    void InitInstallation()
    {
        m_bEncrypted = false;
        LoadDefaultAppSettings(&this->m_dat);
        GetLocalTime(&m_dat.m_InstallDate);
    }

    void SetKey(const char* sz)
    {
        StrCpyNA(m_dat.m_szRegKey, sz, MAX_KEY_LEN);
        TranslateData((BYTE*)&(m_dat.m_szRegKey[0]), sizeof(m_dat.m_szRegKey));
    }

    void SetName(const WCHAR* wsz)
    {
        StrCpyNW(m_dat.m_szName, wsz, MAX_NAME_LEN);
    }

    void SetOrganization(const WCHAR* wsz)
    {
        StrCpyNW(m_dat.m_szOrganization, wsz, MAX_ORG_LEN);
    }

public:
    const WCHAR* m_szName;
    const WCHAR* m_szOrganization;

    BOOL& m_bAdvancedView;
    BOOL& m_bCenter;

    WINDOWPLACEMENT& m_wp;
    BOOL& m_bAlwaysOnTop;

    // The currently selected destination
    DWORD& m_dwDestID;

    // the date when this software was installed.
    SYSTEMTIME& m_InstallDate;
    const char* m_szRegKey;

    MIX_DESTINATION& m_Type;

    // Currently selected Mixer Device
    DWORD& m_dwMixerID;

private:
    CAppSettingsData m_dat;
    bool m_bEncrypted;
    void Encrypt()
    {
        if(m_bEncrypted) return;
        TranslateData((BYTE*)&m_dat, sizeof(m_dat));
        TranslateData((BYTE*)&(m_dat.m_szRegKey[0]), sizeof(m_dat.m_szRegKey));
        m_bEncrypted = true;
    }

    void Decrypt()
    {
        if(!m_bEncrypted) return;
        TranslateData((BYTE*)&m_dat, sizeof(m_dat));
        TranslateData((BYTE*)&(m_dat.m_szRegKey[0]), sizeof(m_dat.m_szRegKey));
        m_bEncrypted = false;
    }
};

