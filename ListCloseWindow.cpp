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

    //Uvo�nenie alokovanej pam�te pre re�azce
    vyskytyPismen = (void *) GetProp(hwndTabCtrl, LISTVIEW_PROP);
    vysledok      = (void *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);
    about         = (void *) GetProp(hwndTabCtrl, ABOUT_PROP);

    DestroyWindow(hwndTabCtrl);     // Zru�� aj dc�rske okn�

    if (vyskytyPismen)
        free(vyskytyPismen);

    if (vysledok)
        free(vysledok);

    if (about)
        free(about);
}
