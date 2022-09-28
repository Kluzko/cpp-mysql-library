#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>

#include "Database.h"
#include "Utils.h"

namespace library {
	class Member : protected Database, protected Utils
	{
	public:
		void createMember();
		std::string getMember();
		bool canBorrowNewBook(bool printInfo, std::string memberId);
	private:
		unsigned int MAX_NUM_OF_BORROWED_BOOKS = 5;
	};
}


#endif // !MEMBER_H




