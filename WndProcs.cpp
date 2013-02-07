// WndProcs.cpp :
//

#include "WndProcs.h"
#include "CreateTabbedWindow.h"
#include "Constants.h"

LRESULT CALLBACK
NewTabCtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND            hwndTabCtrl  = hWnd;
	HWND            hwndRichEdit = 0;
	WNDPROC         OldTabCtrlProc;
    RECT            rect, * pRect = &rect;

    OldTabCtrlProc = (WNDPROC) GetProp(hwndTabCtrl, OLD_TAB_WNDPROC_PROP);

    switch (uMsg)
    {
    case WM_SIZE:
        // Získanie manipulátora dcérskeho okna
        hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);
        if (hwndRichEdit)
        {
            // Výpoèet nového obdåžnika pre dcérske okno
            int cx = GET_X_LPARAM(lParam);
            int cy = GET_Y_LPARAM(lParam);
            SetRect(pRect, 0, 0, cx, cy);
            TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);

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
