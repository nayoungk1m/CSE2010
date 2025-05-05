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
    return (i - 1) / 2;
  }
  // Given the index i of element, return the index of that element's left child in the heap
  int left(int i) {
    // TODO
    return 2 * i + 1;
  }
  // Given the index i of element, return the index of that element's right child in the heap
  int right(int i) {
    // TODO
    return 2 * i + 2;
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
  // Added function to print heap
  void printHeap(ofstream&);
};

void MaxHeap::maxHeapify(int i) {
  // TODO
  int l, r, largest;
  l = left(i);
  r = right(i);

  if (l < count && elements[l] > elements[i]) {
    largest = l;
  } else {
    largest = i;
  }
  if (r < count && elements[r] > elements[largest]){
    largest = r;
  }
  if (largest != i) {
    int temp = elements[i];
    elements[i] = elements[largest];
    elements[largest] = temp;
    maxHeapify(largest);
  }
}

// Time complexity: O(logn)
void MaxHeap::insertElement(int x) {
  // TODO
  if (count >= capacity) {
    cerr << "INSERT: heap overflow" << endl;
    exit(1);
  }
  int i = count;
  int p = parent(i);

  while (i > 0 && elements[p] < x) {
    elements[i] = elements[p];
    i = p;
    p = parent(i);
  }

  elements[i] = x;
  count = count + 1;
}

// Time complexity: O(1)
int MaxHeap::maximum() {
  // TODO
  if (count == 0) {
    cerr << "MAX: no elements" << endl;
    exit(1);
  }
  return elements[0];
}

// Time complexity: O(logn)
int MaxHeap::deleteMaximum() {
  // TODO
  if (count == 0) {
    cerr << "DELETE: heap underflow" << endl;
    exit(1);
  }

  int largest = elements[0];
  elements[0] = elements[count - 1];
  count = count - 1;
  maxHeapify(0);
  return largest;
}

void MaxHeap::printHeap(ofstream& outFile) {
  for (int i = 0; i < count; i++) {
    outFile << elements[i] << " ";
  }
  outFile << endl;
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
  int max;
  int del_max;
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
        h.insertElement(key);
        h.printHeap(outFile);
        break;
      case DELETE:
        // TODO. Call the deletion method
        // If the deletion succeeds, write every element in the array into output file.
        del_max = h.deleteMaximum();
        h.printHeap(outFile);
        break;
      case MAXIMUM:
        // TODO. Call the function to get the maximum
        // If getting the maximum succeeds, write the maximum into output file.
        max = h.maximum();
        outFile << max << endl;
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
