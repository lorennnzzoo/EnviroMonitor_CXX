#include "../../Logger/src/Log.h"
#include "Monitor.h"


typedef std::vector<Monitor::Station> Stations;
typedef std::vector<Monitor::Analyzer> Analyzers;
typedef std::vector<Monitor::Parameter> Parameters;
Stations Monitor::Station::GetStationsFromJson(std::string& jsonPath)
{
	Stations stations;
	try {
		std::ifstream file(jsonPath);
		if (!file.is_open()) {
			throw std::ios_base::failure("Could not open file");
		}
		
		json jsonData;
		file >> jsonData;		
		for (const auto& stationJson : jsonData) {
			Station station;
			 station.Id = stationJson["Id"].get<int>();
			 station.Name = stationJson["Name"].get<std::string>();
			stations.push_back(station);
		}
		file.close();
	}
	catch (const std::exception& ex) {		
		Log::Error("Error at GetStationsFromJson", &ex);
	}
	return stations;
}
Analyzers Monitor::Analyzer::GetAnalyzersFromJson(std::string& jsonPath)
{
	Analyzers analyzers;
	try {
		
		std::ifstream file(jsonPath);
		if (!file.is_open()) {
			throw std::ios_base::failure("Could not open file");
		}

		json jsonData;
		file >> jsonData;		
		for (const auto& analyzerJson : jsonData) {
			Analyzer analyzer;
			analyzer.Id = analyzerJson["Id"].get<int>();
			analyzer.Type = analyzerJson["Type"].get<std::string>();
			analyzer.CommunicationType= analyzerJson["CommunicationType"].get<std::string>();
			analyzer.Comport = analyzerJson["Comport"].get<std::string>();
			analyzer.Parity = analyzerJson["Parity"].get<std::string>();
			analyzer.TimeoutInSeconds= analyzerJson["TimeoutInSeconds"].get<int>();
			analyzer.BaudRate = analyzerJson["BaudRate"].get<int>();
			analyzer.DataBits = analyzerJson["DataBits"].get<int>();
			analyzer.StopBits = analyzerJson["StopBits"].get<int>();
			analyzer.Port = analyzerJson["Port"].get<int>();
			analyzer.Ip= analyzerJson["Ip"].get<std::string>();
			analyzer.Command= analyzerJson["Command"].get<std::string>();
			analyzers.push_back(analyzer);
		}
		file.close();
	}
	catch (const std::exception& ex) {		
		Log::Error("Error at GetAnalyzersFromJson", &ex);
	}
	return analyzers;
}
Parameters Monitor::Parameter::GetParametersFromJson(std::string& jsonPath)
{
	Parameters parameters;
	try {
		std::ifstream file(jsonPath);
		if (!file.is_open()) {
			throw std::ios_base::failure("Could not open file");
		}

		json jsonData;
		file >> jsonData;		
		for (const auto& parameterJson : jsonData) {
			Parameter parameter;
			parameter.Id = parameterJson["Id"].get<int>();
			parameter.Name = parameterJson["Name"].get<std::string>();
			parameter.StationId= parameterJson["StationId"].get<int>();
			parameter.AnalyzerId = parameterJson["AnalyzerId"].get<int>();
			parameter.ChannelNo = parameterJson["ChannelNo"].get<int>();
			parameters.push_back(parameter);
		}
		file.close();

	}
	catch (const std::exception& ex) {		
		Log::Error("Error at GetParametersFromJson", &ex);
	}
	return parameters;
}