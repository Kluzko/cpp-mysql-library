#include "Member.h"

using namespace library;

void Member::createMember()
{
	std::cout << "Adding new member\n";
	std::string name = getString("Name: ", 100);

	std::string insertMember = "INSERT INTO members(name) VALUES ('" + name + "')";

	MYSQL_RES* res = exec_query(insertMember.c_str());
	
	std::cout << "Author successfully added to database";
	mysql_free_result(res);
	
}
