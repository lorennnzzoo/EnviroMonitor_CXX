#include "../../Protocol/src/Monitor.h"
#include "../../Configurator/src/Config.h"
#include "../../Logger//src/Log.h"
#include "../../Communicator/src/Serial.h"
#include "../../Communicator/src/TCP.h"

std::string stationsJsonPath;
std::string analyzersJsonPath;
std::string parametersJsonPath;

typedef std::vector<Monitor::Station> Stations;
typedef std::vector<Monitor::Analyzer> Analyzers;
typedef std::vector<Monitor::Parameter> Parameters;

const std::string CONFIG_PATH = "F:/C++/EnviroMonitor/EM_Runner/CONFIG/CONFIGURATION.json";
//const std::string CONFIG_PATH = "C:/EM_Runner/CONFIG/CONFIGURATION.json";

int main() {
	try {
		Config::File configFile(CONFIG_PATH);		


		stationsJsonPath = configFile.GetStringKey("StationsPath");
		analyzersJsonPath = configFile.GetStringKey("AnalyzersPath");
		parametersJsonPath = configFile.GetStringKey("ParametersPath");



		Stations stations = Monitor::Station::GetStationsFromJson(stationsJsonPath);
		Analyzers analyzers = Monitor::Analyzer::GetAnalyzersFromJson(analyzersJsonPath);
		Parameters parameters = Monitor::Parameter::GetParametersFromJson(parametersJsonPath);


		for (const auto& station : stations) {
			std::vector<Monitor::Parameter> matchedParameters;

			for (const auto& parameter_ : parameters) {
				if (parameter_.StationId == station.Id) {
					matchedParameters.push_back(parameter_);
				}
			}
			if (matchedParameters.size() > 0) {
				Log::Information("Count of matched parameters with Station Id : " + std::to_string(station.Id) + " = " + std::to_string(matchedParameters.size()));
				Log::Information("Station Name : " + station.Name);


				for (const auto& parameter : matchedParameters) {
					Log::Information("Parameter : " + parameter.Name);

					Monitor::Analyzer* matchedAnalyzer = nullptr;

					for (auto& analyzer : analyzers) {
						if (analyzer.Id == parameter.AnalyzerId) {
							matchedAnalyzer = &analyzer;
							break;
						}
					}

					if (matchedAnalyzer != nullptr) {
						Log::Information("Analyzer found for Id : " + std::to_string(parameter.AnalyzerId));
						Log::Information("Type : " + matchedAnalyzer->Type);
						Log::Information("CommunicationType : " + matchedAnalyzer->CommunicationType);
						std::string* response=nullptr;
						if (matchedAnalyzer->CommunicationType == "C") {
							Communicator::Serial serial(matchedAnalyzer->Comport, matchedAnalyzer->BaudRate, matchedAnalyzer->StopBits, matchedAnalyzer->DataBits, matchedAnalyzer->Parity);
							try {
								response = serial.SendCommandAndReceiveResponse(matchedAnalyzer->TimeoutInSeconds, matchedAnalyzer->Command);
							}
							catch (const std::exception& ex) {
								Log::Error("Error at serial communication", &ex);
							}

						}
						else if (matchedAnalyzer->CommunicationType == "IP")
						{
							Log::Information("IP : " + matchedAnalyzer->Ip + " Port : " + std::to_string( matchedAnalyzer->Port));
							Communicator::TCP tcp(matchedAnalyzer->Ip, matchedAnalyzer->TimeoutInSeconds);
							try {

								response = tcp.SendCommandAndReceiveResponse(matchedAnalyzer->TimeoutInSeconds, matchedAnalyzer->Command);
							}
							catch (const std::exception& ex) {
								Log::Error("Error at tcp communication", &ex);
							}
						}
						else {
							Log::Warning("Unknown Communication Type");
						}


						if (response != nullptr) {
							Log::Information("Response : " + *response);
						}
						else {
							Log::Warning("No response received");
						}
							
					}
					else {
						Log::Warning("Unable to find analyzer with Id : " + parameter.AnalyzerId);
					}

				}
			}
			else {
				Log::Warning("No parameters with station id : " + std::to_string(station.Id) + " found\n");
			}
		}


	}
	catch (const std::exception& ex) {
		Log::Error("Error at main", &ex);
	}
	std::cout << "\nPress ENTER to terminate";
	std::cin.get();
}