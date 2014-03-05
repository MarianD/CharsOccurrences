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
#include "resource.h"


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
    SetProp(hwndTabCtrl, cn::PointerToClassic, (HANDLE) pClassic);
    SetProp(hwndTabCtrl, cn::PointerToStatus,  (HANDLE) pStatus);

    // Subclassing of this window and saving the pointer of the old WindowProc to the instance of the class Status
    WNDPROC oldTabCtrlProc = SubclassWindow(hwndTabCtrl, NewTabCtrlProc);    // Macro defined in windowsx.h
    pStatus->setOldTabCtrlWndProc(oldTabCtrlProc);

        /*
         *  Restore the last values from the INI file and store it
         *  into the instance of the Status class
         *
         *  Note:
         *  Sorting by the column 3 ("Percent") is the same as the sorting by
         *  the column 2 ("Count") to don't confuse the user by no reaction after
         *  clicking alternately to the headers of the column 2 and column 3.
         */
        TCHAR * iniFile = new TCHAR[_MAX_PATH + lstrlen(cn::IniFile) + 1];
        getFullIniFilePath(iniFile);

        int lastChosenTab          = GetPrivateProfileInt(cn::IniFileTabsSection,
                                                          cn::IniFileLastChosenTabKey,  0, iniFile);
        int lastClickedColumnAlpha = GetPrivateProfileInt(cn::IniFileSortSection,
                                                          cn::IniFileLastClColAlphaKey, 1, iniFile);
        int lastClickedColumnDigit = GetPrivateProfileInt(cn::IniFileSortSection,
                                                          cn::IniFileLastClColDigitKey, 1, iniFile);
        int fontSize               = GetPrivateProfileInt(cn::IniFileFontSection,
                                                          cn::IniFileFontSize, cn::defaultFontSize, iniFile);
        delete[] iniFile;

        pStatus->setLastChosenTab         (lastChosenTab);
        pStatus->setLastClickedColumnAlpha(lastClickedColumnAlpha);
        pStatus->setLastClickedColumnDigit(lastClickedColumnDigit);
        pStatus->setFontSize              (fontSize);

    // Získanie obdåžnika pre zobrazovaciu èas Tab Control
    GetClientRect(hwndTabCtrl, &rect);
    (void)
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Creating child windows in the display area of the Tab Control
    HMODULE hMod             = GetModuleHandle(cn::thisDLL);
    INITCOMMONCONTROLSEX iCC = {sizeof(INITCOMMONCONTROLSEX), ICC_STANDARD_CLASSES};
    (void) InitCommonControlsEx(&iCC);

    HWND hwndListViewAlpha   = CreateListViewWindow (hwndTabCtrl, &rect, cn::ListViewAlphaId);
    HWND hwndListViewDigit   = CreateListViewWindow (hwndTabCtrl, &rect, cn::ListViewDigitId);
    HWND hwndHistogramAlpha  = CreateHistogramWindow(hwndTabCtrl, &rect, cn::HistogramAlphaId);
    HWND hwndHistogramDigit  = CreateHistogramWindow(hwndTabCtrl, &rect, cn::HistogramDigitId);
    HWND hwndRichEdit        = CreateRichEditWindow (hwndTabCtrl, &rect, cn::RichEditId);
    HWND hwndSettings        = CreateDialog((HINSTANCE) hMod, MAKEINTRESOURCE(SETTINGS), hwndTabCtrl,
                                            (DLGPROC) nullptr);

	if (hwndListViewAlpha && hwndListViewDigit && hwndHistogramAlpha && hwndHistogramDigit &&
        hwndRichEdit      && hwndSettings)
    {
        // Saving the windows handles
        pStatus->setHwndListViewAlpha (hwndListViewAlpha);
        pStatus->setHwndListViewDigit (hwndListViewDigit);
        pStatus->setHwndHistogramAlpha(hwndHistogramAlpha);
        pStatus->setHwndHistogramDigit(hwndHistogramDigit);
        pStatus->setHwndRichEdit      (hwndRichEdit);
        pStatus->setHwndSettings      (hwndSettings);

        pClassic->spracovanieVstupnehoSuboru(FileToLoad);
        pClassic->naplnListView(hwndListViewAlpha, cn::CharsTypeAlpha);
        pClassic->naplnListView(hwndListViewDigit, cn::CharsTypeDigit);

        // Let show items in the ListViews in the last used order
        (void)
        ListView_SortItems(hwndListViewAlpha, cmpFunction, lastClickedColumnAlpha);
        (void)
        ListView_SortItems(hwndListViewDigit, cmpFunction, lastClickedColumnDigit);

        setHeadersArrows  (hwndListViewAlpha, lastClickedColumnAlpha);
        setHeadersArrows  (hwndListViewDigit, lastClickedColumnDigit);

        MoveWindow(hwndSettings, rect.left, rect.top,
                                 rect.right  - rect.left,
                                 rect.bottom - rect.top, FALSE);
        (void)
        TabCtrl_SetCurSel(hwndTabCtrl, lastChosenTab);
        switchTab(hwndTabCtrl);
        (void)
        TabCtrl_SetCurSel(hwndTabCtrl, lastChosenTab);
        switchTab(hwndTabCtrl);
    }

    return hwndTabCtrl;             // The function ListLoadNext() will use it
}

