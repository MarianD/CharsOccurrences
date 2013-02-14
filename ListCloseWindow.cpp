// ListCloseWindow.cpp :
//

#include "ListCloseWindow.h"
#include "Exports.h"
#include "Constants.h"

void CHARSOCCURRENCESCALL
ListCloseWindow(HWND ListWin)
{
	HWND   hwndTabCtrl   = ListWin;
    void  *vyskytyPismen = 0;
    void  *vysledok      = 0;
    void  *about         = 0;

    //Uvoænenie alokovanej pam‰te pre reùazce
    vyskytyPismen = (void *) GetProp(hwndTabCtrl, LISTVIEW_PROP);
    vysledok      = (void *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);
    about         = (void *) GetProp(hwndTabCtrl, ABOUT_PROP);

    DestroyWindow(hwndTabCtrl);     // ZruöÌ aj dcÈrske okn·

    if (vyskytyPismen)
        free(vyskytyPismen);

    if (vysledok)
        free(vysledok);

    if (about)
        free(about);
}
