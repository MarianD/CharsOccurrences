// Helpers.cpp :
//

#include "Helpers.h"
#include "Constants.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;


/********************** Pomocne funkcie *************************/

void switchTab(HWND hwndTabCtrl, HWND hwndListView, HWND hwndListView1, HWND hwndHistogram, HWND hwndRichEdit,
               TCHAR * horizontal, TCHAR * vertical, TCHAR * about)
{
    switch (TabCtrl_GetCurSel(hwndTabCtrl))
    {
    case TAB_LISTVIEW:
        BringWindowToTop(hwndListView);
            break;
    case TAB_LISTVIEW1:
        BringWindowToTop(hwndListView1);
            break;
    case TAB_HISTOGRAM:
        BringWindowToTop(hwndHistogram);
        UpdateWindow(hwndHistogram);
        break;
    case TAB_VERTICAL:
        SetWindowText(hwndRichEdit, vertical);
        BringWindowToTop(hwndRichEdit);
        break;
    case TAB_HORIZONTAL:
        SetWindowText(hwndRichEdit, horizontal);
        BringWindowToTop(hwndRichEdit);
        break;
    case TAB_ABOUT:
        SetWindowText(hwndRichEdit, about);
        BringWindowToTop(hwndRichEdit);
        break;
    default:
        break;
    }
}


void getHandlesOfChildrensWindows(HWND hwndTabCtrl,
                                  HWND &hwndListView, HWND &hwndListView1, HWND &hwndHistogram, HWND &hwndRichEdit)
{
    HWND    hwndChildWin  =  0;
    long    childID       = -1;

    // Z�skanie manipul�torov dc�rskych okien
    hwndChildWin = GetWindow(hwndTabCtrl, GW_CHILD);            // Topmost child Window

    while (hwndChildWin)
    {
        switch(childID = GetWindowLong(hwndChildWin, GWL_ID))
        {
        case LISTVIEW_ID:
            hwndListView  = hwndChildWin;
            break;
        case LISTVIEW1_ID:
            hwndListView1 = hwndChildWin;
            break;
        case HISTOGRAM_ID:
            hwndHistogram = hwndChildWin;
            break;
        case RICHEDIT_ID:
            hwndRichEdit  = hwndChildWin;
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


/** \brief CallBack funkcia volan� pri po�iadavke na zoradenie ListView pod�a niektor�ho st�pca
 *
 * \param hodnota1 LPARAM - 1. porovn�van� hodnota ako kombin�cia po�tu v�skytov a por. ��sla p�smena (0-25)
 * \param hodnota2 LPARAM - 2. porovn�van� hodnota ako kombin�cia po�tu v�skytov a por. ��sla p�smena (0-25)
 * \param stlpec LPARAM   - ��slo st�pca, pod�a ktor�ho sa m� zoznam usporiada�; z�porn� ��slo st�pca znamen� po�iadavku na zmenu smeru usporiadania
 * \return int CALLBACK   - z�porn� <, nula pre =, kladn� pre >
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
        result = (int) hodnota1 % POCET_VELKYCH_PISMEN - (int) hodnota2 % POCET_VELKYCH_PISMEN;
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
    case CHARS_TYPE_ALPHA:
        pocetZnakov = POCET_VELKYCH_PISMEN;
        base        = 0;
        baseChar    = TEXT('A');
        break;
    case CHARS_TYPE_DIGIT:
        pocetZnakov = POCET_CISLIC;
        base        = 0 + POCET_VELKYCH_PISMEN;
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
        lvI.lParam   = (LPARAM) (POCET_VELKYCH_PISMEN * occur + riadok);       // For sorting by columns; NO pocetZnakov!
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


/** \brief Naplnenie asociat�vneho po�a a zistenie po�tu miest nutn�ch pre oddelenie po�tu jednotliv�ch v�skytov
 *
 * \param  parVyskytPismeno - zostupn� asociat�vne pole, ktor� sa m� naplni�
 * \param  pole - pole cel�ch ��sel, v�skytov pr�slu�n�ch p�smen (0. prvok pre A, 1. prvok pre B at�.)
 * \return po�et miest potrebn�ch pre oddelenie ��sel v riadku = po�et miest najv��ieho ��sla + 1
 *
 */
//TODO: Bu� toto urobi� tie� pre parVyskytCislica, alebo do parVyskytPismeno da� aj ��slice
int naplnAsociativnePole(zostupAsociativPole *parVyskytPismeno, int pole[])
{
    int pocetMiest = 0;
    int maximum    = 0;

    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        int pocet = pole[i];
        parVyskytPismeno->insert(make_pair(pocet, TEXT('A') + i));
        if (pocet > maximum)
            maximum = pocet;
    }

    maximum = (maximum == 0) ? 1 : maximum;                        // We will get logarithm of it, so it must not be 0
    pocetMiest = floor(log10(maximum)) + 2;                        // Po�et miest najv��ieho ��sla + 1
    return (pocetMiest > POCET_MIEST) ? pocetMiest : POCET_MIEST;
}


void zobrazCiaru(TCHAR *spolu, TCHAR znak, int pocetMiest)
{
    for (int i = 0; i < PRAZD_MIEST + pocetMiest * POCET_VELKYCH_PISMEN; i++)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%c"), znak);
    }
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
}


void tlacHlavicky(TCHAR *spolu, int pocetMiest)
{
    zobrazCiaru(spolu + lstrlen(spolu), TEXT('-'), pocetMiest);
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // Za�iato�n� pr�zdny st�pec

    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%*s%c"), pocetMiest - 1, "", (TCHAR) ('A' + i));
    }

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
    zobrazCiaru(spolu + lstrlen(spolu), TEXT('-'), pocetMiest);
}


