/* Contents of file ListLoad.h */

#ifndef LISTLOAD_H
    #define LISTLOAD_H

    #define lcp_wraptext	1
    #define lcp_fittowindow 2
    #define lcp_ansi		4
    #define lcp_ascii		8
    #define lcp_variable	12
    #define lcp_forceshow	16

    #define itm_fontstyle	0xFFFD
    #define itm_wrap		0xFFFC
    #define itm_fit		    0xFFFB
    #define itm_next	    0xFFFA

    #include <windows.h>
    #include <commctrl.h>
    #include "version.h"

    #include <richedit.h>

#endif // ndef
