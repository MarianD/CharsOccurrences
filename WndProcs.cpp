// WndProcs.cpp :
//

#include "WndProcs.h"
#include "CreateTabbedWindow.h"
#include "Constants.h"
#include "Helpers.h"

LRESULT CALLBACK
NewTabCtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND            hwndTabCtrl    =  hWnd;
    HWND            hwndChildWin   =  0;
    HWND            hwndHistogram  =  0;
    HWND            hwndListView   =  0;
    HWND            hwndRichEdit   =  0;
    int             childID        = -1;
    RECT            rect, * pRect  = &rect;
    WNDPROC         OldTabCtrlProc;

    OldTabCtrlProc = (WNDPROC) GetProp(hwndTabCtrl, OLD_TAB_WNDPROC_PROP);

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

    switch (uMsg)
    {
    case WM_SIZE:
        if (hwndRichEdit)
        {
            // Výpoèet nového obdåžnika pre dcérske okno
            int cx = GET_X_LPARAM(lParam);
            int cy = GET_Y_LPARAM(lParam);
            SetRect(pRect, 0, 0, cx, cy);
            TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);

            MoveWindow(hwndListView,   pRect->left, pRect->top,
                       pRect->right  - pRect->left,
                       pRect->bottom - pRect->top,
                       TRUE);

            MoveWindow(hwndHistogram,  pRect->left, pRect->top,
                       pRect->right  - pRect->left,
                       pRect->bottom - pRect->top,
                       TRUE);

            MoveWindow(hwndRichEdit,   pRect->left, pRect->top,
                       pRect->right  - pRect->left,
                       pRect->bottom - pRect->top,
                       TRUE);
        }
        break;
    case WM_NOTIFY:
        switch ( ((NMHDR *) lParam) -> code)
        {
        case LVN_COLUMNCLICK:
            LPNMLISTVIEW pnmv;
            int          column;
            int          lastClickedColumn;     // It is increased by 1 to have oportunity to save it with + or -
            int          signum;                // +1 means order in the preferred direction,
                                                // -1 in the opposite direction
            pnmv   = (LPNMLISTVIEW) lParam;
            column = pnmv->iSubItem;            // Numbered from 0, in spite of deletening the original column zero
            column++;                           // Now numbered from 1

            /*
             *  Let the sorting by the column 3 ("Percent") is the same as the sorting by
             *  the column 2 ("Count") to don't confuse the user by no reaction after
             *  clicking alternately to the headers of the column 2 and column 3 -
             *  now both of them will behave as one unit (changing the sorting direction)
             */
            if (column == 3)
                column = 2;

            lastClickedColumn = (INT64) GetProp(hwndListView, LAST_CLICKED_COLUMN);

            /*
             *  Changing the direction of order by the second click
             *  on the same column's header
             */
            signum = (column == lastClickedColumn) ? -1 : 1;

            #ifdef _DEBUG
                TCHAR oznam[100];
                _stprintf(oznam, TEXT("Column: %d\nlastClickedColumn: %d"),
                          column, lastClickedColumn);
                MessageBox(0, oznam, TEXT("Bla"), 0) ;
            #endif

            ListView_SortItems(hwndListView, cmpFunction, (LPARAM) signum * column);

            /*
             *  If it was the immediate second click on the same
             *  column's header, let's save it with the minus sign
             */
            if (column == lastClickedColumn)
                column = -column;

            SetProp(hwndListView, LAST_CLICKED_COLUMN, (HANDLE) column);
            break;
        default:
            break;
        }
    default:
        break;
    }
    return CallWindowProc(OldTabCtrlProc, hWnd, uMsg, wParam, lParam);
}


LRESULT CALLBACK
HistogramProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND            hwndHistogram = hWnd;
    HWND            hwndTabCtrl   = GetParent(hwndHistogram);
    RECT            rect, * pRect = &rect;
    int             cx, cy;

    switch (uMsg)
    {
    case WM_SIZE:
        break;
    default:
        return DefWindowProc (hWnd, uMsg, wParam, lParam);
        break;
    }
    return EXIT_SUCCESS;
}
