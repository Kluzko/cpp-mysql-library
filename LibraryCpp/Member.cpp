#include "Member.h"

using namespace library;

void Member::createMember()
{
	std::cout << "Adding new member\n";
	std::string name = getString("Name: ", 100);

	std::string insertMember = "INSERT INTO members(name) VALUES ('" + name + "')";

	MYSQL_RES* res = exec_query(insertMember.c_str());
	
	std::cout << "Author  successfully added to database";
	mysql_free_result(res);	
}

std::string Member::getMember()
{
	std::string member = getString("Name: ", 100);
    std::vector<std::string> membersId;
    //Search for genres id and get it
    if (!showSearchedQuery("members", "name", member, membersId)) {
        std::cout << "No values found. Would you like to try gain?\n";
        std::string choice = getString("Your choice (y/n): ", 1);

        if (choice == "Y" || choice == "y") {
            std::string member = getString("Name: ", 100);
            bool isGenreFinded = showSearchedQuery("members", "name", member, membersId);

            if (!isGenreFinded) {
                throw "Error: No member found";
            }
        }
        else {
            throw "Error: No member found";
        }
    }
    std::cout << "\nChoose number from the list\n";
    int member_num = getNumberFromProvided(membersId);

	return std::to_string(member_num);
}
