//Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
//For example,
//Given:
//s1 = "aabcc",
//s2 = "dbbca",
//When s3 = "aadbbcbcac", return true.
//When s3 = "aadbbbaccc", return false.
//
//#################################### DP (2d) #################################### 
bool isInterleave(string s1, string s2, string s3) {
    int m= s1.size();
    int n = s2.size();
    int tlen = s3.size();
    if (tlen != m+n) {
      return false;
    }
    vector<vector<bool>> dp(m+1,vector<bool>(n+1, false));
    dp[0][0] = true;
    //Row init
    for (int i = 1; i<=m;i++)
        dp[i][0] = dp[i-1][0] && s3[i-1] == s1[i-1];            
    //Col init
    for (int j = 1; j<=n;j++)
        dp[0][j] = dp[0][j-1] && s3[j-1] == s2[j-1];
    for (int i = 1; i<=m;i++) {
        for (int j = 1; j<=n;j++) {
            dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) || (dp[i][j-1] && s2[j-1] == s3[i+j-1]); 
        }
    }
    return dp[m][n];        
}

//#################################### DP Optimized #################################### 
bool isInterleave(string s1, string s2, string s3) {
    int m = s1.length();
    int n = s2.length();
    int p = s3.length();
    
    if (m + n != p)  { 
      return false;
    }
    //initialize
    vector<bool> dp(n + 1);
    for (int j = 0; j <= n; j++)  {
      dp[j] = s2.substr(0, j) == s3.substr(0, j); 
    }
    
    for (int i = 1; i <= m; i++) {
        dp[0] = s1.substr(0, i)==s3.substr(0, i);
        for (int j = 1; j <= n; j++) {
            dp[j] = (dp[j] && s3[i+j-1]==s1[i-1]) || (dp[j-1] && s3[i+j-1]==s2[j-1]);
        }
    }
    return dp[n];
}

//############################################# BFS ############################################# 
bool isInterleave(string s1, string s2, string s3) {
      typedef pair<int, int> index;
      unordered_set<int> visited;
      queue<index> q;
      q.push(index(-1, -1));
      
      int cols = s2.size() + 1;
      while (!q.empty()) {
          index idx = q.front();
          q.pop();
          
          int i = idx.first + 1;
          int j = idx.second + 1;
          
          if (i == s1.size() && j == s2.size()) {
              return i + j == s3.size();
          }
          
          if (i + j < s3.size()) {
              char next = s3[i + j];
              if (i < s1.size() && s1[i] == next) {
                  if (visited.insert((i + 1) * cols + j).second) {
                      q.push(index(i, j - 1));
                  }
              }
              if (j < s2.size() && s2[j] == next) {
                  if (visited.insert(i * cols + j + 1).second) {
                      q.push(index(i - 1, j));
                  }
              }
          }
      }
      
      return false;
  }
