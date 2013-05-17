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
    HINSTANCE hinst    =  nullptr;
    HMENU     childID  = (HMENU) 0;

    hwndTabCtrl = CreateWindowEx(0, WC_TABCONTROL, TEXT(""),
                                WS_CHILD    | WS_VISIBLE      | WS_CLIPCHILDREN |
                                TCS_BUTTONS | TCS_FLATBUTTONS | TCS_HOTTRACK,
                                pRect->left, pRect->top,
                                pRect->right  - pRect->left,
                                pRect->bottom - pRect->top,
                                ParentWindow, childID, hinst, nullptr);

    // Creating new tabs
    TCITEM tab[cn::NumOfTabs];

    // Filling these tabs with individual values
    tab[cn::ListViewAlphaTab]      .pszText = (TCHAR *) TEXT ("Letters");
    tab[cn::HistogramAlphaTab]     .pszText = (TCHAR *) TEXT ("Histogram");
    tab[cn::ListViewDigitTab]      .pszText = (TCHAR *) TEXT ("Digits");
    tab[cn::HistogramDigitTab]     .pszText = (TCHAR *) TEXT ("Histogram");
    tab[cn::VerticalRichEditTab]   .pszText = (TCHAR *) TEXT ("Vertical");
    tab[cn::HorizontalRichEditATab].pszText = (TCHAR *) TEXT ("Horizontal");
    tab[cn::AboutRichEditTab]      .pszText = (TCHAR *) TEXT ("About");

    // Filling these tabs with common values and adding them to the Tab View
    for (int i = 0; i < cn::NumOfTabs; ++i)
    {
        tab[i].mask       = TCIF_TEXT;
        tab[i].cchTextMax = 20;
        (void)
        TabCtrl_InsertItem(hwndTabCtrl, i, tab + i);
    }

    // Z�skanie obd�nika pre zobrazovaciu �as� Tab Control
    (void)
    TabCtrl_AdjustRect(hwndTabCtrl, FALSE, pRect);

    return hwndTabCtrl;
}
