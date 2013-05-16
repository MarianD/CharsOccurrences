// Main.cpp : Defines the entry point for the DLL application.

#include "Main.h"

BOOL APIENTRY
DllMain(HANDLE /*hModule*/, DWORD  ul_reason_for_call, LPVOID /*lpReserved*/)
{
    HMODULE FLibHandle = nullptr;

    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_PROCESS_DETACH:
			if (FLibHandle != nullptr)
				FreeLibrary(FLibHandle);
			FLibHandle = 0;
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
    }
    return TRUE;
}

