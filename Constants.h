#define INFO TEXT("CharsOccurrences (Lister plugin), version %ld.%ld.%ld %S\n\n" \
             "Author: Marian Denes")

#define HEAD TEXT("Occurrences of individual ASCII letters, ") \
             TEXT("case insensitive:\n\n")

#define MAX_ZNAKOV              6000
#define MAX_ZNAKOV_INFO          300
#define POCET_VELKYCH_PISMEN    ('Z' - 'A' + 1)
#define MAX_DLZ_CIARY           (15 * POCET_VELKYCH_PISMEN)
#define USKO_VYSKYTOV              0
#define USKO_INFORMACII            1
#define VYSKYTY_VLASTNOST    TEXT("0")
#define INFO_VLASTNOST       TEXT("1")
