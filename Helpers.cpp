// Helpers.cpp :
//

#include "Helpers.h"
#include "Constants.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;


/********************** Pomocne funkcie *************************/

void switchTab(HWND    hwndTabCtrl,        HWND    hwndListViewAlpha,   HWND    hwndListViewDigit,
               HWND    hwndHistogramAlpha, HWND    hwndHistogramDigit,  HWND    hwndRichEdit,
               TCHAR * horizontal,         TCHAR * vertical,            TCHAR * about)
{
    switch (TabCtrl_GetCurSel(hwndTabCtrl))
    {
    case ListViewAlphaTab:
        BringWindowToTop(hwndListViewAlpha);
            break;
    case HistogramAlphaTab:
        BringWindowToTop(hwndHistogramAlpha);
        UpdateWindow    (hwndHistogramAlpha);
        break;
    case ListViewDigitTab:
        BringWindowToTop(hwndListViewDigit);
            break;
    case HistogramDigitTab:
        BringWindowToTop(hwndHistogramDigit);
        UpdateWindow    (hwndHistogramDigit);
        break;
    case VerticalRichEditTab:
        SetWindowText   (hwndRichEdit, vertical);
        BringWindowToTop(hwndRichEdit);
        break;
    case HorizontalRichEditATab:
        SetWindowText   (hwndRichEdit, horizontal);
        BringWindowToTop(hwndRichEdit);
        break;
    case AboutRichEditTab:
        SetWindowText   (hwndRichEdit, about);
        BringWindowToTop(hwndRichEdit);
        break;
    default:
        break;
    }
}


void getHandlesOfChildrensWindows(HWND hwndTabCtrl,         HWND &hwndListViewAlpha,  HWND &hwndListViewDigit,
                                  HWND &hwndHistogramAlpha, HWND &hwndHistogramDigit, HWND &hwndRichEdit)
{
    HWND hwndChildWin =  0;
    long childID      = -1;

    // ZÌskanie manipul·torov dcÈrskych okien
    hwndChildWin = GetWindow(hwndTabCtrl, GW_CHILD);            // Topmost child Window

    while (hwndChildWin)
    {
        switch(childID = GetWindowLong(hwndChildWin, GWL_ID))
        {
        case ListViewAlphaId:
            hwndListViewAlpha  = hwndChildWin;
            break;
        case ListViewDigitId:
            hwndListViewDigit  = hwndChildWin;
            break;
        case HistogramAlphaId:
            hwndHistogramAlpha = hwndChildWin;
            break;
        case HistogramDigitId:
            hwndHistogramDigit = hwndChildWin;
            break;
        case RichEditId:
            hwndRichEdit       = hwndChildWin;
            break;
        default:
            break;
        }
        hwndChildWin = GetWindow(hwndChildWin, GW_HWNDNEXT);
    }
}


void getFullIniFilePath(TCHAR * result)
{
    // Near the top is the declaration  EXTERN_C IMAGE_DOS_HEADER __ImageBase;

    TCHAR   strDLLPath[_MAX_PATH];
    tstring fullIniFilePath;
    int     lastBackSlash;

    /*
     *  At first we get the full path to this DLL, then we erase all
     *  characters after the last backslash and append the name of our
     *  ini file.
     *
     *  The declaration of __ImageBase is near the top (as global)
     */
    GetModuleFileName((HINSTANCE)&__ImageBase, strDLLPath, _MAX_PATH);

    fullIniFilePath = strDLLPath;
    lastBackSlash   = fullIniFilePath.rfind(TEXT('\\'));

    fullIniFilePath.erase(++lastBackSlash).append(INI_FILE);

    lstrcpy(result, fullIniFilePath.c_str());
}


/** \brief CallBack funkcia volan· pri poûiadavke na zoradenie ListView podæa niektorÈho stÂpca
 *
 * \param hodnota1 LPARAM - 1. porovn·van· hodnota ako kombin·cia poËtu v˝skytov a por. ËÌsla pÌsmena (0-25)
 * \param hodnota2 LPARAM - 2. porovn·van· hodnota ako kombin·cia poËtu v˝skytov a por. ËÌsla pÌsmena (0-25)
 * \param stlpec LPARAM   - ËÌslo stÂpca, podæa ktorÈho sa m· zoznam usporiadaù; z·pornÈ ËÌslo stÂpca znamen· poûiadavku na zmenu smeru usporiadania
 * \return int CALLBACK   - z·porn· <, nula pre =, kladn· pre >
 *
 */
int CALLBACK cmpFunction(LPARAM hodnota1, LPARAM hodnota2, LPARAM plusMinusStlpec)
{
    int stlpec  = abs(plusMinusStlpec);                 // Numbered from 1
    int signum  = (plusMinusStlpec < 0) ? -1 : 1;       // Changing the direction of order by the second click
    int result;

    if (stlpec == 1)
        result = (int) hodnota1 % NumOfCapitalLetters - (int) hodnota2 % NumOfCapitalLetters;
    else
        result = (int) hodnota2 - (int) hodnota1;
    return signum * result;
}
