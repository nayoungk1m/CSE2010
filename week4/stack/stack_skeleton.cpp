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
  /*
  input: string
  output: bool (if palindrome)
  description: push in stack and match with the top
  time complexity: O(n)
  */

  stack<char> s;  // stack to store char of str

  for (int i = 0; i < str.length(); i++) {  // time complexity: O(n)
    s.push(str[i]); // time complexity: O(1)
  }

  for (int i = 0; i < str.length(); i++) {  // time complexity: O(n)
    if (s.top() != str[i]) return false;
    s.pop();  // time complexity: O(1)
  }
  return true;
}

// Return true if brackets are balanced in str; false otherwise
bool balance(string& str) {
  /*
  input: string with brackets
  output: bool (if bracket is balanced)
  description: push brackets in stack and match with the top
  time complexity: O(n)
  */

  stack<char> s;  // stack to store brackets

  for (int i = 0; i < str.length(); i++) {  // time complexity: O(n)
    if (str[i] == '(' || str[i] == '[' || str[i] == '{'){
      s.push(str[i]); // time complexity: O(1)
      
    }
    else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
      if (s.empty()) return false;

      // if top and current match, pop
      if (str[i] == ')' && s.top() == '(') {
        s.pop();  // time complexity: O(1)
      }
      else if (str[i] == ']' && s.top() == '[') {
        s.pop();  // time complexity: O(1)
      }
      else if (str[i] == '}' && s.top() == '{') {
        s.pop();  // time complexity: O(1)
      }
      else {
        return false;
      }
    }
  }
  // if no open bracket left, return true
  if (s.empty()) {
    return true;
  }
  else {
    return false;
  }
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
