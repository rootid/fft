//Isomorphic Strings
//Given two strings s and t, determine if they are isomorphic.
//Two strings are isomorphic if the characters in s can be replaced to get t.
//All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.
//For example,
//Given "egg", "add", return true.
//Given "foo", "bar", return false.
//Given "paper", "title", return true

#include<iostream>
#include<string>
using namespace std;
bool isIsomorphic(string s, string t) {
    int t1[256],t2[256];
    for(int i=0;i<256;i++) {
         t1[i] = -1;
         t2[i] = -1;
     }
    int sLen = s.length();
    int tLen = t.length();
    if(sLen != tLen) {
         return false;
    }
    for(int i=0;i<sLen;i++) {
        int t1Idx = s[i] ;
        int t2Idx = t[i] ;
        if(t1[t1Idx] != t2[t2Idx]) {
            return false;
        }
        t1[t1Idx] = i;
        t2[t2Idx] = i;
    }
    return true;
}
int main() {
  //isIsomorphic("ab","ab");
  isIsomorphic("ab","aa");
}
