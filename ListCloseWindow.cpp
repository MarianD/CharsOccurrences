// ListCloseWindow.cpp :
//

#include "ListCloseWindow.h"
#include "Exports.h"
#include "Constants.h"

void CHARSOCCURRENCESCALL
ListCloseWindow(HWND ListWin)
{
	HWND      hwndTabCtrl  = ListWin;
	HWND      hwndRichEdit = 0;
    void     *vysledok;
    void     *info;

    //Uvo�nenie alokovanej pam�te pre re�azce
    vysledok = (void *) GetProp(hwndTabCtrl, VYSKYTY_VLASTNOST);
    info     = (void *) GetProp(hwndTabCtrl, INFO_VLASTNOST);

    free(vysledok);
    free(info);

    DestroyWindow(hwndTabCtrl);     // Zru�� aj dc�rske okno
}
