#include "database.hpp"


using namespace std;

Database::Database(const char* filename){
    int statusOfOpen = sqlite3_open(filename, &db);

    if (statusOfOpen == SQLITE_OK)
    {
        cout << "Successfully opened the database" << endl;
    }
    else
    {
        cout << "Problem opening the database" << endl;
    }
}


//TODO finish implementing function
string Database::sql_query(const char* query){
    sqlite3_stmt* statement;

    int statusOfPrep = sqlite3_prepare_v2(db, query, -1, &statement, NULL);

    statusOfPrep = sqlite3_prepare_v2(db, "SELECT * FROM Students", -1, &statement, NULL);

        if (statusOfPrep == SQLITE_OK)
        {
            int statusOfStep = sqlite3_step(statement);

            while (statusOfStep == SQLITE_ROW)
            {
                int id = sqlite3_column_int(statement, 0);
                first = (char*)sqlite3_column_text(statement, 1);
                last = (char*)sqlite3_column_text(statement, 2);

                cout << "Student Id: " << id << endl;
                cout << "First Name: " << first << endl;
                cout << "Last Name: " << last << endl;

                statusOfStep = sqlite3_step(myStatement);
            }

            sqlite3_finalize(statement);
        }
        else
        {
            cout << "Problem creating a prepared statement" << endl;
        }

    return "";
}