// ListLoad.cpp :
//

#include "ListLoad.h"
#include "CreateTabbedWindow.h"
#include "CreateHistogramWindow.h"
#include "CreateRichEditWindow.h"
#include "CreateListViewtWindow.h"
#include "Classic.h"
#include "Status.h"
#include "Helpers.h"
#include "Exports.h"
#include "WndProcs.h"
#include "version.h"
#include "Constants.h"


HWND CHARSOCCURRENCESCALL
ListLoad(HWND ParentWindow, char* FileToLoad, int /*ShowFlags*/)
{
	RECT rect;

    // Vytvorenie okna typu Tab Control, vypåòajúceho rodièovské okno (okno Listera)
    GetClientRect(ParentWindow, &rect);
    HWND hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Creating instance of the classes and saving the pointer to it in the property of the TabCtrl Window
    Classic * pClassic = new Classic();
    Status  * pStatus  = new Status();
    SetProp(hwndTabCtrl, PointerToClassic, (HANDLE) pClassic);
    SetProp(hwndTabCtrl, PointerToStatus,  (HANDLE) pStatus);

    // Subclassing of this window and saving the pointer of the old WindowProc to the instance of the class Status
    WNDPROC oldTabCtrlProc = (WNDPROC) SetWindowLongPtr (hwndTabCtrl, GWLP_WNDPROC, (LONG_PTR) NewTabCtrlProc);
    pStatus->setOldTabCtrlWndProc(oldTabCtrlProc);

    // Získanie obdåžnika pre zobrazovaciu èas Tab Control
    GetClientRect(hwndTabCtrl, &rect);
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Creating child windows in the display area of the Tab Control
    HWND hwndListViewAlpha  = CreateListViewWindow (hwndTabCtrl, &rect, ListViewAlphaId);
    HWND hwndListViewDigit  = CreateListViewWindow (hwndTabCtrl, &rect, ListViewDigitId);
    HWND hwndHistogramAlpha = CreateHistogramWindow(hwndTabCtrl, &rect, HistogramAlphaId);
    HWND hwndHistogramDigit = CreateHistogramWindow(hwndTabCtrl, &rect, HistogramDigitId);
    HWND hwndRichEdit       = CreateRichEditWindow (hwndTabCtrl, &rect, RichEditId);

	if (hwndListViewAlpha && hwndListViewDigit && hwndHistogramAlpha && hwndHistogramDigit && hwndHistogramDigit)
    {
        // Saving the windows handles
        pStatus->setHwndListViewAlpha (hwndListViewAlpha);
        pStatus->setHwndListViewDigit (hwndListViewDigit);
        pStatus->setHwndHistogramAlpha(hwndHistogramAlpha);
        pStatus->setHwndHistogramDigit(hwndHistogramDigit);
        pStatus->setHwndRichEdit      (hwndRichEdit);

        pClassic->spracovanieVstupnehoSuboru(FileToLoad);
        pClassic->naplnListView(hwndListViewAlpha, CharsTypeAlpha);
        pClassic->naplnListView(hwndListViewDigit, CharsTypeDigit);

        /*
         *  Restore the last values from the INI file and store it
         *  into the instance of the Status class
         *
         *  Note:
         *  Sorting by the column 3 ("Percent") is the same as the sorting by
         *  the column 2 ("Count") to don't confuse the user by no reaction after
         *  clicking alternately to the headers of the column 2 and column 3.
         */
        TCHAR iniFile[_MAX_PATH + lstrlen(INI_FILE) + 1];
        getFullIniFilePath(iniFile);

        int lastChosenTab          = GetPrivateProfileInt(IniFileTabsSection,
                                                      IniFileLastChosenTabKey,  0, iniFile);
        int lastClickedColumnAlpha = GetPrivateProfileInt(IniFileSortSection,
                                                      IniFileLastClColAlphaKey, 1, iniFile);
        int lastClickedColumnDigit = GetPrivateProfileInt(IniFileSortSection,
                                                      IniFileLastClColDigitKey, 1, iniFile);

        pStatus->setLastChosenTab         (lastChosenTab);
        pStatus->setLastClickedColumnAlpha(lastClickedColumnAlpha);
        pStatus->setLastClickedColumnDigit(lastClickedColumnDigit);

        // Let show items in the ListViews in the last used order
        HWND hwndListViewAlpha      = pStatus->getHwndListViewAlpha();
        HWND hwndListViewDigit      = pStatus->getHwndListViewDigit();

        ListView_SortItems(hwndListViewAlpha, cmpFunction, lastClickedColumnAlpha);
        ListView_SortItems(hwndListViewDigit, cmpFunction, lastClickedColumnDigit);
        setHeadersArrows  (hwndListViewAlpha, lastClickedColumnAlpha);
        setHeadersArrows  (hwndListViewDigit, lastClickedColumnDigit);

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

