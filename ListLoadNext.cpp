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
	HWND    hwndTabCtrl  = ListWin;
	HWND    hwndChildWin = 0;
	HWND    hwndRichEdit = 0;
	HWND    hwndListView = 0;
    int    *vyskytyPismen;
    TCHAR  *vysledok;
    TCHAR  *horizontal;
    TCHAR  *about;
    TCHAR  *vertical;

    vyskytyPismen = (int   *) GetProp(hwndTabCtrl, LISTVIEW_PROP);   // Len ukazovateæ na skutoËne alokovan˝ reùazec
    vysledok      = (TCHAR *) GetProp(hwndTabCtrl, HORIZONTAL_PROP); // Len ukazovateæ na skutoËne alokovan˝ reùazec
    about         = (TCHAR *) GetProp(hwndTabCtrl, ABOUT_PROP);
    horizontal    = vysledok;

    // ZÌskanie manipul·torov dcÈrskych okien
    hwndChildWin = GetWindow(hwndTabCtrl, GW_CHILD);            // Topmost child Window

    if ((GetWindowLong(hwndChildWin, GWL_ID)) == RICHEDIT_ID)
    {
        hwndRichEdit = hwndChildWin;
        hwndListView = GetWindow(hwndChildWin, GW_HWNDNEXT);    // Sibling window bellow the hwndChild window
    }
    else
    {
        hwndListView = hwndChildWin;
        hwndRichEdit = GetWindow(hwndChildWin, GW_HWNDNEXT);    // Sibling window bellow the hwndChild window
    }
    hwndListView = GetWindow(hwndTabCtrl, GW_CHILD);

	if (hwndRichEdit)
    {
        spracovanieVstupnehoSuboru(vysledok, vyskytyPismen, &vertical, FileToLoad);    // M·me aj horizontal (=vysledok), aj vertical
        naplnListView(hwndListView, vyskytyPismen);
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
        case TAB_LISTVIEW:
            BringWindowToTop(hwndListView);
            break;
        case TAB_VERTICAL:
            SetWindowText(hwndRichEdit, vertical);
            BringWindowToTop(hwndRichEdit);
            break;
        case TAB_HORIZONTAL:
            SetWindowText(hwndRichEdit, horizontal);
            BringWindowToTop(hwndRichEdit);            break;
        case TAB_ABOUT:
            SetWindowText(hwndRichEdit, about);
            BringWindowToTop(hwndRichEdit);            break;
        default:
            break;
        }
        return LISTPLUGIN_OK;
    }
    else
    {
        free(vysledok);
        free(about);
        return LISTPLUGIN_ERROR;
    }
}
