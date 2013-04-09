// CreateListViewtWindow.cpp :

#include "CreateListViewtWindow.h"
#include "Constants.h"

HWND CreateListViewWindow(HWND ParentWindow, RECT * pRect, int id)
{
    HWND      hwndListView;
    HINSTANCE hinst   = 0;
    HMENU     childID = (HMENU) id;

    hwndListView = CreateWindowEx(0, WC_LISTVIEW, TEXT(""),
                                  WS_CHILD   | LVS_REPORT | LVS_EDITLABELS |
                                  WS_HSCROLL | WS_VSCROLL | WS_CLIPSIBLINGS,
                                  pRect->left,    pRect->top,
                                  pRect->right  - pRect->left,
                                  pRect->bottom - pRect->top,
                                  ParentWindow, childID, hinst, NULL);

    if (hwndListView)
    {
        // InitListViewColumns - adds columns to a list-view control.

        const TCHAR * szText  [4] = {TEXT(""), TEXT("Char"), TEXT("Count"), TEXT("Percent")};
        const int     colWidth[4] = {0, 40, 50, 60};
        LVCOLUMN      lvc;
        int           iCol;

        /*
         *  Initialize the LVCOLUMN structure.
         *  The mask specifies that the format, width, text, and subitem members
         *  of the structure are valid.
         */
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

        // Add the columns
        for (iCol = 0; iCol < 4; iCol++)
        {
            lvc.iSubItem = iCol;
            lvc.pszText  = (TCHAR *) szText[iCol];
            lvc.cx       = colWidth[iCol];
            lvc.fmt = (iCol == 1) ? LVCFMT_CENTER : LVCFMT_RIGHT;

            ListView_InsertColumn(hwndListView, iCol, &lvc);
        }

        /*
         *  This column existed only to enable the first column alignment,
         *  because the alignment of the leftmost column is always
         *  left-justified and cannot be changed
         */
        ListView_DeleteColumn(hwndListView, 0);
        return hwndListView;
    }
    else
    {
        return 0;
    }
}
