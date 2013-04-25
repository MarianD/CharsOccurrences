// Classic.cpp :
//

#include "Classic.h"
#include "Constants.h"


const int
Classic::maxDlzkaCiary = (15 * NumOfCapitalLetters);

Classic::Classic()
  : horizontal   ( (TCHAR *) malloc(MaxCharsHorizAndlVertical           * sizeof(TCHAR)) ),
    about        ( (TCHAR *) malloc((lstrlen(TextAbout) + 10)           * sizeof(TCHAR)) ),
    vyskytyPismen( (int   *) malloc((NumOfCapitalLetters + NumOfDigits) * sizeof(int))   )

{
    _stprintf(about, TextAbout,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

}

Classic::~Classic()
{
    free(vyskytyPismen);
    free(horizontal);
    free(about);
}
void Classic::naplnListView(HWND hwndListView, int charsType) const
{
    int    sucetVyskytov = spoluVyskytov(charsType);
    int    pocetZnakov   = -1;
    int    base          = -1;
    TCHAR  baseChar      = -1;
    LVITEM lvI;

    switch(charsType)
    {
    case CharsTypeAlpha:
        base        = 0;
        pocetZnakov = NumOfCapitalLetters;
        baseChar    = TEXT('A');
        break;
    case CharsTypeDigit:
        base        = 0 + NumOfCapitalLetters;
        pocetZnakov = NumOfDigits;
        baseChar    = TEXT('0');
        break;
    }

    ListView_DeleteAllItems(hwndListView);

    for (int riadok = 0; riadok < pocetZnakov; riadok++)
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
        lvI.lParam   = (LPARAM) (NumOfCapitalLetters * occur + riadok);       // For sorting by columns; NO pocetZnakov!
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


bool Classic::jeVelkePismeno(int znak)
{
    if (znak >= 'A' && znak <= 'Z')
        return true;
    else
        return false;
}


bool Classic::jeMalePismeno(int znak)
{
    if (znak >= 'a' && znak <= 'z')
        return true;
    else
        return false;
}


int Classic::zmenMaleNaVelke(int pismeno)
{
    if (jeMalePismeno(pismeno))
        return pismeno - ('a' - 'A');
    else
        return pismeno;
}


/** \brief Naplnenie asociatívneho po¾a a zistenie poètu miest nutných pre oddelenie poètu jednotlivých výskytov
 *
 * \return poèet miest potrebných pre oddelenie èísel v riadku = poèet miest najväèšieho èísla + 1
 *
 */
void Classic::naplnAsociativnePole()
{
    int maximum    = 0;

    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        int pocet = vyskytyPismen[i];
        parVyskytPismeno.insert(make_pair(pocet, TEXT('A') + i));
        if (pocet > maximum)
            maximum = pocet;
    }

    maximum    = (maximum == 0) ? 1 : maximum;      // We will get logarithm of it, so it must not be 0
    pocetMiest = floor(log10(maximum)) + 2;         // Poèet miest najväèšieho èísla + 1 = poèet miest pre _stprintf()
    pocetMiest = max(pocetMiest, MinPocetMiest);
}


void Classic::zobrazCiaru(TCHAR znak)
{
    for (int i = 0; i < UvodnychMedzier + pocetMiest * NumOfCapitalLetters; ++i)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%c"), znak);
    }
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
}


void Classic::tlacHlavicky()
{
    zobrazCiaru(TEXT('-'));
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), UvodnychMedzier, TEXT(""));     // Zaèiatoèný prázdny ståpec

    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%*s%c"), pocetMiest - 1, "", (TCHAR) ('A' + i));
    }

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
    zobrazCiaru(TEXT('-'));
}


void Classic::tlacVyskytuPismen()
{
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), UvodnychMedzier, TEXT(""));

    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        int pocet = vyskytyPismen[i];

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), TEXT("%*d"), pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), pocetMiest, TEXT("-"));
    }

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
}


void Classic::tlacVyskytuPismenZoradeny()
{
    zobrazCiaru(TEXT('*'));

    /*
     * Tlaè hlavièky s písmenami usporiadanými
     * d¾a ich výskytu zostupne
    */
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), UvodnychMedzier, TEXT(""));     // Zaèiatoèný prázdny ståpec

    for (descendingDirectory::iterator pos = parVyskytPismeno.begin(); pos != parVyskytPismeno.end(); ++pos)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%*s%c"), pocetMiest - 1, TEXT(""), pos->second);
    }
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    zobrazCiaru(TEXT('-'));

    /*
     * Tlaè výskytu jednotlivých písmen
    */
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), UvodnychMedzier, TEXT(""));     // Zaèiatoèný prázdny ståpec

    for (descendingDirectory::iterator pos = parVyskytPismeno.begin(); pos != parVyskytPismeno.end(); ++pos)
    {
        int pocet  = pos->first ;

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), TEXT("%*d"), pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), pocetMiest, TEXT("-"));
    }
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    zobrazCiaru(TEXT('-'));
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
}


