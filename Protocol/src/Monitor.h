#pragma once
#include <iostream>
#include <vector>
#include "../../ProjectIncludes/nlohmann/json.hpp"
#include <fstream>
using json = nlohmann::json;
namespace Monitor {
	class Station {
	public:
		int Id;
		std::string Name;
		static std::vector<Station> GetStationsFromJson(std::string& path);
	};

	class Analyzer {
	public:
		int Id;
		std::string Type;
		std::string CommunicationType;
		std::string Comport;
		std::string Parity;
		int TimeoutInSeconds;
		int BaudRate;
		int StopBits;
		int DataBits;

		//ip
		int Port;
		std::string Ip;

		std::string Command;
		static std::vector<Analyzer> GetAnalyzersFromJson(std::string& path);
	};

	class Parameter {
	public:
		int Id;
		std::string Name;
		int StationId;
		int AnalyzerId;
		int ChannelNo;
		static std::vector<Parameter> GetParametersFromJson(std::string& path);
	};
}