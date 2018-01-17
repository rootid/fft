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


/*
 * anticlockwise rotate
 * L-R swap, Transponse 
 * 1 2 3     3 2 1     3 6 9
 * 4 5 6  => 6 5 4  => 2 5 8
 * 7 8 9     9 8 7     1 4 7
*/


/*
 * clockwise rotate
 * T/D swap, Trasponse 
 * 1 2 3     7 8 9     7 4 1
 * 4 5 6  => 4 5 6  => 8 5 2
 * 7 8 9     1 2 3     9 6 3
*/

public class RotateASquareImageCounterclockwise {
  public static void rotateSquareImageCCW(int[][] matrix) {
    leftRightFlip(matrix);
    transposeMatrix(matrix);
  }
  public static void transposeMatrix(int[][] matrix) {
    int m = matrix.length;
    int n = matrix[0].length;
    for (int i = 0; i < m; i++)
      for (int j = i + 1; j < n; j++) doSwap(matrix, i, j, j, i);
  }

  public static void leftRightFlip(int[][] matrix) {
    int m = matrix.length;
    int n = matrix[0].length;
    for (int colIdx = 0; colIdx < n / 2; colIdx++)
      for (int i = 0; i < m; i++) doSwap(matrix, i, colIdx, i, n - colIdx - 1); //i = same row, colIdx,n-colIdx : diff column
  }

  private static void doSwap(int[][] matrix, int i, int j, int k, int l) {
    int tmp = matrix[i][j];
    matrix[i][j] = matrix[k][l];
    matrix[k][l] = tmp;
  }

   //Rotate 90deg clockwise (Ring-By-Ring solution)
   public void rotate(int[][] matrix) {
       int n = matrix.length, temp;
   	for(int i = 0; i < n / 2; i++)
   		for(int j = i; j < n - i - 1; j++) {
   			temp = matrix[i][j];
   			matrix[i][j] = matrix[n - j - 1][i];
   			matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
   			matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
   			matrix[j][n - i - 1] = temp;
   		}
   }
}
