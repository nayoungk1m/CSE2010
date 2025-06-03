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

vector<int> mergeSort(const vector<int>& arr) {
  if (arr.size() <= 1) return arr;

  int mid = arr.size() / 2;
  vector<int> left(arr.begin(), arr.begin() + mid);
  vector<int> right(arr.begin() + mid, arr.end());

  left = mergeSort(left);
  right = mergeSort(right);

  vector<int> result;
  int i = 0, j = 0;
  
  while (i < left.size() && j < right.size()) {
    if (left[i] > right[j]) {
      result.push_back(left[i]);
      i++;
    } else {
      result.push_back(right[j]);
      j++;
    }
  }
  
  while (i < left.size()) {
    result.push_back(left[i]);
    i++;
  }
  
  while (j < right.size()) {
    result.push_back(right[j]);
    j++;
  }
  
  return result;
}

vector<int> quickSort(vector<int>& arr) {
  if (arr.size() <= 1) return arr;

  int pivot = arr[arr.size() / 2];
  vector<int> left, right, equal;

  for (int i = 0; i < arr.size(); ++i) {
    if (arr[i] > pivot) {
      left.push_back(arr[i]);
    } else if (arr[i] < pivot) {
      right.push_back(arr[i]);
    } else {
      equal.push_back(arr[i]);
    }
  }

  left = quickSort(left);
  right = quickSort(right);

  left.insert(left.end(), equal.begin(), equal.end());
  left.insert(left.end(), right.begin(), right.end());

  return left;
}

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
    vector<int> arr, result;
    int size, k;
    int* tempArray;
    // cout <<line<<endl;
    size = readInput(inFile, iss, arr);
    switch(op)
    {
      case MERGE_SORT:
        // TODO
        result = mergeSort(arr);

        for (int i = 0; i < result.size(); ++i) {
          outFile << result[i] << " ";
        }
        outFile << endl;
        break;
      case QUICK_SORT:
        // TODO
        result = quickSort(arr);
        for (int i = 0; i < result.size(); ++i) {
          outFile << result[i] << " ";
        }
        outFile << endl;
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
