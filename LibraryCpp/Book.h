#pragma once


#include <iostream>
#include <mysql.h>

#include "Database.h"
#include "Utils.h"

namespace library {
	class Book :public Database, public Utils
	{
	public:
		void createBook();
		void showAllBooks();
	};
};
