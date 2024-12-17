#include "File.h"

std::vector<std::string> File::ReadAllLines() {
    std::vector<std::string> lines;
    std::ifstream file(File::FilePath);

    if (file) {
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        }
        else {
            throw std::exception("Unable to open file.");
        }
    }
    else {
        throw std::exception("File doesnt exist.");
    }
    return lines;
}


void File::WriteLine(const std::string& text) {
    int length = text.length();
    std::string message;
    char newLine = '\n';
    if (text[length] == newLine) {
         message = text.substr(0, text.length() - 1);
        File::WriteText(message);
    }
    else {
        File::WriteText(message);
    }
}

void File::WriteText(const std::string& message) {
    std::ofstream file(File::FilePath, std::ios::app);
    if (file.is_open()) {
        file << message;  // Write all data to the file at once.
        file.close();  // Close the file after writing.
    }
    else {
        throw std::ios_base::failure("Could not open file : " + File::FilePath);
    }
}

//void File::WriteText(std::string& fileName, const std::string& text) {
//    // Open file once for appending.
//    std::ofstream file(fileName, std::ios::app);
//    if (file.is_open()) {
//        file << text;  // Write all data to the file at once.
//        file.close();  // Close the file after writing.
//    }
//    else {
//        throw std::ios_base::failure("Could not open file : "+fileName);
//    }
//}
//
//
//void File::WriteLine(std::string& fileName, const std::string& text) {
//    int length = text.length();
//    std::string message;
//    char newLine = '\n';
//    if (text[length] == newLine) {
//        message = text.substr(0, text.length() - 1);
//        File::WriteText(fileName,message);
//    }
//    else {
//        File::WriteText(fileName, message);
//    }
//}



bool Directory::IsExists(const std::string& path) {
    bool isExists = false;
    struct stat st;
    if (stat("/tmp", &st) == 0)
        return true;
    return isExists;
}