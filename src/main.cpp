#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "../inc/mysql.h"
#include "../inc/mysqld_error.h"

using namespace std;

const char *HOST = "127.0.0.1";
const char *USER = "root";
const char *PASS = "YOUR_DB_PASSWORD";
const char *DB = "cms";

// Class declaration
class Department;

class Person;
class Student;
class Professor;

class DivisionManager;
class Division;

class Course;

class Login;

// Exceptions for invalid input
class InvalidInputException : public exception
{
public:
    const char *what() const throw()
    {
        return "Invalid input!";
    }
};

class InvalidEmailException : public exception
{
public:
    const char *what() const throw()
    {
        return "Email not found!";
    }
};

class NotFoundException : public exception
{
public:
    const char *what() const throw()
    {
        return "USN Not found!";
    }
};

class InvalidPasswordException : public exception
{
public:
    const char *what() const throw()
    {
        return "Invalid password! Try again.";
    }
};

// Class definations
class Department
{
public:
    string deptname;

    Department(string deptname)
    {
        this->deptname = deptname;
    }

    void info()
    {
        cout << endl
             << "Department Name: " << this->deptname;
    }
};

class Course
{
public:
    string courseName;
    string courseCode;
    float marks;
    int credits;

    Course(string courseName, string courseCode, float marks, int credits)
    {
        this->courseName = courseName;
        this->courseCode = courseCode;
        this->marks = marks;
        this->credits = credits;
    }

    int creditProduct()
    {
        int grade = 0;
        if(this->marks >= 90){
            grade = 10;
        }
        else if(this->marks >= 80){
            grade = 9;
        }
        else if(this->marks >= 70){
            grade = 8;
        }
        else if(this->marks >= 60){
            grade = 7;
        }
        else if(this->marks >= 50){
            grade = 6;
        }
        else if(this->marks >= 40){
            grade = 5;
        }
        else{
            grade = 0;
        }
        return this->credits * grade;
    }
};

class Person : public Department
{
public:
    string name;
    string phone;
    char gender;
    string email;

    Person(string name, string phone, char gender, string email, string dept) : Department(dept)
    {
        this->name = name;
        this->gender = gender;
        this->phone = phone;
        this->email = email;
    }

    virtual void details() = 0;
};

class Student : public Person
{
public:
    string USN;
    char division;
    float CGPA;
    vector<Course> courses;

    Student(string name, string phone, char gender, string email, string dept, string USN, char c, float cgpa) : Person(name, phone, gender, email, dept)
    {
        this->USN = USN;
        this->division = c;
        this->CGPA = cgpa;
    }

    void details()
    {
        cout << endl
             << left << setw(25) << name << setw(25) << phone << setw(10) << email << setw(15) << this->USN << setw(5) << this->division << setw(10) << this->CGPA << endl;
    }

    void addCourses(vector<Course> courses)
    {
        this->courses = courses;
    }

    void viewMarks()
    {
        cout << endl
             << left << setw(25) << "Course Name" << setw(25) << "Course Code" << setw(10) << "Marks" << endl;
        for (size_t i = 0; i < courses.size(); i++)
        {
            cout << endl
                 << left << setw(25) << courses[i].courseName << setw(25) << courses[i].courseCode << setw(10) << courses[i].marks << endl;
        }
    }

    void updateMarks(string courseCode, float marks)
    {
        for (size_t i = 0; i < courses.size(); i++)
        {
            if (courses[i].courseCode == courseCode)
            {
                courses[i].marks = marks;
            }
        }
    }

    void printSGPA()
    {
        float sum = 0;
        float totalCredits = 0;
        for (size_t i = 0; i < courses.size(); i++)
        {
            sum += courses[i].creditProduct();
            totalCredits += courses[i].credits;
        }
        cout << "SGPA of student " << this->USN << " is " << sum / totalCredits << endl;
    }
};

class Professor : public Person
{
public:
    int profid;

    Professor(string name, string phone, char gender, string email, string dept, int id) : Person(name, phone, gender, email, dept)
    {
        this->profid = id;
    }

