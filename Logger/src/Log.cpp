#include "Log.h"
#include "../../DateTime/src/DateTime.h"
const std::string LOG_FILE_NAME = "LOG_"+DateTime:: GetCurrentTime("%Y%m%d")+".txt";



std::string Log::LevelToString(Level& level) {
	switch (level) {
	case Level::InformationLevel: return "INFO";
	case Level::WarningLevel: return "WARN";
	case Level::ErrorLevel: return "ERROR";		
	default: return "UNKNOWN";
	}
}

void Log::WriteToConsole(Level level, const std::string& message, const std::exception* exception = nullptr) {
	std::string messageTemplate;
	if (exception == nullptr) {
		messageTemplate = DateTime::GetCurrentTime("%Y-%m-%d %H:%M:%S") + " : " + LevelToString(level) + " : " + message + "\n";
	}
	else {
		messageTemplate = DateTime::GetCurrentTime("%Y-%m-%d %H:%M:%S") + " : "+ LevelToString(level) + " : " + message + " Error : " + exception->what() + "\n";
	}

	std::cout << messageTemplate;
	
}

	
void Log::WriteToLogFile(Level level, const std::string& message,const std::exception* exception=nullptr){

	std::string messageTemplate;
	if (exception == nullptr) {
		messageTemplate = DateTime::GetCurrentTime("%Y-%m-%d %H:%M:%S") + " : "+ LevelToString(level) + " : " + message+"\n";
	}
	else {
		messageTemplate = DateTime::GetCurrentTime("%Y-%m-%d %H:%M:%S") + " : "+ LevelToString(level) + " : " + message+" Error : "+exception->what()+"\n";
	}
	std::ofstream file(LOG_FILE_NAME, std::ios::app);
	if (file.is_open()) {
		if (file.good()) {
			file << messageTemplate;
		}
		else {
			throw std::ios_base::failure("Error writing to log file");
		}
	}
	else {
		throw std::ios_base::failure("Could not open log file");
	}
}

void Log::Information(const std::string& message) {
	Log::WriteToLogFile(Log::Level::InformationLevel, message);
	Log::WriteToConsole(Log::Level::InformationLevel, message);
}


void Log::Warning(const std::string& message) {
	Log::WriteToLogFile(Log::Level::WarningLevel, message);
	Log::WriteToConsole(Log::Level::WarningLevel, message);
}

void Log::Error(const std::string& message,const std::exception* exception) {
	Log::WriteToLogFile(Log::Level::ErrorLevel, message, exception);
	Log::WriteToConsole(Log::Level::ErrorLevel, message, exception);
}


