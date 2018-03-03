//Longest Palindromic Subsequence
//Given a string s, find the longest palindromic subsequence's length in s. You
//may assume that the maximum length of s is 1000.
//Example 1:
//Input:
//"bbbab"
//Output:
//4
//One possible longest palindromic subsequence is "bbbb".
//Example 2:
//Input:
//"cbbd"
//Output:
//2
//One possible longest palindromic subsequence is "bb".

//########################################### 1D #########################################
//dp[i] : Longest palindrome subsequence starting at i
//T : O(n^2)
//S : O(n)
int longestPalindromeSubseq(string s) {
  int n = s.size(), res = 0;
  vector<int> dp(n, 1);
  for (int i = 1; i < n; i++) {
      int len = 0;
      for (int j = i - 1; j >= 0; j--) {
          int tmp = dp[j];
          if (s[j] == s[i]) {
              dp[j] = len + 2;
          }
          len = max(len, tmp);
      }
  }
  for (auto i : dp) {
      res = max(res, i);
  }
  return res;
}

//######################################### 2D #########################################
//
//dp[i][j]: longest palindrome subseq for s[i ... j] i <= j; i, j = 0 ... n-1
//dp[i][j]: the longest palindromic subsequence's length of substring(i, j)
///State transition:
//dp[i][j] = dp[i+1][j-1] + 2 if s.charAt(i) == s.charAt(j)
//otherwise, dp[i][j] = Math.max(dp[i+1][j], dp[i][j-1])
//Initialization: dp[i][i] = 1
int longestPalindromeSubseq(string s) {
    vector<vector<int> > dp(s.size(), vector<int>(s.size(),0));
    int len = s.size();
    for(int i = 0; i < len; i++)
        dp[i][i] = 1;
    for (int i = len - 1; i >= 0; i--) {
        for (int j = i + 1 ; j < len ; j++) {
            if(s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][len - 1];
}


//######################### reverse the string #########################
int longestPalindromeSubseq(string s) {
  reverse(s.begin(),s.end());
	int len = s.length();
	vector< vector<int> >dp(len+1,vector<int>(len+1,0));
	for(int i=1;i<=len;i++) {
		for(int j=1;j<=len;j++) {
			if(s[i-1]==t[j-1]) {
				dp[i][j] = max(dp[i][j],dp[i-1][j-1]+1);
			}
			dp[i][j] = max(dp[i][j],dp[i][j-1]);
			dp[i][j] = max(dp[i][j],dp[i-1][j]);
		}
	}
	return dp[len][len];
}

//######################### Reduce the problem to LCS #########################
public int longestPalindromeSubseq(String s) {
     int len = s.length();
     if(len < 2) return len;
     int[][] dp= new int[len+1][len+1];
     String reverse = new StringBuilder(s).reverse().toString();
     for(int i = 1; i <= len; i++) {
         for(int j = 1; j <= len; j++) {
             if(s.charAt(i-1) == reverse.charAt(j-1)) dp[i][j] = dp[i-1][j-1] + 1;
             else dp[i][j] = Math.max(dp[i-1][j], dp[i][j-1]);
         }
     }
     return dp[len][len];
 }
