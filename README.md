# Cpp-mysql library

It`s library managmet system. I build it to gain more expirience in cpp language and in mysql.


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
