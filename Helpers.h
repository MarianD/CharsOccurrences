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
    #include "version.h"

    using namespace std;

    typedef multimap <int, TCHAR, greater<int> > zostupAsociativPole;

    /********************  Prototypy funkcií  ***********************/

    void  nulujPole(int pole[], int pocetPrvkov);
    bool  jeVelkePismeno(int znak);
    bool  jeMalePismeno(int znak);
    int   zmenMaleNaVelke(int pismeno);
    int   naplnAsociativnePole(zostupAsociativPole *parVyskytPismeno, int vyskytyPismen[]);
    void  zobrazCiaru(TCHAR *spolu, TCHAR znak, int pocetMiest);
    void  tlacHlavicky(TCHAR *spolu, int pocetMiest);
    void  tlacVyskytuPismen(TCHAR *spolu, int vyskytyPismen[], int pocetMiest);
    void  tlacVyskytuPismenZoradeny(TCHAR *spolu, zostupAsociativPole *parVyskytPismeno, int pocetMiest);
    int   spoluVyskytov(int vyskytyPismen[]);
    void  tlacVyskytuPismenPodSebou(TCHAR *spolu, int vyskytyPismen[], zostupAsociativPole *parVyskytPismeno, int pocetMiest);
    void  tlacSuctovehoRiadka(TCHAR * spolu, int sucetVyskytov, int pocetMiest);
    void  naplnListView(HWND hwndListView, int * vyskytyPismen);
    void  spracovanieVstupnehoSuboru(TCHAR * spolu, int * vyskytyPismen, TCHAR ** pVertical, const char * FileToLoad);

    #include <windows.h>
    #include <cstdio>
    #include <malloc.h>
    #include <richedit.h>
    #include <commdlg.h>
    #include <cmath>
    #include <commctrl.h>

#endif // ndef
