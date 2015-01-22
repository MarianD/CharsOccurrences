#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "22";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.01";
	
	//Software Status
	static const char STATUS[] =  "Release";
	static const char STATUS_SHORT[] =  "r";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 7;
	static const long BUILD  = 2;
	static const long REVISION  = 341;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 1491;
	#define RC_FILEVERSION 1,7,2,341
	#define RC_FILEVERSION_STRING "1, 7, 2, 341\0"
	static const char FULLVERSION_STRING [] = "1.7.2.341";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 15;
	

}
#endif //VERSION_H
