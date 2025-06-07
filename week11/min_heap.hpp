// min_heap.h
#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <iostream>
#include <fstream>

class MinHeap {
  int capacity;
  int count;
  int* elements;

  int parent(int i);
  int left(int i);
  int right(int i);
  void minHeapify(int i);

public:
  MinHeap(int num = 1000);
  ~MinHeap();

  void insertElement(int x);
  int minimum();
  int deleteMinimum();
  void printHeap(std::ofstream& outFile);
  bool isEmpty();
};

#endif
