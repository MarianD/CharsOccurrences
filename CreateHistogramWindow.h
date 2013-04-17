#ifndef CREATEHISTOGRAMWINDOW_H
    #define CREATEHISTOGRAMWINDOW_H

    #include <windows.h>

    const TCHAR * const HistogramClass  = TEXT("ChOcc Histogram");

    HWND CreateHistogramWindow(HWND ParentWindow, RECT * pRect, int id);

#endif // CREATEHISTOGRAMWINDOW_H
