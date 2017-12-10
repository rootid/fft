//Regular Expression Matching
//Implement regular expression matching with support for '.' and '*'.
//'.' Matches any single character.
//'*' Matches zero or more of the preceding element.
//The matching should cover the entire input string (not partial).
//The function prototype should be:
//bool isMatch(const char *s, const char *p)
//Some examples:
//isMatch("aa","a") → false
//isMatch("aa","aa") → true
//isMatch("aaa","aa") → false
//isMatch("aa", "a*") → true
//isMatch("aa", ".*") → true
//isMatch("ab", ".*") → true
//isMatch("aab", "c*a*b") → true
//
//

//######################################### Recursive ########################################
boolean isMatchHelper(String s, String p) {
    int pLen = p.length();
    int sLen = s.length();
    if (pLen == 0) return sLen == 0;
    if (pLen > 1 && '*' == p.charAt(1))
      return (isMatchHelper(s, p.substring(2))  //w/o matching x* => i.e. ends with 'a' //No match skip Regex
			  || sLen > 0 && (s.charAt(0) == p.charAt(0) || '.' == p.charAt(0)) //'matched 'last char/'any'
			  && isMatchHelper(s.substring(1), p));  //abba, "ab*a"
    else
      return sLen > 0 
		  && (s.charAt(0) == p.charAt(0) || '.' == p.charAt(0)) 
		  && isMatchHelper(s.substring(1), p.substring(1));  //starts with 'matched current char'/'any'
  }

public boolean isMatch(String str, String pattern) {
    return isMatchHelper(str, pattern);
}

//######################################### Dynamic + iterative ########################################
public boolean isMatch(String s, String p) {
        /**
         * f[i][j]: if s[0..i-1] matches p[0..j-1]
         * if p[j - 1] != '*'
         *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
         * if p[j - 1] == '*', denote p[j - 2] with x
         *      f[i][j] is true iff any of the following is true
         *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
         *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
         * '.' matches any single character
         */
        int m = s.length(), n = p.length();
        boolean[][] f = new boolean[m+1][n+1];
        
        f[0][0] = true;
        //initialization 
        for (int i = 1; i <= m; i++) f[i][0] = false; //single char

        // p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
		// p = ".*.*"
        for (int j = 1; j <= n; j++) f[0][j] = j > 1 && '*' == p.charAt(j - 1) && f[0][j - 2];  //NOTE : start from 2
       
        //Top-down traversal using pattern checks p[j - 1]
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p.charAt(j - 1) != '*') f[i][j] = f[i - 1][j - 1] && (s.charAt(i - 1) == p.charAt(j - 1) || '.' == p.charAt(j - 1));
                else f[i][j] = f[i][j - 2] || (s.charAt(i - 1) == p.charAt(j - 2) || '.' == p.charAt(j - 2)) && f[i - 1][j];
                    //lookback by 2 position (2 position . or char)
                    // p.charAt(0] cannot be '*' so no need to check "j > 1" here
            } 
        }
        return f[m][n];
 }

//######################################### Recursive ########################################
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty())    return s.empty();
        
        if ('*' == p[1])
            // x* matches empty string or at least one character: x* -> xx*
            // *s is to ensure s is non-empty
            return (isMatch(s, p.substr(2)) || !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p));
        else
            return !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p.substr(1));
    }
};

//######################################### Dynamic + iterative ########################################
class Solution {
public:
    bool isMatch(string s, string p) {
        /**
         * f[i][j]: if s[0..i-1] matches p[0..j-1]
         * if p[j - 1] != '*'
         *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
         * if p[j - 1] == '*', denote p[j - 2] with x
         *      f[i][j] is true iff any of the following is true
         *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
         *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
         * '.' matches any single character
         */
        int m = s.size(), n = p.size();
        vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));
        
        f[0][0] = true;
        //initialization 
        for (int i = 1; i <= m; i++) {
            f[i][0] = false; //single char
        }
        // p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
        for (int j = 1; j <= n; j++) {
            f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];  
        }
       
        //Top-down traversal using pattern checks p[j - 1]
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] != '*') {
                    f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
                }
                else {
                    //lookback by 2 position (2 position . or char)
                    // p[0] cannot be '*' so no need to check "j > 1" here
                    f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];
                }
            } 
        }
        return f[m][n];
    }
};

bool isMatch(const char *s, const char *p) { 
  if (!*p) 
    return (!*s); 
  if ('*' == *(p + 1)) { 
    // x* matches empty string or at least one character: x* -> xx*
    // *s is to ensure s is non-empty 
    return (isMatch(s, p + 2) || *s && (*s == *p || '.' == *p) && isMatch(s + 1, p)); //keep s + ^ p by 2(skip *) 
  } else { 
    if (!*s)    
      return false; 
    return (*s == *p || '.' == *p) ? isMatch(s + 1, p + 1) : false; 
  } 
}

