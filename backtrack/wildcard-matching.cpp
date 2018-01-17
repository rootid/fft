
//Implement wildcard pattern matching with support for '?' and '*'.
//'?' Matches any single character.
//'*' Matches any sequence of characters (including the empty sequence).
//The matching should cover the entire input string (not partial).
//The function prototype should be:
//bool isMatch(const char *s, const char *p)
//	Some examples:
//	isMatch("aa","a") → false
//	isMatch("aa","aa") → true
//	isMatch("aaa","aa") → false
//	isMatch("aa", "*") → true
//	isMatch("aa", "a*") → true
//	isMatch("ab", "?*") → true
//	isMatch("aab", "c*a*b") → false

//######################################### Dynamic + iterative ########################################
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        bool f[m + 1][n + 1];
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for(int i = 1; i <= n; i ++) {
            f[0][i] = p[i - 1] == '*' && f[0][i - 1];
        }
        for(int i = 1; i <= m; i ++) {
            for(int j = 1; j <= n; j ++) {
                if(p[j - 1] != '*') {
                    if(p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                        f[i][j] = f[i - 1][j - 1];
                    }
                }
                else {
                    f[i][j] = (f[i][j - 1] || f[i - 1][j]);
                }
            }
        }
        return f[m][n];
    }
};

//######################################### Bad ########################################
//aa , aa - > fail
class Solution {
public:
    bool isMatch(string s, string t) { 
      int m = s.size();
      int n = t.size();
      vector<vector<bool>> D(m+1,vector<bool>(n+1,false));
      D[0][0] = true; 
      for(int j=1;j<=n; j++){ 
        D[0][j] = D[0][j-1] && t[j-1]=='*';
			  if(!D[0][j]) break; 
      }
      for(int j=1; j<=n; j++){
        for(int i=1; i<=m; i++) { // D[i][j] is false, D[i][j + 1] may be true?
          if(t[j-1]=='*'){
            D[i][j] = D[i-1][j-1] || D[i-1][j] || D[i][j-1];
          } else { 
            D[i][j] = D[i-1][j-1] &&(s[i-1] == t[j-1] || t[j-1]=='?'); 
          } 
          if(!D[i][j]) break; 
        } 
      } 
      return D[m][n]; 
    }
};

