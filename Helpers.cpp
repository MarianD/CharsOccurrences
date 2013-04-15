// Helpers.cpp :
//

#include "Helpers.h"
#include "Constants.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;


/********************** Pomocne funkcie *************************/

void switchTab(HWND    hwndTabCtrl,        HWND    hwndListViewAlpha,   HWND    hwndListViewDigit,
               HWND    hwndHistogramAlpha, HWND    hwndHistogramDigit,  HWND    hwndRichEdit,
               TCHAR * horizontal,         TCHAR * vertical,            TCHAR * about)
{
    switch (TabCtrl_GetCurSel(hwndTabCtrl))
    {
    case ListViewAlphaTab:
        BringWindowToTop(hwndListViewAlpha);
            break;
    case HistogramAlphaTab:
        BringWindowToTop(hwndHistogramAlpha);
        UpdateWindow    (hwndHistogramAlpha);
        break;
    case ListViewDigitTab:
        BringWindowToTop(hwndListViewDigit);
            break;
    case HistogramDigitTab:
        BringWindowToTop(hwndHistogramDigit);
        UpdateWindow    (hwndHistogramDigit);
        break;
    case VerticalRichEditTab:
        SetWindowText   (hwndRichEdit, vertical);
        BringWindowToTop(hwndRichEdit);
        break;
    case HorizontalRichEditATab:
        SetWindowText   (hwndRichEdit, horizontal);
        BringWindowToTop(hwndRichEdit);
        break;
    case AboutRichEditTab:
        SetWindowText   (hwndRichEdit, about);
        BringWindowToTop(hwndRichEdit);
        break;
    default:
        break;
    }
}


void getHandlesOfChildrensWindows(HWND hwndTabCtrl,         HWND &hwndListViewAlpha,  HWND &hwndListViewDigit,
                                  HWND &hwndHistogramAlpha, HWND &hwndHistogramDigit, HWND &hwndRichEdit)
{
    HWND hwndChildWin =  0;
    long childID      = -1;

    // ZÌskanie manipul·torov dcÈrskych okien
    hwndChildWin = GetWindow(hwndTabCtrl, GW_CHILD);            // Topmost child Window

    while (hwndChildWin)
    {
        switch(childID = GetWindowLong(hwndChildWin, GWL_ID))
        {
        case ListViewAlphaId:
            hwndListViewAlpha  = hwndChildWin;
            break;
        case ListViewDigitId:
            hwndListViewDigit  = hwndChildWin;
            break;
        case HistogramAlphaId:
            hwndHistogramAlpha = hwndChildWin;
            break;
        case HistogramDigitId:
            hwndHistogramDigit = hwndChildWin;
            break;
        case RichEditId:
            hwndRichEdit       = hwndChildWin;
            break;
        default:
            break;
        }
        hwndChildWin = GetWindow(hwndChildWin, GW_HWNDNEXT);
    }
}


void getFullIniFilePath(TCHAR * result)
{
    // Near the top is the declaration  EXTERN_C IMAGE_DOS_HEADER __ImageBase;

    TCHAR   strDLLPath[_MAX_PATH];
    tstring fullIniFilePath;
    int     lastBackSlash;

    /*
     *  At first we get the full path to this DLL, then we erase all
     *  characters after the last backslash and append the name of our
     *  ini file.
     *
     *  The declaration of __ImageBase is near the top (as global)
     */
    GetModuleFileName((HINSTANCE)&__ImageBase, strDLLPath, _MAX_PATH);

    fullIniFilePath = strDLLPath;
    lastBackSlash   = fullIniFilePath.rfind(TEXT('\\'));

    fullIniFilePath.erase(++lastBackSlash).append(INI_FILE);

    lstrcpy(result, fullIniFilePath.c_str());
}


/** \brief CallBack funkcia volan· pri poûiadavke na zoradenie ListView podæa niektorÈho stÂpca
 *
 * \param hodnota1 LPARAM - 1. porovn·van· hodnota ako kombin·cia poËtu v˝skytov a por. ËÌsla pÌsmena (0-25)
 * \param hodnota2 LPARAM - 2. porovn·van· hodnota ako kombin·cia poËtu v˝skytov a por. ËÌsla pÌsmena (0-25)
 * \param stlpec LPARAM   - ËÌslo stÂpca, podæa ktorÈho sa m· zoznam usporiadaù; z·pornÈ ËÌslo stÂpca znamen· poûiadavku na zmenu smeru usporiadania
 * \return int CALLBACK   - z·porn· <, nula pre =, kladn· pre >
 *
 */
