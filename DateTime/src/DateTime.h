#pragma once
#include <iostream>
#include <ctime>


class DateTime {
public:
	static std::string GetCurrentTime();
	static std::string GetCurrentTime(const std::string& format);
};