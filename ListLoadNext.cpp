// ListLoadNext.cpp :
//

#include "ListLoadNext.h"
#include "CreateRichEditWindow.h"
#include "Helpers.h"
#include "Exports.h"

int CHAROCCURRENCESCALL
ListLoadNext(HWND ParentWin, HWND ListWin, char* FileToLoad, int ShowFlags)
{
	HWND                hwndTabCtrl  = ListWin;
	HWND                hwndRichEdit = 0;
	RECT                rect;

    // ZÌskanie manipul·tora dcÈrskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

	if (hwndRichEdit)
    {
        char vysledok[10000] = "";
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        strcat(vysledok, "\n\n *** Volala sa funkcia ListLoadNext() ***");      // TODO: Len pre ladenie - vyhodiù potom

        SetWindowText(hwndRichEdit, vysledok);
        ShowWindow(hwndRichEdit, SW_SHOW);
        return LISTPLUGIN_OK;
    }
    else
        return LISTPLUGIN_ERROR;
}
