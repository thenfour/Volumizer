

#include "stdafx.h"
#include <shlwapi.h>
#include <stdio.h>
#include <tchar.h>


#define SMALLEST_STRING 200


/*
    Returns a BUFFER_SIZE aligned size that is guaranteed to hold nRequired
    characters.
*/
int GetOptimalStringSize(int nRequired)
{
    return ((nRequired / SMALLEST_STRING) + 1) * SMALLEST_STRING;
}


/*
    010509 Carl Corcoran
*/
int GetSizeOfStringA(PCSTR sz)
{
    return strlen(sz) + 1;
}


/*
    010509 Carl Corcoran
*/
int GetSizeOfStringW(PCWSTR wsz)
{
    return wcslen(wsz) + 1;
}


/*
    010510 Carl Corcoran
    The returned pointer must be freed by the caller using free().
*/
PWSTR StrToWide(PCSTR sz)
{
    int nRequiredSize = MultiByteToWideChar(CP_ACP, NULL, sz, -1, NULL, 0);

    PWSTR wszString = (PWSTR)malloc(nRequiredSize * (sizeof(WCHAR)));

	if(!wszString)
	{
		__asm int 3;
	}

    MultiByteToWideChar(CP_ACP, NULL, sz, -1, wszString, nRequiredSize);

    return wszString;
}


/*
    010510 Carl Corcoran
*/
void CCString::_CreateFromA(PCSTR sz)
{
    PWSTR wszTemp = StrToWide(sz);

    this->_CreateFromW(wszTemp);

    free(wszTemp);
}


/*
    010511 Carl Corcoran
*/
PWSTR CCString::GetBuffer(int nLen)
{
    this->_SizeSetPreserve(nLen);
    return this->wszString;
}


/*
    010510 Carl Corcoran
*/
void CCString::_CreateFromW(PCWSTR wsz)
{
    int nRequiredSize = GetSizeOfStringW(wsz);
    this->_SizeSetDestructive(nRequiredSize);
    wcscpy(this->wszString, wsz);
}


/*
    010509 Carl Corcoran
*/
CCString::operator PWSTR() const
{
    return (PWSTR)this->wszString;
}


/*
    010509 Carl Corcoran
*/
CCString::CCString()
{
    this->bstrString = NULL;
    this->variantString.vt = VT_BSTR;
    this->variantString.bstrVal = NULL;

    this->nSize = 0;
    this->wszString = NULL;
    this->nSizeA = 0;
    this->szStringA = NULL;

    this->_SizeSetDestructive(1);
    this->wszString[0] = 0;

}


/*
    010509 Carl Corcoran
*/
CCString::CCString(PCSTR sz)
{
    this->nSizeA = 0;
    this->szStringA = NULL;
    this->nSize = 0;
    this->wszString = NULL;

    this->bstrString = NULL;
    this->variantString.vt = VT_BSTR;
    this->variantString.bstrVal = NULL;

    this->_CreateFromA(sz);
}


/*
    010509 Carl Corcoran
*/
CCString::CCString(WCHAR wc)
{
    this->nSizeA = 0;
    this->szStringA = NULL;
    this->nSize = 0;
    this->wszString = NULL;

    this->bstrString = NULL;
    this->variantString.vt = VT_BSTR;
    this->variantString.bstrVal = NULL;

    this->_SizeSetDestructive(2);
    this->wszString[0] = wc;
    this->wszString[1] = 0;
}


/*
    010509 Carl Corcoran
*/
CCString::CCString(PCWSTR wsz)
{
    this->nSizeA = 0;
    this->szStringA = NULL;
    this->nSize = 0;
    this->wszString = NULL;

    this->bstrString = NULL;
    this->variantString.vt = VT_BSTR;
    this->variantString.bstrVal = NULL;

    this->_CreateFromW(wsz);
}


/*
    010509 Carl Corcoran
*/
CCString::CCString(const CCString& str)
{
    this->nSizeA = 0;
    this->szStringA = NULL;
    this->nSize = 0;
    this->wszString = NULL;

    this->bstrString = NULL;
    this->variantString.vt = VT_BSTR;
    this->variantString.bstrVal = NULL;

    this->_CreateFromW((PCWSTR)str);
}


/*
    010509 Carl Corcoran
*/
CCString::~CCString()
{
    this->_SizeDelete();
}