void tlacVyskytuPismen(TCHAR *spolu, int pole[], int pocetMiest)
{
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));

    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
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
     * Tla� hlavi�ky s p�smenami usporiadan�mi
     * d�a ich v�skytu zostupne
    */
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // Za�iato�n� pr�zdny st�pec

    for (multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); pos++)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%*s%c"), pocetMiest - 1, TEXT(""), pos->second);
    }
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    zobrazCiaru(spolu + lstrlen(spolu), TEXT('-'), pocetMiest);

    /*
     * Tla� v�skytu jednotliv�ch p�smen
    */
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // Za�iato�n� pr�zdny st�pec

    for (multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); pos++)
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
    case CHARS_TYPE_ALPHA:
        base     = 0;
        numChars = POCET_VELKYCH_PISMEN;
        break;
    case CHARS_TYPE_DIGIT:
        base     = 0 + POCET_VELKYCH_PISMEN;
        numChars = POCET_CISLIC;
        break;
    }
    /*
     *  S��tanie v�etk�ch v�skytov jednotliv�ch znakov
     */
    int sucetVyskytov = 0;
    for (int i = 0; i < numChars; i++)
        sucetVyskytov += charsOccurrences[base + i];

    return (sucetVyskytov == 0) ? 1 : sucetVyskytov;      // It will be the divisor, so it must not be 0
}


void tlacVyskytuPismenPodSebou(TCHAR *spolu, int charsOccurrences[], zostupAsociativPole *parVyskytPismeno,
                               int pocetMiest, int charsType)
{
    int sucetVyskytov = spoluVyskytov(charsOccurrences, charsType);

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin();
    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        /*
         *  Najprv ich vytla��me abecedne
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
         *  Teraz ich vytla��me pod�a v�skytov
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

    for (int i = 0; i < dlzkaRiadka; i++)
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

    nulujPole(charsOccurrences, POCET_VELKYCH_PISMEN + POCET_CISLIC);

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
            else if (/*znak >= '0' && znak <= '9'*/ isdigit(znak))
            {
                int index = znak - '0';
                index += POCET_VELKYCH_PISMEN;  // Occurrences of digits are just after occurences of letters
                charsOccurrences[index]++;
            }
        }
    }

    fclose(vstup);
    pocetMiest = naplnAsociativnePole(&parVyskytPismeno, charsOccurrences);

    // Filling the string from the beginning
    _stprintf (spolu, HEAD);

    tlacHlavicky(spolu, pocetMiest);
    tlacVyskytuPismen(spolu, charsOccurrences, pocetMiest);
    tlacVyskytuPismenZoradeny(spolu, &parVyskytPismeno, pocetMiest);

    *pVertical  = spolu = spolu + lstrlen(spolu) + sizeof(TCHAR);     // Tu za��na vertik�lny v�pis; ideme za koncov� nulu
    *spolu      = TEXT('\0');                                         // Aby mal �al�� re�azec nulov� d�ku (len istota)

    // Filling the second part of the string from the beginning, again
    _stprintf (spolu, HEAD);

    tlacVyskytuPismenPodSebou(spolu, charsOccurrences, &parVyskytPismeno, pocetMiest, CHARS_TYPE_ALPHA);

    int sucetVyskytov = spoluVyskytov(charsOccurrences, CHARS_TYPE_ALPHA);
    tlacSuctovehoRiadka(spolu, sucetVyskytov, pocetMiest);
}

