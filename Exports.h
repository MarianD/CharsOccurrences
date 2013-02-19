/* Contents of file CharsOccurrences.h */

#ifndef CHARSOCCURRENCES_H
    #define CHARSOCCURRENCES_H

    #include <windows.h>

    #ifdef _WIN32
        /* You should define CHARSOCCURRENCES_EXPORTS *only* when building the DLL */
        #ifdef CHARSOCCURRENCES_EXPORTS
            #define CHARSOCCURRENCESAPI __declspec(dllexport)
        #else
            #define CHARSOCCURRENCESAPI __declspec(dllimport)
        #endif
        /* Define calling convention in one place, for convenience */
        #define CHARSOCCURRENCESCALL __cdecl
    #else /* _WIN32 not defined */
        /* Define with no value on non-Windows OSes. */
        #define CHARSOCCURRENCESAPI
        #define CHARSOCCURRENCESCALL
    #endif

    #ifdef __cplusplus
        extern "C"
        {
    #endif

    /* Declare import/export functions using the above definitions here: */

    CHARSOCCURRENCESAPI HWND  CHARSOCCURRENCESAPI ListLoad                 (HWND ParentWin,               char* FileToLoad, int ShowFlags);
    CHARSOCCURRENCESAPI int   CHARSOCCURRENCESAPI ListLoadNext             (HWND ParentWin, HWND ListWin, char* FileToLoad, int ShowFlags);
    CHARSOCCURRENCESAPI int   CHARSOCCURRENCESAPI ListNotificationReceived (HWND ListWin,   int  Message, WPARAM wParam,    LPARAM lParam);
//    CHARSOCCURRENCESAPI void  CHARSOCCURRENCESAPI ListCloseWindow          (HWND ListWin);
    CHARSOCCURRENCESAPI void  CHARSOCCURRENCESAPI ListGetDetectString      (char* DetectString, int maxlen);

    #ifdef __cplusplus
        }
    #endif

#endif // ndef
