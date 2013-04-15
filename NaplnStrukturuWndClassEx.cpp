#include <windows.h>
#include "NaplnStrukturuWndClassEx.h"
#include "WndProcs.h"

void NaplnStrukturuWndClassEx(WNDCLASSEX * pWndClassEx, HINSTANCE hThisInstance, const TCHAR * className)
{
    /* The Window structure */
    pWndClassEx->hInstance     = hThisInstance;
    pWndClassEx->lpszClassName = className;
    pWndClassEx->lpfnWndProc   = HistogramProc;        /* This function is called by Windows */
    pWndClassEx->style         = CS_DBLCLKS;           /* Catch double-clicks */
    pWndClassEx->cbSize        = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    pWndClassEx->hIcon         = LoadIcon  (0, IDI_APPLICATION);
    pWndClassEx->hIconSm       = LoadIcon  (0, IDI_APPLICATION);
    pWndClassEx->hCursor       = LoadCursor(0, IDC_ARROW);

    pWndClassEx->lpszMenuName  = 0;     /* No menu */
    pWndClassEx->cbClsExtra    = 0;     /* No extra bytes after the window class */
    pWndClassEx->cbWndExtra    = 0;     /* Structure or the Window Instance */

    /* Use Windows's default color as the background of the window */
    pWndClassEx->hbrBackground = (HBRUSH) COLOR_BACKGROUND;
}
