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


    /********************  Prototypy funkci�  ***********************/

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
    setHeadersArrows(HWND hwndListView, int lastClickedColumn);
#endif // ndef
