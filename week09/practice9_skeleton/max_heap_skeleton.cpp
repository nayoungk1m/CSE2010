// Practice 9. Max Heap
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
using namespace std;
const char INSERT = 'I';
const char DELETE = 'D';
const char MAXIMUM = 'M';
const int MAX_CAPACITY = 1000;

class MaxHeap {
  // Define member variables 
  int capacity;
  int count;
  int* elements;
  
  // Given the index i of element, return the index of that element's parent in the heap
  int parent(int i) {
    // TODO
  }
  // Given the index i of element, return the index of that element's left child in the heap
  int left(int i) {
    // TODO
  }
  // Given the index i of element, return the index of that element's right child in the heap
  int right(int i) {
    // TODO
  }
  void maxHeapify(int i);
public:
  MaxHeap(int num = MAX_CAPACITY) {
    elements = new int[num];
    count = 0;
    capacity = num;
  }
  ~MaxHeap() {
    delete elements;
  }
  
  //Insert a given element elem into the heap
  //If the insertion fails, immediately terminate the program with the error message.
  void insertElement(int);
  // Return the maximum of the heap if it exists
  // Otherwise, terminate program with an error
  int maximum();
  // Delete the maximum from the heap and return the maximum
  // If deletion fails, terminate program with an error
  int deleteMaximum();
};

void MaxHeap::maxHeapify(int i) {
  // TODO
}

void MaxHeap::insertElement(int x) {
  // TODO
}

int MaxHeap::maximum() {
  // TODO
}

int MaxHeap::deleteMaximum() {
  // TODO
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [program] [input] [output]"<<endl;
    exit(1);
  }
  MaxHeap h;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int key;
    string name;
    cout <<line<<endl;
    switch(op)
    {
      case INSERT:
        if (!(iss >> key)) {
          cerr<<"INSERT: invalid input"<<endl;
          exit(1);
        }
        // TODO. Call the insertion method
        // If the insertion succeeds, write every element in the array into output file.
        break;
      case DELETE:
        // TODO. Call the deletion method
        // If the deletion succeeds, write every element in the array into output file.
        break;
      case MAXIMUM:
        // TODO. Call the function to get the maximum
        // If getting the maximum succeeds, write the maximum into output file.
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
