// ListNotificationReceived.cpp :
//

#include "ListNotificationReceived.h"
#include "CreateRichEditWindow.h"
#include "CreateListViewtWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "Constants.h"

int CHARSOCCURRENCESCALL
ListNotificationReceived(HWND ListWin, int Message, WPARAM wParam, LPARAM lParam)
{
    HWND    hwndTabCtrl   =  ListWin;
    HWND    hwndHistogram =  0;
    HWND    hwndRichEdit  =  0;
    HWND    hwndListView  =  0;
    HWND    hwndListView1 =  0;
    TCHAR  *horizontal    =  0;
    TCHAR  *vertical      =  0;
    TCHAR  *about         =  0;

    // Získanie manipulátorov dcérskych okien
    getHandlesOfChildrensWindows(hwndTabCtrl, hwndListView, hwndListView1, hwndHistogram, hwndRichEdit);
    if (Message == WM_NOTIFY)
    {
        switch ( ((NMHDR *) lParam) -> code)
        {
        case TCN_SELCHANGING:
            return FALSE;       // Povo¾uje sa zmena uška
            break;
        case TCN_SELCHANGE:
            horizontal = (TCHAR *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);
            vertical   = (TCHAR *) GetProp(hwndTabCtrl, VERTICAL_PROP);
            about      = (TCHAR *) GetProp(hwndTabCtrl, ABOUT_PROP);

            SetProp  (hwndTabCtrl, LAST_CHOSEN_TAB, (HANDLE) TabCtrl_GetCurSel(hwndTabCtrl));
            switchTab(hwndTabCtrl, hwndListView, hwndListView1, hwndHistogram, hwndRichEdit, horizontal, vertical,
                      about);
            return 0;           // To return some (ignored) value
        }
    }
    return 0;       // To return some (ignored) value
}
