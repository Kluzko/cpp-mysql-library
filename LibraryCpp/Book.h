#ifndef BOOK_H
#define BOOK_H


#include <iostream>
#include <mysql.h>
#include <vector>

#include "Database.h"
#include "Utils.h"

namespace library {
	class Book :protected Database, protected Utils
	{
	public:
		bool createBook();
		void showBookBeforeAdd(std::string title, std::string authorId, std::string genreId);

		std::string getBook();
		std::string getGenre();
		std::string getAuthor(bool canAddNewAuthor);
		std::string getBookInLibrary();


		bool showBooksByCategory();
		bool showBooksByAuthor();

		void showBooksBorrowState(int limit, bool showBorrowed);
		void showLatestBooks(int limit);
		void showAllBooks();


	};
};


#endif // !BOOK_H



