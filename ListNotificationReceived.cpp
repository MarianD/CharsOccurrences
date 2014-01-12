// ListNotificationReceived.cpp :
//

#include "ListNotificationReceived.h"
#include "CreateRichEditWindow.h"
#include "CreateListViewtWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "Constants.h"
#include "Status.h"

int CHARSOCCURRENCESCALL
ListNotificationReceived(HWND ListWin, int Message, WPARAM /*wParam*/, LPARAM lParam)
{
    HWND hwndTabCtrl = ListWin;
    Status * pStatus = (Status *) GetProp(hwndTabCtrl, cn::PointerToStatus);

    if (Message == WM_NOTIFY)
    {
        switch ( ((NMHDR *) lParam) -> code)
        {
        case TCN_SELCHANGING:
            return FALSE;       // Switching to this tab is permitted
        case TCN_SELCHANGE:
            pStatus->setLastChosenTab(TabCtrl_GetCurSel(hwndTabCtrl));
            switchTab(hwndTabCtrl);
            return 0;           // To return some (ignored) value
        }
    }
    return 0;       // To return some (ignored) value
}
