/* Contents of file Helpers.h */

#ifndef HELPERS_H
    #define HELPERS_H

    //**************************  Symboly  **************************/

    #define CHYBA	                1
    #define OK		                0
    #define TRUE	                1
    #define FALSE	                0
    #define KONIEC_POLA           (-1)
    #define MAX_ZNAKOV_MENA       256
    #define MAX_DLZ_RIADKA       1000
    #define POCET_MIEST             5
    #define PRAZD_MIEST             0
    #define STLP_MEDZERA           14

    #define itm_percent	        0xFFFE

    #include <windows.h>
    #include <tchar.h>
    #include <map>
    #include <string>
    #include <cstdio>
    #include <malloc.h>
    #include <richedit.h>
    #include <commdlg.h>
    #include <cmath>
    #include <commctrl.h>
    #include "version.h"

    namespace std
    {
        typedef basic_string<TCHAR> tstring;
    }

    using namespace std;

    typedef multimap <int, TCHAR, greater<int> > zostupAsociativPole;

    /********************  Prototypy funkcií  ***********************/

    void switchTab(HWND    hwndTabCtrl,   HWND    hwndListView,   HWND    hwndListView1,
                   HWND    hwndHistogram, HWND    hwndHistogram1, HWND    hwndRichEdit,
                   TCHAR * horizontal,    TCHAR * vertical,       TCHAR * about);
    void getHandlesOfChildrensWindows(HWND hwndTabCtrl,    HWND &hwndListView,   HWND &hwndListView1,
                                      HWND &hwndHistogram, HWND &hwndHistogram1, HWND &hwndRichEdit);
    void getFullIniFilePath(TCHAR * result);
    int   CALLBACK
          cmpFunction(LPARAM hodnota1, LPARAM hodnota2, LPARAM stlpec);

#endif // ndef
