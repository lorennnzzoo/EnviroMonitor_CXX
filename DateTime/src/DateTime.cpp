#include "DateTime.h"
#include "../../String/StringLib.h"
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


int DateTime::Year() {
    std::string currentTime= DateTime::GetCurrentTime("%Y-%m-%d-%H-%M-%S");

    std::vector<std::string> result = StringLib::Split(currentTime, '-');
    return stoi(result[0]);
}

int DateTime::Month() {
    std::string currentTime = DateTime::GetCurrentTime("%Y-%m-%d-%H-%M-%S");

    std::vector<std::string> result = StringLib::Split(currentTime, '-');
    return stoi(result[1]);
}

int DateTime::Day() {
    std::string currentTime = DateTime::GetCurrentTime("%Y-%m-%d-%H-%M-%S");

    std::vector<std::string> result = StringLib::Split(currentTime, '-');
    return stoi(result[2]);
}

int DateTime::Hour() {
    std::string currentTime = DateTime::GetCurrentTime("%Y-%m-%d-%H-%M-%S");

    std::vector<std::string> result = StringLib::Split(currentTime, '-');
    return stoi(result[3]);
}
int DateTime::Minute() {
    std::string currentTime = DateTime::GetCurrentTime("%Y-%m-%d-%H-%M-%S");

    std::vector<std::string> result = StringLib::Split(currentTime, '-');
    return stoi(result[4]);
}

int DateTime::Second() {
    std::string currentTime = DateTime::GetCurrentTime("%Y-%m-%d-%H-%M-%S");

    std::vector<std::string> result = StringLib::Split(currentTime, '-');
    return stoi(result[5]);
}