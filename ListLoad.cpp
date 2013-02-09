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

    // Vytvorenie okna typu Tab Control, vyp��aj�ceho rodi�ovsk� okno (okno Listera)
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Subclassing tohto okna a ulo�enie starej WindowProc do jeho vlastnost�
    OldTabCtrlProc = (WNDPROC) SetWindowLongPtr (hwndTabCtrl, GWLP_WNDPROC, (LONG_PTR) NewTabCtrlProc);
    SetProp(hwndTabCtrl, OLD_TAB_WNDPROC_PROP, (HANDLE) OldTabCtrlProc);

    TCHAR * vysledok   = (TCHAR *) malloc(MAX_ZNAKOV       * sizeof(TCHAR));
    TCHAR * about      = (TCHAR *) malloc(MAX_ZNAKOV_ABOUT * sizeof(TCHAR));
    TCHAR * horizontal = vysledok;    // Tento re�azec je �as�ou re�azca vysledok, toto je   ukazovate� na jeho za�iatok
    TCHAR * vertical   = 0;           // Tento re�azec je �as�ou re�azca vysledok, toto bude ukazovate� na jeho za�iatok


    _stprintf(about, ABOUT,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Z�skanie obd�nika pre zobrazovaciu �as� Tab Control
    GetClientRect(hwndTabCtrl, &rect);
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Vytvorenie RichEdit v zobrazovacej �ast Tab Control
    hwndRichEdit = CreateRichEditWindow(hwndTabCtrl, &rect);

	if (hwndRichEdit)
    {
        // EnableWindow(hwndRichEdit, FALSE);
        spracovanieVstupnehoSuboru(vysledok, &vertical, FileToLoad);    // U� m�me aj re�azec vertical

        SetProp(hwndTabCtrl, VERTICAL_PROP,   (HANDLE) vertical);
        SetProp(hwndTabCtrl, HORIZONTAL_PROP, (HANDLE) vysledok);
        SetProp(hwndTabCtrl, ABOUT_PROP,      (HANDLE) about);

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
        case TAB_VERTICAL:
            SetWindowText(hwndRichEdit, vertical);
            break;
        case TAB_HORIZONTAL:
            SetWindowText(hwndRichEdit, horizontal);
            break;
        case TAB_ABOUT:
            SetWindowText(hwndRichEdit, about);
            break;
        default:
            break;
        }

        ShowWindow(hwndRichEdit, SW_SHOW);
    }
	return hwndTabCtrl;             // Pou�ije ho ListLoadNext()
}

