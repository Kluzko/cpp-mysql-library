#include "LibraryManagment.h"



using namespace library;



void LibraryManagment::borrowBook()
{
	try
	{
		std::string memberId = getMember();

		if (!canBorrowNewBook(true,memberId)) {
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
			MYSQL_RES* insertBorrowedBook = library::Database::exec_query(borrowBook.c_str());
			mysql_free_result(insertBorrowedBook);
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

void LibraryManagment::returnTheBook()
{
	try
	{
		std::string memberId = getMember();
		int numOfBorrowdBooks = numOfBorrowedBook(memberId);

		if (numOfBorrowdBooks == 0) {
			throw "You have no books to return.\n";
		}

		std::string brrowedBookId =  getBrrowedBookId(memberId);

		std::cout << "Do you want to return this book.";

		// TODO: IDK why i need to get it like library::[some class] not from class fix here

		if (library::Book::userChoice()) {
			// change borrowedBook to returned 
			std::string changeBorrowedBookToReturned = "UPDATE borrowed_books SET isReturned = 1 WHERE borrowedBooks_id = " + brrowedBookId + "";
			MYSQL_RES* bookBorrowRes = library::Database::exec_query(changeBorrowedBookToReturned.c_str());
			mysql_free_result(bookBorrowRes);
			// query to get book
			std::string getBookId = "SELECT book_id FROM borrowed_books WHERE borrowedBooks_id = " + brrowedBookId + "";
			MYSQL_RES* bookIdRes = library::Database::exec_query(getBookId.c_str());
			MYSQL_ROW row = mysql_fetch_row(bookIdRes);
			std::string bookId = row[0];
			mysql_free_result(bookIdRes);
			// set is borrowed to false
			std::string setBookToReturned = "UPDATE books SET isBorrowed = 0 WHERE book_id = " + bookId + "";
			MYSQL_RES* bookReturnRes = library::Database::exec_query(setBookToReturned.c_str());
			mysql_free_result(bookReturnRes);

		}
		else {
			throw "Returning book operation aborted.";
		}
	}
	catch (const char* msg)
	{
		std::cout << msg << "\n";
	}	
}
