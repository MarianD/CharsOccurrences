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


