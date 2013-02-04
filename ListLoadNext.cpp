// ListLoadNext.cpp :
//

#include "ListLoadNext.h"
#include "CreateRichEditWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "version.h"
#include "Constants.h"

int CHAROCCURRENCESCALL
ListLoadNext(HWND ParentWin, HWND ListWin, char* FileToLoad, int ShowFlags)
{
	HWND            hwndTabCtrl  = ListWin;
	HWND            hwndRichEdit = 0;
	TCHAR           info[500];

    wsprintf(info, INFO,
            AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Získanie manipulátora dcérskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

	if (hwndRichEdit)
    {
        char vysledok[MAX_ZNAKOV] = "";
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        sprintf(vysledok + strlen(vysledok), "\n\n *** Volala sa funkcia ListLoadNext() ***");      // TODO: Len pre ladenie - vyhodi potom
        sprintf(vysledok + strlen(vysledok), "\n\nhwndTabCtrl  = %d", hwndTabCtrl ->unused);
        sprintf(vysledok + strlen(vysledok), "\n\nhwndRichEdit = %d", hwndRichEdit->unused);

        SetWindowText(hwndRichEdit, vysledok);
        SetProp(hwndTabCtrl, "Usko 0", vysledok);
        SetProp(hwndTabCtrl, "Usko 1", info);
        ShowWindow(hwndRichEdit, SW_SHOW);
        return LISTPLUGIN_OK;
    }
    else
        return LISTPLUGIN_ERROR;
}
