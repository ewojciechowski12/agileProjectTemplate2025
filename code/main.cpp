#include <iostream>
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

int main()
{
    cout << "Welcome To The Attendance Assistant\n" << endl;
    printMainMenu();
    //cin a int to select
    int menuSelection = 0;
    string tempSelect = "";
    cin >> tempSelect;
    return 0;
}
