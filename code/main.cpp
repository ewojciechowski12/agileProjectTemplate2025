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
bool is_digits(string& str)
{
    bool toReturn = true;
    for (char ch : str) {
        int v = ch; // ASCII Val converted
        if (!(ch >= 48 && ch <= 57)) {
            //cout << "False" << endl;
            toReturn = false;
        }
        
    }
 
    //cout << "True" << endl;
    return toReturn;
}
int main()
{
    bool endProgram = false;
    cout << "Welcome To The Attendance Assistant\n" << endl;
    printMainMenu();
    //cin a int to select
    int menuSelection = 0;
    string tempSelect = "";
    
    while (endProgram == false){
        cin >> tempSelect;
        while (is_digits(tempSelect) == false){
        cout <<"\nPlease only enter in numbers" << endl;
        printMainMenu();
        cin >> tempSelect;
        }
        menuSelection = stoi(tempSelect);
        switch (menuSelection){
            case 1:
                cout <<"\nTake Attendance" << endl;
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
    }
    return 0;
}
