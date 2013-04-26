// ListLoad.cpp :
//

#include "ListLoad.h"
#include "CreateTabbedWindow.h"
#include "CreateHistogramWindow.h"
#include "CreateRichEditWindow.h"
#include "CreateListViewtWindow.h"
#include "Classic.h"
#include "Helpers.h"
#include "Exports.h"
#include "version.h"
#include "Constants.h"


HWND CHARSOCCURRENCESCALL
ListLoad(HWND ParentWindow, char* FileToLoad, int /*ShowFlags*/)
{
	HWND    hwndTabCtrl        = 0;
	HWND    hwndListViewAlpha  = 0;
	HWND    hwndListViewDigit  = 0;
	HWND    hwndHistogramAlpha = 0;
	HWND    hwndHistogramDigit = 0;
	HWND    hwndRichEdit       = 0;
	int     lastChosenTab      = 0;
	RECT    rect;
	TCHAR   iniFile[_MAX_PATH + lstrlen(INI_FILE) + 1];

    WNDPROC OldTabCtrlProc;
    extern
    LRESULT CALLBACK
    NewTabCtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


    // Vytvorenie okna typu Tab Control, vypåòajúceho rodièovské okno (okno Listera)
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Subclassing of this window and saving the pointer of the old WindowProc as his property
    OldTabCtrlProc = (WNDPROC) SetWindowLongPtr (hwndTabCtrl, GWLP_WNDPROC, (LONG_PTR) NewTabCtrlProc);
    SetProp(hwndTabCtrl, OldTabCtrlWndProc, (HANDLE) OldTabCtrlProc);

    // Creating instance of the class Classic and saving the pointer to it in the property of the TabCtrl Window
    Classic * pClassic = new Classic();
    SetProp(hwndTabCtrl, PointerToClassic, (HANDLE) pClassic);

    // Získanie obdåžnika pre zobrazovaciu èas Tab Control
    GetClientRect(hwndTabCtrl, &rect);
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Creating child windows in the display area of the Tab Control
    hwndListViewAlpha  = CreateListViewWindow (hwndTabCtrl, &rect, ListViewAlphaId);
    hwndListViewDigit  = CreateListViewWindow (hwndTabCtrl, &rect, ListViewDigitId);
    hwndHistogramAlpha = CreateHistogramWindow(hwndTabCtrl, &rect, HistogramAlphaId);
    hwndHistogramDigit = CreateHistogramWindow(hwndTabCtrl, &rect, HistogramDigitId);
    hwndRichEdit       = CreateRichEditWindow (hwndTabCtrl, &rect, RichEditId);

	if (hwndListViewAlpha && hwndListViewDigit && hwndHistogramAlpha && hwndHistogramDigit && hwndHistogramDigit)
    {
        // Saving the windows handles
        pClassic->setHwndListViewAlpha (hwndListViewAlpha);
        pClassic->setHwndListViewDigit (hwndListViewDigit);
        pClassic->setHwndHistogramAlpha(hwndHistogramAlpha);
        pClassic->setHwndHistogramDigit(hwndHistogramDigit);
        pClassic->setHwndRichEdit      (hwndRichEdit);

        pClassic->spracovanieVstupnehoSuboru(FileToLoad);
        pClassic->naplnListView(hwndListViewAlpha, CharsTypeAlpha);
        pClassic->naplnListView(hwndListViewDigit, CharsTypeDigit);

        SetProp(hwndHistogramAlpha, PointerToClassic,   (HANDLE) pClassic);
        SetProp(hwndHistogramDigit, PointerToClassic,   (HANDLE) pClassic);

        pClassic->setLastClickedColumnAlpha(1);      // As column 0 (renumbered as 1) was already clicked
        pClassic->setLastClickedColumnDigit(1);      // As column 0 (renumbered as 1) was already clicked

        /*
         *  Restore the last chosen tab from the INI file and store it
         *  in the properties
         *  of the Tab Control window
         */
        getFullIniFilePath(iniFile);
        lastChosenTab = GetPrivateProfileInt(IniFileTabsSection, IniFileLastChosenTabKey, 0, iniFile);
        SetProp(hwndTabCtrl, LastChosenTab, (HANDLE) lastChosenTab);       // For the case when default and user didn't choose other

        TabCtrl_SetCurSel(hwndTabCtrl, lastChosenTab);
        switchTab(hwndTabCtrl);

        ShowWindow(hwndListViewAlpha,  SW_SHOW);
        ShowWindow(hwndListViewDigit,  SW_SHOW);
        ShowWindow(hwndHistogramAlpha, SW_SHOW);
        ShowWindow(hwndHistogramDigit, SW_SHOW);
        ShowWindow(hwndRichEdit,       SW_SHOW);
    }

    return hwndTabCtrl;             // The function ListLoadNext() will use it
}

