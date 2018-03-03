//Perfect Squares
//Given a positive integer n, find the least number of perfect square numbers
//(for example, 1, 4, 9, 16, ...) which sum to n.
//For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13,
//return 2 because 13 = 4 + 9.

int numSquares(int n) {

    vector<int> dp(n+1,INT_MAX);

    for(int i=0;i*i<=n;i++) {
        dp[i*i] = 1;
    }

    for(int a=0;a<=n;a++) {
        for(int b=0;a+b*b<=n;b++){
           dp[a + b*b] = min(dp[a] + 1, dp[a + b * b]);
        }
    }
    return dp[n];
}
