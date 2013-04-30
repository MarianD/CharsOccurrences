// ListCloseWindow.cpp :
//

#include <tchar.h>
#include "ListCloseWindow.h"
#include "Exports.h"
#include "Constants.h"
#include "Helpers.h"
#include "Classic.h"
#include "Status.h"

void CHARSOCCURRENCESCALL
ListCloseWindow(HWND ListWin)
{
	HWND     hwndTabCtrl        = ListWin;
	TCHAR    strLastChosenTab [3];
	TCHAR    strlastClColAlpha[3];
	TCHAR    strlastClColDigit[3];
	TCHAR    iniFile[_MAX_PATH + lstrlen(INI_FILE) + 1];

    /*
     *  Removing all items in the property list of the windows
     *  and getting pointers to the instances of the classes
     */
    Classic * pClassic = (Classic *) RemoveProp(hwndTabCtrl, PointerToClassic);
    Status  * pStatus  = (Status  *) RemoveProp(hwndTabCtrl, PointerToStatus );

    DestroyWindow(hwndTabCtrl);         // It in turn destroys the child windows, too

    // Saving status to ini file
    _stprintf(strLastChosenTab,  TEXT("%d"), pStatus->getLastChosenTab());
    _stprintf(strlastClColAlpha, TEXT("%d"), pStatus->getLastClickedColumnAlpha());
    _stprintf(strlastClColDigit, TEXT("%d"), pStatus->getLastClickedColumnDigit());

  	getFullIniFilePath(iniFile);
    WritePrivateProfileString(IniFileTabsSection, IniFileLastChosenTabKey,  strLastChosenTab,  iniFile);
    WritePrivateProfileString(IniFileSortSection, IniFileLastClColAlphaKey, strlastClColAlpha, iniFile);
    WritePrivateProfileString(IniFileSortSection, IniFileLastClColDigitKey, strlastClColDigit, iniFile);



    // Uvo¾nenie alokovanej pamäte pre exempláre triedy
    delete pClassic;
    delete pStatus;


//      MessageBoxA(0, "Tak èo, zas padneš?!", "Padne?", 0);

}
