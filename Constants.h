#ifndef CONSTANTS_H
    #define CONSTANTS_H

    #include <windows.h>

    const TCHAR * const TextAbout       = TEXT("\nCharsOccurrences (Lister plugin), version %ld.%ld.%ld %S\n\n" \
                                                "Author: Marian Denes\n\n\n" \
                                                "This plugin is freeware, created in Code::Blocks IDE.");

    const TCHAR * const TextHead        = TEXT("\nOccurrences of individual ASCII letters, " \
                                                "case insensitive:\n\n");

    const TCHAR * const HistogramClass  = TEXT("ChOcc Histogram");

    const int MaxCharsHorizAndlVertical = 6000;
    const int NumOfDigits               =   10;
    const int NumOfCapitalLetters       = ('Z' - 'A' + 1);
    const int MAX_DLZ_CIARY             = (15 * NumOfCapitalLetters);

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
        ListViewAlphaTab,
        HistogramAlphaTab,
        ListViewDigitTab,
        HistogramDigitTab,
        VerticalRichEditTab,
        HorizontalRichEditATab,
        AboutRichEditTab,
        NumOfTabs               // This must be the last item, because it is not a tab for adding into Tab View
    };

    const char  * const DETECT_STRING           = "ext=\"TXT\" | force";
    const TCHAR * const INI_FILE                = TEXT("CharsOccurrences.ini");

    // Names of window properties
    const TCHAR * const VerticalText            = TEXT("Vertical text");
    const TCHAR * const HorizontalText          = TEXT("Horizontal text");
    const TCHAR * const AboutText               = TEXT("About text");
    const TCHAR * const ArrayOfOccurrences      = TEXT("Array of occurences");
    const TCHAR * const OldTabCtrlWndProc       = TEXT("Old Tab Control Window Proc");
    const TCHAR * const LastClickedColumn       = TEXT("Last clicked column");
    const TCHAR * const ClientWidthAndHight     = TEXT("Client width and hight");
    const TCHAR * const LastChosenTab           = TEXT("Last chosen tab");
    const TCHAR * const IniFileTabsSection       = TEXT("Tabs");
    const TCHAR * const IniFileLastChosenTabKey = TEXT("LastChosenTab");

#endif // ndef
