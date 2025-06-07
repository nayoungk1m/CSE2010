#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
using namespace std;

const char INSERT = 'I';
const char DELETE = 'D';
const char MINIMUM = 'M';
const int MAX_CAPACITY = 1000;

class MinHeap {
  // Define member variables 
  int capacity;
  int count;
  int* elements;
  
  // Given the index i of element, return the index of that element's parent in the heap
  int parent(int i) {
    return (i - 1) / 2;
  }
  
  // Given the index i of element, return the index of that element's left child in the heap
  int left(int i) {
    return 2 * i + 1;
  }
  
  // Given the index i of element, return the index of that element's right child in the heap
  int right(int i) {
    return 2 * i + 2;
  }
  
  void minHeapify(int i);
  
public:
  MinHeap(int num = MAX_CAPACITY) {
    elements = new int[num];
    count = 0;
    capacity = num;
  }
  
  ~MinHeap() {
    delete[] elements;
  }
  
  // Insert a given element elem into the heap
  void insertElement(int);
  
  // Return the minimum of the heap if it exists
  int minimum();
  
  // Delete the minimum from the heap and return the minimum
  int deleteMinimum();
  
  // Added function to print heap
  void printHeap(ofstream&);
  
  bool isEmpty() { return (count == 0); }
};

void MinHeap::minHeapify(int i) {
  int l = left(i), r = right(i), smallest = i;

  if (l < count && elements[l] < elements[i]) {
    smallest = l;
  }
  if (r < count && elements[r] < elements[smallest]) {
    smallest = r;
  }
  
  if (smallest != i) {
    int temp = elements[i];
    elements[i] = elements[smallest];
    elements[smallest] = temp;
    minHeapify(smallest);
  }
}

// Time complexity: O(logn)
void MinHeap::insertElement(int x) {
  if (count >= capacity) {
    cerr << "INSERT: heap overflow" << endl;
    exit(1);
  }
  
  int i = count;
  int p = parent(i);

  while (i > 0 && elements[p] > x) {
    elements[i] = elements[p];
    i = p;
    p = parent(i);
  }

  elements[i] = x;
  count = count + 1;
}

// Time complexity: O(1)
int MinHeap::minimum() {
  if (count == 0) {
    cerr << "MIN: no elements" << endl;
    exit(1);
  }
  return elements[0];
}

// Time complexity: O(logn)
int MinHeap::deleteMinimum() {
  if (count == 0) {
    cerr << "DELETE: heap underflow" << endl;
    exit(1);
  }

  int smallest = elements[0];
  elements[0] = elements[count - 1];
  count = count - 1;
  minHeapify(0);
  return smallest;
}

void MinHeap::printHeap(ofstream& outFile) {
  for (int i = 0; i < count; i++) {
    outFile << elements[i] << " ";
  }
  outFile << endl;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Correct usage: [program] [input] [output]" << endl;
    exit(1);
  }

  MinHeap h;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  int min;
  int del_min;
  
  while (getline(inFile, line)) {
    char op = line[0];
    istringstream iss(line.substr(1));
    int key;
    string name;
    cout << line << endl;
    
    switch (op) {
      case INSERT:
        if (!(iss >> key)) {
          cerr << "INSERT: invalid input" << endl;
          exit(1);
        }
        h.insertElement(key);
        h.printHeap(outFile);
        break;
      case DELETE:
        del_min = h.deleteMinimum();
        h.printHeap(outFile);
        break;
      case MINIMUM:
        min = h.minimum();
        outFile << min << endl;
        break;
      default:
        cerr << "Undefined operator" << endl;
        exit(1);
    }
  }
  
  outFile.close();
  inFile.close();
}
