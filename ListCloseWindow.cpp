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

    //Uvoænenie alokovanej pam‰te pre reùazce
    vysledok = (void *) GetProp(hwndTabCtrl, TEXT("Usko 0"));
    info     = (void *) GetProp(hwndTabCtrl, TEXT("Usko 1"));

    free(vysledok);
    free(info);

    // ZÌskanie manipul·tora dcÈrskeho okna
    hwndRichEdit = GetWindow(hwndTabCtrl, GW_CHILD);

	if (hwndRichEdit)
    {
        DestroyWindow(hwndRichEdit);
    }
    DestroyWindow(hwndTabCtrl);
}
