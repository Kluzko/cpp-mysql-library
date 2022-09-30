#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <mysql.h>
#include <algorithm>
#include <vector>

namespace library {
	class Database
	{
	private:
		MYSQL* _conn = nullptr;
	public:
		Database();
		~Database() {
			mysql_close(_conn);
		};
		MYSQL_RES* exec_query(const char* query);
		bool showSearchedQuery(const std::string& table, const std::string& field, std::string searchedValue, std::vector<std::string>& returnedIds);
		bool showSearchedBooksInLibrary(std::string searchedValue, std::vector<std::string>& returnedIds);
		std::vector<std::string> returnBooksBorrowedByUser(std::string memberId);
		void showFullTable(const std::string& table, std::vector<std::string>& returnedIds);
		std::string lastInsertedId();
		std::string insertValueAndReturnId(const std::string query);
		int checkLength(std::string query);
		
		void queryToDatabase(const std::string query, const std::string msg);
		void readFromDatabase(const std::string query);
	};
};

#endif // !DATABASE_H
