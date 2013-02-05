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


    // Vytvorenie okna typu Tab Control a naplnenie rect hodnotami jeho Diasplay Area
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    TCHAR * vysledok = (TCHAR *) malloc(MAX_ZNAKOV      * sizeof(TCHAR));
    TCHAR * info     = (TCHAR *) malloc(MAX_ZNAKOV_INFO * sizeof(TCHAR));

    SetProp(hwndTabCtrl, VYSKYTY_VLASTNOST, (HANDLE) vysledok);
    SetProp(hwndTabCtrl, INFO_VLASTNOST,    (HANDLE) info);

    _stprintf(info, INFO,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // ZÌskanie obdÂûnika pre zobrazovaciu Ëasù Tab Control
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Vytvorenie RichEdit v zobrazovacej Ëast Tab Control
    hwndRichEdit = CreateRichEditWindow(hwndTabCtrl, &rect);

	if (hwndRichEdit)
    {
//        vysledok[0]      = TEXT('\0');
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\n *** Volala sa funkcia ListLoad() ***"));
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndTabCtrl  = %p"), hwndTabCtrl);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\nhwndRichEdit = %p"),   hwndRichEdit);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nsizeof(TCHAR)   = %d"), sizeof(TCHAR));
        int znakov = lstrlen(vysledok);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\Znakov vysledku = %d"), znakov);

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

	return hwndTabCtrl;             //Pouûije ho ListLoadNext()
}

