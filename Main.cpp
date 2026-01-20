#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
private:
    int rollno;
    char name[50];
    char course[30];
    float marks;

public:
    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollno;
        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Course: ";
        cin.getline(course, 30);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << setw(10) << rollno
             << setw(20) << name
             << setw(15) << course
             << setw(10) << marks << endl;
    }

    int getRoll() const {
        return rollno;
    }

    void update() {
        cout << "Update Name: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Update Course: ";
        cin.getline(course, 30);

        cout << "Update Marks: ";
        cin >> marks;
    }
};

void AddStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "Student added successfully!\n";
}

void ShowAllStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << setw(10) << "RollNo"
         << setw(20) << "Name"
         << setw(15) << "Course"
         << setw(10) << "Marks" << endl;

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }
    file.close();
}

void SearchStudent() {
    int rollno;
    Student s;
    bool found = false;

    cout << "Enter Roll Number to search: ";
    cin >> rollno;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRoll() == rollno) {
            s.display();
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "Student not found!\n";
}

void UpdateStudent() {
    int rollno;
    Student s;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    cout << "Enter Roll Number to update: ";
    cin >> rollno;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRoll() == rollno) {
            streampos pos = file.tellg() - static_cast<streampos>(sizeof(s));
            file.seekp(pos);

            s.update();
            file.write((char*)&s, sizeof(s));

            cout << "Student updated successfully!\n";
            file.close();
            return;
        }
    }

    cout << "Student not found!\n";
    file.close();
}

void DeleteStudent() {
    int rollno;
    Student s;

    cout << "Enter Roll Number to delete: ";
    cin >> rollno;

    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    bool found = false;

    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.getRoll() != rollno) {
            outFile.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: AddStudent(); break;
            case 2: ShowAllStudents(); break;
            case 3: SearchStudent(); break;
            case 4: UpdateStudent(); break;
            case 5: DeleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