    void details()
    {
        cout << endl
             << left << setw(25) << this->profid << setw(25) << name << setw(25) << phone << setw(10) << email;
    }
};

class Division : public Department
{
private:
    int status = 0;
    int bookedBy = 0;

public:
    int classid;
    string classname;
    int capacity;
    vector<Student> students;

    Division(int classid, string classname, int capacity, string dept) : Department(dept)
    {
        this->classid = classid;
        this->classname = classname;
        this->capacity = capacity;
    }

    void details()
    {
        cout << endl
             << left << setw(10) << this->classid << setw(10) << this->classname << setw(5) << this->capacity << setw(5) << this->status << setw(5) << this->bookedBy << endl;
    }

    void addStudents(vector<Student> students)
    {
        this->students = students;
    }

    void viewStudents()
    {
        for (size_t i = 0; i < students.size(); i++)
        {
            students[i].details();
        }
    }

    void printAverageCGPA()
    {
        float sum = 0;
        for (size_t i = 0; i < students.size(); i++)
        {
            sum += students[i].CGPA;
        }
        cout << "Average CGPA of class " << this->classid << " is " << sum / students.size() << endl;
    }

    void setStatus(int status)
    {
        this->status = status;
    }

    void setBookedBy(int bookedBy)
    {
        this->bookedBy = bookedBy;
    }

    int getStatus()
    {
        return this->status;
    }

    int getBookedBy()
    {
        return this->bookedBy;
    }
};

class DivisionManager
{
public:
    vector<Division> divisions;
    vector<Professor> professors;
    vector<Student> students;

    DivisionManager(vector<Division> divisions, vector<Professor> professors, vector<Student> students)
    {
        this->divisions = divisions;
        this->professors = professors;
        this->students = students;
    }

    void viewAllDivisions()
    {
        cout << endl
             << left << setw(10) << "Class ID" << setw(10) << "Class Name" << setw(5) << "Capacity" << setw(5) << "Status" << setw(5) << "Booked By Prof." << endl;
        for (size_t i = 0; i < divisions.size(); i++)
        {
            divisions[i].details();
        }
    }

    void viewDivision(int id)
    {
        cout << endl
             << left << setw(10) << "Class ID" << setw(10) << "Class Name" << setw(5) << "Capacity" << setw(5) << "Status" << setw(5) << "Booked By Prof." << endl;
        for (size_t i = 0; i < divisions.size(); i++)
        {
            if (divisions[i].classid == id)
            {
                divisions[i].details();
            }
        }
    }

    void bookDivision(Division &c, Professor p)
    {
        c.setStatus(1);
        c.setBookedBy(p.profid);
    }

    void markDivisionAsCompleted(Division &c)
    {
        c.setStatus(0);
        c.setBookedBy(0);
    }

    void viewAvailableDivisions()
    {
        cout << endl
             << left << setw(10) << "Class ID" << setw(10) << "Class Name" << setw(5) << "Capacity" << setw(5) << "Status" << setw(5) << "Booked By Prof." << endl;
        for (size_t i = 0; i < divisions.size(); i++)
        {
            int s = divisions[i].getStatus();
            if (s == 0)
            {
                divisions[i].details();
            }
        }
    }

    void viewBookedDivisions()
    {
        cout << endl
             << left << setw(10) << "Class ID" << setw(10) << "Class Name" << setw(5) << "Capacity" << setw(5) << "Status" << setw(5) << "Booked By Prof." << endl;
        for (size_t i = 0; i < divisions.size(); i++)
        {
            int s = divisions[i].getStatus();
            if (s == 1)
            {
                divisions[i].details();
            }
        }
    }

    void viewProfessors()
    {
        for (size_t i = 0; i < professors.size(); i++)
        {
            professors[i].details();
        }
    }

    void viewStudentsOfDivision(int id)
    {
        cout << endl
             << left << setw(25) << "Name" << setw(25) << "Phone" << setw(10) << "Email" << setw(15) << "USN" << setw(5) << "Class" << setw(10) << "CGPA" << endl;
        for (size_t i = 0; i < divisions.size(); i++)
        {
            if (divisions[i].classid == id)
            {
                divisions[i].viewStudents();
            }
        }
    }

