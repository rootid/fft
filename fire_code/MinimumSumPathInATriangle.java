// Minimum Sum Path in a Triangle
// Given a 'triangle' as an ArrayList of ArrayLists of integers, with each list
// representing a level of the triangle, find the minimum sum achieved by
// following a top-down path and adding the integer at each level along the
// path. Movement is restricted to adjacent numbers from the top to the bottom.
// Note:
//- You can only traverse through adjacent nodes while moving up or down the
// triangle.
//- An adjacent node is defined as a node that is reached by moving down and
// left or down and right from a level. For eg, in the triangle shown below, if
// you are at the digit 3 in the second row, its adjacent nodes are 5 and 6
// Example:
// Input Triangle:
//[   [1],
//   [2, 3],
//  [4, 5, 6],
//[7, 8, 9, 10],
//]
// Output : 14 (1->2->4->7)
// Note: [..] denotes an ArrayList
//
//    1
//   1 0
//  1 2 3
// 7 2 3 1
//

public class MinimumSumPathInATriangle {
  //##################### DP/Bottom Up solution #####################
  public static int minTriangleDepthDP(ArrayList<ArrayList<Integer>> input) {
    int[] A = new int[input.size() + 1];
    for (int i = input.size() - 1; i >= 0; i--) {
      int choices = input.get(i).size();
      for (int j = 0; j < choices; j++) {
        A[j] = Math.min(A[j], A[j + 1]) + input.get(i).get(j);
      }
    }
    return A[0];
  }
  //############################# DFS #############################
  public static int minTriangleDepth(ArrayList<ArrayList<Integer>> input) {
    return dfsHelper(input, 0, 0);
  }

  public static int dfsHelper(ArrayList<ArrayList<Integer>> input, int row,
                              int column) {
    if (row >= input.size()) return 0;
    int curValue = input.get(row).get(column);
    int leftSum = dfsHelper(input, row + 1, column);
    int rightSum = dfsHelper(input, row + 1, column + 1);
    return curValue + Math.min(leftSum, rightSum);
  }
}

// int minSum = Integer.MAX_VALUE;
// for (int i = m - 2;i>= 0 ;i--) {
//     int choices = input.get(i).size();
//     for (int j=0;j<choices;j++) {
//         int tmp = Math.min(input.get(i).get(j) + input.get(i+1).get(j),
//                     input.get(i).get(j) + input.get(i+1).get(j+1));
//         minSum = Math.min(tmp,minSum);
//     }
// }
// return minSum;