int CALLBACK cmpFunction(LPARAM hodnota1, LPARAM hodnota2, LPARAM plusMinusStlpec)
{
    int stlpec  = abs(plusMinusStlpec);                 // Numbered from 1
    int signum  = (plusMinusStlpec < 0) ? -1 : 1;       // Changing the direction of order by the second click
    int result;

    #ifdef _DEBUG
    TCHAR oznam[100];
        _stprintf(oznam, TEXT("Stlpec: %d\nSignum: %d"), stlpec, signum);
        MessageBox(0, oznam, TEXT("Bla"), 0) ;
    #endif

    if (stlpec == 1)
        result = (int) hodnota1 % NumOfCapitalLetters - (int) hodnota2 % NumOfCapitalLetters;
    else
        result = (int) hodnota2 - (int) hodnota1;
    return signum * result;
}


void naplnListView(HWND hwndListView, int * charsOccurrences, int charsType)
{
    int    sucetVyskytov = spoluVyskytov(charsOccurrences, charsType);
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
        int   occur         = charsOccurrences[base + riadok];
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


void nulujPole(int pole[], int pocetPrvkov)
{
    for(int i = 0; i < pocetPrvkov; i++)
        pole[i] = 0;
}


bool jeVelkePismeno(int znak)
{
    if (znak >= 'A' && znak <= 'Z')
        return true;
    else
        return false;
}


bool jeMalePismeno(int znak)
{
    if (znak >= 'a' && znak <= 'z')
        return true;
    else
        return false;
}


int zmenMaleNaVelke(int pismeno)
{
    if (jeMalePismeno(pismeno))
        return pismeno - ('a' - 'A');
    else
        return pismeno;
}


/** \brief Naplnenie asociatÌvneho poæa a zistenie poËtu miest nutn˝ch pre oddelenie poËtu jednotliv˝ch v˝skytov
 *
 * \param  parVyskytPismeno - zostupnÈ asociatÌvne pole, ktorÈ sa m· naplniù
 * \param  pole - pole cel˝ch ËÌsel, v˝skytov prÌsluön˝ch pÌsmen (0. prvok pre A, 1. prvok pre B atÔ.)
 * \return poËet miest potrebn˝ch pre oddelenie ËÌsel v riadku = poËet miest najv‰Ëöieho ËÌsla + 1
 *
 */
//TODO: BuÔ toto urobiù tieû pre parVyskytCislica, alebo do parVyskytPismeno daù aj ËÌslice
int naplnAsociativnePole(zostupAsociativPole *parVyskytPismeno, int pole[])
{
    int pocetMiest = 0;
    int maximum    = 0;

    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        int pocet = pole[i];
        parVyskytPismeno->insert(make_pair(pocet, TEXT('A') + i));
        if (pocet > maximum)
            maximum = pocet;
    }

    maximum = (maximum == 0) ? 1 : maximum;                        // We will get logarithm of it, so it must not be 0
    pocetMiest = floor(log10(maximum)) + 2;                        // PoËet miest najv‰Ëöieho ËÌsla + 1
    return (pocetMiest > POCET_MIEST) ? pocetMiest : POCET_MIEST;
}


void zobrazCiaru(TCHAR *spolu, TCHAR znak, int pocetMiest)
{
    for (int i = 0; i < PRAZD_MIEST + pocetMiest * NumOfCapitalLetters; ++i)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%c"), znak);
    }
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
}


void tlacHlavicky(TCHAR *spolu, int pocetMiest)
{
    zobrazCiaru(spolu + lstrlen(spolu), TEXT('-'), pocetMiest);
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // ZaËiatoËn˝ pr·zdny stÂpec

    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%*s%c"), pocetMiest - 1, "", (TCHAR) ('A' + i));
    }

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
    zobrazCiaru(spolu + lstrlen(spolu), TEXT('-'), pocetMiest);
}


void tlacVyskytuPismen(TCHAR *spolu, int pole[], int pocetMiest)
{
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));

    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        int pocet = pole[i];

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), TEXT("%*d"), pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), pocetMiest, TEXT("-"));
    }

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
}


void tlacVyskytuPismenZoradeny(TCHAR *spolu, zostupAsociativPole *parVyskytPismeno, int pocetMiest)
{
    zobrazCiaru(spolu + lstrlen(spolu), TEXT('*'), pocetMiest);

    /*
     * TlaË hlaviËky s pÌsmenami usporiadan˝mi
     * dæa ich v˝skytu zostupne
    */
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // ZaËiatoËn˝ pr·zdny stÂpec

    for (multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); ++pos)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%*s%c"), pocetMiest - 1, TEXT(""), pos->second);
    }
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    zobrazCiaru(spolu + lstrlen(spolu), TEXT('-'), pocetMiest);

    /*
     * TlaË v˝skytu jednotliv˝ch pÌsmen
    */
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // ZaËiatoËn˝ pr·zdny stÂpec

    for (multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); ++pos)
    {
        int pocet  = pos->first ;

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), TEXT("%*d"), pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), pocetMiest, TEXT("-"));
    }
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    zobrazCiaru(spolu, TEXT('-'), pocetMiest);
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
}


