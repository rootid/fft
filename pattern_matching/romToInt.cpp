//Roman to Integer 

//Given a roman numeral, convert it to an integer.
//Input is guaranteed to be within the range from 1 to 3999.


#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<limits.h>
#include<stdlib.h>

using namespace std;

int romanToInt(string s) {

  int len = s.length();
  if(len == 0) {
    return len;
  }
  unordered_map<char,int> rMap = { {'I',1}
                                   ,{'V',5} 
                                   ,{'X',10} 
                                   ,{'L',50} 
                                   ,{'C',100} 
                                   ,{'D',500}
                                   ,{'M',1000} };
  int sum = 0;
  sum = rMap[ s[len-1] ];
  for(int i=len-2;i>=0;i--)  {
    if(rMap[ s[i] ] >= rMap[ s[i+1] ]) { //DCXXI
      sum += rMap[ s[i] ];
    } else {
      sum -= rMap[ s[i] ];
    }
  }
  return sum;
}

int main() {

  //int result = romanToInt("IX");
  int result = romanToInt("XI");
  cout << "R = " << result << endl;
}
