//Valid Parentheses
//Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
//The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

#include<iostream>
#include<stack>
using namespace std;

//######################################### stack + check last element is complement of current ######################################### 
public boolean isValid(String s) {
     int len = s.length();
     if(len%2 == 1) return false;
     Stack<Character> stk = new Stack<>();
     for(int i=0;i<len;i++) {
         if ( s.charAt(i) == '{' || s.charAt(i) == '(' || s.charAt(i) == '[' )
             stk.push(s.charAt(i));
         else {
              if(stk.isEmpty()) return false;
              char lastChar = stk.pop();
              if( (s.charAt(i) == '}' && lastChar != '{' ) || (s.charAt(i) == ']' && lastChar != '[' ) || (s.charAt(i) == ')' && lastChar != '(' )) return false;
             
          }
              
     }
     return stk.size() == 0 ? true : false;
 }

//######################################### stack - Put opposite sign on the stack ######################################### 
public boolean isValid(String s) {
    Stack<Character> stk = new Stack<>();
    for(Character c:s.toCharArray()) {
        switch(c) {
            case '{' : stk.push('}'); break;
            case '(' : stk.push(')'); break;
            case '[' : stk.push(']'); break;
            case '}'  : case ']' : case ')' : 
                if(stk.isEmpty() || stk.pop() != c) return false;
        }
    }
    if(!stk.isEmpty()) return false;
    return true;
}


//######################################### stack ######################################### 
class Solution:
    # @return a boolean
    def isValid(self, s):
        stack = []
        dict = {"]":"[", "}":"{", ")":"("}
        for char in s:
            if char in dict.values():
                stack.append(char)
            elif char in dict.keys():
                if stack == [] or dict[char] != stack.pop():
                    return False
            else:
                return False
        return stack == []

//######################################### stack ######################################### 
class Solution {
public:
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
};

//######################################### map ######################################### 
bool isValid(string s) {
    stack<char> temp;
    map<char, char> m = { {']','['},{')','('},{'}','{'} };
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '[' || s[i] == '(' || s[i] == '{')
            temp.push(s[i]);
        else if (s[i] == ']' || s[i] == ')' || s[i] == '}')
        {
            if (temp.empty()||temp.top() != m[s[i]]) return false;
            else temp.pop();
        }
    }
    return temp.empty();
}

//######################################### check only ascii values ######################################### 
class Solution {
public:
    bool isValid(string s) {
    stack<char> c;
        for (int i = 0; i<s.size(); i++)
        {    
            if (c.empty() || (((c.top() + 0) != (s[i] - 1)) && ((c.top() + 0) != (s[i] - 2))))
                c.push(s[i]);
            else c.pop();
        }
        return c.empty();
    }
};

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
// vim: set sw=2 sts=2 tw=120 et nospell : 
