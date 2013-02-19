// WndProcs.cpp :
//

#include "WndProcs.h"
#include "CreateTabbedWindow.h"
#include "Constants.h"
#include "Helpers.h"

LRESULT CALLBACK
NewTabCtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND            hwndTabCtrl  = hWnd;
    HWND            hwndChildWin = 0;
    HWND            hwndListView = 0;
    HWND            hwndRichEdit = 0;
    WNDPROC         OldTabCtrlProc;
    RECT            rect, * pRect = &rect;

    OldTabCtrlProc = (WNDPROC) GetProp(hwndTabCtrl, OLD_TAB_WNDPROC_PROP);

    // Získanie manipulátorov dcérskych okien                   // TODO: Urobi to lepšie, získaním predtým uložených manipulátorov vo vlastnostiach rodièovského okna
    hwndChildWin = GetWindow(hwndTabCtrl, GW_CHILD);            // Topmost child Window

    if ((GetWindowLong(hwndChildWin, GWL_ID)) == RICHEDIT_ID)
    {
        hwndRichEdit = hwndChildWin;
        hwndListView = GetWindow(hwndChildWin, GW_HWNDNEXT);    // Sibling window bellow the hwndChild window
    }
    else if ((GetWindowLong(hwndChildWin, GWL_ID)) == LISTVIEW_ID)
    {
        hwndListView = hwndChildWin;
        hwndRichEdit = GetWindow(hwndChildWin, GW_HWNDNEXT);    // Sibling window bellow the hwndChild window
    }
    else
    {
        BringWindowToTop(hwndRichEdit);
        SetWindowText(hwndRichEdit, TEXT("Error while switching to this tab!"));
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

            MoveWindow(hwndListView, pRect->left, pRect->top,
                       pRect->right  - pRect->left,
                       pRect->bottom - pRect->top,
                       TRUE);

            MoveWindow(hwndRichEdit, pRect->left, pRect->top,
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
                                                //-1 in the opposite direction
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
