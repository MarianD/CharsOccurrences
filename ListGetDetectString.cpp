// ListGetDetectString.cpp :
//

#include <windows.h>
#include "Exports.h"
#include "Constants.h"

void CHARSOCCURRENCESCALL
ListGetDetectString(char * detectString, int maxlen)
{
	strncpy(detectString, cn::DetectString, maxlen);

	// Only for too long DETECT_STRING (maxlen is >= 2048)
	if (strlen(cn::DetectString) >= (unsigned) maxlen)
	    detectString[maxlen] = '\0';
}
