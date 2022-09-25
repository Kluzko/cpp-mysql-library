#include "Database.h"
#include "Credentials.h"
using namespace library;

Database::Database()
{
	MYSQL* conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, HOST, USER, PASSWD, DB_NAME, PORT, NULL, 0)) {
		// If Db doesnt connect throw error
		std::cout << "Connection error: " << mysql_error(conn) << std::endl;
		exit(1);
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
bool Database::showSearchedQuery(const std::string& table, const std::string& field, std::string searchedValue)
{
	int countRowNum = 0;
	std::string query = "SELECT * FROM " + table + " WHERE " + field + " LIKE '%" + searchedValue + "%'";
	MYSQL_RES* res = exec_query(query.c_str());
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL) {
		std::cout << row[0] << ") " << row[1] << "\n";
		countRowNum++;
	};

	if (countRowNum > 0) {
		return true;
	}

	return false;
}

/*
	This function gives last inserted id from db.
	@return id from mysql db
*/

std::string Database::lastInsertedId()
{
	MYSQL_RES * res = exec_query("SELECT last_insert_id()");
	MYSQL_ROW row = mysql_fetch_row(res);
	std::string id = row[0];
	mysql_free_result(res);
	return id;
}
