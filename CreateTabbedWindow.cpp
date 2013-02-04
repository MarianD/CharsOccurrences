// CreateTabbedWindow.cpp :
//

#include "CreateTabbedWindow.h"

/** \brief  Vytvorenie okna typu Tab Control
 *
 * \param ParentWindow HWND - okno, v ktorom sa m� vytvori�
 * \param pRect RECT*   - ukazovate� na obd�nik okna Tab Control
 * \return HWND - handle vytvoren�ho okna typu Tab Control
 *
 */
HWND CreateTabbedWindow(HWND ParentWindow, RECT * pRect)
{
	HWND            hwndTabCtrl;
    HINSTANCE       hinst;
    HMENU           childID = (HMENU) 0;

    hwndTabCtrl = CreateWindowEx(0, WC_TABCONTROL, TEXT(""), WS_CHILD | WS_VISIBLE,
                                pRect->left, pRect->top,
                                pRect->right  - pRect->left,
                                pRect->bottom - pRect->top,
                                ParentWindow, childID, hinst, NULL);

    // Vytvorenie nov�ch u�iek
    LPTCITEM usko0 = new TCITEM;
    LPTCITEM usko1 = new TCITEM;

    // Naplnenie u�iek hodnotami
    usko0->mask       = TCIF_TEXT;
    usko0->pszText    = TEXT ("Occurrences");
    usko0->cchTextMax = 60;

    usko1->mask       = TCIF_TEXT;
    usko1->pszText    = TEXT ("About");
    usko1->cchTextMax = 60;

    // Pridanie pripraven�ch u�iek
    TabCtrl_InsertItem(hwndTabCtrl, 0, usko0);
    TabCtrl_InsertItem(hwndTabCtrl, 1, usko1);

    // Z�skanie obd�nika pre zobrazovaciu �as� Tab Control
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);

    return hwndTabCtrl;
}
