// WndProcs.cpp :
//

#include "WndProcs.h"
#include "MsgHandlers.h"
#include "Constants.h"
#include "Status.h"


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
    switch (uMsg)
    {
        HANDLE_MSG (hWnd, WM_SIZE,  Histg_OnSize);
        HANDLE_MSG (hWnd, WM_PAINT, Histg_OnPaint);
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return EXIT_SUCCESS;
}


LRESULT CALLBACK
SettingsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
		HANDLE_MSG (hWnd, WM_INITDIALOG, Settings_OnInitDialog);
		HANDLE_MSG (hWnd, WM_COMMAND,    Settings_OnCommand);
    default:
        return FALSE;       // To indicate non-processed message
    }
    return TRUE;            // To indicate processed message
}
