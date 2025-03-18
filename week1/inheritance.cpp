#include <iostream>
using namespace std;

class Person {
    int id;

public:
    void aboutMe() {
        cout << "I am a person." << endl;
    }
};

class Student : public Person {
public:
    void aboutMe() {
        cout << "I am a student." << endl;
    }
};

int main() {
    // Student p = Student();  // Student object
    // p.aboutMe();
    // return 0;

    // Student *p = Student();     // 객체를 포인터에 저장할 수 없음 (객체는 스택에, 포인터는 힙에 저장)
    Student *p = new Student();     // 객체를 힙에 저장
    p->aboutMe();
    delete p;
    return 0;
}