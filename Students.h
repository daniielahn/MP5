#include <iostream>
#include <string>

using namespace std;

class Student {
public:
   

    // Default constructor
    Student() : id(0), name(""), level(""), study(""), gpa(0.0), advisorID(0) {}

    // Constructor with id
    Student(int id) : id(id), name(""), level(""), study(""), gpa(0.0), advisorID(0) {}

    // Constructor with all attributes
    Student(int id, string name, string level, string study, double gpa, int advisorID)
        : id(id), name(name), level(level), study(study), gpa(gpa), advisorID(advisorID) {}

    // Overloaded Operators

    // Equality operator
    bool operator==(const Student &other) const {
        return id == other.id;
    }

    // Less than operator
    bool operator<(const Student &other) const {
        return id < other.id;
    }

    // Greater than operator
    bool operator>(const Student &other) const {
        return id > other.id;
    }

    // Less than or equal to operator
    bool operator<=(const Student &other) const {
        return id <= other.id;
    }

    // Greater than or equal to operator
    bool operator>=(const Student &other) const {
        return id >= other.id;
    }

    // Accessors and Mutators

    // Accessor for ID
    int getId() const { return id; }

    // Accessor for Name
    string getName() const { return name; }

    // Accessor for Level
    string getLevel() const { return level; }

    // Accessor for Major
    string getMajor() const { return study; }

    // Accessor for GPA
    double getGPA() const { return gpa; }

    // Accessor for Advisor ID
    int getAdvisor() const { return advisorID; }

    // Mutator for Name
    void setName(string newName) { name = newName; }

    // Mutator for Level
    void setLevel(string newLevel) { level = newLevel; }

    // Mutator for Major
    void setMajor(string newMajor) { study = newMajor; }

    // Mutator for GPA
    void setGPA(double newGPA) { gpa = newGPA; }

    // Mutator for Advisor ID
    void setAdvisor(int newAdvisor) { advisorID = newAdvisor; }

    // Input/Output Operators

    // Output operator to display Student information
    friend ostream &operator<<(ostream &out, const Student &student) {
        out << "ID: " << student.id << ", Name: " << student.name
            << ", Level: " << student.level << ", Major: " << student.study
            << ", GPA: " << student.gpa << ", Advisor ID: " << student.advisorID;
        return out;
    }

    // Input operator to input Student information
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
