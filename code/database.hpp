#pragma once

#include "sqlite3.h"
#include <string>
#include <iostream>

using namespace std;

class Database{
public:
    Database(const char* filename);
    string sql_query(const char* query);

private:
    sqlite3 *db;
};
