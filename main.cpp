#include "inc/natives.h"

#include "ManTransImports.h"
#include "DashHook.h"
#include "mainfunc.h"
#include "Animations.h"

#include <string>
#include "Logger.h"
#include "iniValues.h"

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

static bool setupSuccess;
static bool DashSetupSucces;

void setUp() {
	DashSetupSucces = setupDash();
	setupSuccess = setupComp();		//make compatible
#pragma warning(suppress : 4996)
	strcpy(mainfunc::_animDict, inivalues::inianimDict.c_str());
#pragma warning(suppress : 4996)
	strcpy(mainfunc::_animName, inivalues::inianimName.c_str());
	logme.write("Setup complete" + std::string(mainfunc::_animDict) + std::string(" ") +  std::string(mainfunc::_animName));
}

static bool isActive = false;

void mainScript() {

	if (setupSuccess) {;
		Player player(PLAYER::PLAYER_ID());
		Ped playerPD(PLAYER::GET_PLAYER_PED(player));
		Vehicle currentVehicle(PED::GET_VEHICLE_PED_IS_IN(playerPD, false));

		if (!ENTITY::DOES_ENTITY_EXIST(currentVehicle)) {
			return;
		}


		if (PED::IS_PED_IN_VEHICLE(playerPD, currentVehicle, false) && !isActive  && MT::isActive && MT::isNeutral()) {


			STREAMING::REQUEST_ANIM_DICT(mainfunc::_animDict);

			while (!STREAMING::HAS_ANIM_DICT_LOADED(mainfunc::_animDict)) {
				WAIT(0);
			}


			AI::TASK_PLAY_ANIM(playerPD,mainfunc::_animDict, mainfunc::_animName, 8.0f, -8.0f, -1, static_cast<int>(AnimFlags::UpperBodyOnly), 0.0f, 0, 0, 0);

			isActive = true;
		}
		else
		{
			if (PED::IS_PED_IN_VEHICLE(playerPD, currentVehicle, false) && MT::isActive && isActive && !MT::isNeutral()) {
				isActive = false; //reset state
			}
		}
	}
}

void DashLogic(){
	if (DashSetupSucces && inivalues::iniDashEnabled) {
		Player player(PLAYER::PLAYER_ID());
		Ped playerPD(PLAYER::GET_PLAYER_PED(player));
		Vehicle currentVehicle(PED::GET_VEHICLE_PED_IS_IN(playerPD, false));

		if (!ENTITY::DOES_ENTITY_EXIST(currentVehicle)) {
			return;
		}
		if (VEHICLE::GET_VEHICLE_ENGINE_HEALTH(currentVehicle) <= 950.0f) {
			DashHook::VehicleDashboardData data;
			DashHook::DashHook_GetData(&data);
			data.engineLight = true;
			data.oilLight = true;
			DashHook::DashHook_SetData(data);
		}
	}

}

void mainfunc::freeme() {
	delete _animDict;
	delete _animName;
	logme.write("Memory freed");
}

void ScriptLoop() {
	setUp();
	while (true) {
		mainScript();
		DashLogic();
		WAIT(0);
	}
}

void mainfunc::LaunchScript() {
	//srand(GetTickCount());
	ScriptLoop();
}