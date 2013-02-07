#define ABOUT TEXT("\nCharsOccurrences (Lister plugin), version %ld.%ld.%ld %S\n\n" \
             "Author: Marian Denes" \
             "\n\n\nThis plugin is freeware, created in Code::Blocks IDE.")

#define HEAD TEXT("\nOccurrences of individual ASCII letters, ") \
             TEXT("case insensitive:\n\n")

#define MAX_ZNAKOV                  6000
#define MAX_ZNAKOV_ABOUT              900
#define POCET_VELKYCH_PISMEN        ('Z' - 'A' + 1)
#define MAX_DLZ_CIARY               (15 * POCET_VELKYCH_PISMEN)
#define TAB_VERTICAL                0
#define TAB_HORIZONTAL              1
#define TAB_ABOUT                   2
#define VERTICAL_PROP           TEXT("0")
#define HORIZONTAL_PROP         TEXT("1")
#define ABOUT_PROP              TEXT("2")
#define OLD_TAB_WNDPROC_PROP    TEXT("OldTabCtrlProc")
#define OLD_CHILD_WNDPROC_PROP  TEXT("OldChildProc")
