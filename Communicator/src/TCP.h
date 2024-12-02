#pragma once
#include <iostream>
#include "../../ProjectIncludes/boost/asio.hpp"

namespace Communicator {
	class TCP {
	public:
		std::string Ip;
		int Port;


		TCP(std::string& ip, int& port) {
			Ip = ip;
			Port = port;
		}

		std::string* SendCommandAndReceiveResponse(int& timeout, const std::string& command);
	};
}