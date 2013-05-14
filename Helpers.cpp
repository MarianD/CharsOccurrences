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


/** \brief CallBack funkcia volan� pri po�iadavke na zoradenie ListView pod�a niektor�ho st�pca
 *
 * \param hodnota1 LPARAM - 1. porovn�van� hodnota ako kombin�cia po�tu v�skytov a por. ��sla p�smena (0-25)
 * \param hodnota2 LPARAM - 2. porovn�van� hodnota ako kombin�cia po�tu v�skytov a por. ��sla p�smena (0-25)
 * \param stlpec LPARAM   - ��slo st�pca, pod�a ktor�ho sa m� zoznam usporiada�; z�porn� ��slo st�pca znamen� po�iadavku na zmenu smeru usporiadania
 * \return int CALLBACK   - z�porn� <, nula pre =, kladn� pre >
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
    // Creating image list for all views except icon view
    HIMAGELIST hSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
                                         GetSystemMetrics(SM_CYSMICON),
                                         ILC_MASK, 1, 1);
    HICON
    hIconItem = LoadIcon ((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(IcoBlank));
    ImageList_AddIcon(hSmall, hIconItem);
    DestroyIcon(hIconItem);

    hIconItem = LoadIcon ((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(IcoUpArrow));
    ImageList_AddIcon(hSmall, hIconItem);
    DestroyIcon(hIconItem);

    hIconItem = LoadIcon ((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(IcoDownArrow));
    ImageList_AddIcon(hSmall, hIconItem);
    DestroyIcon(hIconItem);

    /*
     *  Assign the image list to the list-view control.
     *
     *  This will be the image list for all views except icon view
     *  because of parameter LVSIL_SMALL (LVSIL_NORMAL is for icon view)
     */
    (void)
    ListView_SetImageList(hWndListView, hSmall, LVSIL_SMALL);
}


void setHeadersArrows(HWND hwndListView, int lastClickedColumn)
{
    HWND   hwndHeader = ListView_GetHeader(hwndListView);
    HDITEM hdi, *phdi = &hdi;
    hdi.mask = HDI_IMAGE;      // We vill change only the iImage member (of the structure hdi)

    // First destroying all header's images
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
        phdi->iImage = (lastClickedColumn > 0) ? UpArrow : DownArrow;     // Characters' column
        Header_SetItem(hwndHeader, index, phdi);
        break;
    case 1:
        phdi->iImage = (lastClickedColumn > 0) ? DownArrow : UpArrow;     // Occurences' or percentages' column
        Header_SetItem(hwndHeader, index, phdi);
        Header_SetItem(hwndHeader, index + 1, phdi);
        break;
    default:
        break;
    }
}


