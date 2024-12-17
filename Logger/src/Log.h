#pragma once
#include <iostream>
#include <fstream>
#include "../../FileSystem/src/File.h"
class Log {
public:
	enum Level {
		WarningLevel,
		InformationLevel,
		ErrorLevel
	};


	static void WriteToConsole(Level, const std::string&,const std::exception*);
	static void WriteToLogFile(Level, const std::string&,const std::exception*);

	static void Warning(const std::string& message);
	static void Information(const std::string& message);
	static void Error(const std::string& message,const std::exception*);


	static std::string LevelToString(Level&);
};