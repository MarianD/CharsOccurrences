// Helpers.cpp :
//

#include "Helpers.h"
#include "Constants.h"

/********************** Pomocne funkcie *************************/

void nulujPole(int pole[], int pocetPrvkov)
{
    for(int i = 0; i < pocetPrvkov; i++)
        pole[i] = 0;
}


bool jeVelkePismeno(TCHAR znak)
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


/** \brief Naplnenie asociatívneho po¾a a zistenie poètu miest nutných pre oddelenie poètu jednotlivých výskytov
 *
 * \param  parVyskytPismeno - zostupné asociatívne pole, ktoré sa má naplni
 * \param  pole - pole celých èísel, výskytov príslušných písmen (0. prvok - A)
 * \return poèet miest potrebných pre oddelenie èísel v riadku = poèet miest najväèšieho èísla + 1
 *
 */
int naplnAsociativnePole(zostupAsociativPole *parVyskytPismeno, int pole[])
{
    int pocetMiest = 0;
    int maximum    = 0;
    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        int pocet = pole[i];
        parVyskytPismeno->insert(make_pair(pocet, TEXT('A' + i)));
        if (pocet > maximum)
            maximum = pocet;
    }
    pocetMiest = floor(log10(maximum)) + 2;                            // Poèet miest najväèšieho èísla + 1
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
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // Predtým vo¾né miesto pre èísla riadkov */

    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        _stprintf(spolu + lstrlen(spolu), TEXT("%*s%c"), pocetMiest - 1, "", (TCHAR) ('A' + i));
    }

    _stprintf(spolu + lstrlen(spolu), TEXT("\n"));
    zobrazCiaru(spolu + lstrlen(spolu), TEXT('-'), pocetMiest);
}


void tlacVyskytuPismen(TCHAR *spolu, int pole[], int pocetMiest)
{
    _stprintf(spolu + lstrlen(spolu), "%*s", PRAZD_MIEST, "");

    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        int pocet = pole[i];

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), "%*d", pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), "%*s", pocetMiest, "-");
    }

    _stprintf(spolu + lstrlen(spolu), "\n");
}


void tlacVyskytuPismenZoradeny(TCHAR *spolu, zostupAsociativPole *parVyskytPismeno, int pocetMiest)
{
    zobrazCiaru(spolu + lstrlen(spolu), '*', pocetMiest);

    /*
     * Tlaè hlavièky s písmenami usporiadanými
     * d¾a ich výskytu zostupne
    */
    _stprintf(spolu + lstrlen(spolu), "%*s", PRAZD_MIEST, ""); // Vo¾né miesto - v tomto ståpci boli kedysi èísla jednotlivých riadkov

    for (multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); pos++)
    {
        _stprintf(spolu + lstrlen(spolu), "%*s%c", pocetMiest - 1, "", pos->second);
    }
    _stprintf(spolu + lstrlen(spolu), "\n");

    zobrazCiaru(spolu + lstrlen(spolu), '-', pocetMiest);

    /*
     * Tlaè výskytu jednotlivých písmen
    */
    _stprintf(spolu + lstrlen(spolu), "%*s", PRAZD_MIEST, "");     // Vo¾né miesto - v tomto ståpci sú vyššie èísla riadkov

    for (multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); pos++)
    {
        int pocet  = pos->first ;

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), "%*d", pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), "%*s", pocetMiest, "-");
    }
    _stprintf(spolu + lstrlen(spolu), "\n");

    zobrazCiaru(spolu, '-', pocetMiest);
    _stprintf(spolu + lstrlen(spolu), "\n");
}


int spoluVyskytov(int vyskytyPismen[])
{
    /*
     *  Sèítanie všetkých výskytov jednotlivých znakov
     */
    int sucetVyskytov = 0;
    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
        sucetVyskytov += vyskytyPismen[i];

    return sucetVyskytov;
}

