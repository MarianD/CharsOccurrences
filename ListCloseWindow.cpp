// ListCloseWindow.cpp :
//

#include <tchar.h>
#include "ListCloseWindow.h"
#include "Exports.h"
#include "Constants.h"
#include "Helpers.h"
#include "Classic.h"

void CHARSOCCURRENCESCALL
ListCloseWindow(HWND ListWin)
{
	HWND      hwndTabCtrl        = ListWin;
	Classic * pClassic           = 0;
	int      lastChosenTab       = 0;
	TCHAR    strLastChosenTab[3];
	TCHAR    iniFile[_MAX_PATH + lstrlen(INI_FILE) + 1];

    // Saving the last chosen tab of Tab Control to ini file
    lastChosenTab = (INT64) RemoveProp(hwndTabCtrl, LastChosenTab);
    _stprintf(strLastChosenTab, TEXT("%d"), lastChosenTab);

  	getFullIniFilePath(iniFile);
    WritePrivateProfileString(IniFileTabsSection, IniFileLastChosenTabKey, strLastChosenTab, iniFile);

    /*
     *  Removing all items in the property list of the windows
     *  and getting pointers to allocated chunks of the memory
     */

    pClassic = (Classic *) RemoveProp(hwndTabCtrl, PointerToClassic);

    RemoveProp(hwndTabCtrl,                        OldTabCtrlWndProc);
    RemoveProp(hwndTabCtrl,                        LastChosenTab);

    RemoveProp(pClassic->getHwndListViewAlpha (),  LastClickedColumn);
    RemoveProp(pClassic->getHwndListViewDigit (),  LastClickedColumn);    RemoveProp(pClassic->getHwndHistogramAlpha(),  ClientWidthAndHight);
    RemoveProp(pClassic->getHwndHistogramDigit(),  ClientWidthAndHight);
    RemoveProp(pClassic->getHwndHistogramAlpha(),  PointerToClassic);
    RemoveProp(pClassic->getHwndHistogramDigit(),  PointerToClassic);

    // Uvo¾nenie alokovanej pamäte pre exemplár triedy
    delete pClassic;

    DestroyWindow(hwndTabCtrl);         // It will destroy child windows, too

//      MessageBoxA(0, "Tak èo, zas padneš?!", "Padne?", 0);

}
