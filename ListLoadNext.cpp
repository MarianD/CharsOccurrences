// ListLoadNext.cpp :
//

#include "ListLoadNext.h"
#include "Helpers.h"
#include "Exports.h"

int CHAROCCURRENCESCALL
ListLoadNext(HWND ParentWin, HWND ListWin, char* FileToLoad, int ShowFlags)
{
    char vysledok[10000] = "";
    spracovanieVstupnehoSuboru(vysledok, FileToLoad);

    strcat(vysledok, "\n\n *** Volala sa funkcia ListLoadNext() ***");      // TODO: Len pre ladenie - vyhodi� potom

// TODO: Toto zmeni� - prisp�sobi� pre Tab Control
    SetWindowText(ListWin, vysledok);
    PostMessage(ParentWin, WM_COMMAND, MAKELONG(0, itm_percent), (LPARAM) ListWin);
    return LISTPLUGIN_OK;
}
