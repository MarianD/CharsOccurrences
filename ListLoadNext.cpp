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

    // Získanie manipulátora dcérskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

	if (hwndRichEdit)
    {
        vysledok    = (TCHAR *) GetProp(hwndTabCtrl, VYSKYTY_VLASTNOST);
        info        = (TCHAR *) GetProp(hwndTabCtrl, INFO_VLASTNOST);

//        vysledok[0] = TEXT('\0');
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        #ifdef _DEBUG
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\n *** Volala sa funkcia ListLoadNext() ***"));
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndTabCtrl  = %p"), hwndTabCtrl);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\nhwndRichEdit = %p"),   hwndRichEdit);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nsizeof(TCHAR)   = %d"), sizeof(TCHAR));
            int znakov = lstrlen(vysledok);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\Znakov vysledku = %d"), znakov);
        #endif

        switch (TabCtrl_GetCurSel(hwndTabCtrl))
        {
        case USKO_VYSKYTOV:
            SetWindowText(hwndRichEdit, vysledok);
            break;
        case USKO_INFORMACII:
            SetWindowText(hwndRichEdit, info);
            break;
        default:
            break;
        }
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
