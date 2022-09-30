#include "Utils.h"

/*
This function takes user input check if it`s correct , if so return it.
@param msg - message to show for user in console
@param maxLen - maximal length of inputed by user string
@return string
*/
const std::string getString(const std::string& msg, int maxLen)
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
int getNumber(const std::string& msg)
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

int getNumberWithLimit(const std::string& msg, int limit)
{
	int number = 0;
	std::cout << msg;
	while ((!(std::cin >> number)) || number > limit)
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	return number;
}

/*
	Convert strings to ints.
	@param strs - a vector of strings to conert
*/
std::vector<int> stringsToInts(std::vector<std::string> strs)
{
	std::vector<int> nums;
	if (strs.empty()) {
		return std::vector<int>();
	}
	for (std::string i : strs) {
		int num = std::stoi(i);
		nums.push_back(num);
	}
	return nums;
}

int getNumberFromProvided(std::vector<std::string> strs)
{
	//converting to ints
	std::vector<int> nums = stringsToInts(strs);

	if (nums.empty()) {
		return 0;
	}

	bool numberIsInVec = false;
	int badInputNum = 0;
	int num;

	while (!numberIsInVec) {
		if (badInputNum == 0) {
			num = getNumber("Enter the number you have dialed: ");
		}
		else {
			num = getNumber("Select number from the list. Try again: ");
		}

		for (int i : nums) {
			if (i == num) {
				numberIsInVec = true;
			}
		}
		badInputNum++;
	}
	return num;
}

bool userChoice()
{
	std::string choice = getString("What's your choice ,type (y/n): ", 1);
	if (choice == "Y" || choice == "y")
		return true;

	return false;
}

