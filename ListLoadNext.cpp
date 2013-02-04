// ListLoadNext.cpp :
//

#include "ListLoadNext.h"
#include "CreateRichEditWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "version.h"
#include "Constants.h"

int CHARSOCCURRENCESCALL
ListLoadNext(HWND ParentWin, HWND ListWin, char* FileToLoad, int ShowFlags)
{
	HWND            hwndTabCtrl  = ListWin;
	HWND            hwndRichEdit = 0;
	TCHAR           info[500];

    _stprintf(info, INFO,
            AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Získanie manipulátora dcérskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

	if (hwndRichEdit)
    {
        TCHAR vysledok[MAX_ZNAKOV] = TEXT("");
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\n *** Volala sa funkcia ListLoadNext() ***"));
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndTabCtrl  = %d"), hwndTabCtrl ->unused);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndRichEdit = %d"), hwndRichEdit->unused);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nsizeof(TCHAR) = %d"), sizeof(TCHAR));

        SetWindowText(hwndRichEdit, vysledok);
        SetProp(hwndTabCtrl, TEXT("Usko 0"), (HANDLE) vysledok);
        SetProp(hwndTabCtrl, TEXT("Usko 1"), (HANDLE) info);
        ShowWindow(hwndRichEdit, SW_SHOW);
        return LISTPLUGIN_OK;
    }
    else
        return LISTPLUGIN_ERROR;
}
