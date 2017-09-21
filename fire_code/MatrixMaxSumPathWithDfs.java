// Given an m x n matrix filled with non-negative integers, use depth first
// search to find the maximum sum along a path from the top-left of the grid to
// the bottom-right. Return this maximum sum. The direction of movement is
// limited to right and down.
// Example:
// Input Matrix :
//    1 2 3
//    4 5 6
//    7 8 9
// Output  : 1 + 4 + 7 + 8 + 9 = 29

public class MatrixMaxSumPathWithDfs {
  public static int matrixMaxSumDfs(int[][] grid) {
    int m = grid.length;
    int n = grid[0].length;
    int sum = 0;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++) sum = Math.max(sum, matDFSHelper(grid, i, j));
    return sum;
  }

  private static int matDFSHelper(int[][] grid, int i, int j) {
    int m = grid.length;
    int n = grid[0].length;
    int sum = 0;
    if (i >= m || j >= n) return sum;
    // NOTE : select only max between right and bottom
    sum += grid[i][j] +
           Math.max(matDFSHelper(grid, i + 1, j), matDFSHelper(grid, i, j + 1));
    return sum;
  }

  //############################### DP ###############################
  public static int matrixMaxSumDfsWtihDP(int[][] grid) {
    int m = grid.length;
    int n = grid[0].length;
    int[][] dp = new int[m][n];
    for (int row = 0; row < m; row++) {
      for (int col = 0; col < n; col++) {
        dp[row][col] = grid[row][col];
        int upperMax = row > 0 ? dp[row - 1][col] : 0;
        int leftMax = col > 0 ? dp[row][col - 1] : 0;
        dp[row][col] += Math.max(upperMax, leftMax);
      }
    }
    return dp[m - 1][n - 1];
  }

  // public static int matrixMaxSumDfs(int[][] grid) {
  //    return matrixMaxSumDfs(grid, 0, 0);
  //}
  //
  // private static int matrixMaxSumDfs(int[][] grid, int row, int col) {
  //    if(row >= grid.length || col >= grid[0].length)
  //        return 0;
  //    return grid[row][col]+Math.max(matrixMaxSumDfs(grid, row+1, col),
  //    matrixMaxSumDfs(grid, row, col+1));
  //}
}
