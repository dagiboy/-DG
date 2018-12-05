#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE /*Module*/,
                       DWORD  reason,
                       LPVOID /*Reserved*/
					 )
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

