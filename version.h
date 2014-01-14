#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "14";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2014";
	static const char UBUNTU_VERSION_STYLE[] =  "14.01";
	
	//Software Status
	static const char STATUS[] =  "Release";
	static const char STATUS_SHORT[] =  "r";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 6;
	static const long BUILD  = 1;
	static const long REVISION  = 334;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 1191;
	#define RC_FILEVERSION 1,6,1,334
	#define RC_FILEVERSION_STRING "1, 6, 1, 334\0"
	static const char FULLVERSION_STRING [] = "1.6.1.334";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 13;
	

}
#endif //VERSION_H
