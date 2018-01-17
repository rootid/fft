import java.util.*;
// Find the Transpose of a Square Matrix
// You are given a square 2D image matrix where each integer represents a pixel.
// Write a method transposeMatrix to transform the matrix into its Transpose -
// in-place.
// Example:Input image :
// 1 0
// 1 0
// Modified to :
// 1 1
// 0 0

public class FindTheTransposeOfASquareMatrix {
  public static void transposeMatrix(int[][] matrix) {
    int m = matrix.length;
    int n = matrix[0].length;
    for (int i = 0; i < m; i++) {
      for (int j = i + 1; j < n; j++) {
        int tmp = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = tmp;
      }
    }
  }
}
