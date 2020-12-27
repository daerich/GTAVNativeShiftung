#pragma once
#include <string>

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

class Logger {

private:
	std::string filename;
	void DeleteExisting();

public:
	Logger(std::string, bool);

	void write(std::string);

};

extern Logger logme;