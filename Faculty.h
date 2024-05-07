// File: Faculty.h

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Faculty {
public:
    // Constructors
    Faculty() : id(0), name(""), level(""), department(""), adviseeCount(0), adviseeCapacity(2) {
        advisees = new int[adviseeCapacity];
    }
    Faculty(int id) : id(id), name(""), level(""), department(""), adviseeCount(0), adviseeCapacity(2) {
        advisees = new int[adviseeCapacity];
    }

    Faculty(int id, string name, string level, string department, int *advisees, int count)
        : id(id), name(name), level(level), department(department), adviseeCount(count), adviseeCapacity(count) {
        this->advisees = new int[count];
        copy(advisees, advisees + count, this->advisees);
    }

    Faculty(const Faculty &other)
        : id(other.id), name(other.name), level(other.level), department(other.department), 
          adviseeCount(other.adviseeCount), adviseeCapacity(other.adviseeCapacity) {
        advisees = new int[adviseeCapacity];
        copy(other.advisees, other.advisees + adviseeCount, advisees);
    }

    Faculty &operator=(const Faculty &other) {
        if (this != &other) {
            delete[] advisees;
            id = other.id;
            name = other.name;
            level = other.level;
            department = other.department;
            adviseeCount = other.adviseeCount;
            adviseeCapacity = other.adviseeCapacity;
            advisees = new int[adviseeCapacity];
            copy(other.advisees, other.advisees + adviseeCount, advisees);
        }
        return *this;
    }

    ~Faculty() {
        delete[] advisees;
    }

    // Overloaded Operators
    bool operator==(const Faculty &other) const {
        return id == other.id;
    }

    bool operator<(const Faculty &other) const {
        return id < other.id;
    }

    bool operator>(const Faculty &other) const {
        return id > other.id;
    }

    bool operator<=(const Faculty &other) const {
        return id <= other.id;
    }

    bool operator>=(const Faculty &other) const {
        return id >= other.id;
    }

    // Accessors and Mutators
    int getId() const { return id; }
    string getName() const { return name; }
    string getLevel() const { return level; }
    string getDepartment() const { return department; }
    int *getAdvisees() const { return advisees; }
    int getAdviseeCount() const { return adviseeCount; }

    void setName(string newName) { name = newName; }
    void setLevel(string newLevel) { level = newLevel; }
    void setDepartment(string newDepartment) { department = newDepartment; }

    void addAdvisee(int adviseeID) {
        if (adviseeCount == adviseeCapacity) {
            int newCapacity = adviseeCapacity * 2;
            int *newAdvisees = new int[newCapacity];
            copy(advisees, advisees + adviseeCount, newAdvisees);
            delete[] advisees;
            advisees = newAdvisees;
            adviseeCapacity = newCapacity;
        }
        advisees[adviseeCount++] = adviseeID;
    }

    void removeAdvisee(int adviseeID) {
        int index = -1;
        for (int i = 0; i < adviseeCount; ++i) {
            if (advisees[i] == adviseeID) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            for (int i = index; i < adviseeCount - 1; ++i) {
                advisees[i] = advisees[i + 1];
            }
            --adviseeCount;
        }
    }

    // Input/Output Operators
    friend ostream &operator<<(ostream &out, const Faculty &faculty) {
        out << "ID: " << faculty.id << ", Name: " << faculty.name
            << ", Level: " << faculty.level << ", Department: " << faculty.department
            << ", Advisees: [";
        for (int i = 0; i < faculty.adviseeCount; ++i) {
            out << faculty.advisees[i];
            if (i < faculty.adviseeCount - 1) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }

    friend istream &operator>>(istream &in, Faculty &faculty) {
        delete[] faculty.advisees;
        faculty.adviseeCount = 0;
        faculty.adviseeCapacity = 2;
        faculty.advisees = new int[faculty.adviseeCapacity];

        cout << "Enter ID: ";
        in >> faculty.id;
        in.ignore();
        cout << "Enter name: ";
        getline(in, faculty.name);
        cout << "Enter level: ";
        getline(in, faculty.level);
        cout << "Enter department: ";
        getline(in, faculty.department);
        int numAdvisees;
        cout << "Enter number of advisees: ";
        in >> numAdvisees;
        for (int i = 0; i < numAdvisees; ++i) {
            int adviseeID;
            cout << "Enter advisee ID " << i + 1 << ": ";
            in >> adviseeID;
            faculty.addAdvisee(adviseeID);
        }
        return in;
    }

private:
    int id;
    string name;
    string level;
    string department;
    int *advisees;
    int adviseeCount;
    int adviseeCapacity;
};
