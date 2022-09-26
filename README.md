# Cpp-mysql library

It`s console aplication build for library managmet system.It was created ,becouse I want  to gain more expirience in cpp language and in mysql.


## Prerequisite

First you need to install mysql connector and mysql server.

For me best way to do this was install it from installer:
https://dev.mysql.com/downloads/installer/

Im using 

MySQL Server 8.0.30
Connector/C++ 8.0.30

And second thing are credentials

```cpp
const char* HOST = "your host"; // for local database localhost
const char* USER = "your mysql username";
const char* PASSWD = "your myqsl password";
const char* DB_NAME = "your mysql database name";
const int PORT = 3306; //here port number standard is 3306
```

## MYSQL schema

I added to the project file called library.sql. There are queries 
I used to created this database.

![MySQL schema screenshot](librarySchema.png?raw=true "MySQL schema screenshot")

## Project features

* books
  - creating books [*]
  - showing all books by title with genre and author [*]
  - showing last added books []
* members 
  - creating members []
  - showing most active members []
  - showing all members by name and books they borrow []
* borrowing books 
  - borrowing book []
  - member cant borrow book witch is borrowed []
  - member can borrow maximum of 5 books
## Additon info

I created this project to practice cpp and mysql . I don't recommend following the code written in it. If you want to use this project anyway, please let me know if you find any mistakes. My mail is kluzniakkuba@gmail.com . 
