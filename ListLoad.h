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

    #include <map>
    #include "version.h"

    using namespace std;

    typedef multimap <int, char, greater<int> > zostupAsociativPole;


    #include <windows.h>
    #include <cstdio>
    #include <malloc.h>
    #include <richedit.h>
    #include <commdlg.h>
    #include <cmath>

#endif // ndef
