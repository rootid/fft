//Minimum Path Sum
//Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum
//of all numbers along its path.
//Note: You can only move either down or right at any point in time.




//#################### DP === O(n^2) ####################
//What we need to choose when we at the target/destination -> Left/Up
public int minPathSum(int[][] grid) {

    int m = grid.length;
    int n = grid[0].length;

    for(int i=1;i<m;i++) grid[i][0] += grid[i-1][0];
    for(int j=1;j<n;j++) grid[0][j] += grid[0][j-1];

    for(int i=1;i<m;i++)
        for(int j=1;j<n;j++)
            grid[i][j] += Math.min(grid[i-1][j], grid[i][j-1]);

    return grid[m-1][n-1];
}

///#################### DP === to interleaving string ####################
//
// minimum path sum of arriving at point (i, j) is S[i][j], then the state equation is S[i][j] = min(S[i - 1][j], S[i][j - 1]) + grid[i][j].
// Base cases
//1. topmost row (S[i - 1][j] does not exist)
//2. leftmost column (S[i][j - 1] does not exist).
//Suppose grid is like [1, 1, 1, 1], then the minimum sum to arrive at each point is simply an accumulation of previous
//points and the result is [1, 2, 3, 4].
int minPathSum(vector<vector<int> >& grid) {
     int m = grid.size();
     int n = grid[0].size();
     vector<vector<int> > sum(m, vector<int>(n, grid[0][0]));
     for (int i = 1; i < m; i++) {
         sum[i][0] = sum[i - 1][0] + grid[i][0];
     }
     for (int j = 1; j < n; j++) {
         sum[0][j] = sum[0][j - 1] + grid[0][j];
     }
     for (int i = 1; i < m; i++) {
         for (int j = 1; j < n; j++) {
             sum[i][j]  = min(sum[i - 1][j], sum[i][j - 1]) + grid[i][j];
         }
     }
     return sum[m - 1][n - 1];
}
///############################ DP (SPACE optimized) ############################
//sum[i][j], only need sum[i - 1][j] (at the current column) and sum[i][j - 1] (at the left column)
int minPathSum(vector<vector<int>>& grid) {
      int m = grid.size();
      int n = grid[0].size();
      vector<int> pre(m, grid[0][0]);
      vector<int> cur(m, 0);
      for (int i = 1; i < m; i++)
          pre[i] = pre[i - 1] + grid[i][0];
      for (int j = 1; j < n; j++) {
          cur[0] = pre[0] + grid[0][j];
          for (int i = 1; i < m; i++)
              cur[i] = min(cur[i - 1], pre[i]) + grid[i][j];
          swap(pre, cur);
      }
      return pre[m - 1];
}
///############################ DP (SPACE optimized) ############################
//pre is for recovering pre[i], which is simply cur[i] before its update
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<int> cur(m, grid[0][0]);
    for (int i = 1; i < m; i++)
        cur[i] = cur[i - 1] + grid[i][0];
    for (int j = 1; j < n; j++) {
        cur[0] += grid[0][j];
        for (int i = 1; i < m; i++)
            cur[i] = min(cur[i - 1], cur[i]) + grid[i][j];
    }
    return cur[m - 1];
}
//#################### O(1) SPACE ####################
int minPathSum(vector<vector<int>>& a) {
    int m=a.size();
    if(m==0) return 0;
    int n= a[0].size();

    for(int i = 0 ; i<m; i++  ){
        for(int j=0; j<n ; j++){
            int left= (j==0) ? INT_MAX : a[i][j-1];
            int up = (i==0) ? INT_MAX : a[i-1][j];
            if(i==0 && j==0) continue;
            a[i][j] += min(left, up );
        }
    }
    return a[m-1][n-1];
}
/* vim: set ts=4 sw=4 sts=4 tw=120 et: */
