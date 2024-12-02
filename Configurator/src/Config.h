#pragma once

#include <fstream>
#include <iostream>
#include "../../ProjectIncludes/nlohmann/json.hpp"
namespace Config {
	class File {
	private:
		void LoadConfig();
	public:
		std::string ConfigFilePath;
		nlohmann::json ConfigData;
		File(const std::string& filePath) {
			ConfigFilePath = filePath;
			LoadConfig();
		}
		

		int GetIntKey(const std::string&);
		std::string GetStringKey(const std::string&);
	};
}

