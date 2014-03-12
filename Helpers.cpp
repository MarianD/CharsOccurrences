// Helpers.cpp :
//

#include "Helpers.h"
#include "Constants.h"
#include "Classic.h"
#include "Status.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;


/********************** Helper functions *************************/

void hideAllChildren(const HWND hwndTabCtrl)
{
    Status  * pStatus  = (Status  *) GetProp(hwndTabCtrl, cn::PointerToStatus);

    ShowWindow(pStatus->getHwndRichEdit(),       SW_HIDE);
    ShowWindow(pStatus->getHwndHistogramAlpha(), SW_HIDE);
    ShowWindow(pStatus->getHwndHistogramDigit(), SW_HIDE);
    ShowWindow(pStatus->getHwndSettings(),       SW_HIDE);
}


void switchTab(const HWND hwndTabCtrl)
{
    Classic * pClassic    = (Classic *) GetProp(hwndTabCtrl, cn::PointerToClassic);
    Status  * pStatus     = (Status  *) GetProp(hwndTabCtrl, cn::PointerToStatus);
    HWND      hwndCurrent = nullptr;

    hideAllChildren(hwndTabCtrl);

    switch (TabCtrl_GetCurSel(hwndTabCtrl))
    {
    case cn::TextViewTab:
        hwndCurrent = pStatus->getHwndRichEdit();
        SetWindowText(hwndCurrent, pClassic->getText());
        break;
    case cn::ListViewAlphaTab:
        hwndCurrent = pStatus->getHwndListViewAlpha();
        break;
    case cn::HistogramAlphaTab:
        hwndCurrent = pStatus->getHwndHistogramAlpha();
        break;
    case cn::ListViewDigitTab:
        hwndCurrent = pStatus->getHwndListViewDigit();
        break;
    case cn::HistogramDigitTab:
        hwndCurrent = pStatus->getHwndHistogramDigit();
        break;
    case cn::VerticalRichEditTab:
        hwndCurrent = pStatus->getHwndRichEdit();
        SetWindowText(pStatus->getHwndRichEdit(), pClassic->getVertical());
        break;
    case cn::HorizontalRichEditTab:
        hwndCurrent = pStatus->getHwndRichEdit();
        SetWindowText(pStatus->getHwndRichEdit(), pClassic->getHorizontal());
        break;
    case cn::SettingsTab:
        hwndCurrent = pStatus->getHwndSettings();
        break;
    case cn::AboutRichEditTab:
        hwndCurrent = pStatus->getHwndRichEdit();
        SetWindowText(pStatus->getHwndRichEdit(), pClassic->getAbout());
        break;
    default:
        break;
    }

    BringWindowToTop(hwndCurrent);
    ShowWindow      (hwndCurrent, SW_SHOW);
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

    fullIniFilePath.erase(++lastBackSlash).append(cn::IniFile);

    lstrcpy(result, fullIniFilePath.c_str());
}


