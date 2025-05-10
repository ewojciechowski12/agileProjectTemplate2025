#include "database.hpp"
#include <vector>
#include <string>

using namespace std;

Database::Database(const char* filename) : db(nullptr) {
    int statusOfOpen = sqlite3_open(filename, &db);

    if (statusOfOpen == SQLITE_OK) {
        //cout << "Successfully opened the database" << endl;
    } else {
        //cout << "Problem opening the database: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
        cout << "Database connection closed." << endl;
    }
}

vector<vector<string>> Database::execute_query(sqlite3_stmt* stmt) {
    vector<vector<string>> result;

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

sqlite3_stmt* Database::prepare_and_bind(const char* query, const vector<int>& intParams) {
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return nullptr;
    }

    for (int i = 0; i < intParams.size(); ++i) {
        if (sqlite3_bind_int(stmt, i + 1, intParams[i]) != SQLITE_OK) {
            cout << "Error binding parameter: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            return nullptr;
        }
    }

    return stmt;
}

vector<vector<string>> Database::get_students_by_section(int section_id){
    vector<vector<string>> result; 
    
    const char* query = "SELECT Students.student_id, Students.last_name, Students.first_name "
                    "FROM Students, StudentsInSections " 
                    "WHERE Students.student_id = StudentsInSections.student_id "
                    "AND StudentsInSections.section_id = ?";

    sqlite3_stmt* stmt = prepare_and_bind(query, {section_id});

    if (!stmt) return {};

    return execute_query(stmt);
}


vector<vector<string>> Database::get_semseters(){
    vector<vector<string>> result; 
    
    const char* query = "SELECT Semesters.semester_id, Semesters.name "
                    "FROM Semesters";

    sqlite3_stmt* stmt = prepare_and_bind(query, {});

    if (!stmt) return {};

    return execute_query(stmt);
}


vector<vector<string>> Database::get_courses_sections_by_semseter(int semester_id){
    vector<vector<string>> result; 
    
    const char* query = "SELECT Sections.section_id, Courses.name || ' - ' || Sections.section_number "
                    "FROM Courses, Semesters, Sections " 
                    "WHERE Courses.semester_id = Semesters.semester_id "
                    "AND Sections.course_id = Courses.course_id " 
                    "AND Semesters.semester_id = ?";


    sqlite3_stmt* stmt = prepare_and_bind(query, {semester_id});

    if (!stmt) return {};

    return execute_query(stmt);
}

vector<vector<string>> Database::get_student_name_by_id(int student_id){
    vector<vector<string>> result; 
    
    const char* query = "SELECT last_name, first_name "
                        "FROM Students "
                        "WHERE student_id = ?";


    sqlite3_stmt* stmt = prepare_and_bind(query, {student_id});

    if (!stmt) return {};

    return execute_query(stmt);
}

void Database::print_data(vector<vector<string>> data){
    for (const auto& row : data) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

