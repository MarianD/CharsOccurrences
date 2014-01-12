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
ListCloseWindow(HWND hwndTabCtrl)
{
	TCHAR   strLastChosenTab [3];
	TCHAR   strlastClColAlpha[3];
	TCHAR   strlastClColDigit[3];
	TCHAR * iniFile = new TCHAR[_MAX_PATH + lstrlen(cn::IniFile) + 1];

    /*
     *  Removing all items in the property list of the windows
     *  and getting pointers to the instances of the classes
     */
    Classic * pClassic = (Classic *) RemoveProp(hwndTabCtrl, cn::PointerToClassic);
    Status  * pStatus  = (Status  *) RemoveProp(hwndTabCtrl, cn::PointerToStatus );

    // Restoring the original Tab Control Window Procedure
    SetWindowLongPtr(hwndTabCtrl, GWLP_WNDPROC, (LONG_PTR) pStatus->getOldTabCtrlWndProc());

    delete pClassic;
    delete pStatus;

    DestroyWindow(hwndTabCtrl);                         // It in turn destroys the child windows, too

   // Saving status to ini file
    _stprintf(strLastChosenTab,  TEXT("%d"), pStatus->getLastChosenTab());
    _stprintf(strlastClColAlpha, TEXT("%d"), pStatus->getLastClickedColumnAlpha());
    _stprintf(strlastClColDigit, TEXT("%d"), pStatus->getLastClickedColumnDigit());

  	getFullIniFilePath(iniFile);
    WritePrivateProfileString(cn::IniFileTabsSection, cn::IniFileLastChosenTabKey,  strLastChosenTab,  iniFile);
    WritePrivateProfileString(cn::IniFileSortSection, cn::IniFileLastClColAlphaKey, strlastClColAlpha, iniFile);
    WritePrivateProfileString(cn::IniFileSortSection, cn::IniFileLastClColDigitKey, strlastClColDigit, iniFile);

    delete[] iniFile;
}
