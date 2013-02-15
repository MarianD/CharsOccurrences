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
        return hwndListView;
    }
    else
        return 0;
}
