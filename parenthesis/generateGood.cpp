//Generate Parentheses
//Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
//For example, given n = 3, a solution set is:
//"((()))", "(()())", "(())()", "()(())", "()()()"
//

#include<iostream>
#include<vector>
#include<string>
using namespace std;


void helper(vector<string> & res, string str, int left, int right){
    if(left == 0 && right == 0){
      cout << str << endl;
      res.push_back(str);
      return;
    }
    //if(left > 0) helper(res, str + "(", left - 1, right);
    //if(right > left) helper(res, str + ")", left, right - 1);
    if(right > 0) { helper (res, str+")", left, right-1); }
    if(left > 0) { helper (res, str+"(", left-1, right+1); }
}

vector<string> generateParenthesis(int n) {
     vector<string> ret;
     //helper(ret, "", n, n);
     helper(ret, "", n, 0);
     return ret;
}


int main() {
  //generateParenthesis(2);
  generateParenthesis(3);
}
