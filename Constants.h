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

    const TCHAR * const LISTVIEW_PROP           = TEXT("0");
    const TCHAR * const HISTOGRAM_PROP          = TEXT("1");
    const TCHAR * const VERTICAL_PROP           = TEXT("2");
    const TCHAR * const HORIZONTAL_PROP         = TEXT("3");
    const TCHAR * const ABOUT_PROP              = TEXT("4");
    const TCHAR * const ARRAY_OF_OCCURENCES     = TEXT("ArrayOfOccurences");
    const TCHAR * const OLD_TAB_WNDPROC_PROP    = TEXT("OldTabCtrlProc");
    const TCHAR * const LAST_CLICKED_COLUMN     = TEXT("Last clicked column");
    const TCHAR * const CLIENT_WIDTH_AND_HIGHT  = TEXT("Client width and hight");
    const TCHAR * const LAST_CHOSEN_TAB         = TEXT("Last chosen tab");
    const char  * const DETECT_STRING           = "ext=\"TXT\" | force";
    const TCHAR * const INI_FILE                = TEXT("CharsOccurrences.ini");
    const TCHAR * const INI_SECTION_TAB         = TEXT("Tabs");
    const TCHAR * const INI_KEY_LAST_CHOSEN_TAB = TEXT("LastChosenTab");

#endif // ndef
