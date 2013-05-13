// ListLoadNext.cpp :
//

#include "ListLoadNext.h"
#include "CreateRichEditWindow.h"
#include "Helpers.h"
#include "Classic.h"
#include "Status.h"
#include "Exports.h"
#include "version.h"
#include "Constants.h"

int CHARSOCCURRENCESCALL
ListLoadNext(HWND /*ParentWin*/, HWND ListWin, char* FileToLoad, int /*ShowFlags*/)
{
	HWND      hwndTabCtrl       = ListWin;
    Classic * pClassic          = (Classic *) GetProp(hwndTabCtrl, PointerToClassic);
    Status  * pStatus           = (Status *)  GetProp(hwndTabCtrl, PointerToStatus );
    HWND      hwndListViewAlpha = pStatus->getHwndListViewAlpha();
    HWND      hwndListViewDigit = pStatus->getHwndListViewDigit();

    pClassic->spracovanieVstupnehoSuboru(FileToLoad);
    pClassic->naplnListView(hwndListViewAlpha, CharsTypeAlpha);
    pClassic->naplnListView(hwndListViewDigit, CharsTypeDigit);

    // Let this another file shows items in the ListViews in the last used order
    int lastClickedColumnAlpha = pStatus->getLastClickedColumnAlpha();
    int lastClickedColumnDigit = pStatus->getLastClickedColumnDigit();

    ListView_SortItems(hwndListViewAlpha, cmpFunction, lastClickedColumnAlpha);
    ListView_SortItems(hwndListViewDigit, cmpFunction, lastClickedColumnDigit);
    setHeadersArrows  (hwndListViewAlpha, lastClickedColumnAlpha);
    setHeadersArrows  (hwndListViewDigit, lastClickedColumnDigit);

    // Redrawing the histogram by the new values of this next file
    RECT rect, *pRect = &rect;

    GetClientRect (pStatus->getHwndHistogramAlpha(), pRect);

    InvalidateRect(pStatus->getHwndHistogramAlpha(), pRect, TRUE);
    InvalidateRect(pStatus->getHwndHistogramDigit(), pRect, TRUE);
    UpdateWindow  (pStatus->getHwndHistogramAlpha());
    UpdateWindow  (pStatus->getHwndHistogramDigit());

    // Putting the appropriate child window onto top
    switchTab(hwndTabCtrl);

    return LISTPLUGIN_OK;
}
