#include <iostream>
#include <fstream>
#include <string>
#include "LazyBST.h"
#include "Students.h"
#include "Faculty.h"

using namespace std;

// LazyBST instances to hold Student and Faculty data
LazyBST<Student> studentTable;
LazyBST<Faculty> facultyTable;

void printAllStudents();
void printAllFaculty();
void findStudent();
void findFaculty();
void addStudent();
void deleteStudent();
void addFaculty();
void deleteFaculty();
void changeAdvisor();
void removeAdvisee();
void exitProgram();

int main() {
    int choice;

    // Loop to continuously display the menu and accept user input
    while (true) {
        cout << "Menu Options:" << endl;
        cout << "1. Print all students" << endl;
        cout << "2. Print all faculty" << endl;
        cout << "3. Find student by ID" << endl;
        cout << "4. Find faculty by ID" << endl;
        cout << "5. Add a new student" << endl;
        cout << "6. Delete a student" << endl;
        cout << "7. Add a new faculty member" << endl;
        cout << "8. Delete a faculty member" << endl;
        cout << "9. Change student advisor" << endl;
        cout << "10. Remove advisee" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: printAllStudents(); break;
            case 2: printAllFaculty(); break;
            case 3: findStudent(); break;
            case 4: findFaculty(); break;
            case 5: addStudent(); break;
            case 6: deleteStudent(); break;
            case 7: addFaculty(); break;
            case 8: deleteFaculty(); break;
            case 9: changeAdvisor(); break;
            case 10: removeAdvisee(); break;
            case 11: exitProgram(); return 0;
            default: cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

void printAllStudents() {
    cout << "Student Information:" << endl;
    studentTable.printTree();
}

void printAllFaculty() {
    cout << "Faculty Information:" << endl;
    facultyTable.printTree();
}

void findStudent() {
    int id;
    cout << "Enter student ID: ";
    cin >> id;
    Student student(id);
    if (studentTable.contains(student)) {
        cout << "Student found:" << endl;
        cout << student << endl;
    } else {
        cout << "Student not found." << endl;
    }
}

void findFaculty() {
    int id;
    cout << "Enter faculty ID: ";
    cin >> id;
    Faculty faculty(id);
    if (facultyTable.contains(faculty)) {
        cout << "Faculty found:" << endl;
        cout << faculty << endl;
    } else {
        cout << "Faculty not found." << endl;
    }
}

void addStudent() {
    Student student;
    cout << "Enter student details (ID, Name, Level, Major, GPA, Advisor ID):" << endl;
    cin >> student;
    studentTable.insert(student);
}

void deleteStudent() {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;
    Student student(id);
    studentTable.deleteNode(student);
}

void addFaculty() {
    Faculty faculty;
    cout << "Enter faculty details (ID, Name, Level, Department, Number of Advisees, Advisees):" << endl;
    cin >> faculty;
    facultyTable.insert(faculty);
}

void deleteFaculty() {
    int id;
    cout << "Enter faculty ID to delete: ";
    cin >> id;
    Faculty faculty(id);
    facultyTable.deleteNode(faculty);
}

void changeAdvisor() {
    int studentId, newAdvisorId;
    cout << "Enter student ID: ";
    cin >> studentId;
    cout << "Enter new advisor ID: ";
    cin >> newAdvisorId;

    Student student(studentId), foundStudent;
    Faculty newAdvisor(newAdvisorId), foundFaculty;

    if (studentTable.get(student, foundStudent) && facultyTable.get(newAdvisor, foundFaculty)) {
        foundStudent.setAdvisor(newAdvisorId);
        studentTable.deleteNode(foundStudent);
        studentTable.insert(foundStudent);
        cout << "Advisor changed successfully." << endl;
    } else {
        cout << "Invalid student ID or advisor ID." << endl;
    }
}

void removeAdvisee() {
    int facultyId, adviseeId;
    cout << "Enter faculty ID: ";
    cin >> facultyId;
    cout << "Enter advisee ID: ";
    cin >> adviseeId;

    Faculty faculty(facultyId), foundFaculty;
    Student advisee(adviseeId), foundAdvisee;

    if (facultyTable.get(faculty, foundFaculty) && studentTable.get(advisee, foundAdvisee)) {
        foundFaculty.removeAdvisee(adviseeId);
        facultyTable.deleteNode(foundFaculty);
        facultyTable.insert(foundFaculty);
        cout << "Advisee removed successfully." << endl;
    } else {
        cout << "Invalid faculty ID or advisee ID." << endl;
    }
}


void exitProgram() {
    ofstream outFile("runLog.txt");
    outFile << "Students:" << endl;
    studentTable.printTree(outFile);
    outFile << "Faculty:" << endl;
    facultyTable.printTree(outFile);
    outFile.close();
    cout << "Program terminated. Data saved to runLog.txt" << endl;
}
