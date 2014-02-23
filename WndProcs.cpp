// WndProcs.cpp :
//

#include "WndProcs.h"
#include "CreateTabbedWindow.h"
#include "Constants.h"
#include "Helpers.h"
#include "Classic.h"
#include "Status.h"
#include <wingdi.h>

//
//  Process WM_SIZE message for window/dialog: TabCtrl
//
void TabCtrl_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    RECT     rect, * pRect  = &rect;
    Status * pStatus        = (Status *) GetProp(hwnd, cn::PointerToStatus);
    WNDPROC  oldTabCtrlProc = (WNDPROC) (pStatus->getOldTabCtrlWndProc());

    FORWARD_WM_SIZE(hwnd, state, cx, cy, oldTabCtrlProc);  // Particularly for displaying arrows for short tabs row

    // Computing of the new rectangle for the child windows
    SetRect(pRect, 0, 0, cx, cy);
    (void)
    TabCtrl_AdjustRect(hwnd, FALSE, pRect);
    pStatus->moveAllChildWindows(pRect);
}

//
//  Process WM_SIZE message for window/dialog: Histg
//
void Histg_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    HWND     hwndTabCtrl = GetParent(hwnd);
    Status * pStatus     = (Status  *) GetProp(hwndTabCtrl, cn::PointerToClassic);

	// Saving dimensions of the client area of histogram window - both of them must have the same dimensions
	pStatus->setHistgClientWidth(cx);
	pStatus->setHistgClientHight(cy);
}

