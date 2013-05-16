// CreateHistogramWindow.cpp :

#include "CreateHistogramWindow.h"
#include "NaplnStrukturuWndClassEx.h"
#include "Constants.h"

HWND CreateHistogramWindow(HWND ParentWindow, RECT * pRect, int id)
{
    HMENU      childID     = (HMENU) (INT64) id;
    HINSTANCE  hInstance   = nullptr;               /* Optional parameter for CreateWindowEx */
    WNDCLASSEX wndClassEx;                       /* Data structure for the Window Class */
    HWND       hwndHistogram;

    /* Register the window class */
    NaplnStrukturuWndClassEx(&wndClassEx, hInstance, HistogramClass);
    RegisterClassEx(&wndClassEx);

    hwndHistogram = CreateWindowEx(0, HistogramClass, HistogramClass,
                                   WS_CHILD | WS_CLIPSIBLINGS,
                                   pRect->left,    pRect->top,
                                   pRect->right  - pRect->left,
                                   pRect->bottom - pRect->top,
                                   ParentWindow, childID, hInstance, nullptr);
    return hwndHistogram;
}
