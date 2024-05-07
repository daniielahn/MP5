// File: Students.h

#include <iostream>
#include <string>

using namespace std;

class Student {
public:
    // Constructors
    Student() : id(0), name(""), level(""), study(""), gpa(0.0), advisorID(0) {}
    Student(int id) : id(id), name(""), level(""), study(""), gpa(0.0), advisorID(0) {}
    Student(int id, string name, string level, string study, double gpa, int advisorID)
        : id(id), name(name), level(level), study(study), gpa(gpa), advisorID(advisorID) {}

    // Overloaded Operators
    bool operator==(const Student &other) const {
        return id == other.id;
    }

    bool operator<(const Student &other) const {
        return id < other.id;
    }

    bool operator>(const Student &other) const {
        return id > other.id;
    }

    bool operator<=(const Student &other) const {
        return id <= other.id;
    }

    bool operator>=(const Student &other) const {
        return id >= other.id;
    }

    // Accessors and Mutators
    int getId() const { return id; }
    string getName() const { return name; }
    string getLevel() const { return level; }
    string getMajor() const { return study; }
    double getGPA() const { return gpa; }
    int getAdvisor() const { return advisorID; }

    void setName(string newName) { name = newName; }
    void setLevel(string newLevel) { level = newLevel; }
    void setMajor(string newMajor) { study = newMajor; }
    void setGPA(double newGPA) { gpa = newGPA; }
    void setAdvisor(int newAdvisor) { advisorID = newAdvisor; }

    // Input/Output Operators
    friend ostream &operator<<(ostream &out, const Student &student) {
        out << "ID: " << student.id << ", Name: " << student.name
            << ", Level: " << student.level << ", Major: " << student.study
            << ", GPA: " << student.gpa << ", Advisor ID: " << student.advisorID;
        return out;
    }

    friend istream &operator>>(istream &in, Student &student) {
        cout << "Enter ID: ";
        in >> student.id;
        in.ignore();
        cout << "Enter name: ";
        getline(in, student.name);
        cout << "Enter level: ";
        getline(in, student.level);
        cout << "Enter major: ";
        getline(in, student.study);
        cout << "Enter GPA: ";
        in >> student.gpa;
        cout << "Enter advisor ID: ";
        in >> student.advisorID;
        return in;
    }

private:
    int id;
    string name;
    string level;
    string study;
    double gpa;
    int advisorID;
};
