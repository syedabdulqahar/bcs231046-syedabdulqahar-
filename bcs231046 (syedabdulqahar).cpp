#include <iostream>
#include <string>

using namespace std;

class Student 
{
public:
    Student(int student_id, const string& name) : student_id(student_id), name(name) {}

    
    Student(const Student& other) : student_id(other.student_id), name(other.name) {}

    int getStudentId() const 
    {
        return student_id;
    }

    const string& getName() const
    {
        return name;
    }

private:
    int student_id;
    string name;
};

class Course
{
public:
    Course(const string& course_name, int max_students)
        : course_name(course_name), max_students(max_students), num_students(0), students(new Student* [max_students]) {}

    ~Course()
    {
        delete[] students;
    }

    const string& getCourseName() const {
        return course_name;
    }

    bool addStudent(int student_id, const string& student_name)
    {
        if (num_students < max_students)
        {
            students[num_students] = new Student(student_id, student_name);
            ++num_students;
            return true;
        }
        return false; 
    }

    bool dropStudent(int student_id)
    {
        for (int i = 0; i < num_students; ++i)
        {
            if (students[i]->getStudentId() == student_id)
            {
                delete students[i];
                
                for (int j = i; j < num_students - 1; ++j)
                {
                    students[j] = students[j + 1];
                }
                --num_students;
                return true;
            }
        }
        return false; 
    }

    const Student* const* getStudents() const {
        return students;
    }

    int getNumStudents() const {
        return num_students;
    }

private:
    string course_name;
    int max_students;
    int num_students;
    Student** students;
};

int main() {
    Course course("Math", 3);
    course.addStudent(1, "Alice");
    course.addStudent(2, "Bob");
    course.addStudent(3, "Charlie");

    cout << "Course Name: " << course.getCourseName() << endl;
    const Student* const* students = course.getStudents();
    int num_students = course.getNumStudents();
    for (int i = 0; i < num_students; ++i) {
        cout << "Student ID: " << students[i]->getStudentId() << ", Name: " << students[i]->getName() << endl;
    }

    course.dropStudent(2);

    cout << "After dropping a student:" << endl;
    students = course.getStudents();
    num_students = course.getNumStudents();
    for (int i = 0; i < num_students; ++i) {
        cout << "Student ID: " << students[i]->getStudentId() << ", Name: " << students[i]->getName() << endl;
    }

    return 0;
}
