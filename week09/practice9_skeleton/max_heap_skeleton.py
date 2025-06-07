# Practice 9. Max Heap
import sys
INSERT = 'I'
DELETE = 'D'
MAXIMUM = 'M'
MAX_CAPACITY = 1000
INT_MIN = -sys.maxsize

class MaxHeap:
  def __init__(self, num=MAX_CAPACITY):
    self.elements = [0] * num
    self.count = 0
    self.capacity = num

  # Given the index i of element, return the index of that element's parent in the heap
  def parent(self, i):
    # TODO
    pass
  
  # Given the index i of element, return the index of that element's left child in the heap
  def left(self, i):
    # TODO
    pass
  
  # Given the index i of element, return the index of that element's right child in the heap
  def right(Self, i):
    # TODO
    pass

  # Insert a given element elem into the heap
  # If the insertion fails, immediately terminate the program with the error message.
  def insertElement(self, elem):
    # TODO
    pass

  # Return the maximum of the heap if it exists
  # Otherwise, terminate program with an error
  def maximum(self):
    # TODO
    pass

  # Delete the maximum from the heap and return the maximum
  # If deletion fails, terminate program with an error
  def deleteMaximum(self):
    # TODO
    pass

if __name__ == "__main__":
  if len(sys.argv) != 3:
    raise Exception("Correct usage: [program] [input] [output]")
  
  h = MaxHeap()
  with open(sys.argv[1], 'r') as inFile:
    lines = inFile.readlines()
  with open(sys.argv[2], 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]
      if op == INSERT:
        if len(words) != 2:
          raise Exception("INSERT: invalid input")
        i = int(words[1])
        # TODO. Call the insertion method
        # If the insertion succeeds, write every element in the array into output file.
      elif op == DELETE:
        # TODO. Call the deletion method
        # If the deletion succeeds, write every element in the array into output file.
      elif op == MAXIMUM:
        # TODO. Call the function to get the maximum
        # If getting the maximum succeeds, write the maximum into output file.
      else:
        raise Exception("Undefined operator")
        

