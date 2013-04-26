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
	HWND      hwndTabCtrl   = ListWin;
    Classic * pClassic      = (Classic *) GetProp(hwndTabCtrl, PointerToClassic);

    pClassic->spracovanieVstupnehoSuboru(FileToLoad);
    pClassic->naplnListView(pClassic->getHwndListViewAlpha(), CharsTypeAlpha);
    pClassic->naplnListView(pClassic->getHwndListViewDigit(), CharsTypeDigit);

    // Let this another file shows item in the last used order
    int lastClickedColumnAlpha = pClassic->getLastClickedColumnAlpha();
    int lastClickedColumnDigit = pClassic->getLastClickedColumnDigit();

    ListView_SortItems(pClassic->getHwndListViewAlpha(), cmpFunction, lastClickedColumnAlpha);
    ListView_SortItems(pClassic->getHwndListViewDigit(), cmpFunction, lastClickedColumnDigit);


    // Redrawing the histogram by the new values of this next file
    RECT rect, *pRect = &rect;

    GetClientRect (pClassic->getHwndHistogramAlpha(), pRect);

    InvalidateRect(pClassic->getHwndHistogramAlpha(), pRect, TRUE);
    InvalidateRect(pClassic->getHwndHistogramDigit(), pRect, TRUE);
    UpdateWindow  (pClassic->getHwndHistogramAlpha());
    UpdateWindow  (pClassic->getHwndHistogramDigit());

    // Putting the appropriate child window onto top
    switchTab(hwndTabCtrl);

    return LISTPLUGIN_OK;
}
