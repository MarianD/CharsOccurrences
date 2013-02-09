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

    //Uvoænenie alokovanej pam‰te pre reùazce
    vysledok = (void *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);
    about    = (void *) GetProp(hwndTabCtrl, ABOUT_PROP);

    free(vysledok);
    free(about);

    DestroyWindow(hwndTabCtrl);     // ZruöÌ aj dcÈrske okno
}
