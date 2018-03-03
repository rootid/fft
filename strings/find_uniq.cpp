//First Unique Character in a String
//Given a string, find the first non-repeating character in it and return it's
//index. If it doesn't exist, return -1.
//Examples:
//s = "leetcode"
//return 0.
//s = "loveleetcode",
//return 2.
//Note: You may assume the string contain only lowercase letters.
//
#include<iostream>
#include<vector>
#include<string>
using namespace std;
int firstUniqChar(string s) {
       vector<int> store(256,-1);
       int len = s.length();
       if(len == 0) {
           return -1;
       }
       for(int i=0;i<len;i++) {
           if(store[s [i] ] == -1) {
               store[s[i] ] = i;
           } else {
               store[s [i]] = -2;
           }
       }
       int min = INT_MAX;
       for(int i=0;i<256;i++) {
        if(store[i] >= 0 && min > store[i] ) {
            min = store[i];
        }
    }
    if(min == INT_MAX) {
        return -1;
    }
    return min;
}

int firstUniqChar(string s) {
    vector<int> store(256,0);
    int len = s.length();
    if(len == 0) {
        return -1;
    }
    for(int i=0;i<len;i++) {
        store[s [i]]++;
    }
    for(int i=0;i<len;i++) {
        if(store[s[i]] == 1) {
            return i;
        }
    }
 return -1;
}
