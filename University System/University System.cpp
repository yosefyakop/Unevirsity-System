// University Management System - Data structure project
#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

struct StudentNode {
    int studentID;
    string studentName;
    string studentEmail;
    string studentPhone;
    string studentAddress;
    string studentPassword;
    StudentNode* nextStudent;
};

class StudentLinkedList {
private:
    StudentNode* headStudent;

public:
    StudentLinkedList() : headStudent(nullptr) {}

    void addStudent(int id, string name, string email, string phone, string address, string password) {
        StudentNode* newStudent = new StudentNode{id, name, email, phone, address, password, nullptr};
        if (!headStudent) {
            headStudent = newStudent;
        } else {
            StudentNode* tempStudent = headStudent;
            while (tempStudent->nextStudent) tempStudent = tempStudent->nextStudent;
            tempStudent->nextStudent = newStudent;
        }
    }

    void removeStudent(int id) {
        if (!headStudent) return;
        if (headStudent->studentID == id) {
            StudentNode* tempStudent = headStudent;
            headStudent = headStudent->nextStudent;
            delete tempStudent;
            return;
        }

        StudentNode* tempStudent = headStudent;
        while (tempStudent->nextStudent && tempStudent->nextStudent->studentID != id) tempStudent = tempStudent->nextStudent;
        if (tempStudent->nextStudent) {
            StudentNode* studentToDelete = tempStudent->nextStudent;
            tempStudent->nextStudent = tempStudent->nextStudent->nextStudent;
            delete studentToDelete;
        }
    }

    void displayStudents() {
        StudentNode* tempStudent = headStudent;
        while (tempStudent) {
            cout << "Student ID: " << tempStudent->studentID << ", Name: " << tempStudent->studentName 
                 << ", Email: " << tempStudent->studentEmail << endl;
            tempStudent = tempStudent->nextStudent;
        }
    }
};

struct CourseNode {
    int courseID;
    string courseName;
    int courseCredits;
    string courseInstructor;
    CourseNode* leftCourse;
    CourseNode* rightCourse;
};

class CourseBinarySearchTree {
private:
    CourseNode* rootCourse;

    CourseNode* addCourse(CourseNode* currentCourse, int id, string name, int credits, string instructor) {
        if (!currentCourse) return new CourseNode{id, name, credits, instructor, nullptr, nullptr};
        if (id < currentCourse->courseID)
            currentCourse->leftCourse = addCourse(currentCourse->leftCourse, id, name, credits, instructor);
        else if (id > currentCourse->courseID)
            currentCourse->rightCourse = addCourse(currentCourse->rightCourse, id, name, credits, instructor);
        return currentCourse;
    }

    void inOrderDisplay(CourseNode* currentCourse) {
        if (!currentCourse) return;
        inOrderDisplay(currentCourse->leftCourse);
        cout << "Course ID: " << currentCourse->courseID << ", Name: " << currentCourse->courseName << endl;
        inOrderDisplay(currentCourse->rightCourse);
    }

public:
    CourseBinarySearchTree() : rootCourse(nullptr) {}

    void addNewCourse(int id, string name, int credits, string instructor) {
        rootCourse = addCourse(rootCourse, id, name, credits, instructor);
    }

    void displayAllCourses() {
        inOrderDisplay(rootCourse);
    }
};

struct EnrollmentNode {
    int enrolledStudentID;
    int enrolledCourseID;
    EnrollmentNode* nextEnrollment;
    EnrollmentNode* prevEnrollment;
};

class EnrollmentDoubleLinkedList {
private:
    EnrollmentNode* headEnrollment;

public:
    EnrollmentDoubleLinkedList() : headEnrollment(nullptr) {}

    void addEnrollment(int studentID, int courseID) {
        EnrollmentNode* newEnrollment = new EnrollmentNode{studentID, courseID, nullptr, nullptr};
        if (!headEnrollment) {
            headEnrollment = newEnrollment;
        } else {
            newEnrollment->nextEnrollment = headEnrollment;
            headEnrollment->prevEnrollment = newEnrollment;
            headEnrollment = newEnrollment;
        }
    }

    void viewEnrollmentHistory(int studentID) {
        EnrollmentNode* tempEnrollment = headEnrollment;
        while (tempEnrollment) {
            if (tempEnrollment->enrolledStudentID == studentID)
                cout << "Student ID: " << tempEnrollment->enrolledStudentID 
                     << ", Course ID: " << tempEnrollment->enrolledCourseID << endl;
            tempEnrollment = tempEnrollment->nextEnrollment;
        }
    }
};

