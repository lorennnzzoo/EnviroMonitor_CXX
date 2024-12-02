#include "DateTime.h"

std::string DateTime::GetCurrentTime() {
    time_t now = time(0);
    tm local; 
    localtime_s(&local, &now);

    char buffer[26];
    asctime_s(buffer, sizeof(buffer), &local);

    std::string timeStr(buffer);
    timeStr.pop_back();
    return timeStr;
}

std::string DateTime::GetCurrentTime(const std::string& format) {
    time_t now = time(0);
    tm local;
    localtime_s(&local, &now);

    char buffer[128]; // Sufficiently large buffer to hold the formatted date/time
    if (strftime(buffer, sizeof(buffer), format.c_str(), &local)) {
        return std::string(buffer);
    }
    else {
        throw std::runtime_error("Error formatting date/time string.");
    }
}