// WndProcs.cpp :
//

#include "WndProcs.h"
#include "CreateTabbedWindow.h"
#include "Constants.h"
#include "Helpers.h"
#include "Classic.h"
#include "Status.h"
#include <wingdi.h>


LRESULT CALLBACK
NewTabCtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND      hwndTabCtrl    =  hWnd;
    HWND      hwndFrom       =  0;
    NMHDR  *  pNotifyMsgHdr   =  0;
    int       cx, cy;
    RECT      rect, * pRect  = &rect;

    Status * pStatus        = (Status *) GetProp(hwndTabCtrl, PointerToStatus);
    WNDPROC  oldTabCtrlProc = (WNDPROC) (pStatus->getOldTabCtrlWndProc());


    switch (uMsg)
    {
    case WM_SIZE:
        // Computing of the new rectangle for the child windows
        cx = GET_X_LPARAM(lParam);
        cy = GET_Y_LPARAM(lParam);
        SetRect(pRect, 0, 0, cx, cy);
        TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);

        MoveWindow(pStatus->getHwndListViewAlpha(),  pRect->left, pRect->top,
                   pRect->right  - pRect->left,
                   pRect->bottom - pRect->top,
                   TRUE);

        MoveWindow(pStatus->getHwndListViewDigit(),  pRect->left, pRect->top,
                   pRect->right  - pRect->left,
                   pRect->bottom - pRect->top,
                   TRUE);

        MoveWindow(pStatus->getHwndHistogramAlpha(), pRect->left, pRect->top,
                   pRect->right  - pRect->left,
                   pRect->bottom - pRect->top,
                   TRUE);

        MoveWindow(pStatus->getHwndHistogramDigit(), pRect->left, pRect->top,
                   pRect->right  - pRect->left,
                   pRect->bottom - pRect->top,
                   TRUE);

        MoveWindow(pStatus->getHwndRichEdit(),       pRect->left, pRect->top,
                   pRect->right  - pRect->left,
                   pRect->bottom - pRect->top,
                   TRUE);
        return 0;
    case WM_NOTIFY:
        pNotifyMsgHdr = (NMHDR *) lParam;
        hwndFrom     = pNotifyMsgHdr->hwndFrom;

        switch (pNotifyMsgHdr->code)
        {
        case LVN_COLUMNCLICK:
            LPNMLISTVIEW pnmv;
            int          column;
            int          lastClickedColumn;     // It is increased by 1 to have oportunity to save it with + or -
            int          signum;                // +1 means order in the preferred direction,
                                                // -1 in the opposite direction
            pnmv     = (LPNMLISTVIEW) lParam;
            column   = pnmv->iSubItem;          // Numbered from 0, in spite of deleting the original column zero
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

            ListView_SortItems(hwndFrom, cmpFunction, (LPARAM) signum * column);

            /*
             *  If it was the immediate second click on the same
             *  column's header, let's save it with the minus sign
             */
            if (column == lastClickedColumn)
                column = -column;

            if (hwndFrom == pStatus->getHwndListViewAlpha())
                pStatus->setLastClickedColumnAlpha(column);
            else
                pStatus->setLastClickedColumnDigit(column);

            return 0;       // The return value is ignored
        default:
            break;
        }
    default:
        break;
    }
    return CallWindowProc(oldTabCtrlProc, hWnd, uMsg, wParam, lParam);
}


LRESULT CALLBACK
HistogramProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    int         maxVyskyt =  1;            // It will be the divisor, so it must not be 0
    int         base      = -1;
    int         numChars  = -1;
    TCHAR       baseChar = TEXT('?');

    HWND      hwndTabCtrl   = (HWND)      GetWindowLongPtr(hWnd,  GWLP_HWNDPARENT);
    Classic * pClassic      = (Classic *) GetProp(hwndTabCtrl, PointerToClassic);
    Status  * pStatus       = (Status  *) GetProp(hwndTabCtrl, PointerToClassic);

    switch (uMsg)
    {
    case WM_SIZE:
        // Saving dimension of the client area of histogram window - both of them must have the same dimensions
        pStatus->setHistgClientWidthHight(lParam);
        return 0;
    case WM_PAINT:
        switch (GetWindowLong(hWnd, GWL_ID))
        {
        case HistogramAlphaId:
            base     = 0;
            baseChar = TEXT('A');
            numChars = NumOfCapitalLetters;
            break;
        case HistogramDigitId:
            base     = 0 + NumOfCapitalLetters;
            baseChar = TEXT('0');
            numChars = NumOfDigits;
            break;

        default:
            break;
        }

        hdc = BeginPaint (hWnd, &ps);

        vyskytyPismen = pClassic->getVyskytyPismen();

        for (int i = 0; i < numChars; i++)
        {
            vyskyt    = vyskytyPismen[base + i];
            maxVyskyt = max(maxVyskyt, vyskyt);
        }

        // Getting dimension of the client area of histogram window - both of them must have the same dimensions
        lParam = pStatus->getHistgClientWidthHight();
        cxClient = GET_X_LPARAM (lParam);
        cyClient = GET_Y_LPARAM (lParam);

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

//            SetBkColor(hdc, PALETTEINDEX(COLOR_BACKGROUND));
//            SetBkColor(hdc, RGB(200, 200, 200));
//            SetBkColor(hdc, (COLORREF) GetSysColor(COLOR_BACKGROUND));
            DrawText(hdc, &pismeno, 1, pRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }
        return 0 ;
    default:
        return DefWindowProc (hWnd, uMsg, wParam, lParam);
    }
    return EXIT_SUCCESS;
}
