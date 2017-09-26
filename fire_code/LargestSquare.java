import java.util.*;
// Given a two dimensional matrix made up of 0's and 1's, find the largest
// square containing all 1's and return its 'area'. The 'area' is simply the sum
// of all integers enclosed in the square.
// Example:
// Input Matrix :
//  1101
//  1101
//  1111
// Output  : 4
public class LargestSquare {
  public static int largestSquare(char[][] matrix) {
    int rows = matrix.length, cols = rows > 0 ? matrix[0].length : 0;
    int[][] dp = new int[rows + 1][cols + 1];
    int maxsqlen = 0;
    for (int i = 1; i <= rows; i++) {
      for (int j = 1; j <= cols; j++) {
        if (matrix[i - 1][j - 1] == '1') {
          dp[i][j] =
              Math.min(Math.min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) +
              1;
          maxsqlen = Math.max(maxsqlen, dp[i][j]);
        }
      }
    }
    return maxsqlen * maxsqlen;
  }
}
