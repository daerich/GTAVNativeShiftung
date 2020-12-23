#include "ManTransImports.h"
#include "DashHook.h"
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

namespace DashHook {
	bool DashAsLib = false;
	void (*DashHook_GetData)(VehicleDashboardData*) = nullptr;
	void (*DashHook_SetData)(VehicleDashboardData) = nullptr;
	HMODULE DashHandle = nullptr;
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
		logme.write("[MT]Me not finding module handle!");
		return false;
	}

	MT::isActive = CheckAddr<bool (*)()>(MT::ModuleHandle, "MT_IsActive");
	success &= MT::isActive != nullptr;
	MT::isNeutral = CheckAddr<bool(*)()>(MT::ModuleHandle, "MT_NeutralGear");
	success &= MT::isNeutral != nullptr;
	MT::GetShiftMode = CheckAddr<int(*)()>(MT::ModuleHandle, "MT_GetShiftMode");
	success &= MT::GetShiftMode != nullptr;
	
	return success;
}

bool setupDash() {
	bool success = true;


	DashHook::DashHandle = GetModuleHandle(L"DashHook.dll");
	if (!DashHook::DashHandle) {
		DashHook::DashHandle = LoadLibrary(L"DashHook.dll");
		if (!DashHook::DashHandle) {
			logme.write("[DH] Could not find Library!");
			return false;
		}
		logme.write("[DH] Loaded as Lib!");
		DashHook::DashAsLib = true;
	}
	if (DashHook::DashHandle) {
		DashHook::DashHook_SetData = CheckAddr<void(*)(DashHook::VehicleDashboardData)>(DashHook::DashHandle, "DashHook_SetData");
		success &= DashHook::DashHook_SetData != nullptr;
		DashHook::DashHook_GetData = CheckAddr<void(*)(DashHook::VehicleDashboardData*)>(DashHook::DashHandle, "DashHook_GetData");
		success &= DashHook::DashHook_GetData != nullptr;
	}
	if (success) {
		logme.write("[DH] Successful DashHook Setup");
		return true;
	}
	return false;
}

void releaseDash() {
	if (DashHook::DashHandle) {
		if (DashHook::DashAsLib) {
			if (FreeLibrary(DashHook::DashHandle)) {
				DashHook::DashHandle = nullptr;
				logme.write("[DH] LibraryFreed");
			}
			else {
				logme.write("[DH]Could not free Library");
			}
		}
		else {
			DashHook::DashHandle = nullptr;
			logme.write("[DH]Handle reset");
		}
	}

}

void releaseComp() {
	if (MT::ModuleHandle) {
		MT::ModuleHandle = nullptr;
		logme.write("Compatibilty released");
	}
}