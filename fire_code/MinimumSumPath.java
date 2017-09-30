// Given an m x n matrix filled with non-negative integers, find the minimum sum
// along a path from the top-left of the grid to the bottom-right which
// minimizes the sum of all numbers along it. Return this minimum sum. The
// direction of movement is limited to right and down.
// Example:
// Input Matrix :
//
//    1 2 3
//    4 5 6
//    7 8 9
// Output  : 21

public class MinimumSumPath {
  //##################### T+S = O(n^2) #####################
  public static int minWeightedPath(int[][] grid) {
    if (grid == null || grid.length == 0) return 0;
    int m = grid.length;
    int n = grid[0].length;
    int[][] dp = new int[m][n];
    dp[0][0] = grid[0][0];
    // row update
    for (int i = 1; i < grid.length; i++) dp[i][0] = dp[i - 1][0] + grid[i][0];
    // col update
    for (int j = 1; j < grid[0].length; j++)
      dp[0][j] = dp[0][j - 1] + grid[0][j];

    for (int i = 1; i < m; i++)
      for (int j = 1; j < n; j++)
        dp[i][j] += Math.min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];

    return dp[m - 1][n - 1];
  }
}
