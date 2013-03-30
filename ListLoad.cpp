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
ListLoad(HWND ParentWindow, char* FileToLoad, int ShowFlags)
{
	HWND      hwndTabCtrl   = 0;
	HWND      hwndHistogram = 0;
	HWND      hwndRichEdit  = 0;
	HWND      hwndListView  = 0;
	RECT      rect;

    WNDPROC   OldTabCtrlProc;
    extern
    LRESULT CALLBACK
    NewTabCtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Vytvorenie okna typu Tab Control, vypÂÚaj˙ceho rodiËovskÈ okno (okno Listera)
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Subclassing of this window and saving the pointer of the old WindowProc as his property
    OldTabCtrlProc = (WNDPROC) SetWindowLongPtr (hwndTabCtrl, GWLP_WNDPROC, (LONG_PTR) NewTabCtrlProc);
    SetProp(hwndTabCtrl, OLD_TAB_WNDPROC_PROP, (HANDLE) OldTabCtrlProc);

    int   * vyskytyPismen = (int   *) malloc(POCET_VELKYCH_PISMEN * sizeof(int));
    TCHAR * vysledok      = (TCHAR *) malloc(MAX_ZNAKOV           * sizeof(TCHAR));
    TCHAR * about         = (TCHAR *) malloc(MAX_ZNAKOV_ABOUT     * sizeof(TCHAR));
    TCHAR * horizontal    = vysledok;    // Tento reùazec je Ëasùou reùazca vysledok, toto je   ukazovateæ na jeho zaËiatok
    TCHAR * vertical      = 0;           // Tento reùazec je Ëasùou reùazca vysledok, toto bude ukazovateæ na jeho zaËiatok


    _stprintf(about, ABOUT,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // ZÌskanie obdÂûnika pre zobrazovaciu Ëasù Tab Control
    GetClientRect(hwndTabCtrl, &rect);
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Creating child windows in the display area of the Tab Control
    hwndListView  = CreateListViewWindow (hwndTabCtrl, &rect);
    hwndHistogram = CreateHistogramWindow(hwndTabCtrl, &rect);
    hwndRichEdit  = CreateRichEditWindow (hwndTabCtrl, &rect);

	if (hwndListView && hwndHistogram && hwndRichEdit)
    {
        // EnableWindow(hwndRichEdit, FALSE);
        spracovanieVstupnehoSuboru(vysledok, vyskytyPismen, &vertical, FileToLoad);    // Uû m·me aj reùazec vertical
        naplnListView(hwndListView, vyskytyPismen);

        SetProp(hwndTabCtrl,   LISTVIEW_PROP,       (HANDLE) vyskytyPismen);
        SetProp(hwndListView,  LAST_CLICKED_COLUMN, (HANDLE) 1);           // As column 0 (renumbered as 1) was yet clicked
        SetProp(hwndHistogram, ARRAY_OF_OCCURENCES, (HANDLE) vyskytyPismen);
        SetProp(hwndTabCtrl,   VERTICAL_PROP,       (HANDLE) vertical);
        SetProp(hwndTabCtrl,   HORIZONTAL_PROP,     (HANDLE) vysledok);
        SetProp(hwndTabCtrl,   ABOUT_PROP,          (HANDLE) about);

        #ifdef _DEBUG
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\n *** Volala sa funkcia ListLoad() ***"));
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndTabCtrl  = %p"), hwndTabCtrl);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\nhwndRichEdit = %p"),   hwndRichEdit);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nsizeof(TCHAR)   = %d"), sizeof(TCHAR));
            int znakov = lstrlen(vysledok);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\Znakov vysledku = %d"), znakov);
        #endif

        switch (TabCtrl_GetCurSel(hwndTabCtrl))
        {
        case TAB_LISTVIEW:
            BringWindowToTop(hwndListView);            break;
        case TAB_HISTOGRAM:
            BringWindowToTop(hwndHistogram);
            break;
        case TAB_VERTICAL:
            SetWindowText(hwndRichEdit, vertical);
            BringWindowToTop(hwndRichEdit);            break;
        case TAB_HORIZONTAL:
            SetWindowText(hwndRichEdit, horizontal);
            BringWindowToTop(hwndRichEdit);            break;
        case TAB_ABOUT:
            SetWindowText(hwndRichEdit, about);
            BringWindowToTop(hwndRichEdit);            break;
        default:
            break;
        }
        ShowWindow(hwndListView,  SW_SHOW);
        ShowWindow(hwndHistogram, SW_SHOW);
        ShowWindow(hwndRichEdit,  SW_SHOW);
    }

	return hwndTabCtrl;             // The function ListLoadNext() will use it
}

