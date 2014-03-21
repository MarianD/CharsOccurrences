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


LRESULT CALLBACK HookMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    LPMSG   lpMsg         = (LPMSG) lParam;
    HWND     hwndSettings = GetParent(lpMsg->hwnd);
    HWND     hwndTabCtrl  = GetParent(hwndSettings);
    Status * pStatus      = (Status *) GetProp(hwndTabCtrl, cn::PointerToStatus);
    HHOOK    hHook        = pStatus->getHHook();

   if (nCode >= 0 && PM_REMOVE == wParam)
   {
      // Don't translate non-input events.
      if ( (lpMsg->message >= WM_KEYFIRST && lpMsg->message <= WM_KEYLAST) )
      {

         if (IsDialogMessage(hwndSettings, lpMsg))
         {
            // The value returned from this hookproc is ignored,
            // and it cannot be used to tell Windows the message has been handled.
            // To avoid further processing, convert the message to WM_NULL
            // before returning.
            lpMsg->message = WM_NULL;
            lpMsg->lParam  = 0;
            lpMsg->wParam  = 0;
         }
      }
   }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
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
		HANDLE_MSG (hWnd, WM_DESTROY,    Settings_OnDestroy);
    default:
        return FALSE;       // To indicate non-processed message
    }
    return TRUE;            // To indicate processed message
}
