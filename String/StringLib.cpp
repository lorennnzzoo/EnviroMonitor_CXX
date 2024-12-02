#include "StringLib.h"



std::vector<std::string> StringLib::Split(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::string token;
    std::istringstream tokenStream(input);

    // Split the string by the delimiter
    while (std::getline(tokenStream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}