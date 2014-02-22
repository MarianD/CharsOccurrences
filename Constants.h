#ifndef CONSTANTS_H
    #define CONSTANTS_H

    #include <windows.h>

    namespace cn
    {
        //**************************  Constants  **************************/

        const TCHAR * const thisDLL =
        #ifdef FOR_32_BIT
            TEXT("CharsOccurrences.wlx");
        #else
            TEXT("CharsOccurrences.wlx64");
        #endif

        const
        size_t     MaxCharsHorizAndVert = 4000;
        const int  MinPocetMiest        =    5;
        const int  StlpcovaMedzera      =   14;
        const long defaultFontSize      =   12;     // In points; 1 point = 1/72 of inch
        const long TwipsInInch          = 1440;
        const long PointsInInch         =   72;

        const
        TCHAR * const TextAbout         = TEXT("\n"
                                               "CharsOccurrences (Lister plugin for TC),\n"
                                               "version %ld.%ld.%ld\n\n"
                                               "Author: Marian Denes\n\n\n"
                                               "This plugin is freeware and open source,\n"
                                               "created in Code::Blocks IDE.");

        const size_t  AboutLength       = lstrlen(TextAbout) + 10;
        const
        TCHAR * const TextHead          = TEXT("\n"
                                               "Occurrences of individual ASCII letters, "
                                               "case insensitive:\n\n");

        const size_t  NumOfDigits       =  10;
        const size_t  NumOfCapLetters   = ('Z' - 'A' + 1);

        enum
        {
            CharsTypeAlpha,
            CharsTypeDigit,
        };

        enum
        {
            RichEditId,
            ListViewAlphaId,
            ListViewDigitId,
            HistogramAlphaId,
            HistogramDigitId,
        };

        enum              // The order here is important, because it will be the order of the tabs in the Tab View
        {
            TextViewTab,
            ListViewAlphaTab,
            HistogramAlphaTab,
            ListViewDigitTab,
            HistogramDigitTab,
            VerticalRichEditTab,
            HorizontalRichEditTab,
            SettingsTab,
            AboutRichEditTab,
            NumOfTabs              // This must be the last item, because it is not a tab for adding into Tab View
        };

        enum
        {
            IcoBlank = 1,
            IcoUpArrow,
            IcoDownArrow,
        };

        enum
        {
            Blank,
            UpArrow,
            DownArrow,
        };

        const char  * const DetectString             = "ext=\"TXT\" | force";
        const TCHAR * const IniFile                  = TEXT("CharsOccurrences.ini");

        // Names of window properties
        const TCHAR * const PointerToClassic         = TEXT("Pointer to Classic instance");
        const TCHAR * const PointerToStatus          = TEXT("Pointer to Status  instance");

        // Names for INI file sections and keys
        const TCHAR * const IniFileTabsSection       = TEXT("Tabs");
        const TCHAR * const IniFileLastChosenTabKey  = TEXT("LastChosenTab");
        const TCHAR * const IniFileSortSection       = TEXT("Sort");
        const TCHAR * const IniFileLastClColAlphaKey = TEXT("LettersTab");
        const TCHAR * const IniFileLastClColDigitKey = TEXT("DigitsTab");
        const TCHAR * const IniFileFontSection       = TEXT("Font");
        const TCHAR * const IniFileFontSize          = TEXT("FontSize");
    }

#endif // ndef
