// ListGetDetectString.cpp :
//

#include "Exports.h"
#include "Constants.h"

void CHARSOCCURRENCESCALL
ListGetDetectString(char* DetectString, int maxlen)
{
	strncpy(DetectString, DETECT_STRING, maxlen);

	// Only for too long DETECT_STRING (maxlen is >= 2048)
	if (strlen(DETECT_STRING) >= (unsigned) maxlen)
	    DetectString[maxlen] = '\0';
}
