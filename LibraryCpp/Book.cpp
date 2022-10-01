#include "Book.h"

using namespace library;

/*
	This function creates book from user input.
*/
bool Book::createBook()
{
	try
	{
		std::string title = getString("Title: ", 50);

		std::string genreId = _getGenre();
		std::string authorId = _getAuthor(true);

		std::cout << "Your book values\n";
		_showBookBeforeAdd(title, authorId, genreId);

		std::cout << "\nDo you want to save the book.\n";

		if (userChoice()) {
			std::string creatBookQuery = "INSERT INTO books(title,genre_id,author_id) VALUES \
        ('" + title + "'," + genreId + "," + authorId + ")";
			
			queryToDatabase(creatBookQuery, "Book successfully added to database");

			return true;
		}
		std::cout << "Creating book operation aborted.\n";
		return false;
	}
	catch (const char* msg)
	{
		std::cout << msg << '\n';
		return false;
	}
}

/*
	Show info about book.
	@param title - this is book title
	@param authorId - this is author id from table authors
	@param genreId - this is genre id from table genres
*/
void Book::_showBookBeforeAdd(std::string title, std::string authorId, std::string genreId)
{
	std::string getAuthor = "SELECT authors.name FROM authors WHERE author_id = " + authorId + " ";
	std::string getGenre = "SELECT genres.genre FROM genres WHERE genre_id = " + genreId + "";

	//get values
	MYSQL_RES* authorRes = exec_query(getAuthor.c_str());
	MYSQL_ROW authorRow = mysql_fetch_row(authorRes);
	std::string author = authorRow[0];
	mysql_free_result(authorRes);
	MYSQL_RES* genreRes = exec_query(getGenre.c_str());
	MYSQL_ROW genreRow = mysql_fetch_row(genreRes);
	std::string genre = genreRow[0];
	mysql_free_result(genreRes);

	std::cout << "\n====================================\n";
	std::cout << "Title: " << title;
	std::cout << "\nAuthor: " << author;
	std::cout << "\nGenre: " << genre;
	std::cout << "\n====================================\n";
}

/*
	This function search for all add books and show them with title,author,genre.
*/
void Book::showAllBooks()
{
	// search for books displayed with genre and author
	std::string searchForBooks = "SELECT books.title,authors.name,genres.genre,books.isBorrowed FROM((books\
                INNER JOIN genres ON books.genre_id = genres.genre_id) \
                INNER JOIN authors ON books.author_id = authors.author_id)";

	
	std::cout << "Showing books available in library\n";
	std::cout << "===============================================\n";
	readFromDatabase(searchForBooks);
}

/*
	Function to select genre
	@return genre id
*/
std::string Book::_getGenre()
{
	std::string genre = getString("Genre: ", 50);
	std::vector<std::string> genresId;
	//Search for genres id and get it
	if (!showSearchedQuery("genres", "genre", genre, genresId)) {
		std::cout << "Genre not found. Would you like to try gain?\n";

		if (userChoice()) {
			std::string genre = getString("Genre: ", 50);
			bool isGenreFinded = showSearchedQuery("genres", "genre", genre, genresId);
			// if second time no val show full list
			if (!isGenreFinded) {
				std::cout << "\nNo values. Here a list of available genres\n";
				showFullTable("genres", genresId);
			}
		}
		else {
			throw "Error: Genre not found";
		}
	}
	std::cout << "\nChoose number from the list\n";
	int genre_num = getNumberFromProvided(genresId);

	return std::to_string(genre_num);
}

/*
	Function to create/get author.
	@param canAddNewAuthor - specyfy if function should add new author if not finded in mysql db.
	@return author id
*/
std::string Book::_getAuthor(bool canAddNewAuthor)
{
	std::string author = getString("Author: ", 100);
	//this var is only called when author is created
	std::string insertedAuthorId;
	std::vector<std::string> authorsId;

	//Search for genres id and get it
	if (!showSearchedQuery("authors", "name", author, authorsId)) {
		std::cout << "Author not found. Would you like to try gain?\n";

		if (userChoice()) {
			std::string author = getString("Author: ", 100);
			bool isAuthorFinded = showSearchedQuery("authors", "name", author, authorsId);
			if (!isAuthorFinded && canAddNewAuthor) {
				std::cout << "\nNo author found.Add new author\n";
				std::string author = getString("Author: ", 100);
				std::string query = "INSERT INTO authors(name) VALUES('" + author + "')";
				insertedAuthorId = insertValueAndReturnId(query);
			}
			else {
				throw "Error:Author not found";
			}
		}
		else {
			throw "Error: Author not found";
		}
	}
	std::string authorId;
	if (insertedAuthorId.empty()) {
		std::cout << "\nChoose number from the list\n";
		int author_num = getNumberFromProvided(authorsId);
		authorId = std::to_string(author_num);
	}
	else {
		authorId = insertedAuthorId;
	}
	return authorId;
}

