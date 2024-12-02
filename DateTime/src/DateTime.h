#pragma once
#include <iostream>
#include <ctime>


class DateTime {
public:

	int Minute();
	int Hour();
	int Day();
	int Year();
	int Month();
	int Second();

	static std::string GetCurrentTime();
	static std::string GetCurrentTime(const std::string& format);	
};