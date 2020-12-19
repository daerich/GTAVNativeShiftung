#pragma once
#include <string>

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

class Logger {

private:
	std::string filename;

public:
	Logger(std::string file);

	void write(std::string content);

};

extern Logger logme;