    void viewAverageCGPA(int id)
    {
        for (size_t i = 0; i < divisions.size(); i++)
        {
            if (divisions[i].classid == id)
            {
                divisions[i].printAverageCGPA();
            }
        }
    }

    void viewMarksOfStudent(string USN)
    {
        for (size_t i = 0; i < students.size(); i++)
        {
            if (students[i].USN == USN)
            {
                students[i].viewMarks();
            }
        }
    }

    void updateMarksOfStudent(string USN, string courseCode, float marks)
    {
        for (size_t i = 0; i < students.size(); i++)
        {
            if (students[i].USN == USN)
            {
                students[i].updateMarks(courseCode, marks);
            }
        }
    }

    void viewStudentCGPAAndSGPA(string USN)
    {
        for (size_t i = 0; i < students.size(); i++)
        {
            if (students[i].USN == USN)
            {
                students[i].printSGPA();
                cout << endl
                     << "CGPA: " << students[i].CGPA << endl;
            }
        }
    }
};

DivisionManager getManager()
{
    // All Courses

    Course c1("Communication Systems", "19ECEE301", 45, 3);
    Course c2("Digital Signal Processing", "19ECEE302", 35, 4);
    Course c3("CMOS VLSI", "19ECEE303", 75, 5);
    Course c4("OSED", "19ECEE304", 45, 3);
    Course c5("OOPS", "19ECEE305", 95, 3);

    // Courses of students
    vector<Course> courses_s1;
    courses_s1.push_back(c1);
    courses_s1.push_back(c2);
    courses_s1.push_back(c3);
    courses_s1.push_back(c4);
    courses_s1.push_back(c5);

    // All Students
    Student s1("Rahul", "1234567890", 'M', "rahul@gmail.com", "ECE", "01fe21bec211", 'A', 5.6);
    Student s2("John", "1234567890", 'M', "john@gmail.com", "ECE", "01fe21bec311", 'A', 6.6);
    Student s3("Jane", "1234567890", 'F', "jane@gmail.com", "ECE", "01fe21bec411", 'A', 7.6);
    Student s4("Doe", "1234567890", 'M', "doe@gmail.com", "ECE", "01fe21bec215", 'A', 8.6);
    Student s5("Don", "1234567890", 'M', "don@gmail.com", "ECE", "01fe21bec216", 'A', 9.6);
    Student s6("Surya", "1234567890", 'M', "surya@yahoo.com", "ECE", "01fe21bec221", 'A', 10.0);

    s1.addCourses(courses_s1);
    s2.addCourses(courses_s1);
    s3.addCourses(courses_s1);
    s4.addCourses(courses_s1);
    s5.addCourses(courses_s1);
    s6.addCourses(courses_s1);

    // All professors
    Professor p1("Prof. Mahesh", "1234567890", 'M', "mahesh@gmail.com", "ECE", 1);
    Professor p2("Prof. Suresh", "1234567890", 'M', "suresh@gmail.com", "ECE", 2);
    Professor p3("Prof. Ramya", "1234567890", 'F', "ramya@gmail.com", "ECE", 3);

    // Students of different classes
    vector<Student> students_c1;
    students_c1.push_back(s1);
    students_c1.push_back(s2);

    vector<Student> students_c2;
    students_c2.push_back(s3);

    vector<Student> students_c3;
    students_c3.push_back(s4);

    vector<Student> students_c4;
    students_c4.push_back(s5);

    vector<Student> students_c5;
    students_c5.push_back(s6);

    // All Divisions
    Division d1(1, "ECE101", 70, "ECE");
    d1.addStudents(students_c1);

    Division d2(2, "ECE102", 74, "ECE");
    d2.addStudents(students_c2);

    Division d3(3, "ECE103", 30, "ECE");
    d3.addStudents(students_c3);

    Division d4(4, "ECE104", 45, "ECE");
    d4.addStudents(students_c4);

    Division d5(5, "ECE105", 62, "ECE");
    d5.addStudents(students_c5);

    DivisionManager manager({d1, d2, d3, d4, d5}, {p1, p2, p3}, {s1, s2, s3, s4, s5, s6});

    return manager;
}

