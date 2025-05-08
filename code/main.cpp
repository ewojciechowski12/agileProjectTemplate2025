#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

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
    cout << "1) Course 1" << endl;
    cout << "2) Course 2" << endl;
    cout << "3) Course 3" << endl;
    cout << "\n\nEnter -1 To Return to Main Menu" << endl; 
    
    return readUserInput();
}

void displayStudents(int course){
    // TO DO : Display Students from Database instead of harcoded
    cout <<"\nSelect Student" << endl;
    cout << "1) Student 1" << endl;
    cout << "2) Student 2" << endl;
    cout << "3) Student 3" << endl; 
    cout << "\n\nEnter -1 To Return to Main Menu" << endl;
    
    int student = readUserInput();
    cout << "\nYou selected: " << student << endl;
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
