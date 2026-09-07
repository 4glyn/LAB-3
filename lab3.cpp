#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_CAPACITY = 50;

struct Student {
    int id;
    string name;
};

// Function Prototypes
int findStudentById(const Student roster[], int count, int target, int &comparisons);
bool addStudent(Student roster[], int &count, int id, const string &name);
bool removeStudentById(Student roster[], int &count, int target);
bool safeRecordSelect(const Student roster[], int count, int index, Student &outStudent);
void printRoster(const Student roster[], int count);

int main() {
    Student roster[MAX_CAPACITY];
    int currentCount = 0;
    int choice = 0;

    do {
        cout << "\n========================================\n";
        cout << "   NTC CC105: STUDENT ROSTER MANAGER\n";
        cout << "========================================\n";
        cout << "1. Add Student Record\n";
        cout << "2. Search Student by ID\n";
        cout << "3. Remove Student by ID\n";
        cout << "4. Safe Inspect Record by Index\n";
        cout << "5. Display Full Roster\n";
        cout << "6. Exit\n";
        cout << "Enter choice [1-6]: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name;
                cout << "Enter Student ID: ";
                cin >> id;
                cout << "Enter Student Name: ";
                cin.ignore();
                getline(cin, name);

                if (addStudent(roster, currentCount, id, name)) {
                    cout << "SUCCESS: Student record added.\n";
                } else {
                    cout << "ERROR: Record addition failed (Array full or duplicate ID).\n";
                }
                break;
            }
            case 2: {
                int id, comparisons = 0;
                cout << "Enter Student ID to Search: ";
                cin >> id;

                int index = findStudentById(roster, currentCount, id, comparisons);
                if (index != -1) {
                    cout << "FOUND: ID " << roster[index].id << " | Name: " << roster[index].name
                         << " at index " << index << " (Comparisons: " << comparisons << ")\n";
                } else {
                    cout << "NOT FOUND: Student ID does not exist. (Comparisons: " << comparisons << ")\n";
                }
                break;
            }
            case 3: {
                int id;
                cout << "Enter Student ID to Remove: ";
                cin >> id;

                if (removeStudentById(roster, currentCount, id)) {
                    cout << "SUCCESS: Student removed and remaining records shifted.\n";
                } else {
                    cout << "ERROR: Student ID not found or roster is empty.\n";
                }
                break;
            }
            case 4: {
                int index;
                Student targetStudent;
                cout << "Enter Index to Inspect: ";
                cin >> index;

                if (safeRecordSelect(roster, currentCount, index, targetStudent)) {
                    cout << "RECORD AT INDEX " << index << ": ID " << targetStudent.id
                         << " | Name: " << targetStudent.name << "\n";
                } else {
                    cout << "ERROR: Index out of bounds (0 <= index < " << currentCount << ").\n";
                }
                break;
            }
            case 5:
                printRoster(roster, currentCount);
                break;
            case 6:
                cout << "\nExiting system. Memory cleared successfully.\n";
                break;
            default:
                cout << "ERROR: Invalid choice. Please enter a number between 1 and 6.\n";
                break;
        }

    } while (choice != 6);

    return 0;
}

bool addStudent(Student roster[], int &count, int id, const string &name) {
    if (count >= MAX_CAPACITY) {
        return false;
    }

    int unusedComp = 0;
    if (findStudentById(roster, count, id, unusedComp) != -1) {
        return false;
    } // <-- Added missing closing brace here

    roster[count].id = id;
    roster[count].name = name;
    count++;
    return true;
}

int findStudentById(const Student roster[], int count, int target, int &comparisons) {
    comparisons = 0;
    for (int i = 0; i < count; i++) {
        comparisons++;
        if (roster[i].id == target) {
            return i;
        }
    }
    return -1;
}

bool removeStudentById(Student roster[], int &count, int target) {
    int unusedComp = 0;
    int index = findStudentById(roster, count, target, unusedComp);

    if (index == -1) {
        return false;
    }

    for (int i = index; i < count - 1; i++) {
        roster[i] = roster[i + 1];
    }

    count--;
    return true;
}

bool safeRecordSelect(const Student roster[], int count, int index, Student &outStudent) {
    if (index < 0 || index >= count) {
        return false;
    }

    outStudent = roster[index];
    return true;
}

void printRoster(const Student roster[], int count) {
    if (count == 0) {
        cout << "\nRoster is currently empty.\n";
        return;
    }

    cout << "\n--- CURRENT ROSTER (Total: " << count << ") ---\n";
    for (int i = 0; i < count; i++) {
        cout << "[" << i << "] ID: " << roster[i].id << " | Name: " << roster[i].name << "\n";
    }
}
