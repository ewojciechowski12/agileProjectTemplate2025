#include <iostream>
#include "database.hpp"
using namespace std;

int main()
{
    cout<<"Agile Project"<<endl;

    const char* filename = "attendance_application.db";

    Database db = Database(filename);
    const char* temp = "SELECT Students.student_id, Students.first_name, Students.last_name FROM Students";
    vector<vector<string>> data = db.get_students_by_section(1);
    
    for (const auto& row : data) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }

    return 0;
}
