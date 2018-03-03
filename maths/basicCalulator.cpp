//Implement a basic calculator to evaluate a simple expression string.
//The expression string may contain open ( and closing parentheses ), the plus
//+ or minus sign -, non-negative integers and empty spaces.
//You may assume that the given expression is always valid.
//Some examples:
//"1 + 1" = 2
//" 2-1 + 2 " = 3
//"(1+(4+5+2)-3)+(6+8)" = 23

#include<iostream>
#include<string>
#include<vector>
using namespace std;

//O(n)
//Correctness
int calculate(string s) {

  int result = 0;
  int num1 = 0;
  int num2 = 0;
  vector<char> oprStore;
  for (int i=0;i<s.length();i++) {
    if(s[i] == ' ' or s[i] == '(' or s[i] == ')') {
      continue;
    }
    if(s[i] == '+' or s[i] == '-') {
      oprStore.push_back(s[i]);
    } else {
      num1 = s[i] - '0';
      int oprLen = oprStore.size();
      if(oprLen > 0) {
        if (oprStore[0] == '-' ) {
          result -= num1;
        }
        else {
          result += num1;
        }
        oprStore.pop_back();
      } else {
          result += num1;
      }
      cout << "num1 = "   << num1  << "s_i"  << s[i] << " len = " << oprLen << " | result = " << result<< endl;
    }
  }

  return result;

}


int main() {

  //string st = "1+1";
  string st = "1+(4+5+2) - 3) + (6 + 8)";
  int result = calculate(st);
  cout << "result = " << result  << endl;

}
