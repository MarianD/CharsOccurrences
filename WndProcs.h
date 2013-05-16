#ifndef WNDPROCS_H
    #define WNDPROCS_H

    #include <windows.h>
    #include <windowsx.h>
    #include <tchar.h>

    LRESULT CALLBACK
    NewTabCtrlProc(HWND hwndTabCtrl, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK
    HistogramProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // WNDPROCS_H
