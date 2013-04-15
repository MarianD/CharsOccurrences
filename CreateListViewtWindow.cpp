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

        TCHAR     colHeader[4][10] = {TEXT(""), TEXT("???"), TEXT("Count"), TEXT("Percent")};
        const int colWidth [4]     = {0,        50,          50,            60};
        LVCOLUMN  lvc;
        int       column;

        lstrcpy(colHeader[1], (id == ListViewAlphaId) ? TEXT("Letter") : TEXT("Digit"));

        /*
         *  Initialize the LVCOLUMN structure.
         *  The mask specifies that the format, width, text, and subitem members
         *  of the structure are valid.
         */
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

        // Add the columns
        for (column = 0; column < 4; column++)
        {
            lvc.iSubItem = column;
            lvc.pszText  = colHeader[column];
            lvc.cx       = colWidth[column];
            lvc.fmt      = (column == 1) ? LVCFMT_CENTER : LVCFMT_RIGHT;

            ListView_InsertColumn(hwndListView, column, &lvc);
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
