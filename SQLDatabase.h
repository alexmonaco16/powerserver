#ifndef _SQLDatabase_h
#define _SQLDatabase_h

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <string>
using namespace std;

// MySQL database details
const string server = "tcp://localhost:3306";
const string username = "root";
const string password = "";
const string db_name = "progetto_sad";

class SQLDatabase {
private:
    sql::Driver* driver = NULL;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
public:
    SQLDatabase();
    void connect();
    void insertMisurazione(int, int, string);
    void insertNewSensoreIfNotExists(int);
    inline void disconnect() { delete con; }
    ~SQLDatabase() { disconnect(); }
};



#endif
