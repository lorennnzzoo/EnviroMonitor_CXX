#pragma once
#include <iostream>
//#include "../../ProjectIncludes/boost/asio.hpp"25
#include <Windows.h>

namespace Communicator {
	class Serial {
	public:
		std::string Comport;
		int BaudRate;
		int StopBits;
		int DataBits;
		std::string Parity;

		Serial(std::string& comport,int& baudrate,int& stopbits,int& databits,std::string& parity) {
			Comport = comport;
			BaudRate = baudrate;
			StopBits = stopbits;
			DataBits = databits;
			Parity = parity;
		}

		std::string* SendCommandAndReceiveResponse(int& timeout,const std::string& command);		
	};
}