class PrerequisiteStackManager {
private:
    stack<int> prerequisiteStack;

public:
    void addPrerequisiteCourse(int courseID) {
        prerequisiteStack.push(courseID);
    }

    void validatePrerequisites(int studentID) {
        if (prerequisiteStack.empty()) {
            cout << "Student ID: " << studentID << " has completed all prerequisites!" << endl;
            return;
        }

        cout << "Remaining prerequisites for Student ID: " << studentID << " are:" << endl;
        while (!prerequisiteStack.empty()) {
            cout << "Course ID: " << prerequisiteStack.top() << endl;
            prerequisiteStack.pop();
        }
    }
};

class WaitlistQueueManager {
private:
    queue<int> waitlistQueue;

public:
    void addToWaitlist(int studentID) {
        waitlistQueue.push(studentID);
    }

    void processWaitlist() {
        if (waitlistQueue.empty()) {
            cout << "Waitlist is empty!" << endl;
            return;
        }
        cout << "Student ID: " << waitlistQueue.front() << " has been enrolled!" << endl;
        waitlistQueue.pop();
    }
};

int main() {
    StudentLinkedList studentList;
    CourseBinarySearchTree courseTree;
    EnrollmentDoubleLinkedList enrollmentList;
    PrerequisiteStackManager prereqStack;
    WaitlistQueueManager waitlistManager;

    int choice;
    do {
        cout << "\nUniversity Management System\n";
        cout << "1. Add New Student\n";
        cout << "2. Remove a Student\n";
        cout << "3. Display All Students\n";
        cout << "4. Add New Course\n";
        cout << "5. Display All Courses\n";
        cout << "6. Add Course Enrollment\n";
        cout << "7. View Enrollment History\n";
        cout << "8. Add Course Prerequisite\n";
        cout << "9. Validate Course Prerequisites\n";
        cout << "10. Add to Course Waitlist\n";
        cout << "11. Process Course Waitlist\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            string name, email, phone, address, password;
            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Email: ";
            getline(cin, email);
            cout << "Enter Phone: ";
            getline(cin, phone);
            cout << "Enter Address: ";
            getline(cin, address);
            cout << "Enter Password: ";
            getline(cin, password);
            studentList.addStudent(id, name, email, phone, address, password);
            break;
        }
        case 2: {
            int id;
            cout << "Enter Student ID to Remove: ";
            cin >> id;
            studentList.removeStudent(id);
            break;
        }
        case 3:
            studentList.displayStudents();
            break;
        case 4: {
            int id, credits;
            string name, instructor;
            cout << "Enter Course ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Enter Course Credits: ";
            cin >> credits;
            cin.ignore();
            cout << "Enter Course Instructor: ";
            getline(cin, instructor);
            courseTree.addNewCourse(id, name, credits, instructor);
            break;
        }
        case 5:
            courseTree.displayAllCourses();
            break;
        case 6: {
            int studentID, courseID;
            cout << "Enter Student ID: ";
            cin >> studentID;
            cout << "Enter Course ID: ";
            cin >> courseID;
            enrollmentList.addEnrollment(studentID, courseID);
            break;
        }
        case 7: {
            int studentID;
            cout << "Enter Student ID to View History: ";
            cin >> studentID;
            enrollmentList.viewEnrollmentHistory(studentID);
            break;
        }
        case 8: {
            int courseID;
            cout << "Enter Prerequisite Course ID: ";
            cin >> courseID;
            prereqStack.addPrerequisiteCourse(courseID);
            break;
        }
        case 9: {
            int studentID;
            cout << "Enter Student ID for Prerequisite Validation: ";
            cin >> studentID;
            prereqStack.validatePrerequisites(studentID);
            break;
        }
        case 10: {
            int studentID;
            cout << "Enter Student ID to Add to Waitlist: ";
            cin >> studentID;
            waitlistManager.addToWaitlist(studentID);
            break;
        }
        case 11:
            waitlistManager.processWaitlist();
            break;
        case 0:
            cout << "Exiting Program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid Choice. Please Try Again." << endl;
        }
    } while (choice != 0);

    return 0;
}
