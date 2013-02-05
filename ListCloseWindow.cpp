// ListCloseWindow.cpp :
//

#include "ListCloseWindow.h"
#include "Exports.h"

void CHARSOCCURRENCESCALL
ListCloseWindow(HWND ListWin)
{
	HWND      hwndTabCtrl  = ListWin;
	HWND      hwndRichEdit = 0;
    void     *vysledok;
    void     *info;

    //Uvo�nenie alokovanej pam�te pre re�azce
    vysledok = (void *) GetProp(hwndTabCtrl, TEXT("Usko 0"));
    info     = (void *) GetProp(hwndTabCtrl, TEXT("Usko 1"));

    free(vysledok);
    free(info);

    DestroyWindow(hwndTabCtrl);     // Zru�� aj dc�rske okno
}
