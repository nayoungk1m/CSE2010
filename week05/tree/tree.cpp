// Practice 5. Binary Search Tree
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
const char BUILD = 'B';
const char FIND_MIN = 'm';
const char FIND_MAX = 'M';

class TreeNode {
public:
  int key;
  TreeNode* left;   // left child
  TreeNode* right;  // right child
};

class BinarySearchTree {
public:
  TreeNode* root;
  BinarySearchTree(): root(nullptr) {}
  ~BinarySearchTree();

  TreeNode* arrayToBST(vector<int>&, int, int);
  TreeNode* findMin();
  TreeNode* findMax();
  void printTree();
private:
  int _getHeight(TreeNode*);
  void _printSpaces(double, TreeNode*);
};

BinarySearchTree::~BinarySearchTree() {
  vector<TreeNode*> stack;
  vector<TreeNode*> nodes;

  TreeNode* curr = root;
  TreeNode* prev = nullptr;

  while(curr != nullptr || !stack.empty()){
    while (curr != nullptr){
      stack.push_back(curr);
      curr = curr->left;
    }
    curr = stack.back();
    if (curr->right != nullptr || curr->right == prev)
  }
}

// Given a sequence arr of integers, start index l, the end index r, 
// build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
// Return the root node of the tree
// time complexity: O(n)
TreeNode* BinarySearchTree::arrayToBST(vector<int>& arr, int l, int r) {
  if (l > r) return nullptr;

  // Time complexity: O(n)
  // check if the array is sorted
  for (int i = l; i < r; i++) {
    if (arr[i] >= arr[i + 1]) return nullptr;
  }

  int mid = (l + r) / 2;
  TreeNode* node = new TreeNode();
  node->key = arr[mid];
  node->left = arrayToBST(arr, l, mid - 1);
  node->right = arrayToBST(arr, mid + 1, r);
  return node;
}

// Return the node with the minimum value 
// time complexity: O(h), h: height
TreeNode* BinarySearchTree::findMin() {
  TreeNode* curr = root;
  if (curr == nullptr) return nullptr;
  while (curr->left != nullptr) {
    curr = curr->left;
  }
  return curr;
}

// Return the node with the maximum value 
// time complexity: O(h), h: height
TreeNode* BinarySearchTree::findMax() {
  TreeNode* curr = root;
  if (curr == nullptr) return nullptr;
  while (curr->right != nullptr) {
    curr = curr->right;
  }
  return curr;
}

int BinarySearchTree::_getHeight(TreeNode* curr) {
  if (curr == nullptr) 
    return 0;
  return 1 + max(_getHeight(curr->left), _getHeight(curr->right));
}

void BinarySearchTree::_printSpaces(double n, TreeNode* curr) {
  for(double i = 0; i < n; ++i) 
    cout<<"  ";
  if (curr == nullptr)
    cout<<" ";
  else
    cout<<curr->key;
}

void BinarySearchTree::printTree() {
  if (root == nullptr)
    return;
  queue<TreeNode*> q;
  q.push(root);
  queue<TreeNode*> temp;
  int cnt = 0;
  int height = _getHeight(root) - 1;
  double nMaxNodes = pow(2, height + 1) - 1;
  while (cnt <= height) {
    TreeNode* curr = q.front();
    q.pop();
    if (temp.empty())
      _printSpaces(nMaxNodes / pow(2, cnt + 1) + height - cnt, curr);
    else
      _printSpaces(nMaxNodes / pow(2, cnt), curr);
    if (curr == nullptr) {
      temp.push(nullptr);
      temp.push(nullptr);
    }
    else {
      temp.push(curr->left);
      temp.push(curr->right);
    }
    if (q.empty()) {
      cout<<endl<<endl;
      q = temp;
      queue<TreeNode*> empty;
      swap(temp, empty);
      ++cnt;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [exe] [input] [output]"<<endl;
    exit(1);
  }
  BinarySearchTree tree;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int k;
    TreeNode* found = nullptr;
    vector<int> data;
    switch(op)
    {
      case BUILD:
        while (iss >> k)
          data.push_back(k);
        tree.root = tree.arrayToBST(data, 0, data.size() - 1);
        if (tree.root) {
          outFile<<BUILD<<endl;
        }
        else {
          cerr<<"BUILD: invalid input"<<endl;
          exit(1);
        }
        tree.printTree();
        break;
      case FIND_MIN:
        found = tree.findMin();
        if (found == nullptr) {
          cerr<<"FindMin failed"<<endl;
          exit(1);
        }
        else {
          outFile<<found->key<<endl;
        }
        break;
      case FIND_MAX:
        found = tree.findMax();
        if (found == nullptr) {
          cerr<<"FindMax failed"<<endl;
          exit(1);
        }
        else {
          outFile<<found->key<<endl;
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
