import java.util.*;
// Print Paths
// You're given a 2D board which contains an m x n matrix of chars - char[][]
// board. Write a method - printPaths that prints all possible paths from the
// top left cell to the bottom right cell. Your method should return an
// ArrayList of Strings, where each String represents a path with characters
// appended in the order of movement. You're only allowed to move down and right
// on the board. The order of String insertion in the ArrayList does not matter.
// Example:
// Input Board :
//{
//    {A, X},
//    {D, E}
//}
// Output: ["ADE", "AXE"]

public class PrintPaths {
  private HashSet<Integer> visited = new HashSet<>();

  public ArrayList<String> printPaths(char[][] board) {
    StringBuffer st = new StringBuffer();
    ArrayList<String> strList = new ArrayList<>();
    printPathsHelper(board, 0, 0, st, strList);
    return strList;
  }

  public void printPathsHelper(char[][] board, int x, int y, StringBuffer st,
                               ArrayList<String> strList) {
    int m = board.length;
    int n = board[0].length;
    if (x == m - 1 && y == n - 1) {
      st.append(board[x][y]);
      strList.add(st.toString());
      st.deleteCharAt(st.length() - 1);
      return;
    }
    if (x < m && y < n) {
      st.append(board[x][y]);
      printPathsHelper(board, x + 1, y, st, strList);
      printPathsHelper(board, x, y + 1, st, strList);
      st.deleteCharAt(st.length() - 1);
    }
  }
}
