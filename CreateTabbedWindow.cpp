// CreateTabbedWindow.cpp :
//

#include "CreateTabbedWindow.h"
#include "Constants.h"

/** \brief  Vytvorenie okna typu Tab Control
 *
 * \param ParentWindow HWND - okno, v ktorom sa má vytvori
 * \param pRect RECT*  - ukazovate¾ na obdåžnik okna Tab Control
 * \return HWND - handle vytvoreného okna typu Tab Control
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

    // Creating new tabs
    TCITEM tab[NumOfTabs];

    // Filling these tabs with individual values
    tab[ListViewAlphaTab]      .pszText = (TCHAR *) TEXT ("Letters");
    tab[HistogramAlphaTab]     .pszText = (TCHAR *) TEXT ("Histogram");
    tab[ListViewDigitTab]      .pszText = (TCHAR *) TEXT ("Digits");
    tab[HistogramDigitTab]     .pszText = (TCHAR *) TEXT ("Histogram");
    tab[VerticalRichEditTab]   .pszText = (TCHAR *) TEXT ("Vertical");
    tab[HorizontalRichEditATab].pszText = (TCHAR *) TEXT ("Horizontal");
    tab[AboutRichEditTab]      .pszText = (TCHAR *) TEXT ("About");

    // Filling these tabs with common values and adding them to the Tab View
    for (int i = 0; i < NumOfTabs; ++i)
    {
        tab[i].mask       = TCIF_TEXT;
        tab[i].cchTextMax = 20;
        TabCtrl_InsertItem(hwndTabCtrl, i, tab + i);
    }

    // Získanie obdåžnika pre zobrazovaciu èas Tab Control
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);

    return hwndTabCtrl;
}
