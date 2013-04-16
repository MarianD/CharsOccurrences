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

    // Vytvorenie okna typu Tab Control, vypÂÚaj˙ceho rodiËovskÈ okno (okno Listera)
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Subclassing of this window and saving the pointer of the old WindowProc as his property
    OldTabCtrlProc = (WNDPROC) SetWindowLongPtr (hwndTabCtrl, GWLP_WNDPROC, (LONG_PTR) NewTabCtrlProc);
    SetProp(hwndTabCtrl, OldTabCtrlWndProc, (HANDLE) OldTabCtrlProc);

    int   * vyskytyPismen = (int   *) malloc((NumOfCapitalLetters + NumOfDigits) * sizeof(int));
    TCHAR * vysledok      = (TCHAR *) malloc(MaxCharsHorizAndlVertical           * sizeof(TCHAR));
    TCHAR * about         = (TCHAR *) malloc((lstrlen(TextAbout) + 1)            * sizeof(TCHAR));
    TCHAR * horizontal    = vysledok;    // Tento reùazec je Ëasùou reùazca vysledok, toto je   ukazovateæ na jeho zaËiatok
    TCHAR * vertical      = 0;           // Tento reùazec je Ëasùou reùazca vysledok, toto bude ukazovateæ na jeho zaËiatok

    _stprintf(about, TextAbout,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // ZÌskanie obdÂûnika pre zobrazovaciu Ëasù Tab Control
    GetClientRect(hwndTabCtrl, &rect);
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Creating child windows in the display area of the Tab Control
    hwndListViewAlpha  = CreateListViewWindow (hwndTabCtrl, &rect, ListViewAlphaId);
    hwndListViewDigit  = CreateListViewWindow (hwndTabCtrl, &rect, ListViewDigitId);
    hwndHistogramAlpha = CreateHistogramWindow(hwndTabCtrl, &rect, HistogramAlphaId);
    hwndHistogramDigit = CreateHistogramWindow(hwndTabCtrl, &rect, HistogramDigitId);
    hwndRichEdit       = CreateRichEditWindow (hwndTabCtrl, &rect);

	if (hwndListViewAlpha && hwndListViewDigit && hwndHistogramAlpha && hwndHistogramDigit && hwndRichEdit)
    {
        // EnableWindow(hwndRichEdit, FALSE);
        Classic::spracovanieVstupnehoSuboru(vysledok, vyskytyPismen, &vertical, FileToLoad);    // Uû m·me aj reùazec vertical
        Classic::naplnListView(hwndListViewAlpha, vyskytyPismen, CharsTypeAlpha);
        Classic::naplnListView(hwndListViewDigit, vyskytyPismen, CharsTypeDigit);

        SetProp(hwndTabCtrl,        ArrayOfOccurrences, (HANDLE) vyskytyPismen);
        SetProp(hwndListViewAlpha,  LastClickedColumn,  (HANDLE) 1);           // As column 0 (renumbered as 1) was yet clicked
        SetProp(hwndListViewDigit,  LastClickedColumn,  (HANDLE) 1);           // As column 0 (renumbered as 1) was yet clicked
        SetProp(hwndHistogramAlpha, ArrayOfOccurrences, (HANDLE) vyskytyPismen);
        SetProp(hwndHistogramDigit, ArrayOfOccurrences, (HANDLE) vyskytyPismen);
        SetProp(hwndTabCtrl,        VerticalText,       (HANDLE) vertical);
        SetProp(hwndTabCtrl,        HorizontalText,     (HANDLE) vysledok);
        SetProp(hwndTabCtrl,        AboutText,          (HANDLE) about);

        #ifdef _DEBUG
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\n *** Volala sa funkcia ListLoad() ***"));
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndTabCtrl  = %p"), hwndTabCtrl);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\nhwndRichEdit = %p"),   hwndRichEdit);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nsizeof(TCHAR)   = %d"), sizeof(TCHAR));
            int znakov = lstrlen(vysledok);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\Znakov vysledku = %d"), znakov);
        #endif

        /*
         *  Restore the last chosen tab from the INI file and store it
         *  in the properties
         *  of the Tab Control window
         */
        getFullIniFilePath(iniFile);
        lastChosenTab = GetPrivateProfileInt(IniFileTabsSection, IniFileLastChosenTabKey, 0, iniFile);
        SetProp(hwndTabCtrl, LastChosenTab, (HANDLE) lastChosenTab);       // For the case when default and user didn't choose other

        TabCtrl_SetCurSel(hwndTabCtrl, lastChosenTab);
        switchTab(hwndTabCtrl,        hwndListViewAlpha,  hwndListViewDigit,
                  hwndHistogramAlpha, hwndHistogramDigit, hwndRichEdit,      horizontal, vertical, about);

        ShowWindow(hwndListViewAlpha,  SW_SHOW);
        ShowWindow(hwndListViewDigit,  SW_SHOW);
        ShowWindow(hwndHistogramAlpha, SW_SHOW);
        ShowWindow(hwndHistogramDigit, SW_SHOW);
        ShowWindow(hwndRichEdit,       SW_SHOW);
    }

    return hwndTabCtrl;             // The function ListLoadNext() will use it
}

