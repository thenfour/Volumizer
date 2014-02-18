/*
	CREATED: Feb. 21, 2001 carlco
*/


#pragma once


/*
	Represents one tab on the tab control.
*/
class TAB_ITEM
{
public:
	PCTSTR wszTitle;
    DWORD dwUser;
};


/*
	Number of controls you can attach to a tab control
*/
#define MAX_TAB_ATTACHMENTS 100


class CCEXPORT CCTab : public CCControl
{
public:
	CCTab();
	~CCTab();

	HRESULT Create(HWND hParent, RECT prect, RECT orect, int nTabs, TAB_ITEM* pTabs);

    HRESULT AddTabs(TAB_ITEM* pTabs, int nTabs);

	/*
		To use attach, you must first create the control as a child of
		this tab control.  Then call Attach().
	*/
	HRESULT Attach(CCControl* p);
	LRESULT Size();

    /*
        This selects the first tab with the corresponding LPARAM.
    */
    void SelectLParam(DWORD dw);
    void RemoveLParam(DWORD dw);

    void Select(int);

    DWORD GetLParam(int i);

private:

	CCControl* Attachments[MAX_TAB_ATTACHMENTS];

};


