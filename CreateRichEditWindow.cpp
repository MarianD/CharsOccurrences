// CreateRichEditWindow.cpp :
//

#include "CreateRichEditWindow.h"


HWND CreateRichEditWindow(HWND ParentWindow, RECT * pRect)
{
	HWND            hwndRichEdit;
    HINSTANCE       hinst;
    HMENU           childID = (HMENU) 0;
    CHARFORMAT      charFormat, *pcharFormat = &charFormat;

    /*
     *  Nastavenie p�sma
     */
    pcharFormat->cbSize     = sizeof(charFormat);
    pcharFormat->dwMask     = CFM_BOLD | CFM_FACE | CFM_SIZE;
    pcharFormat->dwEffects  = CFE_BOLD;
    pcharFormat->yHeight    = 240L;
    strcpy(pcharFormat->szFaceName, "Courier New");

    hwndRichEdit = CreateWindowEx(0, RICHEDIT_CLASS, "",
                                  WS_CHILD   | ES_MULTILINE | ES_READONLY  |
                                  WS_HSCROLL | WS_VSCROLL   | ES_NOHIDESEL | WS_VISIBLE,
                                    pRect->left, pRect->top,
                                    pRect->right  - pRect->left,
                                    pRect->bottom - pRect->top,
                                    ParentWindow, childID, hinst, NULL);

	if (hwndRichEdit)
    {
        SendMessage(hwndRichEdit, EM_SETMARGINS,    EC_LEFTMARGIN, 8);
        SendMessage(hwndRichEdit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) pcharFormat);
        SendMessage(hwndRichEdit, EM_SETEVENTMASK,  0, ENM_UPDATE | ENM_REQUESTRESIZE);   //ENM_SCROLL doesn't work for thumb movements!

        return hwndRichEdit;
    }
    else
        return 0;
}

