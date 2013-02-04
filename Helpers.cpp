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


/** \brief Naplnenie asociat�vneho po�a a zistenie po�tu miest nutn�ch pre oddelenie po�tu jednotliv�ch v�skytov
 *
 * \param  parVyskytPismeno - zostupn� asociat�vne pole, ktor� sa m� naplni�
 * \param  pole - pole cel�ch ��sel, v�skytov pr�slu�n�ch p�smen (0. prvok - A)
 * \return po�et miest potrebn�ch pre oddelenie ��sel v riadku = po�et miest najv��ieho ��sla + 1
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
    pocetMiest = floor(log10(maximum)) + 2;                            // Po�et miest najv��ieho ��sla + 1
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
    _stprintf(spolu + lstrlen(spolu), TEXT("%*s"), PRAZD_MIEST, TEXT(""));     // Predt�m vo�n� miesto pre ��sla riadkov */

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
     * Tla� hlavi�ky s p�smenami usporiadan�mi
     * d�a ich v�skytu zostupne
    */
    _stprintf(spolu + lstrlen(spolu), "%*s", PRAZD_MIEST, ""); // Vo�n� miesto - v tomto st�pci boli kedysi ��sla jednotliv�ch riadkov

    for (multimap <int, TCHAR>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); pos++)
    {
        _stprintf(spolu + lstrlen(spolu), "%*s%c", pocetMiest - 1, "", pos->second);
    }
    _stprintf(spolu + lstrlen(spolu), "\n");

    zobrazCiaru(spolu + lstrlen(spolu), '-', pocetMiest);

    /*
     * Tla� v�skytu jednotliv�ch p�smen
    */
    _stprintf(spolu + lstrlen(spolu), "%*s", PRAZD_MIEST, "");     // Vo�n� miesto - v tomto st�pci s� vy��ie ��sla riadkov

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
     *  S��tanie v�etk�ch v�skytov jednotliv�ch znakov
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
         *  Najprv ich vytla��me abecedne
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
         *  Teraz ich vytla��me pod�a v�skytov
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
                int index = znak - 'A';           /* Poradov� ��slo p�smena: A = 0, B = 1, C = 2, ... */
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