const CCString& CCString::operator = (WCHAR c)
{
    this->_SizeSetDestructive(2);
    this->wszString[0] = c;
    this->wszString[1] = 0;
    return (*this);
}


/*
    010509 Carl Corcoran
*/
const CCString& CCString::operator = (PCSTR sz)
{
    this->_CreateFromA(sz);
    return (*this);
}


/*
    010509 Carl Corcoran
*/
const CCString& CCString::operator = (PCWSTR wsz)
{
    this->_CreateFromW(wsz);
    return (*this);
}


/*
    010509 Carl Corcoran
*/
const CCString& CCString::operator = (CCString& str)
{
    this->_CreateFromW((PCWSTR)str);
    return (*this);
}


/*
    010510 Carl Corcoran
*/
void CCString::_CatA(PCSTR sz)
{
    CCString Temp = sz;
    this->_CatW((PCWSTR)Temp);
}


/*
    010510 Carl Corcoran
*/
void CCString::_CatW(PCWSTR wsz)
{
    int nRequiredSize = GetSizeOfStringW(this->wszString) + GetSizeOfStringW(wsz);
    this->_SizeSetPreserve(nRequiredSize);
    wcscat(this->wszString, wsz);
}

/*
    010510 Carl Corcoran
*/
const CCString& CCString::operator += (PCWSTR str)
{
    this->_CatW(str);
    return (*this);
}


/*
    010510 Carl Corcoran
*/
const CCString& CCString::operator += (CCString& str)
{
    this->_CatW((PCWSTR)str);
    return (*this);
}


/*
    010510 Carl Corcoran
*/
const CCString& CCString::operator += (WCHAR wc)
{
    this->_CatW((PCWSTR)CCString(wc));
    return (*this);
}


/*
    010510 Carl Corcoran
*/
CCString::operator PSTR()
{
    _GetAnsiVersion();
    return (PSTR)this->szStringA;
}


/*
    010510 Carl Corcoran
*/
void CCString::_GetAnsiVersion()
{
    if(this->szStringA)
    {
        free(this->szStringA);
		this->szStringA = 0;
    }

    this->nSizeA = GetSizeOfStringW(this->wszString);
    this->szStringA = (PSTR)malloc(sizeof(CHAR) * this->nSizeA);

	if(!this->szStringA)
	{
		__asm int 3;
	}


    WideCharToMultiByte(CP_ACP, NULL, this->wszString, -1,
        this->szStringA, this->nSizeA, NULL, NULL);
}


/*
    010510 Carl Corcoran
*/
const WCHAR CCString::operator [](int n) const
{
    return this->wszString[n];
}


/*
    010510 Carl Corcoran
*/
void CCString::Mid(int nStart, int Len, CCString& Dest)
{
    PWSTR wszDest = (PWSTR)malloc(sizeof(WCHAR) * (Len + 1));
	if(!wszDest)
	{
		__asm int 3;
	}

    wcsncpy(wszDest, this->wszString + nStart, Len + 1);
    wszDest[Len] = 0;
    Dest = wszDest;
    free(wszDest);
}


/*
    010510 Carl Corcoran
*/
void CCString::Mid(int nStart, CCString& Dest)
{
    Dest.cpy(this->wszString + nStart);
    return;
}


/*
    010509 Carl Corcoran
*/
void CCString::Left(int n, CCString& Dest)
{
    PWSTR wszTemp = _wcsdup(this->wszString);
	if(!wszTemp)
	{
		__asm int 3;
	}
    wszTemp[n] = 0;
    Dest.cpy(wszTemp);
    free(wszTemp);
    return;
}


/*
    010509 Carl Corcoran
*/
void CCString::Right(int n, CCString& Dest)
{
    int nPos = wcslen(this->wszString) - n;
    Dest.cpy(this->wszString + nPos);
    return;
}



#define BUFFER_SIZE 1024
/*
    010510 Carl Corcoran
*/
HRESULT CCString::ReadFromFileA(HANDLE hFile)
{
    CHAR c;
    DWORD br = 0;

    CHAR szBuf[BUFFER_SIZE];
    int nPos;// Position in szBuf.

    // Initialize the temp buffer
    ZeroMemory(szBuf, sizeof(CHAR) * BUFFER_SIZE);
    nPos = 0;

    while(1)
    {
        ReadFile(hFile, &c, sizeof(CHAR), &br, NULL);
        if(br == 0) break;
        if(c == 0) break;// we foudn teh null - term.
        szBuf[nPos] = c;

        nPos ++;
        if(nPos == BUFFER_SIZE)
        {
            this->_CatA(szBuf);
            ZeroMemory(szBuf, sizeof(CHAR) * BUFFER_SIZE);
            nPos = 0;
        }
    }

    this->_CatA(szBuf);

    return S_OK;
}
#undef BUFFER_SIZE


