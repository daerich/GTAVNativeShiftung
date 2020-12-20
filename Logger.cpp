#include "Logger.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */



Logger::Logger(std::string file, bool deleteExisting = false) {
	filename = file;
	if (deleteExisting) {
		DeleteExisting();
	}
}

void Logger::DeleteExisting() {
	std::ofstream tobd = std::ofstream(filename);
	if (tobd.good()) {
		DeleteFileA(filename.c_str());
	}
	tobd.close();
}

void Logger::write(std::string content) {
	std::ofstream writefile;
	
	writefile.open(filename, std::ios_base::app);
	
	writefile << content << std::endl;
	writefile.close();
}

Logger logme("NativeShifting.log", true);