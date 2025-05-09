#include <iostream>
#include "database.hpp"
using namespace std;

int main()
{
    cout<<"Agile Project"<<endl;

    const char* filename = "attendance_application.db";

    Database db = Database(filename);
    vector<vector<string>> data = db.get_courses_sections_by_semseter(1);
    
    for (const auto& row : data) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }

    return 0;
}
