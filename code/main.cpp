#include <iostream>
#include "database.hpp"
using namespace std;

int main()
{
    cout<<"Agile Project"<<endl;

    const char* filename = "attendance_application.db";

    Database db = Database(filename);
    int status = db.take_attendance_one("1/1/25", "P", 1, 1);

    cout << status << endl;

    return 0;
}
