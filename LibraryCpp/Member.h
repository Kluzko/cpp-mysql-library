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
		Member() = default;

		std::string getMember();
		std::string getBrrowedBookId(std::string memberId);

		void createMember();
		void showAllMembers();
		void showMostActiveMembers(int limit);
	protected:
		bool canBorrowNewBook(bool printInfo, std::string memberId);
		int numOfBorrowedBook(std::string memberId);
	private:
		unsigned int MAX_NUM_OF_BORROWED_BOOKS = 5;
		void _printBorrowedBooks(std::string memberId);
	};
}

#endif // !MEMBER_H
