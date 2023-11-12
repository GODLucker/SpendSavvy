#include "database.h"
#include "account.h"  

Database::Database(const char* dbName) : dbName(dbName) ,db(nullptr) {
    if (sqlite3_open(this->dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}



Database::~Database() {
      if (db) {
            sqlite3_close(db);
        }
}

const char* Database::getDbName() const {
    return dbName.c_str();
}



bool Database::open() {
     int rc = sqlite3_open(dbName.c_str(), &db);

        if (rc != SQLITE_OK) {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        return true;
}

bool Database::close() {
     // Реалізація методу для закриття бази даних
    if (sqlite3_close(db) != SQLITE_OK) {
        std::cerr << "Can't close database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    db = nullptr;
    return true;
}

bool Database::createTable() {
    // Реалізація методу для створення таблиці
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS accounts (
            id INTEGER PRIMARY KEY,
            accountName TEXT NOT NULL,
            currency TEXT NOT NULL,
            bankName TEXT NOT NULL,
            type INTEGER,
            balance REAL
        );
    )";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQLite error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool Database::insertData(int id, const std::string& accountName, const std::string& currency, const std::string& bankName, int type, double balance) {
    if (accountName.empty() || currency.empty() || bankName.empty()) {
        std::cerr << "Invalid input data" << std::endl;
        return false;
    }

   // Реалізація методу для вставки даних в таблицю
    const char* insertDataSQL = "INSERT INTO accounts (id, accountName, currency, bankName, type, balance) VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, insertDataSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQLite prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, accountName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, currency.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, bankName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, type);
    sqlite3_bind_double(stmt, 6, balance);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQLite step error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

std::vector<account> Database::getAllAccounts() {
    // Реалізація методу для отримання всіх облікових записів з бази
    std::vector<account> accounts;

     const char* selectAllSQL = "SELECT * FROM accounts;";
    sqlite3_stmt* stmt;
    
    

     if (sqlite3_prepare_v2(db, selectAllSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQLite prepare error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Викликаємо finalize перед поверненням
        return std::vector<account>(); // повертаємо пустий вектор у разі помилки
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* accountName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* currency = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* bankName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int type = sqlite3_column_int(stmt, 4);
        double balance = sqlite3_column_double(stmt, 5);

        accounts.emplace_back(id, accountName, currency, bankName, static_cast<cards_type>(type), balance);
    }

    sqlite3_finalize(stmt);
    return accounts;
}

int Database::getLastId() {
    const char* query = "SELECT MAX(id) FROM accounts;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int lastId = sqlite3_column_int(stmt, 0); // 0 - індекс першого стовпця в результаті
            sqlite3_finalize(stmt);
            return lastId;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "SQLite prepare error: " << sqlite3_errmsg(db) << std::endl;
    }

    return -1; // Повертаємо -1 як позначення помилки
}
