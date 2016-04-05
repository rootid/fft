#include<iostream>
#include<string>
#include<vector>
using namespace std;


//(a,b,c) = 3^2,4^2
//a
//b
//c
//a b
//


void generateSubset(string &s,vector<string>& result,vector<int>& inter,int k) {

  int len = s.size();
  if (k == len) {
    string tmp = "";
    for(int i=0;i<k;i++) {
      if(inter[i] == 1) {
        tmp += s[i];
      }
    }
    cout << tmp << endl;
    result.push_back(tmp);
    return;
  }
  inter[k] = 1;
  generateSubset(s,result,inter,k+1);
  inter[k] = 0;
  generateSubset(s,result,inter,k+1);

}

int main () {

  //string s = "abcd";
  string s = "abc";
  vector<string> result;
  int k = 0;
  int len = s.size();
  vector<int> inter(len,0);
  generateSubset(s,result,inter,k);
  cout << "Total subset = " << result.size() << endl;

}
