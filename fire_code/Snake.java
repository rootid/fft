import java.util.*; //Data structures
// Snake
// Let's have some fun with 2D Matrices! Write a method findSpiral to traverse a
// 2D matrix of
// ints in a clockwise spiral order and append the elements to an output
// ArrayList if Integers.
// Example:
// Input Matrix :
//    {1, 2, 3}
//    {4, 5, 6}
//    {7, 8, 9}
// Output ArrayList:[1, 2, 3, 6, 9, 8, 7, 4, 5]
//
public class Snake {
  public static ArrayList<Integer> findSpiral(int[][] arr) {
    ArrayList<Integer> resultList = new ArrayList<>();
    int m = arr.length;
    if (m == 0) return resultList;
    int n = arr[0].length;
    int top = 0, left = 0, bottom = m - 1, right = n - 1;
    int cnt = 0;
    while (top <= bottom && left <= right) {
      for (int i = left; i <= right; i++, cnt++) resultList.add(arr[top][i]);
      top++;

      for (int i = top; i <= bottom; i++, cnt++) resultList.add(arr[i][right]);
      right--;

      for (int i = right; i >= left && top <= bottom; i--, cnt++)
        resultList.add(arr[bottom][i]);
      bottom--;

      for (int i = bottom; i >= top && left <= right; i--, cnt++)
        resultList.add(arr[i][left]);
      left++;
    }
    return resultList;
  }

  public static ArrayList<Integer> findSpiralWithStateMachine(int[][] arr) {
    ArrayList<Integer> ans = new ArrayList<>();
    int m = arr.length;
    if (m == 0) return ans;
    int dir = 0;
    int n = arr[0].length;
    int top = 0, left = 0, bottom = m - 1, right = n - 1;
    while (ans.size() != m * n) {
      if (dir == 0) {  // Right
        for (int i = left; i <= right; ++i) ans.add(arr[top][i]);
        top++;
      } else if (dir == 1) {  // Down
        for (int i = top; i <= bottom; ++i) ans.add(arr[i][right]);
        right--;
      } else if (dir == 2) {  // Left
        for (int i = right; i >= left; --i) ans.add(arr[bottom][i]);
        bottom--;
      } else {  // Up
        for (int i = bottom; i >= top; --i) ans.add(arr[i][left]);
        left++;
      }
      dir = (dir + 1) % 4;
    }
    return ans;
  }
}
