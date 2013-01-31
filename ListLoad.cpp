// ListLoad.cpp :
//

#include "ListLoad.h"
#include "CreateTabbedWindow.h"
#include "Helpers.h"
#include "Exports.h"
#include "version.h"

HWND CHAROCCURRENCESCALL
ListLoad(HWND ParentWin, char* FileToLoad, int ShowFlags)
{
	HWND                hwndTabCtrl;
	HWND                hwnd;
	RECT                rect;
    HINSTANCE           hinst;
    CHARFORMAT          charFormat, *pcharFormat = &charFormat;


    /*
     *  Nastavenie pÌsma
     */

    pcharFormat->cbSize     = sizeof(charFormat);
    pcharFormat->dwMask     = CFM_BOLD | CFM_FACE | CFM_SIZE;
    pcharFormat->dwEffects  = CFE_BOLD;
    pcharFormat->yHeight    = 240L;
    strcpy(pcharFormat->szFaceName, "Courier New");


    // Vytvorenie okna typu Tab Control a naplnenie rect hodnotami jeho Diasplay Area
    hwndTabCtrl = CreateTabbedWindow(ParentWin, &rect);

    // Vytvorenie RichEdit v zobrazovacej Ëast Tab Control
    hwnd = CreateWindow("RichEdit20A", "", WS_CHILD | ES_MULTILINE | ES_READONLY |
                    WS_HSCROLL | WS_VSCROLL | ES_NOHIDESEL,
                    rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
                    hwndTabCtrl, NULL, hinst, NULL);


	if (hwnd)
    {
        SendMessage(hwnd, EM_SETMARGINS,    EC_LEFTMARGIN, 8);
        SendMessage(hwnd, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) pcharFormat);
        SendMessage(hwnd, EM_SETEVENTMASK,  0, ENM_UPDATE); //ENM_SCROLL doesn't work for thumb movements!

        PostMessage(ParentWin, WM_COMMAND, MAKELONG(lcp_ansi, itm_fontstyle), (LPARAM) hwnd);

        char vysledok[10000] = "";
        spracovanieVstupnehoSuboru(vysledok, FileToLoad);

        strcat(vysledok, "\n\n *** Volala sa funkcia ListLoad() ***");      // TODO: Len pre ladenie - vyhodiù potom

        SetWindowText(hwnd, vysledok);
        PostMessage(ParentWin, WM_COMMAND, MAKELONG(0, itm_percent), (LPARAM) hwnd);
    }

	if (hwnd)
		ShowWindow(hwnd,SW_SHOW);

	return hwnd;     // TODO: Vr·tiù manipul·tor spr·vneho okna, lebo ho pouûije ListLoadNext()
}

