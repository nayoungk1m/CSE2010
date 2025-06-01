// Practice 13. Sorting 
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
const char MERGE_SORT = 'M';
const char QUICK_SORT = 'Q';

int readInput(ifstream& inFile, istringstream& iss, vector<int>& input) {
  string line;
  int numInput, val;
  input.clear();
  if (!(iss >> numInput)) {
    cerr<<"Error: invalid number of input"<<endl;
    exit(1);
  }
  if (!getline(inFile, line)) {
    cerr<<"Error: unable to read a line"<<endl;
    exit(1);
  }
  istringstream viss(line);
  for (int i = 0; i < numInput; ++i) {
    if (!(viss >> val)) {
      cerr<<"Error: invalid input value"<<endl;
      exit(1);
    }
    else {
      input.push_back(val);
    }
  }
  return numInput;
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
    int size;
    int* tempArray;
    // cout <<line<<endl;
    size = readInput(inFile, iss, arr);
    switch(op)
    {
      case MERGE_SORT:
        // TODO
        break;
      case QUICK_SORT:
        // TODO
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
