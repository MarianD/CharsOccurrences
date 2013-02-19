// ListCloseWindow.cpp :
//

#include "ListCloseWindow.h"
#include "Exports.h"
#include "Constants.h"

void CHARSOCCURRENCESCALL
ListCloseWindow(HWND ListWin)
{
	HWND   hwndTabCtrl   = ListWin;
	HWND   hwndListView  = 0;
    void  *vyskytyPismen = 0;
    void  *vysledok      = 0;
    void  *about         = 0;

    // Uvo�nenie alokovanej pam�te pre re�azce
    vyskytyPismen = (void *) GetProp(hwndTabCtrl, LISTVIEW_PROP);
    vysledok      = (void *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);
    about         = (void *) GetProp(hwndTabCtrl, ABOUT_PROP);

    // Z�skanie manipul�tora dc�rskeho okna                   // TODO: Urobi� to lep�ie, z�skan�m predt�m ulo�en�ch manipul�torov vo vlastnostiach rodi�ovsk�ho okna
    hwndListView = GetWindow(hwndTabCtrl, GW_CHILD);          // Topmost child Window

    if ((GetWindowLong(hwndListView, GWL_ID)) != LISTVIEW_ID)
        hwndListView = GetWindow(hwndListView, GW_HWNDNEXT);  // Sibling window bellow the "false" hwndListView window

    // Nutn� odstr�ni� v�etky polo�ky v zozname vlastnost� pred de�trukciou okna
    RemoveProp(hwndTabCtrl,  LISTVIEW_PROP);
    RemoveProp(hwndTabCtrl,  HORIZONTAL_PROP);
    RemoveProp(hwndTabCtrl,  VERTICAL_PROP);
    RemoveProp(hwndTabCtrl,  ABOUT_PROP);
    RemoveProp(hwndTabCtrl,  OLD_TAB_WNDPROC_PROP);
    RemoveProp(hwndListView, LAST_CLICKED_COLUMN);

    DestroyWindow(hwndTabCtrl);      // Zru�� aj dc�rske okn�

    if (vyskytyPismen)
        free(vyskytyPismen);

    if (vysledok)
        free(vysledok);

    if (about)
        free(about);
}
