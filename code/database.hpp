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

    void print_data(vector<vector<string>> data);
    vector<vector<string>> get_students_by_section(int section_id);
    vector<vector<string>> get_students_id_by_section(int section_id);
    vector<vector<string>> get_semseters();
    vector<vector<string>> get_courses_sections_by_semester(int semester_id);
    
    bool take_attendance(string date, string attendance_status, int section_id, int student_id);
    bool update_attendance(string date, string attendance_status, int section_id, int student_id);
    bool mark_all_students_present(string date, int section_id);
    bool mark_all_students_present(string date, string attendance_status, int section_id, int student_id);

private:
    sqlite3* db;
    
    vector<vector<string>> execute_select_query(sqlite3_stmt* stmt);
    bool execute_insert_query(sqlite3_stmt* stmt);
    sqlite3_stmt* prepare_and_bind_int(const char* query, const vector<int>& int_params);
};
