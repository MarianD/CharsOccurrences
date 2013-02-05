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

    SetProp(hwndTabCtrl, TEXT("Usko 0"), (HANDLE) vysledok);
    SetProp(hwndTabCtrl, TEXT("Usko 1"), (HANDLE) info);

    vysledok[0]      = TEXT('\0');
    _stprintf(info, INFO,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);


    // Získanie obdåžnika pre zobrazovaciu èas Tab Control
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Vytvorenie RichEdit v zobrazovacej èast Tab Control
    hwndRichEdit = CreateRichEditWindow(hwndTabCtrl, &rect);

	if (hwndRichEdit)
    {
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\n *** Volala sa funkcia ListLoad() ***"));
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndTabCtrl  = %d"), hwndTabCtrl ->unused);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\nhwndRichEdit = %d"), hwndRichEdit->unused);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nsizeof(TCHAR)   = %d"), sizeof(TCHAR));
        int znakov = lstrlen(vysledok);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\Znakov vysledku = %d"), znakov);

        SetWindowText(hwndRichEdit, vysledok);
        ShowWindow(hwndRichEdit, SW_SHOW);
    }

	return hwndTabCtrl;             //Použije ho ListLoadNext()
}

