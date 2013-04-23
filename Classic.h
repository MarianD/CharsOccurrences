/* Contents of file Classic.h */

#ifndef CLASSIC_H
    #define CLASSIC_H

    //**************************  Symboly  **************************/

    const int MinPocetMiest   =  5;
    const int UvodnychMedzier =  0;
    const int StlpcovaMedzera = 14;

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

    typedef multimap <int, TCHAR, greater<int> > descendingDirectory;

    class Classic
    {
    private:
//        static Classic * singleObject;
        static const TCHAR * const textAbout;
        static const TCHAR * const textHead;
        static const int           maxDlzkaCiary;
        int *                      vyskytyPismen;
        descendingDirectory        parVyskytPismeno;
    public:
//        static Classic * getInstance(const char * FileToLoad);
        Classic();
        ~Classic();
        const TCHAR * getTextAbout() {return textAbout;}
        int * getVyskytyPismen() {return vyskytyPismen;}
        void  spracovanieVstupnehoSuboru(TCHAR * spolu, TCHAR ** pVertical, const char * FileToLoad);
        void  naplnListView(HWND hwndListView, int charsType);
    private:
        int   spoluVyskytov(int charsType);
        void  nulujPole(int * const pole, int pocetPrvkov);
        bool  jeVelkePismeno(int znak);
        bool  jeMalePismeno(int znak);
        int   zmenMaleNaVelke(int pismeno);
        int   naplnAsociativnePole();
        void  zobrazCiaru(TCHAR *spolu, TCHAR znak, int pocetMiest);
        void  tlacHlavicky(TCHAR *spolu, int pocetMiest);
        void  tlacVyskytuPismen(TCHAR *spolu, int pocetMiest);
        void  tlacVyskytuPismenZoradeny(TCHAR *spolu, int pocetMiest);
        void  tlacVyskytuPismenPodSebou(TCHAR *spolu, int pocetMiest, int charsType);
        void  tlacSuctovehoRiadka(TCHAR * spolu, int sucetVyskytov, int pocetMiest);
    };

#endif // ndef
