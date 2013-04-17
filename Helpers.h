/* Contents of file Helpers.h */

#ifndef HELPERS_H
    #define HELPERS_H

    #include <windows.h>
    #include <string>
    #include <commctrl.h>

    namespace std
    {
        typedef basic_string<TCHAR> tstring;
    }

    using namespace std;


    /********************  Prototypy funkcií  ***********************/

    void
    switchTab(HWND    hwndTabCtrl,   HWND    hwndListView,   HWND    hwndListView1,
                   HWND    hwndHistogram, HWND    hwndHistogram1, HWND    hwndRichEdit,
                   TCHAR * horizontal,    TCHAR * vertical,       TCHAR * about);
    void
    getHandlesOfChildrensWindows(HWND hwndTabCtrl,    HWND &hwndListView,   HWND &hwndListView1,
                                      HWND &hwndHistogram, HWND &hwndHistogram1, HWND &hwndRichEdit);
    void
    getFullIniFilePath(TCHAR * result);

    int CALLBACK
    cmpFunction(LPARAM hodnota1, LPARAM hodnota2, LPARAM stlpec);

#endif // ndef