//
//  Process WM_PAINT message for window/dialog: Histg
//
void Histg_OnPaint(HWND hwnd)
{
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        rect, * pRect = &rect;
    int         cxClient;
    int         cyClient;
    const
    int *       vyskytyPismen;             // Array of occurences of individual letters
    int         vyskyt;                    // Occurence of actual letter
    int         xLeft;                     // Positions of 4 verteces of rectangle
    int         xRight;
    int         xTop;
    int         xBottom;
    int         zakladna;                  //  = cxClient / (numChars + 2);
    int         desVysky;                  //  = cyClient / 12;
    int         maxVyska;                  //  = 10 * desVysky;
    int         maxVyskyt   =  1;          // It will be the divisor, so it must not be 0
    int         base        = -1;
    int         numChars    = -1;
    TCHAR       baseChar    = TEXT('?');

    HWND        hwndTabCtrl = (HWND)      GetParent(hwnd);
    Classic *   pClassic    = (Classic *) GetProp(hwndTabCtrl, cn::PointerToClassic);
    Status  *   pStatus     = (Status  *) GetProp(hwndTabCtrl, cn::PointerToClassic);

    switch (GetWindowID(hwnd))
    {
    case cn::HistogramAlphaId:
        base     = 0;
        baseChar = TEXT('A');
        numChars = cn::NumOfCapLetters;
        break;
    case cn::HistogramDigitId:
        base     = 0 + cn::NumOfCapLetters;
        baseChar = TEXT('0');
        numChars = cn::NumOfDigits;
        break;

    default:
        break;
    }

    vyskytyPismen = pClassic->getVyskytyPismen();
    hdc           = BeginPaint (hwnd, &ps);

    for (int i = 0; i < numChars; i++)
    {
        vyskyt    = vyskytyPismen[base + i];
        maxVyskyt = max(maxVyskyt, vyskyt);
    }

    // Getting dimensions of the client area of histogram window - both of them must have the same dimensions
    cxClient = pStatus->getHistgClientWidth();
    cyClient = pStatus->getHistgClientHight();

    // Recalculation of variables used for painting
    zakladna = cxClient / (numChars + 2);
    desVysky = cyClient / 12;
    maxVyska = 10 * desVysky;

    // Painting the histogram
    for (int i = 0; i < numChars; i++)
    {
        vyskyt  = vyskytyPismen[base + i];
        xLeft   = zakladna + i * zakladna;
        xRight  = xLeft + zakladna;
        xTop    = desVysky + (int) ((float) vyskyt / maxVyskyt * maxVyska);
        xBottom = desVysky;
        xTop    = cyClient - xTop;
        xBottom = cyClient - xBottom;

        Rectangle(hdc, xLeft, xTop, xRight, xBottom);
    }

    // Vykreslenie obdåžnika pre menovky ståpcov histogramu
    xLeft   = zakladna;
    xRight  = zakladna + numChars * zakladna;
    xTop    = 3 * desVysky / 4;
    xBottom = desVysky / 4;
    xTop    = cyClient - xTop;
    xBottom = cyClient - xBottom;

    Rectangle(hdc, xLeft, xTop, xRight, xBottom);

    // Vykreslenie menoviek ståpcov histogramu
    for (int i = 0; i < numChars; i++)
    {
        TCHAR pismeno = baseChar + i;
        pRect->left   = zakladna + i * zakladna;
        pRect->right  = pRect->left  + zakladna;
        pRect->top    = 3 * desVysky / 4;
        pRect->bottom = desVysky / 4;
        pRect->top    = cyClient - pRect->top;
        pRect->bottom = cyClient - pRect->bottom;

        DrawText(hdc, &pismeno, 1, pRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    }
}


LRESULT CALLBACK
NewTabCtrlProc(HWND hwndTabCtrl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND                hwndFrom       = nullptr;
    NMHDR             * pNotifyMsgHdr  = nullptr;
    LPNMLVCUSTOMDRAW    lplvcd         = nullptr;
    MEASUREITEMSTRUCT * pMis           = nullptr;
    DRAWITEMSTRUCT    * pDIS           = nullptr;
    Status            * pStatus        = (Status *) GetProp(hwndTabCtrl, cn::PointerToStatus);
    WNDPROC             oldTabCtrlProc = (WNDPROC) (pStatus->getOldTabCtrlWndProc());

    switch (uMsg)
    {
         HANDLE_MSG (hwndTabCtrl, WM_SIZE, TabCtrl_OnSize);

    case WM_NOTIFY:
        pNotifyMsgHdr = (NMHDR *) lParam;
        hwndFrom      = pNotifyMsgHdr->hwndFrom;

        switch (pNotifyMsgHdr->code)
        {
        case LVN_COLUMNCLICK:
            LPNMLISTVIEW pNmLv;
            int          column;
            int          lastClickedColumn;     // It is increased by 1 to have oportunity to save it with + or -

            pNmLv   = (LPNMLISTVIEW) lParam;
            column  = pNmLv->iSubItem;          // Numbered from 0, in spite of deleting the original column zero
            ++column;                           // Now numbered from 1

            /*
             *  Let the sorting by the column 3 ("Percent") is the same as the sorting by
             *  the column 2 ("Count") to don't confuse the user by no reaction after
             *  clicking alternately to the headers of the column 2 and column 3 -
             *  now both of them will behave as one unit (changing the sorting direction)
             */
            if (column == 3)
                column = 2;

            lastClickedColumn = (hwndFrom == pStatus->getHwndListViewAlpha()) ?
                                 pStatus->getLastClickedColumnAlpha() :
                                 pStatus->getLastClickedColumnDigit();

            /*
             *  Changing the direction of the ordering to unprefered if it was
             *  the click on the column's header sorted in the prefered order
             */
            if (column == lastClickedColumn)
                column *= -1;                   // + means preferred, - means unpreferred order

            (void)
            ListView_SortItems(hwndFrom, cmpFunction, (LPARAM) column);
            setHeadersArrows(hwndFrom, column);

            if (hwndFrom == pStatus->getHwndListViewAlpha())
                pStatus->setLastClickedColumnAlpha(column);
            else
                pStatus->setLastClickedColumnDigit(column);

            return 0;       // The return value is ignored

        case NM_CUSTOMDRAW:

            lplvcd = (LPNMLVCUSTOMDRAW)lParam;

            switch(lplvcd->nmcd.dwDrawStage)
            {

            case CDDS_PREPAINT:
                return CDRF_NOTIFYITEMDRAW;

            case CDDS_ITEMPREPAINT:
                SelectObject(lplvcd->nmcd.hdc,
                             CreateFont
                             (
                               -16,                           // nHeight,
                                0,                            // nWidth,
                                0,                            // nEscapement,
                                0,                            // nOrientation,
                                FW_BOLD,                      // fnWeight,
                                0,                            // fdwItalic,
                                0,                            // fdwUnderline,
                                0,                            // fdwStrikeOut,
                                DEFAULT_CHARSET,              // fdwCharSet,
                                OUT_DEFAULT_PRECIS,           // fdwOutputPrecision
                                CLIP_DEFAULT_PRECIS,          // fdwClipPrecision,
                                DEFAULT_QUALITY,              // fdwQuality,
                                FF_DONTCARE | DEFAULT_PITCH,  // fdwPitchAndFamily,
                                TEXT("Courier New")           // lpszFace
                             ));
                return CDRF_NEWFONT;
            }

        default:
            break;
        }
    default:
        break;
    }
    return CallWindowProc(oldTabCtrlProc, hwndTabCtrl, uMsg, wParam, lParam);
}


LRESULT CALLBACK
HistogramProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG (hWnd, WM_SIZE, Histg_OnSize);
        HANDLE_MSG (hWnd, WM_PAINT, Histg_OnPaint);

    default:
        return DefWindowProc (hWnd, uMsg, wParam, lParam);
    }
    return EXIT_SUCCESS;
}
