# Cpp-mysql library

This is a console application built for a library management system. It was created to provide more experience in both C++ and MySQL.

## Prerequisite


Before using this application, you must install the MySQL Connector and MySQL Server. The best way to do this is by downloading and installing from the following link:
https://dev.mysql.com/downloads/installer/

I have used the following versions:

- MySQL Server 8.0.30
- Connector/C++ 8.0.30

Additionally, you will need to have the following credentials:

```cpp
const char* HOST = "your host"; // for local database localhost
const char* USER = "your mysql username";
const char* PASSWD = "your myqsl password";
const char* DB_NAME = "your mysql database name";
const int PORT = 3306; //here port number standard is 3306
```

## MYSQL schema

The project file, library.sql, contains the queries used to create the database. You can view a screenshot of the schema below:

![MySQL schema screenshot](librarySchema.png?raw=true "MySQL schema screenshot")

## Project features

The library management system has the following features:

* books
  - creating books [*]
  - showing all books by title with genre and author [*]
  - showing last 20 added/borrowed books [*]
  - showing most borrowed books [*]
* members 
  - creating members [*]
  - showing most active members [*]
  - showing all members by name and books they borrow []
* borrowing books 
  - borrowing book [*]
  - returning book [*]
  - member cannot borrow a book that has already been rented [*]
  - member can borrow maximum of 5 books [*]
## Additon info

This project was created to practice C++ and MySQL and is not meant to be used as a reference for best practices. However, if you still choose to use it, please let the author know if you encounter any mistakes by sending an email to kluzniakkuba@gmail.com.