void tlacVyskytuPismenPodSebou(TCHAR *spolu, int vyskytyPismen[], zostupAsociativPole *parVyskytPismeno, int pocetMiest)
{
    int sucetVyskytov = spoluVyskytov(vyskytyPismen);

    _stprintf(spolu + lstrlen(spolu), "\n");

    multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin();
    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        /*
         *  Najprv ich vytlaèíme abecedne
         */
        int    pocet   = vyskytyPismen[i];
        double percent = (sucetVyskytov != 0) ? pocet * 100. / sucetVyskytov : 0;

        _stprintf(spolu + lstrlen(spolu), "%c: ", 'A' + i);

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), "%*d", pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), "%*s", pocetMiest, "-");

        _stprintf(spolu + lstrlen(spolu), "  (%5.2f %% )", percent);

        /*
         *  Teraz ich vytlaèíme pod¾a výskytov
         */
        _stprintf(spolu + lstrlen(spolu), "%*c: ", STLP_MEDZERA + 1, pos->second);

        pocet   = pos->first ;
        percent = (sucetVyskytov != 0) ? pocet * 100. / sucetVyskytov : 0;

        if (pocet != 0)
            _stprintf(spolu + lstrlen(spolu), "%*d", pocetMiest, pocet);
        else
            _stprintf(spolu + lstrlen(spolu), "%*s", pocetMiest, "-");

        _stprintf(spolu + lstrlen(spolu), "  (%5.2f %% )\n", percent);

        ++pos;
    }
}

void tlacSuctovehoRiadka(TCHAR * spolu, int sucetVyskytov, int pocetMiest)
{
    const TCHAR znak          = '-';
    TCHAR ciara[160]          = "";
    int  sirkaStlpcaVyskytov = (int) (lstrlen("A: ") + pocetMiest);
    int  dlzkaRiadka         = 2 * (sirkaStlpcaVyskytov + lstrlen("  (99.99 % )")) + STLP_MEDZERA;

    for (int i = 0; i < dlzkaRiadka; i++)
        *(ciara + i) = znak;

    *(ciara + dlzkaRiadka) = '\0';

    _stprintf(spolu + lstrlen(spolu), "%s\n", ciara);
    _stprintf(spolu + lstrlen(spolu),
            "%*d (100.00 %% )%*d (100.00 %% )\n",
            sirkaStlpcaVyskytov, sucetVyskytov,
            STLP_MEDZERA + sirkaStlpcaVyskytov, sucetVyskytov);
}


void spracovanieVstupnehoSuboru(TCHAR * spolu, const TCHAR * FileToLoad)
{
    FILE *              vstup = 0;
    int                 vyskytyPismen[POCET_VELKYCH_PISMEN];
    zostupAsociativPole parVyskytPismeno;
    int                 pocetMiest = 0;

    if ((vstup = fopen(FileToLoad, "rb")) == 0)
    {
        _stprintf (spolu + lstrlen(spolu), "Opening of the file \"%s\" failed "
                "(probably it doesn\'t exist), program exits.\n\n", FileToLoad);
        return;
    }

    // Filling the string from the beginning
    _stprintf (spolu, HEAD);

    nulujPole(vyskytyPismen, POCET_VELKYCH_PISMEN);

    while (!feof(vstup))
    {
        int znak = fgetc(vstup) & 0xFF;

        if (!feof(vstup))
        {
            znak = zmenMaleNaVelke(znak);

            if (jeVelkePismeno(znak))
            {
                int index = znak - 'A';           /* Poradové èíslo písmena: A = 0, B = 1, C = 2, ... */
                vyskytyPismen[index]++;
            }
        }
    }

    fclose(vstup);
    pocetMiest = naplnAsociativnePole(&parVyskytPismeno, vyskytyPismen);

    tlacHlavicky(spolu, pocetMiest);
    tlacVyskytuPismen(spolu, vyskytyPismen, pocetMiest);
    tlacVyskytuPismenZoradeny(spolu, &parVyskytPismeno, pocetMiest);
    tlacVyskytuPismenPodSebou(spolu, vyskytyPismen, &parVyskytPismeno, pocetMiest);

    int sucetVyskytov = spoluVyskytov(vyskytyPismen);
    tlacSuctovehoRiadka(spolu, sucetVyskytov, pocetMiest);
}

