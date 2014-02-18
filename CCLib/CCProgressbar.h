

#pragma once


#include "global.h"
#include <windows.h>
#include "CCControl.h"


//A unique name for a class...
#define PROGRESSBAR_CLASS _T("4ea0d3dd-4fd1-43fd-b9bb-13d2153ac800")


class CCProgressBar;


typedef void (CALLBACK* PROGRESSBARPROC)(PVOID pUser, CCProgressBar* pBar, PTSTR Text);


class CCEXPORT CCProgressBar : public CCControl
{
public:
	CCProgressBar();
	~CCProgressBar();

	//int Create(PROGRESSBARPROC pProc, PVOID pUser, HWND hParent, HINSTANCE hInstance, int x, int y, int w, int h);
	int Create(PROGRESSBARPROC pProc, PVOID pUser, HWND hParent, const RECT& prect, const RECT& orect);

	DWORD GetPos();
	DWORD SetPos(DWORD dwNew);
	DWORD GetMax();
	DWORD GetMin();
	DWORD SetMax(DWORD dwNew);
	DWORD SetMin(DWORD dwMin);
	static void CALLBACK DefaultProc(PVOID pUser, CCProgressBar* pBar, PWSTR Text);
	static void CALLBACK DefaultProcNoText(PVOID pUser, CCProgressBar* pBar, PWSTR Text);

private:

    /*
        This invalidates a range of the window based on the given
        progress bar values.
    */
    void InvalidateRange(DWORD dwMin, DWORD dwMax);
    int ValueToPos(DWORD dwValue);// Converts a value to the X pixel offset.
    int _ValueToPos(DWORD dwValue, DWORD dwWindowWidth);// Converts a value to the X pixel offset.

	HBRUSH hBackground;
	HBRUSH hComplete;//the color of the completed portion.

	DWORD dwPos;
	DWORD dwMin;
	DWORD dwMax;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	PROGRESSBARPROC pProc;
	PVOID pUserData;
	TCHAR OldText[1024];

	void OnPaint();

	void CorrectBounds();
};

