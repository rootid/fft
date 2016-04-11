//ZigZag Conversion
//The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
//P   A   H   N
//A P L S I I G
//Y   I   R
//And then read line by line: "PAHNAPLSIIGYIR"
//Write the code that will take a string and make this conversion given a number of rows:
//string convert(string text, int nRows);
//convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
#include<iostream>
#include<string>
#include<vector>
using namespace std;

string convert(string s, int numRows) {
  
  //3-rows,columns
  vector<vector<char> > t(3,vector<char>());
  string result;
  int len = s.size(); 

  int rowNum = 0;
  int offset= 1;
  for(int i=0;i<len;i++) {
    t[rowNum].push_back(s[i]);
    //cout << "R = " << rowNum << endl;
    rowNum += offset;
    if(rowNum == numRows - 1) {
      offset = -1;
    } else if(rowNum == 0) {
      offset = 1;
    }
  }
  for (int i=0;i<numRows;i++) {
    int iLen = t[i].size();
    for(int j=0;j<iLen;j++) {
      result += t[i][j] ;
    }
  }
  return result; 
}

int main() {
  string result = convert("PAYPALISHIRING",3);
  //string result = convert("ABCD",2);  // ACBD
  cout << result  << endl;
}