std::string Book::getBookInLibrary()
{
	std::string book = getString("Title: ", 100);
	std::vector<std::string> booksId;
	if (!showSearchedBooksInLibrary(book, booksId)) {
		std::cout << "No values found. Would you like to try gain?\n";

		if (userChoice()) {
			std::string book = getString("Title: ", 100);
			bool isGenreFinded = showSearchedBooksInLibrary(book, booksId);
			// if second time no val show full list
			if (!isGenreFinded) {
				throw "Error: Book not found";
			}
		}
		else {
			throw "Error: Book not found";
		}
	}

	std::cout << "\nChoose number from the list\n";
	int book_num = getNumberFromProvided(booksId);

	return std::to_string(book_num);
}

/*
	Shows books by category specyfied by user.
	@return True if books with specyfied genre are finded else false.
*/
bool Book::showBooksByCategory()
{
	try
	{
		std::string genreId = _getGenre();
		std::string showBooksByCategory = "SELECT books.title,authors.name,genres.genre FROM((books\
                INNER JOIN genres ON books.genre_id = genres.genre_id) \
                INNER JOIN authors ON books.author_id = authors.author_id) WHERE genres.genre_id = " + genreId + "";

		int len = checkLength(showBooksByCategory);
		

		if (len > 0) {
			std::cout << "Finded " << len << " books for this category \n";
			std::cout << "===============================================\n";
			readFromDatabase(showBooksByCategory);
			return true;
		}
		std::cout << "No books found in this category";

		return false;
	}
	catch (const char* msg)
	{
		std::cout << msg << '\n';
		return false;
	}
}

/*
	Shows books by author specyfied by user.
	@return True if author with specyfied name are finded else false.
*/
bool Book::showBooksByAuthor()
{
	try
	{
		std::string authorId = _getAuthor(false);
		std::string showBooksByAuthor = "SELECT books.title,authors.name,genres.genre FROM((books\
                INNER JOIN genres ON books.genre_id = genres.genre_id) \
                INNER JOIN authors ON books.author_id = authors.author_id) WHERE authors.author_id = " + authorId + "";

		int len = checkLength(showBooksByAuthor);

		if (len > 0) {
			std::cout << "Finded " << len << " books by this author \n";
			std::cout << "===============================================\n";
			readFromDatabase(showBooksByAuthor);
			return true;
		}

		std::cout << "No books found by this author";
		return false;
	}
	catch (const char* msg)
	{
		std::cout << msg << '\n';
		return false;
	}
}

void Book::showBooksBorrowState(int limit, bool showBorrowed)
{
	if (limit < 1) {
		throw "Error: Limit should be bigger than 0";
	}

	std::string strLimit = std::to_string(limit);
	//if borrowed books show 1 for true else false
	std::string borrowState = (showBorrowed) ? "1" : "0";

	std::string query = "SELECT books.title,authors.name,genres.genre,books.created_at FROM((books \
        INNER JOIN genres ON books.genre_id = genres.genre_id) \
        INNER JOIN authors ON books.author_id = authors.author_id) WHERE isBorrowed = " + borrowState + " ORDER BY created_at DESC LIMIT " + strLimit + " ";

	std::string borrowMsg = (showBorrowed) ? " borrowed books" : " not borrowed books";
	// check length to know how many books is there
	int len = checkLength(query.c_str());

	if (len == 0) {
		std::cout << "Dont find any" << borrowMsg << "\n";
	}
	else {
		if (len < limit) {
			std::cout << "You have only " << len << " in your database \n";
		}
		
		std::cout << "Finded " << len << borrowMsg << "\n";
		std::cout << "===============================================\n";
		readFromDatabase(query);
	}
}

/*
	Shows latest added books to library
	@param limit specyfie how many is going to be shown
*/
void Book::showLatestBooks(int limit)
{
	if (limit < 1) {
		throw "Error: Limit should be bigger than 0";
	}
	std::string strLimit = std::to_string(limit);
	std::string latestBooks = "SELECT books.title,authors.name,genres.genre,books.created_at FROM((books \
        INNER JOIN genres ON books.genre_id = genres.genre_id) \
        INNER JOIN authors ON books.author_id = authors.author_id) ORDER BY created_at DESC LIMIT " + strLimit + " ";

	int len = checkLength(latestBooks.c_str());
	if (len == 0) {
		std::cout << "Dont find any books in your databse \n";
	}
	else {
		if (len < limit) {
			std::cout << "You have only " << len << " in your database \n";
		}
		std::cout << "Finded " << len << " latest books." << "\n";
		std::cout << "===============================================\n";
		readFromDatabase(latestBooks);
	}
}

void Book::showMostBorrowedBooks(int limit)
{
	if (limit < 1) {
		throw "Error: Limit should be bigger than 0";
	}
	std::string strLimit = std::to_string(limit);
	std::string mostBorrowedBooks = "SELECT books.title, COUNT(*) FROM((borrowed_books\
			INNER JOIN books ON borrowed_books.book_id = books.book_id)\
			INNER JOIN members ON borrowed_books.member_id = members.member_id)\
		GROUP BY books.title LIMIT " + strLimit + " ";

	int len = checkLength(mostBorrowedBooks.c_str());
	
	if (len < 0) {
		throw "No members found";
	}
	if (limit > len) {
		std::cout << "Found only " << len << " members \n";
	}
	
	std::cout << "Finded " << len << " latest books." << "\n";
	std::cout << "===============================================\n";
	readFromDatabase(mostBorrowedBooks);
}
