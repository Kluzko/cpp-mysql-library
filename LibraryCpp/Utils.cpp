#include "Utils.h"

/*
This function takes user input check if it`s correct , if so return it.
@param msg - message to show for user in console
@param maxLen - maximal length of inputed by user string
@return string
*/
const std::string Utils::getString(const std::string& msg, int maxLen)
{
	std::string s;
	std::cout << msg;
	std::getline(std::cin >> std::ws, s);

	while (s.empty())
	{
		std::cout << "No value.Try again: ";
		std::getline(std::cin, s);
	}

	while (s.size() > maxLen) {
		printf("Value should be equal or lower than %d.Try again: ", maxLen);
		std::getline(std::cin, s);
	}
	return s;
}
/*
This function takes user input check if it`s int , if so return it.
@param msg - message to show for user in console
@return int
*/
int Utils::getNumber(const std::string& msg)
{
	int number = 0;
	std::cout << msg;
	while (!(std::cin >> number))
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	return number;
}