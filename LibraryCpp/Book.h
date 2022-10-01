#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <mysql.h>
#include <vector>

#include "Database.h"
#include "Utils.h"

namespace library {
	class Book :protected Database
	{
	public:
		Book() = default;

		bool createBook();
		bool showBooksByCategory();
		bool showBooksByAuthor();

		void showBooksBorrowState(int limit, bool showBorrowed);
		void showLatestBooks(int limit);
		void showMostBorrowedBooks(int limit);
		void showAllBooks();
	protected:
		std::string getBookInLibrary();

	private:
		void _showBookBeforeAdd(std::string title, std::string authorId, std::string genreId);
		std::string _getGenre();
		std::string _getAuthor(bool canAddNewAuthor);
	};
};

#endif // !BOOK_H
