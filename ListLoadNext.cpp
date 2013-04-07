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
	HWND    hwndTabCtrl   = ListWin;
	HWND    hwndListView  = 0;	HWND    hwndHistogram = 0;
	HWND    hwndRichEdit  = 0;
    int    *vyskytyPismen;
    TCHAR  *vysledok;
    TCHAR  *horizontal;
    TCHAR  *about;
    TCHAR  *vertical;

    vyskytyPismen = (int   *) GetProp(hwndTabCtrl, LISTVIEW_PROP);   // Len ukazovateæ na skutoËne alokovan˝ reùazec
    vysledok      = (TCHAR *) GetProp(hwndTabCtrl, HORIZONTAL_PROP); // Len ukazovateæ na skutoËne alokovan˝ reùazec
    about         = (TCHAR *) GetProp(hwndTabCtrl, ABOUT_PROP);
    horizontal    = vysledok;

    // Getting handles of the child windows
    getHandlesOfChildrensWindows(hwndTabCtrl, hwndListView, hwndHistogram, hwndRichEdit);

	if (hwndListView && hwndHistogram && hwndRichEdit)
    {
        spracovanieVstupnehoSuboru(vysledok, vyskytyPismen, &vertical, FileToLoad);    // M·me aj horizontal (=vysledok), aj vertical
        naplnListView(hwndListView, vyskytyPismen);

        // Let another file shows item in the last used order
        LPARAM lastClickedColumn = (LPARAM) GetProp(hwndListView, LAST_CLICKED_COLUMN);
        ListView_SortItems(hwndListView, cmpFunction, lastClickedColumn);

        #ifdef _DEBUG
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\n *** Volala sa funkcia ListLoadNext() ***"));
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nhwndTabCtrl  = %p"), hwndTabCtrl);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\nhwndRichEdit = %p"),   hwndRichEdit);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\nsizeof(TCHAR)   = %d"), sizeof(TCHAR));
            int znakov = lstrlen(vysledok);
            _stprintf(vysledok + lstrlen(vysledok), TEXT("\n\Znakov vysledku = %d"), znakov);
        #endif

        // Redrawing histogram by new values of the next file
        RECT          rect, *pRect = &rect;
        GetClientRect (hwndHistogram, pRect);
        InvalidateRect(hwndHistogram, pRect, TRUE);
        UpdateWindow  (hwndHistogram);

        switchTab(hwndTabCtrl, hwndListView, hwndHistogram, hwndRichEdit, horizontal, vertical, about);
        return LISTPLUGIN_OK;
    }
    else
    {
        free(vysledok);
        free(about);
        return LISTPLUGIN_ERROR;
    }
}
