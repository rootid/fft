//Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
//For "(()", the longest valid parentheses substring is "()", which has length = 2.
//Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

#include<iostream>
#include<stack>
using namespace std;
int longestValidParentheses(string s) {
    int maxLen = 0;
    int localLen = 0;
    stack<int> stack;
    int len = s.size();
    for (int idx=0;idx<len;idx++) {
          if(s[idx] == '(') {
             stack.push(idx);     
          } else {
              if(!stack.empty()) {
                  if( s[stack.top()] == '(' ) {
                      stack.pop();
                  } else {
                      stack.push(idx);
                  }
              } 
              else {
                 stack.push(idx);
              }
          }
    }
    if(stack.empty()) {
        return len;
    } 
    int a = len;
    while(!stack.empty()) {
        int b = stack.top();
        stack.pop();
        maxLen = max(maxLen,a-b-1);
        a = b;
    }
   maxLen = max(maxLen,a); //for case : "())"
    return maxLen;
}

int main() {
  longestValidParentheses("())");
}
