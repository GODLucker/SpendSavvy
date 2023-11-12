#pragma once
#include "account.h" 

#include <sqlite3.h>
#include <string>
#include <vector>

class Database {
private:
    sqlite3* db;
    std::string dbName;
public:
    Database(const char* dbName);
    ~Database();
    const char* getDbName() const;
    bool open();
    bool close();
    bool createTable();
    bool insertData(int id, const std::string& accountName, const std::string& currency, const std::string& bankName, int type, double balance);
    std::vector<account> getAllAccounts();
    int getLastId();
};
