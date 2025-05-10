#include <iostream>
#include <string>
#include <ctype.h>
#include "database.hpp"

using namespace std;

const char* filename = "attendance_application.db";

Database db = Database(filename);

void printMainMenu(){
    cout <<"Enter the number to select" << endl;
    cout << "1) Take Attendance" << endl;
    cout << "2) Display Attendance" << endl;
    //cout << "3) Display Rate of Attendance on a Day" << endl;
    cout << "3) Show Student Attendance Info" << endl;
    cout << "4) Add Course" << endl;
    cout << "5) Exit" << endl;
}

// Helper function to check if a string is a number
bool is_digits(string& str)
{
    bool toReturn = true;
    for (char ch : str) {
        int v = ch; // ASCII Val converted
        if (!(ch >= 48 && ch <= 57)) {            
            toReturn = false;
        }
        
    } 
    
    return toReturn;
}

// Helper function to read user input
int readUserInput(){
    string menuOption = "";
    cin >> menuOption;

    // -1 is used to return to main menu
    if(menuOption == "-1"){
        return -1;
    }
    while (is_digits(menuOption) == false){
        cout <<"\nPlease only enter in numbers" << endl;
        cin >> menuOption;
    }
    return stoi(menuOption);
}

int displayCourses(){    
    // TO DO : Display Courses from Database instead of harcoded
    cout <<"\nSelect Course" << endl;

    vector<vector<string>> data = db.get_courses_sections_by_semseter(1);
    db.print_data(data);

    cout << "\n\nEnter -1 To Return to Main Menu" << endl; 
    
    return readUserInput();
}

void displayStudents(int course){
    // TO DO : Display Students from Database instead of harcoded
    cout <<"\nSelect Student" << endl;

    vector<vector<string>> data = db.get_students_by_section(course);
    db.print_data(data);
    
    cout << "\n\nEnter -1 To Return to Main Menu" << endl;
    
    int student_id = readUserInput();

    data = db.get_student_name_by_id(student_id);
    cout << "\nYou selected: ";
    db.print_data(data);
}

bool returnToMainMenu(int selection){
    if(selection == -1){
        cout << "\nReturning to Main Menu\n" << endl;
        return true;
    }

    return false;    
}


int main()
{
    bool endProgram = false;
    cout << "Welcome To The Attendance Assistant\n" << endl;
    printMainMenu();

    // Read user input
    int menuSelection = readUserInput();     

    int course = 0;
    
    while (endProgram == false){
        
        switch (menuSelection){
            case 1:                
                course = displayCourses();
                if(returnToMainMenu(course)) break;
                displayStudents(course);
                break;
            case 2:
                cout <<"\nDisplay Attendance" << endl;
                break;
            case 3:
                cout <<"\nShow Student Attendace" << endl;
                break;
            case 4:
                cout <<"\nAdd Corse" << endl;
                break;  
            case 5:
                endProgram = true;
                break;
            default:
            cout <<"\nERR, Please only enter in the numbers to select an option" << endl;
            break;  
        }
        
        printMainMenu();
        menuSelection = readUserInput();
    }
    return 0;
}
