#ifndef CONSTANTS_H
    #define CONSTANTS_H

    #define ABOUT TEXT("\nCharsOccurrences (Lister plugin), version %ld.%ld.%ld %S\n\n" \
                 "Author: Marian Denes" \
                 "\n\n\nThis plugin is freeware, created in Code::Blocks IDE.")

    #define HEAD TEXT("\nOccurrences of individual ASCII letters, ") \
                 TEXT("case insensitive:\n\n")

    #define MAX_ZNAKOV                  6000
    #define MAX_ZNAKOV_ABOUT             900
    #define POCET_VELKYCH_PISMEN        ('Z' - 'A' + 1)
    #define MAX_DLZ_CIARY               (15 * POCET_VELKYCH_PISMEN)
    #define RICHEDIT_ID                 0
    #define LISTVIEW_ID                 1
    #define HISTOGRAM_ID                2
    #define TAB_LISTVIEW                0
    #define TAB_HISTOGRAM               1
    #define TAB_VERTICAL                2
    #define TAB_HORIZONTAL              3
    #define TAB_ABOUT                   4
    #define LISTVIEW_PROP           TEXT("0")
    #define HISTOGRAM_PROP          TEXT("1")
    #define VERTICAL_PROP           TEXT("2")
    #define HORIZONTAL_PROP         TEXT("3")
    #define ABOUT_PROP              TEXT("4")
    #define OLD_TAB_WNDPROC_PROP    TEXT("OldTabCtrlProc")
    #define DETECT_STRING           "ext=\"TXT\" | force"
    #define LAST_CLICKED_COLUMN     TEXT("Last clicked column")

#endif // ndef
