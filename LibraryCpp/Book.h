#pragma once


#include <iostream>
#include <mysql.h>
#include <vector>

#include "Database.h"
#include "Utils.h"

namespace library {
	class Book :public Database, public Utils
	{
	public:
		bool createBook();
		void showBookBeforeAdd(std::string title,std::string authorId,std::string genreId);
		void showAllBooks();
	};
};
