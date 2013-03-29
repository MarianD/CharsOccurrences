// CreateHistogramWindow.cpp :

#include "CreateHistogramWindow.h"
#include "NaplnStrukturuWndClassEx.h"
#include "Constants.h"

HWND CreateHistogramWindow(HWND ParentWindow, RECT * pRect)
{
    HWND            hwndHistogram;
    HMENU           childID       = (HMENU) HISTOGRAM_ID;
    TCHAR           szClassName[] = TEXT("Histogram");
    WNDCLASSEX      wndClassEx;                         /* Data structure for the Window Class */
    HINSTANCE       hInstance     = NULL;                  /* Optional parameter for CreateWindowEx */

    NaplnStrukturuWndClassEx(&wndClassEx, hInstance, szClassName);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wndClassEx))
        return (HWND) EXIT_FAILURE;

    hwndHistogram = CreateWindowEx(0, szClassName, szClassName,
                                   WS_CHILD | WS_CLIPSIBLINGS,
                                   pRect->left,    pRect->top,
                                   pRect->right  - pRect->left,
                                   pRect->bottom - pRect->top,
                                   ParentWindow, childID, hInstance, NULL);

    if (hwndHistogram)
    {
        // TODO: Asi netreba - Ulo�i� manipul�tor hwndHistogram vo vlastnostiach rodi�ovsk�ho okna
        return hwndHistogram;
    }
    else
    {
        return 0;
    }
}
