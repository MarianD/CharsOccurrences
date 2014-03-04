// WndProcs.cpp :
//

#include "WndProcs.h"
#include "MsgHandlers.h"
#include "Constants.h"
#include "Status.h"

#include "Helpers.h"    // Po nahradení spracovania HistogramProc
#include "Classic.h"    // message cracker-mi tieto 3 pôjdu preč
#include <wingdi.h>


LRESULT CALLBACK
NewTabCtrlProc(HWND hwndTabCtrl, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Status  * pStatus        = (Status *) GetProp(hwndTabCtrl, cn::PointerToStatus);
    WNDPROC   oldTabCtrlProc = (WNDPROC) (pStatus->getOldTabCtrlWndProc());

    switch (uMsg)
    {
        HANDLE_MSG (hwndTabCtrl, WM_SIZE,   TabCtrl_OnSize);
        HANDLE_MSG (hwndTabCtrl, WM_NOTIFY, TabCtrl_OnNotify);
    default:
        return CallWindowProc(oldTabCtrlProc, hwndTabCtrl, uMsg, wParam, lParam);

    }
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
        lParam   = pStatus->getHistgClientWidthHight();
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

        // Vykreslenie obd�nika pre menovky st�pcov histogramu
        xLeft   = zakladna;
        xRight  = zakladna + numChars * zakladna;
        xTop    = 3 * desVysky / 4;
        xBottom = desVysky / 4;
        xTop    = cyClient - xTop;
        xBottom = cyClient - xBottom;

        Rectangle(hdc, xLeft, xTop, xRight, xBottom);

        // Vykreslenie menoviek st�pcov histogramu
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