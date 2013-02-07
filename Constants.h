#define INFO TEXT("\nCharsOccurrences (Lister plugin), version %ld.%ld.%ld %S\n\n" \
             "Author: Marian Denes" \
             "\n\n\nThis plugin is freeware, created in Code::Blocks IDE.")

#define HEAD TEXT("\nOccurrences of individual ASCII letters, ") \
             TEXT("case insensitive:\n\n")

#define MAX_ZNAKOV                  6000
#define MAX_ZNAKOV_INFO              900
#define POCET_VELKYCH_PISMEN        ('Z' - 'A' + 1)
#define MAX_DLZ_CIARY               (15 * POCET_VELKYCH_PISMEN)
#define USKO_VYSKYTOV               0
#define USKO_INFORMACII             1
#define VYSKYTY_VLASTNOST       TEXT("0")
#define INFO_VLASTNOST          TEXT("1")
#define OLD_TAB_WNDPROC_PROP    TEXT("OldTabCtrlProc")
#define OLD_CHILD_WNDPROC_PROP  TEXT("OldChildProc")
