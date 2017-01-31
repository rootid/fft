// Longest Palindrome
//Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.
//This is case sensitive, for example "Aa" is not considered a palindrome here.
//Note:
//Assume the length of given string will not exceed 1,010.
//Example:
//Input:
//"abccccdd"
//Output:
//7
//Explanation:
//One longest palindrome that can be built is "dccaccd", whose length is 7.

#include<iostream>
#include<string>
#include<assert.h>
#include<vector>
using namespace std;

int longestPalindrome(string s) {
      assert(s.size() <= 1010);
      
      int pal_len = 0;
      vector<int> c_store(256,0);
      bool is_odd = false;
      for(int i=0;i<s.size();i++) {
          c_store[s[i]]++;
      }
      for(int j=0;j<256;j++) {
        if(c_store[j] % 2 == 0) {
            pal_len += c_store[j];
          cout <<  "pal_len = " << pal_len << endl;
        } else {
            pal_len += (c_store[j] - 1);
          cout <<  "O pal_len = " << pal_len << endl;
            is_odd = true;
        }
      }
      
      if(is_odd) {
           pal_len += 1;
      }
     
      cout <<  "pal_len = " << pal_len << endl;
      return pal_len;
}
int main() {
  string s = "abccccdd";
  longestPalindrome(s);
}
