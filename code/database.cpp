#include "database.hpp"
#include <vector>
#include <string>

using namespace std;

Database::Database(const char* filename) : db(nullptr) {
    int statusOfOpen = sqlite3_open(filename, &db);

    if (statusOfOpen == SQLITE_OK) {
        cout << "Successfully opened the database" << endl;
    }

    else {
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


vector<vector<string>> Database::execute_select_query(sqlite3_stmt* stmt) {
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


bool Database::execute_insert_query(sqlite3_stmt* stmt) {
    if(sqlite3_step(stmt) != SQLITE_DONE){
        cout << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        return 1;
    }
    
    sqlite3_finalize(stmt);

    return 0;
}


sqlite3_stmt* Database::prepare_and_bind_int(const char* query, const vector<int>& int_params) {
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return nullptr;
    }

    for (int i = 0; i < int_params.size(); ++i) {
        if (sqlite3_bind_int(stmt, i + 1, int_params[i]) != SQLITE_OK) {
            cout << "Error binding parameter: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            return nullptr;
        }
    }

    return stmt;
}


vector<vector<string>> Database::get_students_by_section(int section_id){
    vector<vector<string>> result; 
    
    const char* query = "SELECT Students.student_id, Students.first_name, Students.last_name "
                    "FROM Students, StudentsInSections " 
                    "WHERE Students.student_id = StudentsInSections.student_id "
                    "AND StudentsInSections.section_id = ?";

    sqlite3_stmt* stmt = prepare_and_bind_int(query, {section_id});

    if (!stmt) return {};

    return execute_select_query(stmt);
}

vector<vector<string>> Database::get_students_id_by_section(int section_id){
    vector<vector<string>> result; 
    
    const char* query = "SELECT Students.student_id "
                    "FROM Students, StudentsInSections " 
                    "WHERE Students.student_id = StudentsInSections.student_id "
                    "AND StudentsInSections.section_id = ?";

    sqlite3_stmt* stmt = prepare_and_bind_int(query, {section_id});

    if (!stmt) return {};

    return execute_select_query(stmt);
}


vector<vector<string>> Database::get_semseters(){
    vector<vector<string>> result; 
    
    const char* query = "SELECT Semesters.semester_id, Semesters.name "
                    "FROM Semesters";

    sqlite3_stmt* stmt = prepare_and_bind_int(query, {});

    if (!stmt) return {};

    return execute_select_query(stmt);
}


vector<vector<string>> Database::get_courses_sections_by_semester(int semester_id){
    vector<vector<string>> result; 
    
    const char* query = "SELECT Sections.section_id, Courses.name || ' - ' || Sections.section_number "
                    "FROM Courses, Semesters, Sections " 
                    "WHERE Courses.semester_id = Semesters.semester_id "
                    "AND Sections.course_id = Courses.course_id " 
                    "AND Semesters.semester_id = ?";


    sqlite3_stmt* stmt = prepare_and_bind_int(query, {semester_id});

    if (!stmt) return {};

    return execute_select_query(stmt);
}

bool Database::take_attendance(string date, string attendance_status, int section_id, int student_id){
    const char* query = "INSERT INTO Attendance (date, attendance_status, section_id, student_id) "
                        "VALUES (?, ?, ?, ?)";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    if (sqlite3_bind_text(stmt, 1, date.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, attendance_status.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 3, section_id) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 4, student_id) != SQLITE_OK) {

        cout << "Error binding parameters: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    return execute_insert_query(stmt);
}

bool Database::update_attendance(string date, string attendance_status, int section_id, int student_id){
    cout << "Updating student " << student_id << " to status " << attendance_status << endl;
    const char* query = 
    "UPDATE Attendance SET attendance_status = ? "
    "WHERE date = ? AND section_id = ? AND student_id = ?";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    if (sqlite3_bind_text(stmt, 1, attendance_status.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, date.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 3, section_id) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 4, student_id) != SQLITE_OK) {
        cout << "Error binding parameters: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    return execute_insert_query(stmt);
}

bool Database::mark_all_students_present(string date, int section_id){
    string attendance_status = "P";

    // const char* query = "INSERT INTO Attendance (date, attendance_status, section_id, student_id) "
    //                     "VALUES (?, ?, ?, ?)";

    vector<vector<string>> student_ids = get_students_id_by_section(section_id);

    for (const auto& row : student_ids) {
        for (const auto& id : row) {
            if(take_attendance(date, attendance_status, section_id, stoi(id)) == 1){
                return 1;
            }
            
        }
    }

    return 0;
}


void Database::print_data(vector<vector<string>> data){
    for (const auto& row : data) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}