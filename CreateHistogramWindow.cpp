// CreateHistogramWindow.cpp :

#include "CreateHistogramWindow.h"
#include "NaplnStrukturuWndClassEx.h"
#include "Constants.h"

HWND CreateHistogramWindow(HWND ParentWindow, RECT * pRect)
{
    HWND       hwndHistogram;
    HMENU      childID       = (HMENU) HISTOGRAM_ID;
    TCHAR      szClassName[] = TEXT("Histogram");
    WNDCLASSEX wndClassEx;                         /* Data structure for the Window Class */
    HINSTANCE  hInstance     = NULL;               /* Optional parameter for CreateWindowEx */

    /* Register the window class */
    NaplnStrukturuWndClassEx(&wndClassEx, hInstance, szClassName);
    RegisterClassEx(&wndClassEx);

    hwndHistogram = CreateWindowEx(0, szClassName, szClassName,
                                   WS_CHILD | WS_CLIPSIBLINGS,
                                   pRect->left,    pRect->top,
                                   pRect->right  - pRect->left,
                                   pRect->bottom - pRect->top,
                                   ParentWindow, childID, hInstance, NULL);

    return hwndHistogram;
}
