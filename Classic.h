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
        static const
        TCHAR * const       textAbout;
        static const
        TCHAR * const       textHead;
        static const int    maxDlzkaCiary;
        int *               vyskytyPismen;
        descendingDirectory parVyskytPismeno;
        int                 pocetMiest;          // Number of positions of the larger number of occurrences + 1
        TCHAR *             spolu;
        TCHAR *             vertical;
    public:
//        static Classic * getInstance(const char * FileToLoad);
        Classic();
        ~Classic();
        const
        TCHAR * getTextAbout()             {return textAbout;}
        int   * getVyskytyPismen()         {return vyskytyPismen;}
        TCHAR * getHorizontal()            {return spolu;}
        TCHAR * getVertical()              {return vertical;}
        void    spracovanieVstupnehoSuboru (const char * FileToLoad);
        void    naplnListView              (HWND hwndListView, int charsType);
    private:
        int   spoluVyskytov                (int charsType);
        void  nulujPole                    (int * const pole, int pocetPrvkov);
        bool  jeVelkePismeno               (int znak);
        bool  jeMalePismeno                (int znak);
        int   zmenMaleNaVelke              (int pismeno);
        void  naplnAsociativnePole         ();
        void  zobrazCiaru                  (TCHAR znak);
        void  tlacHlavicky                 ();
        void  tlacVyskytuPismen            ();
        void  tlacVyskytuPismenZoradeny    ();
        void  tlacVyskytuPismenPodSebou    (int charsType);
        void  tlacSuctovehoRiadka          (int sucetVyskytov);
    };

#endif // ndef
