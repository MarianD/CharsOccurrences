// Classic.cpp :
//

#include <cstdarg>
#include <fstream>
#include <sys/stat.h>
#include "Classic.h"
#include "Constants.h"




Classic::Classic()
    // Some initializations are here only for the safety - to have some reasonable values
  : horizontal      ( new TCHAR[cn::MaxCharsHorizAndVert] ),
    vertical        ( horizontal ),
    text            ( nullptr ),
    about           ( new TCHAR[cn::AboutLength] ),
    vyskytyPismen   ( new int  [cn::NumOfCapLetters + cn::NumOfDigits] ),
    spolu           ( horizontal ),
    parVyskytPismeno(),
    pocetMiest      ( cn::MinPocetMiest ),
    restChars       ( cn::MaxCharsHorizAndVert - 1 ),
    warningWritten  ( false ),
    verticalIsSet   ( false )
{
//    _sntprintf(text, cn::TextLength, cn::TextText);

    _sntprintf(about, cn::AboutLength, cn::TextAbout,
        AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, AutoVersion::STATUS);

    // Initializations only for the safety
    restChars      = cn::MaxCharsHorizAndVert - 1;
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

    int    base     = (charsType == cn::CharsTypeAlpha) ? 0                       : 0 + cn::NumOfCapLetters;
    int    numChars = (charsType == cn::CharsTypeAlpha) ? cn::NumOfCapLetters : cn::NumOfDigits;
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
        lvI.lParam   = (LPARAM) (cn::NumOfCapLetters * occur + riadok); // For sorting by columns; don't use numChars!
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


/** \brief Naplnenie asociatívneho po¾a a zistenie poètu miest nutných pre oddelenie poètu jednotlivých výskytov
 *
 * \return poèet miest potrebných pre oddelenie èísel v riadku = poèet miest najväèšieho èísla + 1
 *
 */
void Classic::naplnAsociativnePole()
{
    int maximum = 1;                              // We will get logarithm of it, so it must not be 0
    for (size_t i = 0; i < cn::NumOfCapLetters; ++i)
    {
        int pocet = vyskytyPismen[i];
        parVyskytPismeno.insert(make_pair(pocet, TEXT('A') + i));
        maximum = max(maximum, pocet);
    }
    pocetMiest = floor(log10(maximum)) + 2;       // Poèet miest najväèšieho èísla + 1 = poèet miest pre _stprintf()
    pocetMiest = max(pocetMiest, cn::MinPocetMiest);
}


void Classic::zobrazCiaru(TCHAR znak)
{
    for (size_t i = 0; i < pocetMiest * cn::NumOfCapLetters; ++i)
    {
        appendString(TEXT("%c"), znak);
    }
    appendString(TEXT("\n"));
}


void Classic::tlacHlavicky()
{
    zobrazCiaru(TEXT('-'));

    for (size_t i = 0; i < cn::NumOfCapLetters; ++i)
    {
        appendString(TEXT("%*s%c"), pocetMiest - 1, "", (TCHAR) ('A' + i));
    }
    appendString(TEXT("\n"));
    zobrazCiaru(TEXT('-'));
}


void Classic::tlacVyskytuPismen()
{
    for (size_t i = 0; i < cn::NumOfCapLetters; ++i)
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
     * Tlaè hlavièky s písmenami usporiadanými
     * d¾a ich výskytu zostupne
    */
    for (auto par : parVyskytPismeno)
        appendString(TEXT("%*s%c"), pocetMiest - 1, TEXT(""), par.second);

    appendString(TEXT("\n"));
    zobrazCiaru (TEXT('-'));

    /*
     * Tlaè výskytu jednotlivých písmen
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
    int numChars = (charsType == cn::CharsTypeAlpha) ? cn::NumOfCapLetters : cn::NumOfDigits;
    int base     = (charsType == cn::CharsTypeAlpha) ? 0                       : 0 + cn::NumOfCapLetters;

    /*
     *  Sèítanie všetkých výskytov jednotlivých znakov
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
    for (size_t i = 0; i < cn::NumOfCapLetters; ++i)
    {
        /*
         *  Najprv ich vytlaèíme abecedne
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
         *  Teraz ich vytlaèíme pod¾a výskytov
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
    restChars      = cn::MaxCharsHorizAndVert - 1;
    warningWritten = false;

    // Getting the size of the file
    struct stat st;
    stat(FileToLoad, &st);
    int sizeOfFile = st.st_size;

    char *readedText = new char[(sizeOfFile + 1)];

    ifstream in;

    in.open(FileToLoad, ios::in | ios::binary);

    if(in)
        in.read(readedText, sizeOfFile);
    else
    {
        appendString(TEXT("\nOpening of the file\n\n  \"%S\"\n\nfailed ")
                     TEXT("(probably it is the folder).\n\n"), FileToLoad);
        in.close();
        return;
    }
    in.close();

    unsigned char * textAnsi = (unsigned char *) readedText;

    // Brief test of the file content
    bool IsUCS16      = false;              // TODO: Use this flag for UCS-16 files
    bool notAnsi      = false;
    const
    int  patternBytes = 20;

    if ((textAnsi[0] == 0xFF && textAnsi[1] == 0xFE) ||
        (textAnsi[0] == 0xFE && textAnsi[1] == 0xFF))
        IsUCS16 = notAnsi = true;

    if (!IsUCS16)
        for (int i = 0; i < min(patternBytes, sizeOfFile); ++i)
        {
            char znak = textAnsi[i];
            if (znak < ' ' && znak != '\n' && znak != '\r')
            {
                notAnsi = true;
                break;
            }
        }

    // Initializing the member "text"
    delete[] text;   // To avoid memory leak
    text = new TCHAR[(sizeOfFile + 1) * sizeof(TCHAR)];

    // Clearing the counting containers
    nulujPole(vyskytyPismen, cn::NumOfCapLetters + cn::NumOfDigits);
    parVyskytPismeno.clear();

    for (int i = 0; i < sizeOfFile + 1; ++i)
    {
        int znak = textAnsi[i];

        if (notAnsi && znak <  ' '  && znak != '\n' && znak != '\r')
            textAnsi[i] = ' ';                  // Non-ANSI text may contain control codes

        znak = zmenMaleNaVelke(znak);

        if (jeVelkePismeno(znak))
        {
            int index = znak - 'A';             // Ordinal number of the letter: A = 0, B = 1, C = 2, ...
            ++vyskytyPismen[index];
        }
        else if (isdigit(znak))
        {
            int index = znak - '0';
            index += cn::NumOfCapLetters;   // Occurrences of digits are just after occurences of letters
            ++vyskytyPismen[index];
        }
    }

    textAnsi[sizeOfFile] = 0;                   // End of string
//    if (!IsUCS16)
        MultiByteToWideChar(0, 0, readedText, -1, text, sizeOfFile + 1);
//    else
//        text = (TCHAR *) readedText;

    text[sizeOfFile] = 0;                       // End of string
    delete[] readedText;
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

