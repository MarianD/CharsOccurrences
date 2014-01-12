// Status.cpp :
//

#include <cstdarg>
#include "Status.h"
#include "Constants.h"


Status::Status()
    // Initializations are here only for the safety - to have some reasonable values
  : hwndListViewAlpha(0),
    hwndListViewDigit(0),
    hwndHistogramAlpha(0),
    hwndHistogramDigit(0),
    hwndRichEdit(0),
    oldTabCtrlWndProc(0),
    histgClientWidthHight(0),
    lastChosenTab(0),
    lastClickedColumnAlpha (1),
    lastClickedColumnDigit (1)
{
}


Status::~Status()
{
}


void
Status::moveAllChildWindows(PRECT pRect)
{
    LONG left   = pRect->left;
    LONG top    = pRect->top;
    LONG width  = pRect->right  - left;
    LONG height = pRect->bottom - top;

    MoveWindow(hwndListViewAlpha,  left, top, width, height, TRUE);
    MoveWindow(hwndListViewDigit,  left, top, width, height, TRUE);
    MoveWindow(hwndHistogramAlpha, left, top, width, height, TRUE);
    MoveWindow(hwndHistogramDigit, left, top, width, height, TRUE);
    MoveWindow(hwndRichEdit,       left, top, width, height, TRUE);
}
