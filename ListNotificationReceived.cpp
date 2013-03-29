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
    HWND    hwndChildWin  =  0;
    HWND    hwndHistogram =  0;
    HWND    hwndRichEdit  =  0;
    HWND    hwndListView  =  0;
    long    childID       = -1;
    TCHAR  *retazec       =  0;

    // Získanie manipulátorov dcérskych okien                   // TODO: Asi (inde) netreba uklada manipulátory okien vo vlastnostiach rodièovského okna
    hwndChildWin = GetWindow(hwndTabCtrl, GW_CHILD);            // Topmost child Window

    while (hwndChildWin)
    {
        switch(childID = GetWindowLong(hwndChildWin, GWL_ID))
        {
        case LISTVIEW_ID:
            hwndListView  = hwndChildWin;
            break;
        case HISTOGRAM_ID:
            hwndHistogram = hwndChildWin;
            break;
        case RICHEDIT_ID:
            hwndRichEdit  = hwndChildWin;
            break;
        default:
            break;
        }
        hwndChildWin = GetWindow(hwndChildWin, GW_HWNDNEXT);
    }

    if (Message == WM_NOTIFY)
    {
        switch ( ((NMHDR *) lParam) -> code)
        {
        case TCN_SELCHANGING:
            return FALSE;       // Povo¾uje sa zmena uška
            break;
        case TCN_SELCHANGE:
           switch (TabCtrl_GetCurSel(hwndTabCtrl))
            {
            case TAB_LISTVIEW:
                BringWindowToTop(hwndListView);
                break;
            case TAB_HISTOGRAM:
                BringWindowToTop(hwndHistogram);
                break;
            case TAB_VERTICAL:
                retazec = (TCHAR *) GetProp(hwndTabCtrl, VERTICAL_PROP);
                BringWindowToTop(hwndRichEdit);
                break;
            case TAB_HORIZONTAL:
                retazec = (TCHAR *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);
                BringWindowToTop(hwndRichEdit);
                break;
            case TAB_ABOUT:
                retazec = (TCHAR *) GetProp(hwndTabCtrl, ABOUT_PROP);
                BringWindowToTop(hwndRichEdit);
                break;
            default:
                _tcscpy(retazec, TEXT("Error while switching to this tab!"));
                BringWindowToTop(hwndRichEdit);
            }
            SetWindowText(hwndRichEdit, retazec);
            return 0;       // Pre správu TCN_SELCHANGE je návratová hodnota ignorovaná
            break;
        }
    }
    return 0;       // To return some value
}
