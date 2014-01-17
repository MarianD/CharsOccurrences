// Classic.cpp :
//

#include <cstdarg>
#include <fstream>
#include <sys/stat.h>
#include "Classic.h"
#include "Constants.h"




Classic::Classic()
    // Some initializations are here only for the safety - to have some reasonable values
  : horizontal      ( new TCHAR[cn::MaxCharsHorizAndlVertical] ),
    vertical        ( horizontal ),
    text            ( nullptr ),
    about           ( new TCHAR[cn::AboutLength] ),
    vyskytyPismen   ( new int  [cn::NumOfCapitalLetters + cn::NumOfDigits] ),
    spolu           ( horizontal ),
    parVyskytPismeno(),
    pocetMiest      ( cn::MinPocetMiest ),
    restChars       ( cn::MaxCharsHorizAndlVertical - 1 ),
    warningWritten  ( false ),
    verticalIsSet   ( false )
{
//    _sntprintf(text, cn::TextLength, cn::TextText);

    _sntprintf(about, cn::AboutLength, cn::TextAbout,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Initializations only for the safety
    restChars      = cn::MaxCharsHorizAndlVertical - 1;
    warningWritten = false;
    verticalIsSet  = false;
}


Classic::~Classic()
{
    delete[] vyskytyPismen;
    delete[] horizontal;
    delete[] text;
    delete[] about;
}


void Classic::naplnListView(HWND hwndListView, int charsType) const
{
    int
    sucetVyskytov   = max(spoluVyskytov(charsType), 1);         // It will be the divisor, so it must not be 0

    int    base     = (charsType == cn::CharsTypeAlpha) ? 0                       : 0 + cn::NumOfCapitalLetters;
    int    numChars = (charsType == cn::CharsTypeAlpha) ? cn::NumOfCapitalLetters : cn::NumOfDigits;
    TCHAR  baseChar = (charsType == cn::CharsTypeAlpha) ? TEXT('A')               : TEXT('0');
    LVITEM lvI;

    (void)
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
        lvI.lParam   = (LPARAM) (cn::NumOfCapitalLetters * occur + riadok); // For sorting by columns; don't use numChars!
        (void)
        ListView_InsertItem(hwndListView, &lvI);

        lvI.mask     = LVIF_TEXT;
        lvI.iSubItem = 1;
        lvI.pszText  = chOccur;
        (void)
        ListView_SetItem(hwndListView, &lvI);

        lvI.iSubItem = 2;
        lvI.pszText  = chPercent;
        (void)
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
    for (size_t i = 0; i < cn::NumOfCapitalLetters; ++i)
    {
        int pocet = vyskytyPismen[i];
        parVyskytPismeno.insert(make_pair(pocet, TEXT('A') + i));
        maximum = max(maximum, pocet);
    }
    pocetMiest = floor(log10(maximum)) + 2;       // Po�et miest najv��ieho ��sla + 1 = po�et miest pre _stprintf()
    pocetMiest = max(pocetMiest, cn::MinPocetMiest);
}


void Classic::zobrazCiaru(TCHAR znak)
{
    for (size_t i = 0; i < pocetMiest * cn::NumOfCapitalLetters; ++i)
    {
        appendString(TEXT("%c"), znak);
    }
    appendString(TEXT("\n"));
}


void Classic::tlacHlavicky()
{
    zobrazCiaru(TEXT('-'));

    for (size_t i = 0; i < cn::NumOfCapitalLetters; ++i)
    {
        appendString(TEXT("%*s%c"), pocetMiest - 1, "", (TCHAR) ('A' + i));
    }
    appendString(TEXT("\n"));
    zobrazCiaru(TEXT('-'));
}


void Classic::tlacVyskytuPismen()
{
    for (size_t i = 0; i < cn::NumOfCapitalLetters; ++i)
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
    for (auto par : parVyskytPismeno)
        appendString(TEXT("%*s%c"), pocetMiest - 1, TEXT(""), par.second);

    appendString(TEXT("\n"));
    zobrazCiaru (TEXT('-'));

    /*
     * Tla� v�skytu jednotliv�ch p�smen
    */
    for (auto par : parVyskytPismeno)
    {
        int pocet  = par.first ;

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
    int numChars = (charsType == cn::CharsTypeAlpha) ? cn::NumOfCapitalLetters : cn::NumOfDigits;
    int base     = (charsType == cn::CharsTypeAlpha) ? 0                       : 0 + cn::NumOfCapitalLetters;

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
    int sucetVyskytov = max(spoluVyskytov(charsType), 1);      // It will be the divisor, so it must not be 0

    appendString(TEXT("\n"));

    auto pos = parVyskytPismeno.begin();
    for (size_t i = 0; i < cn::NumOfCapitalLetters; ++i)
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
        appendString(TEXT("%*c: "), cn::StlpcovaMedzera + 1, pos->second);

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
    const TCHAR znak         = TEXT('-');
    int  sirkaStlpcaVyskytov = (int) (lstrlen(TEXT("A: ")) + pocetMiest);
    int  dlzkaRiadka         = 2 * (sirkaStlpcaVyskytov + lstrlen(TEXT("  (99.99 % )"))) + cn::StlpcovaMedzera;
    TCHAR * ciara            = new TCHAR[dlzkaRiadka + 1];

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
                 cn::StlpcovaMedzera + sirkaStlpcaVyskytov, sucetVyskytov);

    delete[] ciara;
}


void Classic::spracovanieVstupnehoSuboru(const char * FileToLoad)
{
    spolu          = horizontal;                    // Reset of the member variable
    *spolu         = TEXT('\0');                    // To have the zero length (for safety only)
    verticalIsSet  = false;                         // For testing whether vertical part already began
    restChars      = cn::MaxCharsHorizAndlVertical - 1;
    warningWritten = false;

    // Getting the size of the file
    struct stat st;
    stat(FileToLoad, &st);
    int sizeOfFile = st.st_size;

    char *textAnsi = new char[(sizeOfFile + 1)];

    ifstream in;

    in.open(FileToLoad, ios::in | ios::binary);

    if(in)
        in.read(textAnsi, sizeOfFile);
    else
    {
        appendString(TEXT("\nOpening of the file\n\n  \"%S\"\n\nfailed ")
                     TEXT("(probably it is the folder).\n\n"), FileToLoad);
        in.close();
        return;
    }
    in.close();

    textAnsi[sizeOfFile - 1] = 0;             // Overwrite the last readed character, probably EOF

    // Initializing the member "text"
    delete[] text;   // To avoid memory leak
    text = new TCHAR[(sizeOfFile + 1) * sizeof(TCHAR)];

    // Clearing the counting containers
    nulujPole(vyskytyPismen, cn::NumOfCapitalLetters + cn::NumOfDigits);
    parVyskytPismeno.clear();


    // Non-ANSI text may contain 0 - let skip it
    char *temp = new char[(sizeOfFile + 1)];

    int j = 0;
    for (int i = 0; i < sizeOfFile; ++i)
    {
        if (textAnsi[i] != 0)
            temp[j++] = textAnsi[i];
    }
    temp[j]  = 0;
    delete[] textAnsi;
    textAnsi = temp;
    sizeOfFile = strlen(textAnsi);

    for (int i = 0; i < sizeOfFile; ++i)
    {
        int znak  = textAnsi[i];

        if (jeVelkePismeno(znak))
        {
            int index = znak - 'A';             // Ordinal number of the letter: A = 0, B = 1, C = 2, ...
            ++vyskytyPismen[index];
        }
        else if (isdigit(znak))
        {
            int index = znak - '0';
            index += cn::NumOfCapitalLetters;   // Occurrences of digits are just after occurences of letters
            ++vyskytyPismen[index];
        }
    }
    MultiByteToWideChar(0, 0, textAnsi, sizeOfFile + 1, text, sizeOfFile + 1);
    delete[] temp;
    naplnAsociativnePole();

    // Filling the string from the beginning
    appendString(cn::TextHead);

    tlacHlavicky();
    tlacVyskytuPismen();
    tlacVyskytuPismenZoradeny();

    if(!warningWritten)             // In the opposite case vertical is already set to warning message
    {
        vertical      = spolu = spolu + lstrlen(spolu) + sizeof(TCHAR);     // Here begins vetical listing; moving after binary zero
        verticalIsSet = true;
        *spolu        = TEXT('\0');                                         // Setting of zero length, only for the safety

        // Filling the second part of the string from the beginning, again
        appendString(cn::TextHead);

        tlacVyskytuPismenPodSebou(cn::CharsTypeAlpha);

        int sucetVyskytov = spoluVyskytov(cn::CharsTypeAlpha);
        tlacSuctovehoRiadka(sucetVyskytov);
    }
}

