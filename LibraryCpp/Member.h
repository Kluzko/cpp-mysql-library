#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>

#include "Database.h"
#include "Utils.h"

namespace library {
	class Member : protected Database
	{
	public:
		void createMember();
		std::string getMember();
		void printBorrowedBooks(std::string memberId);
		int numOfBorrowedBook(std::string memberId);
		bool canBorrowNewBook(bool printInfo, std::string memberId);
		std::string getBrrowedBookId(std::string memberId);
		void showAllMembers();
		void showMostActiveMembers(int limit);

	private:
		unsigned int MAX_NUM_OF_BORROWED_BOOKS = 5;
	};
}

#endif // !MEMBER_H
