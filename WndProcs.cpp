// WndProcs.cpp :
//

#include "WndProcs.h"
#include "CreateTabbedWindow.h"
#include "Constants.h"

LRESULT CALLBACK
NewTabCtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND            hwndTabCtrl  = hWnd;
	HWND            hwndChildWin = 0;
	HWND            hwndListView = 0;
	HWND            hwndRichEdit = 0;
	WNDPROC         OldTabCtrlProc;
    RECT            rect, * pRect = &rect;

    typedef struct tagPETINFO
    {
        TCHAR szKind [10];
        TCHAR szBreed[50];
        TCHAR szPrice[20];
    } PETINFO;

    PETINFO rgPetInfo[ ] =
    {
        {TEXT("Dog"),  TEXT("Poodle"),     TEXT("$300.00")},
        {TEXT("Cat"),  TEXT("Siamese"),    TEXT("$100.00")},
        {TEXT("Fish"), TEXT("Angel Fish"), TEXT( "$10.00")},
    };

    OldTabCtrlProc = (WNDPROC) GetProp(hwndTabCtrl, OLD_TAB_WNDPROC_PROP);

    switch (uMsg)
    {
    case WM_SIZE:
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
    default:
        break;
    }
    return CallWindowProc(OldTabCtrlProc, hWnd, uMsg, wParam, lParam);
}
