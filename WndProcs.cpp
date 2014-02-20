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
NewTabCtrlProc(HWND hwndTabCtrl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND                hwndFrom       = nullptr;
    NMHDR             * pNotifyMsgHdr  = nullptr;
    int                 cx, cy;
    RECT                rect, * pRect  = &rect;
    LPNMLVCUSTOMDRAW    lplvcd         = nullptr;
    MEASUREITEMSTRUCT * pMis           = nullptr;
    DRAWITEMSTRUCT    * pDIS           = nullptr;
    LVITEM              lvi;
    WINDOWPOS           WindowPos;
    Status            * pStatus        = (Status *) GetProp(hwndTabCtrl, cn::PointerToStatus);
    WNDPROC             oldTabCtrlProc = (WNDPROC) (pStatus->getOldTabCtrlWndProc());

    switch (uMsg)
    {
    case WM_SIZE:
        oldTabCtrlProc(hwndTabCtrl, uMsg, wParam, lParam);       // Particularly for displaying arrows for short tabs row

        // Computing of the new rectangle for the child windows
        cx = GET_X_LPARAM(lParam);
        cy = GET_Y_LPARAM(lParam);
        SetRect(pRect, 0, 0, cx, cy);
        (void)
        TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);
        pStatus->moveAllChildWindows(pRect);
        SendMessage(hwndTabCtrl, WM_WINDOWPOSCHANGED, 0, (LPARAM) &WindowPos);  // Aby sa poslala WM_MEASUREITEM
        return 0;

    case WM_DRAWITEM:       // Táto správa sa generuje len pri nastavenom štýle okna LVS_OWNERDRAWFIXED
        MessageBoxA(0, "Prijatá správa WM_DRAWITEM", "WM_DRAWITEM", MB_OK);
        pDIS = (DRAWITEMSTRUCT *) lParam;
        hwndFrom = (pDIS->CtlID == cn::ListViewAlphaId) ? pStatus->getHwndListViewAlpha()
                                                        : pStatus->getHwndListViewDigit();
//        pDIS->rcItem.top    += 20L;
//        pDIS->rcItem.bottom += 85L;
        TCHAR itemText[30];
        lvi.iItem      = pDIS->itemID;
        lvi.iSubItem   = 0;
        lvi.pszText    = itemText;
        lvi.cchTextMax = 30;
        lvi.mask       = LVIF_TEXT;

//        **** Toto mi zhadzuje program, keï zmením ve¾kos okna PRED kliknutím na iné usporiadanie, dokonca aj keï to ****
//        **** sem vôbec nemá ís (keï sa správa VM_DRAWITEM neposiela, pretože v štýle NIE JE LVS_OWNERDRAWFIXED) ****
//        ListView_GetItem(hwndFrom, &lvi);       //TODO: Zisti, preèo mi toto pri zmene ve¾kosti okna zhadzuje program
//        SendMessage(hwndFrom, LVM_GETITEM, 0, (LPARAM) &lvi); // Aj keï použijem toto namiesto makra ListView_GetItem()
//
////        TextOut(pDIS->hDC, pDIS->rcItem.left, pDIS->rcItem.top, lpBuff, len);
//        DrawText(pDIS->hDC, lvi.pszText, -1, &pDIS->rcItem, DT_BOTTOM  /*DT_SINGLELINE | DT_VCENTER*/);
        return TRUE;

    case WM_MEASUREITEM:                      // Táto správa sa posiela len pri zapnutom štýle okna LVS_OWNERDRAWFIXED
        pMis = (MEASUREITEMSTRUCT *) lParam;
        if (pMis->CtlType == ODT_LISTVIEW)
        {
            pMis->itemHeight = 20L;     //Funguje až po zmene ve¾kosti okna, a len v režime Custom Draw
//            MessageBoxA(0, "Prijatá správa VM_MEASUREITEM", "WM_MEASUREITEM", MB_OK);
            return TRUE;
        }
        break;

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
//                GetFontForItem(lplvcd->nmcd.dwItemSpec,
//                               lplvcd->nmcd.lItemlParam) );
//                lplvcd->clrText = GetColorForItem(lplvcd->nmcd.dwItemSpec,
//                                                  lplvcd->nmcd.lItemlParam);
//                lplvcd->clrTextBk = GetBkColorForItem(lplvcd->nmcd.dwItemSpec,
//                                                      lplvcd->nmcd.lItemlParam);

                /* At this point, you can change the background colors for the item
                and any subitems and return CDRF_NEWFONT. If the list-view control
                is in report mode, you can simply return CDRF_NOTIFYSUBITEMDRAW
                to customize the item's subitems individually
                        ...*/
                return CDRF_NEWFONT;
            //  or return CDRF_NOTIFYSUBITEMDRAW;

//            case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
//                SelectObject(lplvcd->nmcd.hdc,
//                             GetFontForSubItem(lplvcd->nmcd.dwItemSpec,
//                                               lplvcd->nmcd.lItemlParam,
//                                               lplvcd->iSubItem));
//                lplvcd->clrText = GetColorForSubItem(lplvcd->nmcd.dwItemSpec,
//                                                     lplvcd->nmcd.lItemlParam,
//                                                     lplvcd->iSubItem));
//                lplvcd->clrTextBk = GetBkColorForSubItem(lplvcd->nmcd.dwItemSpec,
//                                                         lplvcd->nmcd.lItemlParam,
//                                                         lplvcd->iSubItem));
//
//                /* This notification is received only if you are in report mode and
//                returned CDRF_NOTIFYSUBITEMDRAW in the previous step. At
//                this point, you can change the background colors for the
//                subitem and return CDRF_NEWFONT.
//                        ...*/
//                return CDRF_NEWFONT;
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

    HWND        hwndTabCtrl = (HWND)      GetWindowLongPtr(hWnd,  GWLP_HWNDPARENT);
    Classic *   pClassic    = (Classic *) GetProp(hwndTabCtrl, cn::PointerToClassic);
    Status  *   pStatus     = (Status  *) GetProp(hwndTabCtrl, cn::PointerToClassic);

    switch (uMsg)
    {
    case WM_SIZE:
        // Saving dimension of the client area of histogram window - both of them must have the same dimensions
        pStatus->setHistgClientWidthHight(lParam);
        return 0;
    case WM_PAINT:
        switch (GetWindowLong(hWnd, GWL_ID))
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
        hdc           = BeginPaint (hWnd, &ps);

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

            DrawText(hdc, &pismeno, 1, pRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }
        return 0 ;
    default:
        return DefWindowProc (hWnd, uMsg, wParam, lParam);
    }
    return EXIT_SUCCESS;
}
