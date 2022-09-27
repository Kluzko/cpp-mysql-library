#pragma once

#include <iostream>
#include <mysql.h>
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
		bool showSearchedQuery(const std::string& table, const std::string& field, std::string searchedValue,std::vector<std::string> &returnedIds );
		void showFullTable(const std::string& table, std::vector<std::string>& returnedIds);
		std::string lastInsertedId();
		std::string insertValueAndReturnId(const std::string& query);
		int checkLength(std::string query);
	};
};
