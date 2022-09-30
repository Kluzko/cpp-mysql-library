#include <iostream>

#include "Book.h"
#include "Member.h"
#include "LibraryManagment.h"
#include "Utils.h"


int main() {
	library::LibraryManagment lib;
	library::Member m;
	library::Book b;
	

	std::cout << "Welcome in console libary managment system \n";
	std::cout << "Choose options from the list \n";
	std::string choice = "Y";

	try
	{
		do
		{
			std::cout << "\nBasic operations";
			std::cout << "\n====================================\n";
			std::cout << "1) Borrow book\n";
			std::cout << "2) Return book\n";

			std::cout << "\nCreating";
			std::cout << "\n====================================\n";
			std::cout << "3) Add new book\n";
			std::cout << "4) Add new member\n";

			std::cout << "\nSearching";
			std::cout << "\n====================================\n";
			std::cout << "5) Show  all books\n";
			std::cout << "6) Show  all members\n";
			std::cout << "7) Show books by author\n";
			std::cout << "8) Show books by genre\n";
			std::cout << "9) Show 5 most active members\n";
			std::cout << "10) Show 5 most frequently borrowed books\n";
			std::cout << "11) Show 20 latest books\n";
			std::cout << "12) Show books 20 last borrowed books\n\n";
			int num =getNumberWithLimit("Your choice: ", 12);

			switch (num)
			{
			case 1: {
				std::cout << "\nBorrowing a book\n";
				std::cout << "\n====================================\n";
				lib.borrowBook();
				std::cout << "\n====================================\n";
				break;
			}
			case 2: {
				std::cout << "\nReturning the book\n";
				std::cout << "\n====================================\n";
				lib.returnTheBook();
				std::cout << "\n====================================\n";
				break;
			}
			case 3: {
				std::cout << "\nAdding new book\n";
				std::cout << "\n====================================\n";
				b.createBook();
				std::cout << "\n====================================\n";
				break;
			}
			case 4: {
				std::cout << "\nAdding new member\n";
				std::cout << "\n====================================\n";
				m.createMember();
				std::cout << "\n====================================\n";
				break;
			}
			case 5: {
				std::cout << "\nShowing all books\n";
				std::cout << "\n====================================\n";
				b.showAllBooks();
				std::cout << "\n====================================\n";
				break;
			}
			case 6: {
				std::cout << "\nShowing all members\n";
				std::cout << "\n====================================\n";
				m.showAllMembers();
				std::cout << "\n====================================\n";
				break;
			}
			case 7: {
				std::cout << "\nShowing books by author\n";
				std::cout << "\n====================================\n";
				b.showBooksByAuthor();
				std::cout << "\n====================================\n";
				break;
			}
			case 8: {
				std::cout << "\nShowing books by genre\n";
				std::cout << "\n====================================\n";
				b.showBooksByCategory();
				std::cout << "\n====================================\n";
				break;
			}
			case 9: {
				//TODO add option to choose limit
				std::cout << "\nShowing 5 most active members\n";
				std::cout << "\n====================================\n";
				m.showMostActiveMembers(5);
				std::cout << "\n====================================\n";
				break;
			}
			case 10: {
				std::cout << "\nShowing 5 most frequently borrowed books\n";
				std::cout << "\n====================================\n";
				b.showMostBorrowedBooks(5);
				std::cout << "\n====================================\n";
				break;
			}
			case 11: {
				//TODO add option to choose limit
				std::cout << "\nShowing 20 latest books\n";
				std::cout << "\n====================================\n";
				b.showLatestBooks(20);
				std::cout << "\n====================================\n";
				break;	
			}
			case 12: {
				//TODO add option to choose limit
				std::cout << "\nShowing books 20 last borrowed books\n";
				std::cout << "\n====================================\n";
				b.showBooksBorrowState(20, true);
				std::cout << "\n====================================\n";
				break;
			}
			default:
				break;
			}

			choice = getString("Do you want to search again (y/n): ", 1);
		} while (choice == "Y" || choice == "y");
	}
	catch (const char* msg)
	{
		std::cout << msg << '/n';
	}

	return 0;
}