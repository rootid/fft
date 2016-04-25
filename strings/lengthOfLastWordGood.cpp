//Length of Last Word
//Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
//If the last word does not exist, return 0.
//Note: A word is defined as a character sequence consists of non-space characters only.
//For example, 
//Given s = "Hello World",
//return 5.


#include<iostream>
#include<vector>
#include<string>
#include<limits.h>
#include<stdlib.h>

using namespace std;


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

int main() {
    //string s = "hello world";
    string s = "a ";
    //string s = "   ";

    int len = lengthOfLastWord(s);
    cout << s  << "  =  " << len << endl;
}
