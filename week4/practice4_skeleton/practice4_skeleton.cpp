// Practice 4. Palindromes and Balance
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 
#include <stack> // built-in library for stacks
using namespace std;
const char PALINDROME = 'P';
const char BALANCE = 'B';

// Return true if str is a palindrome; false otherwise
bool isPalindrome(string& str) {
  // TODO
}

// Return true if brackets are balanced in str; false otherwise
bool balance(string& str) {
  // TODO
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [program] [input] [output]"<<endl;
    exit(1);
  }
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  string input;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int data;
    switch(op)
    {
      case PALINDROME:
        input = line.substr(2);
        if(isPalindrome(input))
          outFile<<"T"<<endl;
        else
          outFile<<"F"<<endl;
        break;
      case BALANCE:
        input = line.substr(2);
        if(balance(input))
          outFile<<"T"<<endl;
        else
          outFile<<"F"<<endl;
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
