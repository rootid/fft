//Compare Version Numbers
//https://leetcode.com/problems/compare-version-numbers/
#include<iostream>
using namespace std;

int getNum(string numStr) {
  int result = 0;
  for(int i=0;i<numStr.length();i++) {
    result = 10*result +  (numStr[i] - '0');
  }
  return result;
}


int compareVersion(string version1, string version2) {  

  int m = version1.length();
  int n = version2.length();
  int mIdx = 0;
  int nIdx = 0;
  int num1 = 0;
  int num2 = 0;
  int mCIdx = 0;
  int nCIdx = 0;
  while (mIdx < m || nIdx < n) {
    while(version1[mIdx] != '.' && mIdx < m) {
      mIdx += 1;
    }
    //cout << "mCIdx = " << mCIdx << "| mIdx = " << mIdx << endl;
    string r = "";
    if(mIdx != mCIdx)  {
       r = version1.substr(mCIdx,mIdx-mCIdx);
    }
    num1 = getNum(r);
    mIdx= mIdx+1;
    mCIdx = mIdx;

    while(version2[nIdx] != '.' && nIdx < n) {
      nIdx += 1;
    }
    
    string s = "";
    if(nIdx != nCIdx)  {
     s = version2.substr(nCIdx,nIdx-nCIdx);
    }
    num2 = getNum(s);
    nIdx= nIdx+1;
    nCIdx = nIdx;

    //cout << "r = " << r << "|s = " << s << endl;
    //cout << "num1 " << num1 << "num2 " << num2 << endl;
    if ( (num1 - num2) > 0 ) {
      return 1;
    } else if (num1- num2 < 0) {
      return -1;
    }
  }
  //cout << "both are equl" << endl;
    return 0; 
}


int main() {
    
  string version1 = "1";
  string version2 = "1.1";

  compareVersion(version1,version2);
}
