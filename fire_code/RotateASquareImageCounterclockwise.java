import java.util.*;
// Rotate_a Square Image Counterclockwise
// You are given a square 2D image matrix where each integer represents a pixel.
// Write a method rotateSquareImageCCW to rotate the image counterclockwise -
// in-place. This problem can be broken down into simpler sub-problems you've
// already solved earlier! Rotating an image counterclockwise can be achieved by
// taking the transpose of the image matrix and then flipping it on its
// horizontal axis. Source: en.wikipedia.org/wiki/Transpose
// Example:
// Input image :
// 1 0
// 1 0
// Modified to :
// 0 0
// 1 1

public class RotateASquareImageCounterclockwise {
  public static void rotateSquareImageCCW(int[][] matrix) {
    verticalFlip(matrix);
    transposeMatrix(matrix);
  }
  public static void transposeMatrix(int[][] matrix) {
    int m = matrix.length;
    int n = matrix[0].length;
    for (int i = 0; i < m; i++)
      for (int j = i + 1; j < n; j++) doSwap(matrix, i, j, j, i);
  }

  public static void verticalFlip(int[][] matrix) {
    int m = matrix.length;
    int n = matrix[0].length;
    for (int colIdx = 0; colIdx < n / 2; colIdx++)
      for (int i = 0; i < m; i++) doSwap(matrix, i, colIdx, i, n - colIdx - 1);
  }

  private static void doSwap(int[][] matrix, int i, int j, int k, int l) {
    int tmp = matrix[i][j];
    matrix[i][j] = matrix[k][l];
    matrix[k][l] = tmp;
  }
}
