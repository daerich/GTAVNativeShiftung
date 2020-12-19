#pragma once

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

//keep it simple for starters :D (thanks ikt @ gta5mods)
namespace MT {
	extern bool (*isActive)();
	extern bool (*isNeutral)();
}

bool setupComp();
void releaseComp();
