// CreateListViewtWindow.cpp :

#include "CreateListViewtWindow.h"
#include "Constants.h"

HWND CreateListViewWindow(HWND ParentWindow, RECT * pRect)
{
    HWND            hwndListView;
    HINSTANCE       hinst;
    HMENU           childID = (HMENU) LISTVIEW_ID;

    hwndListView = CreateWindowEx(0, WC_LISTVIEW, TEXT(""),
                                  WS_CHILD   | LVS_REPORT | LVS_EDITLABELS |
                                  WS_HSCROLL | WS_VSCROLL | WS_CLIPSIBLINGS,
                                  pRect->left, pRect->top,
                                  pRect->right  - pRect->left,
                                  pRect->bottom - pRect->top,
                                  ParentWindow, childID, hinst, NULL);

    if (hwndListView)
    {
        // TODO: Uloûiù manipul·tor hwndListView vo vlastnostiach rodiËovskÈho okna

        // InitListViewColumns - adds columns to a list-view control.

        TCHAR * szText[3] = {TEXT("Letter"), TEXT("Count"), TEXT("Percent")};
        LVCOLUMN lvc;
        int iCol;

        // Initialize the LVCOLUMN structure.
        // The mask specifies that the format, width, text, and subitem members
        // of the structure are valid.
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

        // Add the columns
        for (iCol = 0; iCol < 3; iCol++)
        {
            lvc.iSubItem = iCol;
            lvc.pszText  = szText[iCol];
            lvc.cx       = 60;              // Width of column in pixels

            if ( iCol < 0 )                 // To nikdy nenastane
                lvc.fmt = LVCFMT_LEFT;      // left-aligned column
            else
                lvc.fmt = LVCFMT_RIGHT;     // right-aligned column

            ListView_InsertColumn(hwndListView, iCol, &lvc);
        }


        // Initialize LVITEM members that are common to all items.
        LVITEM lvI;

        lvI.mask = LVIF_TEXT | LVIF_STATE;
        lvI.state = 0;
        lvI.stateMask = 0;

        // TODO: Cel˝ nasleduj˙ci cyklus daù ako samostatn˙ funkciu a volaù ju z ListLoad() a z ListLoadNext()
        // Initialize LVITEM members that are different for each item.
        for (int index = 0; index < POCET_VELKYCH_PISMEN; index++)
        {
            TCHAR pismeno[] = TEXT("X");
            pismeno[0]   = TEXT('A') + index;
            TCHAR chOccur  [20];
            TCHAR chPercent[20];
            _stprintf(chOccur,   TEXT("%d"),        index + 800);               // TODO: Zmeniù toto odsk˙öanie na skutoËn˙ hodnotu
            _stprintf(chPercent, TEXT("%5.2f %%"), (index + 800) / 211.25);     // TODO: Zmeniù toto odsk˙öanie na skutoËn˙ hodnotu
            lvI.iItem    = index;
            lvI.iSubItem = 0;
            lvI.pszText  = pismeno;
            ListView_InsertItem(hwndListView, &lvI);
            lvI.iSubItem = 1;
            lvI.pszText  = chOccur;
            ListView_SetItem(hwndListView, &lvI);
            lvI.iSubItem = 2;
            lvI.pszText  = chPercent;
            ListView_SetItem(hwndListView, &lvI);
        }
        return hwndListView;
    }
    else
        return 0;
}
