// ListLoadNext.cpp :
//

#include "ListLoadNext.h"
#include "CreateRichEditWindow.h"
#include "Helpers.h"
#include "Classic.h"
#include "Exports.h"
#include "version.h"
#include "Constants.h"

int CHARSOCCURRENCESCALL
ListLoadNext(HWND /*ParentWin*/, HWND ListWin, char* FileToLoad, int /*ShowFlags*/)
{
	HWND      hwndTabCtrl        = ListWin;
	HWND      hwndListViewAlpha  = 0;
	HWND      hwndListViewDigit  = 0;	HWND      hwndHistogramAlpha = 0;
	HWND      hwndHistogramDigit = 0;
	HWND      hwndRichEdit       = 0;
	Classic * pClassic           = 0;
    TCHAR   * vysledok;
    TCHAR   * horizontal;
    TCHAR   * about;
    TCHAR   * vertical;

    pClassic      = (Classic *) GetProp(hwndTabCtrl, PointerToClassic);
    vysledok      = (TCHAR *)   GetProp(hwndTabCtrl, HorizontalText); // Len ukazovate¾ na skutoène alokovaný reazec
    about         = (TCHAR *)   GetProp(hwndTabCtrl, AboutText);
    horizontal    = vysledok;

    // Getting handles of the child windows
    getHandlesOfChildrensWindows(hwndTabCtrl,        hwndListViewAlpha,  hwndListViewDigit,
                                 hwndHistogramAlpha, hwndHistogramDigit, hwndRichEdit);

	if (hwndListViewAlpha && hwndHistogramAlpha && hwndRichEdit)
    {
        pClassic->spracovanieVstupnehoSuboru(vysledok, &vertical, FileToLoad);    // Máme aj horizontal (=vysledok), aj vertical
        pClassic->naplnListView(hwndListViewAlpha, CharsTypeAlpha);
        pClassic->naplnListView(hwndListViewDigit, CharsTypeDigit);

        // Let another file shows item in the last used order
        LPARAM lastClickedColumn = (LPARAM) GetProp(hwndListViewAlpha, LastClickedColumn);
        ListView_SortItems(hwndListViewAlpha, cmpFunction, lastClickedColumn);

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
        GetClientRect (hwndHistogramAlpha, pRect);
        InvalidateRect(hwndHistogramAlpha, pRect, TRUE);
        InvalidateRect(hwndHistogramDigit, pRect, TRUE);
        UpdateWindow  (hwndHistogramAlpha);
        UpdateWindow  (hwndHistogramDigit);

        switchTab(hwndTabCtrl,        hwndListViewAlpha,  hwndListViewDigit,
                  hwndHistogramAlpha, hwndHistogramDigit, hwndRichEdit,      horizontal, vertical, about);

        return LISTPLUGIN_OK;
    }
    else
    {
        free(vysledok);
        free(about);
        return LISTPLUGIN_ERROR;
    }
}
