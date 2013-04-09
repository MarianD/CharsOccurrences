// CreateTabbedWindow.cpp :
//

#include "CreateTabbedWindow.h"

/** \brief  Vytvorenie okna typu Tab Control
 *
 * \param ParentWindow HWND - okno, v ktorom sa m· vytvoriù
 * \param pRect RECT*  - ukazovateæ na obdÂûnik okna Tab Control
 * \return HWND - handle vytvorenÈho okna typu Tab Control
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

    // Vytvorenie nov˝ch uöiek
    LPTCITEM tab0 = new TCITEM;
    LPTCITEM tab1 = new TCITEM;
    LPTCITEM tab2 = new TCITEM;
    LPTCITEM tab3 = new TCITEM;
    LPTCITEM tab4 = new TCITEM;
    LPTCITEM tab5 = new TCITEM;
    LPTCITEM tab6 = new TCITEM;

    // Naplnenie uöiek hodnotami
    tab0->mask       = TCIF_TEXT;
    tab0->pszText    = (TCHAR *) TEXT ("Letters");
    tab0->cchTextMax = 60;

    tab1->mask       = TCIF_TEXT;
    tab1->pszText    = (TCHAR *) TEXT ("Histogram");
    tab1->cchTextMax = 60;

    tab2->mask       = TCIF_TEXT;
    tab2->pszText    = (TCHAR *) TEXT ("Digits");
    tab2->cchTextMax = 60;

    tab3->mask       = TCIF_TEXT;
    tab3->pszText    = (TCHAR *) TEXT ("Histogram");
    tab3->cchTextMax = 60;

    tab4->mask       = TCIF_TEXT;
    tab4->pszText    = (TCHAR *) TEXT ("Vertical");
    tab4->cchTextMax = 60;

    tab5->mask       = TCIF_TEXT;
    tab5->pszText    = (TCHAR *) TEXT ("Horizontal");
    tab5->cchTextMax = 60;

    tab6->mask       = TCIF_TEXT;
    tab6->pszText    = (TCHAR *) TEXT ("About");
    tab6->cchTextMax = 60;

    // Pridanie pripraven˝ch uöiek
    TabCtrl_InsertItem(hwndTabCtrl, 0, tab0);
    TabCtrl_InsertItem(hwndTabCtrl, 1, tab1);
    TabCtrl_InsertItem(hwndTabCtrl, 2, tab2);
    TabCtrl_InsertItem(hwndTabCtrl, 3, tab3);
    TabCtrl_InsertItem(hwndTabCtrl, 4, tab4);
    TabCtrl_InsertItem(hwndTabCtrl, 5, tab5);
    TabCtrl_InsertItem(hwndTabCtrl, 6, tab6);

    // ZÌskanie obdÂûnika pre zobrazovaciu Ëasù Tab Control
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);

    return hwndTabCtrl;
}
