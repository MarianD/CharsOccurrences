// Classic.cpp :
//

#include <cstdarg>
#include "Classic.h"
#include "Constants.h"


Classic::Classic()
    // Some initializations are here only for the safety - to have some reasonable values
  : horizontal      ( new TCHAR[MaxCharsHorizAndlVertical] ),
    vertical        ( horizontal ),
    about           ( new TCHAR[AboutLength] ),
    vyskytyPismen   ( new int  [NumOfCapitalLetters + NumOfDigits] ),
    spolu           ( horizontal ),
    parVyskytPismeno(),
    pocetMiest      (MinPocetMiest),
    restChars       (MaxCharsHorizAndlVertical - 1),
    warningWritten  (false),
    verticalIsSet   (false)
{
    _sntprintf(about, AboutLength, TextAbout,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Initializations only for the safety
    restChars      = MaxCharsHorizAndlVertical - 1;
    warningWritten = false;
    verticalIsSet  = false;
}


Classic::~Classic()
{
    delete[] vyskytyPismen;
    delete[] horizontal;
    delete[] about;
}


void Classic::naplnListView(HWND hwndListView, int charsType) const
{
    int
    sucetVyskytov   = max(spoluVyskytov(charsType), 1);         // It will be the divisor, so it must not be 0

    int    base     = (charsType == CharsTypeAlpha) ? 0                   : 0 + NumOfCapitalLetters;
    int    numChars = (charsType == CharsTypeAlpha) ? NumOfCapitalLetters : NumOfDigits;
    TCHAR  baseChar = (charsType == CharsTypeAlpha) ? TEXT('A')           : TEXT('0');
    LVITEM lvI;

    ListView_DeleteAllItems(hwndListView);

    for (int riadok = 0; riadok < numChars; riadok++)
    {
        TCHAR pismeno[]     = TEXT("X");
        pismeno[0]          = baseChar + riadok;
        int   occur         = vyskytyPismen[base + riadok];
        float percent       = (float) occur / sucetVyskytov * 100.;
        TCHAR chOccur  [20];
        TCHAR chPercent[20];

        _stprintf(chOccur,   TEXT("%d"),       occur);
        _stprintf(chPercent, TEXT("%6.2f %%"), percent);

        lvI.mask     = LVIF_TEXT | LVIF_PARAM;
        lvI.iItem    = riadok;
        lvI.iSubItem = 0;
        lvI.pszText  = pismeno;
        lvI.lParam   = (LPARAM) (NumOfCapitalLetters * occur + riadok); // For sorting by columns; don't use numChars!
        ListView_InsertItem(hwndListView, &lvI);

        lvI.mask     = LVIF_TEXT;
        lvI.iSubItem = 1;
        lvI.pszText  = chOccur;
        ListView_SetItem(hwndListView, &lvI);

        lvI.iSubItem = 2;
        lvI.pszText  = chPercent;
        ListView_SetItem(hwndListView, &lvI);
    }
}


void Classic::nulujPole(int * pole, int pocetPrvkov)
{
    for(int i = 0; i < pocetPrvkov; i++)
        pole[i] = 0;
}


int Classic::zmenMaleNaVelke(int pismeno)
{
    return jeMalePismeno(pismeno) ? pismeno - ('a' - 'A') : pismeno;
}


/** \brief Write just formatted string into position showing by pointer "spolu",
 *   if ther is sufficient space indicated by restChars, and updating this pointer
 *   and the restChars
 *
 * \param formatString const TCHAR* - as the first parameter for printf()
 * \param ...
 * \return void
 *
 */
void Classic::appendString(const TCHAR * formatString, ...)
{
    const TCHAR * const warning       = TEXT("\n\n>>>>>>  SPACE FOR APPENDING THE NEXT STRING EXHAUSTED!  <<<<<<");
    const int           criticalSpace = lstrlen(warning) + 100;
    va_list             args;

    va_start(args, formatString);       // Filling the args by variable number of arguments after "formatString"

    if (restChars > criticalSpace)
    {
        restChars -= _vsntprintf(spolu, restChars, formatString, args);
        spolu     += lstrlen(spolu);
    }
    else if (!warningWritten)       // To write the warning only once
    {
        _sntprintf(spolu, lstrlen(warning) + 1, warning);
        warningWritten = true;
        restChars      = -1;        // For safety only

        if (!verticalIsSet)       // Vertical part yet not began
            vertical = spolu;     // Settomg it just at warning message
    }
    va_end(args);
}


/** \brief Naplnenie asociat�vneho po�a a zistenie po�tu miest nutn�ch pre oddelenie po�tu jednotliv�ch v�skytov
 *
 * \return po�et miest potrebn�ch pre oddelenie ��sel v riadku = po�et miest najv��ieho ��sla + 1
 *
 */
void Classic::naplnAsociativnePole()
{
    int maximum = 1;                              // We will get logarithm of it, so it must not be 0
    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        int pocet = vyskytyPismen[i];
        parVyskytPismeno.insert(make_pair(pocet, TEXT('A') + i));
        maximum = max(maximum, pocet);
    }
    pocetMiest = floor(log10(maximum)) + 2;       // Po�et miest najv��ieho ��sla + 1 = po�et miest pre _stprintf()
    pocetMiest = max(pocetMiest, MinPocetMiest);
}


