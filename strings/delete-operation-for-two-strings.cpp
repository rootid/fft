//Delete Operation for Two Strings
//Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, where in each step you can delete one character in either string.
//Example 1:
//Input: "sea", "eat"
//Output: 2
//Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
//Note:
//The length of given words won't exceed 500.
//Characters in given words can only be lower-case letters.



//############################################# Top-Down DP ############################################# 
//int m = word1.size();
//int n = word2.size();
//DP array dp[m + 1][n + 1]
//dp[i][j] means how many operations we need to make word1[0 - i] and word2[0-j] equal.
//Initialization:
//dp[0][j] = 0,1,2,3...n
//dp[i][0] = 0,1,2,3...m
//we need to compare the word1[i] and word2[j], and return dp[m][n]
int minDistance(string word1, string word2) {
     int m = word1.size();
     int n = word2.size();
     int dp[m + 1][n + 1] = {};
     for(int i = 1; i <= m; i++){
         dp[i][0] = i;
     }
     for(int j = 1; j <= n; j++){
         dp[0][j] = j;
     }
     for(int i = 1; i <= m; i++){
         for(int j = 1; j <= n; j++){
             if(word1[i - 1] == word2[j - 1]){
                 dp[i][j] = dp[i - 1][j - 1];
             } else {
                 dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
             }
         }
     }
     return dp[m][n];
}

//############################################# Bottom-up DP ############################################# 
int minDistance(string a, string b) {
     int m = a.size(), n = b.size();
     vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
     dp[m][n] = 0;
     for (int i = m - 1; i >= 0; i--) {
         dp[i][n] = dp[i + 1][n] + 1;
     }
     for (int j = n - 1; j >= 0; j--) {
         dp[m][j] = dp[m][j + 1] + 1;
     }

     for (int i = m - 1; i >= 0; i--) {
         for (int j = n - 1; j >= 0; j--) {
             int dela = 1 + dp[i + 1][j];
             int delb = 1 + dp[i][j + 1];
             int delab = (a[i] == b[j] ? 0 : 2) + dp[i + 1][j + 1];
             dp[i][j] = std::min({dela, delb, delab});
         }
     }
     return dp[0][0]; 
}

//########################### Top down DP + Recursion ########################### 
//The transition/cost function is the minimum of three cases:
//1. Skip character in both string (dp[i - 1][j - 1]).
//  i.e. Cost function (2/0)
//  Add two deleted characters if the character is different
//  Add zero deleted characters if the character is the same (w1[i] == w2[j])
//2. Skip character in the first string (dp[i - 1][j]). Add one deleted character
//3. Skip character in the second string (dp[i][j - 1]). Add one deleted one character
int minDistance(string w1, string w2) {
    if (w1.size() == 0 || w2.size() == 0) {
      return w1.size() + w2.size();
    }
    vector<vector<int> > dp(w1.size(), vector<int>(w2.size(), 0));
    for (int i = 0; i < w1.size(); ++i) {
        for (int j = 0; j < w2.size(); ++j) {
            dp[i][j] = min((i == 0 || j == 0 ? max(i, j) : dp[i - 1][j - 1]) + (w1[i] == w2[j] ? 0 : 2),
                1 + min(i == 0 ? j + 1 : dp[i - 1][j], j == 0 ? i + 1 : dp[i][j - 1]));
        }
    }
    return dp[w1.size() - 1][w2.size() - 1];
}


//########################### Memoization ########################### 
int minDistance(string& w1, string& w2, int p1, int p2, vector<vector<int>>& dp) {
    if (p1 == w1.size() || p2 == w2.size()) {
      return w1.size() - p1 + w2.size() - p2;
    }
    return dp[p1][p2] != - 1 ? dp[p1][p2] : dp[p1][p2] = 
        min(w1[p1] == w2[p2] ? minDistance(w1, w2, p1 + 1, p2 + 1, dp) : INT_MAX,
            1 + min(minDistance(w1, w2, p1 + 1, p2, dp), minDistance(w1, w2, p1, p2 + 1, dp)));
}
int minDistance(string word1, string word2) {
    vector<vector<int>> dp(word1.size(), vector<int>(word2.size(), -1));
    return minDistance(word1, word2, 0, 0, dp);
}



//########################################### Pytonic  ########################################### 
//Let dp(i, j) be the answer for strings A[i:] and B[j:]. Let's try to compute it by a top-down dp:
//
//When i == len(A) or j == len(B), one of the strings is empty, so the answer is just the sum of the remaining lengths.
//When A[i] == B[j], the answer is just dp(i+1, j+1). For example, when evaluating the distance between "acai" and "apple", we only need to look at the distance between "cai" and "pple".
//When A[i] != B[j], then they both cannot be in the final word, so we either delete A[i] or B[j]. Thus, our answer is 1 + min(dp(i+1, j), dp(i, j+1)).
//def minDistance(self, A, B):
//    memo = {}
//    def dp(i, j):
//        if (i, j) not in memo:
//            if i == len(A) or j == len(B):
//                ans = len(A) + len(B) - i - j
//            elif A[i] == B[j]:
//                ans = dp(i+1, j+1)
//            else:
//                ans = 1 + min(dp(i+1, j), dp(i, j+1))
//            memo[i, j] = ans
//        return memo[i, j]
//    return dp(0, 0)
//We could have also attempted a bottom-up DP, as shown below.
//
//def minDistance(self, A, B):
//    M, N = len(A), len(B)
//    dp = [[0] * (N+1) for _ in xrange(M+1)]
//    
//    for i in xrange(M):
//        dp[i][-1] = M-i
//    for j in xrange(N):
//        dp[-1][j] = N-j
//        
//    for i in xrange(M-1, -1, -1):
//        for j in xrange(N-1, -1, -1):
//            if A[i] == B[j]:
//                dp[i][j] = dp[i+1][j+1]
//            else:
//                dp[i][j] = 1 + min(dp[i+1][j], dp[i][j+1])
//    
//    return dp[0][0]
