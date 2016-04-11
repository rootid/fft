//Valid Parentheses
//Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
//The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

#include<iostream>
#include<stack>
using namespace std;

bool isValid(string s) {
  int len = s.size();
  if(len%2 !=0 ) {
    return false;
  }
  stack<char> parStore;
  for(int i=0;i<len;i++) {
    if(s[i] == '(' || s[i] == '{' || s[i] == '[') {
        parStore.push(s[i]);
    } else {
      if(parStore.size() == 0) {
        return false;
      }
      char peekChar = parStore.top();
      int diff = s[i] - peekChar;
      if(diff > 2 || diff < 1) { //[] : are not aligned sequentially , {} : not aligned sequentially
       return false;
      }
      parStore.pop();
    }
  }
  if(parStore.size() == 0) {
    return true;
  }
  return false;
}

int main () {
  int l = '[';
  int r = ']';
  cout << "(" << l << " )=" << r << endl;
  //string s = "()";
  //string s = "(]";
  string s = "([)]";
  if(isValid (s) == true ) {
    cout << " s = " << s << " IS VALID" << endl;
  } else {
    cout << " s = " << s << " IS INVALID" << endl;
  }

}
