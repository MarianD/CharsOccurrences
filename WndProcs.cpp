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

    // Z�skanie manipul�torov dc�rskych okien                   // TODO: Urobi� to lep�ie, z�skan�m predt�m ulo�en�ch manipul�torov vo vlastnostiach rodi�ovsk�ho okna
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
            // V�po�et nov�ho obd�nika pre dc�rske okno
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
            LPNMLISTVIEW pnmv   = (LPNMLISTVIEW) lParam;
            int          stlpec = pnmv->iSubItem;       // ��sluje sa od 0, aj ke� som p�vodn� 0.-t� st�pec vymazal
            ListView_SortItems(hwndListView, cmpFunction, (LPARAM) stlpec);
            break;
//        default:
//            break;
        }
    default:
        break;
    }
    return CallWindowProc(OldTabCtrlProc, hWnd, uMsg, wParam, lParam);
}
