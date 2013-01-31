// CreateRichEditWindow.cpp :
//

#include "CreateRichEditWindow.h"


HWND CreateRichEditWindow(HWND ParentWindow, RECT * pRect)
{
	HWND            hwnd;
    HINSTANCE       hinst;
    CHARFORMAT      charFormat, *pcharFormat = &charFormat;

    /*
     *  Nastavenie písma
     */
    pcharFormat->cbSize     = sizeof(charFormat);
    pcharFormat->dwMask     = CFM_BOLD | CFM_FACE | CFM_SIZE;
    pcharFormat->dwEffects  = CFE_BOLD;
    pcharFormat->yHeight    = 240L;
    strcpy(pcharFormat->szFaceName, "Courier New");

    hwnd = CreateWindowEx(0, RICHEDIT_CLASS, "", WS_CHILD | ES_MULTILINE | ES_READONLY |
                    WS_HSCROLL | WS_VSCROLL | ES_NOHIDESEL,
                                pRect->left, pRect->top,
                                pRect->right  - pRect->left,
                                pRect->bottom - pRect->top,
                                ParentWindow, NULL, hinst, NULL);

	if (hwnd)
    {
        SendMessage(hwnd, EM_SETMARGINS,    EC_LEFTMARGIN, 8);
        SendMessage(hwnd, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) pcharFormat);
        SendMessage(hwnd, EM_SETEVENTMASK,  0, ENM_UPDATE); //ENM_SCROLL doesn't work for thumb movements!

        PostMessage(ParentWindow, WM_COMMAND, MAKELONG(lcp_ansi, itm_fontstyle), (LPARAM) hwnd);

        return hwnd;
    }
    else
        return 0;
}

