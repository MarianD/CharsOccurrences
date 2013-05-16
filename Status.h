#ifndef STATUS_H
    #define STATUS_H

    #include <windows.h>

    class Status
    {
    private:
        HWND                hwndListViewAlpha;
        HWND                hwndListViewDigit;
        HWND                hwndHistogramAlpha;
        HWND                hwndHistogramDigit;
        HWND                hwndRichEdit;
        WNDPROC             oldTabCtrlWndProc;
        LPARAM              histgClientWidthHight;
        int                 lastChosenTab;
        int                 lastClickedColumnAlpha;
        int                 lastClickedColumnDigit;
    public:
        Status();
       ~Status();
        HWND    getHwndListViewAlpha      () const      {return hwndListViewAlpha;}
        void    setHwndListViewAlpha      (HWND h)      {hwndListViewAlpha = h;}
        HWND    getHwndListViewDigit      () const      {return hwndListViewDigit;}
        void    setHwndListViewDigit      (HWND h)      {hwndListViewDigit = h;}
        HWND    getHwndHistogramAlpha     () const      {return hwndHistogramAlpha;}
        void    setHwndHistogramAlpha     (HWND h)      {hwndHistogramAlpha = h;}
        HWND    getHwndHistogramDigit     () const      {return hwndHistogramDigit;}
        void    setHwndHistogramDigit     (HWND h)      {hwndHistogramDigit = h;}
        HWND    getHwndRichEdit           () const      {return hwndRichEdit;}
        void    setHwndRichEdit           (HWND h)      {hwndRichEdit = h;}
        WNDPROC getOldTabCtrlWndProc      () const      {return oldTabCtrlWndProc;}
        void    setOldTabCtrlWndProc      (WNDPROC otwp){oldTabCtrlWndProc = otwp;}
        int     getHistgClientWidthHight  () const      {return histgClientWidthHight;}
        void    setHistgClientWidthHight  (LPARAM  hcwh){histgClientWidthHight = hcwh;}
        int     getLastChosenTab          () const      {return lastChosenTab;}
        void    setLastChosenTab          (int lct)     {lastChosenTab = lct;}
        int     getLastClickedColumnAlpha () const      {return lastClickedColumnAlpha;}
        void    setLastClickedColumnAlpha (int col)     {lastClickedColumnAlpha = col;}
        int     getLastClickedColumnDigit () const      {return lastClickedColumnDigit;}
        void    setLastClickedColumnDigit (int col)     {lastClickedColumnDigit = col;}
    private:
        Status             (const Status&);     // Declarations only to prevent not wanted
        Status& operator=  (const Status&);     //  public compiler-generated functions
    };

#endif // ndef
