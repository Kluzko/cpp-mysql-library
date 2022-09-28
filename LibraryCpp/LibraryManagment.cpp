#include "LibraryManagment.h"



using namespace library;



void LibraryManagment::borrowBook()
{
	try
	{
		std::string memberId = getMember();

		if (!canBorrowNewBook(true, memberId)) {
			throw "\n You need to return books you borrowed to get new one. \n";
		}

		std::string bookId = getBookInLibrary();

		std::cout << "Do you want to borrow this book.";

		// TODO: IDK why i need to get it like library::[some class] not from class fix here
	
		if (library::Book::userChoice()) {

			//update book to borrowed
			std::string setBookToBorrowed = "UPDATE books SET isBorrowed = 1 WHERE book_id = " + bookId + "";
			MYSQL_RES* bookBorrowRes = library::Database::exec_query(setBookToBorrowed.c_str());
			mysql_free_result(bookBorrowRes);
			
			//insert query
			std::string borrowBook = "INSERT INTO borrowed_books(book_id,member_id) VALUES(' "+bookId+" ', ' "+memberId+"' )";
			MYSQL_RES* res = library::Database::exec_query(borrowBook.c_str());
			mysql_free_result(bookBorrowRes);	
			std::cout << "Successful borrowing of a book \n";
		}
		else {
			throw "Borrowing book operation aborted.";
		}
		
	}
	catch (const char * msg)
	{
		std::cout << msg << "\n";
	}
}
