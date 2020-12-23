#include "lib/SimpleIni.h"
#include "mainfunc.h"
#include "iniValues.h"

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

CSimpleIniA shiftingini;
SI_Error rc = shiftingini.LoadFile("NativeShifting/shiftingAnimations.ini");

const char* const _inianimDict = shiftingini.GetValue("Main", "AnimationDictionary", "anim@veh@driveby@plane@luxor2@rear_ds@1h");

const char* const _inianimName = shiftingini.GetValue("Main", "AnimationName", "outro_0");

bool inivalues::iniDashEnabled = shiftingini.GetBoolValue("DashHook", "isEnabled", false);

const std::string inivalues::inianimDict = std::string(_inianimDict);
const std::string inivalues::inianimName = std::string(_inianimName);

char* mainfunc::_animDict = new char[std::size(inivalues::inianimDict) + 1];
char* mainfunc::_animName = new char[std::size(inivalues::inianimName) + 1];




