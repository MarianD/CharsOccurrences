// CreateTabbedWindow.cpp :
//

#include "CreateTabbedWindow.h"
#include "Constants.h"

/** \brief  Vytvorenie okna typu Tab Control
 *
 * \param ParentWindow HWND - okno, v ktorom sa m� vytvori�
 * \param pRect RECT*  - ukazovate� na obd�nik okna Tab Control
 * \return HWND - handle vytvoren�ho okna typu Tab Control
 *
 */
HWND CreateTabbedWindow(HWND ParentWindow, RECT * pRect)
{
	HWND      hwndTabCtrl;
    HINSTANCE hinst    =  0;
    HMENU     childID  = (HMENU) 0;

    hwndTabCtrl = CreateWindowEx(0, WC_TABCONTROL, TEXT(""),
                                WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
                                pRect->left, pRect->top,
                                pRect->right  - pRect->left,
                                pRect->bottom - pRect->top,
                                ParentWindow, childID, hinst, NULL);

    // Vytvorenie nov�ch u�iek
    TCITEM tab[NumOfTabs];

    // Naplnenie u�iek hodnotami
    tab[ListViewAlphaTab].mask             = TCIF_TEXT;
    tab[ListViewAlphaTab].pszText          = (TCHAR *) TEXT ("Letters");
    tab[ListViewAlphaTab].cchTextMax       = 60;

    tab[HistogramAlphaTab].mask            = TCIF_TEXT;
    tab[HistogramAlphaTab].pszText         = (TCHAR *) TEXT ("Histogram");
    tab[HistogramAlphaTab].cchTextMax      = 20;

    tab[ListViewDigitTab].mask             = TCIF_TEXT;
    tab[ListViewDigitTab].pszText          = (TCHAR *) TEXT ("Digits");
    tab[ListViewDigitTab].cchTextMax       = 20;

    tab[HistogramDigitTab].mask            = TCIF_TEXT;
    tab[HistogramDigitTab].pszText         = (TCHAR *) TEXT ("Histogram");
    tab[HistogramDigitTab].cchTextMax      = 20;

    tab[VerticalRichEditTab].mask          = TCIF_TEXT;
    tab[VerticalRichEditTab].pszText       = (TCHAR *) TEXT ("Vertical");
    tab[VerticalRichEditTab].cchTextMax    = 20;

    tab[HorizontalRichEditATab].mask       = TCIF_TEXT;
    tab[HorizontalRichEditATab].pszText    = (TCHAR *) TEXT ("Horizontal");
    tab[HorizontalRichEditATab].cchTextMax = 20;

    tab[AboutRichEditTab].mask             = TCIF_TEXT;
    tab[AboutRichEditTab].pszText          = (TCHAR *) TEXT ("About");
    tab[AboutRichEditTab].cchTextMax       = 20;

    // Pridanie pripraven�ch u�iek
    for (int i = 0; i < NumOfTabs; ++i)
        TabCtrl_InsertItem(hwndTabCtrl, i, tab + i);

    // Z�skanie obd�nika pre zobrazovaciu �as� Tab Control
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);

    return hwndTabCtrl;
}
