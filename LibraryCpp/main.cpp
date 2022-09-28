#include <iostream>

#include "Book.h"
#include "Member.h"
#include "LibraryManagment.h"

int main() {
	try
	{
		library::Book b;
		
		
		
		b.showBooksBorrowState(5, false);
		b.showBooksBorrowState(5, true);
		b.showLatestBooks(5);

	}
	catch (const char * msg)
	{
		std::cout << msg;
	}
	

	return 0;
}