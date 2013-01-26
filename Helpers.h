/* Contents of file Helpers.h */

#ifndef HELPERS_H
    #define HELPERS_H

    //**************************  Symboly  **************************/

    #define CHYBA	                1
    #define OK		                0
    #define TRUE	                1
    #define FALSE	                0
    #define KONIEC_POLA           (-1)
    #define POCET_VELKYCH_PISMEN  ('Z' - 'A' + 1)
    #define MAX_ZNAKOV_MENA       256
    #define MAX_DLZ_RIADKA       1000
    #define POCET_MIEST             5
    #define PRAZD_MIEST             0
    #define STLP_MEDZERA           14

    #define itm_percent	        0xFFFE

    #include <windows.h>
    #include <map>
    #include "version.h"

    using namespace std;

    typedef multimap <int, char, greater<int> > zostupAsociativPole;

    /********************  Prototypy funkcií  ***********************/

    void  nulujPole(int pole[], int pocetPrvkov);
    bool  jeVelkePismeno(char znak);
    bool  jeMalePismeno(char znak);
    char  zmenMaleNaVelke(char pismeno);
    void  zobrazCiaru(char *spolu, char znak, int pocetMiest);
    void  tlacHlavicky(char *spolu, int pocetMiest);
    void  tlacVyskytuPismen(char *spolu, int vyskytyPismen[], int pocetMiest);
    void  tlacVyskytuPismenZoradeny(char *spolu, zostupAsociativPole *parVyskytPismeno, int pocetMiest);
    int   spoluVyskytov(int vyskytyPismen[]);
    void  tlacVyskytuPismenPodSebou(char *spolu, int vyskytyPismen[], zostupAsociativPole *parVyskytPismeno, int pocetMiest);
    int   naplnAsociativnePole(zostupAsociativPole *parVyskytPismeno, int vyskytyPismen[]);
    void tlacSuctovehoRiadka(char * spolu, int sucetVyskytov, int pocetMiest);
    void  spracovanieVstupnehoSuboru(char * spolu, const char * FileToLoad);

    #include <windows.h>
    #include <cstdio>
    #include <malloc.h>
    #include <richedit.h>
    #include <commdlg.h>
    #include <cmath>

#endif // ndef
