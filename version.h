#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "29";
	static const char MONTH[] = "04";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.04";
	
	//Software Status
	static const char STATUS[] = "Release";
	static const char STATUS_SHORT[] = "r";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 4;
	static const long BUILD = 1;
	static const long REVISION = 323;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 685;
	#define RC_FILEVERSION 1,4,1,323
	#define RC_FILEVERSION_STRING "1, 4, 1, 323\0"
	static const char FULLVERSION_STRING[] = "1.4.1.323";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 11;
	

}
#endif //VERSION_H
