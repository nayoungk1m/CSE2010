// Practices 6&7. Binary Search Tree Operations
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
const char SEARCH = 'S';
const char INSERT = 'I';
const char DELETE = 'D';
const char INORDER = 'N';
const char PREORDER = 'R';
const char POSTORDER = 'O';

class TreeNode {
public:
  int key;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int k, TreeNode* l=nullptr, TreeNode* r=nullptr) {
    key = k;
    left = l;
    right = r;
  }
};

class BinarySearchTree {
public:
  TreeNode* root;
  BinarySearchTree(): root(nullptr) {}
  ~BinarySearchTree();

  TreeNode* arrayToBST(vector<int>&, int, int);
  // Return true if tree is empty; false otherwise
  bool isEmpty() { return (root == nullptr); }
  TreeNode* findMin();
  TreeNode* findMax();
  TreeNode* search(int, TreeNode*);     // Added function's argument : TreeNode* p
  bool insertNode(int);   // Modified function type from skeleton code: void -> bool
  bool deleteNode(int);   // Modified function type from skeleton code: void -> bool
  void writeInorder(ofstream&, TreeNode*);     // Added function's argument : TreeNode* node
  void writePreorder(ofstream&, TreeNode*);    // Added function's argument : TreeNode* node
  void writePostorder(ofstream&, TreeNode*);   // Added function's argument : TreeNode* node
  void printTree();
private:
  int _getHeight(TreeNode*);
  void _printSpaces(double, TreeNode*);
};

BinarySearchTree::~BinarySearchTree() {
  // Practice 5
  vector<TreeNode*> stack;
  vector<TreeNode*> nodes;
  TreeNode* curr = root;
  TreeNode* prev = nullptr;

  while (curr != nullptr || !stack.empty()) {
    while (curr != nullptr) {
      stack.push_back(curr);
      curr = curr->left;
    }
    curr = stack.back();
    if (curr->right == nullptr || curr->right == prev) {
      stack.pop_back();
      nodes.push_back(curr);
      prev = curr;
      curr = nullptr;
    }
    else {
      curr = curr->right;
    }
  }
  vector<TreeNode*>::iterator it;
    for (it = nodes.begin(); it != nodes.end(); ++it)
    delete *it;
}

// Given a sequence arr of integers, start index l, the end index r, 
// build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
// Return the root node of the tree
// Time complexity: O(n)
TreeNode* BinarySearchTree::arrayToBST(vector<int>& arr, int l, int r) {
  // Practice 5
  if (l > r) return nullptr;

  vector<int>::iterator it = arr.begin();
  int prev = *it;
  for (; it != arr.end(); it++) {   // Time complexity: O(n)
    if (prev > *it) return nullptr;
    prev = *it;
  }

  int mid = (l + r) / 2;
  TreeNode* node = new TreeNode(arr[mid]);
  node->left = arrayToBST(arr, l, mid - 1);
  node->right = arrayToBST(arr, mid + 1, r);
  return node;
}

// Return the node with the minimum value
// Time complexity: O(h) ~ O(logn), h: height
TreeNode* BinarySearchTree::findMin() {
  // Practice 5
  if (isEmpty()) return nullptr;

  TreeNode* p = root;
  if (p->left != nullptr){
    p = p->left;
  }
  return p;
}

// Return the node with the maximum value 
// Time complexity: O(h) ~ O(logn), h: height
TreeNode* BinarySearchTree::findMax() {
  // Practice 5
  if (isEmpty()) return nullptr;
  TreeNode* p = root;
  if (p->right != nullptr) {
    p = p->right;
  }
  return p;
}

// Given a query, search for the node whose key is equal to query.
// If the node exists, return the key
// Otherwise, return nullptr
// Time complexity: O(h) ~ O(logn), h: height
/* Added function's argument : TreeNode* p */
TreeNode* BinarySearchTree::search(int query, TreeNode* p) {
  // TODO. Practice 6
  if (p->key == query) return p;
  else if (query < p->key && p->left != nullptr){
    return search(query, p->left);
  }
  else if (query > p->key && p->right != nullptr) {
    return search(query, p->right);
  }
  else {
    return nullptr;
  }
}
// TreeNode* BinarySearchTree::search(int query) {
//   // TODO. Practice 6
//   TreeNode* p = root;
//   while (p!= nullptr) {
//     int key = p->key;
//     if (query == key){
//       cout << "Found!!!!!!" << endl;    // 디버깅
//       return p;
//     }
//     else if (query > key) {
//       p = p->right;
//     }
//     else {   // query < key
//       p = p->left;
//     }
//   }
//   return nullptr;
// }


// If node with key k alreay exists in the tree, do nothing
// Otherwise, insert a new node with key k 
// Time complexity: O(h) ~ O(logn), h: height
/* Modified function type from skeleton code: void -> bool */
bool BinarySearchTree::insertNode(int k) {
  // TODO. Practice 7
  TreeNode* p = root;
  TreeNode* parent = nullptr;
  while (p != nullptr) {
    parent = p;
    if (k == p->key){    // Already exit!!
      cerr << "INSERT: "<< k << " already exists" << endl;
      return false;
    }
    else if (k > p->key) {
      p = p->right;
    }
    else {      // k < p->key
      p = p->left;
    }
  }

  TreeNode* node = new TreeNode(k);
  if (root == nullptr){
    root = node;
  }
  else if (k > parent->key){
    parent->right = node;
  }
  else {    // k < parent->key
    parent->left = node;
  }
  cout << "INSERT: successfully insert " << k << endl;
  printTree();
  return true;
}