void paintHistogram(HWND hwndHistogram, HDC hdc, int base, TCHAR baseChar, int numChars)
{
    RECT        rect, * pRect = &rect;
    int         cxClient;
    int         cyClient;
    const
    int *       vyskytyPismen;             // Array of occurences of individual letters
    int         vyskyt;                    // Occurence of actual letter
    int         xLeft;                     // Positions of 4 verteces of rectangle
    int         xRight;
    int         xTop;
    int         xBottom;
    int         zakladna;                  //  = cxClient / (numChars + 2);
    int         desVysky;                  //  = cyClient / 12;
    int         maxVyska;                  //  = 10 * desVysky;
    int         maxVyskyt   =  1;          // It will be the divisor, so it must not be 0

    HWND        hwndTabCtrl = (HWND)      GetParent(hwndHistogram);
    Classic *   pClassic    = (Classic *) GetProp(hwndTabCtrl, cn::PointerToClassic);
    Status  *   pStatus     = (Status  *) GetProp(hwndTabCtrl, cn::PointerToStatus);

    vyskytyPismen = pClassic->getVyskytyPismen();

    for (int i = 0; i < numChars; i++)
    {
        vyskyt    = vyskytyPismen[base + i];
        maxVyskyt = max(maxVyskyt, vyskyt);
    }

    // Getting dimensions of client area of histogram window (the same as of histogram window itself)
    cxClient = pStatus->getHistgClientWidth();
    cyClient = pStatus->getHistgClientHight();

    // Recalculation of variables used for painting
    zakladna = cxClient / (numChars + 2);
    desVysky = cyClient / 12;
    maxVyska = 10 * desVysky;

    // Painting the histogram
    for (int i = 0; i < numChars; i++)
    {
        vyskyt  = vyskytyPismen[base + i];
        xLeft   = zakladna + i * zakladna;
        xRight  = xLeft + zakladna;
        xTop    = desVysky + (int) ((float) vyskyt / maxVyskyt * maxVyska);
        xBottom = desVysky;
        xTop    = cyClient - xTop;
        xBottom = cyClient - xBottom;

        Rectangle(hdc, xLeft, xTop, xRight, xBottom);
    }

    // Drawing rectangle for captions of histogram columns
    xLeft   = zakladna;
    xRight  = zakladna + numChars * zakladna;
    xTop    = 3 * desVysky / 4;
    xBottom = desVysky / 4;
    xTop    = cyClient - xTop;
    xBottom = cyClient - xBottom;

    Rectangle(hdc, xLeft, xTop, xRight, xBottom);

    // Drawing captions of histogram columns
    for (int i = 0; i < numChars; i++)
    {
        TCHAR pismeno = baseChar + i;
        pRect->left   = zakladna + i * zakladna;
        pRect->right  = pRect->left  + zakladna;
        pRect->top    = 3 * desVysky / 4;
        pRect->bottom = desVysky / 4;
        pRect->top    = cyClient - pRect->top;
        pRect->bottom = cyClient - pRect->bottom;

        DrawText(hdc, &pismeno, 1, pRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    }
}


void setFontSize(HWND hwndSettings, int size)
{

}

void selectFont(HWND hwndSettings)
{
        static LOGFONT logfont ;
        CHOOSEFONT cf ;
        cf.lStructSize = sizeof (CHOOSEFONT) ;
        cf.hwndOwner = hwndSettings ;
        cf.hDC = NULL ;
        cf.lpLogFont = &logfont ;
        cf.iPointSize = 0 ;
        cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS ;
        cf.rgbColors = 0 ;
        cf.lCustData = 0 ;
        cf.lpfnHook = NULL ;
        cf.lpTemplateName = NULL ;
        cf.hInstance = NULL ;
        cf.lpszStyle = NULL ;
        cf.nFontType = 0 ; // Returned from ChooseFont
        cf.nSizeMin = 0 ;
        cf.nSizeMax = 0 ;
        (void) //return
        ChooseFont (&cf) ;
}


/** @brief CallBack funkcia volan� pri po�iadavke na zoradenie ListView pod�a niektor�ho st�pca
 *
 * @param  hodnota1 LPARAM - 1. porovn�van� hodnota ako kombin�cia po�tu v�skytov a por. ��sla p�smena (0-25)
 * @param  hodnota2 LPARAM - 2. porovn�van� hodnota ako kombin�cia po�tu v�skytov a por. ��sla p�smena (0-25)
 * @param  stlpec   LPARAM - ��slo st�pca, pod�a ktor�ho sa m� zoznam usporiada�; z�porn� ��slo st�pca znamen� po�iadavku na zmenu smeru usporiadania
 * @return int CALLBACK - z�porn� <, nula pre =, kladn� pre >
 *
 */
int CALLBACK cmpFunction(LPARAM hodnota1, LPARAM hodnota2, LPARAM plusMinusStlpec)
{
    int stlpec  = abs(plusMinusStlpec);                 // Numbered from 1
    int signum  = (plusMinusStlpec < 0) ? -1 : 1;       // Changing the direction of order by the second click
    int result;

    if (stlpec == 1)
        result = (int) hodnota1 % cn::NumOfCapLetters - (int) hodnota2 % cn::NumOfCapLetters;
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
    hIconItem = LoadIcon ((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(cn::IcoBlank));
    ImageList_AddIcon(hSmall, hIconItem);
    DestroyIcon(hIconItem);

    hIconItem = LoadIcon ((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(cn::IcoUpArrow));
    ImageList_AddIcon(hSmall, hIconItem);
    DestroyIcon(hIconItem);

    hIconItem = LoadIcon ((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(cn::IcoDownArrow));
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
        (void)
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
        phdi->iImage = (lastClickedColumn > 0) ? cn::UpArrow   : cn::DownArrow;    // Characters' column
        (void)
        Header_SetItem(hwndHeader, index, phdi);
        break;
    case 1:
        phdi->iImage = (lastClickedColumn > 0) ? cn::DownArrow : cn::UpArrow;      // Occurences' or percentages' column
        (void)
        Header_SetItem(hwndHeader, index, phdi);
        (void)
        Header_SetItem(hwndHeader, index + 1, phdi);
        break;
    default:
        break;
    }
}


