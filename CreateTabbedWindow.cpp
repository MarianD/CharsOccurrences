// CreateTabbedWindow.cpp :
//

#include "CreateTabbedWindow.h"

/** \brief  Vytvorenie okna typu Tab Control
 *
 * \param ParentWindow HWND - okno, v ktorom sa má vytvori
 * \param pRect RECT*  - ukazovate¾ na obdånik okna Tab Control
 * \return HWND - handle vytvoreného okna typu Tab Control
 *
 */
HWND CreateTabbedWindow(HWND ParentWindow, RECT * pRect)
{
	HWND      hwndTabCtrl;
    HINSTANCE hinst   =  0;
    HMENU     childID = (HMENU) 0;

    hwndTabCtrl = CreateWindowEx(0, WC_TABCONTROL, TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
                                pRect->left, pRect->top,
                                pRect->right  - pRect->left,
                                pRect->bottom - pRect->top,
                                ParentWindow, childID, hinst, NULL);

    // Vytvorenie novıch ušiek
    LPTCITEM tab0 = new TCITEM;
    LPTCITEM tab1 = new TCITEM;
    LPTCITEM tab2 = new TCITEM;
    LPTCITEM tab3 = new TCITEM;
    LPTCITEM tab4 = new TCITEM;

    // Naplnenie ušiek hodnotami
    tab0->mask       = TCIF_TEXT;
    tab0->pszText    = (TCHAR *) TEXT ("Flexible");
    tab0->cchTextMax = 60;

    tab1->mask       = TCIF_TEXT;
    tab1->pszText    = (TCHAR *) TEXT ("Histogram");
    tab1->cchTextMax = 60;

    tab2->mask       = TCIF_TEXT;
    tab2->pszText    = (TCHAR *) TEXT ("Vertical");
    tab2->cchTextMax = 60;

    tab3->mask       = TCIF_TEXT;
    tab3->pszText    = (TCHAR *) TEXT ("Horizontal");
    tab3->cchTextMax = 60;

    tab4->mask       = TCIF_TEXT;
    tab4->pszText    = (TCHAR *) TEXT ("About");
    tab4->cchTextMax = 60;

    // Pridanie pripravenıch ušiek
    TabCtrl_InsertItem(hwndTabCtrl, 0, tab0);
    TabCtrl_InsertItem(hwndTabCtrl, 1, tab1);
    TabCtrl_InsertItem(hwndTabCtrl, 2, tab2);
    TabCtrl_InsertItem(hwndTabCtrl, 3, tab3);
    TabCtrl_InsertItem(hwndTabCtrl, 4, tab4);

    // Získanie obdånika pre zobrazovaciu èas Tab Control
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);

    return hwndTabCtrl;
}
