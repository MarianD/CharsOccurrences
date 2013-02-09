// ListNotificationReceived.cpp :
//

#include "ListNotificationReceived.h"
#include "CreateRichEditWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "Constants.h"

int CHARSOCCURRENCESCALL
ListNotificationReceived(HWND ListWin, int Message, WPARAM wParam, LPARAM lParam)
{
	HWND    hwndTabCtrl           = ListWin;
	HWND    hwndRichEdit          = 0;
    TCHAR  *retazec               = 0;

    // Získanie manipulátora dcérskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

    if (Message == WM_NOTIFY)
    {
        switch ( ((NMHDR *) lParam) -> code)
        {
        case TCN_SELCHANGING:
            return FALSE;       // Povo¾uje sa zmena uška
            break;
        case TCN_SELCHANGE:
            switch (TabCtrl_GetCurSel(ListWin))
            {
            case TAB_VERTICAL:
                retazec = (TCHAR *) GetProp(hwndTabCtrl, VERTICAL_PROP);
                break;
            case TAB_HORIZONTAL:
                retazec = (TCHAR *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);
                break;
            case TAB_ABOUT:
                retazec = (TCHAR *) GetProp(hwndTabCtrl, ABOUT_PROP);
                break;
            default:
                _tcscpy(retazec, TEXT("Error while switching to this tab!"));
            }
            SetWindowText(hwndRichEdit, retazec);
            return 0;       // Pre správu TCN_SELCHANGE je návratová hodnota ignorovaná
            break;
        case EN_REQUESTRESIZE:
            break;
        }
    }
    return 0;       // To be some return value
}
