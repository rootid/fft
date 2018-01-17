import java.util.*;
// You're given a 2D Boggle Board which contains an m x n matrix of chars -
// char[][] board, and a String - word. Write a method - boggleSearch that
// searches the Boggle Board for the presence of the input word. Words on the
// board can be constructed with sequentially adjacent letters, where adjacent
// letters are horizontal or vertical neighbors (not diagonal). Also, each
// letter on the Boggle Board must be used only once.
// Example:
// Input Board :
//{
//    {A, O, L},
//    {D, E, L},
//    {G, H, I},
//}
// Word: "HELLO"
// Output: true

// T(k)=4(T(k-1))=4*4T(k-2)=....=.. 4^k.
// TC : (mn*4^k)
public class BoggleSearch {
  public static boolean boggleSearch(char[][] board, String word) {
    if (board == null || board.length == 0) return false;
    int m = board.length;
    int n = board[0].length;
    char[] wArr = word.toCharArray();
    boolean isFound = false;
    for (int i = 0; i < m; i++) {
      if (isFound == true) return true;
      for (int j = 0; j < n; j++) {
        HashSet<Integer> visited = new HashSet<>();
        if (wArr[0] == board[i][j]) {
          if (boggleSearchHelper(board, wArr, 0, i, j, visited) == true) {
            isFound = true;
            break;
          }
          // if(exist(board,i,j,word,0) == true) { isFound = true; break;}
        }
      }
    }
    return isFound;
  }

  //### extra space
  private static boolean boggleSearchHelper(char[][] board, char[] wArr, int k,
                                            int i, int j,
                                            HashSet<Integer> visited) {
    int m = board.length;
    int n = board[0].length;
    int o = wArr.length;
    if (k == o) return true;
    if (i >= m || i < 0 || j >= n || j < 0 || board[i][j] != wArr[k] ||
        visited.contains(i * n + j))
      return false;
    if (board[i][j] == wArr[k]) {
      visited.add(i * n + j);
      // NOTE : highly sensitive to path
      return (
          boggleSearchHelper(board, wArr, k + 1, i - 1, j, visited)       // vt
          || boggleSearchHelper(board, wArr, k + 1, i, j - 1, visited)    // hz
          || boggleSearchHelper(board, wArr, k + 1, i, j + 1, visited)    // vt
          || boggleSearchHelper(board, wArr, k + 1, i + 1, j, visited));  // hz
    }
    return false;
  }

  //##In place##
  private static boolean exist(char[][] board, int i, int j, String word,
                               int ind) {
    if (ind == word.length()) return true;
    if (i > board.length - 1 || i < 0 || j < 0 || j > board[0].length - 1 ||
        board[i][j] != word.charAt(ind))
      return false;
    board[i][j] = '*';
    boolean result = exist(board, i - 1, j, word, ind + 1) ||
                     exist(board, i, j - 1, word, ind + 1) ||
                     exist(board, i, j + 1, word, ind + 1) ||
                     exist(board, i + 1, j, word, ind + 1);
    board[i][j] = word.charAt(ind);
    return result;
  }
}
