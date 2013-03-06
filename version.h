#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "06";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.03";
	
	//Software Status
	static const char STATUS[] = "Release";
	static const char STATUS_SHORT[] = "r";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 2;
	static const long BUILD = 1;
	static const long REVISION = 303;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 303;
	#define RC_FILEVERSION 1,2,1,303
	#define RC_FILEVERSION_STRING "1, 2, 1, 303\0"
	static const char FULLVERSION_STRING[] = "1.2.1.303";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 8;
	

}
#endif //VERSION_H
