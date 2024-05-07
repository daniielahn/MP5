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
    Student foundStudent;

    if (studentTable.get(student, foundStudent)) {
        cout << "Student found:" << endl;
        cout << foundStudent << endl;
    } else {
        cout << "Student not found." << endl;
    }
}

void findFaculty() {
    int id;
    cout << "Enter faculty ID: ";
    cin >> id;
    Faculty faculty(id);
    Faculty foundFaculty;

    if (facultyTable.get(faculty, foundFaculty)) {
        cout << "Faculty found:" << endl;
        cout << foundFaculty << endl;
    } else {
        cout << "Faculty not found." << endl;
    }
}

void addStudent() {
    Student student;
    cout << "Enter student details (ID, Name, Level, Major, GPA, Advisor ID):" << endl;
    cin >> student;

    // Check if the advisor ID exists in the faculty table
    Faculty advisor(student.getAdvisor());
    Faculty foundAdvisor;

    if (facultyTable.get(advisor, foundAdvisor)) {
        // Add student to the tree
        studentTable.insert(student);

        // Add student ID as an advisee to the faculty member
        foundAdvisor.addAdvisee(student.getId());
        facultyTable.deleteNode(advisor);
        facultyTable.insert(foundAdvisor);

        cout << "Student added successfully." << endl;
    } else {
        cout << "Error: Advisor ID does not exist." << endl;
    }
}

void deleteStudent() {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;
    Student student(id);
    Student foundStudent;

    if (studentTable.get(student, foundStudent)) {
        int advisorId = foundStudent.getAdvisor();
        Faculty advisor(advisorId);
        Faculty foundAdvisor;

        // Remove student from advisor's list of advisees if advisor exists
        if (facultyTable.get(advisor, foundAdvisor)) {
            foundAdvisor.removeAdvisee(id);
            facultyTable.deleteNode(advisor);
            facultyTable.insert(foundAdvisor);
        }

        // Delete the student
        studentTable.deleteNode(student);
        cout << "Student deleted successfully." << endl;
    } else {
        cout << "Student not found." << endl;
    }
}


void addFaculty() {
    Faculty faculty;
    cout << "Enter faculty details (ID, Name, Level, Department, Number of Advisees, Advisees):" << endl;
    cin >> faculty;

    // Check if the ID exists in the student table
    if (facultyTable.contains(Faculty(faculty.getId()))) {
        cout << "Error: ID already exists for a faculty member." << endl;
        return;
    }

    facultyTable.insert(faculty);
    cout << "Faculty member added successfully." << endl;
}

void deleteFaculty() {
    int id;
    cout << "Enter faculty ID to delete: ";
    cin >> id;
    Faculty faculty(id);
    Faculty foundFaculty;

    if (facultyTable.get(faculty, foundFaculty)) {
        if (foundFaculty.getAdviseeCount() > 0) {
            int newAdvisorId;
            cout << "Faculty has advisees. Enter new advisor ID for these students: ";
            cin >> newAdvisorId;
            Faculty newAdvisor(newAdvisorId);
            Faculty foundNewAdvisor;

            if (!facultyTable.get(newAdvisor, foundNewAdvisor)) {
                cout << "New advisor ID not found." << endl;
                return;
            }

            // Reassign advisees
            for (int i = 0; i < foundFaculty.getAdviseeCount(); ++i) {
                int adviseeId = foundFaculty.getAdvisees()[i];
                Student student(adviseeId);
                Student foundStudent;

                if (studentTable.get(student, foundStudent)) {
                    foundStudent.setAdvisor(newAdvisorId);
                    studentTable.deleteNode(student);
                    studentTable.insert(foundStudent);
                    foundNewAdvisor.addAdvisee(adviseeId);
                }
            }

            // Update new advisor in the tree
            facultyTable.deleteNode(newAdvisor);
            facultyTable.insert(foundNewAdvisor);
        }

        // Delete the old faculty member
        facultyTable.deleteNode(faculty);
        cout << "Faculty member deleted successfully." << endl;
    } else {
        cout << "Faculty not found." << endl;
    }
}



void changeAdvisor() {
    int studentId, newAdvisorId;
    cout << "Enter student ID: ";
    cin >> studentId;
    cout << "Enter new advisor ID: ";
    cin >> newAdvisorId;

    Student student(studentId);
    Faculty newAdvisor(newAdvisorId);
    Student foundStudent;
    Faculty foundNewAdvisor, foundOldAdvisor;

    if (studentTable.get(student, foundStudent) && facultyTable.get(newAdvisor, foundNewAdvisor)) {
        int oldAdvisorId = foundStudent.getAdvisor();
        if (facultyTable.get(Faculty(oldAdvisorId), foundOldAdvisor)) {
            foundOldAdvisor.removeAdvisee(studentId);
            facultyTable.deleteNode(foundOldAdvisor);
            facultyTable.insert(foundOldAdvisor);
        }
        foundStudent.setAdvisor(newAdvisorId);
        foundNewAdvisor.addAdvisee(studentId);
        studentTable.deleteNode(student);
        studentTable.insert(foundStudent);
        facultyTable.deleteNode(newAdvisor);
        facultyTable.insert(foundNewAdvisor);
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

    Faculty faculty(facultyId);
    Faculty foundFaculty;
    Student advisee(adviseeId);
    Student foundAdvisee;

    if (facultyTable.get(faculty, foundFaculty) && studentTable.get(advisee, foundAdvisee)) {
        foundFaculty.removeAdvisee(adviseeId);
        studentTable.deleteNode(advisee);
        foundAdvisee.setAdvisor(-1); // Or 0, depending on your convention
        studentTable.insert(foundAdvisee);

        // Update faculty table
        facultyTable.deleteNode(faculty);
        facultyTable.insert(foundFaculty);

        cout << "Advisee removed successfully." << endl;
    } else {
        cout << "Invalid faculty ID or advisee ID." << endl;
    }
}




void exitProgram() {
    ofstream outFile("runLog.txt");

    // Log students
    outFile << "Students:" << endl;
    studentTable.printTree(outFile);

    // Log faculty
    outFile << "Faculty:" << endl;
    facultyTable.printTree(outFile);

    outFile.close();
    cout << "Program terminated. Data saved to runLog.txt" << endl;
}

