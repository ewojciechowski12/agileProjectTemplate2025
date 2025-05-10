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
    

    vector<vector<string>> get_students_by_section(int section_id);
    vector<vector<string>> get_semseters();
    vector<vector<string>> get_courses_sections_by_semseter(int semester_id);
    vector<vector<string>> get_student_name_by_id(int student_id);

    void print_data(vector<vector<string>> data);

private:
    sqlite3* db;
    vector<vector<string>> execute_query(sqlite3_stmt* stmt);
    sqlite3_stmt* prepare_and_bind(const char* query, const vector<int>& intParams);
};
