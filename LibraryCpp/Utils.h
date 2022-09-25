#pragma once

#include <iostream>
#include <string>
#include <climits>

class Utils
{
public:
	const std::string getString(const std::string& msg, int maxLen);
	int getNumber(const std::string& msg);
};
