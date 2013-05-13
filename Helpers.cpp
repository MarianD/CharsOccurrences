// Helpers.cpp :
//

#include "Helpers.h"
#include "Constants.h"
#include "Classic.h"
#include "Status.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;


/********************** Pomocne funkcie *************************/

void switchTab(const HWND hwndTabCtrl)
{
    Classic * pClassic = (Classic *) GetProp(hwndTabCtrl, PointerToClassic);
    Status  * pStatus  = (Status  *) GetProp(hwndTabCtrl, PointerToStatus);

    switch (TabCtrl_GetCurSel(hwndTabCtrl))
    {
    case ListViewAlphaTab:
        BringWindowToTop(pStatus->getHwndListViewAlpha());
            break;
    case HistogramAlphaTab:
        BringWindowToTop(pStatus->getHwndHistogramAlpha());
        UpdateWindow    (pStatus->getHwndHistogramAlpha());
        break;
    case ListViewDigitTab:
        BringWindowToTop(pStatus->getHwndListViewDigit());
            break;
    case HistogramDigitTab:
        BringWindowToTop(pStatus->getHwndHistogramDigit());
        UpdateWindow    (pStatus->getHwndHistogramDigit());
        break;
    case VerticalRichEditTab:
        SetWindowText   (pStatus->getHwndRichEdit(), pClassic->getVertical());
        BringWindowToTop(pStatus->getHwndRichEdit());
        break;
    case HorizontalRichEditATab:
        SetWindowText   (pStatus->getHwndRichEdit(), pClassic->getHorizontal());
        BringWindowToTop(pStatus->getHwndRichEdit());
        break;
    case AboutRichEditTab:
        SetWindowText   (pStatus->getHwndRichEdit(), pClassic->getAbout());
        BringWindowToTop(pStatus->getHwndRichEdit());
        break;
    default:
        break;
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


void InitListViewImageLists(HWND hWndListView)
{
    HICON hIconItem;     // Icon for list-view items.

//    HIMAGELIST hLarge;   // Image list for icon view.

    HIMAGELIST hSmall;   // Image list for other views.


    // Create the full-sized icon image lists.

//    hLarge = ImageList_Create(GetSystemMetrics(SM_CXICON),
//                              GetSystemMetrics(SM_CYICON),
//                              ILC_MASK, 1, 1);

    hSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
                              GetSystemMetrics(SM_CYSMICON),
                              ILC_MASK, 1, 1);

    hIconItem = LoadIcon ((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(1));
    ImageList_AddIcon(hSmall, hIconItem);
    DestroyIcon(hIconItem);

    hIconItem = LoadIcon ((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(2));
    ImageList_AddIcon(hSmall, hIconItem);
    DestroyIcon(hIconItem);

    hIconItem = LoadIcon ((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(3));
    ImageList_AddIcon(hSmall, hIconItem);
    DestroyIcon(hIconItem);

    DestroyIcon(hIconItem);

    // Assign the image lists to the list-view control.

//    ListView_SetImageList(hWndListView, hLarge, LVSIL_NORMAL);
    ListView_SetImageList(hWndListView, hSmall, LVSIL_SMALL);
}

void setHeadersArrows(HWND hwndListView, int lastClickedColumn)
{
    HWND   hwndHeader = ListView_GetHeader(hwndListView);
    HDITEM hdi, *phdi = &hdi;
    hdi.mask = HDI_IMAGE;      // We vill change only the iImage member of the structure hdi

    // First destroing all header images
    for (int index = 0; index < 3; ++index)     // Index of header's item
    {
        phdi->iImage = -1;                       // No image
        Header_SetItem(hwndHeader, index, phdi);
    }

    /*
     *  Now we set the appropriate image (up- or downarrow)
     *  for the header(s), by which is their column ordered
     */
    int index = abs(lastClickedColumn) - 1;         // lastClickedColumn si numbered from 1 and has sign (+ or -)
    switch(index)
    {
    case 0:
        phdi->iImage = (lastClickedColumn > 0) ? 1 : 2;     // Characters' column
        Header_SetItem(hwndHeader, index, phdi);
        break;
    case 1:
        phdi->iImage = (lastClickedColumn > 0) ? 2 : 1;     // Occurences' or percentages' column
        Header_SetItem(hwndHeader, index, phdi);
        Header_SetItem(hwndHeader, index + 1, phdi);
        break;
    default:
        //MessageBoxA(0, "Not possible!", "Error", MB_ICONERROR);
        break;
    }
}


