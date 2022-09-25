#pragma once

#include <iostream>
#include <mysql.h>

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
		bool showSearchedQuery(const std::string& table, const std::string& field, std::string searchedValue);
		std::string lastInsertedId();
	};
};
