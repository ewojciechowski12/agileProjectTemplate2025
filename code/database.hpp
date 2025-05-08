#pragma once

#include "sqlite3.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Database {
public:
    Database(const char* filename);
    ~Database();
    vector<vector<string>> sql_query(sqlite3_stmt* stmt);

    vector<vector<string>> get_students_by_section(int section_id);

private:
    sqlite3* db;
};
