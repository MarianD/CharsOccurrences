// ListCloseWindow.cpp :
//

#include <tchar.h>
#include "ListCloseWindow.h"
#include "Exports.h"
#include "Constants.h"
#include "Helpers.h"

void CHARSOCCURRENCESCALL
ListCloseWindow(HWND ListWin)
{
	HWND   hwndTabCtrl        = ListWin;
	HWND   hwndListViewAlpha  = 0;
	HWND   hwndListViewDigit  = 0;
	HWND   hwndRichEdit       = 0;
	HWND   hwndHistogramAlpha = 0;
	HWND   hwndHistogramDigit = 0;
    void  *vyskytyPismen      = 0;
    void  *vysledok           = 0;
    void  *about              = 0;
	int    lastChosenTab      = 0;
	TCHAR  strLastChosenTab[3];
	TCHAR  iniFile[_MAX_PATH + lstrlen(INI_FILE) + 1];

    // Saving the last chosen tab of Tab Control to ini file
    lastChosenTab = (INT64) GetProp(hwndTabCtrl, LastChosenTab);
    _stprintf(strLastChosenTab, TEXT("%d"), lastChosenTab);

  	getFullIniFilePath(iniFile);
    WritePrivateProfileString(IniFileTabsSection, IniFileLastChosenTabKey, strLastChosenTab, iniFile);

    // Getting handles of the child windows
    getHandlesOfChildrensWindows(hwndTabCtrl,        hwndListViewAlpha,  hwndListViewDigit,
                                 hwndHistogramAlpha, hwndHistogramDigit, hwndRichEdit);


    /*
     *  Removing all items in the property list of the windows
     *  and getting pointers to allocated chunks of the memory
     */

    vyskytyPismen = (void *) RemoveProp(hwndTabCtrl,   ArrayOfOccurrences);
    vysledok      = (void *) RemoveProp(hwndTabCtrl,   HorizontalText);
    vysledok      = (void *) RemoveProp(hwndTabCtrl,   AboutText);

    RemoveProp(hwndTabCtrl,         VerticalText);
    RemoveProp(hwndTabCtrl,         OldTabCtrlWndProc);
    RemoveProp(hwndTabCtrl,         LastChosenTab);
    RemoveProp(hwndListViewAlpha,   LastClickedColumn);
    RemoveProp(hwndListViewDigit,   LastClickedColumn);    RemoveProp(hwndHistogramAlpha,  ArrayOfOccurrences);
    RemoveProp(hwndHistogramDigit,  ArrayOfOccurrences);
    RemoveProp(hwndHistogramAlpha,  ClientWidthAndHight);
    RemoveProp(hwndHistogramDigit,  ClientWidthAndHight);

    // Uvoænenie alokovanej pam‰te pre reùazce
    if (vyskytyPismen)
        free(vyskytyPismen);

    if (vysledok)
        free(vysledok);

    if (about)
        free(about);

//    DestroyWindow(hwndTabCtrl);      // ZruöÌ aj dcÈrske okn·

//      MessageBoxA(0, "Tak Ëo, za padneö?!", "Padne?", 0);

}
