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

bool Member::canBorrowNewBook(bool printInfo, std::string memberId)
{
    if (memberId.empty()){
        throw "You need to provide memberId \n";
    }
    int numOfBorrowedBooks = 0;

    std::string borrowedBooksQuery = "SELECT books.title,borrowed_books.created_at FROM((borrowed_books\
        INNER JOIN books ON borrowed_books.book_id = books.book_id)\
        INNER JOIN members ON borrowed_books.member_id = members.member_id)\
        WHERE borrowed_books.member_id = "+memberId+" AND borrowed_books.isReturned = 0";

    int len = checkLength(borrowedBooksQuery.c_str());

    //printInfo == true print borrowed books
    if (len > 0 && printInfo) {
        MYSQL_RES* res = exec_query(borrowedBooksQuery.c_str());
        MYSQL_ROW row;
        std::cout << "You have " << len << " books to return ! \n";
        std::cout << "===============================================\n";
        while ((row = mysql_fetch_row(res)) != NULL) {
            std::cout << "Title " << row[0] << "Borrowed " << row[1] << "\n";
        }
    }


    // If user has less than 5 not returned books can borrow book
    if (len <= MAX_NUM_OF_BORROWED_BOOKS) {
        return true;
    }

    return false;
}