void Classic::zobrazCiaru(TCHAR znak)
{
    for (int i = 0; i < pocetMiest * NumOfCapitalLetters; ++i)
    {
        appendString(TEXT("%c"), znak);
    }
    appendString(TEXT("\n"));
}


void Classic::tlacHlavicky()
{
    zobrazCiaru(TEXT('-'));

    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        appendString(TEXT("%*s%c"), pocetMiest - 1, "", (TCHAR) ('A' + i));
    }
    appendString(TEXT("\n"));
    zobrazCiaru(TEXT('-'));
}


void Classic::tlacVyskytuPismen()
{
    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        int pocet = vyskytyPismen[i];

        if (pocet != 0)
            appendString(TEXT("%*d"), pocetMiest, pocet);
        else
            appendString(TEXT("%*s"), pocetMiest, TEXT("-"));
    }
    appendString(TEXT("\n"));
}


void Classic::tlacVyskytuPismenZoradeny()
{
    zobrazCiaru(TEXT('*'));

    /*
     * Tla� hlavi�ky s p�smenami usporiadan�mi
     * d�a ich v�skytu zostupne
    */
    for (descendingDirectory::iterator pos = parVyskytPismeno.begin(); pos != parVyskytPismeno.end(); ++pos)
    {
        appendString(TEXT("%*s%c"), pocetMiest - 1, TEXT(""), pos->second);
    }
    appendString(TEXT("\n"));
    zobrazCiaru (TEXT('-'));

    /*
     * Tla� v�skytu jednotliv�ch p�smen
    */
    for (descendingDirectory::iterator pos = parVyskytPismeno.begin(); pos != parVyskytPismeno.end(); ++pos)
    {
        int pocet  = pos->first ;

        if (pocet != 0)
            appendString(TEXT("%*d"), pocetMiest, pocet);
        else
            appendString(TEXT("%*s"), pocetMiest, TEXT("-"));
    }
    appendString(TEXT("\n"));
    zobrazCiaru (TEXT('-'));
}


int Classic::spoluVyskytov(int charsType) const
{
    int numChars = (charsType == CharsTypeAlpha) ? NumOfCapitalLetters : NumOfDigits;
    int base     = (charsType == CharsTypeAlpha) ? 0                   : 0 + NumOfCapitalLetters;

    /*
     *  S��tanie v�etk�ch v�skytov jednotliv�ch znakov
     */
    int sucetVyskytov = 0;
    for (int i = 0; i < numChars; ++i)
        sucetVyskytov += vyskytyPismen[base + i];

    return sucetVyskytov;
}


