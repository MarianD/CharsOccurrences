#ifndef MSGHANDLERS_H_INCLUDED
    #define MSGHANDLERS_H_INCLUDED

    #include <windows.h>
    #include <windowsx.h>
    #include <commctrl.h>   // For WM_NOTIFY message crackers
    #include <tchar.h>

    int
    TabCtrl_OnLvnColumClick(HWND hwndTabCtrl, INT id, LPNMHDR pnm);

    int
    TabCtrl_OnCustomDraw(LPNMLVCUSTOMDRAW lplvcd);

    void
    TabCtrl_OnSize(HWND hwndTabCtrl, UINT state, int cx, int cy);

    BOOL
    TabCtrl_OnNotify(HWND hwndTabCtrl, INT id, LPNMHDR pnm);

    void
    Histg_OnSize(HWND hwndHistogram, UINT /*state*/, int cx, int cy);

    void
    Histg_OnPaint(HWND hwndHistogram);

    BOOL
    Settings_OnInitDialog(HWND hwndSettings, HWND hwndFocus, LPARAM lParam);

    void
    Settings_OnCommand(HWND hwndSettings, int id, HWND hwndCtl, UINT codeNotify);

#endif // MSGHANDLERS_H_INCLUDED
