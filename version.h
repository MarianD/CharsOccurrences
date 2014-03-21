#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "21";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2014";
	static const char UBUNTU_VERSION_STYLE[] =  "14.03";
	
	//Software Status
	static const char STATUS[] =  "Release";
	static const char STATUS_SHORT[] =  "r";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 7;
	static const long BUILD  = 1;
	static const long REVISION  = 341;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 1407;
	#define RC_FILEVERSION 1,7,1,341
	#define RC_FILEVERSION_STRING "1, 7, 1, 341\0"
	static const char FULLVERSION_STRING [] = "1.7.1.341";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 15;
	

}
#endif //VERSION_H