void Classic::tlacVyskytuPismenPodSebou(int charsType)
{
    int
    sucetVyskytov = max(spoluVyskytov(charsType), 1);      // It will be the divisor, so it must not be 0

    appendString(TEXT("\n"));

    descendingDirectory::iterator pos = parVyskytPismeno.begin();
    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        /*
         *  Najprv ich vytla��me abecedne
         */
        int    pocet   = vyskytyPismen[i];
        double percent = (double) pocet / sucetVyskytov * 100.;

        appendString(TEXT("%c: "), TEXT('A') + i);

        if (pocet != 0)
            appendString(TEXT("%*d"), pocetMiest, pocet);
        else
            appendString(TEXT("%*s"), pocetMiest, TEXT("-"));

        appendString(TEXT("  (%5.2f %% )"), percent);

        /*
         *  Teraz ich vytla��me pod�a v�skytov
         */
        appendString(TEXT("%*c: "), StlpcovaMedzera + 1, pos->second);

        pocet   = pos->first ;
        percent = (double) pocet / sucetVyskytov * 100.;

        if (pocet != 0)
            appendString(TEXT("%*d"), pocetMiest, pocet);
        else
            appendString(TEXT("%*s"), pocetMiest, TEXT("-"));

        appendString(TEXT("  (%5.2f %% )\n"), percent);
        ++pos;
    }
}


void Classic::tlacSuctovehoRiadka(int sucetVyskytov)
{
    const TCHAR znak           = TEXT('-');
    int  sirkaStlpcaVyskytov   = (int) (lstrlen(TEXT("A: ")) + pocetMiest);
    int  dlzkaRiadka           = 2 * (sirkaStlpcaVyskytov + lstrlen(TEXT("  (99.99 % )"))) + StlpcovaMedzera;
    TCHAR ciara[dlzkaRiadka + 1];

    for (int i = 0; i < dlzkaRiadka; ++i)
        *(ciara + i) = znak;

    *(ciara + dlzkaRiadka) = '\0';

    appendString(TEXT("%s\n"), ciara);
    const TCHAR *
    formatString = (sucetVyskytov == 0) ?
                    TEXT("%*d  ( 0.00 %% )%*d  ( 0.00 %% )\n") :
                    TEXT("%*d (100.00 %% )%*d (100.00 %% )\n");
    appendString(formatString,
                 sirkaStlpcaVyskytov, sucetVyskytov,
                 StlpcovaMedzera + sirkaStlpcaVyskytov, sucetVyskytov);
}


void Classic::spracovanieVstupnehoSuboru(const char * FileToLoad)
{
    spolu          = horizontal;                    // Reset of the member variable
    *spolu         = TEXT('\0');                    // To have the zero length (for safety only)
    verticalIsSet  = false;                         // For testing whether vertical part already began
    restChars      = MaxCharsHorizAndlVertical - 1;
    warningWritten = false;

    FILE   * vstup = 0;

    if ((vstup = fopen(FileToLoad, "rb")) == 0)
    {
        appendString(TEXT("\nOpening of the file\n\n  \"%S\"\n\nfailed ")
                     TEXT("(probably it is the folder).\n\n"), FileToLoad);
        return;
    }

    // Clearing the counting containers
    nulujPole(vyskytyPismen, NumOfCapitalLetters + NumOfDigits);
    parVyskytPismeno.clear();

    while (!feof(vstup))
    {
        int znak = fgetc(vstup) & 0xFF;

        if (!feof(vstup))
        {
            znak = zmenMaleNaVelke(znak);

            if (jeVelkePismeno(znak))
            {
                int index = znak - 'A';         // Ordinal number of the letter: A = 0, B = 1, C = 2, ...
                vyskytyPismen[index]++;
            }
            else if (isdigit(znak))
            {
                int index = znak - '0';
                index += NumOfCapitalLetters;  // Occurrences of digits are just after occurences of letters
                ++vyskytyPismen[index];
            }
        }
    }
    fclose(vstup);
    naplnAsociativnePole();

    // Filling the string from the beginning
    appendString(TextHead);

    tlacHlavicky();
    tlacVyskytuPismen();
    tlacVyskytuPismenZoradeny();

    if(!warningWritten)             // In the opposite case vertical is already set to warning message
    {
        vertical      = spolu = spolu + lstrlen(spolu) + sizeof(TCHAR);     // Here begins vetical listing; moving after binary zero
        verticalIsSet = true;
        *spolu        = TEXT('\0');                                         // Setting of zero length, only for the safety

        // Filling the second part of the string from the beginning, again
        appendString(TextHead);

        tlacVyskytuPismenPodSebou(CharsTypeAlpha);

        int sucetVyskytov = spoluVyskytov(CharsTypeAlpha);
        tlacSuctovehoRiadka(sucetVyskytov);
    }
}

