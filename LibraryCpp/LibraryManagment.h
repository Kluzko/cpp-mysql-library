#ifndef LIBRARY_MANAGMENT_H
#define LIBRARY_MANAGMENT_H

#include <iostream>
#include <mysql.h>

#include "Book.h"
#include "Member.h"
#include "Utils.h"

namespace library {
	class LibraryManagment : protected Member, protected Book
	{
	public:
		void borrowBook ();
		void returnTheBook();
	};
}

#endif // !LIBRARY_MANAGMENT_H
