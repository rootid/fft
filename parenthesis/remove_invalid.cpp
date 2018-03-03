//Remove Invalid Parentheses
//Remove the minimum number of invalid parentheses in order to make the input
//string valid. Return all possible results.
//Note: The input string may contain letters other than the parentheses ( and
//).
//Examples:
//"()())()" -> ["()()()", "(())()"]
//"(a)())()" -> ["(a)()()", "(a())()"]
//")(" -> [""]

#include<vector>
#include<string>
#include<iostream>
using namespace std;

string getValidParenthesis(string s) {
  int len = s.size();
  int cnt = 0;
  int startIdx = 0;
  string tmp ;
  for(int i=0;i<len;i++) {
    if(s[i] == '(') {
      cnt += 1;
    } else if(s[i] == ')') {
      if(cnt == 0) {
        startIdx = i+1;
        continue;
      }
      cnt -= 1;
      cout << "substr = " <<  s.substr(startIdx,i-startIdx+1) << endl;
      tmp += s.substr(startIdx,i-startIdx+1);
      startIdx = i+1;
    }
  }
  return tmp;
}

vector<string> removeInvalidParentheses(string s) {
  vector<string> result;
  string s1 = getValidParenthesis(s);
  if(s1.size() %2 == 0) {
    cout << s1 << " IS VALID" << endl;
  } else {
    cout << s1 << " IS INVALID" << endl;
  }
  cout << "s1 " << s1 << endl;
  return result;
}

int main () {
 //string s = "()())()" ;
 string s = ")(";
 vector<string>rs = removeInvalidParentheses(s);

}
