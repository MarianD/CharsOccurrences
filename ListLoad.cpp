// ListLoad.cpp :
//

#include "ListLoad.h"
#include "CreateTabbedWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "version.h"

HWND CHAROCCURRENCESCALL
ListLoad(HWND ParentWindow, char* FileToLoad, int ShowFlags)
{
	HWND                hwndTabCtrl  = 0;
	HWND                hwndRichEdit = 0;
	RECT                rect;

    // Vytvorenie okna typu Tab Control a naplnenie rect hodnotami jeho Diasplay Area
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Vytvorenie RichEdit v zobrazovacej Ëast Tab Control
    hwndRichEdit = CreateRichEditWindow(hwndTabCtrl, &rect);

	if (hwndRichEdit)
    {
        char vysledok[10000] = "";
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        strcat(vysledok, "\n\n *** Volala sa funkcia ListLoad() ***");      // TODO: Len pre ladenie - vyhodiù potom

        SetWindowText(hwndRichEdit, vysledok);
        ShowWindow(hwndRichEdit, SW_SHOW);
    }

	return hwndTabCtrl;     // TODO: Vr·tiù manipul·tor spr·vneho okna, lebo ho pouûije ListLoadNext()
}

