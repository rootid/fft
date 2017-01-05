//One Edit Distance
//Given two strings S and T, determine if they are both one edit distance apart.
//
#include "../headers/global.hpp"
//Input:  s1 = "geeks", s2 = "geek"
//Output: yes
//Number of edits is 1
//Input:  s1 = "geeks", s2 = "geeks"
//Output: no
//Number of edits is 0
//Input:  s1 = "geaks", s2 = "geeks"
//Output: yes
//Number of edits is 1
//Input:  s1 = "peaks", s2 = "geeks"
//Output: no
//Number of edits is 2
 bool isOneEditDistance(string s, string t) {
    int m = s.length();
    int n = t.length();
    int cnt = 0;
    if(abs(m-n) > 1) {
      return false;
    }
    int no_of_compares = 0;
    for(int i=0,j=0;i<m && j < n;) {
      if(s[i] != t[j]) {
        //char mismatch
        if(m == n) {
          i++; j++;
        } else if(m < n) {
          j++; //== delete char from t 
        } else {
          i++;
        }
        cnt += 1;
      } else {
        i++; j++;
      }
      if(cnt > 1) {
          return false;
      }
      no_of_compares += 1;
    }
    if(no_of_compares  < m || no_of_compares  < n) {
        cnt += 1;
    }
    return cnt == 1;
}
int main() {

  isOneEditDistance("ab","ba");
}