// If deletion fails, immediately terminate the program
// Otherwise, delete the node with key k
// Time complexity: O(h) ~ O(logn), h: height
/* Modified function type from skeleton code: void -> bool */
bool BinarySearchTree::deleteNode(int k) { 
  // TODO. Practice 7
  TreeNode* parent = nullptr;
  TreeNode* p = root;

  while (p != nullptr && p->key != k) {
    if (k > p->key) {
      parent = p;
      p = p->right;
    }
    else {      // k < p->key
      parent = p;
      p = p->left;
    }
  }
  
  if (p == nullptr) {
    cerr << "DELETE: Node not found" << endl;
    return false;
  }

  if (p->left == nullptr && p->right == nullptr) {
    if (p == root) {
      p = nullptr;
    }
    else {
      if (p->key > parent->key) parent->right = nullptr;
      else                      parent->left = nullptr;
    }
    delete p;
  }
  else if (p->right == nullptr || p->left == nullptr) {   // only one child exists
    // determine node's child
    TreeNode* child;
    if (p->right == nullptr) {
      child = p->left;
    }
    else{
      child = p->right;
    }

    if (p == root) {
      root = child;
    }
    if (parent != nullptr) {
      if (p->key > parent->key) parent->right = child;
      else                      parent->left = child;
    }
    delete p;
  }
  else {    // Node has two children
    TreeNode* successorParent = p;
    TreeNode* successor = p->right;
    while (successor->left != nullptr) {
      successorParent = successor;
      successor = successor->left;
    }
    cout << "Successor: " << successor->key << " SuccessorParent: " << successorParent->key << endl;
    if (successor->right != nullptr) {
      successorParent->left = successor->right;
    }
    else{
      successorParent->left = nullptr;
    }
    p->key = successor->key;
    delete successor;
  }
  cout << "DELETE: successfully delete " << k << endl;
  printTree();
  return true;
}

// Given an output file stream, write the keys of all the nodes 
// visited in inorder traversal
// Time complexity: O(n)
/* Added function's argument : TreeNode* node */
void BinarySearchTree::writeInorder(ofstream& outFile, TreeNode* node) {
  // Practice 6
  if (isEmpty() || node == nullptr) return;

  writeInorder(outFile, node->left);
  outFile << node->key << " ";
  writeInorder(outFile, node->right);
}

// Given an output file stream, write the keys of all the nodes 
// visited in preorder traversal
// Time complexity: O(n)
/* Added function's argument : TreeNode* node */
void BinarySearchTree::writePreorder(ofstream& outFile, TreeNode* node) {
  // Practice 6
  if (isEmpty() || node == nullptr) return;

  outFile << node->key << " ";
  writePreorder(outFile, node->left);
  writePreorder(outFile, node->right);
}

// Given an output file stream, write the keys of all the nodes 
// visited in postorder traversal
// Time complexity: O(n)
/* Added function's argument : TreeNode* node */
void BinarySearchTree::writePostorder(ofstream& outFile, TreeNode* node) {
  // Practice 6
  if (isEmpty() || node == nullptr) return;

  writePostorder(outFile, node->left);
  writePostorder(outFile, node->right);
  outFile << node->key << " ";
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
  bool insert_bool;
  bool delete_bool;
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
      case SEARCH:
        if (!(iss >> k)) {
          cerr<<"SEARCH: invalid input"<<endl;
          exit(1);
        }
        // Practice 6. Call the function for search
        found = tree.search(k, tree.root);
        if (found == nullptr) {
          cerr << "Search failed" << endl;
          exit(1);
        }
        else {
          outFile << found->key << endl;
          cout << "SEARCH: Found " << k << endl;
        }

        break;
      case INORDER:
        // Practice 6. Call the function for inorder traversal;
        tree.writeInorder(outFile, tree.root);
        outFile << endl;
        break;
      case PREORDER:
        // Practice 6. Call the function for preorder traversal;
        tree.writePreorder(outFile, tree.root);
        outFile << endl;
        break;
      case POSTORDER:
        // Practice 6. Call the function for postorder traversal;
        tree.writePostorder(outFile, tree.root);
        outFile << endl;
        break;
      case INSERT:
        if (!(iss >> k)) {
          cerr<<"INSERT: invalid input"<<endl;
          exit(1);
        }
        insert_bool = tree.insertNode(k);
        if (insert_bool) {
          outFile << "I " << k << endl;
        }
        // TODO. Practice 7. Call the function for insertion
        break;
      case DELETE:
        if (!(iss >> k)) {
          cerr<<"DELETE: invalid input"<<endl;
          exit(1);
        }
        // TODO. Practice 7. Call the function for deletion
        delete_bool = tree.deleteNode(k);
        if (delete_bool) {
          outFile << "D " << k << endl;
        }
        else{
          exit(1);
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
