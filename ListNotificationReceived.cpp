// ListNotificationReceived.cpp :
//

#include "ListNotificationReceived.h"
#include "CreateRichEditWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "Constants.h"

int CHAROCCURRENCESCALL
ListNotificationReceived(HWND ListWin, int Message, WPARAM wParam, LPARAM lParam)
{
    int     usko;
	HWND    hwndTabCtrl           = ListWin;
	HWND    hwndRichEdit          = 0;
	RECT    rect, *pRect          = &rect;
	char    propName      []      = "Usko X";
	char    propValue[MAX_ZNAKOV] = "*** No value ***";

    // ZÌskanie manipul·tora dcÈrskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

    if (Message == WM_NOTIFY)
    {
        switch ( ((NMHDR *) lParam) -> code)
        {
        case TCN_SELCHANGING:
            usko = TabCtrl_GetCurSel(ListWin);
            propName[5] = '0' + usko;
            GetWindowText(hwndRichEdit, propValue, MAX_ZNAKOV - 1);
//            SetProp(hwndTabCtrl, propName, (HANDLE) propValue);
            break;
        case TCN_SELCHANGE:
            usko = TabCtrl_GetCurSel(ListWin);
            propName[5] = '0' + usko;
            strcpy(propValue, (char *) GetProp(hwndTabCtrl, propName));
            SetWindowText(hwndRichEdit, propValue);
            break;
        case EN_REQUESTRESIZE:
            // ZÌskanie obdÂûnika pre zobrazovaciu Ëasù Tab Control
            TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

            MoveWindow(hwndRichEdit, pRect->left, pRect->top,
                                pRect->right  - pRect->left,
                                pRect->bottom - pRect->top,
                                TRUE);
            break;
        }
    }

    return 0;       // TODO: Daù vyûadovan˙ hodnotu
}
