/* Contents of file Classic.h */

#ifndef CLASSIC_H
    #define CLASSIC_H

    #include <windows.h>


    //**************************  Konštanty  **************************/

    const int     MaxCharsHorizAndlVertical = 6000;
    const int     MinPocetMiest             =    5;
    const int     UvodnychMedzier           =    0;
    const int     StlpcovaMedzera           =   14;
    const
    TCHAR * const TextAbout       = TEXT("\nCharsOccurrences (Lister plugin), version %ld.%ld.%ld %S\n\n"
                                           "Author: Marian Denes\n\n\n"
                                           "This plugin is freeware, created in Code::Blocks IDE.");
    const
    TCHAR * const TextHead        = TEXT("\nOccurrences of individual ASCII letters, " \
                                           "case insensitive:\n\n");

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
        static const int    maxDlzkaCiary;
        TCHAR * const       horizontal;
        TCHAR *             vertical;
        TCHAR * const       about;
        int   * const       vyskytyPismen;
        TCHAR *             spolu;
        descendingDirectory parVyskytPismeno;
        int                 pocetMiest;        // Number of positions of the larger number of occurrences + 1
        HWND                hwndListViewAlpha;
        HWND                hwndListViewDigit;
        HWND                hwndHistogramAlpha;
        HWND                hwndHistogramDigit;
        HWND                hwndRichEdit;
    public:
        Classic();
       ~Classic();
        const
        TCHAR * getAbout() const              {return about;}
        const
        int   * getVyskytyPismen() const      {return vyskytyPismen;}
        const
        TCHAR * getHorizontal() const         {return horizontal;}
        const
        TCHAR * getVertical() const           {return vertical;}
        HWND    getHwndListViewAlpha () const {return hwndListViewAlpha;}
        void    setHwndListViewAlpha (HWND h) {hwndListViewAlpha = h;}
        HWND    getHwndListViewDigit () const {return hwndListViewDigit;}
        void    setHwndListViewDigit (HWND h) {hwndListViewDigit = h;}
        HWND    getHwndHistogramAlpha() const {return hwndHistogramAlpha;}
        void    setHwndHistogramAlpha(HWND h) {hwndHistogramAlpha = h;}
        HWND    getHwndHistogramDigit() const {return hwndHistogramDigit;}
        void    setHwndHistogramDigit(HWND h) {hwndHistogramDigit = h;}
        HWND    getHwndRichEdit      () const {return hwndRichEdit;}
        void    setHwndRichEdit      (HWND h) {hwndRichEdit = h;}
        void    spracovanieVstupnehoSuboru    (const char * FileToLoad);
        void    naplnListView                 (HWND hwndListView, int charsType) const;
    private:
        static
        void    nulujPole                     (int * pole, int pocetPrvkov);
        static
        bool    jeVelkePismeno                (int znak);
        static
        bool    jeMalePismeno                 (int znak);
        static
        int     zmenMaleNaVelke               (int pismeno);
        int     spoluVyskytov                 (int charsType) const;
        void    naplnAsociativnePole          ();
        void    zobrazCiaru                   (TCHAR znak);
        void    tlacHlavicky                  ();
        void    tlacVyskytuPismen             ();
        void    tlacVyskytuPismenZoradeny     ();
        void    tlacVyskytuPismenPodSebou     (int charsType);
        void    tlacSuctovehoRiadka           (int sucetVyskytov);
    };

#endif // ndef