#define BUFFER_SIZE 1024
/*
    010510 Carl Corcoran
*/
HRESULT CCString::ReadFromFileW(HANDLE hFile)
{
    WCHAR ch;
    DWORD br = 0;

    WCHAR wszBuf[BUFFER_SIZE];
    int nPos;// Position in szBuf.

    // Initialize the temp buffer
    ZeroMemory(wszBuf, sizeof(WCHAR) * BUFFER_SIZE);
    nPos = 0;

    while(1)
    {
        ReadFile(hFile, &ch, sizeof(WCHAR), &br, NULL);
        if(br == 0) break;
        if(ch == 0) break;// we foudn teh null - term.
        wszBuf[nPos] = ch;

        nPos ++;
        if(nPos == BUFFER_SIZE)
        {
            this->_CatW(wszBuf);
            ZeroMemory(wszBuf, sizeof(WCHAR) * BUFFER_SIZE);
            nPos = 0;
        }
    }
    this->_CatW(wszBuf);

    return S_OK;
}
#undef BUFFER_SIZE


/*
    010510 Carl Corcoran
*/
HRESULT CCString::WriteToFileA(HANDLE hFile)
{
    DWORD br;

    this->_GetAnsiVersion();

    if(WriteFile(hFile, this->szStringA, strlen(this->szStringA) * sizeof(CHAR), &br, NULL)
        == 0)
    {
        //odssys("CCString::WriteToFileA()", "WriteFile()", GetLastError());
        return GetLastError();
    }

    return S_OK;
}


/*
    010510 Carl Corcoran
*/
HRESULT CCString::WriteToFileW(HANDLE hFile)
{
    DWORD br;

    if(WriteFile(hFile, this->wszString, wcslen(this->wszString) * sizeof(WCHAR), &br, NULL)
        == 0)
    {
        //odssys("CCString::WriteToFileW()", "WriteFile()", GetLastError());
        return GetLastError();
    }

    return S_OK;
}


/*
    010510 Carl Corcoran
*/
void CCString::FormatA(PCSTR szFormat, ...)
{
    va_list argptr;
    va_start(argptr, szFormat);
    this->FormatvA(szFormat, argptr);
    va_end(argptr);
}


/*
    010510 Carl Corcoran
*/
void CCString::FormatW(PCWSTR wszFormat, ...)
{
    va_list argptr;
    va_start(argptr, wszFormat);
    this->FormatvW(wszFormat, argptr);
    va_end(argptr);
}


/*
    010510 Carl Corcoran
*/
void CCString::FormatvW(PCWSTR wszFormat, va_list arg)
{
    WCHAR wsz[1024];
    wvsprintfW(wsz, wszFormat, arg);
    this->cpy(wsz);
}


/*
    010510 Carl Corcoran
*/
void CCString::FormatvA(PCSTR szFormat, va_list arg)
{
    CHAR sz[1024];
    wvsprintfA(sz, szFormat, arg);
    this->cpy(CCString(sz));
}


/*
    010509 Carl Corcoran
*/
void CCString::cpy(PCWSTR s)
{
    this->_CreateFromW((PCWSTR)s);
    return;
}


/*
    010509 Carl Corcoran
*/
void CCString::cat(PCWSTR s)
{
    this->_CatW(s);
    return;
}


/*
    010509 Carl Corcoran
*/
int CCString::cmp(PCWSTR s)
{
    return wcscmp(this->wszString, s);
}


/*
    010509 Carl Corcoran
*/
int CCString::cmpi(PCWSTR s)
{
    return wcsicmp(this->wszString, s);
}


/*
    010509 Carl Corcoran
*/
int CCString::len()
{
    return wcslen(this->wszString);
}


/*
    010509 Carl Corcoran
*/
void CCString::upr()
{
    wcsupr(this->wszString);
}


/*
    010509 Carl Corcoran
*/
void CCString::lwr()
{
    wcslwr(this->wszString);
}


