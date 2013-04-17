/* Contents of file Classic.h */

#ifndef CLASSIC_H
    #define CLASSIC_H

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
    #include <cmath>
    #include <commctrl.h>

    #include "version.h"

    namespace std
    {
        typedef basic_string<TCHAR> tstring;
    }

    using namespace std;

    typedef multimap <int, TCHAR, greater<int> > zostupAsociativPole;

    class Classic
    {
    private:
        static const TCHAR * const textAbout;
        static const TCHAR * const textHead;
        static const int MAX_DLZ_CIARY;
    public:
        static const TCHAR * getTextAbout() {return textAbout;}
        static void  spracovanieVstupnehoSuboru(TCHAR * spolu, int * vyskytyPismen, TCHAR ** pVertical, const char * FileToLoad);
        static int   spoluVyskytov(int vyskytyPismen[], int charsType);
        static void  naplnListView(HWND hwndListView, int * vyskytyPismen, int charsType);
    private:
        static void  nulujPole(int pole[], int pocetPrvkov);
        static bool  jeVelkePismeno(int znak);
        static bool  jeMalePismeno(int znak);
        static int   zmenMaleNaVelke(int pismeno);
        static int   naplnAsociativnePole(zostupAsociativPole *parVyskytPismeno, int vyskytyPismen[]);
        static void  zobrazCiaru(TCHAR *spolu, TCHAR znak, int pocetMiest);
        static void  tlacHlavicky(TCHAR *spolu, int pocetMiest);
        static void  tlacVyskytuPismen(TCHAR *spolu, int vyskytyPismen[], int pocetMiest);
        static void  tlacVyskytuPismenZoradeny(TCHAR *spolu, zostupAsociativPole *parVyskytPismeno, int pocetMiest);
        static void  tlacVyskytuPismenPodSebou(TCHAR *spolu, int vyskytyPismen[], zostupAsociativPole *parVyskytPismeno,
                                        int pocetMiest, int charsType);
        static void  tlacSuctovehoRiadka(TCHAR * spolu, int sucetVyskytov, int pocetMiest);
    };

#endif // ndef
