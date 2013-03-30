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
	HWND   hwndRichEdit  = 0;
	HWND   hwndHistogram = 0;
	HWND   hwndChildWin  = 0;
	int    childID       = 0;
    void  *vyskytyPismen = 0;
    void  *vysledok      = 0;
    void  *about         = 0;

    // Uvo�nenie alokovanej pam�te pre re�azce
    vyskytyPismen = (void *) GetProp(hwndTabCtrl, LISTVIEW_PROP);
    vysledok      = (void *) GetProp(hwndTabCtrl, HORIZONTAL_PROP);
    about         = (void *) GetProp(hwndTabCtrl, ABOUT_PROP);

    // Z�skanie manipul�torov dc�rskych okien
    hwndChildWin = GetWindow(hwndTabCtrl, GW_CHILD);            // Topmost child Window

    while (hwndChildWin)
    {
        switch(childID = GetWindowLong(hwndChildWin, GWL_ID))
        {
        case LISTVIEW_ID:
            hwndListView  = hwndChildWin;
            break;
        case HISTOGRAM_ID:
            hwndHistogram = hwndChildWin;
            break;
        case RICHEDIT_ID:
            hwndRichEdit  = hwndChildWin;
            break;
        default:
            break;
        }
        hwndChildWin = GetWindow(hwndChildWin, GW_HWNDNEXT);
    }


    // Nutn� odstr�ni� v�etky polo�ky v zozname vlastnost� pred de�trukciou okna
    RemoveProp(hwndTabCtrl,   LISTVIEW_PROP);
    RemoveProp(hwndTabCtrl,   HORIZONTAL_PROP);
    RemoveProp(hwndTabCtrl,   VERTICAL_PROP);
    RemoveProp(hwndTabCtrl,   ABOUT_PROP);
    RemoveProp(hwndTabCtrl,   OLD_TAB_WNDPROC_PROP);
    RemoveProp(hwndListView,  LAST_CLICKED_COLUMN);    RemoveProp(hwndHistogram, ARRAY_OF_OCCURENCES);

    DestroyWindow(hwndTabCtrl);      // Zru�� aj dc�rske okn�

    if (vyskytyPismen)
        free(vyskytyPismen);

    if (vysledok)
        free(vysledok);

    if (about)
        free(about);
}