/*
    010509 Carl Corcoran
*/
void CCString::TrimLeft(PCWSTR wszChars)
{
    // Find the first char NOT a one of the chars.
    PWSTR wsz = this->wszString;

    while(1)
    {
        if(wcschr(wszChars, *wsz) == NULL)
        {
            // here it is.
            CCString Temp;
            this->Mid(wsz - this->wszString, Temp);
            this->_CreateFromW(Temp);
            return;
        }

        wsz++;
    }
}


/*
    010509 Carl Corcoran
*/
void CCString::TrimRight(PCWSTR wszChars)
{
    // Find the first char NOT a one of the chars.
    PWSTR wsz = this->wszString + wcslen(this->wszString) - 1;

    while(1)
    {
        if(wcschr(wszChars, *wsz) == NULL)
        {
            // here it is.
            CCString Temp;
            this->Left(wsz - this->wszString, Temp);
            this->_CreateFromW(Temp);
            return;
        }

        wsz--;
    }
}


/*
    010515 Carl Corcoran
    chKey is the $ or % or whatever that will be inserted.
    wszChars is a string that contains all the characters to be encoded.

    String="The"
    Encode(L'$', L"he");
    Yields: T$68$65
*/
void CCString::Encode(WCHAR chKey, PCWSTR wszChars)
{
    CCString r = "";// Resulting string
    CCString t = "";
    PWSTR wszSrcThis = this->wszString;
    PCWSTR wszSrcChars = wszChars;

    WCHAR ch;

    while(1)
    {
        ch = wszSrcThis[0];
        if(ch == 0) break;

        wszSrcChars = wszChars;

        if(wcschr(wszChars, ch) != 0)
        {
            t.FormatW(L"%c%02.2x", chKey, ch);
            r += t;
        }
        else
        {
            r += ch;
        }

        wszSrcThis ++;
    }

    this->_CreateFromW(r);
}


/*
    010509 Carl Corcoran
*/
void CCString::Decode(WCHAR ch)
{
    PWSTR wszFrom = this->wszString;
    PWSTR wszTo = this->wszString;
    WCHAR wc;
    WCHAR wszTemp[3] = {0};

    while(1)
    {
        if(wszFrom[0] == ch)
        {
            wszTemp[0] = wszFrom[1];
            wszTemp[1] = wszFrom[2];
            wszFrom += 2;
            wc = (WCHAR)wcstoul(wszTemp, NULL, 16);
            wszTo[0] = wc;
        }
        else
        {
            wszTo[0] = wszFrom[0];
        }
        if(wszFrom[0] == 0){
            break;
        }
        wszFrom ++;
        wszTo ++;
    }
}


/*
    010510 Carl Corcoran
*/
int CCString::Find(PCWSTR s, int nStart)
{
    PWSTR n = wcsstr(this->wszString + nStart, s);
    if(n == 0) return -1;
    return n - this->wszString;
}


/*
    010510 Carl Corcoran
*/
int CCString::Find(WCHAR wc, int nStart)
{
    PWSTR n = wcschr(this->wszString + nStart, wc);
    if(n == 0) return -1;
    return n - this->wszString;
}


/*
    010601 Carl Corcoran
*/
int CCString::FindI(PCWSTR s, int nStart)
{
    PWSTR n = StrStrIW(this->wszString + nStart, s);
    if(n == 0) return -1;
    return n - this->wszString;
}


/*
    010601 Carl Corcoran
*/
int CCString::FindI(WCHAR wc, int nStart)
{
    PWSTR wsz = this->wszString;

    while(1)
    {
        if(wsz[0] == 0) return -1;
        if(wsz[0] == wc) return wsz - this->wszString;

        wsz++;
    }

    return 0;
}


/*
    010509 Carl Corcoran
*/
int CCString::Path_FindExtension()
{
    return PathFindExtensionW(this->wszString) - this->wszString;
}


/*
    010509 Carl Corcoran
*/
void CCString::Path_StripToFilename()
{
    PathStripPathW(this->wszString);
}


/*
    010509 Carl Corcoran
*/
void CCString::Path_StripToPath()
{
    PathRemoveFileSpecW(this->wszString);
}


/*
    010509 Carl Corcoran
*/
void CCString::Path_Append(PCWSTR wsz)
{
    this->_SizeSetPreserve(GetSizeOfStringW(this->wszString) + wcslen(wsz) + 2);
    PathAppendW(this->wszString, wsz);
}


