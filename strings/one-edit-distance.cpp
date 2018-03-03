//One Edit Distance
//Given two strings S and T, determine if they are both one edit distance
//apart.
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

//S: k i t t e n
//T: k i t *t* e n
//In fact, cases 1 (substitue), 2(insert) and 3(delete) can be further handled
//using the same piece of code.
//For strings of the same length, once we find a mismatch, we just substitute
//one to be another and check whether
//they are now the same. For strings of one apart in lengths, we insert the
//deleted character of the longer string
//into the shorter one and compare whether they are the same.
//S = "ab" and T = "abc".
bool isOneEditDistance(string s, string t) {
    int m = s.size(), n = t.size();
    if (m > n) return isOneEditDistance(t, s);
    if (n - m > 1 || s.equals(t)) return false;
    for (int i = 0; i < m; i++) //m(t) > n(s)
        if (s[i] != t[i]) {
            if (m == n) s[i] = t[i]; //subtitute case
            else s.insert(i, 1, t[i]); //insert/delete case
            break;
        }
    return s.equals(t) || t.equals(s + t[n - 1]);
}

//If s and t are one distance away then no matter it is insert or delete or
//replace the count of common characters must be max(m, n) - 1, where m is the
//length of s and n is the length of t. It is easy to see that the reverse is
//also true.
//Assume the length of common prefix (from left to right) is i and the length
//of common suffix after i (from right to left) is j, the answer is then max(m,
//n) - 1 == i + j
//Example 1 (1 replace)
//s = "abcdefg", m = 7
//t = "abcxefg", n = 7
//i = 3, j = 3
//max(m, n) - 1 == i + j is true
//Example 2 (0 edit)
//s = "abcdefg", m = 7
//t = "abcdefg", n = 7
//i = 7, j = 0
//max(m, n) - 1 == i + j is false
//Example 3 (1 insert)
//s = "abcdefg", m = 7
//t = "abcefg", n = 6
//i = 3, j = 3
//max(m, n) - 1 == i + j is true
//Example 4 (1 delete 1 insert)
//s = "abcdefg", m = 7
//t = "abcefgh", n = 7
//i = 3, j = 0
//max(m, n) - 1 == i + j is false
//The method is O(m+n) since any character is visited at most once.


//######################################### JAVA #########################################
public boolean isOneEditDistance(String s, String t) {
    int m = s.length(), n = t.length();
    if (Math.abs(m - n) > 1) return false;
    int k = Math.min(m, n);
    int i = 0, j = 0;
    while (i < k && s.charAt(i) == t.charAt(i)) ++i;  //match from start
	//i : Matched count
    while (j < k - i && s.charAt(m - 1 - j) == t.charAt(n - 1 - j)) ++j; //match from end
	//j : Matched count
    return m + n - k - 1 == i + j;
}
// Runtime : 2ms
//######################################### Python #########################################
def isOneEditDistance(self, s, t):
    n, m = len(s), len(t)
    if abs(n - m) > 1:
        return False
    k = min(n, m)
    i = j = 0
    while i < k and s[i] == t[i]:
        i += 1
    while j < k - i and s[~j] == t[~j]:
        j += 1
    return max(n, m) - (i + j) == 1
