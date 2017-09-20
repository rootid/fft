// Image Manipulation
// You are given an n x n square 2D matrix that represents the pixels of an
// image.
// Rotate it by 90 degrees in the clockwise direction.
// Example:
// Input Matrix :
//              1 0
//              0 1
// Output       :
//              0 1
//              1 0
public class ImageManipulation {
  public static int[][] rotate(int[][] matrix) {
    int s = 0, e = matrix.length - 1;
    while (s < e) {
      int[] temp = matrix[s];
      matrix[s] = matrix[e];
      matrix[e] = temp;
      s++;
      e--;
    }

    for (int i = 0; i < matrix.length; i++) {
      for (int j = i + 1; j < matrix[i].length; j++) {
        int temp = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = temp;
      }
    }
    return matrix.
  }
}
