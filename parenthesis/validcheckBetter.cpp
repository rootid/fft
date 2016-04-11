//Valid Parentheses
//Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
//The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

#include<iostream>
#include<stack>
using namespace std;

bool isValid(string s) {
  stack<char> paren;
  for (char& c : s) {
      switch (c) {
          case '(': 
          case '{': 
          case '[': paren.push(c); break;
          case ')': if (paren.empty() || paren.top()!='(') return false; else paren.pop(); break;
          case '}': if (paren.empty() || paren.top()!='{') return false; else paren.pop(); break;
          case ']': if (paren.empty() || paren.top()!='[') return false; else paren.pop(); break;
          default: ; // pass
      }
  }
  return paren.empty() ;
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
