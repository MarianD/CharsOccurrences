// CreateListViewtWindow.cpp :

#include "CreateListViewtWindow.h"
#include "Constants.h"
#include "Helpers.h"

HWND CreateListViewWindow(HWND ParentWindow, RECT * pRect, int id)
{
    HWND      hwndListView;
    HINSTANCE hinst   = nullptr;
    HMENU     childID = (HMENU) (INT64) id;

    hwndListView = CreateWindowEx(0,                            // Lots of extended attributes are not functional here
                                  WC_LISTVIEW, TEXT(""),
                                  WS_CHILD   | LVS_REPORT | /*LVS_OWNERDRAWFIXED |*/
                                  WS_HSCROLL | WS_VSCROLL | WS_CLIPSIBLINGS,
                                  pRect->left,    pRect->top,
                                  pRect->right  - pRect->left,
                                  pRect->bottom - pRect->top,
                                  ParentWindow, childID, hinst, nullptr);
    if (hwndListView)
    {
        (void)
        ListView_SetExtendedListViewStyleEx(hwndListView,
                                            LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT,
                                            LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT);
        InitListViewImageLists(hwndListView);

        // Preparation for adding columns to the List-View control
        TCHAR     colHeader[4][10] = {TEXT(""), TEXT("???"), TEXT("Count"), TEXT("Percent")};
//        const int colWidth [4]     = {0,        50 + 20,     53 + 20,       60 + 40};

        lstrcpy(colHeader[1], (id == cn::ListViewAlphaId) ? TEXT("Letter") : TEXT("Digit"));

        /*
         *  Initialize the LVCOLUMN structure.
         *  The mask specifies that the format, width, text, and subitem members
         *  of the structure are valid.
         */
        LVCOLUMN   lvc;
        lvc.mask = LVCF_FMT     | LVCF_WIDTH | LVCF_TEXT |
                   LVCF_SUBITEM | LVCF_IMAGE;               // LVCF_IMAGE is for columns' HEADERS

        // Adding the columns
        for (int column = 0; column < 4; ++column)
        {
            lvc.iSubItem = column;
            lvc.pszText  = colHeader   [column];
            lvc.cx       = cn::colWidth[column];
            lvc.fmt      = (column == 1) ? LVCFMT_CENTER : LVCFMT_RIGHT;
//          lvc.fmt     |= LVCFMT_BITMAP_ON_RIGHT;                          // It was not good for the alignment
            lvc.iImage   = -1;  // No image
            (void)
            ListView_InsertColumn(hwndListView, column, &lvc);
        }

        /*
         *  This column existed only to enable the first column alignment,
         *  because the alignment of the leftmost column is always
         *  left-justified and cannot be changed
         */
        (void)
        ListView_DeleteColumn(hwndListView, 0);

        return hwndListView;
    }
    else
    {
        return 0;
    }
}
