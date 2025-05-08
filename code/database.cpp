#include "database.hpp"
#include <vector>
#include <string>

using namespace std;

Database::Database(const char* filename) : db(nullptr) {
    int statusOfOpen = sqlite3_open(filename, &db);

    if (statusOfOpen == SQLITE_OK) {
        cout << "Successfully opened the database" << endl;
    } else {
        cout << "Problem opening the database: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
        cout << "Database connection closed." << endl;
    }
}

vector<vector<string>> Database::sql_query(sqlite3_stmt* stmt) {
    vector<vector<string>> result;
    if (!db) {
        cout << "Database connection is not open." << endl;
        return result;
    }

    int statusOfStep = sqlite3_step(stmt);

    int columnCount = sqlite3_column_count(stmt);

    while (statusOfStep == SQLITE_ROW) {
        vector<string> row;

        for (int i = 0; i < columnCount; ++i) {
            string data = (char*)(sqlite3_column_text(stmt, i));
            row.push_back(data);
        }

        result.push_back(row);

        statusOfStep = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    return result;
}

vector<vector<string>> Database::get_students_by_section(int section_id){
    vector<vector<string>> result; 
    
    const char* query = "SELECT Students.student_id, Students.first_name, Students.last_name "
                    "FROM Students, StudentsInSections " 
                    "WHERE Students.student_id = StudentsInSections.student_id "
                    "AND StudentsInSections.section_id = ?";

    cout << query << endl;

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return result;
    }

    if (sqlite3_bind_int(stmt, 1, section_id) != SQLITE_OK) {
        cout << "Error binding parameter: " << sqlite3_errmsg(db) << endl;
        return result;
    }

    result = sql_query(stmt);
    return result;
}