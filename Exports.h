/* Contents of file CharsOccurrences.h */

#ifndef CHAROCCURRENCES_H
    #define CHAROCCURRENCES_H

    #include <windows.h>

    #ifdef _WIN32
        /* You should define FOURCC_EXPORTS *only* when building the DLL */
        #ifdef CHAROCCURRENCES_EXPORTS
            #define CHAROCCURRENCESAPI __declspec(dllexport)
        #else
            #define CHAROCCURRENCESAPI __declspec(dllimport)
        #endif
        /* Define calling convention in one place, for convenience */
        #define CHAROCCURRENCESCALL __cdecl
    #else /* _WIN32 not defined */
        /* Define with no value on non-Windows OSes. */
        #define CHAROCCURRENCESAPI
        #define CHAROCCURRENCESCALL
    #endif

    #ifdef __cplusplus
        extern "C"
        {
    #endif

    /* Declare import/export functions using the above definitions here: */

    CHAROCCURRENCESAPI HWND CHAROCCURRENCESAPI ListLoad    (HWND ParentWin,               char* FileToLoad, int ShowFlags);
    CHAROCCURRENCESAPI  int CHAROCCURRENCESAPI ListLoadNext(HWND ParentWin, HWND ListWin, char* FileToLoad, int ShowFlags);
    CHAROCCURRENCESAPI  int ListNotificationReceived       (HWND ListWin,   int  Message, WPARAM wParam,    LPARAM lParam);
    #ifdef __cplusplus
        }
    #endif

#endif // ndef
