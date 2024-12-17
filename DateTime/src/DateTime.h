#pragma once
#include <iostream>
#include <ctime>


class DateTime {
public:

	static int Minute();
	static int Hour();
	static int Day();
	static int Year();
	static int Month();
	static int Second();

	static std::string GetCurrentTime();
	static std::string GetCurrentTime(const std::string& format);	
};