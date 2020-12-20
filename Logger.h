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
	Logger(std::string file, bool deleteExisting);

	void write(std::string content);

};

extern Logger logme;