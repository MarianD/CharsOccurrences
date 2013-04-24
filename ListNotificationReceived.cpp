// ListNotificationReceived.cpp :
//

#include "ListNotificationReceived.h"
#include "CreateRichEditWindow.h"
#include "CreateListViewtWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "Constants.h"
#include "Classic.h"

int CHARSOCCURRENCESCALL
ListNotificationReceived(HWND ListWin, int Message, WPARAM /*wParam*/, LPARAM lParam)
{
    HWND      hwndTabCtrl        = ListWin;
    HWND      hwndListViewAlpha  = 0;
    HWND      hwndListViewDigit  = 0;
    HWND      hwndHistogramAlpha = 0;
    HWND      hwndHistogramDigit = 0;
    HWND      hwndRichEdit       = 0;
    TCHAR   * horizontal         = 0;
    TCHAR   * vertical           = 0;
    TCHAR   * about              = 0;
    Classic * pClassic           = 0;

    // Z�skanie manipul�torov dc�rskych okien
    getHandlesOfChildrensWindows(hwndTabCtrl,        hwndListViewAlpha,  hwndListViewDigit,
                                 hwndHistogramAlpha, hwndHistogramDigit, hwndRichEdit);

    // Getting the pointer to the instance of the class Classic
    pClassic = (Classic *) GetProp(hwndTabCtrl, PointerToClassic);

    if (Message == WM_NOTIFY)
    {
        switch ( ((NMHDR *) lParam) -> code)
        {
        case TCN_SELCHANGING:
            return FALSE;       // Povo�uje sa zmena u�ka
        case TCN_SELCHANGE:
            horizontal = pClassic->getHorizontal();
            vertical   = pClassic->getVertical();
            about      = (TCHAR *) GetProp(hwndTabCtrl, AboutText);

            SetProp  (hwndTabCtrl, LastChosenTab, (HANDLE) TabCtrl_GetCurSel(hwndTabCtrl));

            switchTab(hwndTabCtrl,        hwndListViewAlpha,  hwndListViewDigit,
                      hwndHistogramAlpha, hwndHistogramDigit, hwndRichEdit,      horizontal, vertical, about);

            return 0;           // To return some (ignored) value
        }
    }
    return 0;       // To return some (ignored) value
}
