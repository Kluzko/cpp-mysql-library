#include "Database.h"
#include "Credentials.h"


using namespace library;

Database::Database()
{
	MYSQL* conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, HOST, USER, PASSWD, DB_NAME, PORT, NULL, 0)) {
		// If Db doesnt connect throw error
		throw mysql_error(conn);
		
	}
	_conn = conn;
}

/*
		Execute inputed query
		@param query - query to execute
		@return MYSQL_RES *
*/
MYSQL_RES* Database::exec_query(const char* query)
{
	//return true if some error

	if (mysql_query(_conn, query)) {
		std::cout << "Query error: " << mysql_error(_conn) << std::endl;
		exit(1);
	}
	return mysql_use_result(_conn);
}

/*
Searching for inputed filed
@param table - mysql table name
@param filed - mysql field name
@param searchedValue - value you want to find in database
@return bool , if query finded true else false
*/
bool Database::showSearchedQuery(const std::string& table, const std::string& field, std::string searchedValue, std::vector<std::string>& returnedIds)
{
	int countRowNum = 0;
	std::string query = "SELECT * FROM " + table + " WHERE " + field + " LIKE '%" + searchedValue + "%'";
	MYSQL_RES* res = exec_query(query.c_str());
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL) {
		std::cout << row[0] << ") " << row[1] << "\n";
		countRowNum++;
		returnedIds.push_back(row[0]);
	};

	mysql_free_result(res);

	if (countRowNum > 0) {
		return true;
	}

	return false;
}

bool Database::showSearchedBooksInLibrary(std::string searchedValue, std::vector<std::string>& returnedIds)
{
	int countRowNum = 0;
	std::string query = "SELECT books.book_id,books.title FROM books WHERE title LIKE '%" + searchedValue + "%' AND isBorrowed = 0";
	MYSQL_RES* res = exec_query(query.c_str());
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL) {
		std::cout << row[0] << ") " << row[1] << "\n";
		countRowNum++;
		returnedIds.push_back(row[0]);
	};

	mysql_free_result(res);

	if (countRowNum > 0) {
		return true;
	}

	return false;
}

std::vector<std::string> library::Database::returnBooksBorrowedByUser(std::string memberId)
{
	std::vector<std::string> returnIDs;

	std::string borrowedBooksQuery = "SELECT borrowed_books.borrowedBooks_id FROM((borrowed_books\
        INNER JOIN books ON borrowed_books.book_id = books.book_id)\
        INNER JOIN members ON borrowed_books.member_id = members.member_id)\
        WHERE borrowed_books.member_id = " + memberId + " AND borrowed_books.isReturned = 0";

	MYSQL_RES* res = exec_query(borrowedBooksQuery.c_str());
	MYSQL_ROW row;

	while ((row = mysql_fetch_row(res)) != NULL) {
		returnIDs.push_back(row[0]);
	}
	mysql_free_result(res);

	return returnIDs;
}

/*
	Show all cells in choosen table [for now only for tables witch have only id and some value].
	@param table - mysql table name.
	@param returnedIds - this takes ids returned from table
*/
void Database::showFullTable(const std::string& table, std::vector<std::string>& returnedIds)
{
	std::string query = "SELECT * FROM " + table + "";
	MYSQL_RES* res = exec_query(query.c_str());
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL) {
		std::cout << row[0] << " ) " << row[1] << '\n';
		returnedIds.push_back(row[0]);
	}
	mysql_free_result(res);
}

/*
	This function gives last inserted id from db.
	@return id from mysql db
*/
std::string Database::_lastInsertedId()
{
	MYSQL_RES* res = exec_query("SELECT last_insert_id()");
	MYSQL_ROW row = mysql_fetch_row(res);
	std::string id = row[0];
	mysql_free_result(res);
	return id;
}

/*
	Insert value to mysql and return its id
	@return id from mysql db
*/
std::string Database::insertValueAndReturnId(const std::string query)
{
	queryToDatabase(query, "Succesfull new author add.");
	std::string id = _lastInsertedId();
	return id;
}

/*
	Function to check number of rows
	@param string query to fetch
	@return Number of rows in query
*/
int Database::checkLength(std::string query)
{
	int len = 0;
	MYSQL_RES* res = exec_query(query.c_str());
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL) {
		len++;
	}
	mysql_free_result(res);
	return len;
}

void Database::queryToDatabase(const std::string query,const std::string msg)
{
	try
	{
		MYSQL_RES* res = exec_query(query.c_str());
		mysql_free_result(res);
		std::cout << msg;
	}
	catch (const char * msg)
	{
		std::cout << "Connection error: " << msg << "\n";
	}
}

void Database::readFromDatabase(const std::string query)
{
	try
	{
		
		MYSQL_RES* res = exec_query(query.c_str());

		std::vector<std::string> tableNames;
		
	
		MYSQL_FIELD* f{};
		while (f = mysql_fetch_field(res)) {
			tableNames.push_back(f->name);
		}

		
		MYSQL_ROW row{};
		const std::size_t size = tableNames.size();
		
		while ((row = mysql_fetch_row(res)) != NULL) {
			for (std::size_t i = 0; i < size; i++) {
				size_t findedId = tableNames[i].find("_id");
				size_t findIsBorrowed = tableNames[i].find("isBorrowed");
				size_t findIsReturned = tableNames[i].find("isReturned");
				size_t findCount = tableNames[i].find("COUNT(*)");

				if (findedId != std::string::npos) {
					std::cout << row[i] << ") ";
				}
				else if ((findIsBorrowed != std::string::npos) || (findIsReturned != std::string::npos)) {
					if (i == size - 1) {
						if ((std::string)row[i] == "0") {
							std::cout << tableNames[i] << ": " << "No";
						}
						else {
							std::cout << tableNames[i] << ": " << "Yes";
						}
					}
					else {
						if ((std::string)row[i] == "0") {
							std::cout << tableNames[i] << ": " << "No" << " | ";
						}
						else {
							std::cout << tableNames[i] << ": " << "Yes" << " | ";
						}
					}
				}
				else if (findCount != std::string::npos) {
					std::cout <<"borrowed: " << row[i];
				}
				else if (i == size -1) {
					std::cout << tableNames[i] << ": " << row[i];
				}
				else {
					std::cout << tableNames[i] << ": " << row[i] << " | ";
				}
			}
			std::cout << "\n";
		}
		
		mysql_free_result(res);
	
		
	}
	catch (const char* msg)
	{
		std::cout << "Connection error: " << msg << "\n";
	}
}


