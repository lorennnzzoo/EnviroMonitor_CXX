#include "Config.h"
using json = nlohmann::json;
void Config::File::LoadConfig() {
	if (File::ConfigFilePath.empty()) {
		throw std::invalid_argument("Empty File path passed");
	}
	json jsonData;
	std::fstream file(File::ConfigFilePath);
	if (!file.is_open()) {
		throw std::ios_base::failure("Could not open file");
	}
	file >> jsonData;	
	file.close();
	File::ConfigData = jsonData;	
}

int Config::File::GetIntKey(const std::string& Key) {
	if (Key.empty()) {
		throw std::invalid_argument("NULL key passed");
	}
	return File::ConfigData[Key].get<int>();
}


std::string Config::File::GetStringKey(const std::string& Key) {
	if (Key.empty()) {
		throw std::invalid_argument("NULL key passed");
	}
	return File::ConfigData[Key].get<std::string>();
}