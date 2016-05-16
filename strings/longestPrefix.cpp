//Longest Common Prefix
//Write a function to find the longest common prefix string amongst an array of strings.

#include<iostream>
#include<string>
#include<vector>
using namespace std;

string longestCommonPrefix(vector<string>& strs) {
  int tLen = strs.size();
  int idx =0;
  bool found = true;
  if(tLen == 0) {
      return "";
  }
  if(tLen == 1) {
      return strs[0];
  }
  while(found == true) {
    for(int i=1;i<tLen;i++) {
      int lLen = strs[i].length();
      if(idx > lLen || idx > strs[0].length() || strs[i][idx] != strs[0][idx]) {
        //cout << "idx " << idx << endl;
        found = false;
        break; 
      }
    }
    idx += 1;
  }
   return strs[0].substr(0,idx-1);
}

int main(int argc, char *argv[])
{
 
  vector<string> svec( {"",""} );
  string str  = longestCommonPrefix(svec);
  cout << str  << endl;
  return 0;
}
