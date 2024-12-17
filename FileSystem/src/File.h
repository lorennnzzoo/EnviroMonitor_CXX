#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
class File {
public:
	std::string FilePath;
	File(const std::string& filePath) {
		FilePath = filePath;
	}

	std::vector<std::string> ReadAllLines();
	std::string ReadAllText();
	

	/*static void WriteText(std::string&,const std::string&);
	static void WriteLine(std::string&, const std::string&);*/
	void WriteLine(const std::string&);
	void WriteText(const std::string&);
	
};


class Directory {
public:	
	static bool IsExists(const std::string&);
	static void Create(const std::string&);
	static std::string GetCurrentDirectory();
};