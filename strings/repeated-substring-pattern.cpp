//Repeated Substring Pattern
//Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.
//Example 1:
//Input: "abab"
//Output: True
//Explanation: It's the substring "ab" twice.
//Example 2:
//Input: "aba"
//Output: False
//Example 3:
//Input: "abcabcabcabc"
//Output: True
//Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)

#include "../headers/global.hpp"
bool repeatedSubstringPattern(string str) {
  int n = str.length();
  for (int i = 1; i <= n / 2; i++) {
    //check left and right part of string
      if (n % i == 0 && str.substr(0, n - i) == str.substr(i)) {
          //cout << "i " << i << endl;
          //cout << "n-i " << str.substr(0, n - i) << endl;
          //cout << "i " << str.substr(i) << endl;
          return true;
      }
  }
  return false;
}

int main() {
  repeatedSubstringPattern ("aaaaaaaaaaaaaaaaaaaaa");
}
//aaaaaaaaaaaaaaaaaaaaa 
