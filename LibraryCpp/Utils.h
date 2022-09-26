#pragma once

#include <iostream>
#include <string>
#include <climits>
#include <vector>

class Utils
{
public:
	const std::string getString(const std::string& msg, int maxLen);
	int getNumber(const std::string& msg);
	std::vector<int> stringsToInts(std::vector<std::string> strs);
	int getNumberFromProvided(std::vector<std::string> strs);

};
