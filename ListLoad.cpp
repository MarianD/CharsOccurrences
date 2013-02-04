// ListLoad.cpp :
//

#include "ListLoad.h"
#include "CreateTabbedWindow.h"
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
	TCHAR     info[500];

    _stprintf(info, INFO,
            AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Vytvorenie okna typu Tab Control a naplnenie rect hodnotami jeho Diasplay Area
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Získanie obdåžnika pre zobrazovaciu èas Tab Control
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Vytvorenie RichEdit v zobrazovacej èast Tab Control
    hwndRichEdit = CreateRichEditWindow(hwndTabCtrl, &rect);

	if (hwndRichEdit)
    {
//        ListLoadNext(ParentWindow, hwndTabCtrl, FileToLoad, ShowFlags);
        TCHAR vysledok[MAX_ZNAKOV] = TEXT("");
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\n *** Volala sa funkcia ListLoad() ***"));
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndTabCtrl  = %d"), hwndTabCtrl ->unused);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndRichEdit = %d"), hwndRichEdit->unused);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nsizeof(TCHAR) = %d"), sizeof(TCHAR));

        SetWindowText(hwndRichEdit, vysledok);
        SetProp(hwndTabCtrl, TEXT("Usko 0"), (HANDLE) vysledok);
        SetProp(hwndTabCtrl, TEXT("Usko 1"), (HANDLE) info);
        ShowWindow(hwndRichEdit, SW_SHOW);
    }

	return hwndTabCtrl;             //Použije ho ListLoadNext()
}

