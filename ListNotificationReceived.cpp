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
    HWND hwndTabCtrl = ListWin;

    if (Message == WM_NOTIFY)
    {
        switch ( ((NMHDR *) lParam) -> code)
        {
        case TCN_SELCHANGING:
            return FALSE;       // Povo¾uje sa zmena uška
        case TCN_SELCHANGE:
            SetProp  (hwndTabCtrl, LastChosenTab, (HANDLE) TabCtrl_GetCurSel(hwndTabCtrl));
            switchTab(hwndTabCtrl);
            return 0;           // To return some (ignored) value
        }
    }
    return 0;       // To return some (ignored) value
}
