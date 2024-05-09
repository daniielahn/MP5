#include <iostream>
#include <string>
#include <algorithm> // For copy function

using namespace std;

class Faculty {
public:
    // Constructors
    Faculty() : id(0), name(""), level(""), department(""), adviseeCount(0), adviseeCapacity(2) {
        advisees = new int[adviseeCapacity]; // Allocate memory for initial advisees
    }
    Faculty(int id) : id(id), name(""), level(""), department(""), adviseeCount(0), adviseeCapacity(2) {
        advisees = new int[adviseeCapacity]; // Allocate memory for initial advisees
    }

    Faculty(int id, string name, string level, string department, int *advisees, int count)
        : id(id), name(name), level(level), department(department), adviseeCount(count), adviseeCapacity(count) {
        this->advisees = new int[count]; // Allocate memory for given advisees
        copy(advisees, advisees + count, this->advisees); // Copy advisees
    }

    Faculty(const Faculty &other)
        : id(other.id), name(other.name), level(other.level), department(other.department), 
          adviseeCount(other.adviseeCount), adviseeCapacity(other.adviseeCapacity) {
        advisees = new int[adviseeCapacity]; // Allocate memory for advisees
        copy(other.advisees, other.advisees + adviseeCount, advisees); // Copy advisees
    }

    Faculty &operator=(const Faculty &other) {
        if (this != &other) {
            delete[] advisees; // Free existing memory
            id = other.id;
            name = other.name;
            level = other.level;
            department = other.department;
            adviseeCount = other.adviseeCount;
            adviseeCapacity = other.adviseeCapacity;
            advisees = new int[adviseeCapacity]; // Allocate memory for advisees
            copy(other.advisees, other.advisees + adviseeCount, advisees); // Copy advisees
        }
        return *this;
    }

    ~Faculty() {
        delete[] advisees; // Free allocated memory
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
        // Ensure capacity
        if (adviseeCount == adviseeCapacity) {
            int newCapacity = adviseeCapacity * 2;
            int* newAdvisees = new int[newCapacity];
            std::copy(advisees, advisees + adviseeCount, newAdvisees); // Copy existing advisees
            delete[] advisees; // Free old memory
            advisees = newAdvisees; // Point to new memory
            adviseeCapacity = newCapacity;
        }
        advisees[adviseeCount++] = adviseeID;
    }

    void removeAdvisee(int adviseeID) {
        // Find and remove the advisee
        for (int i = 0; i < adviseeCount; ++i) {
            if (advisees[i] == adviseeID) {
                // Shift elements to the left to fill the gap
                for (int j = i; j < adviseeCount - 1; ++j) {
                    advisees[j] = advisees[j + 1];
                }
                --adviseeCount;
                break;
            }
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
        delete[] faculty.advisees; // Free existing memory
        faculty.adviseeCount = 0;
        faculty.adviseeCapacity = 2;
        faculty.advisees = new int[faculty.adviseeCapacity]; // Allocate memory for initial advisees

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
            faculty.addAdvisee(adviseeID); // Add advisee
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
