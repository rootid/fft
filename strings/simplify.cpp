//Given an absolute path for a file (Unix-style), simplify it.
//For example,
//path = "/home/", => "/home"
//path = "/a/./b/../../c/", => "/c"
//click to show corner cases.
//Corner Cases:
//Did you consider the case where path = "/../"?
//In this case, you should return "/".
//Another corner case is the path might contain multiple slashes '/' together,
//such as "/home//foo/".
//In this case, you should ignore redundant slashes and return "/home/foo".
#include<iostream>
#include<sstream>
#include<stack>  //Reason not to use the stack is I need to print the path
#include<vector>
using namespace std;
//split equivalent in c++
//
string simplifyPath(string path) {
  stringstream ss(path);
  string strTok;
  string res;
  vector<string> strStk;
  while(getline(ss,strTok,'/')) {
    if(strTok == "" || strTok == ".") {
      continue;
    }
    if(strTok == "..") {
      if(!strStk.empty()) {
        strStk.pop_back();
      }
    } else {
        strStk.push_back(strTok);
    }
  }
 for(auto tmp:strStk) {
    res += "/";
    res += tmp;
  }
  if(res.empty()) {
    return "/";
  }
  return res;
}
int main() {
  string result = simplifyPath("../home/");
  cout << "result " << result << endl;
}
