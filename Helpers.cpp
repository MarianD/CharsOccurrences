// Helpers.cpp :
//

#include "Helpers.h"

/********************** Pomocne funkcie *************************/

void nulujPole(int pole[], int pocetPrvkov)
{
    for(int i = 0; i < pocetPrvkov; i++)
        pole[i] = 0;
}


bool jeVelkePismeno(char znak)
{
    if (znak >= 'A' && znak <= 'Z')
        return true;
    else
        return false;
}


bool jeMalePismeno(char znak)
{
    if (znak >= 'a' && znak <= 'z')
        return true;
    else
        return false;
}

char zmenMaleNaVelke(char pismeno)
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
        parVyskytPismeno->insert(make_pair(pocet, 'A' + i));
        if (pocet > maximum)
            maximum = pocet;
    }
    pocetMiest = floor(log10(maximum)) + 2;                            // Po�et miest najv��ieho ��sla + 1
    return (pocetMiest > POCET_MIEST) ? pocetMiest : POCET_MIEST;
}


void zobrazCiaru(char *spolu, char znak, int pocetMiest)
{
    for (int i = 0; i < PRAZD_MIEST + pocetMiest * POCET_VELKYCH_PISMEN; i++)
    {
        sprintf(spolu + strlen(spolu), "%c", znak);
    }
    sprintf(spolu + strlen(spolu), "\n");
}


void tlacHlavicky(char *spolu, int pocetMiest)
{
    zobrazCiaru(spolu + strlen(spolu), '-', pocetMiest);
    sprintf(spolu + strlen(spolu), "%*s", PRAZD_MIEST, "");     // Predt�m vo�n� miesto pre ��sla riadkov */

    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        sprintf(spolu + strlen(spolu), "%*s%c", pocetMiest - 1, "", 'A' + i);
    }

    sprintf(spolu + strlen(spolu), "\n");
    zobrazCiaru(spolu + strlen(spolu), '-', pocetMiest);
}


void tlacVyskytuPismen(char *spolu, int pole[], int pocetMiest)
{
    sprintf(spolu + strlen(spolu), "%*s", PRAZD_MIEST, "");

    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        int pocet = pole[i];

        if (pocet != 0)
            sprintf(spolu + strlen(spolu), "%*d", pocetMiest, pocet);
        else
            sprintf(spolu + strlen(spolu), "%*s", pocetMiest, "-");
    }

    sprintf(spolu + strlen(spolu), "\n");
}


void tlacVyskytuPismenZoradeny(char *spolu, zostupAsociativPole *parVyskytPismeno, int pocetMiest)
{
    zobrazCiaru(spolu + strlen(spolu), '*', pocetMiest);

    /*
     * Tla� hlavi�ky s p�smenami usporiadan�mi
     * d�a ich v�skytu zostupne
    */
    sprintf(spolu + strlen(spolu), "%*s", PRAZD_MIEST, ""); // Vo�n� miesto - v tomto st�pci boli kedysi ��sla jednotliv�ch riadkov

    for (multimap <int, char>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); pos++)
    {
        sprintf(spolu + strlen(spolu), "%*s%c", pocetMiest - 1, "", pos->second);
    }
    sprintf(spolu + strlen(spolu), "\n");

    zobrazCiaru(spolu + strlen(spolu), '-', pocetMiest);

    /*
     * Tla� v�skytu jednotliv�ch p�smen
    */
    sprintf(spolu + strlen(spolu), "%*s", PRAZD_MIEST, "");     // Vo�n� miesto - v tomto st�pci s� vy��ie ��sla riadkov

    for (multimap <int, char>::iterator pos = parVyskytPismeno->begin(); pos != parVyskytPismeno->end(); pos++)
    {
        int pocet  = pos->first ;

        if (pocet != 0)
            sprintf(spolu + strlen(spolu), "%*d", pocetMiest, pocet);
        else
            sprintf(spolu + strlen(spolu), "%*s", pocetMiest, "-");
    }
    sprintf(spolu + strlen(spolu), "\n");

    zobrazCiaru(spolu, '-', pocetMiest);
    sprintf(spolu + strlen(spolu), "\n");
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

void tlacVyskytuPismenPodSebou(char *spolu, int vyskytyPismen[], zostupAsociativPole *parVyskytPismeno, int pocetMiest)
{
    int sucetVyskytov = spoluVyskytov(vyskytyPismen);

    sprintf(spolu + strlen(spolu), "\n");

    multimap <int, char>::iterator pos = parVyskytPismeno->begin();
    for (int i = 0; i < POCET_VELKYCH_PISMEN; i++)
    {
        /*
         *  Najprv ich vytla��me abecedne
         */
        int    pocet   = vyskytyPismen[i];
        double percent = (sucetVyskytov != 0) ? pocet * 100. / sucetVyskytov : 0;

        sprintf(spolu + strlen(spolu), "%c: ", 'A' + i);

        if (pocet != 0)
            sprintf(spolu + strlen(spolu), "%*d", pocetMiest, pocet);
        else
            sprintf(spolu + strlen(spolu), "%*s", pocetMiest, "-");

        sprintf(spolu + strlen(spolu), "  (%5.2f %% )", percent);

        /*
         *  Teraz ich vytla��me pod�a v�skytov
         */
        sprintf(spolu + strlen(spolu), "%*c: ", STLP_MEDZERA + 1, pos->second);

        pocet   = pos->first ;
        percent = (sucetVyskytov != 0) ? pocet * 100. / sucetVyskytov : 0;

        if (pocet != 0)
            sprintf(spolu + strlen(spolu), "%*d", pocetMiest, pocet);
        else
            sprintf(spolu + strlen(spolu), "%*s", pocetMiest, "-");

        sprintf(spolu + strlen(spolu), "  (%5.2f %% )\n", percent);

        ++pos;
    }
}

void tlacSuctovehoRiadka(char * spolu, int sucetVyskytov, int pocetMiest)
{
    const char znak = '-';
    char ciara[160] = "";
    int  pocet      = 2 * (strlen("A: ") + pocetMiest + strlen("  (99.99 % )")) + STLP_MEDZERA;

    for (int i = 0; i < pocet; i++)
        *(ciara + i) = znak;

    *(ciara + pocet) = '\0';

    sprintf(spolu + strlen(spolu), "%s\n", ciara);
    sprintf(spolu + strlen(spolu),
            "%*d (100.00 %% )%*d (100.00 %% )\n",
            strlen("A: ") + pocetMiest, sucetVyskytov,
            STLP_MEDZERA + strlen("A: ") + pocetMiest, sucetVyskytov);
}


void spracovanieVstupnehoSuboru(char * spolu, const char * FileToLoad)
{
    FILE *              vstup = 0;
    int                 vyskytyPismen[POCET_VELKYCH_PISMEN];
    zostupAsociativPole parVyskytPismeno;
    int                 pocetMiest = 0;

    if ((vstup = fopen(FileToLoad, "rb")) == 0)
    {
        sprintf (spolu + strlen(spolu), "Opening of the file \"%s\" failed "
                "(probably it doesn\'t exist), program exits.\n\n", FileToLoad);

        return;
    }

    sprintf(spolu, "\nOccurrences of individual ASCII letters, case insensitive, "
       "version %ld.%ld.%ld %s\n\n",
       AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

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

