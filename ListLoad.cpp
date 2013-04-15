// ListLoad.cpp :
//

#include "ListLoad.h"
#include "CreateTabbedWindow.h"
#include "CreateHistogramWindow.h"
#include "CreateRichEditWindow.h"
#include "CreateListViewtWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "version.h"
#include "Constants.h"


HWND CHARSOCCURRENCESCALL
ListLoad(HWND ParentWindow, char* FileToLoad, int /*ShowFlags*/)
{
	HWND    hwndTabCtrl    = 0;
	HWND    hwndHistogram  = 0;
	HWND    hwndHistogram1 = 0;
	HWND    hwndRichEdit   = 0;
	HWND    hwndListView   = 0;
	HWND    hwndListView1  = 0;
	int     lastChosenTab  = 0;
	RECT    rect;
	TCHAR   iniFile[_MAX_PATH + lstrlen(INI_FILE) + 1];

    WNDPROC OldTabCtrlProc;
    extern
    LRESULT CALLBACK
    NewTabCtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Vytvorenie okna typu Tab Control, vyp��aj�ceho rodi�ovsk� okno (okno Listera)
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Subclassing of this window and saving the pointer of the old WindowProc as his property
    OldTabCtrlProc = (WNDPROC) SetWindowLongPtr (hwndTabCtrl, GWLP_WNDPROC, (LONG_PTR) NewTabCtrlProc);
    SetProp(hwndTabCtrl, OLD_TAB_WNDPROC_PROP, (HANDLE) OldTabCtrlProc);

    int   * vyskytyPismen = (int   *) malloc((NumOfCapitalLetters + NumOfDigits) * sizeof(int));
    TCHAR * vysledok      = (TCHAR *) malloc(MaxCharsHorizAndlVertical           * sizeof(TCHAR));
    TCHAR * about         = (TCHAR *) malloc((lstrlen(TextAbout) + 1)            * sizeof(TCHAR));
    TCHAR * horizontal    = vysledok;    // Tento re�azec je �as�ou re�azca vysledok, toto je   ukazovate� na jeho za�iatok
    TCHAR * vertical      = 0;           // Tento re�azec je �as�ou re�azca vysledok, toto bude ukazovate� na jeho za�iatok


    _stprintf(about, TextAbout,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Z�skanie obd�nika pre zobrazovaciu �as� Tab Control
    GetClientRect(hwndTabCtrl, &rect);
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Creating child windows in the display area of the Tab Control
    hwndListView   = CreateListViewWindow (hwndTabCtrl, &rect, ListViewAlphaId);
    hwndListView1  = CreateListViewWindow (hwndTabCtrl, &rect, ListViewDigitId);
    hwndHistogram  = CreateHistogramWindow(hwndTabCtrl, &rect, HistogramAlphaId);
    hwndHistogram1 = CreateHistogramWindow(hwndTabCtrl, &rect, HistogramDigitId);
    hwndRichEdit   = CreateRichEditWindow (hwndTabCtrl, &rect);

	if (hwndListView && hwndListView1 && hwndHistogram && hwndHistogram1 && hwndRichEdit)
    {
        // EnableWindow(hwndRichEdit, FALSE);
        spracovanieVstupnehoSuboru(vysledok, vyskytyPismen, &vertical, FileToLoad);    // U� m�me aj re�azec vertical
        naplnListView(hwndListView,  vyskytyPismen, CharsTypeAlpha);
        naplnListView(hwndListView1, vyskytyPismen, CharsTypeDigit);

        SetProp(hwndTabCtrl,    LISTVIEW_PROP,       (HANDLE) vyskytyPismen);
        SetProp(hwndListView,   LAST_CLICKED_COLUMN, (HANDLE) 1);           // As column 0 (renumbered as 1) was yet clicked
        SetProp(hwndListView1,  LAST_CLICKED_COLUMN, (HANDLE) 1);           // As column 0 (renumbered as 1) was yet clicked
        SetProp(hwndHistogram,  ARRAY_OF_OCCURENCES, (HANDLE) vyskytyPismen);
        SetProp(hwndHistogram1, ARRAY_OF_OCCURENCES, (HANDLE) vyskytyPismen);
        SetProp(hwndTabCtrl,    VERTICAL_PROP,       (HANDLE) vertical);
        SetProp(hwndTabCtrl,    HORIZONTAL_PROP,     (HANDLE) vysledok);
        SetProp(hwndTabCtrl,    ABOUT_PROP,          (HANDLE) about);

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
        lastChosenTab = GetPrivateProfileInt(INI_SECTION_TAB, INI_KEY_LAST_CHOSEN_TAB, 0, iniFile);
        SetProp(hwndTabCtrl, LAST_CHOSEN_TAB, (HANDLE) lastChosenTab);       // For the case when default and user didn't choose other

        TabCtrl_SetCurSel(hwndTabCtrl, lastChosenTab);
        switchTab(hwndTabCtrl,   hwndListView,   hwndListView1,
                  hwndHistogram, hwndHistogram1, hwndRichEdit,  horizontal, vertical, about);

        ShowWindow(hwndListView,   SW_SHOW);
        ShowWindow(hwndListView1,  SW_SHOW);
        ShowWindow(hwndHistogram,  SW_SHOW);
        ShowWindow(hwndHistogram1, SW_SHOW);
        ShowWindow(hwndRichEdit,   SW_SHOW);
    }

    return hwndTabCtrl;             // The function ListLoadNext() will use it
}

