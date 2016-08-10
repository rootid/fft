//Given two binary strings, return their sum (also a binary string).
//
//For example,
//a = "11"
//b = "1"
//Return "100".
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string addBinary(string a, string b) {
      string result = "";
      int carry = 0;
      int idx = 0;
      while(carry != 0 || idx < a.size() || idx < b.size()) {
          if(idx < a.size() ){
              carry += (a[a.size() - 1 - idx] - '0');
          }
          if(idx <b.size()) {
              carry += (b[b.size() - 1 - idx] - '0');
          }
          result.push_back( (carry % 2) + '0');
          carry = carry/2;  
          idx += 1;
      }
      reverse(result.begin(),result.end());
      return result;
}


int main() {
  string a = "11";
  string b = "1";
  string r = addBinary(a,b);
  cout << " R = " << r << endl;
}
