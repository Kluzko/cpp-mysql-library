#include "Member.h"

using namespace library;

void Member::createMember()
{
	std::string name = getString("Name: ", 100);

	std::string insertMember = "INSERT INTO member(name) VALUES ('" + name + "')";
	
	queryToDatabase(insertMember, "Author  successfully added to database");
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

void Member::_printBorrowedBooks(std::string memberId)
{
	int len = numOfBorrowedBook(memberId);
	std::string borrowedBooksQuery = "SELECT borrowed_books.borrowedBooks_id,books.title,\
        borrowed_books.created_at FROM((borrowed_books\
        INNER JOIN books ON borrowed_books.book_id = books.book_id)\
        INNER JOIN members ON borrowed_books.member_id = members.member_id)\
        WHERE borrowed_books.member_id = " + memberId + " AND borrowed_books.isReturned = 0";

	std::cout << "You have " << len << " books to return ! \n";
	std::cout << "===============================================\n";
	readFromDatabase(borrowedBooksQuery);
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
			_printBorrowedBooks(memberId);
		}

		// If user has less than 5 not returned books can borrow book
		if ((unsigned) len <= MAX_NUM_OF_BORROWED_BOOKS) {
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

	_printBorrowedBooks(memberId);

	std::vector<std::string> booksId = returnBooksBorrowedByUser(memberId);

	std::cout << "\nChoose number from the list\n";
	int book_num = getNumberFromProvided(booksId);

	return std::to_string(book_num);
}

void Member::showAllMembers()
{
	std::string query = "SELECT member_id,name FROM members";
	readFromDatabase(query);
}

void library::Member::showMostActiveMembers(int limit)
{
	std::string strLimit = std::to_string(limit);

	std::string query = "SELECT members.name,COUNT(*) FROM((borrowed_books\
		INNER JOIN books ON borrowed_books.book_id = books.book_id)\
		INNER JOIN members ON borrowed_books.member_id = members.member_id)\
		GROUP BY members.name LIMIT "+ strLimit +" ";

	int len = checkLength(query.c_str());
	if (len < 0) {
		throw "No members found";
	}
	if (limit > len) {
		std::cout << "Found only " << len << " members \n";
	}
	
	readFromDatabase(query);
}
