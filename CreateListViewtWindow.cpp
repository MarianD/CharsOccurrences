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

        const TCHAR * szText  [3] = {TEXT("Letter"), TEXT("Count"), TEXT("Percent")};
        const int     colWidth[3] = {42, 50, 60};
        LVCOLUMN      lvc;
        int           iCol;

        // Initialize the LVCOLUMN structure.
        // The mask specifies that the format, width, text, and subitem members
        // of the structure are valid.
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

        // Add the columns
        for (iCol = 0; iCol < 3; iCol++)
        {
            lvc.iSubItem = iCol;
            lvc.pszText  = (TCHAR *) szText[iCol];
            lvc.cx       = colWidth[iCol];
            lvc.fmt      = LVCFMT_RIGHT;    // The alignment of the leftmost column is always left-justified and cannot be changed

            ListView_InsertColumn(hwndListView, iCol, &lvc);
        }
        return hwndListView;
    }
    else
        return 0;
}
