#include "ManTransImports.h"
#include <Windows.h>
#include <string>
#include "Logger.h"

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

namespace MT {
	 bool (*isActive)() = nullptr;
	 bool (*isNeutral)() = nullptr;
	 int (*GetShiftMode)() = nullptr;

	HMODULE ModuleHandle = nullptr;
} 


template<typename T>
T CheckAddr(HMODULE lib, const std::string &function) {
	FARPROC func = GetProcAddress(lib, function.c_str());
		if(func == nullptr) {
			logme.write("Me not finding process!");
			return nullptr;
		}
		logme.write("Process found!");
		return reinterpret_cast<T>(func);
}

bool setupComp() {
	bool success = true;

	MT::ModuleHandle = GetModuleHandle(L"Gears.asi");

	if (!MT::ModuleHandle) {
		logme.write("Me not finding module handle!");
		return false;
	}

	MT::isActive = CheckAddr<bool (*)()>(MT::ModuleHandle, "MT_IsActive");
	success &= MT::isActive != nullptr;
	MT::isNeutral = CheckAddr<bool(*)()>(MT::ModuleHandle, "MT_NeutralGear");
	success &= MT::isNeutral != nullptr;
	MT::GetShiftMode = CheckAddr<int(*)()>(MT::ModuleHandle, "MT_GetShiftMode");
	success &= MT::GetShiftMode != nullptr;
	
	logme.write("Succ!(CompInit)");
	return success;
}

void releaseComp() {
	if (MT::ModuleHandle) {
		MT::ModuleHandle = nullptr;
		logme.write("Compatibilty released");
	}
}