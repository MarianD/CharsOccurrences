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
    TCHAR          *horizontal;
    TCHAR          *about;
    TCHAR          *vertical;

    // ZÌskanie manipul·tora dcÈrskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

	if (hwndRichEdit)
    {
        vysledok     = (TCHAR *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);   // Len ukazovateæ na skutoËne alokovan˝ reùazec
        about        = (TCHAR *) GetProp(hwndTabCtrl, ABOUT_PROP);
        horizontal   = vysledok;

        spracovanieVstupnehoSuboru(vysledok, &vertical, FileToLoad);    // M·me aj horizontal (=vysledok), aj vertical

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
        case TAB_VERTICAL:
            SetWindowText(hwndRichEdit, vertical);
            break;
        case TAB_HORIZONTAL:
            SetWindowText(hwndRichEdit, horizontal);
            break;
        case TAB_ABOUT:
            SetWindowText(hwndRichEdit, about);
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
        free(about);
        return LISTPLUGIN_ERROR;
    }
}
