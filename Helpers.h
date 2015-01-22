#ifndef HELPERS_H
    #define HELPERS_H

    #include <windows.h>
    #include <string>
    #include <commctrl.h>
    #include <richedit.h>

    namespace std
    {
        typedef basic_string<TCHAR> tstring;
    }

    using namespace std;


    /********************  Prototypy funkcií  ***********************/

    void
    switchTab(const HWND hwndTabCtrl);

    void
    getFullIniFilePath(TCHAR * result);

    int CALLBACK
    cmpFunction(LPARAM hodnota1, LPARAM hodnota2, LPARAM stlpec);

    void
    InitListViewImageLists(HWND hWndListView);

    void
    paintHistogram(HWND hwndHistogram, HDC hdc, int base, TCHAR baseChar, int numChars);

    void
    setFontSize(HWND hwndSettings, int size);

    void
    setFontBold(HWND hwndSettings, bool isBold);

    void
    selectFont(HWND hwndSettings);

    void
    setHeadersArrows(HWND hwndListView, int lastClickedColumn);

#endif // ndef
