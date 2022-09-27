#include "Book.h"

using namespace library;


/*
    This function creates book from user input.
*/
bool Book::createBook()
{
    try
    {
        std::cout << "Creating book \n";
        std::string title = getString("Title: ", 50);

        std::string genreId = getGenre();
        std::string authorId = getAuthor(true);

        std::cout << "Your book values\n";
        showBookBeforeAdd(title, authorId, genreId);

        std::cout << "\nDo you want to save the book.\n";
        std::string createBookChoice = getString("Your choice (y/n): ", 1);
        if (createBookChoice == "Y" || createBookChoice == "y") {
            std::string creatBookQuery = "INSERT INTO books(title,genre_id,author_id) VALUES \
        ('" + title + "'," + genreId + "," + authorId + ")";
            MYSQL_RES* res = exec_query(creatBookQuery.c_str());
            if (!res) {
                std::cout << "Creating book operation aborted.\n";
                return false;
            }
            mysql_free_result(res);
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
void Book::showBookBeforeAdd(std::string title, std::string authorId, std::string genreId)
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
    std::string searchForBooks = "SELECT books.title,authors.name,genres.genre FROM((books\
                INNER JOIN genres ON books.genre_id = genres.genre_id) \
                INNER JOIN authors ON books.author_id = authors.author_id)";

    MYSQL_RES* res = exec_query(searchForBooks.c_str());
    MYSQL_ROW row;
    std::cout << "Showing books available in library\n";
    std::cout << "===============================================\n";
    while ((row = mysql_fetch_row(res)) != NULL) {
        std::cout << "Title: " << row[0] << " ,Author: " << row[1] << " ,Genre: " << row[2] << "\n";
    }

    mysql_free_result(res);
}


/*
    Function to select genre
    @return genre id
*/
std::string Book::getGenre()
{
    std::string genre = getString("Genre: ", 50);
    std::vector<std::string> genreIds;
    //Search for genres id and get it
    if (!showSearchedQuery("genres", "genre", genre, genreIds)) {
        std::cout << "No values found. Would you like to try gain?\n";
        std::string choice = getString("Your choice (y/n): ", 1);

        if (choice == "Y" || choice == "y") {
            std::string genre = getString("Genre: ", 50);
            bool isGenreFinded = showSearchedQuery("genres", "genre", genre, genreIds);
            // if second time no val show full list
            if (!isGenreFinded) {
                std::cout << "\nNo values. Here a list of available genres\n";
                showFullTable("genres", genreIds);
            }
        }
        else {
            throw "Error: No genre found";
        }
    }
    std::cout << "\nChoose number from the list\n";
    int genre_num = getNumberFromProvided(genreIds);

    return std::to_string(genre_num);
}


/*
    Function to create/get author.
    @param canAddNewAuthor - specyfy if function should add new author if not finded in mysql db.
    @return author id
*/
std::string Book::getAuthor(bool canAddNewAuthor)
{
    std::string author = getString("Author: ", 100);
    //this var is only called when author is created
    std::string insertedAuthorId;
    std::vector<std::string> authorIds;

    //Search for genres id and get it
    if (!showSearchedQuery("authors", "name", author, authorIds)) {
        std::cout << "No author found. Would you like to try gain?\n";
        std::string choice = getString("Your choice (y/n): ", 1);

        if (choice == "Y" || choice == "y") {
            std::string author = getString("Author: ", 100);
            bool isAuthorFinded = showSearchedQuery("authors", "name", author, authorIds);
            if (!isAuthorFinded && canAddNewAuthor) {
                std::cout << "\nNo author found.Add new author\n";
                std::string author = getString("Author: ", 100);
                std::string query = "INSERT INTO authors(name) VALUES('" + author + "')";
                insertedAuthorId = insertValueAndReturnId(query);
            }
            else {
                throw "Error: No author found";
            }
        }
        else {
            throw "Error: No author found";
        }
    }
    std::string authorId;
    if (insertedAuthorId.empty()) {
        std::cout << "\nChoose number from the list\n";
        int author_num = getNumberFromProvided(authorIds);
        authorId = std::to_string(author_num);
    }
    else {
        authorId = insertedAuthorId;
    }
    return authorId;
}

/*
    Shows books by category specyfied by user.
    @return True if books with specyfied genre are finded else false.
*/
bool Book::showBooksByCategory()
{
    try
    {
        std::string genreId = getGenre();
        std::string showBooksByCategory =  "SELECT books.title,authors.name,genres.genre FROM((books\
                INNER JOIN genres ON books.genre_id = genres.genre_id) \
                INNER JOIN authors ON books.author_id = authors.author_id) WHERE genres.genre_id = "+genreId+"";


        int len =  checkLength(showBooksByCategory);
        MYSQL_RES* res = exec_query(showBooksByCategory.c_str());
       
      
        if (len > 0) {
            MYSQL_ROW row;
            std::cout << "Find "<<len<< " books for this category \n";
            std::cout << "===============================================\n";
            while ((row = mysql_fetch_row(res)) != NULL) {
                std::cout << "Title: " << row[0] << " ,Author: " << row[1] << " ,Genre: " << row[2] << "\n";
            }
           
            
            return true;
        }
        std::cout << "No books found in this category";
       
        return false;
    }
    catch (const char * msg)
    {
        std::cout << msg<<'\n';
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
        std::string authorId = getAuthor(false);
        std::string showBooksByAuthor = "SELECT books.title,authors.name,genres.genre FROM((books\
                INNER JOIN genres ON books.genre_id = genres.genre_id) \
                INNER JOIN authors ON books.author_id = authors.author_id) WHERE authors.author_id = " + authorId + "";

        int len = checkLength(showBooksByAuthor);
        MYSQL_RES* res = exec_query(showBooksByAuthor.c_str());
       

        if (len > 0) {
            MYSQL_ROW row;
            std::cout << "Find"<<len<< "books by this author \n";
            std::cout << "===============================================\n";
            while ((row = mysql_fetch_row(res)) != NULL) {
                std::cout << "Title: " << row[0] << " ,Author: " << row[1] << " ,Genre: " << row[2] << "\n";
            }
            mysql_free_result(res);
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

/*
    Shows latest added books to library
    @param limit specyfie how many is going to be shown
*/
void Book::showLatestBooks(int limit)
{
    if (limit > 0) {
        std::string strLimit = std::to_string(limit);
        std::string latestBooks = "SELECT books.title,authors.name,genres.genre,books.created_at FROM((books \
        INNER JOIN genres ON books.genre_id = genres.genre_id) \
        INNER JOIN authors ON books.author_id = authors.author_id) ORDER BY created_at DESC LIMIT " + strLimit + " ";
        MYSQL_RES* res = exec_query(latestBooks.c_str());
        MYSQL_ROW row;
        std::cout << "Showing "+strLimit+" latest books \n";
        std::cout << "===============================================\n";
        while ((row = mysql_fetch_row(res)) != NULL) {
            std::cout << "Title: " << row[0] << " ,Author: " << row[1] << " ,Genre: " << row[2] <<" , Created at:  " << row[3] << "\n";
        }
        mysql_free_result(res);
    }
    else {
        throw "Limit should be bigger than 0";
    }  
}
