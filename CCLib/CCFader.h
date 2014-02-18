

#pragma once


/*
    Sent as a notification...
*/
#define CCF_POSCHANGED    0x00000001


//////////////////////////////////////////////////////////////////////////////
class CCEXPORT CCFader : public CCControl
{
public:
	CCFader();
	~CCFader();

    HRESULT Create(HWND hParent, HINSTANCE hInstance, RECT prect, RECT orect);

    HRESULT SetPos(int nPos);
    int     GetPos();

    HRESULT SetBounds(int nLow, int nHigh);
    HRESULT GetBounds(int* pnLow, int* pnHigh);

    void Destroy();

private:

    int PositionToPixels(int nPos);
    int PixelsToPosition(int nPixels);

    BOOL bIsTracking;

    void OnMouseMove(int x, int y);

    CCString sClass;

    HBRUSH hFader;
    HBRUSH hBackground;
    HBRUSH hSlit;
    HBRUSH hCenterLine;
    HBRUSH hTickMarks;

    int nLow;
    int nHigh;
    int nPos;

    void Draw(HDC dc);
    void _DrawTicks(HDC dc);
    void _DrawCursor(HDC dc);
    void _DrawSlit(HDC dc);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


