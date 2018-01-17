// Minimum Window Substring
//Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
//For example,
//S = "ADOBECODEBANC"
//T = "ABC"
//Minimum window is "BANC".
//Note:
//If there is no such window in S that covers all characters in T, return the empty string "".
//If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
//

#include<iostream>
#include<string>
using namespace std;


//1. Use two pointers: start and end to represent a window.
//2. Move end to find a valid window.
//3. When a valid window is found, move start to find a smaller window.

string minWindow(string s, string t) {
  vector<int> tv(256,0);

  for(auto s:t) {
    tv[s]++;
  }
  
  int end=0;
  int start=0;
  int nxtStart = 0;
  int minLen= INT_MAX;
  int counter = t.size();
  int ls = s.size();
  while(end < ls) {
    if(tv[s[end]] > 0) {
      counter--;
    } 
    tv[s[end]]--;
    end++; //get the end
    while(counter == 0) {
        if(minLen > end-nxtStart) {
          minLen = end - nxtStart; //find 1st window
          start = nxtStart;
        }
        tv[s[nxtStart]]++;
        if(tv[s[nxtStart]] > 0) { 
          counter++;
        }
        nxtStart++; //update the start
    }
  }
  if(minLen != INT_MAX) {
    return s.substr(start,minLen);
  }
  return "";
}

int main() {

}
