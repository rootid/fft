// Matrix Max Sum Path with Dynamic Programming
// Given an m x n matrix filled with non-negative integers, use dynamic
// programming techniques to find the maximum sum along a path from the top-left
// of the grid to the bottom-right. Return this maximum sum. The direction of
// movement is limited to right and down.
// Example:
// Input Matrix :
//    1 2 3
//    4 5 6
//    7 8 9
// Output  : 1 + 4 + 7 + 8 + 9 = 29
// Note:
// You may have previously solved the DFS variant of this problem. That won't
// work for large sized matrices - just consider the size of the recursion tree
// for a 100x100 matrix! Dynamic Programming should afford a better solution.

public class MatrixMaxSumPath {
  // Iteration
  public static int matrixMaxSumDP(int[][] grid) {
    int m = grid.length;
    int n = m == 0 ? 0 : grid[0].length;
    if (n == 0) return 0;
    int[][] memo = new int[m + 1][n + 1];
    for (int i = 1; i < memo.length; i++) {
      for (int j = 1; j < memo[0].length; j++) {
        memo[i][j] =
            grid[i - 1][j - 1] + Math.max(memo[i - 1][j], memo[i][j - 1]);
      }
    }
    return memo[m][n];
  }

  // Init + Iteration
  public static int matrixMaxSumDPUgly(int[][] grid) {
    int m = grid.length;
    int n = m == 0 ? 0 : grid[0].length;
    if (n == 0) return 0;
    int[][] memo = new int[m][n];
    memo[0] = grid[0];
    for (int i = 1; i < m; i++) {
      memo[i][0] = memo[i - 1][0] + grid[i][0];
    }
    for (int j = 1; j < n; j++) {
      memo[0][j] = memo[0][j - 1] + grid[0][j];
    }
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        memo[i][j] = grid[i][j] + Math.max(memo[i - 1][j], memo[i][j - 1]);
      }
    }
    return memo[m - 1][n - 1];
  }
}