int spoluVyskytov(int charsOccurrences[], int charsType)
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
     *  SËÌtanie vöetk˝ch v˝skytov jednotliv˝ch znakov
     */
    int sucetVyskytov = 0;
    for (int i = 0; i < numChars; ++i)
        sucetVyskytov += charsOccurrences[base + i];

    return (sucetVyskytov == 0) ? 1 : sucetVyskytov;      // It will be the divisor, so it must not be 0
}


void tlacVyskytuPismenPodSebou(TCHAR *spolu, int charsOccurrences[], zostupAsociativPole *parVyskytPismeno,
                               int pocetMiest, int charsType)
{
    int sucetVyskytov = spoluVyskytov(charsOccurrences, charsType);

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin();
    for (int i = 0; i < NumOfCapitalLetters; ++i)
    {
        /*
         *  Najprv ich vytlaËÌme abecedne
         */
        int    pocet   = charsOccurrences[i];
        double percent = (double) pocet / sucetVyskytov * 100.;

        _stprintf(spolu + lstrlen(spolu), TEXT("%c: "), TEXT('A') + i);

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), TEXT("%*d"), pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), pocetMiest, TEXT("-"));

        _stprintf(spolu + lstrlen(spolu), TEXT("  (%5.2f %% )"), percent);

        /*
         *  Teraz ich vytlaËÌme podæa v˝skytov
         */
        _stprintf(spolu + lstrlen(spolu), TEXT("%*c: "), STLP_MEDZERA + 1, pos->second);

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


void tlacSuctovehoRiadka(TCHAR * spolu, int sucetVyskytov, int pocetMiest)
{
    const TCHAR znak           = TEXT('-');
    TCHAR ciara[MAX_DLZ_CIARY];
    int  sirkaStlpcaVyskytov   = (int) (lstrlen(TEXT("A: ")) + pocetMiest);
    int  dlzkaRiadka           = 2 * (sirkaStlpcaVyskytov + lstrlen(TEXT("  (99.99 % )"))) + STLP_MEDZERA;

    for (int i = 0; i < dlzkaRiadka; ++i)
        *(ciara + i) = znak;

    *(ciara + dlzkaRiadka) = '\0';

    _stprintf(spolu + lstrlen(spolu), TEXT("%s\n"), ciara);
    _stprintf(spolu + lstrlen(spolu),
            TEXT("%*d (100.00 %% )%*d (100.00 %% )\n"),
            sirkaStlpcaVyskytov, sucetVyskytov,
            STLP_MEDZERA + sirkaStlpcaVyskytov, sucetVyskytov);
}


void spracovanieVstupnehoSuboru(TCHAR * spolu, int * charsOccurrences, TCHAR ** pVertical, const char * FileToLoad)
{
    FILE *              vstup = 0;
    zostupAsociativPole parVyskytPismeno;
    int                 pocetMiest = 0;

    if ((vstup = fopen(FileToLoad, "rb")) == 0)
    {
        _stprintf (spolu, TEXT("\nOpening of the file\n\n  \"%S\"\n\nfailed ")
                TEXT("(probably it is the folder).\n\n"), FileToLoad);
        return;
    }

    nulujPole(charsOccurrences, NumOfCapitalLetters + NumOfDigits);

    while (!feof(vstup))
    {
        int znak = fgetc(vstup) & 0xFF;

        if (!feof(vstup))
        {
            znak = zmenMaleNaVelke(znak);

            if (jeVelkePismeno(znak))
            {
                int index = znak - 'A';         // Ordinal number of the letter: A = 0, B = 1, C = 2, ...
                charsOccurrences[index]++;
            }
            else if (isdigit(znak))
            {
                int index = znak - '0';
                index += NumOfCapitalLetters;  // Occurrences of digits are just after occurences of letters
                ++charsOccurrences[index];
            }
        }
    }

    fclose(vstup);
    pocetMiest = naplnAsociativnePole(&parVyskytPismeno, charsOccurrences);

    // Filling the string from the beginning
    _stprintf (spolu, TextHead);

    tlacHlavicky(spolu, pocetMiest);
    tlacVyskytuPismen(spolu, charsOccurrences, pocetMiest);
    tlacVyskytuPismenZoradeny(spolu, &parVyskytPismeno, pocetMiest);

    *pVertical  = spolu = spolu + lstrlen(spolu) + sizeof(TCHAR);     // Tu zaËÌna vertik·lny v˝pis; ideme za koncov˙ nulu
    *spolu      = TEXT('\0');                                         // Aby mal ÔalöÌ reùazec nulov˙ dÂûku (len istota)

    // Filling the second part of the string from the beginning, again
    _stprintf (spolu, TextHead);

    tlacVyskytuPismenPodSebou(spolu, charsOccurrences, &parVyskytPismeno, pocetMiest, CharsTypeAlpha);

    int sucetVyskytov = spoluVyskytov(charsOccurrences, CharsTypeAlpha);
    tlacSuctovehoRiadka(spolu, sucetVyskytov, pocetMiest);
}

