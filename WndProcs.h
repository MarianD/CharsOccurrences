#ifndef WNDPROCS_H
    #define WNDPROCS_H

    #include <windows.h>
    #include <windowsx.h>
    #include <commctrl.h>   // For WM_NOTIFY message crackers
    #include <tchar.h>

    LRESULT CALLBACK
    NewTabCtrlProc(HWND hwndTabCtrl, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK
    HistogramProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK
    SettingsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK
    HookMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

#endif // WNDPROCS_H
