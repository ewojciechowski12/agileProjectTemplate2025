#include <iostream>
#include <string>
#include <ctype.h>
#include "database.hpp"

using namespace std;
void printMainMenu();
bool is_digits(string& str);
int readUserInput();
int displayCourses();
void displayStudents(int course);
int displaySemester();
int displayDate();
bool returnToMainMenu(int selection);
void displayAttendance(int course, int date);
void displayStudentAttendacne(int course, int studentId);
int giveStudentId(int course);

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
    // cout << "1) Course 1" << endl;
    // cout << "2) Course 2" << endl;
    // cout << "3) Course 3" << endl;
    vector<vector<string>> courses = db.get_courses_sections_by_semseter(1);
    db.print_data(courses);
    cout << "\n\nEnter -1 To Return to Main Menu" << endl; 
    
    return readUserInput();
}

void displayStudents(int course){
    int stuNumber = 0;

    // TO DO : Display Students from Database instead of harcoded
    cout <<"\nSelect Student" << endl;
    vector<vector<string>> students = db.get_students_by_section(course); 
    db.print_data(students);
    cout << "\n\nEnter -1 To Return to Main Menu" << endl;    

}

// Function to display attendance status
bool returnToMainMenu(int selection){
    if(selection == -1){
        cout << "\nReturning to Main Menu\n" << endl;
        return true;
    }

    return false;    
}
int displaySemester(){
    cout <<"\nSelect Semester" << endl;
    vector<vector<string>> semesters = db.get_semseters();
    db.print_data(semesters);
    cout << "\n\nEnter -1 To Return to Main Menu" << endl;

    return readUserInput();
}

int displayDate(){
    cout <<"\nSelect Date" << endl;
    cout << "1) May 1st" << endl;
    cout << "2) May 2nd" << endl;
    cout << "3) May 3rd" << endl;
    cout << "\n\nEnter -1 To Return to Main Menu" << endl;
    return readUserInput();
}

void displayAttendance(int course, int date){
    cout << "Student 1: P" << endl;
    cout << "Student 2: P" << endl;
    cout << "Student 3: P" << endl;
}
int giveStudentId(int course){
    int courseTemp = 5;
    for (int i = 0; i < courseTemp; i++){
        cout << i+1 << ") Student " << i+1 << endl;
    }
    cout << "\n\nEnter -1 To Return to Main Menu" << endl;
    int studentId = readUserInput();
    return studentId;
}
void displayStudentAttendacne(int course, int studentId){
    int courseTempDates = 30;
    string present = "P";
    for (int i = 0; i < courseTempDates; i++){
        cout << i+1 << " for Student " << studentId << ": " << present << endl;
    }
}

// Function to change attendance value for student
void changeAttendanceValue(){
    int selection = 0;
    // To DO : database instruction to update atendance status
    cout << "\nEnter Student Number to Edit Attendance Status" << endl;
    
    //validate input
    cout << "\nSelect Attendance Status" << endl;
    cout << "1) Late" << endl;
    cout << "2) Absent" << endl;  
    cout << "3) Cancel" << endl; 
    cin >> selection;
    
    
}


int main()
{
    bool endProgram = false;
    cout << "Welcome To The Attendance Assistant\n" << endl;
    printMainMenu();

    // Read user input
    int menuSelection = readUserInput();     

    int course = 0;
    int semester = 0;
    int date = 0;
    int studentId = 0;
    
    while (endProgram == false){
        
        switch (menuSelection){
            case 1:                
                course = displayCourses();
                if(returnToMainMenu(course)) break;
                displayStudents(course);
                changeAttendanceValue();
                break;
            case 2:
                //cout <<"\nDisplay Attendance" << endl;
                semester = displaySemester();
                if(returnToMainMenu(semester)) break;
                course = displayCourses();
                if(returnToMainMenu(course)) break;
                date = displayDate();
                if(returnToMainMenu(date)) break;
                displayAttendance(course, date);
                break;
            case 3:
                cout <<"\nShow Student Attendace" << endl;
                //need semester and course, then select student
                semester = displaySemester();
                if(returnToMainMenu(semester)) break;
                course = displayCourses();
                if(returnToMainMenu(course)) break;
                studentId = giveStudentId(course);
                if (returnToMainMenu(studentId)) break;
                displayStudentAttendacne(course, studentId);
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
        
        if(endProgram) break;

        printMainMenu();
        menuSelection = readUserInput();
    }
}
