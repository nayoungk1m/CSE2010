#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
const char ADD = 'A';
const char DELETE = 'D';
const char FIND = 'F';

class Student {
public:
  // node structure
  int id;
  string name;
  Student* next;
};

class Course {
public:
  Student* head;
  Course() {
    head = nullptr;
  }
  ~Course() {
    // release data
    Student* current = head;
    while (current != nullptr) {
      Student* temp = current;
      current = current->next;
      delete temp;
    }
  }
  
  bool isEmpty() {
    return (head == nullptr);
  }

  bool addStudent(int id, string name);
  bool deleteStudent(int id);
  Student* find(int id);
  void write(ofstream& outFile);
};

bool Course::addStudent(int id, string name) {
  Student* current = head;
  Student* previous = nullptr;

  // find right position to insert
  while (current != nullptr && current->id < id) {
    previous = current;
    current = current->next;
  }

  // check if id already exists
  if (current != nullptr && current->id == id) {
    return false;
  }

  // insert new student
  Student* newStudent = new Student;
  newStudent->id = id;
  newStudent->name = name;
  newStudent->next = current;

  if (previous == nullptr) {
    // insert at head
    head = newStudent;
  }
  else {
    previous->next = newStudent;
  }
  return true;
}

bool Course::deleteStudent(int id) {
  if (isEmpty()) return false;

  Student* current = head;
  Student* previous = nullptr;

  // fine student to delete
  while (current != nullptr && current->id != id) {
    previous = current;
    current = current->next;
  }

  // no student found
  if (current == nullptr) return false;

  if (previous == nullptr) {
    // delete head
    head = current->next;
  }
  else {
    previous->next = current->next;
  }
  delete current;
  return true;
}

Student* Course::find(int id) {
  Student* current = head;
  while (current != nullptr && current->id != id) {
    current = current->next;
  }
  // return nullptr if not found
  return current;
}

void Course::write(ofstream& outFile) {
  if (outFile.is_open()){
    Student* current = head;
    while (current != nullptr) {
      outFile << current->id << " " << current->name << " ";
      current = current->next;
    }
    outFile << endl;
  }
  else {
    cerr << "Unable to open file" << endl;
    exit(1);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [program] [input] [output]"<<endl;
    exit(1);
  }
  Course course;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int id;
    string name;
    Student* found = nullptr;
    cout <<line<<endl;
    switch(op)
    {
      case ADD:
        if (!(iss >> id >> name)) {
          cerr<<"ADD: invalid input"<<endl;
          exit(1);
        }
        if (course.addStudent(id, name))
          course.write(outFile);
        else
          outFile<<"Addition failed"<<endl;
        break;
      case DELETE:
        if (!(iss >> id)) {
          cerr<<"DELETE: invalid input"<<endl;
          exit(1);
        }
        if (course.deleteStudent(id))
          course.write(outFile);
        else
          outFile<<"Deletion failed"<<endl;
        break;
      case FIND:
        if (!(iss >> id)) {
          cerr<<"FIND: invalid input"<<endl;
          exit(1);
        }
        found = course.find(id);
        if (found == nullptr)
          outFile<<"Search failed"<<endl;
        else
          outFile<<found->id<<" "<<found->name<<endl;
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
