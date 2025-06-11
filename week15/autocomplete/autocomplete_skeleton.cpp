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
        break;
      case AUTOCOMPLETE:
        if (!(iss >> prefix)) {
          cerr<<"AUTOCOMPLETE: invalid input"<<endl;
          exit(1);
        }
        // TODO. Run autocomplete with "prefix" and write result into "outFile"
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
