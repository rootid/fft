//Distinct Subsequences
//Given a string S and a string T, count the number of distinct subsequences of T in S.
//A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of
//the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of
//"ABCDE" while "AEC" is not).
//Here is an example:
//S = "rabbbit", T = "rabbit"
//Return 3.


//########################### DP ###########################
//S: [acdabefbc] and T: [ab]
//first we check with a:
//            *  *
//       S = [acdabefbc]
//memST[1] = [0111222222]
//then we check with ab:
//
//                *  * ]
//       S = [acdabefbc]
//memST[1] = [0111222222]
//memST[2] = [0000022244]
//
//And the result is 4, as the distinct subsequences are:
//      S = [a   b    ]
//      S = [a      b ]
//      S = [   ab    ]
//      S = [   a   b ]

public int numDistinct(String s, String t) {
    int m = t.length();
    int n = s.length();
    if(n == 0) return 0;
    int[][] memST = new int[m+1][n+1];
    Arrays.fill(memST[0],1);
    for(int i=1;i<=t.length();i++) {
        for(int j=1;j<=s.length();j++) {
            if(t.charAt(i-1) == s.charAt(j-1))
                memST[i][j] = memST[i-1][j-1] + memST[i][j-1];
            else
                memST[i][j] = memST[i][j-1];
        }
    }
    return memST[m][n];
}

//########################### DP ###########################
int numDistinct(string s, string t) {
    int m = t.length(), n = s.length();
    vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0));
    //t is empty
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 1;
    }
    for (int j = 1; j <= n; j++) { //iterate over s
        for (int i = 1; i <= m; i++) { //iterate over t

            dp[i][j] = dp[i][j - 1] + (t[i - 1] == s[j - 1] ? dp[i - 1][j - 1] : 0);
        }
    }
    return dp[m][n];
}

//############################ Space optimized ############################
int numDistinct(string s, string t) {
    int m = t.length(), n = s.length();
    vector<int> cur(m + 1, 0);
    cur[0] = 1;
    for (int j = 1; j <= n; j++) {
        int pre = 1;
        for (int i = 1; i <= m; i++) {
            int temp = cur[i];
            cur[i] = cur[i] + (t[i - 1] == s[j - 1] ? pre : 0);
            pre = temp;
        }
    }
    return cur[m];
}


/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
