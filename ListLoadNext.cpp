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

    SetWindowText(ListWin, vysledok);
    PostMessage(ParentWin, WM_COMMAND, MAKELONG(0, itm_percent), (LPARAM) ListWin);
    return LISTPLUGIN_OK;
}
