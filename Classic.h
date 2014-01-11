#ifndef CLASSIC_H
    #define CLASSIC_H

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
        static const
        TCHAR * const       textHead;
        TCHAR * const       horizontal;
        TCHAR *             vertical;
        TCHAR *             text;
        TCHAR * const       about;
        int   * const       vyskytyPismen;
        TCHAR *             spolu;
        descendingDirectory parVyskytPismeno;
        int                 pocetMiest;         // Number of positions of the larger number of occurrences + 1
        int                 restChars;          // How many chars remainds in the output buffer "spolu"
        bool                warningWritten;
        bool                verticalIsSet;
    public:
        Classic();
       ~Classic();
        const
        TCHAR * getText() const            {return text;}
        const
        TCHAR * getAbout() const           {return about;}
        const
        int   * getVyskytyPismen() const   {return vyskytyPismen;}
        const
        TCHAR * getHorizontal   () const   {return horizontal;}
        const
        TCHAR * getVertical     () const   {return vertical;}
        void    spracovanieVstupnehoSuboru (const char * FileToLoad);
        void    naplnListView              (HWND hwndListView, int charsType) const;
    private:
        Classic                            (const Classic&);     // Declarations only to prevent not wanted
        Classic& operator=                 (const Classic&);     //  public compiler-generated functions
        static
        void    nulujPole                  (int * pole, int pocetPrvkov);
        static
        bool    jeVelkePismeno             (int znak) {return znak >= 'A' && znak <= 'Z';}
        static
        bool    jeMalePismeno              (int znak) {return znak >= 'a' && znak <= 'z';}
        static
        int     zmenMaleNaVelke            (int pismeno);
        void    appendString               (const TCHAR * formatString, ...);
        int     spoluVyskytov              (int charsType) const;
        void    naplnAsociativnePole       ();
        void    zobrazCiaru                (TCHAR znak);
        void    tlacHlavicky               ();
        void    tlacVyskytuPismen          ();
        void    tlacVyskytuPismenZoradeny  ();
        void    tlacVyskytuPismenPodSebou  (int charsType);
        void    tlacSuctovehoRiadka        (int sucetVyskytov);
    };

#endif // ndef
