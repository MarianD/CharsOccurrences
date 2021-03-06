// CreateRichEditWindow.cpp :

#include "CreateRichEditWindow.h"
#include "Constants.h"
#include "Status.h"

HWND CreateRichEditWindow(HWND ParentWindow, RECT * pRect, int id)
{
	HWND       hwndRichEdit;
	HWND       hwndTabCtrl = ParentWindow;
    HINSTANCE  hinst       = GetModuleHandle(nullptr);
    HMENU      childID     = (HMENU) (INT64) id;
    Status   * pStatus     = (Status *)  GetProp(hwndTabCtrl, cn::PointerToStatus );
    CHARFORMAT charFormat,
              *pcharFormat = &charFormat;

    /*
     *  Font settings
     */
    pcharFormat->cbSize    = sizeof(charFormat);
    pcharFormat->dwMask    = CFM_BOLD | CFM_FACE | CFM_SIZE;
    pcharFormat->dwEffects = pStatus->isFontBold() ? CFE_BOLD : 0;
    pcharFormat->yHeight   = pStatus->getFontSize() * cn::TwipsInInch / cn::PointsInInch;     // yHeight is in twips
    _tcscpy(pcharFormat->szFaceName, TEXT("Courier New"));

    hwndRichEdit = CreateWindowEx(0, RICHEDIT_CLASS, TEXT(""),
                                  WS_CHILD   | ES_MULTILINE | ES_READONLY  |
                                  WS_HSCROLL | WS_VSCROLL   | ES_NOHIDESEL | WS_CLIPSIBLINGS,
                                  pRect->left,    pRect->top,
                                  pRect->right  - pRect->left,
                                  pRect->bottom - pRect->top,
                                  ParentWindow, childID, hinst, nullptr);

	if (hwndRichEdit)
    {
        SendMessage(hwndRichEdit, EM_SETMARGINS,    EC_LEFTMARGIN, 8);
        SendMessage(hwndRichEdit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM) pcharFormat);
        SendMessage(hwndRichEdit, EM_SETEVENTMASK,  0, ENM_UPDATE | ENM_REQUESTRESIZE);   //ENM_SCROLL doesn't work for thumb movements!

        return hwndRichEdit;
    }
    else
    {
        return 0;
    }
}

