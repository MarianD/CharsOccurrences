// Helpers.cpp :
//

#include "Helpers.h"
#include "Constants.h"

/********************** Pomocne funkcie *************************/

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
        result = (int) hodnota1 % POCET_VELKYCH_PISMEN - (int) hodnota2 % POCET_VELKYCH_PISMEN;
    else
        result = (int) hodnota2 - (int) hodnota1;
    return signum * result;
}


void naplnListView(HWND hwndListView, int * vyskytyPismen)
{
    int    sucetVyskytov = spoluVyskytov(vyskytyPismen);
    LVITEM lvI;

    ListView_DeleteAllItems(hwndListView);

    for (int riadok = 0; riadok < POCET_VELKYCH_PISMEN; riadok++)
    {
        TCHAR pismeno[] = TEXT("X");
        pismeno[0]      = TEXT('A') + riadok;
        int occur       = vyskytyPismen[riadok];
        float percent   = (float) occur / sucetVyskytov * 100.;
        TCHAR chOccur  [20];
        TCHAR chPercent[20];

        _stprintf(chOccur,   TEXT("%d"),       occur);
        _stprintf(chPercent, TEXT("%6.2f %%"), percent);

        lvI.mask     = LVIF_TEXT | LVIF_PARAM;
        lvI.iItem    = riadok;
        lvI.iSubItem = 0;
        lvI.pszText  = pismeno;
        lvI.lParam   = (LPARAM) (POCET_VELKYCH_PISMEN * occur + riadok);       // For sorting by columns
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
    pocetMiest = floor(log10(maximum)) + 2;                            // PoËet miest najv‰Ëöieho ËÌsla + 1
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
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // ZaËiatoËn˝ pr·zdny stÂpec

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
     * TlaË hlaviËky s pÌsmenami usporiadan˝mi
     * dæa ich v˝skytu zostupne
    */
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // ZaËiatoËn˝ pr·zdny stÂpec

    for (multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); pos++)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%*s%c"), pocetMiest - 1, TEXT(""), pos->second);
    }
    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    zobrazCiaru(spolu + lstrlen(spolu), TEXT('-'), pocetMiest);

    /*
     * TlaË v˝skytu jednotliv˝ch pÌsmen
    */
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // ZaËiatoËn˝ pr·zdny stÂpec

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


int spoluVyskytov(int vyskytyPismen[])
{
    /*
     *  SËÌtanie vöetk˝ch v˝skytov jednotliv˝ch znakov
     */
    int sucetVyskytov = 0;
    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
        sucetVyskytov += vyskytyPismen[i];

    return sucetVyskytov;
}


void tlacVyskytuPismenPodSebou(TCHAR *spolu, int vyskytyPismen[], zostupAsociativPole *parVyskytPismeno, int pocetMiest)
{
    int sucetVyskytov = spoluVyskytov(vyskytyPismen);

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));

    multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin();
    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        /*
         *  Najprv ich vytlaËÌme abecedne
         */
        int    pocet   = vyskytyPismen[i];
        double percent = (sucetVyskytov != 0) ? pocet * 100. / sucetVyskytov : 0;

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
        percent = (sucetVyskytov != 0) ? pocet * 100. / sucetVyskytov : 0;

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


void spracovanieVstupnehoSuboru(TCHAR * spolu, int * vyskytyPismen, TCHAR ** pVertical, const char * FileToLoad)
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

    nulujPole(vyskytyPismen, POCET_VELKYCH_PISMEN);

    while (!feof(vstup))
    {
        int znak = fgetc(vstup) & 0xFF;

        if (!feof(vstup))
        {
            znak = zmenMaleNaVelke(znak);

            if (jeVelkePismeno(znak))
            {
                int index = znak - 'A';           /* PoradovÈ ËÌslo pÌsmena: A = 0, B = 1, C = 2, ... */
                vyskytyPismen[index]++;
            }
        }
    }

    fclose(vstup);
    pocetMiest = naplnAsociativnePole(&parVyskytPismeno, vyskytyPismen);

    // Filling the string from the beginning
    _stprintf (spolu, HEAD);

    tlacHlavicky(spolu, pocetMiest);
    tlacVyskytuPismen(spolu, vyskytyPismen, pocetMiest);
    tlacVyskytuPismenZoradeny(spolu, &parVyskytPismeno, pocetMiest);

    *pVertical  = spolu = spolu + lstrlen(spolu) + sizeof(TCHAR);     // Tu zaËÌna vertik·lny v˝pis; ideme za koncov˙ nulu
    *spolu      = TEXT('\0');                                         // Aby mal ÔalöÌ reùazec nulov˙ dÂûku (len istota)

    // Filling the second part of the string from the beginning, again
    _stprintf (spolu, HEAD);

    tlacVyskytuPismenPodSebou(spolu, vyskytyPismen, &parVyskytPismeno, pocetMiest);

    int sucetVyskytov = spoluVyskytov(vyskytyPismen);
    tlacSuctovehoRiadka(spolu, sucetVyskytov, pocetMiest);
}

