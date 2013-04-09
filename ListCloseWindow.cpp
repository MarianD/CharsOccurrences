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
	HWND   hwndListView       = 0;
	HWND   hwndListView1      = 0;
	HWND   hwndRichEdit       = 0;
	HWND   hwndHistogram      = 0;
    void  *vyskytyPismen      = 0;
    void  *vysledok           = 0;
    void  *about              = 0;
	int    lastChosenTab      = 0;
	TCHAR  strLastChosenTab[3];
	TCHAR  iniFile[_MAX_PATH + lstrlen(INI_FILE) + 1];

    // Saving the last chosen tab of Tab Control to ini file
    lastChosenTab = (INT64) GetProp(hwndTabCtrl, LAST_CHOSEN_TAB);
    _stprintf(strLastChosenTab, TEXT("%d"), lastChosenTab);

  	getFullIniFilePath(iniFile);
    WritePrivateProfileString(INI_SECTION_TAB, INI_KEY_LAST_CHOSEN_TAB, strLastChosenTab, iniFile);

    // Getting handles of the child windows
    getHandlesOfChildrensWindows(hwndTabCtrl, hwndListView, hwndListView1, hwndHistogram, hwndRichEdit);


    /*
     *  Removing all items in the property list of the windows
     *  and getting pointers to allocated chunks of the memory
     */

    vyskytyPismen = (void *) RemoveProp(hwndTabCtrl,   LISTVIEW_PROP);
    vysledok      = (void *) RemoveProp(hwndTabCtrl,   HORIZONTAL_PROP);
    vysledok      = (void *) RemoveProp(hwndTabCtrl,   ABOUT_PROP);

    RemoveProp(hwndTabCtrl,   VERTICAL_PROP);
    RemoveProp(hwndTabCtrl,   OLD_TAB_WNDPROC_PROP);
    RemoveProp(hwndTabCtrl,   LAST_CHOSEN_TAB);
    RemoveProp(hwndListView,  LAST_CLICKED_COLUMN);    RemoveProp(hwndHistogram, ARRAY_OF_OCCURENCES);
    RemoveProp(hwndHistogram, CLIENT_WIDTH_AND_HIGHT);

    // Uvoænenie alokovanej pam‰te pre reùazce
    if (vyskytyPismen)
        free(vyskytyPismen);

    if (vysledok)
        free(vysledok);

    if (about)
        free(about);

    DestroyWindow(hwndTabCtrl);      // ZruöÌ aj dcÈrske okn·

//      MessageBoxA(0, "Tak Ëo, za padneö?!", "Padne?", 0);

}