void managementUI()
{
    int choice;

    DivisionManager manager = getManager();
    cout << "****************************************************************" << endl;
    cout << "\n Welcome to CMS!" << endl;
    cout << "****************************************************************" << endl;
    try
    {
        while (1)
        {
            cout << "Choose what you want to do \n"
                 << endl;
            cout << "****************************************************************" << endl;
            cout << endl
                 << left << setw(25) << "1." << setw(10) << "View All Divisions" << endl;
            cout << endl
                 << left << setw(25) << "2." << setw(10) << "Get divison average CGPA" << endl;
            cout << endl
                 << left << setw(25) << "3." << setw(10) << "Book a division" << endl;
            cout << endl
                 << left << setw(25) << "4." << setw(10) << "Mark division as completed" << endl;
            cout << endl
                 << left << setw(25) << "5." << setw(10) << "View available divisions" << endl;
            cout << endl
                 << left << setw(25) << "6." << setw(10) << "Get division info" << endl;
            cout << endl
                 << left << setw(25) << "7." << setw(10) << "View students of a division" << endl;
            cout << endl
                 << left << setw(25) << "8." << setw(10) << "View booked divisions" << endl;
            cout << endl
                 << left << setw(25) << "9." << setw(10) << "Update marks of a student" << endl;
            cout << endl
                 << left << setw(25) << "10." << setw(10) << "View marks of a student" << endl;
            cout << endl
                 << left << setw(25) << "11." << setw(10) << "View SGPA and CGPA of a student" << endl;
            cout << endl
                 << left << setw(25) << "12." << setw(10) << "Exit" << endl;
            cout << "****************************************************************" << endl;

            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "****************************************************************" << endl;
                cout << "All divisions: " << endl;
                manager.viewAllDivisions();
                cout << "****************************************************************" << endl;
                break;
            case 2:
                cout << "****************************************************************" << endl;
                cout << "Select division (1-5)" << endl;
                int classid;
                cin >> classid;
                if (classid > 5 && classid < 1)
                {
                    throw InvalidInputException();
                    break;
                }
                manager.viewAverageCGPA(classid);
                cout << "****************************************************************" << endl;
                break;
            case 3:
                cout << "****************************************************************" << endl;
                cout << "Select division to book (1-5)" << endl;
                int classid1;
                int profid1;
                cin >> classid1;
                if (classid1 > 5 && classid1 < 1)
                {
                    throw InvalidInputException();
                    break;
                }
                cout << "Select professor to book (1-3)" << endl;
                cin >> profid1;
                if (profid1 > 3 && profid1 < 1)
                {
                    throw InvalidInputException();
                    break;
                }
                manager.bookDivision(manager.divisions[classid1 - 1], manager.professors[profid1 - 1]);
                cout << "Division booked successfully!" << endl;
                cout << "****************************************************************" << endl;
                break;
            case 4:
                cout << "****************************************************************" << endl;
                cout << "Select division to mark as completed (1-5)" << endl;
                int classid2;
                cin >> classid2;
                if (classid2 > 5 && classid2 < 1)
                {
                    throw InvalidInputException();
                    break;
                }
                manager.markDivisionAsCompleted(manager.divisions[classid2 - 1]);
                cout << "****************************************************************" << endl;
                break;
            case 5:
                cout << "****************************************************************" << endl;
                cout << "Available divisions: " << endl;
                manager.viewAvailableDivisions();
                cout << "****************************************************************" << endl;
                break;
            case 6:
                cout << "****************************************************************" << endl;
                cout << "Select division to view (1-5)" << endl;
                int classid3;
                cin >> classid3;
                if (classid3 > 5 && classid3 < 1)
                {
                    throw InvalidInputException();
                    break;
                }
                manager.viewDivision(classid3);
                cout << "****************************************************************" << endl;
                break;
            case 7:
                cout << "****************************************************************" << endl;
                cout << "Select division to view students (1-5)" << endl;
                int classid4;
                cin >> classid4;
                if (classid4 > 5 && classid4 < 1)
                {
                    throw InvalidInputException();
                    break;
                }
                manager.viewStudentsOfDivision(classid4);
                cout << "****************************************************************" << endl;
                break;
            case 8:
                cout << "****************************************************************" << endl;
                cout << "Booked divisions: " << endl;
                manager.viewBookedDivisions();
                cout << "****************************************************************" << endl;
                break;
            case 9:
            {
                cout << "****************************************************************" << endl;
                cout << "Enter USN of student: " << endl;
                string USN;
                cin >> USN;
                cout << "Enter course code: " << endl;
                string courseCode;
                cin >> courseCode;
                cout << "Enter marks: " << endl;
                float marks;
                cin >> marks;
                manager.updateMarksOfStudent(USN, courseCode, marks);
                break;
            }
            case 10:
            {
                cout << "****************************************************************" << endl;
                cout << "Enter USN of student: " << endl;
                string USN1;
                cin >> USN1;
                manager.viewMarksOfStudent(USN1);
                cout << "****************************************************************" << endl;
                break;
            }
            case 11:
            {
                cout << "View SGPA of a student" << endl;
                cout << "Enter USN of student: " << endl;
                string USN2;
                cin >> USN2;
                manager.viewStudentCGPAAndSGPA(USN2);
                break;
            }
            case 12:
                cout << "Exiting..." << endl;
                exit(0);
                break;
            }
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
}

class Login
{
private:
    string id, pass;

public:
    Login() {}

    void setId(string id)
    {
        this->id = id;
    }

    void setPassword(string pass)
    {
        this->pass = pass;
    }

    string getId()
    {
        return this->id;
    }
};

MYSQL *mysqlConnect()
{
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, HOST, USER, PASS, DB, 3306, NULL, 0))
    {
        cout << "Connected to database!" << endl;
        cout << "Please wait..." << endl;
        Sleep(3000);
    }
    else
    {
        cerr << "Connection failed: " << mysql_error(conn) << endl;
    }
    return conn;
}

