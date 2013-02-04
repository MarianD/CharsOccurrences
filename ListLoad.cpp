// ListLoad.cpp :
//

#include "ListLoad.h"
#include "CreateTabbedWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "version.h"
#include "Constants.h"

HWND CHAROCCURRENCESCALL
ListLoad(HWND ParentWindow, char* FileToLoad, int ShowFlags)
{
	HWND            hwndTabCtrl  = 0;
	HWND            hwndRichEdit = 0;
	RECT            rect;
	TCHAR           info[500];

    wsprintf(info, INFO,
            AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Vytvorenie okna typu Tab Control a naplnenie rect hodnotami jeho Diasplay Area
    GetClientRect(ParentWindow, &rect);
    hwndTabCtrl = CreateTabbedWindow(ParentWindow, &rect);

    // Z�skanie obd�nika pre zobrazovaciu �as� Tab Control
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

    // Vytvorenie RichEdit v zobrazovacej �ast Tab Control
    hwndRichEdit = CreateRichEditWindow(hwndTabCtrl, &rect);

	if (hwndRichEdit)
    {
        char vysledok[MAX_ZNAKOV] = "";      // TODO: Mo�no treba dlh�ie pole
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        sprintf(vysledok + strlen(vysledok), "\n\n *** Volala sa funkcia ListLoad() ***");      // TODO: Len pre ladenie - vyhodi� potom
        sprintf(vysledok + strlen(vysledok), "\n\nhwndTabCtrl  = %d", hwndTabCtrl ->unused);
        sprintf(vysledok + strlen(vysledok), "\n\nhwndRichEdit = %d", hwndRichEdit->unused);

        SetWindowText(hwndRichEdit, vysledok);
        SetProp(hwndTabCtrl, "Usko 0", vysledok);
        SetProp(hwndTabCtrl, "Usko 1", info);
        ShowWindow(hwndRichEdit, SW_SHOW);
    }

	return hwndTabCtrl;     // TODO: Vr�ti� manipul�tor spr�vneho okna, lebo ho pou�ije ListLoadNext()
}