/*
    010509 Carl Corcoran
*/
void CCString::Path_Canonicalize()
{
    WCHAR wsz[MAX_PATH];
    PathCanonicalizeW(wsz, this->wszString);
    this->_CreateFromW(wsz);
}


/*
    010509 Carl Corcoran
*/
void CCString::Path_AbsoluteToRelative(PCWSTR wszNewRoot)
{
    WCHAR wszNewString[MAX_PATH];
    WCHAR wszCanonString[MAX_PATH];

    PathRelativePathToW(wszNewString,
        wszNewRoot, FILE_ATTRIBUTE_DIRECTORY,
        this->wszString, FILE_ATTRIBUTE_NORMAL
        );

    PathCanonicalizeW(wszCanonString, wszNewString);

    this->cpy(wszCanonString);

    return;
}


/*
    010509 Carl Corcoran
*/
HRESULT CCString::FromGuid(GUID* pGuid)
{
    WCHAR* wsz;
    UuidToStringW(pGuid, &wsz);
    this->_CreateFromW(wsz);
    RpcStringFreeW(&wsz);

    return S_OK;
}


/*
    010509 Carl Corcoran
*/
HRESULT CCString::FromNewGuid()
{
    GUID guid;
    UuidCreate(&guid);
    this->FromGuid(&guid);

    return S_OK;
}


/*
    010509 Carl Corcoran
*/
HRESULT CCString::ToGuid(GUID* pGuid)
{
    return UuidFromStringW(this->wszString, pGuid);
}


HRESULT CCString::froml(long n, int nBase)
{
    this->_SizeSetDestructive(25);
    _ltow(n, this->wszString, nBase);
    return S_OK;
}


long CCString::tol(int nBase)
{
    return wcstol(this->wszString, 0, nBase);
}


HRESULT CCString::fromul(unsigned long n, int nBase)
{
    this->_SizeSetDestructive(25);
    _ultow(n, this->wszString, nBase);
    return S_OK;
}


unsigned long CCString::toul(int nBase)
{
    return wcstoul(this->wszString, 0, nBase);
}


/*
    010509 Carl Corcoran
*/
int CCString::_SizeGet()
{
    return this->nSize;
}


/*
    010509 Carl Corcoran
*/
void CCString::_SizeDelete()
{
    if(this->wszString)
    {
        free(this->wszString);
        this->wszString = NULL;
        this->nSize = 0;
    }

    if(this->szStringA)
    {
        free(this->szStringA);
        this->szStringA = NULL;
        this->nSizeA = 0;
    }

    if(this->bstrString)
    {
        SysFreeString(this->bstrString);
        this->bstrString = NULL;
    }

    this->variantString.bstrVal = NULL;

    return;
}


/*
    010509 Carl Corcoran
*/
void CCString::_SizeSetDestructive(int nSize)
{
    this->_SizeSetPreserve(nSize);
}


/*
    010509 Carl Corcoran
*/
void CCString::_SizeSetPreserve(int nSize)
{
    // Do we actually need to reallocate?
    if(nSize <= this->nSize)
    {
        return;
    }

    nSize = GetOptimalStringSize(nSize);

    // Do we need to RE-alloc or just malloc?
    if(this->wszString == NULL)
    {
        this->wszString = (PWSTR)malloc(nSize * sizeof(WCHAR));
		if(!this->wszString)
		{
			__asm int 3;
		}
        this->nSize = nSize;
        return;
    }

    PWSTR wszTemp = NULL;

    wszTemp = (PWSTR)malloc(nSize * sizeof(WCHAR));
	if(!wszTemp)
	{
		__asm int 3;
	}

    wcscpy(wszTemp, this->wszString);

    this->_SizeDelete();
    
    this->wszString = wszTemp;
    this->nSize = nSize;

    return;
}


/*
    010511 Carl Corcoran
*/
void CCString::Path_GetCurrentDirectory()
{
    PWSTR wsz = this->GetBuffer(MAX_PATH);
    GetCurrentDirectoryW(MAX_PATH, wsz);
}


/*
    010512 Carl Corcoran
*/
BOOL CCString::Path_FileExists()
{
    return PathFileExistsW(this->wszString);
}


/*
    010512 Carl Corcoran
*/
BOOL CCString::Path_IsRelative()
{
    return PathIsRelativeW(this->wszString);
}


