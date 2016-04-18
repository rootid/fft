//Valid Anagram
//Given two strings s and t, write a function to determine if t is an anagram of s.
//
//For example,
//s = "anagram", t = "nagaram", return true.
//s = "rat", t = "car", return false.


#include<iostream>
#include<vector>
#include<string>
#include<limits.h>
#include<stdlib.h>

using namespace std;


bool isAnagrams(string &s,string &s1) {

  int MAX_CHAR = 26;
  if (s.length() == s1.length()) {
    int len_ = s1.length();
    char mx[MAX_CHAR] = {0};
    for (int i=0;i<len_;i++) {
      mx[s[i] - 'a']++;   //aaaa
      mx[s1[i] - 'a']--;   //aaaa
    }
    for(int i=0;i<MAX_CHAR;i++) {
      if ( mx[i] != 0 ) {
        return false;
      }
    }
    return true; 
  }
  return false;
}


void testMe(string& s,string& s1) {

    if ( isAnagrams(s,s1) == true) {
      cout << " s= " << s<< "| s1= " << s1 << " are anagrams." << endl;
    } else {
      cout << " s= " << s<< "| s1= " << s1 << " are not anagrams." << endl;
    }
}


int main() {
    string s = "quick";
    string s1 = "fox"; 
    testMe(s1,s);

    s = "anagram";
    s1 = "nagaram"; 
    testMe(s1,s);
}
