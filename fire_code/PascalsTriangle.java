import java.util.*;
// Pascal's Triangle
// Given an input parameter numRows, generate the first numRows number of rows
// of Pascal's triangle. As a quick refresher - in a Pascal's triangle, each
// number is equal to the sum of the two directly above it.
// Example:
// Input  : 4
// Output :
//        [
//             [1],
//            [1,1],
//           [1,2,1],
//          [1,3,3,1]
//        ]

public class PascalsTriangle {
  // K(i)(j)=K(i-1)(j-1)+K(i-1)(j) except for the first and last element
  public List<List<Integer>> generate(int numRows) {
    List<List<Integer>> triangle = new ArrayList<>();
    if (numRows <= 0) return triangle;
    for (int i = 0; i < numRows; i++) {
      List<Integer> row = new ArrayList<>();
      for (int j = 0; j < i + 1; j++) {
        if (j == 0 || j == i)
          row.add(1);
        else
          row.add(triangle.get(i - 1).get(j - 1) + triangle.get(i - 1).get(j));
      }
      triangle.add(row);
    }
    return triangle;
  }

  public static ArrayList<ArrayList<Integer>> generatePascalTriangle(
      int numRows) {
    ArrayList<ArrayList<Integer>> pascleTri = new ArrayList<>();
    if (numRows == 0) return pascleTri;
    for (int i = 0; i < numRows; i++) {
      ArrayList<Integer> row = new ArrayList<>();
      row.add(1);
      if (i >= 1) {
        ArrayList<Integer> prevRow = pascleTri.get(i - 1);
        for (int j = 1; j <= i - 1; j++)  // fill only [1,i) items
          row.add(prevRow.get(j) + prevRow.get(j - 1));
        row.add(1);
      }
      pascleTri.add(row);
    }
    return pascleTri;
  }
}