/*
    010601 Carl Corcoran
*/
void CCString::RemoveAll(WCHAR ch)
{
    // Because the resulting string will ALWAYS be smaller or equal to the
    // original, no need for reallocation here...
    PWSTR wszSrc = this->wszString;
    PWSTR wszDest = this->wszString;

    while(1)
    {
        if(wszSrc[0] == 0)
        {
            wszDest[0] = 0;
            return;
        }

        if(wszSrc[0] == ch)
        {
            wszSrc++;
        }
        else
        {
            wszDest[0] = wszSrc[0];
            wszSrc ++;
            wszDest ++;
        }

    }
}


/*
    010602 Carl Corcoran
*/
HRESULT CCString::FromDouble(double d)
{
    char sz[50];
    _gcvt(d, 10, sz);
    this->_CreateFromA(sz);
    return S_OK;
}


/*
    010602 Carl Corcoran
*/
double CCString::ToDouble()
{
    return wcstod(this->wszString, NULL);
}


/*
    010603 Carl Corcoran
*/
COLORREF CCString::ToColorref()
{
    WCHAR wsz[3] = {0};
    DWORD dwRed, dwGreen, dwBlue;
    PWSTR wszSrc = this->wszString;

    if(wszSrc[0] == L'#') wszSrc++;

    wsz[0] = wszSrc[0];
    wsz[1] = wszSrc[1];
    dwRed = wcstoul(wsz, NULL, 16);

    wsz[0] = wszSrc[2];
    wsz[1] = wszSrc[3];
    dwGreen = wcstoul(wsz, NULL, 16);

    wsz[0] = wszSrc[4];
    wsz[1] = wszSrc[5];
    dwBlue = wcstoul(wsz, NULL, 16);

    return RGB(dwRed, dwGreen, dwBlue);
}


/*
    010604 Carl Corcoran
*/
void CCString::Insert(int nStart, PCWSTR wsz)
{
    int nLen = wcslen(wsz);
    int nThisLen = wcslen(this->wszString);

    this->_SizeSetPreserve(nThisLen + nLen + 1);

    memmove(
        this->wszString + nStart + nLen, 
        this->wszString + nStart,
        sizeof(WCHAR) * (nThisLen - nStart + 1));

    memcpy(this->wszString + nStart, wsz, nLen * sizeof(WCHAR));
}


/*
    010604 Carl Corcoran
*/
void CCString::Insert(int nStart, WCHAR wc)
{
    int nThisLen = wcslen(this->wszString);

    this->_SizeSetPreserve(nThisLen + 2);

    memmove(
        this->wszString + nStart + 1, 
        this->wszString + nStart,
        sizeof(WCHAR) * (nThisLen - nStart + 1));

    this->wszString[nStart] = wc;
}


/*
    010604 Carl Corcoran
*/
void CCString::Remove(int nStart, int nLen)
{
    int nSize = wcslen(this->wszString) - (nStart + nLen);

    memmove(
        &this->wszString[nStart], 
        &this->wszString[nStart + nLen],
        sizeof(WCHAR) * (wcslen(this->wszString) - nStart)
        );
}


/*
    010604 Carl Corcoran
*/
void CCString::Truncate(int nStart)
{
    if(nStart > this->len()) return;

    this->wszString[nStart] = 0;
}


/*
    010605 Carl Corcoran
*/
int CCString::FindNextWord(int nStart)
{
    int nLen = this->len();

    if(nStart < 0) return 0;
    if(nStart >= nLen) return nLen;

    BOOL bHaveHitSpaces = FALSE;
    int n = nStart;

    while(1)
    {
        if(this->wszString[n] == 0) return n;

        if(this->wszString[n] == L' ')
        {
            bHaveHitSpaces = TRUE;
        }
        else
        {
            if(bHaveHitSpaces == TRUE)
            {
                return n;
            }
        }

        n++;
    }

    return 0;
}



/*
    010605 Carl Corcoran
*/
int CCString::FindPreviousWord(int nStart)
{
    int nLen = this->len();

    if(nStart <= 1) return 0;
    if(nStart >= nLen) return nLen;

    BOOL bHaveHitLetters = FALSE;
    int n = nStart;

    while(1)
    {
        /*
            We will search backwards, skipping first through any white-space
        */
        if(n == 0) return 0;

        if(this->wszString[n] != L' ')
        {
            bHaveHitLetters = TRUE;
        }
        else
        {
            if(bHaveHitLetters == TRUE)
            {
                return n + 1;
            }
        }

        n--;
    }

    return 0;
}


