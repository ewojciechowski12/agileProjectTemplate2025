#include <iostream>
#include "database.hpp"
using namespace std;

int main()
{
    cout<<"Agile Project"<<endl;

    const char* filename = "attendance_application.db";

    Database db = Database(filename);
    return 0;
}
