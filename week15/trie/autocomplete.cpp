// Practice 15. Autocomplete System
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
const char BUILD_TRIE = 'T';
const char AUTOCOMPLETE = 'A';
const int CHAR_SIZE = 128; // Contains ASCII codes for a-z & A-Z.

class TrieNode{
public:
  char data;
  bool endsHere;
  TrieNode* child[CHAR_SIZE];

  TrieNode(): data(0), endsHere(false), child() {}
  TrieNode(char c): data(c), endsHere(false), child() {}

  void insert(const char*);
  bool search(const char*);
  vector<string> autoComplete(string prefix);
};

void TrieNode::insert(const char* word) {
  TrieNode* root = this;
  for (int i = 0; word[i]; ++i) {
    if (!root->child[word[i]]){
      root->child[word[i]] = new TrieNode(word[i]);
    }
    root = root->child[word[i]];
  }

  root->endsHere = true;
}

bool TrieNode::search(const char* word) {
  TrieNode* root = this;
  for (int i = 0; word[i]; ++i) {
    if (!root->child[word[i]])
      return false;
    root = root->child[word[i]];
  }
  return root->endsHere;
}

TrieNode* buildTrie(vector<string> words) {
  TrieNode* trie = new TrieNode();
  for (const auto& word : words) {
    trie->insert(word.c_str());
  }
  return trie;
}

void traverse(TrieNode* node, string current, vector<string>& result) {
  if (node->endsHere) {
    result.push_back(current);
  }

  for (int i = 0; i < CHAR_SIZE; ++i) {
    if (node->child[i]) {
      traverse(node->child[i], current + node->child[i]->data, result);
    }
  }
}

vector<string> TrieNode::autoComplete(string prefix) {
  TrieNode* root = this;
  for (char c : prefix) {
    if (!root->child[c])
      return {};
    root = root->child[c];
  }

  vector<string> result;
  traverse(root, prefix, result);
  return result;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [program] [input] [output]"<<endl;
    exit(1);
  }
  TrieNode* trie;
  vector<string> result;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(2));
    vector<string> words;
    string prefix;
    int n;
    switch(op)
    {
      case BUILD_TRIE: 
        if (!(iss >> n)) {
          cerr<<"BUILD_TRIE: invalid input"<<endl;
          exit(1);
        }
        for (int i = 0; i < n; ++i) {
          if (!getline(inFile, line)) {
            cerr<<"BUILD_TRIE: invalid input"<<endl;
            exit(1);
          }
          words.push_back(line);
        }
        // TODO. Bulid a trie with the stings in vector "words"
        trie = buildTrie(words);
        break;
      case AUTOCOMPLETE:
        if (!(iss >> prefix)) {
          cerr<<"AUTOCOMPLETE: invalid input"<<endl;
          exit(1);
        }
        // TODO. Run autocomplete with "prefix" and write result into "outFile"
        result = trie->autoComplete(prefix);
        for (int i = 0; i != result.size(); ++i) {
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
