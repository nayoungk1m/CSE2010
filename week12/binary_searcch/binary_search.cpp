// Practice 12. Search
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
#include <utility>
using namespace std;
const char BINARY_SEARCH = 'B';
const char PERFECT_SQUARE = 'P';

int binarySearch(vector<int> arr, int x) {
  int start = 0; int end = arr.size() - 1;
  int mid;

  while (start <= end) {
    mid = (start + end) / 2;
    if (arr[mid] == x) return mid;

    if (arr[mid] < x) {
      start = mid + 1;
    }
    else {    // arr[mid] > x
      end = mid - 1;
    }
  }
  return -1;
}

bool perfectSquare(int x) {
  int start = 0; int end = x;
  int mid;
  
  while (start <= end) {
    mid = (start + end) / 2;
    if (mid * mid == x) {
      return true;
    }
    if (mid * mid < x) {
      start = mid + 1;
    }
    else {    // mid * mid > x
      end = mid - 1;
    }
  }
  return false;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [program] [input] [output]"<<endl;
    exit(1);
  }
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(2));
    vector<int> arr;
    int size, x, index;
    bool isSquare;
    switch(op)
    {
      case BINARY_SEARCH:
      {
        // TODO
        if (!(iss >> size >> x)) {
          cerr<<"Error: invalid input"<<endl;
          exit(1);
        }
        
        if (!getline(inFile, line)) {
          cerr << "Error: expected array line after BINARY_SEARCH" << endl;
          exit(1);
        }

        istringstream arrStream(line);
        int k;
        while (arrStream >> k)
          arr.push_back(k);

        if (size != arr.size()) {
          cerr << "BINARY SEARCH: incorrect size" << endl;
          exit(1);
        }

        outFile << "B " << size << " " << x << endl;
        index = binarySearch(arr, x);
        if (index == -1) {
          outFile << "N" << endl;
        }
        else{
          outFile << index << endl;
        }
        break;
      }
      case PERFECT_SQUARE:
        if (!(iss >> x)) {
          cerr<<"Error: invalid input"<<endl;
          exit(1);
        }
        // TODO
        isSquare = perfectSquare(x);
        if (isSquare) {
          outFile << "T" << endl;
        } else{
          outFile << "F" << endl;
        }
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
