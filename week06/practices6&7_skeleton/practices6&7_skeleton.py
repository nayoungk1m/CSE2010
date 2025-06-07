# Practices 6&7. Binary Search Tree Operations
import sys
from collections import deque
BUILD = 'B'
FIND_MIN = 'm'
FIND_MAX = 'M'
SEARCH = 'S'
INSERT = 'I'
DELETE = 'D'
INORDER = 'N'
PREORDER = 'R'
POSTORDER = 'O'

# Node implementation
class TreeNode:
  def __init__(self, k, l=None, r=None):
    self.key = k
    self.left = l
    self.right = r

class BinarySearchTree:
  def __init__(self):
    self.root = None

  # Return True if tree is empty; False otherwise
  def isEmpty(self):
    return self.root == None

  # Given a sequence arr of integers, start index l, the end index r, 
  # build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
  # Return the root node of the tree
  def arrayToBST(self, arr, l, r):
    # Practice 5
    pass

  # Return the node with the minimum value 
  def findMin(self):
    # Practice 5
    pass

  # Return the node with the maximum value 
  def findMax(self):
    # Practice 5
    pass

  def _getHeight(self, curr):
    if not curr:
      return 0
    return 1 + max(self._getHeight(curr.left), self._getHeight(curr.right))

  def _printSpaces(self, n, curr):
    for i in range(int(n)):
      print("  ", end="")
    if not curr:
      print(" ", end="")
    else:
      print(str(curr.key), end="")

  def printTree(self):
    if not self.root:
      return 
    q = deque()
    q.append(self.root)
    temp = deque()
    cnt = 0
    height = self._getHeight(self.root) - 1
    nMaxNodes = 2**(height + 1) - 1
    while cnt <= height:
      curr = q.popleft()
      if len(temp) == 0:
        self._printSpaces(nMaxNodes / (2**(cnt+1)), curr)
      else:
        self._printSpaces(nMaxNodes / (2**cnt), curr)
      if not curr:
        temp.append(None)
        temp.append(None)
      else:
        temp.append(curr.left)
        temp.append(curr.right)
      if len(q) == 0:
        print("\n")
        q = temp
        temp = deque()
        cnt += 1

  # Given a query, search for the node whose key is equal to query.
  # If the node exists, return the key
  # Otherwise, return nullptr  
  def search(self, query):
    # Practice 6
    # TODO
    pass

  # Given an output file, write the keys of all the nodes 
  # visited in inorder traversal
  def writeInorder(self, outFile):
    # Practice 6
    # TODO
    pass

  # Given an output file, write the keys of all the nodes 
  # visited in preorder traversal
  def writePreorder(self, outFile):
    # Practice 6
    # TODO
    pass
  
  # Given an output file, write the keys of all the nodes 
  # visited in postorder traversal
  def writePostorder(self, outFile):
    # Practice 6
    # TODO
    pass
  
  # If node with key k alreay exists in the tree, do nothing
  # Otherwise, insert new node with key k 
  def insertNode(self, k):
    # Practice 7
    # TODO
    pass

  # If deletion fails, immediately terminate the program
  # Otherwise, delete the node with key k
  def deleteNode(self, k):
    # Practice 7
    # TODO
    pass

if __name__ == "__main__":
  if len(sys.argv) != 3:
    raise Exception("Correct usage: [program] [input] [output]")
  
  tree = BinarySearchTree()
  with open(sys.argv[1], 'r') as inFile:
    lines = inFile.readlines()
  with open(sys.argv[2], 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]
      if op == BUILD:
        data = [int(s) for s in words[1:]]
        tree.root = tree.arrayToBST(data, 0, len(data) - 1)
        if tree.root:
          outFile.write(BUILD + "\n")
          tree.printTree()
        else:
          raise Exception("BUILD: invalid input")
      elif op == FIND_MIN:
        found = tree.findMin()
        if not found:
          raise Exception("FindMin failed")
        else:
          outFile.write(str(found.key) + "\n")
      elif op == FIND_MAX:
        found = tree.findMax()
        if not found:
          raise Exception("FindMax failed")
        else:
          outFile.write(str(found.key) + "\n")
      elif op == SEARCH:
        if len(words) != 2:
          raise Exception("SEARCH: invalid input")
        k = int(words[1])
        # Practice 6. Call the function for search
        pass
      elif op == INORDER:
        # Practice 6. Call the function for inorder traversal
        pass
      elif op == PREORDER:
        # Practice 6. Call the function for preorder traversal
        pass
      elif op == POSTORDER:
        # Practice 6. Call the function for postorder traversal
        pass
      elif op == INSERT:
        if len(words) != 2:
          raise Exception("INSERT: invalid input")
        k = int(words[1])
        # TODO. Practice 7. Call the function for insertion
        pass
      elif op == DELETE:
        if len(words) != 2:
          raise Exception("DELETE: invalid input")
        k = int(words[1])
        # TODO. Practice 7. Call the function for deletion
        pass
      else:
        raise Exception("Undefined operator")
        
