#ifndef WNDPROCS_H
    #define WNDPROCS_H

    #include <windows.h>
    #include <windowsx.h>
    #include <commctrl.h>   // For WM_NOTIFY message crackers

    LRESULT CALLBACK
    NewTabCtrlProc(HWND hwndTabCtrl, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK
    HistogramProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // WNDPROCS_H
