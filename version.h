#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "31";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.03";
	
	//Software Status
	static const char STATUS[] = "Release";
	static const char STATUS_SHORT[] = "r";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 3;
	static const long BUILD = 0;
	static const long REVISION = 304;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 550;
	#define RC_FILEVERSION 1,3,0,304
	#define RC_FILEVERSION_STRING "1, 3, 0, 304\0"
	static const char FULLVERSION_STRING[] = "1.3.0.304";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 9;
	

}
#endif //VERSION_H
