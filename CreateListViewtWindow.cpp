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
//        SendMessage(hwndListView, EM_SETMARGINS,    EC_LEFTMARGIN, 8);
//        SendMessage(hwndListView, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) pcharFormat);
//        SendMessage(hwndListView, EM_SETEVENTMASK,  0, ENM_UPDATE | ENM_REQUESTRESIZE);   //ENM_SCROLL doesn't work for thumb movements!

        return hwndListView;
    }
    else
        return 0;
}

