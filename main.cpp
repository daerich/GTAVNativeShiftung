#include "inc/natives.h"
#include "inc/types.h"
#include "inc/nativeCaller.h"
#include "inc/enums.h"

#include "ManTransImports.h"
#include "mainfunc.h"
#include "Animations.h"

#include <string>
#include "Logger.h"


/*
#include <ctime>
#include <chrono>
*/

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

//need of char pointer, cause old c-style api
const char animDict[] = "anim@veh@driveby@plane@luxor2@rear_ds@1h";
const char animName[] = "outro_0";
const char* aniMdict = "anim@veh@driveby@plane@luxor2@rear_ds@1h";
const char* aniMname = "outro_0";

static char* _animDict = new char[sizeof(animDict)];
static char* _animName = new char[sizeof(animName)];
 

static bool setupSuccess;

void setUp() {
	setupSuccess = setupComp();							//make compatible
#pragma warning(suppress : 4996)
	strcpy(_animDict, aniMdict);
#pragma warning(suppress : 4996)
	strcpy(_animName, aniMname);
	logme.write("Setup complete" + std::string(_animDict) + std::string(" ") +  std::string(_animName));
}

static bool isActive = false;

void mainScript() {
	
	//std::string animDict = "anim@veh@driveby@plane@luxor2@rear_ds@1h";
	//std::string animName = "outro_0";
	if (setupSuccess) {
		Player player = PLAYER::PLAYER_ID();
		Ped playerPD = PLAYER::GET_PLAYER_PED(player);
		Vehicle currentVehicle = PED::GET_VEHICLE_PED_IS_IN(playerPD, false);

		if (!ENTITY::DOES_ENTITY_EXIST(currentVehicle)) {
			return;
		}
		if (PED::IS_PED_IN_VEHICLE(playerPD, currentVehicle, false) && !isActive && MT::isNeutral() && MT::isActive) {


			STREAMING::REQUEST_ANIM_DICT(_animDict);
			//time_t endtime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) + 10000LL);

			while (!STREAMING::HAS_ANIM_DICT_LOADED(_animDict)) {
				WAIT(0);
			}


			AI::TASK_PLAY_ANIM(playerPD, _animDict, _animName, 8.0f, -8.0f, -1, (int)AnimFlags::UpperBodyOnly, 0.0f, 0, 0, 0);

			isActive = true;
		}
		else
		{
			if (MT::isActive && isActive && !MT::isNeutral()) {
				isActive = false; //reset state
			}
		}
	}
}

void freeme() {
	delete _animDict, _animName;
}

void ScriptLoop() {
	setUp();
	while (true) {
		mainScript();
		WAIT(0);
	}
}

void LaunchScript() {
	//srand(GetTickCount());
	ScriptLoop();
}