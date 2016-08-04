//Given a string, find the length of the longest substring without repeating characters.
//Examples:
//Given "abcabcbb", the answer is "abc", which the length is 3.
//Given "bbbbb", the answer is "b", with the length of 1.
//Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
//
#include<iostream>
#include<string>
using namespace std;
// "dvdf" : expected 3
int lengthOfLongestSubstring(string s) {
    int charSet[256] = {0};
    int minLen = 0;
    int curLen = 0;
    for(int i=0;i<s.length();i++) {
        if(charSet[s[i] ] != 0) {
            for(int i=0;i<256;i++) {
                charSet[i] = 0;
            }
            curLen = 0;
        }
        charSet[s[i] ] = 1;
        curLen += 1;
        if(curLen > minLen) {
            minLen = curLen;
        }
    }
    return minLen;
}
int main() {
}
