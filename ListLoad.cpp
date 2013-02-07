// ListLoad.cpp :
//

#include "ListLoad.h"
#include "CreateTabbedWindow.h"
#include "CreateRichEditWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "version.h"
#include "Constants.h"

HWND CHARSOCCURRENCESCALL
ListLoad(HWND ParentWindow, char* FileToLoad, int ShowFlags)
{
	HWND      hwndTabCtrl  = 0;
	HWND      hwndRichEdit = 0;
	RECT      rect;

    WNDPROC   OldTabCtrlProc;
    extern
    LRESULT CALLBACK
    NewTabCtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    WNDPROC   OldChildProc;
    extern
    LRESULT CALLBACK
    NewChildProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Vytvorenie okna typu Tab Control, vypÂÚaj˙ceho rodiËovskÈ okno (okno Listera)
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Subclassing tohto okna a uloûenie starej WindowProc do jeho vlastnostÌ
    OldTabCtrlProc = (WNDPROC) SetWindowLongPtr (hwndTabCtrl, GWLP_WNDPROC, (LONG_PTR) NewTabCtrlProc);
    SetProp(hwndTabCtrl, OLD_TAB_WNDPROC_PROP, (HANDLE) OldTabCtrlProc);

    TCHAR * vysledok = (TCHAR *) malloc(MAX_ZNAKOV      * sizeof(TCHAR));
    TCHAR * info     = (TCHAR *) malloc(MAX_ZNAKOV_INFO * sizeof(TCHAR));

    SetProp(hwndTabCtrl, VYSKYTY_VLASTNOST,    (HANDLE) vysledok);
    SetProp(hwndTabCtrl, INFO_VLASTNOST,       (HANDLE) info);

    _stprintf(info, INFO,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // ZÌskanie obdÂûnika pre zobrazovaciu Ëasù Tab Control
    GetClientRect(hwndTabCtrl, &rect);
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Vytvorenie RichEdit v zobrazovacej Ëast Tab Control
    hwndRichEdit = CreateRichEditWindow(hwndTabCtrl, &rect);

	if (hwndRichEdit)
    {
        // EnableWindow(hwndRichEdit, FALSE);
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

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
        case USKO_VYSKYTOV:
            SetWindowText(hwndRichEdit, vysledok);
            break;
        case USKO_INFORMACII:
            SetWindowText(hwndRichEdit, info);
            break;
        default:
            break;
        }

        ShowWindow(hwndRichEdit, SW_SHOW);
    }

	return hwndTabCtrl;             // Pouûije ho ListLoadNext()
}

