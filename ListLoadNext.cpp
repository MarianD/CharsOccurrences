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
    Classic * pClassic          = (Classic *) GetProp(hwndTabCtrl, cn::PointerToClassic);
    Status  * pStatus           = (Status *)  GetProp(hwndTabCtrl, cn::PointerToStatus );
    HWND      hwndListViewAlpha = pStatus->getHwndListViewAlpha();
    HWND      hwndListViewDigit = pStatus->getHwndListViewDigit();
    HWND      hwndRichEdit      = pStatus->getHwndRichEdit();

    pClassic->spracovanieVstupnehoSuboru(FileToLoad);
    pClassic->naplnListView(hwndListViewAlpha, cn::CharsTypeAlpha);
    pClassic->naplnListView(hwndListViewDigit, cn::CharsTypeDigit);

    // Let this another file shows items in the ListViews in the last used order
    int lastClickedColumnAlpha = pStatus->getLastClickedColumnAlpha();
    int lastClickedColumnDigit = pStatus->getLastClickedColumnDigit();

    (void)
    ListView_SortItems(hwndListViewAlpha, cmpFunction, lastClickedColumnAlpha);
    (void)
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

    // Go to the top of the Rich Edit window
    CHARRANGE chRange;
    chRange.cpMin = 0L;
    chRange.cpMax = 0L;

    (void) SendMessage(hwndRichEdit, EM_EXSETSEL, 0, (LPARAM)&chRange);


    // Putting the appropriate child window onto top
    if (TabCtrl_GetCurSel(hwndTabCtrl) == cn::AboutRichEditTab)     // The tab "About" is not interesting,
    {
        TabCtrl_SetCurSel(hwndTabCtrl, cn::TextViewTab);            // so let it switch to the "Text" tab
        pStatus->setLastChosenTab(cn::TextViewTab);                 // and save it (for latter saving to .ini file)
    }
    switchTab(hwndTabCtrl);

    return LISTPLUGIN_OK;
}
