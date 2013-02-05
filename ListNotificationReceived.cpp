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
    int     usko;
	HWND    hwndTabCtrl           = ListWin;
	HWND    hwndRichEdit          = 0;
	RECT    rect, *pRect          = &rect;
    TCHAR  *retazec;

    // Z�skanie manipul�tora dc�rskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

    if (Message == WM_NOTIFY)
    {
        switch ( ((NMHDR *) lParam) -> code)
        {
        case TCN_SELCHANGING:
            break;
        case TCN_SELCHANGE:
            switch (TabCtrl_GetCurSel(ListWin))
            {
            case USKO_VYSKYTOV:
                retazec = (TCHAR *) GetProp(hwndTabCtrl, VYSKYTY_VLASTNOST);
                break;
            case USKO_INFORMACII:
                retazec = (TCHAR *) GetProp(hwndTabCtrl, INFO_VLASTNOST);
                break;
            default:
                break;
            }
            SetWindowText(hwndRichEdit, retazec);
            break;
        case EN_REQUESTRESIZE:
            // Z�skanie obd�nika pre zobrazovaciu �as� Tab Control
            TabCtrl_AdjustRect(hwndTabCtrl, FALSE, &rect);

            MoveWindow(hwndRichEdit, pRect->left, pRect->top,
                                pRect->right  - pRect->left,
                                pRect->bottom - pRect->top,
                                TRUE);
            break;
        }
    }

    return 0;       // Pre spr�vu WM_NOTIFY je n�vratov� hodnota ignorovan�
}
