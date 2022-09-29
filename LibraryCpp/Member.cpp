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
	std::string member = getString("Member Name: ", 100);
	std::vector<std::string> membersId;
	//Search for genres id and get it
	if (!showSearchedQuery("members", "name", member, membersId)) {
		std::cout << "No values found. Would you like to try gain?\n";
		if (userChoice()) {
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

void Member::printBorrowedBooks(std::string memberId)
{
	int len = numOfBorrowedBook(memberId);
	std::string borrowedBooksQuery = "SELECT borrowed_books.borrowedBooks_id,books.title,\
        borrowed_books.created_at FROM((borrowed_books\
        INNER JOIN books ON borrowed_books.book_id = books.book_id)\
        INNER JOIN members ON borrowed_books.member_id = members.member_id)\
        WHERE borrowed_books.member_id = " + memberId + " AND borrowed_books.isReturned = 0";

	MYSQL_RES* res = exec_query(borrowedBooksQuery.c_str());
	MYSQL_ROW row;
	std::cout << "You have " << len << " books to return ! \n";
	std::cout << "===============================================\n";
	while ((row = mysql_fetch_row(res)) != NULL) {
		std::cout << row[0] << ") " << "Title " << row[1] << ", Borrowed " << row[2] << "\n";
	}
	mysql_free_result(res);
}

int Member::numOfBorrowedBook(std::string memberId)
{
	if (memberId.empty()) {
		throw "You need to provide memberId \n";
	}

	std::string borrowedBooksQuery = "SELECT books.title,borrowed_books.created_at FROM((borrowed_books\
        INNER JOIN books ON borrowed_books.book_id = books.book_id)\
        INNER JOIN members ON borrowed_books.member_id = members.member_id)\
        WHERE borrowed_books.member_id = " + memberId + " AND borrowed_books.isReturned = 0";

	int len = checkLength(borrowedBooksQuery.c_str());

	return len;
}

bool Member::canBorrowNewBook(bool printInfo, std::string memberId)
{
	try
	{
		int len = numOfBorrowedBook(memberId);

		if (len > 0 && printInfo) {
			printBorrowedBooks(memberId);
		}

		// If user has less than 5 not returned books can borrow book
		if (len <= MAX_NUM_OF_BORROWED_BOOKS) {
			return true;
		}

		return false;
	}
	catch (const char* msg)
	{
		std::cout << msg << "\n";
		return false;
	}
}

std::string Member::getBrrowedBookId(std::string memberId)
{
	if (memberId.empty()) {
		throw "No member specified \n";
	}

	printBorrowedBooks(memberId);

	std::vector<std::string> booksId = returnBooksBorrowedByUser(memberId);

	std::cout << "\nChoose number from the list\n";
	int book_num = getNumberFromProvided(booksId);

	return std::to_string(book_num);
}