#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <climits>
#include <vector>


const std::string getString(const std::string& msg, int maxLen);
int getNumber(const std::string& msg);
int getNumberWithLimit(const std::string& msg, int limit);
std::vector<int> stringsToInts(std::vector<std::string> strs);
int getNumberFromProvided(std::vector<std::string> strs);
bool userChoice();


#endif // !UTILS_H
