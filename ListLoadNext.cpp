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
    TCHAR          *vysledok;
    TCHAR          *info;

    _stprintf(info, INFO,
            AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Získanie manipulátora dcérskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

	if (hwndRichEdit)
    {
        vysledok    = (TCHAR *) GetProp(hwndTabCtrl, TEXT("Usko 0"));
        info        = (TCHAR *) GetProp(hwndTabCtrl, TEXT("Usko 1"));
        vysledok[0] = TEXT('\0');

        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\n *** Volala sa funkcia ListLoadNext() ***"));
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndTabCtrl  = %d"), hwndTabCtrl ->unused);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndRichEdit = %d"), hwndRichEdit->unused);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nsizeof(TCHAR) = %d"), sizeof(TCHAR));
        int znakov = lstrlen(vysledok);
        _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\Znakov vysledku = %d"), znakov);

        SetWindowText(hwndRichEdit, vysledok);
        ShowWindow(hwndRichEdit, SW_SHOW);
        return LISTPLUGIN_OK;
    }
    else
    {
        free(vysledok);
        free(info);
        return LISTPLUGIN_ERROR;
    }
}