int main()
{

    MYSQL *conn = mysqlConnect();
    Login admin;

    bool exit_menu = false;
    int choice;
    string admin_email;
    string admin_pass_db;
    string admin_pass;

    if (conn == NULL)
    {
        cerr << "mysql_init() failed!" << endl;
    }

    try
    {
        while (!exit_menu)
        {
            cout << "1. Login as admin" << endl;
            cout << "2. Exit" << endl;

            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                cout << "Enter your email: ";
                cin >> admin_email;
                admin.setId(admin_email);
                cout << endl;
                string email_q = "SELECT email FROM creds WHERE email = '" + admin_email + "'";
                if (mysql_query(conn, email_q.c_str()))
                {
                    cerr << "Error: " << mysql_error(conn) << endl;
                }
                else
                {
                    MYSQL_RES *res = mysql_store_result(conn);
                    MYSQL_ROW row = mysql_fetch_row(res);
                    if (row == NULL)
                    {
                        throw InvalidEmailException();
                        break;
                    }
                }
                cout << "Enter your password: ";
                cin >> admin_pass;
                admin.setPassword(admin_pass);
                cout << endl;
                string pass_q = "SELECT password FROM creds WHERE email = '" + admin_email + "'";
                if (mysql_query(conn, pass_q.c_str()))
                {
                    cerr << "Error: " << mysql_error(conn) << endl;
                }
                else
                {
                    MYSQL_RES *res = mysql_store_result(conn);
                    MYSQL_ROW row = mysql_fetch_row(res);
                    admin_pass_db = row[0];
                    if (admin_pass == admin_pass_db)
                    {
                        cout << "Logged in successfully!" << endl;
                        managementUI();
                    }
                    else
                    {
                        throw InvalidPasswordException();
                        break;
                    }
                }
                break;
            }
            case 2:
                exit(0);
                break;
            }
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
