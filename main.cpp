#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void register_student() {
    string student_name;
    
    cout << "Enter a student name:";
    cin.ignore(); // Clear any newline characters in the input buffer
    getline(cin, student_name);

    if (student_name != "Exit" && student_name != "0") {
        ofstream outFile("student_records.txt", ios::app);

        if (outFile.is_open()) {
            outFile << student_name << endl;
            cout << "Student '" << student_name << "' registered successfully!" << endl;
            outFile.close();
        } else {
            cout << "Error opening file for writing" << endl;
        }
    } else {
        cout << "Exiting..." << endl;
        exit(0);
    }
}

void deleteStudent() {
    string student_name;

    cout << "Enter the name of the student to delete: ";
    cin.ignore(); // Clear any newline characters in the input buffer
    getline(cin, student_name);

    ifstream inFile("student_records.txt");
    ofstream tempFile("temp.txt", ios::out);

    if (!inFile.is_open()) {
        cout << "Error opening file for reading" << endl;
        return;
    }

    if (!tempFile.is_open()) {
        cout << "Error opening temporary file for writing" << endl;
        inFile.close();
        return;
    }

    string line;
    bool studentFound = false;

    while (getline(inFile, line)) {
        if (line != student_name) {
            tempFile << line << endl;
        } else {
            studentFound = true;
            cout << "Student '" << student_name << "' deleted successfully!" << endl;
        }
    }

    if (!studentFound) {
        cout << "Student '" << student_name << "' not found." << endl;
    }

    inFile.close();
    tempFile.close();

    remove("student_records.txt");           // Remove the old file
    rename("temp.txt", "student_records.txt");// Rename the temp file to the original name
}

void listStudents() {
    ifstream inFile("student_records.txt");

    if (!inFile.is_open()) {
        cout << "Error opening file for reading" << endl;
        return;
    }

    string student_name;

    cout << "List of Students:" << endl;

    while (getline(inFile, student_name)) {
        cout << student_name << endl;
    }

    inFile.close();
}

void studentManagementMenu(string d_username) {
    cout << "Hello, welcome to the system, " << d_username << endl << endl;
    cout << "1 - Register a Student" << endl;
    cout << "2 - Delete Student" << endl;
    cout << "3 - List Students" << endl;
    cout << "4 - Exit" << endl << endl;

    while (true) {
        string operation;

        cout << "Enter transaction: ";
        cin >> operation;

        if (operation == "1") {
            cout << "Register a student" << endl;
            register_student();
        } else if (operation == "2") {
            cout << "Delete student" << endl;
            deleteStudent();
        } else if (operation == "3") {
            cout << "List students" << endl;
            listStudents(); // Call the listStudents function
        } else if (operation == "4") {
            cout << "Exiting the system..." << endl;
            break;
        } else {
            cout << "Incorrect Operation! Please try again" << endl;
        }
    }
}

void login() {
    string username;
    string password;

    string d_username = "admin";
    string d_password = "1453";

    cout << "Student Management System v.01" << endl << endl;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    while (username != d_username || password != d_password) {
        cout << "Username or Password incorrect! Please try again." << endl;

        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;
    }

    cout << "Entry Successful!" << endl << endl;
}

int main() {
    login();
    studentManagementMenu("admin");
    return 0;
}