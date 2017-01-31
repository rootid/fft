//Length of Last Word
//Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
//If the last word does not exist, return 0.
//Note: A word is defined as a character sequence consists of non-space characters only.
//For example, 
//Given s = "Hello World",
//return 5.


#include "../headers/global.hpp"

//############################################### Good ############################################### 
int lengthOfLastWord(string& s) {
  int len = 0;
  int tail = s.length() - 1;
  while (tail >= 0 && s[tail] == ' ')  {
    tail--;
  }
  while (tail >= 0 && s[tail] != ' ') {
    len++;
    tail--;
  }
 return len;

}

//############################################### Bad  ############################################### 
int lengthOfLastWord(string& s) {

  int len = s.length();
  int lLen = 0;
  int tail = 0;
  if(len == 0) {
    return lLen;
  }
  for(int i=len-1;i>=0;i--) {
    if(s[i] != ' ') {
      tail = i;
      break;
    }
  }
  for(int i=0;i<=tail;i++) {
    if(s[i] == ' ') {
      lLen = 0; 
    } else {
      lLen += 1;
    }
  }

  return lLen;
}

int main() {
    //string s = "hello world";
    string s = "a ";
    //string s = "   ";

    int len = lengthOfLastWord(s);
    cout << s  << "  =  " << len << endl;
}
