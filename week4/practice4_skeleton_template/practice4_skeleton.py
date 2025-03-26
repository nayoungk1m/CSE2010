# Practice 4. Palindromes and Balance
import sys

# Return True if string is a palindrome; False otherwise
def isPalindrome(string):
  # TODO

# Return True if brackets are balanced in string; False otherwise
def balance(string):
  # TODO

if __name__ == "__main__":
  if len(sys.argv) != 3:
    raise Exception("Correct usage: [program] [input] [output]")
  with open(sys.argv[1], 'r') as inFile:
    lines = inFile.readlines()
  with open(sys.argv[2], 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]
      if op == 'P':
        if len(words) != 2:
          raise Exception("PALINDROME: invalid input")
        ret = "T" if isPalindrome(words[1]) else "F"
        outFile.write(ret+"\n")
      elif op == 'B':
        if len(words) != 2:
          raise Exception("BALANCE: invalid input")
        ret = "T" if balance(words[1]) else "F"
        outFile.write(ret+"\n")
      else:
        raise Exception("Undefined operator")

        