/*
    010605 Carl Corcoran
*/
HRESULT CCString::CopyToClipboard()
{
	HANDLE hMem;
    int nSize;
	PVOID hMemLoc;

    this->_GetAnsiVersion();

    /* 
        Start the operation:
    */
	if(OpenClipboard(0) == FALSE) return E_FAIL;
    EmptyClipboard();

    /*
        Do unicode text:
    */
    nSize = (wcslen(this->wszString) + 1) * sizeof(WCHAR);

    hMem = GlobalAlloc(GMEM_MOVEABLE, nSize);

    hMemLoc = GlobalLock(hMem);
    memcpy(hMemLoc, (PVOID)this->wszString, nSize);
	GlobalUnlock(hMem);
    
    SetClipboardData(CF_UNICODETEXT, hMem);

    /*
        Do the ANSI version
    */
    nSize = strlen(this->szStringA) + 1;

    hMem = GlobalAlloc(GMEM_MOVEABLE, nSize);

    hMemLoc = GlobalLock(hMem);
    memcpy(hMemLoc, (PVOID)this->wszString, nSize);
	GlobalUnlock(hMem);
    
    SetClipboardData(CF_TEXT, hMem);

    /*
        And finally close the clipboard and say goodbye.
    */
	CloseClipboard();

    return S_OK;
}


HRESULT CCString::PasteFromClipboard()
{
    HANDLE hMemory;
    PVOID pData;

    if(OpenClipboard(0) == FALSE) return E_FAIL;

    hMemory = GetClipboardData(CF_UNICODETEXT);

    if(hMemory == NULL)
    {
        // Try for an ansi version
        hMemory = GetClipboardData(CF_UNICODETEXT);

        if(hMemory == NULL) return E_FAIL;

        pData = GlobalLock(hMemory);
        this->_CreateFromA((PCSTR)pData);

        GlobalUnlock(hMemory);
    }
    else
    {
        // Work with the unicode version
        pData = GlobalLock(hMemory);
        this->_CreateFromW((PCWSTR)pData);

        GlobalUnlock(hMemory);
    }

    CloseClipboard();

    return S_OK;
}


BSTR CCString::bstr()
{
    if(this->bstrString)
    {
        SysFreeString(this->bstrString);
    }

    this->bstrString = SysAllocString(this->wszString);

    return this->bstrString;
}


VARIANT CCString::variant()
{
    this->bstr();
    this->variantString.vt = VT_BSTR;
    this->variantString.bstrVal = this->bstrString;
    return this->variantString;
}


CCString::operator BSTR()
{
    return this->bstr();
}


CCString::operator VARIANT()
{
    return this->variant();
}


HRESULT CCString::FromWindow(HWND hWnd)
{
    int n;

    n = GetWindowTextLength(hWnd);

    if(n == 0)
    {
        this->_CreateFromW(L"");
        return S_OK;
    }

    GetWindowTextW(hWnd, this->GetBuffer(n + 1), n + 1);

    return S_OK;
}


HRESULT CCString::ToDate(int* pnYear, int* pnMonth, int* pnDay)
{
    __asm int 3;
    return E_FAIL;
}

/*
    43 0A 0D 3F 49 49 4C 41 0D 0A
*/
HRESULT CCString::FromBinary(const void* p, int nSizeBytes)
{
    PBYTE pData = (PBYTE)p;
    int i;
    PWSTR wsz;

    this->_SizeSetDestructive((nSizeBytes * 3) + 1);
    wsz = this->wszString;

    for(i=0;i<nSizeBytes;i++)
    {
        swprintf(wsz, L"%02X ", pData[i]);
        wsz += 3;
    }

    return S_OK;
}


int CCString::ToBinary(PVOID p, int nBufferSize)
{
    PBYTE pData = (PBYTE)p;
    int i;
    PWSTR wsz = wcsdup(this->wszString);
    PWSTR token;

    i = 0;
    token = wcstok(wsz, L" ");
    while(token != NULL)
    {
        if(i < nBufferSize && pData != 0)
        {
            pData[i] = (BYTE)wcstol(token, NULL, 16);
        }

        token = wcstok(NULL, L" ");
        i++;
    }

    free(wsz);

    return i;
}


void CCString::rev()
{
	if(!this->wszString) return;

	wcsrev(this->wszString);
}

