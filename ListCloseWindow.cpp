// ListCloseWindow.cpp :
//

#include "ListCloseWindow.h"
#include "Exports.h"
#include "Constants.h"

void CHARSOCCURRENCESCALL
ListCloseWindow(HWND ListWin)
{
	HWND      hwndTabCtrl  = ListWin;
    void     *vysledok;
    void     *about;

    //Uvo�nenie alokovanej pam�te pre re�azce
    vysledok = (void *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);
    about    = (void *) GetProp(hwndTabCtrl, ABOUT_PROP);

    free(vysledok);
    free(about);

    DestroyWindow(hwndTabCtrl);     // Zru�� aj dc�rske okno
}
