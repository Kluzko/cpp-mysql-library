#include "Book.h"

using namespace library;


/*
    This function creates book from user input.
*/
void Book::createBook()
{
    std::cout<<"Creating book \n";

    std::string titile = getString("Titile: ", 100);
    std::string genre = getString("Genre: ", 50);
    if (!showSearchedQuery("genres", "genre", genre)) {
        std::string choice;
        std::cout << "No values found.Would you like to try again?\n";
        choice = getString("Your choice (y/n): ", 1);


        if (choice == "Y" || choice == "y") {
            int genreRowNum = 0;
            std::string genre = getString("Genre: ", 50);
            bool isGenreFinded = showSearchedQuery("genres", "genre", genre);
            // if second time no value found show full list
            if (!isGenreFinded) {
                std::cout << "\nNo values. Here a list of available genres\n";
                //
                MYSQL_RES* res = exec_query("SELECT * FROM genres");
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res))) {
                    std::cout << row[0] << " ) " << row[1] << '\n';
                }
               
            };
        }
    }
    int genreId = getNumber("Write genre number to choose it: ");

    std::string author = getString("Author: ", 100);
    std::string createdAuthorId;
   
    if (!showSearchedQuery("authors", "name", author)) {
        std::string choice;
        std::cout << "No values found.Would you like to try again?\n";
        choice = getString("Your choice (y/n): ", 1);
        //TODO if second time no value ask to add new author
        if (choice == "Y" || choice == "y") {
            int authorRowNumber = 0;
            std::string author = getString("Author: ", 100);
            bool isAuthorFinded = showSearchedQuery("authors", "name", author);
            if (!isAuthorFinded) {
                std::cout << "\nAuthor not found.Add new author\n";
                std::string author = getString("Author: ", 100);
                std::string query = "INSERT INTO authors(name) VALUES('" + author + "')";
                MYSQL_RES* res = exec_query(query.c_str());

                createdAuthorId = lastInsertedId();
                
            }
        }
    }
    int authorId = 0;
   
    if (createdAuthorId.empty()) {
        authorId = getNumber("Write author number to choose it: ");
    }
    

    // TODO: Show book before add 
    std::cout << "\nDo you want to save the book.\n";
    std::string createBookChoice = getString("Your choice (y/n): ", 1);
    if (createBookChoice == "Y" || createBookChoice == "y") {

        std::string selectAuthorId = (authorId == 0) ? createdAuthorId : std::to_string(authorId);
        std::string creatBookQuery = "INSERT INTO books(title,genre_id,author_id) VALUES \
    ('" + titile + "'," + std::to_string(genreId) + "," + selectAuthorId + ")";

 
        MYSQL_RES* res = exec_query(creatBookQuery.c_str());
       
        std::cout << "Book created successfully.";
    }
    else {
        std::cout << "Book not created.";
        exit(1);
    }
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
