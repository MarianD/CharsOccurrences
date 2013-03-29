#include <windows.h>
#include "NaplnStrukturuWndClassEx.h"
#include "WndProcs.h"

void NaplnStrukturuWndClassEx(WNDCLASSEX * pWndClassEx, HINSTANCE hThisInstance, TCHAR * szClassName)
{
    /* The Window structure */
    pWndClassEx->hInstance     = hThisInstance;
    pWndClassEx->lpszClassName = szClassName;
    pWndClassEx->lpfnWndProc   = HistogramProc;        /* This function is called by Windows */
    pWndClassEx->style         = CS_DBLCLKS;           /* Catch double-clicks */
    pWndClassEx->cbSize        = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    pWndClassEx->hIcon         = LoadIcon  (NULL, IDI_APPLICATION);
    pWndClassEx->hIconSm       = LoadIcon  (NULL, IDI_APPLICATION);
    pWndClassEx->hCursor       = LoadCursor(NULL, IDC_ARROW);

    pWndClassEx->lpszMenuName  = NULL;                   /* No menu */
    pWndClassEx->cbClsExtra    = 0;                      /* No extra bytes after the window class */
    pWndClassEx->cbWndExtra    = 0;                      /* Structure or the Window Instance */

    /* Use Windows's default color as the background of the window */
    pWndClassEx->hbrBackground = (HBRUSH) COLOR_BACKGROUND;
}
