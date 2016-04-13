//Generate Parentheses
//Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
//For example, given n = 3, a solution set is:
//"((()))", "(()())", "(())()", "()(())", "()()()"
//

#include<iostream>
#include<vector>
#include<string>
using namespace std;

//()
void generateParenthesisHelper(int n,string& result,int left,int right) {
  if(left + right == 2*n) { 
    cout << result << endl;
    return;
  }
  if(left < n) {
    result.push_back('(');
    left += 1;
    //generateParenthesisHelper(n,result + "(",left+1,right); // don't need to perfomr left -= 1 and update result when strings are immutable like JAVA;
    generateParenthesisHelper(n,result,left,right);
    left -= 1;
    result.pop_back();
  }
  if(left > right) {
    result.push_back(')');
    right  += 1;
    generateParenthesisHelper(n,result,left,right);
    right  -= 1;
    result.pop_back();
  }

}

vector<string> generateParenthesis(int n) {

  vector<string> resultV;
  string result = "";
  int left = 0;
  int right = 0;
  generateParenthesisHelper(n,result,left,right);
  return resultV;
}

int main() {
  generateParenthesis(2);
}
