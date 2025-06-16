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

// S = n + (n-1) + ... + 1 = n(n+1)/2
// Time complexity: O(n^2)
void selectionSort(vector<int>& arr, int n) {
  for (int i = 0; i < n-1; ++i) {
    int min = i;
    for (int j = i+1; j < n; ++j) {
      if (arr[min] > arr[j]) {
        min = j;
      }
    }
    // swap arr[min] and arr[i]
    int temp = arr[min];
    arr[min] = arr[i];
    arr[i] = temp;
  }
}

// S = 1 + 2 + ... + n = n(n+1)/2
// Time complexity: O(n^2)
void insertionSort(vector<int>& arr, int n) {
  for (int i = 1; i < n; ++i) {
    int v = arr[i];
    int j = i;
    while (j >= 1 && arr[j-1] > v) {
      arr[j] = arr[j-1];
      --j;
    }
    arr[j] = v;
  }
}

void mergeSort(vector<int>& arr, int* tempArray, int l, int r) {
  // for entire sort, mergeSort(arr, tempArray, 0, arr.size() - 1)
  if (l >= r) return;
  int mid = (l + r) / 2;
  mergeSort(arr, tempArray, l, mid);
  mergeSort(arr, tempArray, mid+1, r);
  merge(arr, tempArray, l, mid+1, r);
}

void merge(vector<int>& arr, int* tempArray, int lPos, int rPos, int rEnd) {
  // merge arr[l..mid] and arr[mid+1..r]
  int lEnd = rPos - 1, tpos = lPos, size = rEnd - lPos + 1;
  while (lPos <= lEnd && rPos <= rEnd) {
    if (arr[lPos] <= arr[rPos]) {
      tempArray[tpos++] = arr[lPos++];
    } else {
      tempArray[tpos++] = arr[rPos++];
    }
  }
  while (lPos <= lEnd) {
    tempArray[tpos++] = arr[lPos++];
  }
  while (rPos <= rEnd) {
    tempArray[tpos++] = arr[rPos++];
  }
  for (int i = 0; i < size; ++i) {
    arr[rEnd - i] = tempArray[rEnd - i];
  }
}

void quickSort(vector<int>& arr, int l, int r) {
  // for entire sort, quickSort(arr, 0, arr.size() - 1)
  if (l >= r) return;
  int pivotIndex = partition(arr, l, r);
  quickSort(arr, l, pivotIndex - 1);
  quickSort(arr, pivotIndex + 1, r);
}

int partition(vector<int>& arr, int low, int high) {
  // pivot as the last element
  int pivot = arr[high];
  int left = low, right = high;
  while (left < right) {
    while (arr[left] < pivot) {
      ++left;
    }
    while (arr[right] >= pivot) {
      --right;
    }
    if (left < right) {
      // swap arr[left] and arr[right]
      swap(arr[left], arr[right]);
    }
  }
  swap(arr[left], arr[high]);
  return left; // return the pivot index
}

int randomPartition(vector<int>& arr, int low, int high) {
  // choose a random pivot
  int randomIndex = low + rand() % (high - low + 1);
  swap(arr[randomIndex], arr[high]); // move pivot to the end
  return partition(arr, low, high);
}

void randomQuickSort(vector<int>& arr, int low, int high) {
  // for entire sort, randomQuickSort(arr, 0, arr.size() - 1)
  if (low >= high) return;
  int pivotIndex = randomPartition(arr, low, high);
  randomQuickSort(arr, low, pivotIndex - 1);
  randomQuickSort(arr, pivotIndex + 1, high);
}

// Counting sort is a non-comparison based sorting algorithm
// Time Complexity: O(n + k) = O(n)
vector<int> countingSort(const vector<int>& arr, int maxVal) {
  vector<int> count(maxVal +1, 0);
  vector<int> sortedArr(arr.size());
  for (int val : arr) {
    count[val]++;
  }
  for (int i = 1; i <= maxVal; ++i) {
    count[i] += count[i - 1]; // cumulative count
  }
  for (int i = arr.size() - 1; i >= 0; --i) {
    sortedArr[count[arr[i]] - 1] = arr[i];
    count[arr[i]]--;
  }
  return sortedArr;
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
