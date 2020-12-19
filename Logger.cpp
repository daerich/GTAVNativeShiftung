#include "Logger.h"
#include <iostream>
#include <fstream>

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */



Logger::Logger(std::string file) {
	filename = file;
}

void Logger::write(std::string content) {
	std::ofstream writefile;
	
	
	writefile.open(filename, std::ios_base::app);
	
	writefile << content << std::endl;
	writefile.close();
}

Logger logme("1A_daerich.log");