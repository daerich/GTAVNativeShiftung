#include <Windows.h>
#include "inc/main.h"
#include "mainfunc.h"
#include "ManTransImports.h"

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		scriptRegister(hInstance, LaunchScript);
		break;
	case DLL_PROCESS_DETACH:
		releaseComp();
		freeme();
		scriptUnregister(hInstance);
		break;
	}
	return TRUE;
}