int Classic::spoluVyskytov(int charsType) const
{
    int numChars = -1;
    int base     = -1;

    switch(charsType)
    {
    case CharsTypeAlpha:
        base     = 0;
        numChars = NumOfCapitalLetters;
        break;
    case CharsTypeDigit:
        base     = 0 + NumOfCapitalLetters;
        numChars = NumOfDigits;
        break;
    }
    /*
     *  Sèítanie všetkých výskytov jednotlivých znakov
     */
    int sucetVyskytov = 0;
    for (int i = 0; i < numChars; ++i)
        sucetVyskytov += vyskytyPismen[base + i];

    return (sucetVyskytov == 0) ? 1 : sucetVyskytov;      // It will be the divisor, so it must not be 0
}


void Classic::tlacVyskytuPismenPodSebou(int charsType)
{
    int sucetVyskytov = spoluVyskytov(charsType);

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    descendingDirectory::iterator pos = parVyskytPismeno.begin();
    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        /*
         *  Najprv ich vytlaèíme abecedne
         */
        int    pocet   = vyskytyPismen[i];
        double percent = (double) pocet / sucetVyskytov * 100.;

        _stprintf(spolu + lstrlen(spolu), TEXT("%c: "), TEXT('A') + i);

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), TEXT("%*d"), pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), pocetMiest, TEXT("-"));

        _stprintf(spolu + lstrlen(spolu), TEXT("  (%5.2f %% )"), percent);

        /*
         *  Teraz ich vytlaèíme pod¾a výskytov
         */
        _stprintf(spolu + lstrlen(spolu), TEXT("%*c: "), StlpcovaMedzera + 1, pos->second);

        pocet   = pos->first ;
        percent = (double) pocet / sucetVyskytov * 100.;

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), TEXT("%*d"), pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), pocetMiest, TEXT("-"));

        _stprintf(spolu + lstrlen(spolu), TEXT("  (%5.2f %% )\n"), percent);

        ++pos;
    }
}


void Classic::tlacSuctovehoRiadka(int sucetVyskytov)
{
    const TCHAR znak           = TEXT('-');
    TCHAR ciara[maxDlzkaCiary];
    int  sirkaStlpcaVyskytov   = (int) (lstrlen(TEXT("A: ")) + pocetMiest);
    int  dlzkaRiadka           = 2 * (sirkaStlpcaVyskytov + lstrlen(TEXT("  (99.99 % )"))) + StlpcovaMedzera;

    for (int i = 0; i < dlzkaRiadka; ++i)
        *(ciara + i) = znak;

    *(ciara + dlzkaRiadka) = '\0';

    _stprintf(spolu + lstrlen(spolu), TEXT("%s\n"), ciara);
    _stprintf(spolu + lstrlen(spolu),
            TEXT("%*d (100.00 %% )%*d (100.00 %% )\n"),
            sirkaStlpcaVyskytov, sucetVyskytov,
            StlpcovaMedzera + sirkaStlpcaVyskytov, sucetVyskytov);
}


void Classic::spracovanieVstupnehoSuboru(const char * FileToLoad)
{
    FILE  * vstup = 0;
    spolu = horizontal;

    if ((vstup = fopen(FileToLoad, "rb")) == 0)
    {
        _stprintf (spolu, TEXT("\nOpening of the file\n\n  \"%S\"\n\nfailed ")
                TEXT("(probably it is the folder).\n\n"), FileToLoad);
        return;
    }

    nulujPole(vyskytyPismen, NumOfCapitalLetters + NumOfDigits);

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
    _stprintf (spolu, TextHead);

    tlacHlavicky();
    tlacVyskytuPismen();
    tlacVyskytuPismenZoradeny();

    vertical  = spolu = spolu + lstrlen(spolu) + sizeof(TCHAR);     // Tu zaèína vertikálny výpis; ideme za koncovú nulu
    *spolu    = TEXT('\0');                                         // Aby mal ïalší reazec nulovú dåžku (len istota)

    // Filling the second part of the string from the beginning, again
    _stprintf (spolu, TextHead);

    tlacVyskytuPismenPodSebou(CharsTypeAlpha);

    int sucetVyskytov = spoluVyskytov(CharsTypeAlpha);
    tlacSuctovehoRiadka(sucetVyskytov);
}

