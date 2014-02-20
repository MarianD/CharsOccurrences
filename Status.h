#ifndef STATUS_H
    #define STATUS_H

    #include <windows.h>

    class Status
    {
    private:
        HWND    hwndListViewAlpha;
        HWND    hwndListViewDigit;
        HWND    hwndHistogramAlpha;
        HWND    hwndHistogramDigit;
        HWND    hwndRichEdit;
        HWND    hwndSettings;
        WNDPROC oldTabCtrlWndProc;
        LPARAM  histgClientWidthHight;
        int     lastChosenTab;
        int     lastClickedColumnAlpha;
        int     lastClickedColumnDigit;
        int     fontSize;                 // In points; 1 point = 1/72 of inch
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
        HWND    getHwndSettings           () const      {return hwndSettings;}
        void    setHwndSettings           (HWND h)      {hwndSettings = h;}
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
        int     getFontSize               () const      {return fontSize;}
        void    setFontSize               (int fSize)   {fontSize = fSize;}
        void    moveAllChildWindows       (const PRECT pRect);
    private:
        Status             (const Status&);     // Declarations only to prevent not wanted
        Status& operator=  (const Status&);     //  public compiler-generated functions
    };

#endif // ndef
